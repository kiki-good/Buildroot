/*-
 * Copyright (c) 1983, 1988, 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

char copyright[] =
  "@(#) Copyright (c) 1983, 1988, 1989 "
  "The Regents of the University of California.\n"
  "All rights reserved.\n";

/* 
 * From: @(#)rlogind.c	5.53 (Berkeley) 4/20/91
 */
char rcsid[] = 
  "$Id: rlogind.c,v 1.37 2000/07/23 03:07:58 dholland Exp $";
#include "../version.h"

/*
 * remote login server:
 *	\0
 *	remuser\0
 *	locuser\0
 *	terminal_type/speed\0
 *	data
 */

#include <sys/types.h>   /* for size_t */
#include <sys/param.h>   /* for MAXPATHLEN */
#include <sys/stat.h>    /* for chmod() */
#include <sys/ioctl.h>   /* for TIOCPKT */
#include <sys/time.h>    /* for FD_SET() et al. */
#include <signal.h>      /* for SIGCHLD */
#include <termios.h>     /* for tcsetattr() */
#include <sys/socket.h>  /* for shutdown() */
#include <arpa/inet.h>   /* for ntohs() */
#include <stdio.h>       /* for EOF, BUFSIZ, snprintf() */
#include <syslog.h>      /* for syslog() */
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "pathnames.h"
#include "logwtmp.h"
#include "rlogind.h"

pid_t forkpty(int *, char *, struct termios *, struct winsize *);
int logout(const char *);

#ifndef TIOCPKT_WINDOW
#define TIOCPKT_WINDOW 0x80
#endif

int keepalive = 1;
int check_all = 0;
int use_rhosts = 1;
int allow_root_rhosts = 0;
int deny_all_rhosts_hequiv = 0;

static char oobdata[] = {(char)TIOCPKT_WINDOW};
static char line[MAXPATHLEN];
struct winsize win = { 0, 0, 0, 0 };


void fatal(int f, const char *msg, int syserr) {
    char buf[BUFSIZ];

    /*
     * Send out a binary one if we haven't sent the magic null as confirmation.
     */
    network_anticonfirm();

    if (!syserr) {
	snprintf(buf, sizeof(buf), "rlogind: %s.\r\n", msg);
    }
    else {
	snprintf(buf, sizeof(buf), "rlogind: %s: %s.\r\n", 
		 msg, strerror(errno));
    }
    write(f, buf, strlen(buf));
    auth_finish();
    exit(1);
}


////////////////////////////////////////////////// parent ////////////////////

/*
 * Handle a "control" request (signaled by magic being present)
 * in the data stream.  For now, we are only willing to handle
 * window size changes.
 */
static int control(int pty, char *cp, int n) {
	struct winsize w;

	if (n < 4+(int)sizeof(w) || cp[2] != 's' || cp[3] != 's') {
		return 0;
	}
	oobdata[0] &= ~TIOCPKT_WINDOW;	/* we know he heard */
	memcpy(&w, cp+4, sizeof(w));
	w.ws_row = ntohs(w.ws_row);
	w.ws_col = ntohs(w.ws_col);
	w.ws_xpixel = ntohs(w.ws_xpixel);
	w.ws_ypixel = ntohs(w.ws_ypixel);
	ioctl(pty, TIOCSWINSZ, &w);
	return 4+sizeof(w);
}

/*
 * rlogin "protocol" machine.
 */
