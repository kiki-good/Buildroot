/*
 * nfs4mount.c -- Linux NFS mount
 * Copyright (C) 2002 Trond Myklebust <trond.myklebust@fys.uio.no>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Note: this file based on the original nfsmount.c
 *
 * 2006-06-06 Amit Gud <agud@redhat.com>
 * - Moved to nfs-utils/utils/mount from util-linux/mount.
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <time.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <rpc/auth.h>
#include <rpc/rpc.h>
#ifdef HAVE_RPCSVC_NFS_PROT_H
#include <rpcsvc/nfs_prot.h>
#else
#include <linux/nfs.h>
#define nfsstat nfs_stat
#endif

#include "nls.h"
#include "conn.h"
#include "xcommon.h"

#include "nfs4_mount.h"
#include "nfs_mount.h"

#if defined(VAR_LOCK_DIR)
#define DEFAULT_DIR VAR_LOCK_DIR
#else
#define DEFAULT_DIR "/var/lock/subsys"
#endif

extern int verbose;

char *IDMAPLCK = DEFAULT_DIR "/rpcidmapd";
#define idmapd_check() do { \
	if (access(IDMAPLCK, F_OK)) { \
		printf(_("Warning: rpc.idmapd appears not to be running.\n" \
			"         All uids will be mapped to the nobody uid.\n")); \
	} \
} while(0);

char *GSSDLCK = DEFAULT_DIR "/rpcgssd";
#define gssd_check() do { \
		if (access(GSSDLCK, F_OK)) { \
			printf(_("Warning: rpc.gssd appears not to be running.\n")); \
		} \
} while(0); 

#ifndef NFS_PORT
#define NFS_PORT 2049
#endif

struct {
	char    *flavour;
	int     fnum;
} flav_map[] = {
	{ "krb5",	RPC_AUTH_GSS_KRB5	},
	{ "krb5i",	RPC_AUTH_GSS_KRB5I	},
	{ "krb5p",	RPC_AUTH_GSS_KRB5P	},
	{ "lipkey",	RPC_AUTH_GSS_LKEY	},
	{ "lipkey-i",	RPC_AUTH_GSS_LKEYI	},
	{ "lipkey-p",	RPC_AUTH_GSS_LKEYP	},
	{ "spkm3",	RPC_AUTH_GSS_SPKM	},
	{ "spkm3i",	RPC_AUTH_GSS_SPKMI	},
	{ "spkm3p",	RPC_AUTH_GSS_SPKMP	},
	{ "unix",	AUTH_UNIX		},
	{ "sys",	AUTH_SYS		},
	{ "null",	AUTH_NULL		},
	{ "none",	AUTH_NONE		},
};

#define FMAPSIZE		(sizeof(flav_map)/sizeof(flav_map[0]))
#define MAX_USER_FLAVOUR	16

static int parse_sec(char *sec, int *pseudoflavour)
{
	int i, num_flavour = 0;

	for (sec = strtok(sec, ":"); sec; sec = strtok(NULL, ":")) {
		if (num_flavour >= MAX_USER_FLAVOUR) {
			fprintf(stderr,
				_("mount: maximum number of security flavors "
				  "exceeded\n"));
			return 0;
		}
		for (i = 0; i < FMAPSIZE; i++) {
			if (strcmp(sec, flav_map[i].flavour) == 0) {
				pseudoflavour[num_flavour++] = flav_map[i].fnum;
				break;
			}
		}
		if (i == FMAPSIZE) {
			fprintf(stderr,
				_("mount: unknown security type %s\n"), sec);
			return 0;
		}
	}
	if (!num_flavour)
		fprintf(stderr,
			_("mount: no security flavors passed to sec= option\n"));
	return num_flavour;
}

static int parse_devname(char *hostdir, char **hostname, char **dirname)
{
	char *s;

	if (!(s = strchr(hostdir, ':'))) {
		fprintf(stderr,
			_("mount: "
			  "directory to mount not in host:dir format\n"));
		return -1;
	}
	*hostname = hostdir;
	*dirname = s + 1;
	*s = '\0';
	/* Ignore all but first hostname in replicated mounts
	   until they can be fully supported. (mack@sgi.com) */
	if ((s = strchr(hostdir, ','))) {
		*s = '\0';
		fprintf(stderr,
			_("mount: warning: "
			  "multiple hostnames not supported\n"));
	}
	return 0;
}

static int fill_ipv4_sockaddr(const char *hostname, struct sockaddr_in *addr)
{
	struct hostent *hp;
	addr->sin_family = AF_INET;

	if (inet_aton(hostname, &addr->sin_addr))
		return 0;
	if ((hp = gethostbyname(hostname)) == NULL) {
		fprintf(stderr, _("mount: can't get address for %s\n"),
			hostname);
		return -1;
	}
	if (hp->h_length > sizeof(struct in_addr)) {
		fprintf(stderr,
			_("mount: got bad hp->h_length\n"));
		hp->h_length = sizeof(struct in_addr);
	}
	memcpy(&addr->sin_addr, hp->h_addr, hp->h_length);
	return 0;
}

