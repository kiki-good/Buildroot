/*
 * rngd_entsource.c -- Entropy source and conditioning
 *
 * Copyright (C) 2001 Philipp Rumpf
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335  USA
 */

#define _GNU_SOURCE

#ifndef HAVE_CONFIG_H
#error Invalid or missing autoconf build environment
#endif

#include "rng-tools-config.h"

#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <string.h>
#include <stddef.h>

#include "rngd.h"
#include "fips.h"
#include "exits.h"
#include "rngd_entsource.h"


/* The overhead incured when tpm returns the random nos as per TCG spec
 * it is 14 bytes.*/
#define TPM_GET_RNG_OVERHEAD	14

/* Read data from the entropy source */
int xread(void *buf, size_t size, struct rng *ent_src)
{
	size_t off = 0;
	ssize_t r;

	while (size > 0) {
		do {
			r = read(ent_src->rng_fd, buf + off, size);
		} while ((r == -1) && (errno == EINTR));
		if (r <= 0)
			break;
		off += r;
		size -= r;
	}

	if (size) {
		message(LOG_DAEMON|LOG_ERR, "read error\n");
		return -1;
	}
	return 0;
}

/* tpm rng read call to kernel has 13 bytes of overhead
 * the logic to process this involves reading to a temporary_buf
 * and copying the no generated to buf */
int xread_tpm(void *buf, size_t size, struct rng *ent_src)
{
	size_t bytes_read = 0;
	ssize_t r;
	int retval;
	unsigned char *temp_buf = NULL;
	unsigned char rng_cmd[] = {
		0, 193,            /* TPM_TAG_RQU_COMMAND */
		0, 0, 0, 14,       /* length */
		0, 0, 0, 70,       /* TPM_ORD_GetRandom */
		0, 0, 0, 0,        /* number of bytes to return */
	};
	char *offset;

	ent_src->rng_fd = open(ent_src->rng_name, O_RDWR);
	if (ent_src->rng_fd == -1) {
		message(LOG_ERR|LOG_INFO,"Unable to open file: %s",ent_src->rng_name);
		return -1;
	}

	temp_buf = (unsigned char *) malloc(size + TPM_GET_RNG_OVERHEAD);
	memset(temp_buf, 0, (size+TPM_GET_RNG_OVERHEAD));
	if (temp_buf == NULL) {
		message(LOG_ERR|LOG_INFO,"No memory");
		close(ent_src->rng_fd);
		return -1;
	}
	/* 32 bits has been reserved for random byte size */
	rng_cmd[13] = (unsigned char)(size & 0xFF);
	rng_cmd[12] = (unsigned char)((size >> 8) & 0xFF);
	rng_cmd[11] = (unsigned char)((size >> 16) & 0xFF);
	rng_cmd[10] = (unsigned char)((size >> 24) & 0xFF);
	offset = buf;
	while (bytes_read < size) {
		r=0;
		while (r < sizeof(rng_cmd)) {
			retval = write(ent_src->rng_fd,
				       rng_cmd + r,
				       sizeof(rng_cmd) - r);
			if (retval < 0) {
				message(LOG_ERR|LOG_INFO,
					"Error writing %s\n",
					ent_src->rng_name);
				retval = -1;
				goto error_out;
			}
			r += retval;
		}
		if (r < sizeof(rng_cmd)) {
			message(LOG_ERR|LOG_INFO,
				"Error writing %s\n", ent_src->rng_name);
			retval = -1;
			goto error_out;
		}
		r = read(ent_src->rng_fd, temp_buf,size);
		r = (r - TPM_GET_RNG_OVERHEAD);
		if(r <= 0) {
			message(LOG_ERR|LOG_INFO,
			"Error reading from TPM, no entropy gathered");
			retval = -1;
			goto error_out;
		}
		bytes_read = bytes_read + r;
		if (bytes_read > size) {
			memcpy(offset,temp_buf + TPM_GET_RNG_OVERHEAD,
				r - (bytes_read - size));
			break;
		}
		memcpy(offset, temp_buf + TPM_GET_RNG_OVERHEAD, r);
		offset = offset + r;
	}
	retval = 0;
error_out:
    close(ent_src->rng_fd);
	free(temp_buf);
	return retval;
}

/* Initialize entropy source */
static int discard_initial_data(struct rng *ent_src)
{
	/* Trash 32 bits of what is probably stale (non-random)
	 * initial state from the RNG.  For Intel's, 8 bits would
	 * be enough, but since AMD's generates 32 bits at a time...
	 *
	 * The kernel drivers should be doing this at device powerup,
	 * but at least up to 2.4.24, it doesn't. */
	unsigned char tempbuf[4];
	xread(tempbuf, sizeof(tempbuf), ent_src);

	/* Return 32 bits of bootstrap data */
	xread(tempbuf, sizeof(tempbuf), ent_src);

	return tempbuf[0] | (tempbuf[1] << 8) |
		(tempbuf[2] << 16) | (tempbuf[3] << 24);
}

/*
 * Open entropy source, and initialize it
 */
int init_entropy_source(struct rng *ent_src)
{
	ent_src->rng_fd = open(ent_src->rng_name, O_RDONLY);
	if (ent_src->rng_fd == -1) {
		return 1;
	}
	src_list_add(ent_src);
	/* Bootstrap FIPS tests */
	ent_src->fipsctx = malloc(sizeof(fips_ctx_t));
	fips_init(ent_src->fipsctx, discard_initial_data(ent_src));
	return 0;
}

/*
 * Open tpm entropy source, and initialize it
 */
int init_tpm_entropy_source(struct rng *ent_src)
{
	ent_src->rng_fd = open(ent_src->rng_name, O_RDWR);
	if (ent_src->rng_fd == -1) {
		message(LOG_ERR|LOG_INFO,"Unable to open file: %s",ent_src->rng_name);
		return 1;
	}
	src_list_add(ent_src);
	/* Bootstrap FIPS tests */
	ent_src->fipsctx = malloc(sizeof(fips_ctx_t));
	fips_init(ent_src->fipsctx, 0);
	close(ent_src->rng_fd);
	return 0;
}
