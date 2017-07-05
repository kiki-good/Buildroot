/*
 *
 *  BlueZ - Bluetooth protocol stack for Linux
 *
 *  Copyright (C) 2011-2012  Intel Corporation
 *  Copyright (C) 2004-2010  Marcel Holtmann <marcel@holtmann.org>
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <arpa/inet.h>
#include <sys/stat.h>

#define MONITOR_NEW_INDEX	0
#define MONITOR_DEL_INDEX	1
#define MONITOR_COMMAND_PKT	2
#define MONITOR_EVENT_PKT	3
#define MONITOR_ACL_TX_PKT	4
#define MONITOR_ACL_RX_PKT	5
#define MONITOR_SCO_TX_PKT	6
#define MONITOR_SCO_RX_PKT	7

static inline uint64_t ntoh64(uint64_t n)
{
	uint64_t h;
	uint64_t tmp = ntohl(n & 0x00000000ffffffff);

	h = ntohl(n >> 32);
	h |= tmp << 32;

	return h;
}

#define hton64(x)     ntoh64(x)

struct btsnoop_hdr {
	uint8_t		id[8];		/* Identification Pattern */
	uint32_t	version;	/* Version Number = 1 */
	uint32_t	type;		/* Datalink Type */
} __attribute__ ((packed));
#define BTSNOOP_HDR_SIZE (sizeof(struct btsnoop_hdr))

struct btsnoop_pkt {
	uint32_t	size;		/* Original Length */
	uint32_t	len;		/* Included Length */
	uint32_t	flags;		/* Packet Flags */
	uint32_t	drops;		/* Cumulative Drops */
	uint64_t	ts;		/* Timestamp microseconds */
	uint8_t		data[0];	/* Packet Data */
} __attribute__ ((packed));
#define BTSNOOP_PKT_SIZE (sizeof(struct btsnoop_pkt))

static const uint8_t btsnoop_id[] = { 0x62, 0x74, 0x73, 0x6e,
				      0x6f, 0x6f, 0x70, 0x00 };

static const uint32_t btsnoop_version = 1;

static int btsnoop_create(const char *path)
{
	struct btsnoop_hdr hdr;
	ssize_t written;
	int fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0) {
		perror("failed to output file");
		return -1;
	}

	memcpy(hdr.id, btsnoop_id, sizeof(btsnoop_id));
	hdr.version = htonl(btsnoop_version);
	hdr.type = htonl(2001);

	written = write(fd, &hdr, BTSNOOP_HDR_SIZE);
	if (written < 0) {
		perror("failed to write output header");
		close(fd);
		return -1;
	}

	return fd;
}

static int btsnoop_open(const char *path, uint32_t *type)
{
	struct btsnoop_hdr hdr;
	ssize_t len;
	int fd;

	fd = open(path, O_RDONLY | O_CLOEXEC);
	if (fd < 0) {
		perror("failed to open input file");
		return -1;
	}

	len = read(fd, &hdr, BTSNOOP_HDR_SIZE);
	if (len < 0 || len != BTSNOOP_HDR_SIZE) {
		perror("failed to read input header");
		close(fd);
		return -1;
	}

	if (memcmp(hdr.id, btsnoop_id, sizeof(btsnoop_id))) {
		fprintf(stderr, "not a valid btsnoop header\n");
		close(fd);
		return -1;
	}

	if (ntohl(hdr.version) != btsnoop_version) {
		fprintf(stderr, "invalid btsnoop version\n");
		close(fd);
		return -1;
	}

	if (type)
		*type = ntohl(hdr.type);

	return fd;
}

#define MAX_MERGE 8