static int get_my_ipv4addr(char *ip_addr, int len)
{
	char myname[1024];
	struct sockaddr_in myaddr;

	if (gethostname(myname, sizeof(myname))) {
		fprintf(stderr, _("mount: can't determine client address\n"));
		return -1;
	}
	if (fill_ipv4_sockaddr(myname, &myaddr))
		return -1;
	snprintf(ip_addr, len, "%s", inet_ntoa(myaddr.sin_addr));
	ip_addr[len-1] = '\0';
	return 0;
}

int nfs4mount(const char *spec, const char *node, int *flags,
	      char **extra_opts, char **mount_opts,
	      int running_bg)
{
	static struct nfs4_mount_data data;
	static char hostdir[1024];
	static char ip_addr[16] = "127.0.0.1";
	static struct sockaddr_in server_addr, client_addr;
	static int pseudoflavour[MAX_USER_FLAVOUR];
	int num_flavour = 0;
	int ip_addr_in_opts = 0;

	char *hostname, *dirname, *old_opts;
	char new_opts[1024];
	char *opt, *opteq;
	char *s;
	int val;
	int bg, soft, intr;
	int nocto, noac;
	int retry;
	int retval;
	time_t timeout, t;

	retval = EX_FAIL;
	if (strlen(spec) >= sizeof(hostdir)) {
		fprintf(stderr, _("mount: "
				  "excessively long host:dir argument\n"));
		goto fail;
	}
	strcpy(hostdir, spec);
	if (parse_devname(hostdir, &hostname, &dirname))
		goto fail;

	if (fill_ipv4_sockaddr(hostname, &server_addr))
		goto fail;
	if (get_my_ipv4addr(ip_addr, sizeof(ip_addr)))
		goto fail;

	/* add IP address to mtab options for use when unmounting */
	s = inet_ntoa(server_addr.sin_addr);
	old_opts = *extra_opts;
	if (!old_opts)
		old_opts = "";
	if (strlen(old_opts) + strlen(s) + 10 >= sizeof(new_opts)) {
		fprintf(stderr, _("mount: "
				  "excessively long option argument\n"));
		goto fail;
	}
	snprintf(new_opts, sizeof(new_opts), "%s%saddr=%s",
		 old_opts, *old_opts ? "," : "", s);
	*extra_opts = xstrdup(new_opts);

	/* Set default options.
	 * rsize/wsize and timeo are left 0 in order to
	 * let the kernel decide.
	 */
	memset(&data, 0, sizeof(data));
	data.retrans	= 3;
	data.acregmin	= 3;
	data.acregmax	= 60;
	data.acdirmin	= 30;
	data.acdirmax	= 60;
	data.proto	= IPPROTO_TCP;

	bg = 0;
	soft = 0;
	intr = NFS4_MOUNT_INTR;
	nocto = 0;
	noac = 0;
	retry = 10000;		/* 10000 minutes ~ 1 week */

	/*
	 * NFSv4 specifies that the default port should be 2049
	 */
	server_addr.sin_port = htons(NFS_PORT);

	/* parse options */

	for (opt = strtok(old_opts, ","); opt; opt = strtok(NULL, ",")) {
		if ((opteq = strchr(opt, '='))) {
			val = atoi(opteq + 1);	
			*opteq = '\0';
			if (!strcmp(opt, "rsize"))
				data.rsize = val;
			else if (!strcmp(opt, "wsize"))
				data.wsize = val;
			else if (!strcmp(opt, "timeo"))
				data.timeo = val;
			else if (!strcmp(opt, "retrans"))
				data.retrans = val;
			else if (!strcmp(opt, "acregmin"))
				data.acregmin = val;
			else if (!strcmp(opt, "acregmax"))
				data.acregmax = val;
			else if (!strcmp(opt, "acdirmin"))
				data.acdirmin = val;
			else if (!strcmp(opt, "acdirmax"))
				data.acdirmax = val;
			else if (!strcmp(opt, "actimeo")) {
				data.acregmin = val;
				data.acregmax = val;
				data.acdirmin = val;
				data.acdirmax = val;
			}
			else if (!strcmp(opt, "retry"))
				retry = val;
			else if (!strcmp(opt, "port"))
				server_addr.sin_port = htons(val);
			else if (!strcmp(opt, "proto")) {
				if (!strncmp(opteq+1, "tcp", 3))
					data.proto = IPPROTO_TCP;
				else if (!strncmp(opteq+1, "udp", 3))
					data.proto = IPPROTO_UDP;
				else
					printf(_("Warning: Unrecognized proto= option.\n"));
			} else if (!strcmp(opt, "clientaddr")) {
				if (strlen(opteq+1) >= sizeof(ip_addr))
					printf(_("Invalid client address %s"),
								opteq+1);
				strncpy(ip_addr,opteq+1, sizeof(ip_addr));
				ip_addr[sizeof(ip_addr)-1] = '\0';
				ip_addr_in_opts = 1;
			} else if (!strcmp(opt, "sec")) {
				num_flavour = parse_sec(opteq+1, pseudoflavour);
				if (!num_flavour)
					goto fail;
			} else if (!strcmp(opt, "addr")) {
				/* ignore */;
			} else {
				printf(_("unknown nfs mount parameter: "
					 "%s=%d\n"), opt, val);
				goto fail;
			}
		} else {
			val = 1;
			if (!strncmp(opt, "no", 2)) {
				val = 0;
				opt += 2;
			}
			if (!strcmp(opt, "bg")) 
				bg = val;
			else if (!strcmp(opt, "fg")) 
				bg = !val;
			else if (!strcmp(opt, "soft"))
				soft = val;
			else if (!strcmp(opt, "hard"))
				soft = !val;
			else if (!strcmp(opt, "intr"))
				intr = val;
			else if (!strcmp(opt, "cto"))
				nocto = !val;
			else if (!strcmp(opt, "ac"))
				noac = !val;
			else {
				printf(_("unknown nfs mount option: "
					 "%s%s\n"), val ? "" : "no", opt);
				goto fail;
			}
		}
	}

	data.flags = (soft ? NFS4_MOUNT_SOFT : 0)
		| (intr ? NFS4_MOUNT_INTR : 0)
		| (nocto ? NFS4_MOUNT_NOCTO : 0)
		| (noac ? NFS4_MOUNT_NOAC : 0);

	/*
	 * Give a warning if the rpc.idmapd daemon is not running
	 */
	idmapd_check();

	if (num_flavour == 0)
		pseudoflavour[num_flavour++] = AUTH_UNIX;
	else {
		/*
		 * ditto with rpc.gssd daemon
		 */
		gssd_check();
	}
	data.auth_flavourlen = num_flavour;
	data.auth_flavours = pseudoflavour;

	data.client_addr.data = ip_addr;
	data.client_addr.len = strlen(ip_addr);

	data.mnt_path.data = dirname;
	data.mnt_path.len = strlen(dirname);

	data.hostname.data = hostname;
	data.hostname.len = strlen(hostname);
	data.host_addr = (struct sockaddr *)&server_addr;
	data.host_addrlen = sizeof(server_addr);

#ifdef NFS_MOUNT_DEBUG
	printf("rsize = %d, wsize = %d, timeo = %d, retrans = %d\n",
	       data.rsize, data.wsize, data.timeo, data.retrans);
	printf("acreg (min, max) = (%d, %d), acdir (min, max) = (%d, %d)\n",
	       data.acregmin, data.acregmax, data.acdirmin, data.acdirmax);
	printf("port = %d, bg = %d, retry = %d, flags = %.8x\n",
	       ntohs(server_addr.sin_port), bg, retry, data.flags);
	printf("soft = %d, intr = %d, nocto = %d, noac = %d\n",
	       (data.flags & NFS4_MOUNT_SOFT) != 0,
	       (data.flags & NFS4_MOUNT_INTR) != 0,
	       (data.flags & NFS4_MOUNT_NOCTO) != 0,
	       (data.flags & NFS4_MOUNT_NOAC) != 0);

	if (num_flavour > 0) {
		int pf_cnt, i;

		printf("sec = ");
		for (pf_cnt = 0; pf_cnt < num_flavour; pf_cnt++) {
			for (i = 0; i < FMAPSIZE; i++) {
				if (flav_map[i].fnum == pseudoflavour[pf_cnt]) {
					printf("%s", flav_map[i].flavour);
					break;
				}
			}
			printf("%s", (pf_cnt < num_flavour-1) ? ":" : "\n");
		}
	}
	printf("proto = %s\n", (data.proto == IPPROTO_TCP) ? "tcp" : "udp");
#endif

	timeout = time(NULL) + 60 * retry;
	data.version = NFS4_MOUNT_VERSION;
	for (;;) {
		if (verbose) {
			fprintf(stderr, 
				"mount: pinging: prog %d vers %d prot %s port %d\n", 
				NFS_PROGRAM, 4, data.proto == IPPROTO_UDP ? "udp" : "tcp", 
				ntohs(server_addr.sin_port));
		}
		client_addr.sin_family = 0;
		client_addr.sin_addr.s_addr = 0;
		clnt_ping(&server_addr, NFS_PROGRAM, 4, data.proto, &client_addr);
		if (rpc_createerr.cf_stat == RPC_SUCCESS) {
			if (!ip_addr_in_opts &&
			    client_addr.sin_family != 0 &&
			    client_addr.sin_addr.s_addr != 0) {
				snprintf(ip_addr, sizeof(ip_addr), "%s",
					 inet_ntoa(client_addr.sin_addr));
				data.client_addr.len = strlen(ip_addr);
			}
			break;
		}

		switch(rpc_createerr.cf_stat){
		case RPC_TIMEDOUT:
			break;
		case RPC_SYSTEMERROR:
			if (errno == ETIMEDOUT)
				break;
		default:
			mount_errors(hostname, 0, bg);
			goto fail;
		}
		t = time(NULL);
		if (t >= timeout) {
			mount_errors(hostname, 0, bg);
			goto fail;
		}
		mount_errors(hostname, 1, bg);
		continue;
	}

	*mount_opts = (char *) &data;
	/* clean up */
	return 0;

fail:
	return retval;
}
