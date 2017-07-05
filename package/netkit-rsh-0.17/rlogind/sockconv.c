/*
 * A generic conversation function for text based applications
 *
 * Written by Andrew Morgan <morgan@physics.ucla.edu>
 *    modified for socket file descriptors by Erik Troan <ewt@redhat.com>
 *
 * $Log: sockconv.c,v $
 * Revision 1.6  1999/10/02 21:50:52  dholland
 * Various minor cleanup; straighten out (hopefully) the problems in
 * rlogind/auth.c.
 *
 * Revision 1.5  1999/09/30 23:23:14  netbug
 * added the TYPE(socklen_t) check to the MCONFIG.in files
 * question? do I need to update the .cvsignore files to
 * prevent CVS checking in configure scripts....
 *
 * Revision 1.4  1999/03/27 07:42:06  dholland
 * PAM changes.
 *
 * Revision 1.3  1998/03/08 16:51:50  root
 * grabbed the redhat pam patches and integrated most of it
 * though I've decided to go with xstrdup as opposed to pam's x_strdup
 *
 * Revision 1.2  1997/06/08 19:57:22  dholland
 * minor fix - don't define __USE_BSD if already defined.
 *
 * Revision 1.1  1997/04/06 00:32:37  dholland
 * Initial revision
 *
 *
 * From: misc_conv.c,v 1.2 1996/07/07 23:59:56 morgan Exp
 *
 * Revision 1.2  1996/07/07 23:59:56  morgan
 * changed the name of the misc include file
 *
 * Revision 1.1  1996/05/02 05:17:06  morgan
 * Initial revision
 */

#include <stdio.h>
#include <stdlib.h>
#ifndef __USE_BSD
#define __USE_BSD                /* needed for prototype for getpass() */
#endif
#include <unistd.h>

#include <security/pam_appl.h>
#include <security/pam_misc.h>

int sock_conv(int num_msg, const struct pam_message **msgm,
	      struct pam_response **response, void *appdata_ptr);

#define INPUTSIZE PAM_MAX_MSG_SIZE

#define CONV_ECHO_ON  1
#define CONV_ECHO_OFF 0

static char *read_string(int echo, const char *remark)
{
  char buffer[INPUTSIZE];
  char *text;
  int charsRead = 0;
  char * nl = "\n\r";
  
  fprintf(stderr,"%s",remark);
  
  while (charsRead < (INPUTSIZE - 1)) {
    read(0, &buffer[charsRead], 1);
    
    if (buffer[charsRead] == '\r') {
      write(1, nl, 2);
      buffer[charsRead] = '\0';
      break;
    }
    
    if (echo) {
      write(1, &buffer[charsRead], 1);
    }
    
    charsRead++;
  }

  /* get some space for this text */
  text = strdup(buffer);
  
  return (text);
}

static void drop_reply(struct pam_response *reply, int replies)
{
  int i;
  
  for (i=0; i<replies; ++i) {
    _pam_overwrite(reply[i].resp);      /* might be a password */
    free(reply[i].resp);
  }
  if (reply)
    free(reply);
}

int sock_conv(int num_msg, const struct pam_message **msgm,
	      struct pam_response **response, void *appdata_ptr)
{
  int replies=0;
  struct pam_response *reply=NULL;
  char *string=NULL; /* ...and all shall be INITIALISED */
  
  reply = malloc(sizeof(struct pam_response) * num_msg);
  if (!reply) return PAM_CONV_ERR;
  
  for (replies=0; replies < num_msg; replies++) {
    string = NULL;
    switch (msgm[replies]->msg_style) {
    case PAM_PROMPT_ECHO_OFF:
      string = read_string(CONV_ECHO_OFF,msgm[replies]->msg);
      if (string == NULL) {
	drop_reply(reply,replies);
	return (PAM_CONV_ERR);
      }
      break;
    case PAM_PROMPT_ECHO_ON:
      string = read_string(CONV_ECHO_ON,msgm[replies]->msg);
      if (string == NULL) {
	drop_reply(reply,replies);
	return (PAM_CONV_ERR);
      }
      break;
    case PAM_ERROR_MSG:
      fprintf(stderr,"%s\n",msgm[replies]->msg);
      string = NULL;
      
      break;
    case PAM_TEXT_INFO:
      fprintf(stderr,"%s\n",msgm[replies]->msg);
      string = NULL;
      break;
    default:
      fprintf(stderr, "erroneous conversation (%d)\n"
	      ,msgm[replies]->msg_style);
      drop_reply(reply,replies);
      return (PAM_CONV_ERR);
    }
    
    /* add string to list of responses */
    reply[replies].resp_retcode = 0;
    reply[replies].resp = string;
    
  }
  
  *response = reply;

   /* shut up gcc */
   appdata_ptr=NULL;
  
  
  return PAM_SUCCESS;
}
