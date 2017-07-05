/* upstart
 *
 * test_util_common.c - common test utilities
 *
 * Copyright © 2012-2013 Canonical Ltd.
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

#include <nih/test.h>
#include <nih/file.h>
#include <nih/string.h>
#include <nih/signal.h>
#include <nih/logging.h>
#include <nih/timer.h>
#include <nih/io.h>
#include <nih/child.h>
#include <nih/main.h>
#include <nih-dbus/test_dbus.h>

#include <dbus/dbus.h>

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <regex.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <time.h>

#include <nih-dbus/dbus_error.h>
#include <nih-dbus/dbus_connection.h>
#include <nih-dbus/dbus_proxy.h>
#include <nih-dbus/errors.h>  

#include "dbus/upstart.h"

#include <nih-dbus/dbus_connection.h>
#ifdef ENABLE_CGROUPS
#include <cgmanager/cgmanager-client.h>
#endif

#include "test_util_common.h"

#ifndef UPSTART_BINARY
#error unable to find init binary as UPSTART_BINARY not defined
#endif /* UPSTART_BINARY */

#ifndef INITCTL_BINARY
#error unable to find initctl binary as INITCTL_BINARY not defined
#endif /* INITCTL_BINARY */

static char *saved_xdg_config_home = NULL;
static char *saved_xdg_runtime_dir = NULL;
static char  test_xdg_config_home[PATH_MAX];
static char  test_xdg_runtime_dir[PATH_MAX];

#ifdef ENABLE_CGROUPS

static NihDBusProxy *cgroup_manager;

#endif /* ENABLE_CGROUPS */

/**
 * test_setup_called:
 *
 * Set to TRUE if test_setup() called.
 **/
static int test_setup_called = FALSE;

static void selfpipe_write (int n);
static void selfpipe_setup (void);

/**
 * wait_for_upstart:
 *
 * @session_init_pid: pid of Session Init (which uses a private bus
 * rather than the session bus), else 0.
 *
 * Wait for Upstart to appear on D-Bus denoting its completion of
 * initialisation. Wait time is somewhat arbitrary (but more
 * than adequate!).
 **/
void
wait_for_upstart (int session_init_pid)
{
	nih_local NihDBusProxy *upstart = NULL;
	DBusConnection         *connection;
	char                   *address;
	NihError               *err;
	int                     running = FALSE;

	/* XXX: arbitrary value */
	int                     attempts = 10;

	if (session_init_pid) {
		TEST_TRUE (set_upstart_session (session_init_pid));
		address = getenv ("UPSTART_SESSION");
	} else {
		address = getenv ("DBUS_SESSION_BUS_ADDRESS");
	}

	TEST_TRUE (address);

	while (attempts) {
		attempts--;
		sleep (1);
		connection = nih_dbus_connect (address, NULL);

		if (! connection) {
			err = nih_error_get ();
			nih_free (err);
			continue;
		}

		upstart = nih_dbus_proxy_new (NULL, connection,
				      	      NULL,
					      DBUS_PATH_UPSTART,
				      	      NULL, NULL);

		if (! upstart) {
			err = nih_error_get ();
			nih_free (err);
			dbus_connection_unref (connection);
		} else {
			running = TRUE;
			break;
		}
	}
	TEST_EQ (running, TRUE);
}

/**
 * session_init_reexec:
 *
 * @pid: pid of Session Init.
 *
 * Cause the Session Init running as pid @pid to re-exec.
 **/