static void command_merge(const char *output, int argc, char *argv[])
{
	struct btsnoop_pkt input_pkt[MAX_MERGE];
	unsigned char buf[2048];
	int output_fd, input_fd[MAX_MERGE], num_input = 0;
	int i, select_input;
	ssize_t len, written;
	uint32_t toread, flags;
	uint16_t index, opcode;

	if (argc > MAX_MERGE) {
		fprintf(stderr, "only up to %d files allowed\n", MAX_MERGE);
		return;
	}

	for (i = 0; i < argc; i++) {
		uint32_t type;
		int fd;

		fd = btsnoop_open(argv[i], &type);
		if (fd < 0)
			break;

		if (type != 1002) {
			fprintf(stderr, "unsupported link data type %u\n",
									type);
			close(fd);
			break;
		}

		input_fd[num_input++] = fd;
	}

	if (num_input != argc) {
		fprintf(stderr, "failed to open all input files\n");
		goto close_input;
	}

	output_fd = btsnoop_create(output);
	if (output_fd < 0)
		goto close_input;

	for (i = 0; i < num_input; i++) {
		len = read(input_fd[i], &input_pkt[i], BTSNOOP_PKT_SIZE);
		if (len < 0 || len != BTSNOOP_PKT_SIZE) {
			close(input_fd[i]);
			input_fd[i] = -1;
		}
	}

next_packet:
	select_input = -1;

	for (i = 0; i < num_input; i++) {
		uint64_t ts;

		if (input_fd[i] < 0)
			continue;

		if (select_input < 0) {
			select_input = i;
			continue;
		}

		ts = ntoh64(input_pkt[i].ts);

		if (ts < ntoh64(input_pkt[select_input].ts))
			select_input = i;
	}

	if (select_input < 0)
		goto close_output;

	toread = ntohl(input_pkt[select_input].size);
	flags = ntohl(input_pkt[select_input].flags);

	len = read(input_fd[select_input], buf, toread);
	if (len < 0 || len != (ssize_t) toread) {
		close(input_fd[select_input]);
		input_fd[select_input] = -1;
		goto next_packet;
	}

	written = input_pkt[select_input].size = htonl(toread - 1);
	written = input_pkt[select_input].len = htonl(toread - 1);

	switch (buf[0]) {
	case 0x01:
		opcode = MONITOR_COMMAND_PKT;
		break;
	case 0x02:
		if (flags & 0x01)
			opcode = MONITOR_ACL_RX_PKT;
		else
			opcode = MONITOR_ACL_TX_PKT;
		break;
	case 0x03:
		if (flags & 0x01)
			opcode = MONITOR_SCO_RX_PKT;
		else
			opcode = MONITOR_ACL_TX_PKT;
		break;
	case 0x04:
		opcode = MONITOR_EVENT_PKT;
		break;
	default:
		goto skip_write;
	}

	index = select_input;
	input_pkt[select_input].flags = htonl((index << 16) | opcode);

	written = write(output_fd, &input_pkt[select_input], BTSNOOP_PKT_SIZE);
	if (written != BTSNOOP_PKT_SIZE) {
		fprintf(stderr, "write of packet header failed\n");
		goto close_output;
	}

	written = write(output_fd, buf + 1, toread - 1);
	if (written != (ssize_t) toread - 1) {
		fprintf(stderr, "write of packet data failed\n");
		goto close_output;
	}

skip_write:
	len = read(input_fd[select_input],
				&input_pkt[select_input], BTSNOOP_PKT_SIZE);
	if (len < 0 || len != BTSNOOP_PKT_SIZE) {
		close(input_fd[select_input]);
		input_fd[select_input] = -1;
	}

	goto next_packet;

close_output:
	close(output_fd);

close_input:
	for (i = 0; i < num_input; i++)
		close(input_fd[i]);
}

