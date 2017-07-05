/* upstart
 *
 * test_main.c - test suite for init/main.c
 *
 * Copyright © 2013 Canonical Ltd.
 * Author: James Hunt <james.hunt@canonical.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif /* HAVE_CONFIG_H */

#include <nih/string.h>
#include <nih/main.h>
#include <nih/test.h>

#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "conf.h"
#include "job_class.h"
#include "job.h"
#include "xdg.h"

#include "test_util_common.h"


void
test_confdir (void)
{
	char             confdir_a[PATH_MAX];
	char             confdir_b[PATH_MAX];
	char             confdir_c[PATH_MAX];
	char             confdir_d[PATH_MAX];
	char             confdir_e[PATH_MAX];
	char             confdir_f[PATH_MAX];
	char            *xdg_config_home;
	char            *xdg_runtime_dir;
	char             logdir[PATH_MAX];
	pid_t            upstart_pid = 0;
	pid_t            dbus_pid = 0;
	char           **output;
	size_t           lines;
	nih_local char  *cmd = NULL;
	nih_local char  *xdg_conf_dir = NULL;
	nih_local char  *session_file = NULL;
	nih_local char  *path = NULL;

	/* space for 2 sets of confdir options, 2 sets of
	 * prepend-confdir, 2 sets of append-confdirs and a terminator.
	 */
	char            *extra[13];

	xdg_config_home = getenv ("XDG_CONFIG_HOME");
	TEST_NE_P (xdg_config_home, NULL);

	xdg_runtime_dir = getenv ("XDG_RUNTIME_DIR");
	TEST_NE_P (xdg_runtime_dir, NULL);

	TEST_GROUP ("--confdir command-line option handling");

	TEST_FILENAME (confdir_a);
	assert0 (mkdir (confdir_a, 0755));

	TEST_FILENAME (confdir_b);
	assert0 (mkdir (confdir_b, 0755));

	TEST_FILENAME (confdir_c);
	assert0 (mkdir (confdir_c, 0755));

	TEST_FILENAME (confdir_d);
	assert0 (mkdir (confdir_d, 0755));

	TEST_FILENAME (confdir_e);
	assert0 (mkdir (confdir_e, 0755));

	TEST_FILENAME (confdir_f);
	assert0 (mkdir (confdir_f, 0755));

	xdg_conf_dir = nih_sprintf (NULL, "%s/%s", xdg_config_home, "upstart");
	TEST_NE_P (xdg_conf_dir, NULL);
	assert0 (mkdir (xdg_conf_dir, 0755));

	TEST_FILENAME (logdir);
	assert0 (mkdir (logdir, 0755));

	/* disable system default job dir */
	assert0 (setenv ("UPSTART_NO_SYSTEM_USERCONFDIR", "1", 1));

	TEST_DBUS (dbus_pid);

	/************************************************************/
	TEST_FEATURE ("Session Init without --confdir");

	CREATE_FILE (xdg_conf_dir, "foo.conf", "exec true");
	CREATE_FILE (xdg_conf_dir, "bar.conf", "exec true");
	CREATE_FILE (xdg_conf_dir, "baz.conf", "exec true");

	start_upstart_common (&upstart_pid, TRUE, FALSE, NULL, logdir, NULL);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	session_file = get_session_file (xdg_runtime_dir, upstart_pid);

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	TEST_EQ (lines, 3);
	TEST_STR_MATCH (output[0], "bar stop/waiting");
	TEST_STR_MATCH (output[1], "baz stop/waiting");
	TEST_STR_MATCH (output[2], "foo stop/waiting");
	nih_free (output);

	DELETE_FILE (xdg_conf_dir, "foo.conf");
	DELETE_FILE (xdg_conf_dir, "bar.conf");
	DELETE_FILE (xdg_conf_dir, "baz.conf");

	STOP_UPSTART (upstart_pid);
	assert0 (unlink (session_file));

	/************************************************************/
	TEST_FEATURE ("Session Init with --confdir");

	CREATE_FILE (xdg_conf_dir, "xdg_dir_job.conf", "exec true");
	CREATE_FILE (confdir_a, "conf_dir_job.conf", "exec true");

	start_upstart_common (&upstart_pid, TRUE, FALSE, confdir_a, logdir, NULL);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	session_file = get_session_file (xdg_runtime_dir, upstart_pid);

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	/* We expect jobs in xdg_conf_dir to be ignored */
	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], "conf_dir_job stop/waiting");
	nih_free (output);

	DELETE_FILE (xdg_conf_dir, "xdg_dir_job.conf");
	DELETE_FILE (confdir_a, "conf_dir_job.conf");

	STOP_UPSTART (upstart_pid);
	assert0 (unlink (session_file));

	/************************************************************/
	TEST_FEATURE ("Session Init with --prepend-confdir");

	CREATE_FILE (confdir_a, "foo.conf", "exec foo");
	CREATE_FILE (confdir_a, "conflict.conf", "emits prepend");
	CREATE_FILE (xdg_conf_dir, "conflict.conf", "emits confdir");
	CREATE_FILE (xdg_conf_dir, "baz.conf", "exec baz");

	extra[0] = "--prepend-confdir";
	extra[1] = confdir_a;
	extra[2] = NULL;

	start_upstart_common (&upstart_pid, TRUE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	session_file = get_session_file (xdg_runtime_dir, upstart_pid);

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	TEST_EQ (lines, 3);
	TEST_STR_MATCH (output[0], "baz stop/waiting");
	TEST_STR_MATCH (output[1], "conflict stop/waiting");
	TEST_STR_MATCH (output[2], "foo stop/waiting");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config %s 2>&1", get_initctl (), "conflict");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "conflict");
	TEST_STR_MATCH (output[1], "  emits prepend");
	nih_free (output);

	DELETE_FILE (confdir_a, "foo.conf");
	DELETE_FILE (confdir_a, "conflict.conf");
	DELETE_FILE (xdg_conf_dir, "conflict.conf");
	DELETE_FILE (xdg_conf_dir, "baz.conf");

	STOP_UPSTART (upstart_pid);
	assert0 (unlink (session_file));

	/************************************************************/
	TEST_FEATURE ("Session Init with --append-confdir");

	CREATE_FILE (xdg_conf_dir, "xdg_dir_job.conf", "exec true");
	CREATE_FILE (confdir_a, "conf_dir_job.conf", "exec true");

	extra[0] = "--append-confdir";
	extra[1] = confdir_a;
	extra[2] = NULL;

	start_upstart_common (&upstart_pid, TRUE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	session_file = get_session_file (xdg_runtime_dir, upstart_pid);

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	/* jobs in xdg_conf_dir should be considered */
	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "conf_dir_job stop/waiting");
	TEST_STR_MATCH (output[1], "xdg_dir_job stop/waiting");
	nih_free (output);

	DELETE_FILE (xdg_conf_dir, "xdg_dir_job.conf");
	DELETE_FILE (confdir_a, "conf_dir_job.conf");

	STOP_UPSTART (upstart_pid);
	assert0 (unlink (session_file));

	/************************************************************/
	TEST_FEATURE ("Session Init with multiple --confdir");

	CREATE_FILE (xdg_conf_dir, "xdg_dir_job.conf", "exec true");
	CREATE_FILE (confdir_a, "conf_dir_a_job.conf", "exec true");
	CREATE_FILE (confdir_b, "conf_dir_b_job.conf", "exec true");

	extra[0] = "--confdir";
	extra[1] = confdir_a;
	extra[2] = "--confdir";
	extra[3] = confdir_b;
	extra[4] = NULL;

	/* pass 2 confdir directories */
	start_upstart_common (&upstart_pid, TRUE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	session_file = get_session_file (xdg_runtime_dir, upstart_pid);

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	/* We expect jobs in xdg_conf_dir to be ignored */
	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "conf_dir_a_job stop/waiting");
	TEST_STR_MATCH (output[1], "conf_dir_b_job stop/waiting");
	nih_free (output);

	DELETE_FILE (xdg_conf_dir, "xdg_dir_job.conf");
	DELETE_FILE (confdir_a, "conf_dir_a_job.conf");
	DELETE_FILE (confdir_b, "conf_dir_b_job.conf");

	STOP_UPSTART (upstart_pid);
	assert0 (unlink (session_file));

	/************************************************************/
	TEST_FEATURE ("Session Init with multiple --prepend-confdir");

	CREATE_FILE (xdg_conf_dir, "xdg_dir_job.conf", "exec true");
	CREATE_FILE (confdir_a, "conf_dir_a_job.conf", "exec true");
	CREATE_FILE (confdir_b, "conf_dir_b_job.conf", "exec true");

	extra[0] = "--prepend-confdir";
	extra[1] = confdir_a;
	extra[2] = "--prepend-confdir";
	extra[3] = confdir_b;
	extra[4] = NULL;

	/* pass 2 confdir directories */
	start_upstart_common (&upstart_pid, TRUE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	session_file = get_session_file (xdg_runtime_dir, upstart_pid);

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	/* jobs in xdg_conf_dir should be considered */
	TEST_EQ (lines, 3);
	TEST_STR_MATCH (output[0], "conf_dir_a_job stop/waiting");
	TEST_STR_MATCH (output[1], "conf_dir_b_job stop/waiting");
	TEST_STR_MATCH (output[2], "xdg_dir_job stop/waiting");
	nih_free (output);

	DELETE_FILE (xdg_conf_dir, "xdg_dir_job.conf");
	DELETE_FILE (confdir_a, "conf_dir_a_job.conf");
	DELETE_FILE (confdir_b, "conf_dir_b_job.conf");

	STOP_UPSTART (upstart_pid);
	assert0 (unlink (session_file));

	/************************************************************/
	TEST_FEATURE ("Session Init with multiple --append-confdir");

	CREATE_FILE (xdg_conf_dir, "xdg_dir_job.conf", "exec true");
	CREATE_FILE (confdir_a, "conf_dir_a_job.conf", "exec true");
	CREATE_FILE (confdir_b, "conf_dir_b_job.conf", "exec true");

	extra[0] = "--append-confdir";
	extra[1] = confdir_a;
	extra[2] = "--append-confdir";
	extra[3] = confdir_b;
	extra[4] = NULL;

	/* pass 2 confdir directories */
	start_upstart_common (&upstart_pid, TRUE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	session_file = get_session_file (xdg_runtime_dir, upstart_pid);

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	/* jobs in xdg_conf_dir should be considered */
	TEST_EQ (lines, 3);
	TEST_STR_MATCH (output[0], "conf_dir_a_job stop/waiting");
	TEST_STR_MATCH (output[1], "conf_dir_b_job stop/waiting");
	TEST_STR_MATCH (output[2], "xdg_dir_job stop/waiting");
	nih_free (output);

	DELETE_FILE (xdg_conf_dir, "xdg_dir_job.conf");
	DELETE_FILE (confdir_a, "conf_dir_a_job.conf");
	DELETE_FILE (confdir_b, "conf_dir_b_job.conf");

	STOP_UPSTART (upstart_pid);
	assert0 (unlink (session_file));

	/************************************************************/
	TEST_FEATURE ("Session Init with multiple --confdir and conflicting names");

	CREATE_FILE (xdg_conf_dir, "conflict.conf", "emits xdg_conf_dir");
	CREATE_FILE (confdir_a, "conflict.conf", "emits confdir_a");
	CREATE_FILE (confdir_b, "foo.conf", "exec true");

	extra[0] = "--confdir";
	extra[1] = confdir_a;
	extra[2] = "--confdir";
	extra[3] = confdir_b;
	extra[4] = NULL;

	/* pass 2 confdir directories */
	start_upstart_common (&upstart_pid, TRUE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	session_file = get_session_file (xdg_runtime_dir, upstart_pid);

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	/* We expect jobs in xdg_conf_dir to be ignored */
	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "conflict stop/waiting");
	TEST_STR_MATCH (output[1], "foo stop/waiting");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config %s 2>&1", get_initctl (), "conflict");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	/* Ensure the correct version of the conflict job is found */
	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "conflict");
	TEST_STR_MATCH (output[1], "  emits confdir_a");
	nih_free (output);

	DELETE_FILE (xdg_conf_dir, "conflict.conf");
	DELETE_FILE (confdir_a, "conflict.conf");
	DELETE_FILE (confdir_b, "foo.conf");

	STOP_UPSTART (upstart_pid);
	assert0 (unlink (session_file));

	/************************************************************/
	TEST_FEATURE ("Session Init with multiple --prepend-confdir and conflicting names");

	CREATE_FILE (xdg_conf_dir, "conflict.conf", "emits xdg_conf_dir");
	CREATE_FILE (confdir_a, "conflict.conf", "emits confdir_a");
	CREATE_FILE (confdir_b, "foo.conf", "exec true");

	extra[0] = "--prepend-confdir";
	extra[1] = confdir_a;
	extra[2] = "--prepend-confdir";
	extra[3] = confdir_b;
	extra[4] = NULL;

	/* pass 2 confdir directories */
	start_upstart_common (&upstart_pid, TRUE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	session_file = get_session_file (xdg_runtime_dir, upstart_pid);

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	/* We expect jobs in xdg_conf_dir to be ignored */
	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "conflict stop/waiting");
	TEST_STR_MATCH (output[1], "foo stop/waiting");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config %s 2>&1", get_initctl (), "conflict");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	/* Ensure the correct version of the conflict job is found */
	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "conflict");
	TEST_STR_MATCH (output[1], "  emits confdir_a");
	nih_free (output);

	DELETE_FILE (xdg_conf_dir, "conflict.conf");
	DELETE_FILE (confdir_a, "conflict.conf");
	DELETE_FILE (confdir_b, "foo.conf");

	STOP_UPSTART (upstart_pid);
	assert0 (unlink (session_file));

	/************************************************************/
	TEST_FEATURE ("Session Init with multiple --append-confdir and conflicting names");

	CREATE_FILE (xdg_conf_dir, "conflict.conf", "emits xdg_conf_dir");
	CREATE_FILE (confdir_a, "conflict.conf", "emits confdir_a");
	CREATE_FILE (confdir_b, "foo.conf", "exec true");

	extra[0] = "--append-confdir";
	extra[1] = confdir_a;
	extra[2] = "--append-confdir";
	extra[3] = confdir_b;
	extra[4] = NULL;

	/* pass 2 confdir directories */
	start_upstart_common (&upstart_pid, TRUE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	session_file = get_session_file (xdg_runtime_dir, upstart_pid);

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	/* We expect jobs in xdg_conf_dir to be ignored */
	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "conflict stop/waiting");
	TEST_STR_MATCH (output[1], "foo stop/waiting");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config %s 2>&1", get_initctl (), "conflict");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	/* Ensure the correct version of the conflict job is found */
	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "conflict");
	TEST_STR_MATCH (output[1], "  emits xdg_conf_dir");
	nih_free (output);

	DELETE_FILE (xdg_conf_dir, "conflict.conf");
	DELETE_FILE (confdir_a, "conflict.conf");
	DELETE_FILE (confdir_b, "foo.conf");

	STOP_UPSTART (upstart_pid);
	assert0 (unlink (session_file));

	/************************************************************/
	TEST_FEATURE ("Session Init with multiple --confdir, --prepend-confdir and --append-confdir with conflicting names");

	CREATE_FILE (xdg_conf_dir, "conflict.conf", "emits xdg_conf_dir");
	CREATE_FILE (confdir_a, "conflict.conf", "emits confdir_a");
	CREATE_FILE (confdir_b, "foo.conf", "exec true");
	CREATE_FILE (confdir_c, "conflict.conf", "emits confdir_c");
	CREATE_FILE (confdir_d, "conflict.conf", "emits confdir_d");
	CREATE_FILE (confdir_e, "bar.conf", "exec false");

	extra[0] = "--prepend-confdir";
	extra[1] = confdir_d;
	extra[2] = "--prepend-confdir";
	extra[3] = confdir_e;
	extra[4] = "--confdir";
	extra[5] = confdir_a;
	extra[6] = "--confdir";
	extra[7] = confdir_b;
	extra[8] = "--append-confdir";
	extra[9] = confdir_c;
	extra[10] = NULL;

	start_upstart_common (&upstart_pid, TRUE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	session_file = get_session_file (xdg_runtime_dir, upstart_pid);

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	TEST_EQ (lines, 3);
	TEST_STR_MATCH (output[0], "bar stop/waiting");
	TEST_STR_MATCH (output[1], "conflict stop/waiting");
	TEST_STR_MATCH (output[2], "foo stop/waiting");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config %s 2>&1", get_initctl (), "conflict");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	/* Ensure the correct version of the conflict job is found */
	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "conflict");
	TEST_STR_MATCH (output[1], "  emits confdir_d");
	nih_free (output);

	DELETE_FILE (xdg_conf_dir, "conflict.conf");
	DELETE_FILE (confdir_a, "conflict.conf");
	DELETE_FILE (confdir_b, "foo.conf");
	DELETE_FILE (confdir_c, "conflict.conf");
	DELETE_FILE (confdir_d, "conflict.conf");
	DELETE_FILE (confdir_e, "bar.conf");

	STOP_UPSTART (upstart_pid);
	assert0 (unlink (session_file));

	/************************************************************/
	TEST_FEATURE ("Session Init with multiple out of order --confdir, --prepend-confdir and --append-confdir");

	CREATE_FILE (xdg_conf_dir, "conflict.conf", "emits xdg_conf_dir");
	CREATE_FILE (confdir_a, "conflict.conf", "emits confdir_a");
	CREATE_FILE (confdir_b, "foo.conf", "exec true");
	CREATE_FILE (confdir_c, "conflict.conf", "emits confdir_c");
	CREATE_FILE (confdir_d, "conflict.conf", "emits confdir_d");
	CREATE_FILE (confdir_e, "bar.conf", "exec false");
	CREATE_FILE (confdir_f, "baz.conf", "exec false");

	extra[0] = "--append-confdir";
	extra[1] = confdir_a;
	extra[2] = "--prepend-confdir";
	extra[3] = confdir_e;
	extra[4] = "--confdir";
	extra[5] = confdir_b;
	extra[6] = "--append-confdir";
	extra[7] = confdir_c;
	extra[8] = "--prepend-confdir";
	extra[9] = confdir_f;
	extra[10] = "--confdir";
	extra[11] = confdir_d;
	extra[12] = NULL;

	start_upstart_common (&upstart_pid, TRUE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	session_file = get_session_file (xdg_runtime_dir, upstart_pid);

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	TEST_EQ (lines, 4);
	TEST_STR_MATCH (output[0], "bar stop/waiting");
	TEST_STR_MATCH (output[1], "baz stop/waiting");
	TEST_STR_MATCH (output[2], "conflict stop/waiting");
	TEST_STR_MATCH (output[3], "foo stop/waiting");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config %s 2>&1", get_initctl (), "conflict");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	/* Ensure the correct version of the conflict job is found */
	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "conflict");
	TEST_STR_MATCH (output[1], "  emits confdir_d");
	nih_free (output);

	DELETE_FILE (xdg_conf_dir, "conflict.conf");
	DELETE_FILE (confdir_a, "conflict.conf");
	DELETE_FILE (confdir_b, "foo.conf");
	DELETE_FILE (confdir_c, "conflict.conf");
	DELETE_FILE (confdir_d, "conflict.conf");
	DELETE_FILE (confdir_e, "bar.conf");
	DELETE_FILE (confdir_f, "baz.conf");

	STOP_UPSTART (upstart_pid);
	assert0 (unlink (session_file));

	/************************************************************/
	TEST_FEATURE ("System Init without --confdir");

	/* Use the "secret" interface */
	assert0 (setenv ("UPSTART_CONFDIR", confdir_a, 1));

	CREATE_FILE (confdir_a, "foo.conf", "exec true");
	CREATE_FILE (confdir_a, "bar.conf", "exec true");
	CREATE_FILE (confdir_a, "baz.conf", "exec true");

	/* Disable user mode */
	test_user_mode = FALSE;

	start_upstart_common (&upstart_pid, FALSE, FALSE, NULL, logdir, NULL);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	TEST_EQ (lines, 3);
	TEST_STR_MATCH (output[0], "bar stop/waiting");
	TEST_STR_MATCH (output[1], "baz stop/waiting");
	TEST_STR_MATCH (output[2], "foo stop/waiting");
	nih_free (output);

	DELETE_FILE (confdir_a, "foo.conf");
	DELETE_FILE (confdir_a, "bar.conf");
	DELETE_FILE (confdir_a, "baz.conf");

	STOP_UPSTART (upstart_pid);

	/************************************************************/
	TEST_FEATURE ("System Init with --confdir");

	CREATE_FILE (confdir_a, "foo.conf", "exec true");
	CREATE_FILE (confdir_a, "bar.conf", "exec true");
	CREATE_FILE (confdir_b, "baz.conf", "exec true");

	start_upstart_common (&upstart_pid, FALSE, FALSE, confdir_b, logdir, NULL);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], "baz stop/waiting");
	nih_free (output);

	DELETE_FILE (confdir_a, "foo.conf");
	DELETE_FILE (confdir_a, "bar.conf");
	DELETE_FILE (confdir_b, "baz.conf");

	STOP_UPSTART (upstart_pid);

	/************************************************************/
	TEST_FEATURE ("System Init with --prepend-confdir");

	TEST_FALSE (file_exists ("/etc/init/must-not-exist-by-default.conf"));

	CREATE_FILE (confdir_a, "must-not-exist-by-default.conf", "exec true");

	extra[0] = "--prepend-confdir";
	extra[1] = confdir_a;
	extra[2] = NULL;

	start_upstart_common (&upstart_pid, FALSE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	cmd = nih_sprintf (NULL, "%s status %s 2>&1", get_initctl (), "must-not-exist-by-default");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], "must-not-exist-by-default stop/waiting");
	nih_free (output);

	DELETE_FILE (confdir_a, "must-not-exist-by-default.conf");

	STOP_UPSTART (upstart_pid);

	/************************************************************/
	TEST_FEATURE ("System Init with --append-confdir");

	TEST_FALSE (file_exists ("/etc/init/must-not-exist-by-default.conf"));

	CREATE_FILE (confdir_a, "must-not-exist-by-default.conf", "exec true");

	extra[0] = "--append-confdir";
	extra[1] = confdir_a;
	extra[2] = NULL;

	start_upstart_common (&upstart_pid, FALSE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	cmd = nih_sprintf (NULL, "%s status %s 2>&1", get_initctl (), "must-not-exist-by-default");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], "must-not-exist-by-default stop/waiting");
	nih_free (output);

	DELETE_FILE (confdir_a, "must-not-exist-by-default.conf");

	STOP_UPSTART (upstart_pid);

	/************************************************************/
	TEST_FEATURE ("System Init with multiple --confdir");

	assert0 (setenv ("UPSTART_CONFDIR", xdg_conf_dir, 1));

	CREATE_FILE (xdg_conf_dir, "foo.conf", "exec true");
	CREATE_FILE (confdir_a, "bar.conf", "exec true");
	CREATE_FILE (confdir_b, "baz.conf", "exec true");
	CREATE_FILE (confdir_b, "qux.conf", "exec true");

	extra[0] = "--confdir";
	extra[1] = confdir_a;
	extra[2] = "--confdir";
	extra[3] = confdir_b;
	extra[4] = NULL;

	start_upstart_common (&upstart_pid, FALSE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	/* Like a Session Init, the System Init behaviour is (now) to
	 * honour all --confdirs.
	 */
	TEST_EQ (lines, 3);

	TEST_STR_MATCH (output[0], "bar stop/waiting");
	TEST_STR_MATCH (output[1], "baz stop/waiting");
	TEST_STR_MATCH (output[2], "qux stop/waiting");
	nih_free (output);

	DELETE_FILE (xdg_conf_dir, "foo.conf");
	DELETE_FILE (confdir_a, "bar.conf");
	DELETE_FILE (confdir_b, "baz.conf");
	DELETE_FILE (confdir_b, "qux.conf");

	STOP_UPSTART (upstart_pid);

	/************************************************************/
	TEST_FEATURE ("System Init with multiple --prepend-confdir");

	TEST_FALSE (file_exists ("/etc/init/must-not-exist-by-default.conf"));
	TEST_FALSE (file_exists ("/etc/init/must-not-exist-by-default2.conf"));

	CREATE_FILE (confdir_a, "must-not-exist-by-default.conf", "exec true");
	CREATE_FILE (confdir_b, "must-not-exist-by-default2.conf", "exec true");

	extra[0] = "--prepend-confdir";
	extra[1] = confdir_a;
	extra[2] = "--prepend-confdir";
	extra[3] = confdir_b;
	extra[4] = NULL;

	start_upstart_common (&upstart_pid, FALSE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	cmd = nih_sprintf (NULL, "%s status %s 2>&1", get_initctl (), "must-not-exist-by-default");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], "must-not-exist-by-default stop/waiting");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s status %s 2>&1", get_initctl (), "must-not-exist-by-default2");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], "must-not-exist-by-default2 stop/waiting");
	nih_free (output);

	DELETE_FILE (confdir_a, "must-not-exist-by-default.conf");
	DELETE_FILE (confdir_b, "must-not-exist-by-default2.conf");

	STOP_UPSTART (upstart_pid);

	/************************************************************/
	TEST_FEATURE ("System Init with multiple --append-confdir");

	TEST_FALSE (file_exists ("/etc/init/must-not-exist-by-default.conf"));
	TEST_FALSE (file_exists ("/etc/init/must-not-exist-by-default2.conf"));

	CREATE_FILE (confdir_a, "must-not-exist-by-default.conf", "exec true");
	CREATE_FILE (confdir_b, "must-not-exist-by-default2.conf", "exec true");

	extra[0] = "--append-confdir";
	extra[1] = confdir_a;
	extra[2] = "--append-confdir";
	extra[3] = confdir_b;
	extra[4] = NULL;

	start_upstart_common (&upstart_pid, FALSE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	cmd = nih_sprintf (NULL, "%s status %s 2>&1", get_initctl (), "must-not-exist-by-default");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], "must-not-exist-by-default stop/waiting");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s status %s 2>&1", get_initctl (), "must-not-exist-by-default2");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], "must-not-exist-by-default2 stop/waiting");
	nih_free (output);

	DELETE_FILE (confdir_a, "must-not-exist-by-default.conf");
	DELETE_FILE (confdir_b, "must-not-exist-by-default2.conf");

	STOP_UPSTART (upstart_pid);

	/************************************************************/
	TEST_FEATURE ("System Init with multiple --confdir and conflicting names");

	assert0 (setenv ("UPSTART_CONFDIR", xdg_conf_dir, 1));

	CREATE_FILE (xdg_conf_dir, "conflict.conf", "emits xdg_conf_dir");
	CREATE_FILE (confdir_a, "conflict.conf", "emits confdir_a");
	CREATE_FILE (confdir_b, "conflict.conf", "emits confdir_b");

	extra[0] = "--confdir";
	extra[1] = confdir_a;
	extra[2] = "--confdir";
	extra[3] = confdir_b;
	extra[4] = NULL;

	/* pass 2 confdir directories */
	start_upstart_common (&upstart_pid, FALSE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], "conflict stop/waiting");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config %s 2>&1", get_initctl (), "conflict");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	/* Ensure the correct version of the conflict job is found */
	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "conflict");
	TEST_STR_MATCH (output[1], "  emits confdir_a");
	nih_free (output);

	DELETE_FILE (xdg_conf_dir, "conflict.conf");
	DELETE_FILE (confdir_a, "conflict.conf");
	DELETE_FILE (confdir_b, "conflict.conf");

	STOP_UPSTART (upstart_pid);

	/************************************************************/
	TEST_FEATURE ("System Init with multiple --prepend-confdir and conflicting names");

	TEST_FALSE (file_exists ("/etc/init/must-not-exist-by-default.conf"));

	CREATE_FILE (confdir_a, "must-not-exist-by-default.conf", "emits confdir_a");
	CREATE_FILE (confdir_b, "must-not-exist-by-default.conf", "emits confdir_b");

	extra[0] = "--prepend-confdir";
	extra[1] = confdir_a;
	extra[2] = "--prepend-confdir";
	extra[3] = confdir_b;
	extra[4] = NULL;

	start_upstart_common (&upstart_pid, FALSE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	cmd = nih_sprintf (NULL, "%s show-config %s 2>&1", get_initctl (), "must-not-exist-by-default");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	/* Ensure the correct version of the conflict job is found */
	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "must-not-exist-by-default");
	TEST_STR_MATCH (output[1], "  emits confdir_a");
	nih_free (output);

	DELETE_FILE (confdir_a, "must-not-exist-by-default.conf");
	DELETE_FILE (confdir_b, "must-not-exist-by-default.conf");

	STOP_UPSTART (upstart_pid);

	/************************************************************/
	TEST_FEATURE ("System Init with multiple --append-confdir and conflicting names");

	TEST_FALSE (file_exists ("/etc/init/must-not-exist-by-default.conf"));

	CREATE_FILE (confdir_a, "must-not-exist-by-default.conf", "emits confdir_a");
	CREATE_FILE (confdir_b, "must-not-exist-by-default.conf", "emits confdir_b");

	extra[0] = "--append-confdir";
	extra[1] = confdir_a;
	extra[2] = "--append-confdir";
	extra[3] = confdir_b;
	extra[4] = NULL;

	start_upstart_common (&upstart_pid, FALSE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	cmd = nih_sprintf (NULL, "%s show-config %s 2>&1", get_initctl (), "must-not-exist-by-default");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	/* Ensure the correct version of the conflict job is found */
	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "must-not-exist-by-default");
	TEST_STR_MATCH (output[1], "  emits confdir_a");
	nih_free (output);

	DELETE_FILE (confdir_a, "must-not-exist-by-default.conf");
	DELETE_FILE (confdir_b, "must-not-exist-by-default.conf");

	STOP_UPSTART (upstart_pid);

	/************************************************************/
	TEST_FEATURE ("System Init with multiple out of order --confdir, --prepend-confdir and --append-confdir");

	CREATE_FILE (confdir_a, "conflict.conf", "emits confdir_a");
	CREATE_FILE (confdir_a, "wibble.conf", "emits wobble");
	CREATE_FILE (confdir_b, "conflict.conf", "emits confdir_b");
	CREATE_FILE (confdir_c, "conflict.conf", "emits confdir_c");
	CREATE_FILE (confdir_d, "foo.conf", "emits hello");
	CREATE_FILE (confdir_e, "bar.conf", "emits world");
	CREATE_FILE (confdir_e, "conflict.conf", "emits confdir_e");
	CREATE_FILE (confdir_f, "conflict.conf", "emits confdir_f");
	CREATE_FILE (confdir_f, "baz.conf", "exec true");

	extra[0] = "--append-confdir";
	extra[1] = confdir_a;
	extra[2] = "--prepend-confdir";
	extra[3] = confdir_e;
	extra[4] = "--confdir";
	extra[5] = confdir_b;
	extra[6] = "--append-confdir";
	extra[7] = confdir_f;
	extra[8] = "--confdir";
	extra[9] = confdir_c;
	extra[10] = "--prepend-confdir";
	extra[11] = confdir_d;
	extra[12] = NULL;

	start_upstart_common (&upstart_pid, FALSE, FALSE, NULL, logdir, extra);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	TEST_EQ (lines, 5);
	TEST_STR_MATCH (output[0], "bar stop/waiting");
	TEST_STR_MATCH (output[1], "baz stop/waiting");
	TEST_STR_MATCH (output[2], "conflict stop/waiting");
	TEST_STR_MATCH (output[3], "foo stop/waiting");
	TEST_STR_MATCH (output[4], "wibble stop/waiting");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config %s 2>&1", get_initctl (), "conflict");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "conflict");
	TEST_STR_MATCH (output[1], "  emits confdir_e");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config %s 2>&1", get_initctl (), "wibble");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "wibble");
	TEST_STR_MATCH (output[1], "  emits wobble");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config %s 2>&1", get_initctl (), "foo");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "foo");
	TEST_STR_MATCH (output[1], "  emits hello");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config %s 2>&1", get_initctl (), "bar");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "bar");
	TEST_STR_MATCH (output[1], "  emits world");
	nih_free (output);

	DELETE_FILE (confdir_a, "conflict.conf");
	DELETE_FILE (confdir_a, "wibble.conf");
	DELETE_FILE (confdir_b, "conflict.conf");
	DELETE_FILE (confdir_c, "conflict.conf");
	DELETE_FILE (confdir_d, "foo.conf");
	DELETE_FILE (confdir_e, "bar.conf");
	DELETE_FILE (confdir_e, "conflict.conf");
	DELETE_FILE (confdir_f, "conflict.conf");
	DELETE_FILE (confdir_f, "baz.conf");

	STOP_UPSTART (upstart_pid);

	TEST_DBUS_END (dbus_pid);

	assert0 (rmdir (confdir_a));
	assert0 (rmdir (confdir_b));
	assert0 (rmdir (confdir_c));
	assert0 (rmdir (confdir_d));
	assert0 (rmdir (confdir_e));
	assert0 (rmdir (confdir_f));
	assert0 (rmdir (xdg_conf_dir));
	assert0 (rmdir (logdir));
	assert0 (unsetenv ("UPSTART_CONFDIR"));
}

int
main (int   argc,
      char *argv[])
{
	test_common_setup ();

	test_confdir ();

	test_common_cleanup ();

	return 0;
}