void
session_init_reexec (pid_t pid)
{
	nih_local NihDBusProxy *upstart = NULL;
	char                   *address;
	DBusConnection         *connection;
	DBusMessage            *method_call;
	DBusMessageIter         iter;
	DBusError               error;

	TEST_TRUE (pid);

	TEST_TRUE (set_upstart_session (pid));
	address = getenv ("UPSTART_SESSION");

	TEST_TRUE (address);

	connection = nih_dbus_connect (address, NULL);
	TEST_NE_P (connection, NULL);

	upstart = nih_dbus_proxy_new (NULL, connection,
			NULL,
			DBUS_PATH_UPSTART,
			NULL, NULL);
	TEST_NE_P (upstart, NULL);

	method_call = dbus_message_new_method_call (upstart->name,
			upstart->path,
			"com.ubuntu.Upstart0_6", "Restart");
	TEST_NE_P (method_call, NULL);

	dbus_message_set_auto_start (method_call, upstart->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	/* Don't bother checking reply - Upstart will sever the
	 * connection anyway.
	 */
	(void)dbus_connection_send_with_reply_and_block (upstart->connection, method_call, -1, &error);

	dbus_message_unref (method_call);
	dbus_connection_unref (connection);
}

/* TRUE to denote that Upstart is running in user session mode
 * (FALSE to denote it's using the users D-Bus session bus).
 */
int test_user_mode = FALSE;

/**
 * set_upstart_session:
 *
 * @session_init_pid: pid of Session Init.
 *
 * Attempt to "enter" an Upstart session by setting UPSTART_SESSION to
 * the value of the session running under pid @session_init_pid.
 *
 * Returns: TRUE if it was possible to enter the currently running
 * Upstart session, else FALSE.
 **/
int
set_upstart_session (pid_t session_init_pid)
{
	char                     *value;
	nih_local char           *cmd = NULL;
	nih_local char          **output = NULL;
	size_t                    lines = 0;
	int                       got = FALSE;
	int                       i;
	pid_t                     pid;

	/* XXX: arbitrary value */
	int                       loops = 5;

	nih_assert (session_init_pid);

	/* list-sessions relies on this */
	if (! getenv ("XDG_RUNTIME_DIR"))
		return FALSE;

	cmd = nih_sprintf (NULL, "%s list-sessions 2>&1", get_initctl_binary ());
	TEST_NE_P (cmd, NULL);

	/* We expect the list-sessions command to return a valid session
	 * within a reasonable period of time.
	 */
	for (i = 0; i < loops; i++) {
		sleep (1);

		RUN_COMMAND (NULL, cmd, &output, &lines);

		if (lines < 1)
			continue;

		/* Look for the specific session */
		for (size_t line = 0; line < lines; lines++) {

			/* No pid in output */
			if (! isdigit(output[line][0]))
				continue;

			pid = (pid_t)atoi(output[line]);
			nih_assert (pid > 0);

			if (pid != session_init_pid)
				continue;

			/* look for separator between pid and value of
			 * UPSTART_SESSION.
			 */
			value = strstr (output[0], " ");
			if (! value)
				continue;

			/* jump over space */
			value  += 1;
			if (! value)
				continue;

			/* No socket address */
			if (strstr (value, "unix:abstract") == value) {
				got = TRUE;
				goto out;
			}
		}
	}

out:

	if (got != TRUE)
		return FALSE;

	assert0 (setenv ("UPSTART_SESSION", value, 1));

	return TRUE;
}

/**
 * selfpipe:
 *
 * Used to allow a timed process wait.
 **/
static int selfpipe[2] = { -1, -1 };

static void
selfpipe_write (int n)
{
    assert (selfpipe[1] != -1);

    TEST_EQ (write (selfpipe[1], "", 1), 1);
}

/**
 * selfpipe_setup:
 *
 * Arrange for SIGCHLD to write to selfpipe such that we can select(2)
 * on child process status changes.
 **/
static void
selfpipe_setup (void)
{
    static struct sigaction  act;
    int                      read_flags;
    int                      write_flags;

    assert (selfpipe[0] == -1);

    assert (! pipe (selfpipe));

    /* Set non-blocking */
    read_flags = fcntl (selfpipe[0], F_GETFL);
    write_flags = fcntl (selfpipe[1], F_GETFL);

    read_flags |= O_NONBLOCK;
    write_flags |= O_NONBLOCK;

    assert (fcntl (selfpipe[0], F_SETFL, read_flags) == 0);
    assert (fcntl (selfpipe[1], F_SETFL, write_flags) == 0);

    /* Don't leak */
    assert (fcntl (selfpipe[0], F_SETFD, FD_CLOEXEC) == 0);
    assert (fcntl (selfpipe[1], F_SETFD, FD_CLOEXEC) == 0);

    memset (&act, 0, sizeof (act));

    /* register SIGCHLD handler which will cause pipe write when child
     * changes state.
     */
    act.sa_handler = selfpipe_write;

    sigaction (SIGCHLD, &act, NULL);
}

/**
 * have_timed_waitpid
 *
 * Return TRUE if precise timing information is available for timing
 * tests.
 **/
int
have_timed_waitpid (void)
{
	struct timespec res;

	if (clock_getres (CLOCK_MONOTONIC_RAW, &res) < 0)
		return FALSE;

	return TRUE;
}

/**
 * timed_waitpid:
 *
 * @pid: pid to wait for,
 * @timeout: seconds to wait for @pid to change state.
 *
 * Simplified waitpid(2) with timeout using a pipe to allow select(2)
 * with timeout to be used to wait for process state change.
 *
 * Returns: as waitpid(2).
 **/
pid_t
timed_waitpid (pid_t pid, time_t timeout)
{
    static char     buffer[1];
    fd_set          read_fds;
    struct timeval  tv;
    int             status;
    int             nfds;
    int             ret;
    pid_t           ret2;

    assert (pid);
    assert (timeout);

    if (selfpipe[0] == -1)
	    selfpipe_setup ();

    FD_ZERO (&read_fds);
    FD_SET (selfpipe[0], &read_fds);

    nfds = 1 + selfpipe[0];

    tv.tv_sec   = timeout;
    tv.tv_usec  = 0;

    /* wait for some activity */
    ret = select (nfds, &read_fds, NULL, NULL, &tv);

    if (! ret)
	    /* timed out */
	    return 0;

    /* discard any data written to pipe */
    while (read (selfpipe[0], buffer, sizeof (buffer)) > 0)
	    ;

    while (TRUE) {
	    /* wait for status change or error */
	    ret2 = waitpid (pid, &status, WNOHANG);

	    if (ret2 < 0)
		    return -1;

	    if (! ret2)
		    /* give child a chance to change state */
		    sleep (1);

	    if (ret2) {
		    if (WIFEXITED (status))
			    return ret2;

		    /* unexpected status change */
		    return -1;
	    }
    }
}


/**
 * get_initctl():
 *
 * Determine a suitable initctl command-line for testing purposes.
 *
 * Returns: Static string representing full path to initctl binary with
 * default option to allow communication with an Upstart started using
 * START_UPSTART().
 **/
char *
get_initctl (void)
{
	static char path[PATH_MAX + 1024] = { 0 };
	int         ret;
	int         env_valid;

	/* Sanity check calling environment */
	if (test_user_mode) {
		env_valid = getenv ("UPSTART_SESSION") ? TRUE : FALSE;
	} else {
		env_valid = getenv ("DBUS_SESSION_BUS_ADDRESS") ? TRUE : FALSE;
	}

	nih_assert (env_valid);

	ret = sprintf (path, "%s %s",
			get_initctl_binary (),
			test_user_mode
			? "--user"
			: "--session");

	assert (ret > 0);

	return path;
}

/*
 * _start_upstart:
 *
 * @pid: PID of running instance,
 * @user: TRUE if upstart will run in User Session mode (FALSE to
 *  use the users D-Bus session bus),
 * @args: optional list of arguments to specify.
 *
 * Start an instance of Upstart.
 *
 * If the instance fails to start, abort(3) is called.
 **/
void
_start_upstart (pid_t *pid, int user, char * const *args)
{
	nih_local char  **argv = NULL;
	sigset_t          child_set, orig_set;

	assert (pid);

	argv = NIH_MUST (nih_str_array_new (NULL));

	NIH_MUST (nih_str_array_add (&argv, NULL, NULL,
				get_upstart_binary ()));

	if (args)
		NIH_MUST (nih_str_array_append (&argv, NULL, NULL, args));

	sigfillset (&child_set);
	sigprocmask (SIG_BLOCK, &child_set, &orig_set);

	TEST_NE (*pid = fork (), -1);

	if (! *pid) {
		char  *argv0;
		int    fd;

		nih_signal_reset ();

		sigprocmask (SIG_SETMASK, &orig_set, NULL);

		if (! getenv ("UPSTART_TEST_VERBOSE")) {
			fd = open ("/dev/null", O_RDWR);
			assert (fd >= 0);
			assert (dup2 (fd, STDIN_FILENO) != -1);
			assert (dup2 (fd, STDOUT_FILENO) != -1);
			assert (dup2 (fd, STDERR_FILENO) != -1);
		}

		argv0 = argv[0];
		assert (execvp (argv0, argv) != -1);
	}

	sigprocmask (SIG_SETMASK, &orig_set, NULL);
	wait_for_upstart (user ? *pid : 0);
}

/**
 * start_upstart_common:
 *
 * @pid: PID of running instance,
 * @user: TRUE if upstart should run in User Session mode (FALSE to
 * use the users D-Bus session bus),
 * @inherit_env: if TRUE, inherit parent environment,
 * @confdir: full path to configuration directory,
 * @logdir: full path to log directory,
 * @extra: optional extra arguments.
 *
 * Wrapper round _start_upstart() which specifies common options.
 **/
void
start_upstart_common (pid_t *pid, int user, int inherit_env,
		      const char *confdir, const char *logdir,
		      char * const *extra)
{
	nih_local char  **args = NULL;

	assert (pid);

	args = NIH_MUST (nih_str_array_new (NULL));

	if (user) {
		NIH_MUST (nih_str_array_add (&args, NULL, NULL,
					"--user"));
		test_user_mode = TRUE;
	} else {
		TEST_TRUE (getenv ("DBUS_SESSION_BUS_ADDRESS"));
		NIH_MUST (nih_str_array_add (&args, NULL, NULL,
					"--session"));
	}

	if (! inherit_env) {
		NIH_MUST (nih_str_array_add (&args, NULL, NULL,
					"--no-inherit-env"));
	}

	if (confdir) {
		NIH_MUST (nih_str_array_add (&args, NULL, NULL,
					"--confdir"));
		NIH_MUST (nih_str_array_add (&args, NULL, NULL,
					confdir));
	}

	if (logdir) {
		NIH_MUST (nih_str_array_add (&args, NULL, NULL,
					"--logdir"));
		NIH_MUST (nih_str_array_add (&args, NULL, NULL,
					logdir));
	}

	if (extra)
		NIH_MUST (nih_str_array_append (&args, NULL, NULL, extra));

	_start_upstart (pid, user, args);
}

/**
 * start_upstart:
 *
 * @pid: PID of running instance.
 *
 * Wrapper round _start_upstart() which just runs an instance with no
 * options.
 **/
void
start_upstart (pid_t *pid)
{
	start_upstart_common (pid, FALSE, FALSE, NULL, NULL, NULL);
}

/**
 * job_to_pid:
 *
 * @job: job name.
 *
 * Determine pid of running job.
 *
 * WARNING: it is the callers responsibility to ensure that
 * @job is still running when this function is called!!
 *
 * Returns: pid of job, or -1 if not found.
 **/
pid_t
job_to_pid (const char *job)
{
	pid_t            pid;
	regex_t          regex;
	regmatch_t       regmatch[2];
	int              ret;
	nih_local char  *cmd = NULL;
	nih_local char  *pattern = NULL;
	size_t           lines;
	char           **status;
	nih_local char  *str_pid = NULL;

	assert (job);

	pattern = NIH_MUST (nih_sprintf
			(NULL, "^\\b%s\\b .*, process ([0-9]+)", job));

	cmd = NIH_MUST (nih_sprintf (NULL, "%s status %s 2>&1",
			get_initctl (), job));
	RUN_COMMAND (NULL, cmd, &status, &lines);
	TEST_EQ (lines, 1);

	ret = regcomp (&regex, pattern, REG_EXTENDED);
	assert0 (ret);

	ret = regexec (&regex, status[0], 2, regmatch, 0);
	if (ret == REG_NOMATCH) {
		ret = -1;
		goto out;
	}
	assert0 (ret);

	if (regmatch[1].rm_so == -1 || regmatch[1].rm_eo == -1) {
		ret = -1;
		goto out;
	}

	/* extract the pid */
	NIH_MUST (nih_strncat (&str_pid, NULL,
			&status[0][regmatch[1].rm_so],
			regmatch[1].rm_eo - regmatch[1].rm_so));

	nih_free (status);

	pid = (pid_t)atol (str_pid);

	/* check it's running */
	ret = kill (pid, 0);
	if (! ret)
		ret = pid;

out:
	regfree (&regex);
	return ret;
}

const char *
get_upstart_binary (void)
{
	static const char *upstart_binary = UPSTART_BINARY;

	TEST_TRUE (file_exists (upstart_binary));

	return upstart_binary;
}

const char *
get_initctl_binary (void)
{
	static const char *initctl_binary = INITCTL_BINARY;

	TEST_TRUE (file_exists (initctl_binary));

	return initctl_binary;
}

/**
 * string_check:
 *
 * @a: first string,
 * @b: second string.
 *
 * Compare @a and @b either or both of which may be NULL.
 *
 * Returns 0 if strings are identical or both NULL, else 1.
 **/
int
string_check (const char *a, const char *b)
{
	if (!a && !b)
		return 0;

	if (!a || !b)
		return 1;

	if (strcmp (a, b))
		return 1;

	return 0;
}

/**
 * strcmp_compar:
 *
 * @a: first string,
 * @b: second string.
 *
 * String comparison function suitable for passing to qsort(3).
 * See the qsort(3) man page for further details.
 **/
int
strcmp_compar (const void *a, const void *b)
{
	return strcmp(*(char * const *)a, *(char * const *)b);
}

/**
 * get_session_file:
 *
 * @xdg_runtime_dir: Directory to treat as XDG_RUNTIME_DIR,
 * @pid: pid of running Session Init instance.
 *
 * Determine full path to a Session Inits session file.
 *
 * Note: No check on the existence of the session file is performed.
 *
 * Returns: Newly-allocated string representing full path to Session
 *          Inits session file.
 **/
char *
get_session_file (const char *xdg_runtime_dir, pid_t pid)
{
	char *session_file;
	
	nih_assert (xdg_runtime_dir);
	nih_assert (pid);

	session_file = nih_sprintf (NULL, "%s/upstart/sessions/%d.session",
			xdg_runtime_dir, (int)pid);

	nih_assert (session_file);

	return session_file;
}

/**
 * in_chroot:
 *
 * Determine if running inside a chroot environment.
 *
 * Failures are fatal.
 *
 * Returns TRUE if within a chroot, else FALSE.
 **/
int
in_chroot (void)
{
	struct stat st;
	int i;
	char dir[] = "/";

	i = stat(dir, &st);
	    
	if ( i != 0 ) { 
		fprintf (stderr, "ERROR: cannot stat '%s'\n", dir);
		exit (EXIT_FAILURE);
	}

	if ( st.st_ino == 2 )
		return FALSE;

	return TRUE;
}

/**
 * dbus_configured
 *
 * Determine if D-Bus has been configured (with dbus-uuidgen).
 *
 * Returns TRUE if D-Bus appears to have been configured,
 * else FALSE.
 **/
int
dbus_configured (void)
{
	struct stat st;
	char path[] = "/var/lib/dbus/machine-id";

	return !stat (path, &st);
}

/**
 * search_and_replace:
 *
 * @parent: parent for returned string,
 * @str: string to operate on,
 * @from: string to look for,
 * @to: string to replace @from with.
 *
 * Replace all occurences of @from in @str with @to.
 *
 * Returns: Newly-allocated string, or NULL on error or
 * if @str does not contain any occurences of @from.
 **/
char *
search_and_replace (void        *parent,
		    const char  *str,
		    const char  *from,
		    const char  *to)
{
	const char *start;
	const char *match;
	char       *new = NULL;
	size_t      len;

	nih_assert (str);
	nih_assert (from);
	nih_assert (to);

	start = str;
	len = strlen (from);

	while (start && *start) {
		match = strstr (start, from);

		if (! match) {
			/* No more matches, so copy the remainder of the original string */
			if (! nih_strcat (&new, parent, start))
				return NULL;
			break;
		}

		/* Copy data from start of segment to the match */
		if (! nih_strncat (&new, parent , start, match - start))
			return NULL;

		/* Replace the string */
		if (! nih_strcat (&new, parent, to))
			return NULL;

		/* Make start move to 1 byte beyond the end of the match */
		start = match + len;
	}

	return new;
}

/**
 * file_exists:
 * @path: file to check.
 *
 * Determine if specified file exists.
 *
 * Returns: TRUE if @path exists, else FALSE.
 **/
int
file_exists (const char *path)
{
	struct stat  st;

	nih_assert (path);

	return ! stat (path, &st);
}

/**
 * test_common_setup:
 *
 * Perform test setup.
 *
 * Currently, only needed for those tests which require unique xdg
 * directories.
 *
 * If called, test must call test_common_cleanup() to cleanup.
 **/
void
test_common_setup (void)
{
	char  *xdg_config_home;
	char  *xdg_runtime_dir;

	/* Take care to avoid disrupting users environment by saving and
	 * restoring these variable (assuming the tests all pass...).
	 */

	xdg_config_home = getenv ("XDG_CONFIG_HOME");
	if (xdg_config_home) {
		nih_info ("Existing XDG_CONFIG_HOME found ('%s') - "
				"saving for later restore",
				xdg_config_home);

		saved_xdg_config_home = NIH_MUST (nih_strdup (NULL, xdg_config_home));
	}

	TEST_FILENAME (test_xdg_config_home);
	assert0 (mkdir (test_xdg_config_home, TEST_DIR_MODE));
	assert0 (setenv ("XDG_CONFIG_HOME", test_xdg_config_home, 1));

	nih_info ("Using test XDG_CONFIG_HOME='%s'", test_xdg_config_home);

	xdg_runtime_dir = getenv ("XDG_RUNTIME_DIR");
	if (xdg_runtime_dir) {
		nih_info ("Existing XDG_RUNTIME_DIR found ('%s') - "
				"saving for later restore",
				xdg_runtime_dir);

		saved_xdg_runtime_dir = NIH_MUST (nih_strdup (NULL, xdg_runtime_dir));
	}

	TEST_FILENAME (test_xdg_runtime_dir);
	assert0 (mkdir (test_xdg_runtime_dir, TEST_DIR_MODE));
	assert0 (setenv ("XDG_RUNTIME_DIR", test_xdg_runtime_dir, 1));

	nih_info ("Using test XDG_RUNTIME_DIR='%s'", test_xdg_runtime_dir);

	test_setup_called = TRUE;
}

/**
 * test_common_cleanup:
 *
 * Perform cleanup of test setup.
 *
 * Currently, only needed for those tests which require unique xdg
 * directories.
 *
 * If called, test must already have called test_common_setup().
 **/
void
test_common_cleanup (void)
{
	nih_local char  *path = NULL;
	char            *xdg_config_home;
	char            *xdg_runtime_dir;
	struct stat      statbuf;

	if (! test_setup_called) {
		nih_error ("BUG: Called %s without first calling %s",
				__func__, "test_common_setup()");
		abort ();
	}

	xdg_config_home = getenv ("XDG_CONFIG_HOME");
	xdg_runtime_dir = getenv ("XDG_RUNTIME_DIR");

	if (saved_xdg_config_home) {
		nih_assert (test_xdg_config_home[0]);
		TEST_EQ_STR (test_xdg_config_home, xdg_config_home);

		if (stat (test_xdg_config_home, &statbuf)) {
			nih_error ("A test has removed XDG_CONFIG_HOME '%s'", test_xdg_config_home);
			abort ();
		}

		if (! S_ISDIR (statbuf.st_mode)) {
			nih_error ("XDG_CONFIG_HOME '%s' no longer a directory", test_xdg_config_home);
			abort ();
		}

		assert0 (rmdir (test_xdg_config_home));

		assert0 (setenv ("XDG_CONFIG_HOME", saved_xdg_config_home, 1));
		nih_info ("Restoring XDG_RUNTIME_DIR='%s'", saved_xdg_config_home);
		nih_free (saved_xdg_config_home);
		saved_xdg_config_home = NULL;
	}

	if (saved_xdg_runtime_dir) {
		nih_assert (test_xdg_runtime_dir[0]);
		TEST_EQ_STR (test_xdg_runtime_dir, xdg_runtime_dir);

		if (stat (test_xdg_runtime_dir, &statbuf)) {
			nih_error ("A test has removed XDG_RUNTIME_DIR '%s'", test_xdg_runtime_dir);
			abort ();
		}

		if (! S_ISDIR (statbuf.st_mode)) {
			nih_error ("XDG_RUNTIME_DIR '%s' no longer a directory", test_xdg_runtime_dir);
			abort ();
		}

		path = NIH_MUST (nih_sprintf (NULL, "%s/upstart/sessions", xdg_runtime_dir));

		if (! stat (path, &statbuf)) {
			nih_local char *cmd = NULL;

			/* Clean up if tests forgot to */
			cmd = NIH_MUST (nih_sprintf (NULL, "rm -f %s/*.session 2>/dev/null", path));
			assert0 (system (cmd));

			/* Remove the directory tree the first Session Init created */
			assert0 (rmdir (path));
			path = NIH_MUST (nih_sprintf (NULL, "%s/upstart", xdg_runtime_dir));
			assert0 (rmdir (path));
		}

		assert0 (rmdir (test_xdg_runtime_dir));

		assert0 (setenv ("XDG_RUNTIME_DIR", saved_xdg_runtime_dir, 1));
		nih_info ("Restoring XDG_RUNTIME_DIR='%s'", saved_xdg_config_home);
		nih_free (saved_xdg_runtime_dir);
		saved_xdg_runtime_dir = NULL;

	}
}

/**
 * timer_cb:
 *
 * @data: unused,
 * @timer: timer.
 *
 * Exit main loop with an error value indicating that the expected main
 * loop events/actions were not performed within the expected time.
 **/
void
timer_cb (void *data, NihTimer *timer)
{
	nih_assert (timer);

	/* Return non-zero to denote failure */
	nih_main_loop_exit (42);
}

/**
 * fd_valid:
 * @fd: file descriptor.
 *
 * Return 1 if @fd is valid, else 0.
 **/
int
fd_valid (int fd)
{
	int flags = 0;

	if (fd < 0)
		return 0;

	errno = 0;
	flags = fcntl (fd, F_GETFL);

	if (flags < 0)
		return 0;

	/* redundant really */
	if (errno == EBADF)
		return 0;

	return 1;
}

/**
 * read_from_fd:
 *
 * @parent: parent,
 * @fd: open file descriptor.
 *
 * Read from the specified fd, close the fd and return the data.
 *
 * Returns: Newly-allocated NihIoBuffer representing data read from @fd.
 *
 **/
NihIoBuffer *
read_from_fd (void *parent, int fd)
{
	NihIoBuffer *buffer = NULL;
	ssize_t      len;

	assert (fd >= 0);

	buffer = nih_io_buffer_new (parent);
	nih_assert (buffer);

	while (TRUE) {

		nih_assert (! nih_io_buffer_resize (buffer, 1024));

		len = read (fd,
				buffer->buf + buffer->len,
				buffer->size - buffer->len);

		if (len < 0 && errno != EAGAIN && errno != EINTR) {
			break;
		} else if (! len) {
			break;
		} else if (len > 0) {
			buffer->len += len;
		}
	}

	close (fd);

	return buffer;
}

/**
 * test_list_handler_generic:
 *
 * Generic handler.
 *
 * Put a break point on this function in gdb to allow you to cast entry
 * as desired.
 **/
int
test_list_handler_generic (NihList *entry, void *data)
{
  nih_assert (entry);

  /* XXX: stop compiler optimising this function away */
  asm ("");

  return 1;
}


/**
 * test_list_foreach:
 * @list: list,
 * @len: optional output parameter that will contain length of list,
 * @handler: optional function called for each list entry,
 * @data: optional data to pass to handler along with list entry.
 *
 * Iterate over specified list.
 *
 * One of @len or @handler may be NULL.
 * If @handler is NULL, list length will still be returned in @len.
 * If @handler returns 1, @len will be set to the number of list entries
 * processed successfully up to that point.
 *
 * Returns 0 on success (and when both @len and @handler are NULL),
 * or -1 if handler returns an error.
 **/
int
test_list_foreach (const NihList *list, size_t *len,
	NihListHandler handler, void *data)
{
	int ret;

	nih_assert (list);

	if (len) *len = 0;

	if (!len && !handler) return 0;

	NIH_LIST_FOREACH (list, iter) {
		if (handler) {
			ret = handler (iter, data);
			if (ret == FALSE) return -1;
		}
		if (len) ++*len;
	}

	return 0;
}

/**
 * test_list_count:
 * @list: list.
 * 
 * Returns count of number of entries in @list.
 **/
size_t
test_list_count (const NihList *list)
{
	size_t len = 0;
	int ret;

	nih_assert (list);

	ret = test_list_foreach (list, &len, NULL, NULL);

	return (ret == -1 ? 0 : len);
}

NihList *
test_list_get_index (NihList *list, size_t count)
{
	size_t i = 0;

	nih_assert (list);

	NIH_LIST_FOREACH (list, iter) {
		if (i == count)
			return iter;
		i++;
	}

	return NULL;
}

/**
 * test_hash_foreach:
 *
 * @hash: hash,
 * @len: optional output parameter that will contain count of hash entries,
 * @handler: optional function called for each hash entry,
 * @data: optional data to pass to handler along with hash entry.
 *
 * Iterate over specified hash.
 *
 * One of @len or @handler may be NULL.
 * If @handler is NULL, count of hash entries will still be returned in @len.
 * If @handler returns 1, @len will be set to the number of hash entries
 * processed successfully up to that point.
 *
 * Returns 0 on success (and when both @len and @handler are NULL),
 * or -1 if handler returns an error.
 **/
int
test_hash_foreach (const NihHash *hash, size_t *len,
	NihListHandler handler, void *data)
{
	int ret;

	nih_assert (hash);

	if (len) *len = 0;

	if (!len && !handler) return 0;

	NIH_HASH_FOREACH (hash, iter) {
		if (handler) {
			ret = handler (iter, data);
			if (ret == FALSE) return -1;
		}
		if (len) ++*len;
	}

	return 0;
}

/**
 * test_hash_count:
 *
 * @hash: hash.
 * 
 * Returns count of number of entries in @hash.
 **/
size_t
test_hash_count (const NihHash *hash)
{
	size_t len = 0;
	int ret;

	nih_assert (hash);

	ret = test_hash_foreach (hash, &len, NULL, NULL);

	return (ret == -1 ? 0 : len);
}


/**
 * test_tree_foreach:
 *
 * @tree: tree,
 * @len: optional output parameter that will contain count of tree nodes,
 * @handler: optional function called for each tree node,
 * @data: optional data to pass to handler along with tree node.
 *
 * Iterate over specified tree.
 *
 * One of @len or @handler may be NULL.
 * If @handler is NULL and @len is non-NULL, count of tree nodes will
 * still be returned in @len.
 * If @handler returns 1, @len will be set to the number of tree nodes
 * processed successfully up to that point.
 *
 * Returns 0 on success (and when both @len and @handler are NULL),
 * or -1 if handler returns an error.
 **/
int
test_tree_foreach (NihTree *tree, size_t *len,
	NihTreeHandler handler, void *data)
{
	int ret;

	nih_assert (tree);

	if (len) *len = 0;

	if (!len && !handler) return 0;

	NIH_TREE_FOREACH_FULL (tree, iter, NULL, data) {
		if (handler) {
			ret = handler (iter, data);
			if (!ret) return -1;
		}
		if (len) ++*len;
	}

	return 0;
}

/**
 * test_tree_count:
 *
 * @tree: tree.
 * 
 * Returns count of number of entries in @tree.
 **/
size_t
test_tree_count (NihTree *tree)
{
	size_t len = 0;
	int ret;

	nih_assert (tree);

	ret = test_tree_foreach (tree, &len, NULL, NULL);

	return (ret == -1 ? 0 : len);
}

#ifdef ENABLE_CGROUPS

/*
 * connect_to_cgmanager:
 *
 * Returns -2 if cgmanager is not running, -1 on other error,
 * and 0 on success
 */
int
connect_to_cgmanager(void)
{
	DBusError dbus_error;
	static DBusConnection *connection;

	dbus_error_init(&dbus_error);

	connection = dbus_connection_open_private(CGMANAGER_DBUS_SOCK, &dbus_error);
	if (!connection) {
		nih_error("Failed opening dbus connection: %s: %s",
				dbus_error.name, dbus_error.message);
		dbus_error_free(&dbus_error);
		return -2;
	}
	if (nih_dbus_setup(connection, NULL) < 0) {
		NihError *nerr;
		nerr = nih_error_get();
		nih_error("Unable to open cgmanager connection at %s: %s", CGMANAGER_DBUS_SOCK,
			nerr->message);
		nih_free(nerr);
		dbus_error_free(&dbus_error);
		dbus_connection_unref(connection);
		return -1;
	}
	dbus_connection_set_exit_on_disconnect(connection, FALSE);
	dbus_error_free(&dbus_error);
	cgroup_manager = nih_dbus_proxy_new(NULL, connection,
				NULL /* p2p */,
				"/org/linuxcontainers/cgmanager", NULL, NULL);
	dbus_connection_unref(connection);
	if (!cgroup_manager) {
		NihError *nerr;
		nerr = nih_error_get();
		nih_error("Error opening cgmanager proxy: %s", nerr->message);
		nih_free(nerr);
		return -1;
	}

	if (cgmanager_ping_sync(NULL, cgroup_manager, 0) != 0) {
		NihError *nerr;
		nerr = nih_error_get();
		nih_error("Error pinging cgroup manager: %s", nerr->message);
		nih_free(nerr);
		disconnect_cgmanager();
		return -1;
	}
	return 0;
}

void
disconnect_cgmanager(void)
{
       if (cgroup_manager) {
	       dbus_connection_flush(cgroup_manager->connection);
	       dbus_connection_close(cgroup_manager->connection);
               nih_free(cgroup_manager);
       }
       cgroup_manager = NULL;
}

/*
 * get_pid_cgroup:
 *
 * @controller: cgroup controller to query
 * @pid: pid whose cgroup to return
 *
 * The result must be nih_freed
 */
char *
get_pid_cgroup(const char *controller, pid_t pid)
{
	char *str;
	if (cgmanager_get_pid_cgroup_sync(NULL, cgroup_manager,
				controller, pid, &str) != 0) {
		
		NihError *nerr;
		nerr = nih_error_get();
		nih_error("call to cgmanager_set_value_sync failed: %s", nerr->message);
		nih_free(nerr);
		return NULL;
	}
	return str;
}

/*
 * setup_cgroup_sandbox:
 *
 * Creates a unique cgroup, sets it to remove on empty, and enters the
 * current task into the new cgroup.
 */
int
setup_cgroup_sandbox(void)
{
	char tmpnam[32], line[1024], *cg;
	int32_t e;
	int ret = -1, fd = -1;
	FILE *cgf = NULL;
	pid_t mypid = getpid();

	if (!cgroup_manager) {
		nih_error("%s: connect_to_cgmanager must be called first",
				__func__);
		goto out;
	}
	memset(tmpnam, 0, 32);
	strcpy(tmpnam, "/tmp/upstart-test-XXXXXX");
	if ((fd = mkstemp(tmpnam)) < 0) {
		nih_error("%s: failed to create a tempfile", __func__);
		goto out;
	}
	unlink(tmpnam);
	cg = tmpnam+5;

	if ((cgf = fopen("/proc/cgroups", "r")) == NULL) {
		nih_error("%s: failed to read my cgroups", __func__);
		goto out;
	}
	while (fgets(line, 1024, cgf)) {
		char *p;
		if (line[0] == '#')
			continue;

		p = strchr(line, '\t');
		if (!p) {
			nih_error("failed to find a \t");
			continue;
		}
		*p = '\0';
		if (cgmanager_create_sync(NULL, cgroup_manager, line, cg,
					&e) != 0) {
			NihError *nerr;
			nerr = nih_error_get();
			nih_error("%s: failed to create cgroup %s:%s: %s",
				__func__, line, cg, nerr->message);
			nih_free(nerr);
			goto out;
		}
		if (e == 1)
			nih_warn("%s: boggle: cgroup %s:%s already existed",
					__func__, line, cg);
		if (cgmanager_remove_on_empty_sync(NULL, cgroup_manager, line,
					cg) != 0) {
			NihError *nerr;
			nerr = nih_error_get();
			nih_warn("%s: failed to mark %s:%s remove-on-empty: %s",
				__func__, line, cg, nerr->message);
			nih_free(nerr);
		}
		if (cgmanager_move_pid_sync(NULL, cgroup_manager, line, cg,
					mypid) != 0) {
			NihError *nerr;
			nerr = nih_error_get();
			nih_error("%s: failed to move myself to cgroup %s:%s: %s",
				__func__, line, cg, nerr->message);
			nih_free(nerr);
			goto out;
		}
	}
	ret = 0;

out:
	if (fd != -1)
		close(fd);
	if (cgf)
		fclose(cgf);
	return ret;
}
#endif /* ENABLE_CGROUPS */