static void command_extract_eir(const char *input)
{
	struct btsnoop_pkt pkt;
	unsigned char buf[2048];
	ssize_t len;
	uint32_t type, toread, flags;
	uint16_t opcode;
	int fd, count = 0;

	fd = btsnoop_open(input, &type);
	if (fd < 0)
		return;

	if (type != 2001) {
		fprintf(stderr, "unsupported link data type %u\n", type);
		close(fd);
		return;
	}

next_packet:
	len = read(fd, &pkt, BTSNOOP_PKT_SIZE);
	if (len < 0 || len != BTSNOOP_PKT_SIZE)
		goto close_input;

	toread = ntohl(pkt.size);
	flags = ntohl(pkt.flags);

	opcode = flags & 0x00ff;

	len = read(fd, buf, toread);
	if (len < 0 || len != (ssize_t) toread) {
		fprintf(stderr, "failed to read packet data\n");
		goto close_input;
	}

	switch (opcode) {
	case MONITOR_EVENT_PKT:
		/* extended inquiry result event */
		if (buf[0] == 0x2f) {
			uint8_t *eir_ptr, eir_len, i;

			eir_len = buf[1] - 15;
			eir_ptr = buf + 17;

			if (eir_len < 1 || eir_len > 240)
				break;

			printf("\t[Extended Inquiry Data with %u bytes]\n",
								eir_len);
			printf("\t\t");
			for (i = 0; i < eir_len; i++) {
				printf("0x%02x", eir_ptr[i]);
				if (((i + 1) % 8) == 0) {
					if (i < eir_len - 1)
						printf(",\n\t\t");
				} else {
					if (i < eir_len - 1)
						printf(", ");
				}
			}
			printf("\n");

			count++;
		}
		break;
	}

	goto next_packet;

close_input:
	close(fd);
}

static void command_extract_ad(const char *input)
{
	struct btsnoop_pkt pkt;
	unsigned char buf[2048];
	ssize_t len;
	uint32_t type, toread, flags;
	uint16_t opcode;
	int fd, count = 0;

	fd = btsnoop_open(input, &type);
	if (fd < 0)
		return;

	if (type != 2001) {
		fprintf(stderr, "unsupported link data type %u\n", type);
		close(fd);
		return;
	}

next_packet:
	len = read(fd, &pkt, BTSNOOP_PKT_SIZE);
	if (len < 0 || len != BTSNOOP_PKT_SIZE)
		goto close_input;

	toread = ntohl(pkt.size);
	flags = ntohl(pkt.flags);

	opcode = flags & 0x00ff;

	len = read(fd, buf, toread);
	if (len < 0 || len != (ssize_t) toread) {
		fprintf(stderr, "failed to read packet data\n");
		goto close_input;
	}

	switch (opcode) {
	case MONITOR_EVENT_PKT:
		/* advertising report */
		if (buf[0] == 0x3e && buf[2] == 0x02) {
			uint8_t *ad_ptr, ad_len, i;

			ad_len = buf[12];
			ad_ptr = buf + 13;

			if (ad_len < 1 || ad_len > 40)
				break;

			printf("\t[Advertising Data with %u bytes]\n", ad_len);
			printf("\t\t");
			for (i = 0; i < ad_len; i++) {
				printf("0x%02x", ad_ptr[i]);
				if (((i + 1) % 8) == 0) {
					if (i < ad_len - 1)
						printf(",\n\t\t");
				} else {
					if (i < ad_len - 1)
						printf(", ");
				}
			}
			printf("\n");

			count++;
		}
		break;
	}

	goto next_packet;

close_input:
	close(fd);
}
static const uint8_t conn_complete[] = { 0x04, 0x03, 0x0B, 0x00 };
static const uint8_t disc_complete[] = { 0x04, 0x05, 0x04, 0x00 };