static void protocol(int f, int p) {
	static char magic[2] = { (char)0377, (char)0377 };

	char pibuf[1024+1], fibuf[1024], *pbp = NULL, *fbp = NULL;
	int pcc = 0, fcc = 0;
	int cc, nfd, m;
	char cntl;

	/*
	 * Must ignore SIGTTOU, otherwise we'll stop
	 * when we try and set slave pty's window shape
	 * (our controlling tty is the master pty).
	 */
	(void) signal(SIGTTOU, SIG_IGN);
	send(f, oobdata, 1, MSG_OOB);	/* indicate new rlogin */
	if (f > p)
		nfd = f + 1;
	else
		nfd = p + 1;
	if (nfd > FD_SETSIZE) {
		syslog(LOG_ERR, "select mask too small, increase FD_SETSIZE");
		fatal(f, "internal error (select mask too small)", 0);
	}
	for (;;) {
		fd_set ibits, obits, ebits, *omask;

		FD_ZERO(&ebits);
		FD_ZERO(&ibits);
		FD_ZERO(&obits);
		omask = (fd_set *)NULL;
		if (fcc) {
			FD_SET(p, &obits);
			omask = &obits;
		} else
			FD_SET(f, &ibits);
		if (pcc >= 0) {
			if (pcc) {
				FD_SET(f, &obits);
				omask = &obits;
			} else {
				FD_SET(p, &ibits);
			}
		}
		FD_SET(p, &ebits);
		if ((m = select(nfd, &ibits, omask, &ebits, 0)) < 0) {
			if (errno == EINTR)
				continue;
			fatal(f, "select", 1);
		}
		if (m == 0) {
			/* shouldn't happen... */
			sleep(5);
			continue;
		}
#define	pkcontrol(c)	((c)&(TIOCPKT_FLUSHWRITE|TIOCPKT_NOSTOP|TIOCPKT_DOSTOP))
		if (FD_ISSET(p, &ebits)) {
			cc = read(p, &cntl, 1);
			if (cc == 1 && pkcontrol(cntl)) {
				cntl |= oobdata[0];
				send(f, &cntl, 1, MSG_OOB);
				if (cntl & TIOCPKT_FLUSHWRITE) {
					pcc = 0;
					FD_CLR(p, &ibits);
				}
			}
		}
		if (FD_ISSET(f, &ibits)) {
				fcc = read(f, fibuf, sizeof(fibuf));
			if (fcc < 0 && errno == EWOULDBLOCK)
				fcc = 0;
			else {
				register char *cp;
				int left, nn;

				if (fcc <= 0)
					break;
				fbp = fibuf;

			top:
				for (cp = fibuf; cp < fibuf+fcc-1; cp++)
					if (cp[0] == magic[0] &&
					    cp[1] == magic[1]) {
						left = fcc - (cp-fibuf);
						nn = control(p, cp, left);
						if (nn) {
							left -= nn;
							if (left > 0)
								bcopy(cp+nn, cp, left);
							fcc -= nn;
							goto top; /* n^2 */
						}
					}
				FD_SET(p, &obits);		/* try write */
			}
		}

		if (FD_ISSET(p, &obits) && fcc > 0) {
			cc = write(p, fbp, fcc);
			if (cc > 0) {
				fcc -= cc;
				fbp += cc;
			}
		}

		if (FD_ISSET(p, &ibits)) {
			pcc = read(p, pibuf, sizeof (pibuf));
			pbp = pibuf;
			if (pcc < 0 && errno == EWOULDBLOCK)
				pcc = 0;
			else if (pcc <= 0)
				break;
			else if (pibuf[0] == 0) {
				pbp++, pcc--;
					FD_SET(f, &obits);	/* try write */
			} else {
				if (pkcontrol(pibuf[0])) {
					pibuf[0] |= oobdata[0];
					send(f, &pibuf[0], 1, MSG_OOB);
				}
				pcc = 0;
			}
		}
		if ((FD_ISSET(f, &obits)) && pcc > 0) {
				cc = write(f, pbp, pcc);
			if (cc < 0 && errno == EWOULDBLOCK) {
				/*
				 * This happens when we try write after read
				 * from p, but some old kernels balk at large
				 * writes even when select returns true.
				 */
				if (!FD_ISSET(p, &ibits))
					sleep(5);
				continue;
			}
			if (cc > 0) {
				pcc -= cc;
				pbp += cc;
			}
		}
	}
}

static void cleanup(int sig) {
    char *p;
    (void)sig;

    p = line + sizeof(_PATH_DEV) - 1;
    if (logout(p)) logwtmp(p, "", "");

    auth_finish();
    network_close();

    /* tty end to root.system mode 600 */
    chmod(line, 0600);
    chown(line, 0, 0);

    /* pty end to root.system mode 666 */
    *p = 'p';
    chmod(line, 0666);
    chown(line, 0, 0);

    /* all done */
    exit(0);
}


////////////////////////////////////////////////// child ////////////////////

static void setup_term(int fd, const char *termtype) {
    char *x;
    struct termios tt;

    tcgetattr(fd, &tt);
    if ((x=strchr(termtype, '/')) != NULL) {
	*x++ = '\0';
	cfsetispeed(&tt, atoi(x));
	cfsetospeed(&tt, atoi(x));
    }
#if 0  /* notyet */
    tt.c_iflag = TTYDEF_IFLAG;
    tt.c_oflag = TTYDEF_OFLAG;
    tt.c_lflag = TTYDEF_LFLAG;
#endif
    tcsetattr(fd, TCSAFLUSH, &tt);
}

