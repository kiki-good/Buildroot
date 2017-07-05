/*
 * Copyright (C) 1995, 1997-1999 Jeffrey A. Uphoff
 * Modified by Olaf Kirch, Oct. 1996.
 * Modified by Lon Hohberger, Oct. 2000.
 *
 * NSM for Linux.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "statd.h"
#include "notlist.h"

/* Callback notify list. */
/* notify_list *cbnl = NULL; ... never used */


/* 
 * Services SM_NOTIFY requests.
 * Any clients that have asked us to monitor that host are put on
 * the global callback list, which is processed as soon as statd
 * returns to svc_run.
 */
void *
sm_notify_1_svc(struct stat_chge *argp, struct svc_req *rqstp)
{
	notify_list    *lp, *call;
	static char    *result = NULL;

	dprintf(N_DEBUG, "Received SM_NOTIFY from %s, state: %d",
				argp->mon_name, argp->state);

	/* quick check - don't bother if we're not monitoring anyone */
	/* LH - this was != MULL, meaning that if anyone _was_ in our RTNL,
	 * we'd never pass this point. */
	if (!(lp = rtnl)) {
		note(N_WARNING, "SM_NOTIFY from %s while not monitoring any hosts.",
				argp->mon_name, argp->state);
		return ((void *) &result);
	}

	/* okir change: statd doesn't remove the remote host from its
	 * internal monitor list when receiving an SM_NOTIFY call from
	 * it. Lockd will want to continue monitoring the remote host
	 * until it issues an SM_UNMON call.
	 */
	while ((lp = nlist_gethost(lp, argp->mon_name, 0)) != NULL) {
		if (NL_STATE(lp) != argp->state) {
			NL_STATE(lp) = argp->state;
			call = nlist_clone(lp);
			NL_TYPE(call) = NOTIFY_CALLBACK;
			nlist_insert(&notify, call);
		}
		lp = NL_NEXT(lp);
	}

	return ((void *) &result);
}