static void command_extract_sdp(const char *input)
{
	struct btsnoop_pkt pkt;
	unsigned char buf[2048];
	ssize_t len;
	uint32_t type, toread;
	uint16_t current_cid = 0x0000;
	uint8_t pdu_buf[512];
	uint16_t pdu_len = 0;
	bool pdu_first = false;
	int fd, count = 0;

	fd = btsnoop_open(input, &type);
	if (fd < 0)
		return;

	if (type != 1002) {
		fprintf(stderr, "unsupported link data type %u\n", type);
		close(fd);
		return;
	}

next_packet:
	len = read(fd, &pkt, BTSNOOP_PKT_SIZE);
	if (len < 0 || len != BTSNOOP_PKT_SIZE)
		goto close_input;

	toread = ntohl(pkt.size);

	len = read(fd, buf, toread);
	if (len < 0 || len != (ssize_t) toread) {
		fprintf(stderr, "failed to read packet data\n");
		goto close_input;
	}

	if (buf[0] == 0x02) {
		uint8_t acl_flags;

		/* first 4 bytes are handle and data len */
		acl_flags = buf[2] >> 4;

		/* use only packet with ACL start flag */
		if (acl_flags & 0x02) {
			if (current_cid == 0x0040 && pdu_len > 0) {
				int i;
				if (!pdu_first)
					printf(",\n");
				printf("\t\traw_pdu(");
				for (i = 0; i < pdu_len; i++) {
					printf("0x%02x", pdu_buf[i]);
					if (((i + 1) % 8) == 0) {
						if (i < pdu_len - 1)
							printf(",\n\t\t\t");
					} else {
						if (i < pdu_len - 1)
							printf(", ");
					}
				}
				printf(")");
				pdu_first = false;
			}

			/* next 4 bytes are data len and cid */
			current_cid = buf[8] << 8 | buf[7];
			memcpy(pdu_buf, buf + 9, len - 9);
			pdu_len = len - 9;
		} else if (acl_flags & 0x01) {
			memcpy(pdu_buf + pdu_len, buf + 5, len - 5);
			pdu_len += len - 5;
		}
	}

	if ((size_t) len > sizeof(conn_complete)) {
		if (memcmp(buf, conn_complete, sizeof(conn_complete)) == 0) {
			printf("\tdefine_test(\"/test/%u\",\n", ++count);
			pdu_first = true;
		}
	}

	if ((size_t) len > sizeof(disc_complete)) {
		if (memcmp(buf, disc_complete, sizeof(disc_complete)) == 0) {
			printf(");\n");
		}
	}

	goto next_packet;

close_input:
	close(fd);
}

static void usage(void)
{
	printf("btsnoop trace file handling tool\n"
		"Usage:\n");
	printf("\tbtsnoop <command> [files]\n");
	printf("commands:\n"
		"\t-m, --merge <output>   Merge multiple btsnoop files\n"
		"\t-e, --extract <input>  Extract data from btsnoop file\n"
		"\t-h, --help             Show help options\n");
}

static const struct option main_options[] = {
	{ "merge",   required_argument, NULL, 'm' },
	{ "extract", required_argument, NULL, 'e' },
	{ "type",    required_argument, NULL, 't' },
	{ "version", no_argument,       NULL, 'v' },
	{ "help",    no_argument,       NULL, 'h' },
	{ }
};

enum { INVALID, MERGE, EXTRACT };

int main(int argc, char *argv[])
{
	const char *output_path = NULL;
	const char *input_path = NULL;
	const char *type = NULL;
	unsigned short command = INVALID;

	for (;;) {
		int opt;

		opt = getopt_long(argc, argv, "m:e:t:vh", main_options, NULL);
		if (opt < 0)
			break;

		switch (opt) {
		case 'm':
			command = MERGE;
			output_path = optarg;
			break;
		case 'e':
			command = EXTRACT;
			input_path = optarg;
			break;
		case 't':
			type = optarg;
			break;
		case 'v':
			printf("%s\n", VERSION);
			return EXIT_SUCCESS;
		case 'h':
			usage();
			return EXIT_SUCCESS;
		default:
			return EXIT_FAILURE;
		}
	}

	switch (command) {
	case MERGE:
		if (argc - optind < 1) {
			fprintf(stderr, "input files required\n");
			return EXIT_FAILURE;
		}

		command_merge(output_path, argc - optind, argv + optind);
		break;

	case EXTRACT:
		if (argc - optind > 0) {
			fprintf(stderr, "extra arguments not allowed\n");
			return EXIT_FAILURE;
		}

		if (!type) {
			fprintf(stderr, "not extract type specified\n");
			return EXIT_FAILURE;
		}

		if (!strcasecmp(type, "eir"))
			command_extract_eir(input_path);
		else if (!strcasecmp(type, "ad"))
			command_extract_ad(input_path);
		else if (!strcasecmp(type, "sdp"))
			command_extract_sdp(input_path);
		else
			fprintf(stderr, "extract type not supported\n");
		break;

	default:
		usage();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
