/* Original code copied from uclibc if_index.c. Original copyright is
   below.
 */

/* Copyright (C) 1997, 1998, 1999, 2000, 2002, 2003, 2004, 2005
   Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.

   Reworked Dec 2002 by Erik Andersen <andersen@codepoet.org>
 */

#define __FORCE_GLIBC
#include <features.h>
#include <string.h>
#include <alloca.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
//#include <libc-internal.h>
//#include <bits/stackinfo.h>

/* The following code fragments are taken from uclibc. They are
 * included here because the original code which we cut-and-paste here
 * uses some internal uclibc functions which are not available to
 * external code.
 */

/* Uncancelable close. We just use the cancelable version here. */
#define close_not_cancel(fd) \
  close(fd)

#define close_not_cancel_no_status(fd) \
  (void) ({ close(fd); })

#if _STACK_GROWS_DOWN
# define extend_alloca(buf, len, newlen) \
  (__typeof (buf)) ({ size_t __newlen = (newlen);			      \
		      char *__newbuf = alloca (__newlen);		      \
		      if (__newbuf + __newlen == (char *) buf)		      \
			len += __newlen;				      \
		      else						      \
			len = __newlen;					      \
		      __newbuf; })
#elif _STACK_GROWS_UP
# define extend_alloca(buf, len, newlen) \
  (__typeof (buf)) ({ size_t __newlen = (newlen);			      \
		      char *__newbuf = alloca (__newlen);		      \
		      char *__buf = (buf);				      \
		      if (__buf + __newlen == __newbuf)			      \
			{						      \
			  len += __newlen;				      \
			  __newbuf = __buf;				      \
			}						      \
		      else						      \
			len = __newlen;					      \
		      __newbuf; })
#else
# warning unknown stack
# define extend_alloca(buf, len, newlen) \
  alloca (((len) = (newlen)))
#endif

/* Return a socket of any type.  The socket can be used in subsequent
   ioctl calls to talk to the kernel.  */
static int __opensock (void)
{
  int fd;
#ifdef __UCLIBC_HAS_IPV6__
  fd = socket(AF_INET6, SOCK_DGRAM, 0);
  if (fd<0)
#endif /* __UCLIBC_HAS_IPV6__ */
    fd = socket(AF_INET, SOCK_DGRAM, 0);
  return(fd);
}

/* The main purpose of this library is to filter duplicates from the
 * returned interface list. This function is called to check if the
 * named interface is already in the list.
 */
static int __is_duplicate(char *name, struct if_nameindex *idx, unsigned int nifs)
{
  int i;

  for (i = 0; i < nifs; ++i)
    {
      if (idx[i].if_name == NULL)
	break;

      if (!strcmp(idx[i].if_name, name))
	return 1;
    }

  return 0;
}

/* This code is almost identical to the standard uclibc version, apart
 * from the use of __is_duplicate().
 */
struct if_nameindex *if_nameindex (void)
{
#ifndef SIOCGIFINDEX
  __set_errno (ENOSYS);
  return NULL;
#else
  int fd = __opensock ();
  struct ifconf ifc;
  unsigned int nifs, i, k;
  int rq_len;
  struct if_nameindex *idx = NULL;
# define RQ_IFS	4

  if (fd < 0)
    return NULL;

  ifc.ifc_buf = NULL;

  /* Guess on the correct buffer size... */
  rq_len = RQ_IFS * sizeof (struct ifreq);

  /* Read all the interfaces out of the kernel.  */
  /* Note: alloca's in this loop are diff from glibc because it's smaller */
  do
    {
      ifc.ifc_buf = extend_alloca (ifc.ifc_buf, rq_len, 2 * rq_len);
      ifc.ifc_len = rq_len;

      if (ioctl (fd, SIOCGIFCONF, &ifc) < 0)
	{
#ifdef __UCLIBC_HAS_THREADS_NATIVE__
	  close_not_cancel_no_status (fd);
#else
	  close (fd);
#endif
	  return NULL;
	}
    }
  while (ifc.ifc_len == rq_len);

  nifs = ifc.ifc_len / sizeof(struct ifreq);

  idx = calloc ((nifs + 1), sizeof (struct if_nameindex));
  if (idx == NULL)
    {
#ifdef __UCLIBC_HAS_THREADS_NATIVE__
      close_not_cancel_no_status (fd);
#else
      close(fd);
#endif
      __set_errno(ENOBUFS);
      return NULL;
    }

  k = 0;
  for (i = 0; i < nifs; ++i)
    {
      struct ifreq *ifr = &ifc.ifc_req[i];

      if (ifr->ifr_name == NULL) {
	continue;
      }

      if (__is_duplicate (ifr->ifr_name, idx, nifs)) {
	continue;
      }

      idx[k].if_name = strdup (ifr->ifr_name);
      if (idx[k].if_name == NULL
	  || ioctl (fd, SIOCGIFINDEX, ifr) < 0)
	{
	  int saved_errno = errno;
	  unsigned int j;

	  for (j =  0; j < i; ++j)
	    free (idx[j].if_name);
	  free(idx);
#ifdef __UCLIBC_HAS_THREADS_NATIVE__
	  close_not_cancel_no_status (fd);
#else
	  close(fd);
#endif
	  if (saved_errno == EINVAL)
	    saved_errno = ENOSYS;
	  else if (saved_errno == ENOMEM)
	    saved_errno = ENOBUFS;
	  __set_errno (saved_errno);
	  return NULL;
	}

      idx[k].if_index = ifr->ifr_ifindex;
      k++;
    }

  idx[k].if_index = 0;
  idx[k].if_name = NULL;

#ifdef __UCLIBC_HAS_THREADS_NATIVE__
  close_not_cancel_no_status (fd);
#else
  close(fd);
#endif
  return idx;
#endif
}