/*
 * Close all fds, in case libc has left fun stuff like /etc/shadow open.
 */
static void closeall(void) {
    int i;
    for (i = getdtablesize()-1; i > 2; i--) close(i);
}


static void child(const char *hname, const char *termtype,
		  const char *localuser, int authenticated)
{
    char *termenv[2];

    setup_term(0, termtype);

    termenv[0] = malloc(strlen(termtype)+6);
    if (termenv[0]) {   /* shouldn't ever fail, mind you */
	strcpy(termenv[0], "TERM=");
	strcat(termenv[0], termtype);
    }
    termenv[1] = NULL;

    if (authenticated) {
	auth_finish();
	closeall();
	execle(_PATH_LOGIN, "login", "-p",
	       "-h", hname, "-f", localuser, NULL, termenv);
    } 
    else {
	if (localuser[0] == '-') {
	    syslog(LOG_AUTH|LOG_INFO, "rlogin with an option as a name!");
	    exit(1);
	}
	auth_finish();
	closeall();
	execle(_PATH_LOGIN, "login", "-p",
	       "-h", hname, localuser, NULL, termenv);
    }
    /* Can't exec login, croak */
    fatal(STDERR_FILENO, _PATH_LOGIN, 1);
}


////////////////////////////////////////////////// main ////////////////////


static void getstr(char *buf, int cnt, const char *errmsg) {
    char c;
    do {
	if (read(STDIN_FILENO, &c, 1) != 1) exit(1);
	if (--cnt < 0) fatal(STDOUT_FILENO, errmsg, 0);
	*buf++ = c;
    } while (c != 0);
}

static void doit(int netfd) {
    int master, pid, on = 1;
    int authenticated = 0;
    char *hname;
    int hostok;
    char lusername[32], rusername[32], termtype[256];

    hname = network_init(netfd, &hostok);

    getstr(rusername, sizeof(rusername), "remuser too long");
    getstr(lusername, sizeof(lusername), "locuser too long");
    getstr(termtype, sizeof(termtype), "Terminal type too long");
    
    /*
     * This function will either die, return -1 if authentication failed,
     * or return 0 if authentication succeeded.
     * 
     * dholland 6/13/97 I've changed this so it doesn't even call 
     * auth_checkauth if the hostname was bogus. I don't *think* 
     * this will break anything or give away state secrets.
     */
    if (hostok) {
	if (auth_checkauth(rusername, hname, 
			   lusername, sizeof(lusername)) == 0) {
	   authenticated=1;
	}
    }
    network_confirm();

    if (!hostok) {
	write(netfd, "rlogind: Host address mismatch.\r\n", 33);
    }

    pid = forkpty(&master, line, NULL, &win);
    if (pid < 0) {
	if (errno == ENOENT) fatal(netfd, "Out of ptys", 0);
	fatal(netfd, "Forkpty", 1);
    }
    if (pid == 0) {
	/* netfd should always be 0, but... */ 
	if (netfd > 2) close(netfd);
	child(hname, termtype, lusername, authenticated);
    }
    on = 1;
    ioctl(netfd, FIONBIO, &on);
    ioctl(master, FIONBIO, &on);
    ioctl(master, TIOCPKT, &on);
    signal(SIGCHLD, cleanup);
    protocol(netfd, master);
    signal(SIGCHLD, SIG_IGN);
    cleanup(0);
}

int main(int argc, char **argv) {
    int ch;
    use_rhosts = 1;     /* default */

    openlog("rlogind", LOG_PID | LOG_CONS, LOG_AUTH);

    opterr = 0;
    while ((ch = getopt(argc, argv, "ahLln")) != EOF) {
	switch (ch) {
	    case 'a': check_all = 1; break;
	    case 'h': allow_root_rhosts = 1; break;
	    case 'L': deny_all_rhosts_hequiv = 1; break;
	    case 'l': use_rhosts = 0; break;
	    case 'n': keepalive = 0; break;
	    case '?': default:
		syslog(LOG_ERR, "usage: rlogind [-ahLln]");
		break;
	}
    }
    argc -= optind;
    argv += optind;

    auth_checkoptions();
    
    doit(0);
    return 0;
}
