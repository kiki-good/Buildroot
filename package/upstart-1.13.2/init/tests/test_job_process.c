/* upstart
 *
 * test_job_process.c - test suite for init/job_process.c
 *
 * Copyright © 2011-2014 Canonical Ltd.
 * Author: Scott James Remnant <scott@netsplit.com>.
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

#include <nih/test.h>

#if HAVE_VALGRIND_VALGRIND_H
#include <valgrind/valgrind.h>
#endif /* HAVE_VALGRIND_VALGRIND_H */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ptrace.h>

#include <time.h>
#include <stdio.h>
#include <pty.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utmp.h>
#include <utmpx.h>
#include <dirent.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pwd.h>
#include <grp.h>
#include <fnmatch.h>

#include <nih/macros.h>
#include <nih/string.h>
#include <nih/list.h>
#include <nih/io.h>
#include <nih/main.h>
#include <nih/error.h>
#include <nih/logging.h>

#include "job_process.h"
#include "job.h"
#include "event.h"
#include "blocked.h"
#include "conf.h"
#include "errors.h"
#include "test_util_common.h"

#define EXPECTED_JOB_LOGDIR       "/var/log/upstart"
#define TEST_SHELL                "/bin/sh"
#define TEST_SHELL_ARG            "-e"

/* Used to generate single- and multi-line output. */
#define TEST_CMD_ECHO             "/bin/echo"

/* Used to generate multi-line output out stdout without using shell
 * meta-characters.
 */
#define TEST_CMD_YES              "/usr/bin/yes"

/* Used to generate multi-line output on stderr without using shell
 * meta-characters.
 */
#define TEST_CMD_DD               "/bin/dd"

/* number of iterations to perform to check file contents */
#define MAX_ITERATIONS            5

/**
 * SHELL_CHARS:
 *
 * This is the list of characters that, if encountered in a process, cause
 * it to always be run with a shell.
 **/
#define SHELL_CHARS "~`!$^&*()=|\\{}[];\"'<>?"

/**
 * CHECK_FILE_EQ:
 *
 * @_file: FILE to read from,
 * @_line: line to expect.
 *
 * Check that the next line in the file @_file is @_line, which should
 * include the terminating newline if one is expected.
 *
 * This differs from TEST_FILE_EQ() in that the test is performed
 * MAX_ITERATIONS times with a 1 second sleep between iterations.
 **/
#define CHECK_FILE_EQ(_file, _line, _select) \
	do { \
		int ok = FALSE; \
		char filebuf[1024]; \
		for (int i = 0; i < MAX_ITERATIONS; i++) { \
			TEST_NE_P (fgets (filebuf, sizeof (filebuf), _file), NULL); \
			if (! strcmp (filebuf, _line)) { \
				ok = TRUE; \
				break; \
			} \
			if (_select) { \
				TEST_WATCH_UPDATE_TIMEOUT_SECS (1); \
			} else { \
				sleep (1); \
			} \
			rewind (_file); \
		} \
		TEST_EQ (ok, TRUE); \
	} while (0)


/* 
 * Register regular child handler.
 * Register another handler to be called after the primary
 * Upstart handler to allow the test to exit the main loop
 * quickly on success.
 * Process the event queue each time through the main loop
 */

#define TEST_INSTALL_CHILD_HANDLERS()		                \
	NIH_MUST (nih_child_add_watch (NULL,			\
				       -1,			\
				       NIH_CHILD_ALL,		\
				       test_job_process_handler,\
				       NULL));			\
	NIH_MUST (nih_child_add_watch (NULL,			\
				       -1,			\
				       NIH_CHILD_ALL,		\
				       job_process_handler,	\
				       NULL));			\
	NIH_MUST (nih_main_loop_add_func (NULL, (NihMainLoopCb)event_poll, \
					  NULL))


#define TEST_CLEAR_CHILD_STATUS()				\
	do {							\
		TEST_EQ (waitid (P_ALL, 0, &siginfo, WEXITED | WNOWAIT), -1); \
		TEST_EQ (errno, ECHILD);			\
		errno = 0;					\
		child_exit_after = 1;				\
		for (int _i = 0; _i < PROCESS_LAST; _i++) {	\
			child_exit_status[_i] = -1;		\
		}						\
	} while (0)


/* Modified version of NIH's TEST_CHILD() that is resilient
 * to temporary errors.
 */
#define RESILIENT_TEST_CHILD(_pid) \
	do { \
		int _test_fds[2]; \
		fflush (stdout);	    \
		fflush (stderr);	    \
		assert0 (pipe (_test_fds)); \
		_pid = fork (); \
		if (_pid > 0) { \
			ssize_t ret; \
			char _test_buf[1]; \
			close (_test_fds[1]); \
			while (TRUE) { \
				ret = read (_test_fds[0], _test_buf, 1); \
				if (ret > 0) { \
					assert (ret == 1); \
					break; \
				} else if (ret < 0 && errno != EINTR) { \
					nih_assert_not_reached (); \
				} else { \
					nih_assert_not_reached (); \
				} \
			} \
			close (_test_fds[0]); \
		} else if (_pid == 0) { \
			close (_test_fds[0]); \
			assert (write (_test_fds[1], "\n", 1) == 1); \
			close (_test_fds[1]); \
		} \
	} while (0); \
	if (_pid == 0) \
		for (int _test_child = 0; _test_child < 2; _test_child++) \
			if (_test_child) { \
				abort (); \
			} else

/* Sadly we can't test everything that job_process_spawn() does simply because
 * a lot of it can only be done by root, or in the case of the console stuff,
 * kills whatever had /dev/console (usually X).
 *
 * This set of tests at least ensures some level of code coverage.
 */
enum child_tests {
	TEST_SIMPLE,
	TEST_PIDS,
	TEST_CONSOLE,
	TEST_PWD,
	TEST_ENVIRONMENT,
	TEST_OUTPUT,
	TEST_OUTPUT_WITH_STOP,
	TEST_FDS
};


pid_t pty_child_pid;

static char *argv0;

static int get_available_pty_count (void) __attribute__((unused));
static void close_all_files (void);

static int child_exit_status[PROCESS_LAST];
static int child_exit_after;

/**
 * test_job_process_handler:
 *
 * @data: existing NihList that this function will add entries to,
 * @pid: process that changed,
 * @event: event that occurred on the child,
 * @status: exit status, signal raised or ptrace event.
 *
 * Handler that just sets some globals and requests the main loop to
 * exit to allow the test that installs it to check the values passed to
 * this function as appropriate.
 **/
void
test_job_process_handler (void           *data,
			  pid_t           pid,
			  NihChildEvents  event,
			  int             status)
{
	if (event != NIH_CHILD_EXITED)
		return;
	child_exit_after--;
	child_exit_status[child_exit_after] = status;
	if (child_exit_after < 1)
		nih_main_loop_exit (0);
}


static void
child (enum child_tests  test,
       const char       *filename)
{
	FILE  *out;
	char   tmpname[PATH_MAX], path[PATH_MAX];
	int    i;
	int    ret = EXIT_SUCCESS;

	strcpy (tmpname, filename);
	strcat (tmpname, ".tmp");

	out = fopen (tmpname, "w");

	switch (test) {
	case TEST_SIMPLE:
		break;
	case TEST_PIDS:
		fprintf (out, "pid: %d\n", getpid ());
		fprintf (out, "ppid: %d\n", getppid ());
		fprintf (out, "pgrp: %d\n", getpgrp ());
		fprintf (out, "sid: %d\n", getsid (0));
		break;
	case TEST_CONSOLE:
		for (i = 0; i < 3; i++) {
			struct stat buf;

			fstat (i, &buf);
			fprintf (out, "%d: %d %d\n", i,
				 major (buf.st_rdev),
				 minor (buf.st_rdev));
		}
		break;
	case TEST_PWD:
		assert (getcwd (path, sizeof (path)));
		fprintf (out, "wd: %s\n", path);
		break;
	case TEST_ENVIRONMENT:
		/* guarantee output ordering */
		for (i = 0; environ[i]; i++);
		qsort (environ, i, sizeof (environ[0]), strcmp_compar);

		for (char **env = environ; *env; env++)
			fprintf (out, "%s\n", *env);
		break;
	case TEST_OUTPUT:
		/* Write to stdout and stderr.
		 *
		 * Of course, daemon's usually make a point of not writing to
		 * stdout/stderr...
		 */
		fprintf(stdout, "stdout\n");
		fprintf(stderr, "stderr\n");

		/* write out pid to the output file to make it easier
		 * for the caller to track us if we've already forked
		 */
		fprintf (out, "%d\n", getpid ());
		
		fflush (NULL);
		break;
	case TEST_OUTPUT_WITH_STOP:
		fprintf (stdout, "started\n");
		fflush (NULL);

		/* wait for signal */
		raise (SIGSTOP);

		fprintf(stdout, "ended\n");
		fflush (NULL);
		break;
	case TEST_FDS:
		/* Establish list of open (valid) and closed (invalid)
		 * file descriptors.
		 *
		 * XXX: Note that if you attempt to run this program
		 * through gdb, the TEST_FDS tests will probably fail.
		 * This seems to be due to gdb creating/leaking atleast 1 fd.
		 *
		 * To work around this issue, either comment out all
		 * TEST_FDS tests to allow you to debug the _actual_ failing
		 * test(s), or if it is one of the TEST_FDS tests which is
		 * failing either use an alternative technique to debug the
		 * failing test(s) (such as strace(1)), or force the TEST_FDS
		 * tests to pass in gdb by setting the appropriate flag
		 * variable to indicate the test(s) passed.
		 */
		{
			DIR           *dir;
			struct dirent *ent;
			struct stat    statbuf;
			char          *prefix_path = "/proc/self/fd";
			char           path[PATH_MAX];
			char           link[PATH_MAX];
			int            saved_errno;
			ssize_t        len;
			int            valid;

			dir = opendir(prefix_path);

			if (!dir)
			{
				saved_errno = errno;
				fprintf (out, "failed to open '%s'"
						" (errno=%d [%s])",
						prefix_path,
						saved_errno, strerror(saved_errno));

				ret = EXIT_FAILURE;
				goto out;
			}

			while ((ent=readdir(dir)) != NULL)
			{
				int fd;

				valid = 0;

				if ( !strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..") )
					continue;

				sprintf (path, "%s/%s", prefix_path, ent->d_name);
				fd = atoi (ent->d_name);

				len = readlink (path, link, sizeof (link));
				TEST_GT (len, 0);
				link[len] = '\0';

				if (fd == fileno (out)) {
					/* we (have to) pretend the log file that
					 * we write is invisible.
					 */
					valid = 0;
				} else if (link[0] == '/') {
					sprintf (path, "/proc/%d/fd", getpid ());

					if (stat (link, &statbuf) < 0)
						valid = 0;
					else if (S_ISDIR (statbuf.st_mode) && ! strcmp (path, link)) {
						/* Ignore the last entry which is a link to the
						 * /proc/self/fd/ directory.
						 */
						valid = 0;
					} else {
						valid = 1;
					}
				} else {
					valid = fd_valid (fd);
				}

				fprintf (out, "fd %d: %svalid (link=%s)\n",
						fd,
						valid ? "" : "in",
						link);
			}

			closedir(dir);
		}
		break;
	}

out:
	fsync (fileno (out));
	fclose (out);

	rename (tmpname, filename);

	exit (ret);
}

/* FIXME:
 *
 * This is not currently reliable due to a kernel bug that does
 * not bound 'nr' to the range:
 *
 *	0 <= nr <= 'max'
 */

/**
 * get_available_pty_count:
 *
 * Return count of available ptys.
 *
 **/
static int
get_available_pty_count (void)
{
	FILE *f;
	int nr, max;
	int ret;

	f = fopen ("/proc/sys/kernel/pty/max", "r");
	TEST_NE_P (f, NULL);

	ret = fscanf (f, "%d", &max);
	TEST_EQ (ret, 1);
	TEST_GT (max, 0);

	fclose (f);

	f = fopen ("/proc/sys/kernel/pty/nr", "r");
	TEST_NE_P (f, NULL);

	ret = fscanf (f, "%d", &nr);
	TEST_EQ (ret, 1);
	TEST_GE (nr, 0);

	fclose (f);

	return max - nr;
}

/* Helper function to close all fds above 2, in case any have been leaked
 * to us from the environment (and thence to the child process)
 */
static void
close_all_files (void)
{
	unsigned long i;
	struct rlimit rlim;

	if (getrlimit(RLIMIT_NOFILE, &rlim) < 0)
		return;

	for (i = 3; i < rlim.rlim_cur; i++)
		close(i);
}

/* XXX: Note that none of these tests attempts to test with a Session
 * passed to job_class_new() since to do so would modify the home
 * directory of the user running these tests (BAD!!).
 *
 * (Such tests are handled in the bundled test_user_sessions.sh script).
 */
void
test_start (void)
{
	char             dirname[PATH_MAX];
	JobClass        *class = NULL;
	Job             *job = NULL;
	FILE            *output;
	struct stat      statbuf;
	char             filename[PATH_MAX], buf[80];
	char             function[PATH_MAX];
	int              status;
	siginfo_t        info;
	char             filebuf[1024];
	struct passwd   *pwd;
	struct group    *grp;
	char            *p;
	int              ok;
	char             buffer[1024];
	pid_t            pid;
	int              i;
	siginfo_t        siginfo;

	log_unflushed_init ();
	job_class_init ();

	TEST_FUNCTION ("job_process_start");

	TEST_FILENAME (filename);
	program_name = "test";

	TEST_FILENAME (dirname);       
	TEST_EQ (mkdir (dirname, 0755), 0);

	/* Override default location to ensure job output goes to a
	 * writeable location
	 */
	TEST_EQ (setenv ("UPSTART_LOGDIR", dirname, 1), 0);

	/* Check that we can run a simple command, and have the process id
	 * and state filled in.  We should be able to wait for the pid to
	 * finish and see that it has been run as expected.
	 */
	TEST_FEATURE ("with simple command");
	TEST_HASH_EMPTY (job_classes);

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			class = job_class_new (NULL, "test", NULL);
			class->console = CONSOLE_NONE;
			class->process[PROCESS_MAIN] = process_new (class);
			class->process[PROCESS_MAIN]->command = nih_sprintf (
				class->process[PROCESS_MAIN],
				"touch %s", filename);

			job = job_new (class, "");
			job->goal = JOB_START;
			job->state = JOB_SPAWNED;
		}

		job_process_start (job, PROCESS_MAIN);

		TEST_NE (job->pid[PROCESS_MAIN], 0);

		waitpid (job->pid[PROCESS_MAIN], NULL, 0);
		TEST_EQ (stat (filename, &statbuf), 0);

		unlink (filename);
		nih_free (class);
	}


	/* Check that we can run a command that requires a shell to be
	 * intepreted correctly, a shell should automatically be used to
	 * make this work.  Check the contents of a file we'll create to
	 * check that a shell really was used.
	 */
	TEST_FEATURE ("with shell command");
	TEST_HASH_EMPTY (job_classes);

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			class = job_class_new (NULL, "test", NULL);
			class->console = CONSOLE_NONE;
			class->process[PROCESS_MAIN] = process_new (class);
			class->process[PROCESS_MAIN]->command = nih_sprintf (
				class->process[PROCESS_MAIN],
				"echo $$ > %s\n", filename);

			job = job_new (class, "");
			job->goal = JOB_START;
			job->state = JOB_SPAWNED;
		}

		job_process_start (job, PROCESS_MAIN);

		TEST_NE (job->pid[PROCESS_MAIN], 0);

		waitpid (job->pid[PROCESS_MAIN], NULL, 0);
		TEST_EQ (stat (filename, &statbuf), 0);
		TEST_EQ (job->class->process[PROCESS_MAIN]->script, FALSE);

		/* Filename should contain the pid */
		output = fopen (filename, "r");
		sprintf (buf, "%d\n", job->pid[PROCESS_MAIN]);
		TEST_FILE_EQ (output, buf);
		TEST_FILE_END (output);
		fclose (output);
		unlink (filename);

		nih_free (class);
	}

	/* Check that we can run a small shell script, and that it's run
	 * by using the shell directly and passing the script in on the
	 * command-line.
	 */
	TEST_FEATURE ("with small script");
	TEST_HASH_EMPTY (job_classes);

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			class = job_class_new (NULL, "test", NULL);
			class->console = CONSOLE_NONE;
			class->process[PROCESS_MAIN] = process_new (class);
			class->process[PROCESS_MAIN]->script = TRUE;
			class->process[PROCESS_MAIN]->command = nih_sprintf (
				class->process[PROCESS_MAIN],
				"echo $0 $@ > %s\n", filename);

			job = job_new (class, "");
			job->goal = JOB_START;
			job->state = JOB_SPAWNED;
		}

		job_process_start (job, PROCESS_MAIN);

		TEST_NE (job->pid[PROCESS_MAIN], 0);

		waitpid (job->pid[PROCESS_MAIN], &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		output = fopen (filename, "r");
		TEST_FILE_EQ (output, "/bin/sh\n");
		TEST_FILE_END (output);
		fclose (output);
		unlink (filename);

		nih_free (class);
	}


	/* Check that we can run a small shell script that has many newlines
	 * to be stripped from the end before passing it on the command-line.
	 */
	TEST_FEATURE ("with small script and trailing newlines");
	TEST_HASH_EMPTY (job_classes);

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			class = job_class_new (NULL, "test", NULL);
			class->console = CONSOLE_NONE;
			class->process[PROCESS_MAIN] = process_new (class);
			class->process[PROCESS_MAIN]->script = TRUE;
			class->process[PROCESS_MAIN]->command = nih_sprintf (
				class->process[PROCESS_MAIN],
				"echo $0 $@ > %s\n\n\n", filename);

			job = job_new (class, "");
			job->goal = JOB_START;
			job->state = JOB_SPAWNED;
		}

		job_process_start (job, PROCESS_MAIN);

		TEST_NE (job->pid[PROCESS_MAIN], 0);

		waitpid (job->pid[PROCESS_MAIN], &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		output = fopen (filename, "r");
		TEST_FILE_EQ (output, "/bin/sh\n");
		TEST_FILE_END (output);
		fclose (output);
		unlink (filename);

		nih_free (class);
	}


	/* Check that shell scripts are run with the -e option set, so that
	 * any failing command causes the entire script to fail.
	 */
	TEST_FEATURE ("with script that will fail");
	TEST_HASH_EMPTY (job_classes);

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			class = job_class_new (NULL, "test", NULL);
			class->console = CONSOLE_NONE;
			class->process[PROCESS_MAIN] = process_new (class);
			class->process[PROCESS_MAIN]->script = TRUE;
			class->process[PROCESS_MAIN]->command = nih_sprintf (
				class->process[PROCESS_MAIN],
				"test -d %s > %s\n",
				filename, filename);

			job = job_new (class, "");
			job->goal = JOB_START;
			job->state = JOB_SPAWNED;
		}

		job_process_start (job, PROCESS_MAIN);

		TEST_NE (job->pid[PROCESS_MAIN], 0);

		waitpid (job->pid[PROCESS_MAIN], &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 1);

		output = fopen (filename, "r");
		TEST_FILE_END (output);
		fclose (output);
		unlink (filename);

		nih_free (class);
	}


	/* Check that a job is run with the environment from its env member,
	 * with the job name appended to it.
	 */
	TEST_FEATURE ("with environment of unnamed instance");
	TEST_HASH_EMPTY (job_classes);

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			class = job_class_new (NULL, "test", NULL);
			class->console = CONSOLE_NONE;
			class->process[PROCESS_MAIN] = process_new (class);
			class->process[PROCESS_MAIN]->script = FALSE;
			class->process[PROCESS_MAIN]->command = nih_sprintf (
				class->process[PROCESS_MAIN],
				"%s %d %s", argv0, TEST_ENVIRONMENT, filename);

			job = job_new (class, "");
			job->goal = JOB_START;
			job->state = JOB_SPAWNED;

			assert (nih_str_array_add (&job->env, job, NULL, "FOO=BAR"));
			assert (nih_str_array_add (&job->env, job, NULL, "BAR=BAZ"));

			assert (nih_str_array_add (&job->stop_env, job, NULL,
						   "FOO=SMACK"));
			assert (nih_str_array_add (&job->stop_env, job, NULL,
						   "CRACKLE=FIZZ"));
		}

		job_process_start (job, PROCESS_MAIN);

		TEST_NE (job->pid[PROCESS_MAIN], 0);

		waitpid (job->pid[PROCESS_MAIN], NULL, 0);
		TEST_EQ (stat (filename, &statbuf), 0);

		/* Read back the environment to make sure it matched that from
		 * the job.
		 */
		output = fopen (filename, "r");
		TEST_FILE_EQ (output, "BAR=BAZ\n");
		TEST_FILE_EQ (output, "FOO=BAR\n");
		if (job->class->process[PROCESS_MAIN]->script || strpbrk (job->class->process[PROCESS_MAIN]->command, SHELL_CHARS))
			TEST_FILE_EQ (output, "PWD=/\n");
		TEST_FILE_EQ (output, "UPSTART_INSTANCE=\n");
		TEST_FILE_EQ (output, "UPSTART_JOB=test\n");
		TEST_FILE_EQ (output, "UPSTART_NO_SESSIONS=1\n");
		TEST_FILE_END (output);
		fclose (output);
		unlink (filename);

		nih_free (class);
	}


	/* Check that a job is run with the environment from its env member,
	 * with the job name and instance name appended to it.
	 */
	TEST_FEATURE ("with environment of named instance");
	TEST_HASH_EMPTY (job_classes);

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			class = job_class_new (NULL, "test", NULL);
			class->console = CONSOLE_NONE;
			class->process[PROCESS_MAIN] = process_new (class);
			class->process[PROCESS_MAIN]->script = FALSE;
			class->process[PROCESS_MAIN]->command = nih_sprintf (
				class->process[PROCESS_MAIN],
				"%s %d %s", argv0, TEST_ENVIRONMENT, filename);

			job = job_new (class, "foo");
			job->goal = JOB_START;
			job->state = JOB_SPAWNED;

			assert (nih_str_array_add (&job->env, job, NULL, "FOO=BAR"));
			assert (nih_str_array_add (&job->env, job, NULL, "BAR=BAZ"));

			assert (nih_str_array_add (&job->stop_env, job, NULL,
						   "FOO=SMACK"));
			assert (nih_str_array_add (&job->stop_env, job, NULL,
						   "CRACKLE=FIZZ"));
		}

		job_process_start (job, PROCESS_MAIN);

		TEST_NE (job->pid[PROCESS_MAIN], 0);

		waitpid (job->pid[PROCESS_MAIN], NULL, 0);
		TEST_EQ (stat (filename, &statbuf), 0);

		/* Read back the environment to make sure it matched that from
		 * the job.
		 */
		output = fopen (filename, "r");
		TEST_FILE_EQ (output, "BAR=BAZ\n");
		TEST_FILE_EQ (output, "FOO=BAR\n");
		if (job->class->process[PROCESS_MAIN]->script || strpbrk (job->class->process[PROCESS_MAIN]->command, SHELL_CHARS))
			TEST_FILE_EQ (output, "PWD=/\n");
		TEST_FILE_EQ (output, "UPSTART_INSTANCE=foo\n");
		TEST_FILE_EQ (output, "UPSTART_JOB=test\n");
		TEST_FILE_EQ (output, "UPSTART_NO_SESSIONS=1\n");
		TEST_FILE_END (output);
		fclose (output);
		unlink (filename);

		nih_free (class);
	}


	/* Check that the pre-stop job is run with the environment from the
	 * stop_env member as well as from the env member, overriding where
	 * necessary, and the job name and id appended.
	 */
	TEST_FEATURE ("with environment for pre-stop");
	TEST_HASH_EMPTY (job_classes);

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			class = job_class_new (NULL, "test", NULL);
			class->console = CONSOLE_NONE;
			class->process[PROCESS_PRE_STOP] = process_new (class);
			class->process[PROCESS_PRE_STOP]->script = FALSE;
			class->process[PROCESS_PRE_STOP]->command = nih_sprintf (
				class->process[PROCESS_PRE_STOP],
				"%s %d %s", argv0, TEST_ENVIRONMENT, filename);

			job = job_new (class, "");
			job->goal = JOB_STOP;
			job->state = JOB_PRE_STOP;

			assert (nih_str_array_add (&job->env, job, NULL, "FOO=BAR"));
			assert (nih_str_array_add (&job->env, job, NULL, "BAR=BAZ"));

			assert (nih_str_array_add (&job->stop_env, job, NULL,
						   "FOO=SMACK"));
			assert (nih_str_array_add (&job->stop_env, job, NULL,
						   "CRACKLE=FIZZ"));
		}

		job_process_start (job, PROCESS_PRE_STOP);

		TEST_NE (job->pid[PROCESS_PRE_STOP], 0);

		waitpid (job->pid[PROCESS_PRE_STOP], NULL, 0);
		TEST_EQ (stat (filename, &statbuf), 0);

		/* Read back the environment to make sure it matched that from
		 * the job.
		 */
		output = fopen (filename, "r");
		TEST_FILE_EQ (output, "BAR=BAZ\n");
		TEST_FILE_EQ (output, "CRACKLE=FIZZ\n");
		TEST_FILE_EQ (output, "FOO=SMACK\n");
		if (job->class->process[PROCESS_PRE_STOP]->script || strpbrk (job->class->process[PROCESS_PRE_STOP]->command, SHELL_CHARS))
			TEST_FILE_EQ (output, "PWD=/\n");
		TEST_FILE_EQ (output, "UPSTART_INSTANCE=\n");
		TEST_FILE_EQ (output, "UPSTART_JOB=test\n");
		TEST_FILE_EQ (output, "UPSTART_NO_SESSIONS=1\n");
		TEST_FILE_END (output);
		fclose (output);
		unlink (filename);

		nih_free (class);
	}


	/* Check that the post-stop job is run with the environment from the
	 * stop_env member as well as from the env member, overriding where
	 * necessary, and the job name and id appended.
	 */
	TEST_FEATURE ("with environment for post-stop");
	TEST_HASH_EMPTY (job_classes);

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			class = job_class_new (NULL, "test", NULL);
			class->console = CONSOLE_NONE;
			class->process[PROCESS_POST_STOP] = process_new (class);
			class->process[PROCESS_POST_STOP]->script = FALSE;
			class->process[PROCESS_POST_STOP]->command = nih_sprintf (
				class->process[PROCESS_POST_STOP],
				"%s %d %s", argv0, TEST_ENVIRONMENT, filename);

			job = job_new (class, "");
			job->goal = JOB_STOP;
			job->state = JOB_POST_STOP;

			assert (nih_str_array_add (&job->env, job, NULL, "FOO=BAR"));
			assert (nih_str_array_add (&job->env, job, NULL, "BAR=BAZ"));

			assert (nih_str_array_add (&job->stop_env, job, NULL,
						   "FOO=SMACK"));
			assert (nih_str_array_add (&job->stop_env, job, NULL,
						   "CRACKLE=FIZZ"));
		}

		job_process_start (job, PROCESS_POST_STOP);

		TEST_NE (job->pid[PROCESS_POST_STOP], 0);

		waitpid (job->pid[PROCESS_POST_STOP], NULL, 0);
		TEST_EQ (stat (filename, &statbuf), 0);

		/* Read back the environment to make sure it matched that from
		 * the job.
		 */
		output = fopen (filename, "r");
		TEST_FILE_EQ (output, "BAR=BAZ\n");
		TEST_FILE_EQ (output, "CRACKLE=FIZZ\n");
		TEST_FILE_EQ (output, "FOO=SMACK\n");
		if (job->class->process[PROCESS_POST_STOP]->script || strpbrk (job->class->process[PROCESS_POST_STOP]->command, SHELL_CHARS))
			TEST_FILE_EQ (output, "PWD=/\n");
		TEST_FILE_EQ (output, "UPSTART_INSTANCE=\n");
		TEST_FILE_EQ (output, "UPSTART_JOB=test\n");
		TEST_FILE_EQ (output, "UPSTART_NO_SESSIONS=1\n");
		TEST_FILE_END (output);
		fclose (output);
		unlink (filename);

		nih_free (class);
	}


	/* Check that a particularly long script is instead invoked by
	 * using the /proc/self/fd feature, with the shell script fed to the
	 * child process by an NihIo structure.
	 */
	TEST_FEATURE ("with long script");
	TEST_HASH_EMPTY (job_classes);

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			class = job_class_new (NULL, "test", NULL);
			class->console = CONSOLE_NONE;
			class->process[PROCESS_MAIN] = process_new (class);
			class->process[PROCESS_MAIN]->script = TRUE;
			class->process[PROCESS_MAIN]->command = nih_alloc (
				class->process[PROCESS_MAIN], 4096);
			sprintf (class->process[PROCESS_MAIN]->command,
				 "exec > %s\necho $0\necho $@\n", filename);

			job = job_new (class, "");
			job->goal = JOB_START;
			job->state = JOB_SPAWNED;
		}

		job_process_start (job, PROCESS_MAIN);

		TEST_NE (job->pid[PROCESS_MAIN], 0);

		TEST_WATCH_LOOP ();

		waitpid (job->pid[PROCESS_MAIN], &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		output = fopen (filename, "r");
		TEST_FILE_EQ_N (output, "/proc/self/fd/");
		TEST_FILE_EQ (output, "\n");
		TEST_FILE_END (output);
		fclose (output);
		unlink (filename);

		nih_free (class);
	}


	/* Check that if we're running a non-daemon job, the trace state
	 * is reset and no process trace is established.
	 */
	TEST_FEATURE ("with non-daemon job");
	TEST_HASH_EMPTY (job_classes);

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			class = job_class_new (NULL, "test", NULL);
			class->console = CONSOLE_NONE;
			class->process[PROCESS_MAIN] = process_new (class);
			class->process[PROCESS_MAIN]->script = FALSE;
			class->process[PROCESS_MAIN]->command = "true";

			job = job_new (class, "");
			job->goal = JOB_START;
			job->state = JOB_SPAWNED;

			job->trace_forks = 2;
			job->trace_state = TRACE_NORMAL;
		}

		job_process_start (job, PROCESS_MAIN);

		TEST_EQ (job->trace_forks, 0);
		TEST_EQ (job->trace_state, TRACE_NONE);

		TEST_NE (job->pid[PROCESS_MAIN], 0);

		assert0 (waitid (P_PID, job->pid[PROCESS_MAIN], &info,
				 WEXITED | WSTOPPED));
		TEST_EQ (info.si_pid, job->pid[PROCESS_MAIN]);
		TEST_EQ (info.si_code, CLD_EXITED);
		TEST_EQ (info.si_status, 0);

		nih_free (class);
	}


	/* Check that if we're running a script for a daemon job, the
	 * trace state is reset and no process trace is established.
	 */
	TEST_FEATURE ("with script for daemon job");
	TEST_HASH_EMPTY (job_classes);

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			class = job_class_new (NULL, "test", NULL);
			class->console = CONSOLE_NONE;
			class->process[PROCESS_PRE_START] = process_new (class);
			class->process[PROCESS_PRE_START]->script = FALSE;
			class->process[PROCESS_PRE_START]->command = "true";

			job = job_new (class, "");
			job->goal = JOB_START;
			job->state = JOB_PRE_START;

			job->trace_forks = 2;
			job->trace_state = TRACE_NORMAL;
		}

		job_process_start (job, PROCESS_PRE_START);

		TEST_EQ (job->trace_forks, 0);
		TEST_EQ (job->trace_state, TRACE_NONE);

		TEST_NE (job->pid[PROCESS_PRE_START], 0);

		assert0 (waitid (P_PID, job->pid[PROCESS_PRE_START], &info,
				 WEXITED | WSTOPPED));
		TEST_EQ (info.si_pid, job->pid[PROCESS_PRE_START]);
		TEST_EQ (info.si_code, CLD_EXITED);
		TEST_EQ (info.si_status, 0);

		nih_free (class);
	}


	/* Check that if we're running a daemon job, the trace state
	 * is reset and a process trace is established so that we can
	 * follow the forks.
	 */
	TEST_FEATURE ("with daemon job");
	TEST_HASH_EMPTY (job_classes);

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			class = job_class_new (NULL, "test", NULL);
			class->console = CONSOLE_NONE;
			class->expect = EXPECT_DAEMON;
			class->process[PROCESS_MAIN] = process_new (class);
			class->process[PROCESS_MAIN]->script = FALSE;
			class->process[PROCESS_MAIN]->command = "true";

			job = job_new (class, "");
			job->goal = JOB_START;
			job->state = JOB_SPAWNED;

			job->trace_forks = 2;
			job->trace_state = TRACE_NORMAL;
		}

		job_process_start (job, PROCESS_MAIN);

		TEST_EQ (job->trace_forks, 0);
		TEST_EQ (job->trace_state, TRACE_NEW);

		TEST_NE (job->pid[PROCESS_MAIN], 0);

		assert0 (waitid (P_PID, job->pid[PROCESS_MAIN], &info,
				 WEXITED | WSTOPPED));
		TEST_EQ (info.si_pid, job->pid[PROCESS_MAIN]);
		TEST_EQ (info.si_code, CLD_TRAPPED);
		TEST_EQ (info.si_status, SIGTRAP);

		assert0 (ptrace (PTRACE_DETACH, job->pid[PROCESS_MAIN],
				 NULL, 0));

		assert0 (waitid (P_PID, job->pid[PROCESS_MAIN], &info,
				 WEXITED | WSTOPPED));
		TEST_EQ (info.si_pid, job->pid[PROCESS_MAIN]);
		TEST_EQ (info.si_code, CLD_EXITED);
		TEST_EQ (info.si_status, 0);

		nih_free (class);
	}


	/* Check that if we're running a forking job, the trace state
	 * is reset and a process trace is established so that we can
	 * follow the fork.
	 */
	TEST_FEATURE ("with forking job");
	TEST_HASH_EMPTY (job_classes);

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			class = job_class_new (NULL, "test", NULL);
			class->console = CONSOLE_NONE;
			class->expect = EXPECT_FORK;
			class->process[PROCESS_MAIN] = process_new (class);
			class->process[PROCESS_MAIN]->script = FALSE;
			class->process[PROCESS_MAIN]->command = "true";

			job = job_new (class, "");
			job->goal = JOB_START;
			job->state = JOB_SPAWNED;

			job->trace_forks = 2;
			job->trace_state = TRACE_NORMAL;
		}

		job_process_start (job, PROCESS_MAIN);

		TEST_EQ (job->trace_forks, 0);
		TEST_EQ (job->trace_state, TRACE_NEW);

		TEST_NE (job->pid[PROCESS_MAIN], 0);

		assert0 (waitid (P_PID, job->pid[PROCESS_MAIN], &info,
				 WEXITED | WSTOPPED));
		TEST_EQ (info.si_pid, job->pid[PROCESS_MAIN]);
		TEST_EQ (info.si_code, CLD_TRAPPED);
		TEST_EQ (info.si_status, SIGTRAP);

		assert0 (ptrace (PTRACE_DETACH, job->pid[PROCESS_MAIN],
				 NULL, 0));

		assert0 (waitid (P_PID, job->pid[PROCESS_MAIN], &info,
				 WEXITED | WSTOPPED));
		TEST_EQ (info.si_pid, job->pid[PROCESS_MAIN]);
		TEST_EQ (info.si_code, CLD_EXITED);
		TEST_EQ (info.si_status, 0);

		nih_free (class);
	}


	/* Check that if we try and run a command that doesn't exist,
	 * job_process_start() raises a ProcessError and the command doesn't
	 * have any stored process id for it.
	 */
	TEST_FEATURE ("with no such file");
	TEST_HASH_EMPTY (job_classes);

	TEST_RESET_MAIN_LOOP ();
	TEST_INSTALL_CHILD_HANDLERS ();

	output = tmpfile ();

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			TEST_HASH_EMPTY (job_classes);
			class = job_class_new (NULL, "test", NULL);
			class->console = CONSOLE_NONE;
			class->process[PROCESS_MAIN] = process_new (class);
			class->process[PROCESS_MAIN]->script = FALSE;
			class->process[PROCESS_MAIN]->command = filename;

			job = job_new (class, "foo");
			job->goal = JOB_START;
			job->state = JOB_SPAWNED;

			nih_hash_add (job_classes, &class->entry);
			TEST_CLEAR_CHILD_STATUS ();
		}

		TEST_DIVERT_STDERR (output) {
			job_process_start (job, PROCESS_MAIN);
			pid = job->pid[PROCESS_MAIN];
			TEST_GT (pid, 0);
			TEST_EQ (nih_main_loop (), 0);
			TEST_EQ (child_exit_status[PROCESS_MAIN], 255);
		}
		rewind (output);
		
		TEST_EQ (job->pid[PROCESS_MAIN], 0);
		TEST_GT (sprintf (buffer, "test: test (foo) main process (%i) terminated with status 255\n", pid), 0);

		TEST_GT (fgets (filebuf, sizeof (filebuf), output), 0);

		TEST_TRUE (strcmp (filebuf, ("test: Failed to spawn test (foo) main "
						"process: unable to execute: "
						"No such file or directory\n")) == 0
			   || strcmp (filebuf, buffer) == 0);
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		nih_free (class);
	}

	TEST_EQ (rmdir (dirname), 0);

	TEST_RESET_MAIN_LOOP ();

	TEST_FILENAME (dirname);       
	TEST_EQ (mkdir (dirname, 0755), 0);

	/* Override default location to ensure job output goes to a
	 * writeable location
	 */
	TEST_EQ (setenv ("UPSTART_LOGDIR", dirname, 1), 0);

	/************************************************************/
	TEST_FEATURE ("ensure sane fds with no console, no script");

	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "prism", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/prism.log", dirname), 0);

	sprintf (function, "%d", TEST_FDS);

	class->console = CONSOLE_NONE;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s %s %s",
			argv0, function, filename);
	class->process[PROCESS_MAIN]->script = FALSE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_EQ (stat (filename, &statbuf), 0);

	output = fopen (filename, "r");

	{
		char  state[32];
		int   fd;
		int   ret;
		int   valid;

		while (fgets (filebuf, sizeof(filebuf), output) != NULL) {
			ret = sscanf (filebuf, "fd %d: %s ", &fd, state);
			TEST_EQ (ret, 2);

			if (! strcmp ("invalid", state))
				valid = 0;
			else
				valid = 1;

			/* 0, 1, 2 */
			if (fd < 3) {
				if (! valid)
					TEST_FAILED ("fd %d is unexpectedly invalid", fd);
			} else {
				if (valid)
					TEST_FAILED ("fd %d is unexpectedly valid", fd);
			}
		}
	}

	fclose (output);
	TEST_EQ (unlink (filename), 0);

	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("ensure sane fds with no console, and script");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "prism", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/prism.log", dirname), 0);

	sprintf (function, "%d", TEST_FDS);

	class->console = CONSOLE_NONE;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s %s %s",
			argv0, function, filename);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_EQ (stat (filename, &statbuf), 0);

	output = fopen (filename, "r");

	{
		char  state[32];
		int   fd;
		int   ret;
		int   valid;

		while (fgets (filebuf, sizeof(filebuf), output) != NULL) {
			ret = sscanf (filebuf, "fd %d: %s ", &fd, state);
			TEST_EQ (ret, 2);

			if (! strcmp ("invalid", state))
				valid = 0;
			else
				valid = 1;

			/* 0, 1, 2 */
			if (fd < 3) {
				if (! valid)
					TEST_FAILED ("fd %d is unexpectedly invalid", fd);
			} else {
				if (valid)
					TEST_FAILED ("fd %d is unexpectedly valid", fd);
			}
		}
	}

	fclose (output);
	TEST_EQ (unlink (filename), 0);

	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("ensure sane fds with console log, no script");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "prism", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/prism.log", dirname), 0);

	sprintf (function, "%d", TEST_FDS);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s %s %s",
			argv0, function, filename);
	class->process[PROCESS_MAIN]->script = FALSE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_EQ (stat (filename, &statbuf), 0);

	output = fopen (filename, "r");

	{
		char  state[32];
		int   fd;
		int   ret;
		int   valid;

		while (fgets (filebuf, sizeof(filebuf), output) != NULL) {
			ret = sscanf (filebuf, "fd %d: %s ", &fd, state);
			TEST_EQ (ret, 2);

			if (! strcmp ("invalid", state))
				valid = 0;
			else
				valid = 1;

			/* 0, 1, 2 */
			if (fd < 3) {
				if (! valid)
					TEST_FAILED ("fd %d is unexpectedly invalid", fd);
			} else {
				if (valid)
					TEST_FAILED ("fd %d is unexpectedly valid", fd);
			}
		}
	}

	fclose (output);
	TEST_EQ (unlink (filename), 0);

	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("ensure sane fds with console log, and script");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "prism", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/prism.log", dirname), 0);

	sprintf (function, "%d", TEST_FDS);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s %s %s",
			argv0, function, filename);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_EQ (stat (filename, &statbuf), 0);

	output = fopen (filename, "r");

	{
		char  state[32];
		int   fd;
		int   ret;
		int   valid;

		while (fgets (filebuf, sizeof(filebuf), output) != NULL) {
			ret = sscanf (filebuf, "fd %d: %s ", &fd, state);
			TEST_EQ (ret, 2);

			if (! strcmp ("invalid", state))
				valid = 0;
			else
				valid = 1;

			/* 0, 1, 2 */
			if (fd < 3) {
				if (! valid)
					TEST_FAILED ("fd %d is unexpectedly invalid", fd);
			} else {
				if (valid)
					TEST_FAILED ("fd %d is unexpectedly valid", fd);
			}
		}
	}

	fclose (output);
	TEST_EQ (unlink (filename), 0);

	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("ensure that no log file written for single-line no-output script");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "test", NULL);
	TEST_NE_P (class, NULL);
	TEST_GT (sprintf (filename, "%s/test.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_strdup (
			class->process[PROCESS_MAIN],
			"/bin/true");
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	ENSURE_DIRECTORY_EMPTY (dirname);

	/* Paranoia */
	TEST_TRUE (stat (filename, &statbuf) < 0 && errno == ENOENT);

	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("ensure that no log file written for single-line no-output command");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "test", NULL);
	TEST_NE_P (class, NULL);
	TEST_GT (sprintf (filename, "%s/test.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_strdup (
			class->process[PROCESS_MAIN],
			"/bin/true");
	class->process[PROCESS_MAIN]->script = FALSE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	ENSURE_DIRECTORY_EMPTY (dirname);

	/* Paranoia */
	TEST_TRUE (stat (filename, &statbuf) < 0 && errno == ENOENT);

	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("ensure that no log file written for CONSOLE_NONE");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "test", NULL);
	TEST_NE_P (class, NULL);
	TEST_GT (sprintf (filename, "%s/test.log", dirname), 0);

	class->console = CONSOLE_NONE;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s hello world", TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));

	TEST_EQ (WEXITSTATUS (status), 0);

	/* If a log is written, select(2) will inform us, but we don't
	 * expect this, hence specify a timeout.
	 */
	{
		struct timeval t;
		/* be generous */
		t.tv_sec  = 2;
		t.tv_usec = 0;
		TEST_WATCH_UPDATE_TIMEOUT (&t);
	}

	ENSURE_DIRECTORY_EMPTY (dirname);

	/* Paranoia */
	TEST_TRUE (stat (filename, &statbuf) < 0 && errno == ENOENT);

	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("ensure that no log file written for multi-line no-output script");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "test", NULL);
	TEST_NE_P (class, NULL);
	TEST_GT (sprintf (filename, "%s/test.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_strdup (
			class->process[PROCESS_MAIN],
			"/bin/true\n/bin/false");
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	/* XXX: call 0: async process setup */
	TEST_WATCH_UPDATE ();

	/* XXX: call 1: wait for script write to child shell */
	TEST_WATCH_UPDATE ();

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));

	/* we've just run /bin/false remember? :) */
	TEST_EQ (WEXITSTATUS (status), 1);

	/* XXX: call 2: wait for read from pty allowing logger to write to log file */
	TEST_WATCH_UPDATE ();

	ENSURE_DIRECTORY_EMPTY (dirname);

	/* Paranoia */
	TEST_TRUE (stat (filename, &statbuf) < 0 && errno == ENOENT);

	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with single-line script that writes 1 line to stdout");
	TEST_HASH_EMPTY (job_classes);

	/* Note we can't use TEST_ALLOC_FAIL() for this test since on
	 * the ENOMEM loop all we could do is discard the error and
	 * continue since job_process_start() calls job_process_spawn()
	 * repeatedly until it works, but the alloc fails in log_new()
	 * invoked by job_process_spawn() such that when we've left
	 * job_process_start(), it's too late.
	 *
	 * However, we test this scenario in test_spawn() so all is not
	 * lost.
	 */
	class = job_class_new (NULL, "test", NULL);
	TEST_NE_P (class, NULL);

	TEST_GT (sprintf (filename, "%s/test.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s hello world", TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "hello world\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with single-line script that is killed");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "test", NULL);
	TEST_NE_P (class, NULL);

	TEST_GT (sprintf (filename, "%s/test.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s hello world;sleep 999", TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	/*  wait for process to setup */
	TEST_WATCH_UPDATE ();

	/*  wait for read from pty allowing logger to write to log file */
	TEST_WATCH_UPDATE ();

	TEST_EQ (kill (-job->pid[PROCESS_MAIN], SIGKILL), 0);
	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFSIGNALED (status));
	TEST_EQ (WTERMSIG (status), SIGKILL);

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	/* This is very icky...
	 *
	 * Since we're not running an nih_main_loop, select(2) is
	 * not being called for us. We have already called
	 * select(2) once via TEST_WATCH_UPDATE() (since we expect
	 * the job to have produced output) but we have absolutely
	 * no way of knowing if it should be called again unless we have
	 * a custom loop which calls select(2) and then checks for the
	 * expected result. However, that would either mean
	 * TEST_WATCH_UPDATE() could not be called "in isolation" or
	 * that it would need to accept a block that could check some
	 * condition to know whether to call select(2) again.
	 *
	 * For now, we cheat by re-reading the log file a number of
	 * times. If we don't see the expected result within a
	 * "reasonable" period, we fail.
	 *
	 * This loop is necessary since although the amount of data
	 * being transferred is tiny, the kernel occasionally splits it
	 * into multiple chunks using one of the line end characters as
	 * a "delimiter".
	 */
	CHECK_FILE_EQ (output, "hello world\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with single-line command that is killed");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "test", NULL);
	TEST_NE_P (class, NULL);

	TEST_GT (sprintf (filename, "%s/test.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s", TEST_CMD_YES);
	class->process[PROCESS_MAIN]->script = FALSE;

	job = job_new (class, "");
	TEST_NE_P (job, NULL);

	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	/*  wait for process to setup */
	TEST_WATCH_UPDATE ();

	/*  wait for read from pty allowing logger to write to log file */
	TEST_WATCH_UPDATE ();

	TEST_EQ (kill (job->pid[PROCESS_MAIN], SIGKILL), 0);
	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFSIGNALED (status));
	TEST_EQ (WTERMSIG (status), SIGKILL);

	/* allow destructor to write any lingering unflushed data */
	nih_free (class);

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	/* Timed repeated read until we get the result we expect.
	 */
	ok = FALSE;
	while (fgets (filebuf, sizeof(filebuf), output) != NULL) {
		if (! strcmp (filebuf, "y\r\n"))
			ok = TRUE;
		else
			ok = FALSE;

		if (! ok)
			break;
	}

	if (! ok) {
		/* The last entry has been truncated, probably due to
		 * the kernel breaking the data on one of the newline
		 * characters. Attempt a few times to re-read all the
		 * expected data.
		 */
		for (int i = 0; i < MAX_ITERATIONS; i++) {
			/* rewind until 3 bytes ('y', '\r' and '\n')
			 * before EOF.
			 */
			fseek (output, 3, SEEK_END);

			TEST_NE_P (fgets (filebuf, sizeof (filebuf), output), NULL);
			if (! strcmp (filebuf, "y\r\n")) {
				ok = TRUE;
				break;
			}
			sleep (1);
			rewind (output);
		}
	}
	TEST_EQ (ok, TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);

	/************************************************************/
	TEST_FEATURE ("with multi-line script that is killed");
	TEST_HASH_EMPTY (job_classes);

	/* Note we can't use TEST_ALLOC_FAIL() for this test since on
	 * the ENOMEM loop all we could do is discard the error and
	 * continue since job_process_start() calls job_process_spawn()
	 * repeatedly until it works, but the alloc fails in log_new()
	 * invoked by job_process_spawn() such that when we've left
	 * job_process_start(), it's too late.
	 *
	 * However, we test this scenario in test_spawn() so all is not
	 * lost.
	 */
	class = job_class_new (NULL, "test", NULL);
	TEST_NE_P (class, NULL);

	TEST_GT (sprintf (filename, "%s/test.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s hello world\nsleep 999", TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	/*  wait for process to setup */
	TEST_WATCH_UPDATE ();

	/* XXX: call 1: wait for script write to child shell */
	TEST_WATCH_UPDATE ();

	/* XXX: call 2: wait for read from pty allowing logger to write to log file */
	TEST_WATCH_UPDATE ();

	TEST_EQ (kill (-job->pid[PROCESS_MAIN], SIGKILL), 0);
	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFSIGNALED (status));
	TEST_EQ (WTERMSIG (status), SIGKILL);

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "hello world\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with single-line script that writes 1 byte and is killed");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "test", NULL);
	TEST_NE_P (class, NULL);

	TEST_GT (sprintf (filename, "%s/test.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s -ne X;sleep 999", TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	/*  wait for process to setup */
	TEST_WATCH_UPDATE ();

	/*  wait for read from pty allowing logger to write to log file */
	TEST_WATCH_UPDATE ();

	TEST_EQ (kill (-job->pid[PROCESS_MAIN], SIGKILL), 0);
	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFSIGNALED (status));
	TEST_EQ (WTERMSIG (status), SIGKILL);

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	TEST_FILE_EQ (output, "X");
	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	/* Can't think of a command that would echo 1 byte and then
	 * either sleep or read a file forever to allow us time to kill
	 * it *after* it had written the single byte. Answers on a
	 * postcard please.
	 *
	 * TEST_FEATURE ("with single-line command that writes 1 byte and is killed");
	 */

	/************************************************************/
	TEST_FEATURE ("with multi-line script that writes 1 byte and is killed");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "multiline", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/multiline.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"/bin/true\n%s -ne F", TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	/*  wait for process to setup */
	TEST_WATCH_UPDATE ();

	/* XXX: call 1: wait for script write to child shell */
	TEST_WATCH_UPDATE ();

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	/* XXX: call 2: wait for read from pty allowing logger to write to log file */
	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	TEST_FILE_EQ (output, "F");
	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with single-line command that writes 1 line to stdout");
	TEST_HASH_EMPTY (job_classes);

	/* Note we can't use TEST_ALLOC_FAIL() for this test since on
	 * the ENOMEM loop all we could do is discard the error and
	 * continue since job_process_start() calls job_process_spawn()
	 * repeatedly until it works, but the alloc fails in log_new()
	 * invoked by job_process_spawn() such that when we've left
	 * job_process_start(), it's too late.
	 *
	 * However, we test this scenario in test_spawn() so all is not
	 * lost.
	 */
	class = job_class_new (NULL, "test", NULL);
	TEST_NE_P (class, NULL);

	TEST_GT (sprintf (filename, "%s/test.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s hello world", TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = FALSE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "hello world\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with multi-line script that writes 1 line to stdout");
	TEST_HASH_EMPTY (job_classes);

	/* XXX: Note that all tests which use multi-line scripts (but
	 * XXX: *NOT* commands!) and produce output must call
	 * XXX: TEST_WATCH_UPDATE() *TWICE* to ensure select(2) is
	 * XXX: called twice.
	 *
	 * This is required since job_process_start() uses an NihIo object
	 * to squirt the script to the shell sub-process and this
	 * triggers select to return when the data is written to the shell.
	 * However, we don't care about that directly - we care more about
	 * a subsequent fd becoming ready to read data from - the fd
	 * associated with the pty which will trigger the log file to be
	 * written.
	 *
	 * Note that the 2nd call to TEST_WATCH_UPDATE would not be
	 * required should job_process_start() simple invoke write(2) to
	 * send the data.
	 */

	class = job_class_new (NULL, "multiline", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/multiline.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"/bin/true\n%s hello world\n\n\n\n\n\n\n\n\n\n", TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	/*  wait for process to setup */
	TEST_WATCH_UPDATE ();

	/* XXX: call 1: wait for script write to child shell */
	TEST_WATCH_UPDATE ();

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	/* XXX: call 2: wait for read from pty allowing logger to write to log file */
	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "hello world\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with instance job and single-line script that writes 1 line to stdout");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "test", NULL);
	TEST_NE_P (class, NULL);

	TEST_GT (sprintf (filename, "%s/test-instance.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s hello world", TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "instance");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "hello world\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with single-line script that writes >1 lines to stdout");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "foo", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/foo.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			/* XXX: note the required quoting */
			"%s -ne \"hello world\\n\\n\\n\"", TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	/* Yup, pseudo-terminals record *everything*,
	 * even the carriage returns.
	 */
	CHECK_FILE_EQ (output, "hello world\r\n", TRUE);
	CHECK_FILE_EQ (output, "\r\n", TRUE);
	CHECK_FILE_EQ (output, "\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with single-line command that writes >1 lines to stdout");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "foo", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/foo.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			/* XXX: note the required quoting */
			"%s -ne \"hello world\\n\\n\\n\"", TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = FALSE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "hello world\r\n", TRUE);
	CHECK_FILE_EQ (output, "\r\n", TRUE);
	CHECK_FILE_EQ (output, "\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with multi-line script that writes >1 lines to stdout");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "elf", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/elf.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			/* XXX: note the required quoting */
			"\n/bin/true\n%s -ne \"hello world\\n\\n\\n\"\n\n", TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	TEST_WATCH_UPDATE ();
	TEST_WATCH_UPDATE ();
	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);
	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "hello world\r\n", TRUE);
	CHECK_FILE_EQ (output, "\r\n", TRUE);
	CHECK_FILE_EQ (output, "\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with single-line script that writes 1 line to stderr");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "test", NULL);
	TEST_NE_P (class, NULL);

	TEST_GT (sprintf (filename, "%s/test.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s hello world >&2", TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "hello world\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with single-line command that writes 1 line to stderr");
	TEST_HASH_EMPTY (job_classes);

	/* Run a command that generates output to stderr without having
	 * to use script redirection.
	 *
	 * dd(1) is a good choice as it always writes to stderr.
	 */
	class = job_class_new (NULL, "test", NULL);
	TEST_NE_P (class, NULL);

	TEST_GT (sprintf (filename, "%s/test.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s if=/dev/zero of=/dev/null bs=1 count=0", TEST_CMD_DD);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "0+0 records in\r\n", TRUE);
	CHECK_FILE_EQ (output, "0+0 records out\r\n", TRUE);

	TEST_FILE_MATCH (output, "0 bytes (0 B) copied,*\r\n");
	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with multi-line script that writes 1 line to stderr");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "test", NULL);
	TEST_NE_P (class, NULL);

	TEST_GT (sprintf (filename, "%s/test.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"/bin/true\n%s hello world >&2\n\n\n", TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	TEST_WATCH_UPDATE ();
	TEST_WATCH_UPDATE ();

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "hello world\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with single-line script that writes >1 lines to stderr");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "foo", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/foo.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			/* XXX: note the required quoting */
			"%s -ne \"hello\\nworld\\n\\n\\n\" >&2", TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	/* Yup, pseudo-terminals record *everything*,
	 * even the carriage returns.
	 */
	CHECK_FILE_EQ (output, "hello\r\n", TRUE);
	CHECK_FILE_EQ (output, "world\r\n", TRUE);
	CHECK_FILE_EQ (output, "\r\n", TRUE);
	CHECK_FILE_EQ (output, "\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with single-line command that writes >1 lines to stderr");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "foo", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/foo.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			/* XXX: note the required quoting */
			"%s -ne \"hello world\\n\\n\\n\"", TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = FALSE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "hello world\r\n", TRUE);
	CHECK_FILE_EQ (output, "\r\n", TRUE);
	CHECK_FILE_EQ (output, "\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with multi-line script that writes >1 lines to stderr");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "elf", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/elf.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			/* XXX: note the required quoting */
			"/bin/true\n%s -ne \"hello world\\n\\n\" 1>&2\n\n\n", TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	TEST_WATCH_UPDATE ();
	TEST_WATCH_UPDATE ();

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "hello world\r\n", TRUE);
	CHECK_FILE_EQ (output, "\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with single-line script that writes 1 line to stdout then 1 line to stderr");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "blah", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/blah.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			/* XXX: note the required quoting */
			"%s stdout;%s stderr >&2",
			TEST_CMD_ECHO, TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "stdout\r\n", TRUE);
	CHECK_FILE_EQ (output, "stderr\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with single-line script that writes 1 line to stderr then 1 line to stdout");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "blah", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/blah.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			/* XXX: note the required quoting */
			"%s stderr >&2;%s stdout",
			TEST_CMD_ECHO, TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "stderr\r\n", TRUE);
	CHECK_FILE_EQ (output, "stdout\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with single-line command that writes to stdout and stderr");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "blah", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/blah.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s if=/dev/zero bs=1 count=7", TEST_CMD_DD);
	class->process[PROCESS_MAIN]->script = FALSE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	TEST_NE_P (fgets (filebuf, sizeof(filebuf), output), NULL);
	TEST_EQ (memcmp (filebuf, "\000\000\000\000\000\000", 7), 0);
	p = filebuf + 7;
	TEST_EQ_STR (p, "7+0 records in\r\n");

	CHECK_FILE_EQ (output, "7+0 records out\r\n", TRUE);
	TEST_FILE_MATCH (output, "7 bytes (7 B) copied,*\r\n");
	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with single-line script running an invalid command");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "blah", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/blah.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_strdup (
			class->process[PROCESS_MAIN],
			"/this/command/does/not/exist");
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_NE (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	TEST_TRUE (fgets (buffer, sizeof(buffer), output));
	TEST_STR_MATCH (buffer, "*sh:*/this/command/does/not/exist:*");

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************
	 * Superficially, there seems little point in running a test for
	 * this scenario since if Upstart attempts to exec(2) directly a
	 * command that does not exist, the exec simply fails (since
	 * there is no shell to report the error).
	 *
	 * And yet -- ironically -- bug 912558 would have been prevented
	 * had we originally tested this scenario!
	 ************************************************************/
	TEST_FEATURE ("with single-line command running an invalid command");
	TEST_HASH_EMPTY (job_classes);

	TEST_RESET_MAIN_LOOP ();
	TEST_INSTALL_CHILD_HANDLERS ();

	class = job_class_new (NULL, "buzz", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/buzz.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_strdup (
			class->process[PROCESS_MAIN],
			"/this/command/does/not/exist");
	class->process[PROCESS_MAIN]->script = FALSE;

	/* Stranger things have happened at sea */
	TEST_EQ (stat (class->process[PROCESS_MAIN]->command, &statbuf), -1);
	TEST_EQ (errno, ENOENT);

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	/* XXX: Manually add the class so job_process_find() works */
	nih_hash_add (job_classes, &class->entry);

	output = tmpfile ();
	TEST_NE_P (output, NULL);
	TEST_CLEAR_CHILD_STATUS ();
	TEST_DIVERT_STDERR (output) {
		job_process_start (job, PROCESS_MAIN);
		TEST_GT (job->pid[PROCESS_MAIN], 0);
		TEST_EQ (nih_main_loop (), 0);
		TEST_EQ (child_exit_status[PROCESS_MAIN], 255);
	}

	TEST_FILE_END (output);

	fclose (output);

	/* We don't expect a logfile to be written since there is no
	 * accompanying shell to write the error.
	 */
	TEST_EQ (stat (filename, &statbuf), -1);
	TEST_EQ (errno, ENOENT);

	nih_free (class);
	TEST_RESET_MAIN_LOOP ();

#if 0
	/************************************************************/
	TEST_FEATURE ("with single-line command running an invalid command, then a 1-line post-stop script");
	TEST_HASH_EMPTY (job_classes);

	TEST_INSTALL_CHILD_HANDLERS ();

	class = job_class_new (NULL, "asterix", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/asterix.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_strdup (
			class->process[PROCESS_MAIN],
			"/this/command/does/not/exist");
	class->process[PROCESS_MAIN]->script = FALSE;

	class->process[PROCESS_POST_STOP] = process_new (class);
	class->process[PROCESS_POST_STOP]->command = nih_sprintf (
			class->process[PROCESS_POST_STOP],
			"echo hello");
	class->process[PROCESS_POST_STOP]->script = TRUE;

	/* Stranger things have happened at sea */
	TEST_EQ (stat (class->process[PROCESS_MAIN]->command, &statbuf), -1);
	TEST_EQ (errno, ENOENT);

	job = job_new (class, "");

	/* XXX: Manually add the class so job_process_find() works */
	nih_hash_add (job_classes, &class->entry);

	output = tmpfile ();
	TEST_NE_P (output, NULL);
	TEST_DIVERT_STDERR (output) {

		job->goal = JOB_START;
		job->state = JOB_SPAWNED;

		TEST_CLEAR_CHILD_STATUS ();
		child_exit_after = 2;
		job_process_start (job, PROCESS_MAIN);
		TEST_GT (job->pid[PROCESS_MAIN], 0);
		TEST_EQ (nih_main_loop (), 0);
		/* Check exit status in reverse order */
		/* Main */
		TEST_EQ (child_exit_status[1], 255);
		/* Post-stop */
		TEST_EQ (child_exit_status[0], 0);
		/* And the post stop should have written data */
		TEST_EQ (stat (filename, &statbuf), 0);
	}
	fclose (output);

	/* check file contents */
	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "hello\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);

	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with single-line command running an invalid command, then a 2-line post-stop script");
	TEST_HASH_EMPTY (job_classes);

	TEST_RESET_MAIN_LOOP ();
	TEST_INSTALL_CHILD_HANDLERS ();

	class = job_class_new (NULL, "asterix", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/asterix.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_strdup (
			class->process[PROCESS_MAIN],
			"/this/command/does/not/exist");
	class->process[PROCESS_MAIN]->script = FALSE;

	class->process[PROCESS_POST_STOP] = process_new (class);
	class->process[PROCESS_POST_STOP]->command = nih_sprintf (
			class->process[PROCESS_POST_STOP],
			"echo hello\necho world");
	class->process[PROCESS_POST_STOP]->script = TRUE;

	/* Stranger things have happened at sea */
	TEST_EQ (stat (class->process[PROCESS_MAIN]->command, &statbuf), -1);
	TEST_EQ (errno, ENOENT);

	job = job_new (class, "");
	/* XXX: Manually add the class so job_process_find() works */
	nih_hash_add (job_classes, &class->entry);

	output = tmpfile ();
	TEST_NE_P (output, NULL);
	TEST_DIVERT_STDERR (output) {

		job->goal = JOB_START;
		job->state = JOB_SPAWNED;

		TEST_CLEAR_CHILD_STATUS ();
		child_exit_after = 2;
		job_process_start (job, PROCESS_MAIN);
		TEST_NE (job->pid[PROCESS_MAIN], 0);

		TEST_EQ (nih_main_loop (), 0);
		TEST_EQ (child_exit_status[1], 255);
		TEST_EQ (child_exit_status[0], 0);
		
		/* And the post stop should have written data */
		TEST_EQ (stat (filename, &statbuf), 0);
	}
	fclose (output);

	/* check file contents */
	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "hello\r\n", TRUE);
	CHECK_FILE_EQ (output, "world\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);

	nih_free (class);
	TEST_RESET_MAIN_LOOP ();

	/************************************************************/
	TEST_FEATURE ("with single-line command running an invalid command, then a post-stop command");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "asterix", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/asterix.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_strdup (
			class->process[PROCESS_MAIN],
			"/this/command/does/not/exist");
	class->process[PROCESS_MAIN]->script = FALSE;

	class->process[PROCESS_POST_STOP] = process_new (class);
	class->process[PROCESS_POST_STOP]->command = nih_sprintf (
			class->process[PROCESS_POST_STOP],
			"echo hello");
	class->process[PROCESS_POST_STOP]->script = FALSE;

	/* Stranger things have happened at sea */
	TEST_EQ (stat (class->process[PROCESS_MAIN]->command, &statbuf), -1);
	TEST_EQ (errno, ENOENT);

	job = job_new (class, "");

	TEST_RESET_MAIN_LOOP ();
	TEST_INSTALL_CHILD_HANDLERS ();

	output = tmpfile ();
	TEST_NE_P (output, NULL);
	TEST_DIVERT_STDERR (output) {

		job->goal = JOB_START;
		job->state = JOB_SPAWNED;

		TEST_CLEAR_CHILD_STATUS ();
		child_exit_after = 2;

		job_process_start (job, PROCESS_MAIN);
		TEST_GT (job->pid[PROCESS_MAIN], 0);
		TEST_EQ (nih_main_loop (), 0);
		TEST_GT (job->pid[PROCESS_POST_STOP], 0);
		TEST_EQ (child_exit_status[1], 255);
		TEST_EQ (child_exit_status[0], 0);

		/* The post stop should have written data */
		TEST_EQ (stat (filename, &statbuf), 0);

	}
	fclose (output);

	/* check file contents */
	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "hello\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);

	nih_free (class);

	TEST_RESET_MAIN_LOOP ();
#endif

	/************************************************************/
	TEST_FEATURE ("with single-line command running an invalid command, then an invalid post-stop command");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "asterix", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/asterix.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_strdup (
			class->process[PROCESS_MAIN],
			"/this/command/does/not/exist");
	class->process[PROCESS_MAIN]->script = FALSE;

	class->process[PROCESS_POST_STOP] = process_new (class);
	class->process[PROCESS_POST_STOP]->command = nih_sprintf (
			class->process[PROCESS_POST_STOP],
			"/this/command/does/not/exist");
	class->process[PROCESS_POST_STOP]->script = FALSE;

	/* Stranger things have happened at sea */
	TEST_EQ (stat (class->process[PROCESS_MAIN]->command, &statbuf), -1);
	TEST_EQ (errno, ENOENT);

	job = job_new (class, "");

	TEST_RESET_MAIN_LOOP ();
	TEST_INSTALL_CHILD_HANDLERS ();

	output = tmpfile ();
	TEST_NE_P (output, NULL);
	TEST_DIVERT_STDERR (output) {

		job->goal = JOB_START;
		job->state = JOB_SPAWNED;

		TEST_CLEAR_CHILD_STATUS ();
		child_exit_after = 2;

		job_process_start (job, PROCESS_MAIN);
		TEST_GT (job->pid[PROCESS_MAIN], 0);
		TEST_EQ (nih_main_loop (), 0);
		TEST_EQ (child_exit_status[1], 255);
		TEST_EQ (child_exit_status[0], 255);

		/* Again, no file expected */
		TEST_EQ (stat (filename, &statbuf), -1);
		TEST_EQ (errno, ENOENT);
	}
	fclose (output);
	nih_free (class);

	TEST_RESET_MAIN_LOOP ();

	/************************************************************/
	TEST_FEATURE ("with single-line command running a valid command, then a 1-line invalid post-stop command");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "obelix", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/obelix.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s hello world", TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = FALSE;

	class->process[PROCESS_POST_STOP] = process_new (class);
	class->process[PROCESS_POST_STOP]->command = nih_strdup (
			class->process[PROCESS_POST_STOP],
			"/this/command/does/not/exist");
	class->process[PROCESS_POST_STOP]->script = FALSE;

	/* Stranger things have happened at sea */
	TEST_EQ (stat (class->process[PROCESS_POST_STOP]->command, &statbuf), -1);
	TEST_EQ (errno, ENOENT);

	job = job_new (class, "");

	TEST_RESET_MAIN_LOOP ();
	TEST_INSTALL_CHILD_HANDLERS ();

	output = tmpfile ();
	TEST_NE_P (output, NULL);
	TEST_DIVERT_STDERR (output) {

		job->goal = JOB_START;
		job->state = JOB_SPAWNED;

		TEST_CLEAR_CHILD_STATUS ();

		job_process_start (job, PROCESS_MAIN);
		TEST_GT (job->pid[PROCESS_MAIN], 0);
		TEST_EQ (nih_main_loop (), 0);
		TEST_EQ (child_exit_status[0], 0);
		TEST_EQ (child_exit_status[1], -1);

		/* Expect a log file */
		TEST_EQ (stat (filename, &statbuf), 0);

		job->goal = JOB_STOP;
		job->state = JOB_POST_STOP;
		
		TEST_CLEAR_CHILD_STATUS ();

		job_process_start (job, PROCESS_POST_STOP);
		TEST_GT (job->pid[PROCESS_POST_STOP], 0);
		TEST_EQ (nih_main_loop (), 0);
		TEST_EQ (child_exit_status[0], 255);
	}
	fclose (output);

	/* check file contents */
	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "hello world\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);

	nih_free (class);

	TEST_RESET_MAIN_LOOP ();

	/************************************************************/
	TEST_FEATURE ("with multi-line script running an invalid command");
	TEST_HASH_EMPTY (job_classes);

	TEST_RESET_MAIN_LOOP ();
	TEST_INSTALL_CHILD_HANDLERS ();

	class = job_class_new (NULL, "blah", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/blah.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_strdup (
			class->process[PROCESS_MAIN],
			"true\n/this/command/does/not/exist");
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;
	nih_hash_add (job_classes, &class->entry);
	TEST_CLEAR_CHILD_STATUS ();

	job_process_start (job, PROCESS_MAIN);
	TEST_GT (job->pid[PROCESS_MAIN], 0);
	TEST_EQ (nih_main_loop (), 0);
	TEST_EQ (child_exit_status[0], 127);

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	TEST_TRUE (fgets (buffer, sizeof(buffer), output));
	TEST_STR_MATCH (buffer, "/proc/self/fd/9*/this/command/does/not/exist:*");

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);
	TEST_RESET_MAIN_LOOP ();

	/************************************************************/
	TEST_FEATURE ("with multi-line script that writes 1 line to stdout then 1 line to stderr");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "blah", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/blah.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s stdout\n%s stderr >&2\n",
			TEST_CMD_ECHO, TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);
	TEST_WATCH_UPDATE ();

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	TEST_WATCH_UPDATE ();

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "stdout\r\n", TRUE);
	CHECK_FILE_EQ (output, "stderr\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with multi-line script that writes 1 line to stderr then 1 line to stdout");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "blah", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/blah.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s stderr >&2\n%s stdout\n",
			TEST_CMD_ECHO, TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = TRUE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);
	TEST_WATCH_UPDATE ();

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	TEST_WATCH_UPDATE ();

	waitpid (job->pid[PROCESS_MAIN], &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "stderr\r\n", TRUE);
	CHECK_FILE_EQ (output, "stdout\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);
	nih_free (class);

	/************************************************************/
	/* XXX: Note that we don't force a watch update here to simulate
	 * a job that writes data _after_ Upstart has run nih_io_handle_fds()
	 * in the main loop and just _before_ it exits _in the same main
	 * loop iteration_.
	 */
	TEST_FEATURE ("with single line command writing fast and exiting");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "budapest", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/budapest.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	/* program to run "fast", so directly exec a program with
	 * no shell intervention.
	 */
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s hello\n",
			TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = FALSE;

	/* XXX: Manually add the class so job_process_find() works */
	nih_hash_add (job_classes, &class->entry);

	NIH_MUST (nih_child_add_watch (NULL,
				-1,
				NIH_CHILD_ALL,
				job_process_handler,
				NULL)); 

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);

	/* Wait for process to avoid any possibility of EAGAIN in
	 * log_read_watch().
	 */
	pid = job->pid[PROCESS_MAIN];
	TEST_EQ (waitpid (pid, NULL, 0), pid);

	/* allow destructor to write any lingering unflushed data */
	nih_free (class);

	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "hello\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	TEST_EQ (unlink (filename), 0);

	/************************************************************/
	TEST_FEATURE ("with single line command writing lots of data fast and exiting");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "foo", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/foo.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	/* program must run "fast", so directly exec with
	 * no shell intervention.
	 *
	 * Writes large number of nulls (3MB).
	 */
#define EXPECTED_1K_BLOCKS	(1024*3)
#define TEST_BLOCKSIZE           1024

	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s if=/dev/zero bs=%d count=%d",
			TEST_CMD_DD, TEST_BLOCKSIZE, EXPECTED_1K_BLOCKS);
	class->process[PROCESS_MAIN]->script = FALSE;

	NIH_MUST (nih_child_add_watch (NULL,
				-1,
				NIH_CHILD_ALL,
				job_process_handler,
				NULL)); 

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	job_process_start (job, PROCESS_MAIN);
	TEST_WATCH_UPDATE ();
	TEST_WATCH_UPDATE ();

	pid = job->pid[PROCESS_MAIN];

	/* job will block until something reads the other end of the pty */
	TEST_EQ (kill (pid, 0), 0);

	{
		size_t  bytes = 0;
		size_t  expected_bytes = TEST_BLOCKSIZE * EXPECTED_1K_BLOCKS;
		off_t   filesize = (off_t)-1;

		/* Check repeatedly for job log output jobs until
		 * we've either read the expected number of nulls, or we
		 * timed out.
		 */
		while ( 1 ) {
			size_t           length;
			size_t           i;
			struct timeval   t;
			nih_local char  *file = NULL;

			t.tv_sec  = 1;
			t.tv_usec = 0;

			TEST_WATCH_UPDATE_TIMEOUT (&t);

			TEST_EQ (stat (filename, &statbuf), 0);

			/* We expect the file size to change */
			if (statbuf.st_size == filesize) {
				break;
			}

			filesize = statbuf.st_size;

			file = nih_file_read (NULL, filename, &length);
			TEST_NE_P (file, NULL);

			bytes = 0;
			for (i=0; i < length; ++i) {
				if (file[i] == '\0')
					bytes++;
			}

			if (bytes == expected_bytes) {
				break;
			}
		}

		TEST_EQ (bytes, expected_bytes);
	}

	TEST_EQ (kill (pid, 0), 0);

	/* Wait until the process is in a known state. This ensures that
	 * when job_process_terminated() calls log_handle_unflushed(), 
	 * the log object will _not_ get added to the unflushed list,
	 * meaning it will get destroyed immediately.
	 */
	waitid (P_PID, pid, &siginfo, WEXITED | WNOWAIT);

	nih_child_poll ();

	/* The process should now be dead */
	TEST_EQ (kill (pid, 0), -1);
	TEST_EQ (errno, ESRCH);

	nih_free (class);
	TEST_EQ (stat (filename, &statbuf), 0);

	TEST_TRUE (S_ISREG (statbuf.st_mode));

	TEST_TRUE  (statbuf.st_mode & S_IRUSR);
	TEST_TRUE  (statbuf.st_mode & S_IWUSR);
	TEST_FALSE (statbuf.st_mode & S_IXUSR);

	TEST_TRUE  (statbuf.st_mode & S_IRGRP);
	TEST_FALSE (statbuf.st_mode & S_IWGRP);
	TEST_FALSE (statbuf.st_mode & S_IXGRP);

	TEST_FALSE (statbuf.st_mode & S_IROTH);
	TEST_FALSE (statbuf.st_mode & S_IWOTH);
	TEST_FALSE (statbuf.st_mode & S_IXOTH);

	TEST_EQ (unlink (filename), 0);

#undef  EXPECTED_1K_BLOCKS
#undef  TEST_BLOCKSIZE

	/************************************************************/
	/* Applies to respawn jobs too */

	TEST_FEATURE ("with log object freed on process exit");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "acorn", NULL);
	TEST_NE_P (class, NULL);

	TEST_FILENAME (filename);
	TEST_GT (sprintf (filename, "%s/acorn.log", dirname), 0);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s hello",
			TEST_CMD_ECHO);
	class->process[PROCESS_MAIN]->script = FALSE;

	/* XXX: Manually add the class so job_process_find() works */
	nih_hash_add (job_classes, &class->entry);

	NIH_MUST (nih_child_add_watch (NULL,
				-1,
				NIH_CHILD_ALL,
				job_process_handler,
				NULL)); 

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	TEST_NE_P (job->log, NULL);
	TEST_ALLOC_PARENT (job->log, job);

	for (i = 0; i < PROCESS_LAST; i++) {
		TEST_EQ_P (job->log[i], NULL);
	}

	job_process_start (job, PROCESS_MAIN);
	TEST_WATCH_UPDATE ();

	pid = job->pid[PROCESS_MAIN];

	job->goal = JOB_STOP;
	job->state = JOB_KILLED;

	TEST_NE (job->pid[PROCESS_MAIN], 0);

	TEST_NE_P (job->log, NULL);
	for (i = 0; i < PROCESS_LAST; i++) {
		if (i == PROCESS_MAIN) {
			TEST_NE_P (job->log[i], NULL);
			TEST_ALLOC_PARENT (job->log[i], job->log);
		} else {
			TEST_EQ_P (job->log[i], NULL);
		}
	}

	TEST_FREE_TAG (job);
	TEST_FREE_TAG (job->log);

	/* Wait until the process is in a known state. This ensures that
	 * when job_process_terminated() calls log_handle_unflushed(), 
	 * the log object will _not_ get added to the unflushed list,
	 * meaning it will get destroyed immediately.
	 */
	waitid (P_PID, pid, &siginfo, WEXITED | WNOWAIT);

	nih_child_poll ();

	/* Should have been destroyed now */
	TEST_FREE (job);
	TEST_FREE (job->log);

	nih_free (class);
	unlink (filename);

	/************************************************************/

	/* Check that we can succesfully setuid and setgid to
	 * ourselves. This should always work, privileged or
	 * otherwise.
	 */
	TEST_FEATURE ("with setuid me");
	TEST_HASH_EMPTY (job_classes);

	TEST_NE_P (output, NULL);
	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			class = job_class_new (NULL, "test", NULL);
			class->process[PROCESS_MAIN] = process_new (class);
			class->process[PROCESS_MAIN]->command = nih_sprintf (
				class->process[PROCESS_MAIN],
				"touch %s", filename);

			pwd = getpwuid (getuid ());
			TEST_NE (pwd, NULL);
			class->setuid = nih_strdup (class, pwd->pw_name);

			grp = getgrgid (getgid ());
			TEST_NE (grp, NULL);
			class->setgid = nih_strdup (class, grp->gr_name);

			job = job_new (class, "");
			job->goal = JOB_START;
			job->state = JOB_SPAWNED;

			output = tmpfile ();
		}

		TEST_DIVERT_STDERR (output) {
			job_process_start (job, PROCESS_MAIN);
		}
		fclose (output);

		TEST_NE (job->pid[PROCESS_MAIN], 0);

		waitpid (job->pid[PROCESS_MAIN], NULL, 0);
		TEST_EQ (stat (filename, &statbuf), 0);

		unlink (filename);
		nih_free (class);
	}

	/************************************************************/

	/* Check that initgroups gets called.
	 * The test will run a job as nobody/nogroup (setuid/setgid) target.
	 *
	 * When run from an unprivileged user, the check will ensure that upstart
	 * fails to start the job (returning -1) as initgroups() is a privileged
	 * call (similar to setuid and setgid).
	 *
	 * When run from a privileged user (root), the check will ensure that
	 * upstart succeeds in dropping privileges, which includes calling
	 * initgroup, setuid and setgid.
	 *
	 * If the test is started by user nobody/nogroup, then it'll succeed as
	 * there's no privilege changes to be done in such case (same uid/gid).
	 */
	TEST_FEATURE ("with setuid");
	TEST_HASH_EMPTY (job_classes);
	TEST_RESET_MAIN_LOOP ();
	TEST_INSTALL_CHILD_HANDLERS ();


	TEST_NE_P (output, NULL);
	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			class = job_class_new (NULL, "test", NULL);
			class->process[PROCESS_MAIN] = process_new (class);
			class->process[PROCESS_MAIN]->command = nih_sprintf (
				class->process[PROCESS_MAIN],
				"touch %s", filename);

			pwd = getpwnam ("nobody");
			TEST_NE (pwd, NULL);
			class->setuid = nih_strdup (class, pwd->pw_name);

			grp = getgrnam ("nogroup");
			TEST_NE (grp, NULL);
			class->setgid = nih_strdup (class, grp->gr_name);

			job = job_new (class, "");
			job->goal = JOB_START;
			job->state = JOB_SPAWNED;

			nih_hash_add (job_classes, &class->entry);
			TEST_CLEAR_CHILD_STATUS ();

			output = tmpfile ();
		}

		TEST_DIVERT_STDERR (output) {
			job_process_start (job, PROCESS_MAIN);
			TEST_GT (job->pid[PROCESS_MAIN], 0);
			TEST_EQ (nih_main_loop (), 0);
		}

		if (geteuid() == 0 || getuid() == pwd->pw_uid) {
			TEST_EQ (stat (filename, &statbuf), 0);
		} else {
			TEST_EQ (stat (filename, &statbuf), -1);
		}

		unlink (filename);
		nih_free (class);
	}
	
	TEST_RESET_MAIN_LOOP ();


	/************************************************************/
	TEST_FEATURE ("with multiple processes and log");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "aero", NULL);
	TEST_NE_P (class, NULL);

	TEST_EQ (setenv ("UPSTART_LOGDIR", dirname, 1), 0);

	TEST_GT (sprintf (filename, "%s/aero.log", dirname), 0);

	sprintf (function, "%d", TEST_OUTPUT_WITH_STOP);

	/* Create a temporary filename for child() output. We don't care
	 * about this file as we're interested in childs() stdout/stderr
	 * output only.
	 */
	TEST_FILENAME (filebuf);

	class->console = CONSOLE_LOG;
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_sprintf (
			class->process[PROCESS_MAIN],
			"%s %s %s",
			argv0, function, filebuf);
	class->process[PROCESS_MAIN]->script = FALSE;

	sprintf (function, "%d", TEST_OUTPUT);

	class->process[PROCESS_POST_START] = process_new (class);
	class->process[PROCESS_POST_START]->command = nih_sprintf (
			class->process[PROCESS_POST_START],
			"%s %s %s",
			argv0, function, filebuf);
	class->process[PROCESS_POST_START]->script = FALSE;

	job = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNING;

	job_process_start (job, PROCESS_MAIN);
	while (stat (filename, &statbuf) != 0 || statbuf.st_size < 9) {
		TEST_WATCH_UPDATE ();
	}
	pid = job->pid[PROCESS_MAIN];
	TEST_GT (pid, 0);

	TEST_EQ (stat (filename, &statbuf), 0);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	/* initial output from main process */
	TEST_FILE_EQ (output, "started\r\n");

	TEST_EQ (fclose (output), 0);

	job_process_start (job, PROCESS_POST_START);
	TEST_WATCH_UPDATE ();

	pid = job->pid[PROCESS_POST_START];
	TEST_GT (pid, 0);

	/* wait for post-start to finish */
	waitpid (pid, &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	while (stat (filename, &statbuf) != 0 || statbuf.st_size < 25) {
		TEST_WATCH_UPDATE ();
	}

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	/* initial output from main process, followed by all output from
	 * post-start process.
	 */
	CHECK_FILE_EQ (output, "started\r\n", TRUE);
	CHECK_FILE_EQ (output, "stdout\r\n", TRUE);
	CHECK_FILE_EQ (output, "stderr\r\n", TRUE);

	TEST_FILE_END (output);

	TEST_EQ (fclose (output), 0);

	pid = job->pid[PROCESS_MAIN];

	TEST_EQ (kill (pid, SIGCONT), 0);
	waitpid (pid, &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	/* wait for post-start to finish */
	waitpid (pid, &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	TEST_WATCH_UPDATE ();

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	/* initial output from main process, followed by all output from
	 * post-start process, followed by final data from main process.
	 */
	CHECK_FILE_EQ (output, "started\r\n", TRUE);
	CHECK_FILE_EQ (output, "stdout\r\n", TRUE);
	CHECK_FILE_EQ (output, "stderr\r\n", TRUE);
	CHECK_FILE_EQ (output, "ended\r\n", TRUE);

	TEST_FILE_END (output);

	TEST_EQ (fclose (output), 0);

	TEST_EQ (unlink (filebuf), 0);
	TEST_EQ (unlink (filename), 0);

	/************************************************************/
	/* Final clean-up */

	TEST_EQ (rmdir (dirname), 0);
	TEST_EQ (unsetenv ("UPSTART_LOGDIR"), 0);
	TEST_HASH_EMPTY (job_classes);
}


/* 
 * XXX: Note that none of these tests attempts to test with a Session
 * passed to job_class_new() since to do so would modify the home
 * directory of the user running these tests (BAD!!).
 *
 * (Such tests are handled in the bundled test_user_sessions.sh script).
 */
void
test_spawn (void)
{
	FILE             *output, *input;
	char              function[PATH_MAX], filename[PATH_MAX];
	char              dirname[PATH_MAX];
	char              script[PATH_MAX];
	char              buf[80];
	char              filebuf[1024];
	char             *args[6];
	char             *env[3];
	nih_local char  **args_array = NULL;
	size_t            argc;
	JobClass         *class;
	Job              *job;
	pid_t             pid;
	siginfo_t         info;
	NihError         *err;
	//JobProcessError  *perr;
	int               status;
	struct stat       statbuf;
	int               ret;
	int               job_process_fd = -1;
	nih_local NihIoBuffer *buffer = NULL;

	log_unflushed_init ();

	/* reset */
	(void) umask (0);
	TEST_FILENAME (dirname);       
	TEST_EQ (mkdir (dirname, 0755), 0);

	/* Override default location to ensure job output goes to a
	 * writeable location
	 */
	TEST_EQ (setenv ("UPSTART_LOGDIR", dirname, 1), 0);

	TEST_FUNCTION ("job_process_spawn_with_fd");
	TEST_FILENAME (filename);

	args[0] = argv0;
	args[1] = function;
	args[2] = filename;
	args[3] = NULL;

	/* Check that we can spawn a simple job, waiting for the child
	 * process to complete and reading from the file written to check
	 * that the process tree is what we expect it to look like.
	 */
	TEST_FEATURE ("with simple job");
	TEST_HASH_EMPTY (job_classes);

	sprintf (function, "%d", TEST_PIDS);

	class = job_class_new (NULL, "test", NULL);
	class->console = CONSOLE_NONE;
	job   = job_new (class, "");

	pid = job_process_spawn_with_fd (job, args, NULL, FALSE, -1, PROCESS_MAIN, &job_process_fd);
	TEST_GT (pid, 0);

	waitpid (pid, NULL, 0);
	output = fopen (filename, "r");

	TEST_GT (pid, 0);
	TEST_NE (pid, getpid ());

	sprintf (buf, "pid: %d\n", pid);
	TEST_FILE_EQ (output, buf);

	sprintf (buf, "ppid: %d\n", getpid ());
	TEST_FILE_EQ (output, buf);

	sprintf (buf, "pgrp: %d\n", pid);
	TEST_FILE_EQ (output, buf);

	sprintf (buf, "sid: %d\n", pid);
	TEST_FILE_EQ (output, buf);

	TEST_FILE_END (output);

	fclose (output);
	assert0 (unlink (filename));

	nih_free (class);


	/* Check that a job spawned with no console has the file descriptors
	 * bound to the /dev/null device.
	 */
	TEST_FEATURE ("with no console");
	TEST_HASH_EMPTY (job_classes);

	sprintf (function, "%d", TEST_CONSOLE);

	class = job_class_new (NULL, "test", NULL);
	class->console = CONSOLE_NONE;
	job = job_new (class, "");

	pid = job_process_spawn_with_fd (job, args, NULL, FALSE, -1, PROCESS_MAIN, &job_process_fd);
	TEST_GT (pid, 0);

	waitpid (pid, NULL, 0);
	output = fopen (filename, "r");

	TEST_FILE_EQ (output, "0: 1 3\n");
	TEST_FILE_EQ (output, "1: 1 3\n");
	TEST_FILE_EQ (output, "2: 1 3\n");
	TEST_FILE_END (output);

	fclose (output);
	assert0 (unlink (filename));

	nih_free (class);

	/* Check that a job spawned with a log console has file descriptors:
	 *
	 * 0 bound to the /dev/null device.
	 * 1 bound to the pseudo-tty device.
	 * 2 bound to the pseudo-tty device.
	 *
	 */
	TEST_FEATURE ("with console logging");
	TEST_HASH_EMPTY (job_classes);

	sprintf (function, "%d", TEST_CONSOLE);

	class = job_class_new (NULL, "test", NULL);
	class->console = CONSOLE_LOG;
	job = job_new (class, "");

	pid = job_process_spawn_with_fd (job, args, NULL, FALSE, -1, PROCESS_MAIN, &job_process_fd);
	TEST_GT (pid, 0);

	waitpid (pid, NULL, 0);
	output = fopen (filename, "r");

	/* /dev/null */
	TEST_FILE_EQ (output, "0: 1 3\n");

	/* stdout and stderr should be bound to the same Unix98 PTY slave
	 * device (one of the char devices in range 136-143).
	 * We ignore the minor as it could be any value.
	 */
	{
		unsigned int major, saved_major;
		unsigned int unused;

		TEST_EQ (fscanf (output, "1: %u %u\n", &major, &unused), 2);
		TEST_TRUE (major >= 136 && major <= 143);
		saved_major = major;

		TEST_EQ (fscanf (output, "2: %u %u\n", &major, &unused), 2);
		TEST_TRUE (major == saved_major);
	}


	TEST_FILE_END (output);

	fclose (output);
	assert0 (unlink (filename));

	nih_free (class);


	/* Check that a job with an alternate working directory is run from
	 * that directory.
	 */
	TEST_FEATURE ("with working directory");
	TEST_HASH_EMPTY (job_classes);

	sprintf (function, "%d", TEST_PWD);

	class = job_class_new (NULL, "test", NULL);
	class->console = CONSOLE_NONE;
	class->chdir = "/tmp";
	job = job_new (class, "");

	pid = job_process_spawn_with_fd (job, args, NULL, FALSE, -1, PROCESS_MAIN, &job_process_fd);
	TEST_GT (pid, 0);

	waitpid (pid, NULL, 0);
	output = fopen (filename, "r");

	TEST_FILE_EQ (output, "wd: /tmp\n");
	TEST_FILE_END (output);

	fclose (output);
	assert0 (unlink (filename));

	nih_free (class);


	/* Check that a job is run with only the environment variables
	 * specifiec in the function call.
	 */
	TEST_FEATURE ("with environment");
	TEST_HASH_EMPTY (job_classes);

	sprintf (function, "%d", TEST_ENVIRONMENT);
	setenv ("BAR", "baz", TRUE);

	env[0] = "PATH=/bin";
	env[1] = "FOO=bar";
	env[2] = NULL;

	class = job_class_new (NULL, "test", NULL);
	class->console = CONSOLE_NONE;
	job   = job_new (class, "");

	pid = job_process_spawn_with_fd (job, args, env, FALSE, -1, PROCESS_MAIN, &job_process_fd);
	TEST_GT (pid, 0);

	waitpid (pid, NULL, 0);
	output = fopen (filename, "r");

	TEST_FILE_EQ (output, "FOO=bar\n");
	TEST_FILE_EQ (output, "PATH=/bin\n");
	TEST_FILE_EQ (output, "UPSTART_NO_SESSIONS=1\n");
	TEST_FILE_END (output);

	fclose (output);
	assert0 (unlink (filename));

	nih_free (class);


	/* Check that when we spawn an ordinary job, it isn't usually ptraced
	 * since that's a special honour reserved for daemons that we expect
	 * to fork.
	 */
	TEST_FEATURE ("with non-daemon job");
	TEST_HASH_EMPTY (job_classes);

	sprintf (function, "%d", TEST_SIMPLE);

	class = job_class_new (NULL, "test", NULL);
	class->console = CONSOLE_NONE;
	job   = job_new (class, "");

	pid = job_process_spawn_with_fd (job, args, NULL, FALSE, -1, PROCESS_MAIN, &job_process_fd);
	TEST_GT (pid, 0);

	assert0 (waitid (P_PID, pid, &info, WEXITED | WSTOPPED | WCONTINUED));
	TEST_EQ (info.si_code, CLD_EXITED);
	TEST_EQ (info.si_status, 0);

	assert0 (unlink (filename));

	nih_free (class);


	/* Check that when we spawn a daemon job, we can request that the
	 * parent be traced.
	 */
	TEST_FEATURE ("with daemon job");
	TEST_HASH_EMPTY (job_classes);

	sprintf (function, "%d", TEST_SIMPLE);

	class = job_class_new (NULL, "test", NULL);
	job   = job_new (class, "");
	class->console = CONSOLE_NONE;
	pid = job_process_spawn_with_fd (job, args, NULL, TRUE, -1, PROCESS_MAIN, &job_process_fd);
	TEST_GT (pid, 0);

	assert0 (waitid (P_PID, pid, &info, WEXITED | WSTOPPED | WCONTINUED));
	TEST_EQ (info.si_code, CLD_TRAPPED);
	TEST_EQ (info.si_status, SIGTRAP);

	assert0 (ptrace (PTRACE_DETACH, pid, NULL, 0));

	assert0 (waitid (P_PID, pid, &info, WEXITED | WSTOPPED | WCONTINUED));
	TEST_EQ (info.si_code, CLD_EXITED);
	TEST_EQ (info.si_status, 0);

	assert0 (unlink (filename));

	nih_free (class);


#if 0
	/* Check that attempting to spawn a binary that doesn't exist returns
	 * an error immediately with all of the expected information in the
	 * error structure.
	 */
	TEST_FEATURE ("with no such file");
	TEST_HASH_EMPTY (job_classes);

	args[0] = filename;
	args[1] = filename;
	args[2] = NULL;

	class = job_class_new (NULL, "test", NULL);
	class->console = CONSOLE_NONE;
	job   = job_new (class, "");

	pid = job_process_spawn_with_fd (job, args, NULL, FALSE, -1, PROCESS_MAIN, &job_process_fd);
	TEST_NE (pid, 0);

	buffer = read_from_fd (NULL, job_process_fd);
	TEST_NE_P (buffer, NULL);
	job_process_error_handler (buffer->buf, buffer->len);

	err = nih_error_get ();
	TEST_EQ (err->number, JOB_PROCESS_ERROR);
	TEST_ALLOC_SIZE (err, sizeof (JobProcessError));

	perr = (JobProcessError *)err;
	TEST_EQ (perr->type, JOB_PROCESS_ERROR_EXEC);
	TEST_EQ (perr->arg, 0);
	TEST_EQ (perr->errnum, ENOENT);
	nih_free (perr);
	nih_free (buffer);
#endif

	/************************************************************/
	TEST_FEATURE ("with no such file, no shell and console log");
	TEST_HASH_EMPTY (job_classes);

	args[0] = "does-not-exist";
	args[1] = NULL;

	class = job_class_new (NULL, "test", NULL);
	class->console = CONSOLE_LOG;
	job   = job_new (class, "");
	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	TEST_NE_P (job->log, NULL);
	TEST_EQ_P (job->log[PROCESS_MAIN], NULL);
	pid = job_process_spawn_with_fd (job, args, NULL, FALSE, -1, PROCESS_MAIN, &job_process_fd);
	job->process_data[PROCESS_MAIN] = NIH_MUST (
		job_process_data_new (job->process_data, job, PROCESS_MAIN, job_process_fd));
	TEST_WATCH_UPDATE ();
	TEST_NE (pid, 0);

	TEST_GT (waitpid (-1, NULL, 0), 0);

	NihIo *io = nih_io_reopen (job, job_process_fd, NIH_IO_STREAM, NULL, NULL, NULL, NULL);
	TEST_NE_P (io, NULL);
	buffer = read_from_fd (NULL, job_process_fd);
	TEST_NE_P (buffer, NULL);
	TEST_NE_P (job->process_data[PROCESS_MAIN], NULL);
	TEST_TRUE (job->process_data[PROCESS_MAIN]->valid);
	

	TEST_NE_P (job->log[PROCESS_MAIN], NULL);

	job_process_child_reader (job->process_data[PROCESS_MAIN], io, buffer->buf, buffer->len);

	/* The log should have been allocated in job_process_spawn,
	 * but then freed on error.
	 */
	TEST_EQ_P (job->log[PROCESS_MAIN], NULL);

	/* Check that we can spawn a job and pause it
	 */
	TEST_FEATURE ("with debug enabled");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "test", NULL);
	class->console = CONSOLE_NONE;
	class->debug = TRUE;
	job = job_new (class, "");

	sprintf (function, "%s", "/bin/true");
	args[0] = function;
	args[1] = function;
	args[2] = NULL;

	pid = job_process_spawn_with_fd (job, args, NULL, FALSE, -1, PROCESS_MAIN, &job_process_fd);
	TEST_GT (pid, 0);

	/* Ensure process is still running after some period of time.
	 *
	 * If it hasn't stopped as we expect it will certainly have finished by now,
	 * thanks to the sleep.
	 */
	sleep (1);
	assert0 (kill(pid, 0));

	TEST_GE (waitid (P_PID, pid, &info, WNOHANG | WUNTRACED), 0);
	TEST_EQ (info.si_code, CLD_STOPPED);
	TEST_EQ (info.si_status, SIGSTOP);

	assert0 (kill(pid, SIGCONT));
	waitpid (pid, &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	nih_free (class);

	/********************************************************************/
	TEST_FEATURE ("ensure sane fds with no console");
	TEST_HASH_EMPTY (job_classes);

	sprintf (function, "%d", TEST_FDS);

	args[0] = argv0;
	args[1] = function;
	args[2] = filename;
	args[3] = NULL;

	class = job_class_new (NULL, "test", NULL);
	class->console = CONSOLE_NONE;
	job = job_new (class, "");

	pid = job_process_spawn_with_fd (job, args, NULL, FALSE, -1, PROCESS_MAIN, &job_process_fd);
	TEST_GT (pid, 0);

	waitpid (pid, NULL, 0);
	TEST_EQ (stat (filename, &statbuf), 0);
	output = fopen (filename, "r");

	TEST_NE_P (output, NULL);

	{
		char  state[32];
		int   fd;
		int   ret;
		int   valid;

		while (fgets (filebuf, sizeof(filebuf), output) != NULL) {
			ret = sscanf (filebuf, "fd %d: %s ", &fd, state);
			TEST_EQ (ret, 2);

			if (! strcmp ("invalid", state))
				valid = 0;
			else
				valid = 1;

			/* 0, 1, 2 */
			if (fd < 3) {
				if (! valid)
					TEST_FAILED ("fd %d is unexpectedly invalid", fd);
			} else {
				if (valid)
					TEST_FAILED ("fd %d is unexpectedly valid", fd);
			}
		}
	}

	fclose (output);
	assert0 (unlink (filename));

	nih_free (class);

	/********************************************************************/
	TEST_FEATURE ("ensure sane fds with console log");
	TEST_HASH_EMPTY (job_classes);

	sprintf (function, "%d", TEST_FDS);

	args[0] = argv0;
	args[1] = function;
	args[2] = filename;
	args[3] = NULL;

	class = job_class_new (NULL, "test", NULL);
	class->console = CONSOLE_LOG;
	job = job_new (class, "");

	pid = job_process_spawn_with_fd (job, args, NULL, FALSE, -1, PROCESS_MAIN, &job_process_fd);
	TEST_GT (pid, 0);

	waitpid (pid, NULL, 0);
	TEST_EQ (stat (filename, &statbuf), 0);
	output = fopen (filename, "r");

	TEST_NE_P (output, NULL);

	{
		char  state[32];
		int   fd;
		int   ret;
		int   valid;

		while (fgets (filebuf, sizeof(filebuf), output) != NULL) {
			ret = sscanf (filebuf, "fd %d: %s ", &fd, state);
			TEST_EQ (ret, 2);

			if (! strcmp ("invalid", state))
				valid = 0;
			else
				valid = 1;

			/* 0, 1, 2 */
			if (fd < 3) {
				if (! valid)
					TEST_FAILED ("fd %d is unexpectedly invalid", fd);
			} else {
				if (valid)
					TEST_FAILED ("fd %d is unexpectedly valid", fd);
			}
		}
	}

	fclose (output);
	assert0 (unlink (filename));
	TEST_EQ (rmdir (dirname), 0);

	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("ensure multi process output logged");
	TEST_LIST_EMPTY (nih_io_watches);
	TEST_HASH_EMPTY (job_classes);

	TEST_FILENAME (dirname);       
	TEST_EQ (mkdir (dirname, 0755), 0);

	TEST_EQ (setenv ("UPSTART_LOGDIR", dirname, 1), 0);

	class = job_class_new (NULL, "multiproc", NULL);
	TEST_NE_P (class, NULL);

	class->console = CONSOLE_LOG;

	TEST_GT (sprintf (filename, "%s/multiproc.log", dirname), 0);
	job = job_new (class, "");
	TEST_NE_P (job, NULL);

	sprintf (function, "%d", TEST_OUTPUT_WITH_STOP);

	/* Create a temporary filename for child() output. We don't care
	 * about this file as we're interested in childs() stdout/stderr
	 * output only.
	 */
	TEST_FILENAME (filebuf);

	args[0] = argv0;
	args[1] = function;
	args[2] = filebuf;
	args[3] = NULL;

	job->pid[PROCESS_MAIN] = job_process_spawn_with_fd (job, args, NULL,
							    FALSE, -1, PROCESS_MAIN, &job_process_fd);
	pid = job->pid[PROCESS_MAIN];
	TEST_GT (pid, 0);

	/* The main process is now running, but paused. It should have
	 * produced some output so check that now.
	 */
	TEST_WATCH_UPDATE ();

	TEST_EQ (stat (filename, &statbuf), 0);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "started\r\n", TRUE);

	TEST_FILE_END (output);
	TEST_EQ (fclose (output), 0);

	sprintf (function, "%d", TEST_OUTPUT);

	args[0] = argv0;
	args[1] = function;
	args[2] = filebuf;
	args[3] = NULL;

	job->pid[PROCESS_POST_START] = job_process_spawn_with_fd (job, args, NULL,
								  FALSE, -1, PROCESS_POST_START, &job_process_fd);
	pid = job->pid[PROCESS_POST_START];
	TEST_GT (pid, 0);

	/* wait for post-start process to end */
	waitpid (pid, &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	/* ensure log written */
	nih_free (job->log[PROCESS_POST_START]);
	job->log[PROCESS_POST_START] = NULL;

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	/* from main process */
	CHECK_FILE_EQ (output, "started\r\n", TRUE);

	/* from post-start process */
	CHECK_FILE_EQ (output, "stdout\r\n", TRUE);

	/* from post-start process */
	CHECK_FILE_EQ (output, "stderr\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	pid = job->pid[PROCESS_MAIN];
	TEST_EQ (kill (pid, SIGCONT), 0);

	/* wait for main process to end */
	waitpid (pid, &status, 0);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	/* ensure log written */
	nih_free (job->log[PROCESS_MAIN]);
	job->log[PROCESS_MAIN] = NULL;

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	/* from main process */
	CHECK_FILE_EQ (output, "started\r\n", TRUE);

	/* from post-start process */
	CHECK_FILE_EQ (output, "stdout\r\n", TRUE);

	/* from post-start process */
	CHECK_FILE_EQ (output, "stderr\r\n", TRUE);

	/* from main process */
	CHECK_FILE_EQ (output, "ended\r\n", TRUE);

	TEST_FILE_END (output);
	fclose (output);

	assert0 (unlink (filebuf));
	assert0 (unlink (filename));
	TEST_EQ (rmdir (dirname), 0);

	TEST_EQ (unsetenv ("UPSTART_LOGDIR"), 0);

	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("simple test");
	TEST_HASH_EMPTY (job_classes);

	TEST_FILENAME (dirname);       
	umask(0);
	TEST_EQ (mkdir (dirname, 0755), 0);

	TEST_EQ (setenv ("UPSTART_LOGDIR", dirname, 1), 0);
	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			class = job_class_new (NULL, "simple-test", NULL);
			TEST_NE_P (class, NULL);

			job = job_new (class, "");
			TEST_NE_P (job, NULL);

			argc = 0;
			args_array = NIH_MUST (nih_str_array_new (NULL));

			TEST_FILENAME (script);
			input = fopen (script, "w");
			TEST_NE_P (input, NULL);
			TEST_GT (fprintf (input, "%s hello world\n", TEST_CMD_ECHO), 0);
			fclose (input);

			NIH_MUST (nih_str_array_add (&args_array, NULL, &argc, TEST_SHELL));
			NIH_MUST (nih_str_array_add (&args_array, NULL, &argc, TEST_SHELL_ARG));
			NIH_MUST (nih_str_array_add (&args_array, NULL, &argc, script));
		}

		pid = job_process_spawn_with_fd (job, args_array, NULL, FALSE, -1, PROCESS_MAIN, &job_process_fd);

		if (test_alloc_failed) {
			TEST_LT (pid, 0);
			err = nih_error_get ();
			TEST_NE_P (err, NULL);
			TEST_EQ (err->number, ENOMEM);
			nih_free (err);
			assert0 (unlink (script));
		} else {
			TEST_GT (pid, 0);
			TEST_EQ (waitpid (pid, &status, 0), pid);
		}

		TEST_ALLOC_SAFE {
			/* May alloc space if there is log data */
			nih_free (class);
			TEST_GT (sprintf (filename, "%s/simple-test.log", dirname), 0);
			if (!test_alloc_failed) {
				output = fopen (filename, "r");
				TEST_NE_P (output, NULL);
				CHECK_FILE_EQ (output, "hello world\r\n", TRUE);
				TEST_FILE_END (output);
				TEST_EQ (fclose (output), 0);
			}
			unlink (filename);
		}
	}

	assert0 (rmdir (dirname));

	/************************************************************/
	TEST_FEATURE ("with single-line script and 'console log'");
	TEST_HASH_EMPTY (job_classes);

	/* Check that we can spawn a job and retrieve its output.
	 */

	TEST_FILENAME (dirname);       
	umask(0);
	TEST_EQ (mkdir (dirname, 0755), 0);

	/* Override default location to ensure job output goes to a
	 * writeable location
	 */
	TEST_EQ (setenv ("UPSTART_LOGDIR", dirname, 1), 0);

	class = job_class_new (NULL, "with-single-line-script-and-console-log", NULL);
	TEST_NE_P (class, NULL);

	TEST_GT (sprintf (filename, "%s/with-single-line-script-and-console-log.log", dirname), 0);
	job = job_new (class, "");
	TEST_NE_P (job, NULL);

	argc = 0;
	args_array = NIH_MUST (nih_str_array_new (NULL));
	
	TEST_FILENAME (script);       
	input = fopen (script, "w");
	TEST_NE_P (input, NULL);
	TEST_GT (fprintf (input, "%s hello world\n", TEST_CMD_ECHO), 0);
	fclose (input);

	NIH_MUST (nih_str_array_add (&args_array, NULL, &argc, TEST_SHELL));
	NIH_MUST (nih_str_array_add (&args_array, NULL, &argc, TEST_SHELL_ARG));
	NIH_MUST (nih_str_array_add (&args_array, NULL, &argc, script));

	pid = job_process_spawn_with_fd (job, args_array, NULL, FALSE, -1, PROCESS_MAIN, &job_process_fd);
	TEST_GT (pid, 0);

	TEST_EQ (waitpid (pid, &status, 0), pid);
	TEST_TRUE (WIFEXITED (status));

	TEST_WATCH_UPDATE ();

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "hello world\r\n", TRUE);

	TEST_FILE_END (output);

	TEST_EQ (fclose (output), 0);

	assert0 (unlink (filename));
	assert0 (unlink (script));
	TEST_EQ (rmdir (dirname), 0);
	TEST_EQ (unsetenv ("UPSTART_LOGDIR"), 0);

	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with multi-line script and 'console log'");
	TEST_HASH_EMPTY (job_classes);

	/* Check that we can spawn a job and retrieve its output.
	 */
	TEST_FILENAME (dirname);       
	umask(0);
	TEST_EQ (mkdir (dirname, 0755), 0);

	TEST_EQ (setenv ("UPSTART_LOGDIR", dirname, 1), 0);

	class = job_class_new (NULL, "with-multi-line-script-and-console-log", NULL);
	TEST_NE_P (class, NULL);

	TEST_GT (sprintf (filename, "%s/with-multi-line-script-and-console-log.log", dirname), 0);
	job = job_new (class, "");
	TEST_NE_P (job, NULL);

	argc = 0;
	args_array = NIH_MUST (nih_str_array_new (NULL));
	
	TEST_FILENAME (script);       
	input = fopen (script, "w");
	TEST_NE_P (input, NULL);
	TEST_GT (fprintf (input, "/bin/true\n%s hello world\n", TEST_CMD_ECHO), 0);
	fclose (input);

	NIH_MUST (nih_str_array_add (&args_array, NULL, &argc, TEST_SHELL));
	NIH_MUST (nih_str_array_add (&args_array, NULL, &argc, TEST_SHELL_ARG));
	NIH_MUST (nih_str_array_add (&args_array, NULL, &argc, script));

	pid = job_process_spawn_with_fd (job, args_array, NULL, FALSE, -1, PROCESS_MAIN, &job_process_fd);
	TEST_GT (pid, 0);

	TEST_EQ (waitpid (pid, &status, 0), pid);
	TEST_TRUE (WIFEXITED (status));

	TEST_WATCH_UPDATE ();

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "hello world\r\n", TRUE);

	TEST_FILE_END (output);

	TEST_EQ (fclose (output), 0);

	assert0 (unlink (filename));
	assert0 (unlink (script));

	TEST_EQ (rmdir (dirname), 0);
	TEST_EQ (unsetenv ("UPSTART_LOGDIR"), 0);

	nih_free (job);

	/************************************************************/
	TEST_FEATURE ("read single null byte with 'console log'");
	TEST_HASH_EMPTY (job_classes);

	/* Check that we can spawn a job and read a single byte written
	 * to stdout.
	 */

	TEST_FILENAME (dirname);       
	umask(0);
	TEST_EQ (mkdir (dirname, 0755), 0);

	TEST_EQ (setenv ("UPSTART_LOGDIR", dirname, 1), 0);

	class = job_class_new (NULL, "read-single-null-bytes-with-console-log", NULL);
	TEST_NE_P (class, NULL);

	TEST_GT (sprintf (filename, "%s/read-single-null-bytes-with-console-log.log", dirname), 0);
	job = job_new (class, "");
	TEST_NE_P (job, NULL);

	argc = 0;
	args_array = NIH_MUST (nih_str_array_new (NULL));

	NIH_MUST (nih_str_array_add (&args_array, NULL, &argc, TEST_CMD_ECHO));
	NIH_MUST (nih_str_array_add (&args_array, NULL, &argc, "-en"));
	NIH_MUST (nih_str_array_add (&args_array, NULL, &argc, "\\000"));

	pid = job_process_spawn_with_fd (job, args_array, NULL, FALSE, -1, PROCESS_MAIN, &job_process_fd);
	TEST_GT (pid, 0);

	TEST_EQ (waitpid (pid, &status, 0), pid);
	TEST_TRUE (WIFEXITED (status));

	ret = log_handle_unflushed (job->log, job->log[PROCESS_MAIN]);
	TEST_EQ (ret, 1);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	TEST_NE_P (fgets (filebuf, sizeof(filebuf), output), NULL);
	TEST_EQ (memcmp (filebuf, "\000", 1), 0);
	TEST_FILE_END (output);

	TEST_EQ (fclose (output), 0);

	assert0 (unlink (filename));

	TEST_EQ (rmdir (dirname), 0);
	TEST_EQ (unsetenv ("UPSTART_LOGDIR"), 0);

	nih_free (job);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("read data from forked process");
	TEST_HASH_EMPTY (job_classes);

	TEST_FILENAME (dirname);
	umask(0);
	TEST_EQ (mkdir (dirname, 0755), 0);

	TEST_EQ (setenv ("UPSTART_LOGDIR", dirname, 1), 0);

	class = job_class_new (NULL, "read-data-from-forked-process", NULL);
	TEST_NE_P (class, NULL);

	TEST_GT (sprintf (filename, "%s/read-data-from-forked-process.log", dirname), 0);
	job = job_new (class, "");
	TEST_NE_P (job, NULL);

	sprintf (function, "%d", TEST_OUTPUT);

	/* fork */
	sprintf (filebuf, "%d", 1);
	TEST_FILENAME (script);

	args[0] = argv0;
	args[1] = function;
	args[2] = script;
	args[3] = filebuf;
	args[4] = NULL;

	pid = job_process_spawn_with_fd (job, args, NULL, FALSE, -1, PROCESS_MAIN, &job_process_fd);
	TEST_GT (pid, 0);

	TEST_NE (waitpid (pid, &status, 0), -1);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	ret = log_handle_unflushed (job->log, job->log[PROCESS_MAIN]);
	TEST_EQ (ret, 1);

	TEST_WATCH_UPDATE ();

	/* This will eventually call the log destructor */
	nih_free (class);

	TEST_LIST_EMPTY (nih_io_watches);

	TEST_EQ (stat (filename, &statbuf), 0);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "stdout\r\n", FALSE);
	CHECK_FILE_EQ (output, "stderr\r\n", FALSE);

	TEST_FILE_END (output);

	TEST_EQ (fclose (output), 0);

	assert0 (unlink (filename));

	TEST_EQ (rmdir (dirname), 0);
	TEST_EQ (unsetenv ("UPSTART_LOGDIR"), 0);

	/************************************************************/
	TEST_FEATURE ("read data from daemon process");
	TEST_HASH_EMPTY (job_classes);

	TEST_FILENAME (dirname);       
	umask(0);
	TEST_EQ (mkdir (dirname, 0755), 0);

	TEST_EQ (setenv ("UPSTART_LOGDIR", dirname, 1), 0);

	class = job_class_new (NULL, "test", NULL);
	TEST_NE_P (class, NULL);

	TEST_GT (sprintf (filename, "%s/test.log", dirname), 0);
	job = job_new (class, "");
	TEST_NE_P (job, NULL);

	sprintf (function, "%d", TEST_OUTPUT);

	/* daemonize */
	sprintf (filebuf, "%d", 2);
	TEST_FILENAME (script);

	args[0] = argv0;
	args[1] = function;
	args[2] = script;
	args[3] = filebuf;
	args[4] = NULL;

	pid = job_process_spawn_with_fd (job, args, NULL, FALSE, -1, PROCESS_MAIN, &job_process_fd);
	TEST_GT (pid, 0);

	TEST_WATCH_UPDATE ();

	TEST_EQ (waitpid (pid, &status, 0), pid);
	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 0);

	/* This will eventually call the log destructor */
	nih_free (class);

	output = fopen (filename, "r");
	TEST_NE_P (output, NULL);

	CHECK_FILE_EQ (output, "stdout\r\n", FALSE);
	CHECK_FILE_EQ (output, "stderr\r\n", FALSE);

	TEST_FILE_END (output);

	TEST_EQ (fclose (output), 0);

	assert0 (unlink (filename));

	TEST_EQ (rmdir (dirname), 0);
	TEST_EQ (unsetenv ("UPSTART_LOGDIR"), 0);

	/* FIXME */
#if 0
	/************************************************************/
	TEST_FEATURE ("when no free ptys");
	TEST_HASH_EMPTY (job_classes);
	{
		int            available_ptys;
		int            ret;
		struct rlimit  rlimit;

		TEST_FILENAME (dirname);       
		umask(0);
		TEST_EQ (mkdir (dirname, 0755), 0);

		TEST_EQ (setenv ("UPSTART_LOGDIR", dirname, 1), 0);

		class = job_class_new (NULL, "test", NULL);
		TEST_NE_P (class, NULL);
		TEST_EQ (class->console, CONSOLE_LOG);

		TEST_GT (sprintf (filename, "%s/test.log", dirname), 0);
		job = job_new (class, "");
		TEST_NE_P (job, NULL);

		available_ptys = get_available_pty_count ();
		TEST_GT (available_ptys, 1);
		
		TEST_EQ (getrlimit (RLIMIT_NOFILE, &rlimit), 0);
		
		if ((unsigned int)rlimit.rlim_cur <= (unsigned int)available_ptys) {
			/* Since we do not run as root, we are unable to
			 * raise our limit to allow us to consume all
			 * remaining ptys.
			 */
			printf ("WARNING:\n");
			printf ("WARNING: Test not run as insufficient files available\n");
			printf ("WARNING: (%u available files for uid %d, need atleast %u)\n",
					 (unsigned int)rlimit.rlim_cur,
					 (int)getuid (),
					 (unsigned int)available_ptys);
			printf ("WARNING:\n");
			printf ("WARNING: See limits(5).\n");
			printf ("WARNING:\n");
		} else {
			/* Consume all free ptys */
			{
				int pty;

				for (pty = 0; pty < available_ptys; ++pty) {
					ret = posix_openpt (O_RDWR | O_NOCTTY);
					if (ret < 0)
						break;
				}
			}

			pid = job_process_spawn_with_fd (job, args, NULL, FALSE, -1, PROCESS_MAIN, &job_process_fd);
			TEST_WATCH_UPDATE ();
			TEST_NE (pid, 0);

			buffer = read_from_fd (NULL, job_process_fd);
			TEST_NE_P (buffer, NULL);
			job_process_error_handler (buffer->buf, buffer->len);

			/* Ensure logging disabled in failure scenarios */
			TEST_EQ (class->console, CONSOLE_NONE);

			err = nih_error_get ();
			TEST_EQ (err->number, ENOMEM);
			nih_free (err);
		}
		nih_free (class);
	}
	assert0 (rmdir (dirname));
#else
		/* FIXME */
		TEST_FEATURE ("WARNING: FIXME: test 'when no free ptys' disabled due to kernel bug");
#endif

	TEST_EQ (unsetenv ("UPSTART_LOGDIR"), 0);
}

void
test_log_path (void)
{
	JobClass        *class = NULL;
	Job             *job = NULL;
	nih_local char  *log_path = NULL;
	nih_local char  *expected = NULL;
	nih_local char  *home = NULL;
	char             dirname[PATH_MAX];

	TEST_FILENAME (dirname);       

	TEST_FUNCTION ("job_process_log_path");

	/************************************************************/
	TEST_FEATURE ("with system job with simple name");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "system", NULL);
	TEST_NE_P (class, NULL);
	job = job_new (class, "");
	TEST_NE_P (job, NULL);

	log_path = job_process_log_path (job, FALSE);
	TEST_NE_P (log_path, NULL);

	expected = NIH_MUST (nih_sprintf (NULL, "%s/%s.log",
				EXPECTED_JOB_LOGDIR, "system"));
	TEST_EQ_STR (log_path, expected);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with system job containing illegal path characters");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "//hello_foo bar.z/", NULL);
	TEST_NE_P (class, NULL);
	job = job_new (class, "");
	TEST_NE_P (job, NULL);

	log_path = job_process_log_path (job, FALSE);
	TEST_NE_P (log_path, NULL);

	expected = NIH_MUST (nih_sprintf (NULL, "%s/%s.log",
				EXPECTED_JOB_LOGDIR, "__hello_foo bar.z_"));
	TEST_EQ_STR (log_path, expected);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with system job with named instance");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "foo bar", NULL);
	TEST_NE_P (class, NULL);
	job = job_new (class, "bar foo");
	TEST_NE_P (job, NULL);

	log_path = job_process_log_path (job, FALSE);
	TEST_NE_P (log_path, NULL);

	expected = NIH_MUST (nih_sprintf (NULL, "%s/%s.log",
				EXPECTED_JOB_LOGDIR, "foo bar-bar foo"));
	TEST_EQ_STR (log_path, expected);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with system job with named instance and illegal path characters");
	TEST_HASH_EMPTY (job_classes);

	class = job_class_new (NULL, "a/b", NULL);
	TEST_NE_P (class, NULL);
	job = job_new (class, "c/d_?/");
	TEST_NE_P (job, NULL);

	log_path = job_process_log_path (job, FALSE);
	TEST_NE_P (log_path, NULL);

	expected = NIH_MUST (nih_sprintf (NULL, "%s/%s.log",
				EXPECTED_JOB_LOGDIR, "a_b-c_d_?_"));
	TEST_EQ_STR (log_path, expected);
	nih_free (class);

	/************************************************************/
	TEST_FEATURE ("with subverted logdir and system job with named instance and illegal path characters");
	TEST_HASH_EMPTY (job_classes);

	TEST_EQ (setenv ("UPSTART_LOGDIR", dirname, 1), 0);

	class = job_class_new (NULL, "a/b", NULL);
	TEST_NE_P (class, NULL);
	job = job_new (class, "c/d_?/");
	TEST_NE_P (job, NULL);

	log_path = job_process_log_path (job, FALSE);
	TEST_NE_P (log_path, NULL);

	expected = NIH_MUST (nih_sprintf (NULL, "%s/%s.log",
				dirname, "a_b-c_d_?_"));
	TEST_EQ_STR (log_path, expected);
	nih_free (class);

	TEST_EQ (unsetenv ("UPSTART_LOGDIR"), 0);
	TEST_HASH_EMPTY (job_classes);
}


void
test_kill (void)
{
	JobClass *      class;
	Job *           job = NULL;
	NihTimer *      timer;
	struct timespec now;
	pid_t           pid;
	int             status;

	TEST_FUNCTION ("job_process_kill");
	nih_timer_init ();
	event_init ();

	class = job_class_new (NULL, "test", NULL);
	class->kill_timeout = 1000;

	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = nih_strdup (
		class->process[PROCESS_MAIN], "echo");


	/* Check that an easily killed process goes away with just a single
	 * call to job_process_kill, having received the TERM signal.
	 * A kill timer should be set to handle the case where the child
	 * doesn't get reaped.
	 */
	TEST_FEATURE ("with easily killed process");
	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");
		}

		job->goal = JOB_STOP;
		job->state = JOB_KILLED;
		TEST_CHILD (job->pid[PROCESS_MAIN]) {
			pause ();
		}
		pid = job->pid[PROCESS_MAIN];
		setpgid (pid, pid);

		job_process_kill (job, PROCESS_MAIN);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_KILLED);
		TEST_EQ (job->pid[PROCESS_MAIN], pid);

		waitpid (job->pid[PROCESS_MAIN], &status, 0);
		TEST_TRUE (WIFSIGNALED (status));
		TEST_EQ (WTERMSIG (status), SIGTERM);

		assert0 (clock_gettime (CLOCK_MONOTONIC, &now));

		TEST_NE_P (job->kill_timer, NULL);
		TEST_ALLOC_SIZE (job->kill_timer, sizeof (NihTimer));
		TEST_ALLOC_PARENT (job->kill_timer, job);
		TEST_GE (job->kill_timer->due, now.tv_sec + 950);
		TEST_LE (job->kill_timer->due, now.tv_sec + 1000);

		TEST_EQ (job->kill_process, PROCESS_MAIN);

		nih_free (job->kill_timer);
		job->kill_timer = NULL;
		job->kill_process = PROCESS_INVALID;

		nih_free (job);

		event_poll ();
	}


	/* Check that a process that's hard to kill doesn't go away, but
	 * that the kill timer sends the KILL signal which should finally
	 * get rid of it.
	 */
	TEST_FEATURE ("with hard to kill process");
	TEST_ALLOC_FAIL {
		int wait_fd = 0;

		TEST_ALLOC_SAFE {
			job = job_new (class, "");
		}

		job->goal = JOB_STOP;
		job->state = JOB_KILLED;
		TEST_CHILD_WAIT (job->pid[PROCESS_MAIN], wait_fd) {
			struct sigaction act;

			act.sa_handler = SIG_IGN;
			act.sa_flags = 0;
			sigemptyset (&act.sa_mask);
			sigaction (SIGTERM, &act, NULL);

			TEST_CHILD_RELEASE (wait_fd);

			for (;;)
				pause ();
		}
		pid = job->pid[PROCESS_MAIN];
		setpgid (pid, pid);

		job_process_kill (job, PROCESS_MAIN);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_KILLED);
		TEST_EQ (job->pid[PROCESS_MAIN], pid);

		TEST_EQ (kill (job->pid[PROCESS_MAIN], 0), 0);

		assert0 (clock_gettime (CLOCK_MONOTONIC, &now));

		TEST_NE_P (job->kill_timer, NULL);
		TEST_ALLOC_SIZE (job->kill_timer, sizeof (NihTimer));
		TEST_ALLOC_PARENT (job->kill_timer, job);
		TEST_GE (job->kill_timer->due, now.tv_sec + 950);
		TEST_LE (job->kill_timer->due, now.tv_sec + 1000);

		TEST_EQ (job->kill_process, PROCESS_MAIN);

		/* Run the kill timer */
		timer = job->kill_timer;
		timer->callback (timer->data, timer);
		nih_free (timer);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_KILLED);
		TEST_EQ (job->pid[PROCESS_MAIN], pid);

		waitpid (job->pid[PROCESS_MAIN], &status, 0);
		TEST_TRUE (WIFSIGNALED (status));
		TEST_EQ (WTERMSIG (status), SIGKILL);

		TEST_EQ_P (job->kill_timer, NULL);
		TEST_EQ (job->kill_process, PROCESS_INVALID);

		nih_free (job);

		event_poll ();
	}

	nih_free (class);
}


void
test_handler (void)
{
	ConfSource *    source;
	ConfFile *      file;
	JobClass *      class;
	Job *           job = NULL;
	Blocked *       blocked = NULL;
	Event *         event;
	Event *         bevent = NULL;
	FILE *          output;
	int             exitcodes[2] = { 100, SIGINT << 8 };
	int             status;
	pid_t           pid;
	siginfo_t       info;
	unsigned long   data;
	struct timespec now;
	char            dirname[PATH_MAX];
	nih_local char *logfile = NULL;
	int             fds[2] = { -1, -1};
	NihIo          *io = NULL;
	nih_local NihIoBuffer    *buffer= NULL;

	TEST_FILENAME (dirname);       
	TEST_EQ (mkdir (dirname, 0755), 0);
	TEST_EQ (setenv ("UPSTART_LOGDIR", dirname, 1), 0);

	logfile = NIH_MUST (nih_sprintf (NULL, "%s/%s.log",
				dirname, "test"));

	TEST_FUNCTION ("job_process_handler");
	program_name = "test";
	output = tmpfile ();

	source = conf_source_new (NULL, "/tmp", CONF_JOB_DIR);
	file = conf_file_new (source, "/tmp/test");
	file->job = class = job_class_new (NULL, "test", NULL);
	TEST_NE_P (file->job, NULL);
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = "echo";

	class->start_on = event_operator_new (class, EVENT_MATCH,
					       "foo", NULL);
	class->stop_on = event_operator_new (class, EVENT_MATCH,
					      "foo", NULL);
	nih_hash_add (job_classes, &class->entry);

	event = event_new (NULL, "foo", NULL);


	/* Check that the child handler can be called with a pid that doesn't
	 * match the job, and that the job state doesn't change.
	 */
	TEST_FEATURE ("with unknown pid");
	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_RUNNING;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		job_process_handler (NULL, 999, NIH_CHILD_EXITED, 0);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_RUNNING);
		TEST_EQ (job->pid[PROCESS_MAIN], 1);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_EQ_P (job->blocker, NULL);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		nih_free (job);
	}


	/* Check that we can handle the running task of the job terminating,
	 * which should set the goal to stop and transition a state change
	 * into the stopping state.  This should not be considered a failure.
	 */
	TEST_FEATURE ("with running process");
	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_RUNNING;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		nih_free (job);
	}


	/* Check that we can handle a running task of the job after it's been
	 * sent the TERM signal and a kill timer set.  The kill timer should
	 * be cancelled and freed, and since we killed it, the job should
	 * still not be considered failed.
	 */
	TEST_FEATURE ("with kill timer");
	TEST_ALLOC_FAIL {
		NihTimer *timer = NULL;

		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_STOP;
		job->state = JOB_KILLED;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_ALLOC_SAFE {
			timer = (void *) nih_strdup (job, "test");
		}

		TEST_FREE_TAG (timer);
		job->kill_timer = timer;
		job->kill_process = PROCESS_MAIN;

		TEST_FREE_TAG (job);

		job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);

		TEST_FREE (timer);
		TEST_FREE (job);

		TEST_EQ (event->blockers, 0);
		TEST_EQ (event->failed, FALSE);

		TEST_FREE (blocked);
	}


	/* Check that if the process is restarting, and died when we killed
	 * it, the goal remains as start and a state change is still
	 * transitioned.  This should also not be considered a failure.
	 */
	TEST_FEATURE ("with restarting process");
	TEST_ALLOC_FAIL {
		NihTimer *timer = NULL;

		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_KILLED;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_ALLOC_SAFE {
			timer = (void *) nih_strdup (job, "test");
		}

		TEST_FREE_TAG (timer);
		job->kill_timer = timer;
		job->kill_process = PROCESS_MAIN;

		job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);

		TEST_FREE (timer);

		TEST_EQ_P (job->kill_timer, NULL);
		TEST_EQ (job->kill_process, PROCESS_INVALID);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_STARTING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		nih_free (job);
	}


	/* Check that we can handle the pre-start process of the job exiting,
	 * and if it terminates with a good error code, end up in the running
	 * state.
	 */
	TEST_FEATURE ("with pre-start process");
	class->process[PROCESS_PRE_START] = process_new (class);
	class->process[PROCESS_PRE_START]->command = "echo";

	assert0 (pipe (fds));
	close (fds[1]);

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);

			job->process_data[PROCESS_PRE_START] = NIH_MUST (
					job_process_data_new (job->process_data, job, PROCESS_PRE_START, fds[0]));
		}

		job->goal = JOB_START;
		job->state = JOB_PRE_START;
		job->pid[PROCESS_MAIN] = 0;
		job->pid[PROCESS_PRE_START] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);
		TEST_EQ (job->state, JOB_SPAWNED);
		job_change_state (job, job_next_state(job));

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_RUNNING);
		TEST_EQ (job->pid[PROCESS_PRE_START], 0);
		TEST_GT (job->pid[PROCESS_MAIN], 0);

		waitpid (job->pid[PROCESS_MAIN], NULL, 0);

		TEST_EQ (event->blockers, 0);
		TEST_EQ (event->failed, FALSE);

		TEST_EQ_P (job->blocker, NULL);

		TEST_LIST_EMPTY (&job->blocking);
		TEST_FREE (blocked);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		nih_free (job);
	}

	close (fds[0]);

	nih_free (class->process[PROCESS_PRE_START]);
	class->process[PROCESS_PRE_START] = NULL;

	unlink (logfile);

	/* Check that we can handle a failing pre-start process of the job,
	 * which changes the goal to stop and transitions a state change in
	 * that direction to the stopping state.  An error should be emitted
	 * and the job and event should be marked as failed.
	 */
	TEST_FEATURE ("with failed pre-start process");
	class->process[PROCESS_PRE_START] = process_new (class);
	class->process[PROCESS_PRE_START]->command = "echo";

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_PRE_START;
		job->pid[PROCESS_PRE_START] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, 1, NIH_CHILD_EXITED, 1);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_PRE_START], 0);

		TEST_EQ (event->blockers, 0);
		TEST_EQ (event->failed, TRUE);

		TEST_LIST_EMPTY (&job->blocking);
		TEST_FREE (blocked);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, TRUE);
		TEST_EQ (job->failed_process, PROCESS_PRE_START);
		TEST_EQ (job->exit_status, 1);

		TEST_FILE_EQ (output, ("test: test pre-start process (1) "
				       "terminated with status 1\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		nih_free (job);
	}

	nih_free (class->process[PROCESS_PRE_START]);
	class->process[PROCESS_PRE_START] = NULL;

	unlink (logfile);

	/* Check that we can handle a killed starting task, which should
	 * act as if it failed.  A different error should be output and
	 * the failed exit status should contain the signal and the high bit.
	 */
	TEST_FEATURE ("with killed pre-start process");
	class->process[PROCESS_PRE_START] = process_new (class);
	class->process[PROCESS_PRE_START]->command = "echo";

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_PRE_START;
		job->pid[PROCESS_PRE_START] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, 1, NIH_CHILD_KILLED, SIGTERM);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_PRE_START], 0);

		TEST_EQ (event->blockers, 0);
		TEST_EQ (event->failed, TRUE);

		TEST_LIST_EMPTY (&job->blocking);
		TEST_FREE (blocked);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, TRUE);
		TEST_EQ (job->failed_process, PROCESS_PRE_START);
		TEST_EQ (job->exit_status, SIGTERM << 8);

		TEST_FILE_EQ (output, ("test: test pre-start process (1) "
				       "killed by TERM signal\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		nih_free (job);
	}

	nih_free (class->process[PROCESS_PRE_START]);
	class->process[PROCESS_PRE_START] = NULL;

	unlink (logfile);

	/* Check that we can catch the running task of a service stopping
	 * with an error, and if the job is to be respawned, go into
	 * the stopping state but don't change the goal to stop.
	 *
	 * This should also emit a warning, but should not set the failed
	 * state since we're dealing with it.
	 */
	TEST_FEATURE ("with respawn of running service process");
	class->respawn = TRUE;
	class->respawn_limit = 5;
	class->respawn_interval = 10;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_RUNNING;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, 1, NIH_CHILD_EXITED, 1);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);

		assert0 (clock_gettime (CLOCK_MONOTONIC, &now));

		TEST_EQ (job->respawn_count, 1);
		TEST_LE (job->respawn_time, now.tv_sec);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);
		TEST_EQ (job->class->process[PROCESS_MAIN]->script, FALSE);

		TEST_FILE_EQ (output, ("test: test main process (1) "
				       "terminated with status 1\n"));
		TEST_FILE_EQ (output, ("test: test main process ended, "
				       "respawning\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		nih_free (job);
	}

	class->respawn = FALSE;


	/* Check that we can catch the running task of a service stopping
	 * with an error, and if the job is to be respawned, go into
	 * the stopping state but don't change the goal to stop.
	 *
	 * This should also emit a warning, but should not set the failed
	 * state since we're dealing with it.
	 */
	TEST_FEATURE ("with respawn of running task process");
	class->task = TRUE;
	class->respawn = TRUE;
	class->respawn_limit = 5;
	class->respawn_interval = 10;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_RUNNING;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, 1, NIH_CHILD_EXITED, 1);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);

		assert0 (clock_gettime (CLOCK_MONOTONIC, &now));

		TEST_EQ (job->respawn_count, 1);
		TEST_LE (job->respawn_time, now.tv_sec);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);
		TEST_EQ (job->class->process[PROCESS_MAIN]->script, FALSE);

		TEST_FILE_EQ (output, ("test: test main process (1) "
				       "terminated with status 1\n"));
		TEST_FILE_EQ (output, ("test: test main process ended, "
				       "respawning\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		nih_free (job);
	}

	class->respawn = FALSE;
	class->task = FALSE;


	/* Check that if the process has been respawned too many times
	 * recently, the goal is changed to stop and the process moved into
	 * the stopping state.
	 */
	TEST_FEATURE ("with too many respawns of running process");
	class->respawn = TRUE;
	class->respawn_limit = 5;
	class->respawn_interval = 10;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);

			assert0 (clock_gettime (CLOCK_MONOTONIC, &now));

			job->respawn_count = 5;
			job->respawn_time = now.tv_sec - 5;
		}

		job->goal = JOB_START;
		job->state = JOB_RUNNING;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);

		TEST_EQ (job->respawn_count, 6);

		TEST_EQ (event->blockers, 0);
		TEST_EQ (event->failed, TRUE);

		TEST_LIST_EMPTY (&job->blocking);
		TEST_FREE (blocked);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, TRUE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);
		TEST_EQ (job->class->process[PROCESS_MAIN]->script, FALSE);

		TEST_FILE_EQ (output, ("test: test respawning too fast, "
				       "stopped\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		nih_free (job);
	}

	class->respawn = FALSE;


	/* Check that we can catch a running task exiting with a "normal"
	 * exit code, and even if it's marked respawn, set the goal to
	 * stop and transition into the stopping state.
	 */
	TEST_FEATURE ("with normal exit of running respawn process");
	class->respawn = TRUE;
	class->normalexit = exitcodes;
	class->normalexit_len = 1;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_RUNNING;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		job_process_handler (NULL, 1, NIH_CHILD_EXITED, 100);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);
		TEST_EQ (job->class->process[PROCESS_MAIN]->script, FALSE);

		nih_free (job);
	}

	class->respawn = FALSE;
	class->normalexit = NULL;
	class->normalexit_len = 0;


	/* Check that a zero exit is not considered normal for a service
	 * by default.
	 */
	TEST_FEATURE ("with respawn of service process and zero exit code");
	class->respawn = TRUE;
	class->respawn_limit = 5;
	class->respawn_interval = 10;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_RUNNING;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);

		assert0 (clock_gettime (CLOCK_MONOTONIC, &now));

		TEST_EQ (job->respawn_count, 1);
		TEST_LE (job->respawn_time, now.tv_sec);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);
		TEST_EQ (job->class->process[PROCESS_MAIN]->script, FALSE);

		TEST_FILE_EQ (output, ("test: test main process ended, "
				       "respawning\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		nih_free (job);
	}

	class->respawn = FALSE;


	/* Check that zero is considered a normal exit code for a task.
	 */
	TEST_FEATURE ("with respawn of task process and zero exit code");
	class->task = TRUE;
	class->respawn = TRUE;
	class->respawn_limit = 5;
	class->respawn_interval = 10;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_RUNNING;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);
		TEST_EQ (job->class->process[PROCESS_MAIN]->script, FALSE);

		nih_free (job);
	}

	class->respawn = FALSE;
	class->task = FALSE;


	/* Check that a running task that fails with an exit status not
	 * listed in normalexit causes the job to be marked as failed.
	 */
	TEST_FEATURE ("with abnormal exit of running process");
	class->normalexit = exitcodes;
	class->normalexit_len = 2;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_RUNNING;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, 1, NIH_CHILD_EXITED, 99);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);

		TEST_EQ (event->blockers, 0);
		TEST_EQ (event->failed, TRUE);

		TEST_LIST_EMPTY (&job->blocking);
		TEST_FREE (blocked);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, TRUE);
		TEST_EQ (job->failed_process, PROCESS_MAIN);
		TEST_EQ (job->exit_status, 99);

		TEST_FILE_EQ (output, ("test: test main process (1) "
				       "terminated with status 99\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		nih_free (job);
	}

	class->normalexit = NULL;
	class->normalexit_len = 0;


	/* Check that a running task that fails doesn't mark the job or
	 * event as failed if the goal was already to stop the job (since
	 * it's probably failed because of the TERM or KILL signal).
	 */
	TEST_FEATURE ("with killed running process");
	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_STOP;
		job->state = JOB_KILLED;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_FREE_TAG (job);

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, 1, NIH_CHILD_KILLED, SIGTERM);
		}
		rewind (output);

		TEST_FREE (job);

		TEST_EQ (event->blockers, 0);
		TEST_EQ (event->failed, FALSE);

		TEST_FREE (blocked);

		TEST_FILE_EQ (output, ("test: test main process (1) "
				       "killed by TERM signal\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);
	}


	/* Check that a running task that fails with an exit status
	 * listed in normalexit does not cause the job to be marked as
	 * failed, but instead just stops it normally.
	 */
	TEST_FEATURE ("with normal exit of running process");
	class->normalexit = exitcodes;
	class->normalexit_len = 2;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_RUNNING;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		job_process_handler (NULL, 1, NIH_CHILD_EXITED, 100);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		nih_free (job);
	}

	class->normalexit = NULL;
	class->normalexit_len = 0;


	/* Check that a running task that fails with an signal
	 * listed in normalexit does not cause the job to be marked as
	 * failed, but instead just stops it normally.
	 */
	TEST_FEATURE ("with normal signal killed running process");
	class->normalexit = exitcodes;
	class->normalexit_len = 2;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_RUNNING;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, 1, NIH_CHILD_KILLED, SIGINT);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		TEST_FILE_EQ (output, ("test: test main process (1) "
				       "killed by INT signal\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		nih_free (job);
	}

	class->normalexit = NULL;
	class->normalexit_len = 0;


	/* A running task exiting with the zero exit code is considered
	 * a normal termination if not marked respawn.
	 */
	TEST_FEATURE ("with running task and zero exit");
	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_RUNNING;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		nih_free (job);
	}


	/* Check that we can handle the post-stop process of the job exiting,
	 * and end up in the waiting state.
	 */
	TEST_FEATURE ("with post-stop process");
	class->process[PROCESS_POST_STOP] = process_new (class);
	class->process[PROCESS_POST_STOP]->command = "echo";

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_STOP;
		job->state = JOB_POST_STOP;
		job->pid[PROCESS_POST_STOP] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_FREE_TAG (job);

		job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);

		TEST_FREE (job);

		TEST_EQ (event->blockers, 0);
		TEST_EQ (event->failed, FALSE);

		TEST_FREE (blocked);
	}

	nih_free (class->process[PROCESS_POST_STOP]);
	class->process[PROCESS_POST_STOP] = NULL;


	/* Check that we can handle a failing post-stop process of the job,
	 * which should get marked as failed if the job hasn't been already.
	 */
	TEST_FEATURE ("with failed post-stop process");
	class->process[PROCESS_POST_STOP] = process_new (class);
	class->process[PROCESS_POST_STOP]->command = "echo";

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_STOP;
		job->state = JOB_POST_STOP;
		job->pid[PROCESS_POST_STOP] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_FREE_TAG (job);

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, 1, NIH_CHILD_EXITED, 1);
		}
		rewind (output);

		TEST_FREE (job);

		TEST_EQ (event->blockers, 0);
		TEST_EQ (event->failed, TRUE);

		TEST_FREE (blocked);

		TEST_FILE_EQ (output, ("test: test post-stop process (1) "
				       "terminated with status 1\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);
	}

	nih_free (class->process[PROCESS_POST_STOP]);
	class->process[PROCESS_POST_STOP] = NULL;


	/* Check that a failing stopping task doesn't overwrite the record
	 * of a failing earlier task.
	 */
	TEST_FEATURE ("with stopping task failure after failure");
	class->process[PROCESS_POST_STOP] = process_new (class);
	class->process[PROCESS_POST_STOP]->command = "echo";

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_STOP;
		job->state = JOB_POST_STOP;
		job->pid[PROCESS_POST_STOP] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = TRUE;

		job->failed = TRUE;
		job->failed_process = PROCESS_MAIN;
		job->exit_status = SIGSEGV << 8;

		TEST_FREE_TAG (job);

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, 1, NIH_CHILD_EXITED, 1);
		}
		rewind (output);

		TEST_FREE (job);

		TEST_EQ (event->blockers, 0);
		TEST_EQ (event->failed, TRUE);

		TEST_FREE (blocked);

		TEST_FILE_EQ (output, ("test: test post-stop process (1) "
				       "terminated with status 1\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);
	}

	nih_free (class->process[PROCESS_POST_STOP]);
	class->process[PROCESS_POST_STOP] = NULL;


	/* Check that we can handle the post-start task of the job exiting,
	 * the exit status should be ignored and the job transitioned into
	 * the running state.  The pid of the job shouldn't be cleared,
	 * but the aux pid should be.
	 */
	TEST_FEATURE ("with post-start process");
	class->process[PROCESS_POST_START] = process_new (class);
	class->process[PROCESS_POST_START]->command = "echo";

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_POST_START;
		job->pid[PROCESS_MAIN] = 1;
		job->pid[PROCESS_POST_START] = 2;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, 2, NIH_CHILD_EXITED, 1);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_RUNNING);
		TEST_EQ (job->pid[PROCESS_MAIN], 1);
		TEST_EQ (job->pid[PROCESS_POST_START], 0);

		TEST_EQ (event->blockers, 0);
		TEST_EQ (event->failed, FALSE);

		TEST_EQ_P (job->blocker, NULL);

		TEST_LIST_EMPTY (&job->blocking);
		TEST_FREE (blocked);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		TEST_FILE_EQ (output, ("test: test post-start process (2) "
				       "terminated with status 1\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		nih_free (job);
	}

	nih_free (class->process[PROCESS_POST_START]);
	class->process[PROCESS_POST_START] = NULL;


	/* Check that we can handle the running task of the job exiting, even
	 * if it dies during the post-start state, which should set the goal to
	 * stop and transition a state change into the stopping state.
	 */
	TEST_FEATURE ("with running process in post-start state");
	class->process[PROCESS_POST_START] = process_new (class);
	class->process[PROCESS_POST_START]->command = "echo";

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_POST_START;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		nih_free (job);
	}

	nih_free (class->process[PROCESS_POST_START]);
	class->process[PROCESS_POST_START] = NULL;


	/* Check that we can handle the running task of the job exiting while
	 * there is a post-start script running; this should only set the goal
	 * to stop since we also have to wait for the post-start script to
	 * stop.
	 */
	TEST_FEATURE ("with running process while post-start running");
	class->process[PROCESS_POST_START] = process_new (class);
	class->process[PROCESS_POST_START]->command = "echo";

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_POST_START;
		job->pid[PROCESS_MAIN] = 1;
		job->pid[PROCESS_POST_START] = 2;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_POST_START);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);
		TEST_EQ (job->pid[PROCESS_POST_START], 2);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_EQ_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		nih_free (job);
	}

	nih_free (class->process[PROCESS_POST_START]);
	class->process[PROCESS_POST_START] = NULL;


	/* Check that we can handle the running process exiting before the
	 * post-start process finishes.  This should mark the job to be
	 * stopped, but not change the state, handling the post-start process
	 * exiting afterwards should change the state.
	 */
	TEST_FEATURE ("with running then post-start process");
	class->process[PROCESS_POST_START] = process_new (class);
	class->process[PROCESS_POST_START]->command = "echo";

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_POST_START;
		job->pid[PROCESS_MAIN] = 1;
		job->pid[PROCESS_POST_START] = 2;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_POST_START);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);
		TEST_EQ (job->pid[PROCESS_POST_START], 2);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_EQ_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		job_process_handler (NULL, 2, NIH_CHILD_EXITED, 0);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);
		TEST_EQ (job->pid[PROCESS_POST_START], 0);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		nih_free (job);
	}

	nih_free (class->process[PROCESS_POST_START]);
	class->process[PROCESS_POST_START] = NULL;


	/* Check that we can handle a failed running process before the
	 * post-start process finishes.  This should mark the job to be
	 * stopped, but not change the state, then handling the post-start
	 * process exiting afterwards should change the state.
	 */
	TEST_FEATURE ("with failed running then post-start process");
	class->process[PROCESS_POST_START] = process_new (class);
	class->process[PROCESS_POST_START]->command = "echo";

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_POST_START;
		job->pid[PROCESS_MAIN] = 1;
		job->pid[PROCESS_POST_START] = 2;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, 1, NIH_CHILD_KILLED, SIGSEGV);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_POST_START);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);
		TEST_EQ (job->pid[PROCESS_POST_START], 2);

		TEST_EQ (event->blockers, 0);
		TEST_EQ (event->failed, TRUE);

		TEST_EQ_P (job->blocker, NULL);

		TEST_LIST_EMPTY (&job->blocking);
		TEST_FREE (blocked);

		TEST_EQ (job->failed, TRUE);
		TEST_EQ (job->failed_process, PROCESS_MAIN);
		TEST_EQ (job->exit_status, SIGSEGV << 8);

		TEST_FILE_EQ (output, ("test: test main process (1) "
				       "killed by SEGV signal\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		job_process_handler (NULL, 2, NIH_CHILD_EXITED, 0);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);
		TEST_EQ (job->pid[PROCESS_POST_START], 0);

		TEST_EQ (event->blockers, 0);
		TEST_EQ (event->failed, TRUE);

		TEST_LIST_EMPTY (&job->blocking);
		TEST_FREE (blocked);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, TRUE);
		TEST_EQ (job->failed_process, PROCESS_MAIN);
		TEST_EQ (job->exit_status, SIGSEGV << 8);

		nih_free (job);
	}

	nih_free (class->process[PROCESS_POST_START]);
	class->process[PROCESS_POST_START] = NULL;


	/* Check that we can handle the running process of a respawn job
	 * exiting before the post-start process finishes.  This should
	 * mark the job to be respawned when the post-start script finishes
	 * instead of making any state change.
	 */
	TEST_FEATURE ("with respawn of running while post-start process");
	class->respawn = TRUE;
	class->respawn_limit = 5;
	class->respawn_interval = 10;

	class->process[PROCESS_POST_START] = process_new (class);
	class->process[PROCESS_POST_START]->command = "echo";

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_POST_START;
		job->pid[PROCESS_MAIN] = 1;
		job->pid[PROCESS_POST_START] = 2;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_RESPAWN);
		TEST_EQ (job->state, JOB_POST_START);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);
		TEST_EQ (job->pid[PROCESS_POST_START], 2);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_EQ_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		job_process_handler (NULL, 2, NIH_CHILD_EXITED, 0);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);
		TEST_EQ (job->pid[PROCESS_POST_START], 0);

		assert0 (clock_gettime (CLOCK_MONOTONIC, &now));

		TEST_EQ (job->respawn_count, 1);
		TEST_LE (job->respawn_time, now.tv_sec);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);
		TEST_EQ (job->class->process[PROCESS_MAIN]->script, FALSE);

		TEST_FILE_EQ (output, ("test: test main process ended, "
				       "respawning\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		nih_free (job);
	}

	nih_free (class->process[PROCESS_POST_START]);
	class->process[PROCESS_POST_START] = NULL;

	class->respawn = FALSE;


	/* Check that we can handle the pre-stop task of the job exiting, the
	 * exit status should be ignored and the job transitioned into
	 * the stopping state.  The pid of the job shouldn't be cleared,
	 * but the aux pid should be.
	 */
	TEST_FEATURE ("with pre-stop process");
	class->process[PROCESS_PRE_STOP] = process_new (class);
	class->process[PROCESS_PRE_STOP]->command = "echo";

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_STOP;
		job->state = JOB_PRE_STOP;
		job->pid[PROCESS_MAIN] = 1;
		job->pid[PROCESS_PRE_STOP] = 2;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, 2, NIH_CHILD_EXITED, 1);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 1);
		TEST_EQ (job->pid[PROCESS_PRE_STOP], 0);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		TEST_FILE_EQ (output, ("test: test pre-stop process (2) "
				       "terminated with status 1\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		nih_free (job);
	}

	nih_free (class->process[PROCESS_PRE_STOP]);
	class->process[PROCESS_PRE_STOP] = NULL;


	/* Check that we can handle the running task of the job exiting, even
	 * if it dies during the pre-stop state, which transition a state
	 * change into the stopping state.
	 */
	TEST_FEATURE ("with running process in pre-stop state");
	class->process[PROCESS_PRE_STOP] = process_new (class);
	class->process[PROCESS_PRE_STOP]->command = "echo";

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_STOP;
		job->state = JOB_PRE_STOP;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		nih_free (job);
	}

	nih_free (class->process[PROCESS_PRE_STOP]);
	class->process[PROCESS_PRE_STOP] = NULL;


	/* Check that we can handle the running task of the job exiting while
	 * there is a pre-stop script running; this should have no other effect
	 * since we also have to wait for the pre-stop script to stop.
	 */
	TEST_FEATURE ("with running process while pre-stop running");
	class->process[PROCESS_PRE_STOP] = process_new (class);
	class->process[PROCESS_PRE_STOP]->command = "echo";

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_STOP;
		job->state = JOB_PRE_STOP;
		job->pid[PROCESS_MAIN] = 1;
		job->pid[PROCESS_PRE_STOP] = 2;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_PRE_STOP);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);
		TEST_EQ (job->pid[PROCESS_PRE_STOP], 2);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_EQ_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		nih_free (job);
	}

	nih_free (class->process[PROCESS_PRE_STOP]);
	class->process[PROCESS_PRE_STOP] = NULL;


	/* Check that we can handle the running process of a respawn job
	 * exiting before the pre-stop process finishes.  This should
	 * mark the job to be respawned when the pre-stop script finishes
	 * instead of making any state change.
	 */
	TEST_FEATURE ("with respawn of running while pre-stop process");
	class->respawn = TRUE;
	class->respawn_limit = 5;
	class->respawn_interval = 10;

	class->process[PROCESS_PRE_STOP] = process_new (class);
	class->process[PROCESS_PRE_STOP]->command = "echo";

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_PRE_STOP;
		job->pid[PROCESS_MAIN] = 1;
		job->pid[PROCESS_PRE_STOP] = 2;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_RESPAWN);
		TEST_EQ (job->state, JOB_PRE_STOP);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);
		TEST_EQ (job->pid[PROCESS_PRE_STOP], 2);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_EQ_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		job_process_handler (NULL, 2, NIH_CHILD_EXITED, 0);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);
		TEST_EQ (job->pid[PROCESS_PRE_STOP], 0);

		assert0 (clock_gettime (CLOCK_MONOTONIC, &now));

		TEST_EQ (job->respawn_count, 1);
		TEST_LE (job->respawn_time, now.tv_sec);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);
		TEST_EQ (job->class->process[PROCESS_MAIN]->script, FALSE);

		TEST_FILE_EQ (output, ("test: test main process ended, "
				       "respawning\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		nih_free (job);
	}

	nih_free (class->process[PROCESS_PRE_STOP]);
	class->process[PROCESS_PRE_STOP] = NULL;

	class->respawn = FALSE;


	/* Check that we don't respawn the job if the running process exits
	 * before the pre-stop process finishes if we were going to stop the
	 * running proecss anyway.
	 */
	TEST_FEATURE ("with respawn of to be stopped while pre-stop process");
	class->respawn = TRUE;
	class->respawn_limit = 5;
	class->respawn_interval = 10;

	class->process[PROCESS_PRE_STOP] = process_new (class);
	class->process[PROCESS_PRE_STOP]->command = "echo";

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_STOP;
		job->state = JOB_PRE_STOP;
		job->pid[PROCESS_MAIN] = 1;
		job->pid[PROCESS_PRE_STOP] = 2;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = -1;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_PRE_STOP);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);
		TEST_EQ (job->pid[PROCESS_PRE_STOP], 2);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_EQ_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, (ProcessType)-1);
		TEST_EQ (job->exit_status, 0);

		job_process_handler (NULL, 2, NIH_CHILD_EXITED, 0);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);
		TEST_EQ (job->pid[PROCESS_PRE_STOP], 0);

		TEST_EQ (job->respawn_count, 0);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_NE_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocker->blocking);

		blocked = (Blocked *)job->blocker->blocking.next;
		TEST_ALLOC_SIZE (blocked, sizeof (Blocked));
		TEST_ALLOC_PARENT (blocked, job->blocker);
		TEST_EQ (blocked->type, BLOCKED_JOB);
		TEST_EQ_P (blocked->job, job);
		nih_free (blocked);

		TEST_LIST_EMPTY (&job->blocker->blocking);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, (ProcessType)-1);
		TEST_EQ (job->exit_status, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		nih_free (job);
	}

	nih_free (class->process[PROCESS_PRE_STOP]);
	class->process[PROCESS_PRE_STOP] = NULL;

	class->respawn = FALSE;

	/* Check that a running task that exits while we're waiting for
	 * the stopping event to finish does not change the state or
	 * record the exit information since we were stopping anyway and
	 * this just makes our job easier.
	 */
	TEST_FEATURE ("with running process while stopping");
	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);

			bevent = event_new (job, "stopping", NULL);
		}

		job->goal = JOB_STOP;
		job->state = JOB_STOPPING;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = bevent;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, 1, NIH_CHILD_KILLED, SIGTERM);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_STOP);
		TEST_EQ (job->state, JOB_STOPPING);
		TEST_EQ (job->pid[PROCESS_MAIN], 0);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_EQ_P (job->blocker, bevent);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		nih_free (job);

		TEST_FILE_EQ (output, ("test: test main process (1) "
				       "killed by TERM signal\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);
	}


#if HAVE_VALGRIND_VALGRIND_H
	/* These tests fail when running under valgrind.
	 */
	if (! RUNNING_ON_VALGRIND) {
#endif
	/* Check that we ignore a process stopping on a signal if it isn't
	 * the main process of the job.
	 */
	TEST_FEATURE ("with stopped non-main process");
	class->expect = EXPECT_STOP;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		TEST_CHILD (pid) {
			raise (SIGSTOP);
			exit (0);
		}

		assert0 (waitid (P_PID, pid, &info, WSTOPPED | WNOWAIT));

		job->goal = JOB_START;
		job->state = JOB_SPAWNED;
		job->pid[PROCESS_MAIN] = 1;
		job->pid[PROCESS_POST_START] = pid;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, pid,
					   NIH_CHILD_STOPPED, SIGSTOP);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_SPAWNED);
		TEST_EQ (job->pid[PROCESS_MAIN], 1);
		TEST_EQ (job->pid[PROCESS_POST_START], pid);

		TEST_EQ (kill (pid, SIGCONT), 0);

		waitpid (job->pid[PROCESS_POST_START], &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_EQ_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		nih_free (job);
	}

	class->expect = EXPECT_NONE;


	/* Check that we ignore the main process stopping on a signal if the
	 * job isn't in the spawned state.
	 */
	TEST_FEATURE ("with stopped main process outside of spawned");
	class->expect = EXPECT_STOP;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		TEST_CHILD (pid) {
			raise (SIGSTOP);
			exit (0);
		}

		assert0 (waitid (P_PID, pid, &info, WSTOPPED | WNOWAIT));

		job->goal = JOB_START;
		job->state = JOB_POST_START;
		job->pid[PROCESS_MAIN] = pid;
		job->pid[PROCESS_POST_START] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, pid,
					   NIH_CHILD_STOPPED, SIGSTOP);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_POST_START);
		TEST_EQ (job->pid[PROCESS_MAIN], pid);
		TEST_EQ (job->pid[PROCESS_POST_START], 1);

		TEST_EQ (kill (pid, SIGCONT), 0);

		waitpid (job->pid[PROCESS_MAIN], &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_EQ_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		nih_free (job);
	}

	class->expect = EXPECT_NONE;


	/* Check that we ignore the main process stopping on a signal in
	 * the spawned state if we're not waiting for it to do so.
	 */
	TEST_FEATURE ("with stopped main process for non-wait job");
	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		TEST_CHILD (pid) {
			raise (SIGSTOP);
			exit (0);
		}

		assert0 (waitid (P_PID, pid, &info, WSTOPPED | WNOWAIT));

		job->goal = JOB_START;
		job->state = JOB_SPAWNED;
		job->pid[PROCESS_MAIN] = pid;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, pid,
					   NIH_CHILD_STOPPED, SIGSTOP);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_SPAWNED);
		TEST_EQ (job->pid[PROCESS_MAIN], pid);

		TEST_EQ (kill (pid, SIGCONT), 0);

		waitpid (job->pid[PROCESS_MAIN], &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_EQ_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		nih_free (job);
	}


	/* Check that we ignore the main process stopping on the wrong
	 * signal.
	 */
	TEST_FEATURE ("with stopped main process but wrong signal");
	class->expect = EXPECT_STOP;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		TEST_CHILD (pid) {
			raise (SIGTSTP);
			exit (0);
		}

		assert0 (waitid (P_PID, pid, &info, WSTOPPED | WNOWAIT));

		job->goal = JOB_START;
		job->state = JOB_SPAWNED;
		job->pid[PROCESS_MAIN] = pid;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, pid,
					   NIH_CHILD_STOPPED, SIGTSTP);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_SPAWNED);
		TEST_EQ (job->pid[PROCESS_MAIN], pid);

		TEST_EQ (kill (pid, SIGCONT), 0);

		waitpid (job->pid[PROCESS_MAIN], &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		TEST_EQ (event->blockers, 1);
		TEST_EQ (event->failed, FALSE);

		TEST_EQ_P (job->blocker, NULL);

		TEST_LIST_NOT_EMPTY (&job->blocking);
		TEST_NOT_FREE (blocked);
		TEST_EQ_P (blocked->event, event);
		event_unblock (event);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		nih_free (job);
	}

	class->expect = EXPECT_NONE;


	/* Check that if we're waiting in spawned for the main process to
	 * stop, and it does so, the process is continued and the job state
	 * changed to running.
	 */
	TEST_FEATURE ("with stopped main process waiting in spawned");
	class->expect = EXPECT_STOP;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		TEST_CHILD (pid) {
			raise (SIGSTOP);
			exit (0);
		}

		assert0 (waitid (P_PID, pid, &info, WSTOPPED | WNOWAIT));

		job->goal = JOB_START;
		job->state = JOB_SPAWNED;
		job->pid[PROCESS_MAIN] = pid;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, pid,
					   NIH_CHILD_STOPPED, SIGSTOP);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_RUNNING);
		TEST_EQ (job->pid[PROCESS_MAIN], pid);

		waitpid (job->pid[PROCESS_MAIN], &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		TEST_EQ (event->blockers, 0);
		TEST_EQ (event->failed, FALSE);

		TEST_EQ_P (job->blocker, NULL);

		TEST_LIST_EMPTY (&job->blocking);
		TEST_FREE (blocked);

		TEST_EQ (job->failed, FALSE);
		TEST_EQ (job->failed_process, PROCESS_INVALID);
		TEST_EQ (job->exit_status, 0);

		nih_free (job);
	}

	class->expect = EXPECT_NONE;


	/* Check that a traced process has a signal delivered to it
	 * unchanged.
	 */
	TEST_FEATURE ("with signal delivered to traced process");
	class->expect = EXPECT_DAEMON;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");
			job->trace_state = TRACE_NORMAL;
		}

		TEST_CHILD (pid) {
			assert0 (ptrace (PTRACE_TRACEME, 0, NULL, 0));
			signal (SIGTERM, SIG_IGN);
			raise (SIGTERM);
			exit (0);
		}

		assert0 (waitid (P_PID, pid, &info, WSTOPPED | WNOWAIT));

		job->goal = JOB_START;
		job->state = JOB_SPAWNED;
		job->pid[PROCESS_MAIN] = pid;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, pid,
					   NIH_CHILD_TRAPPED, SIGTERM);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_SPAWNED);
		TEST_EQ (job->pid[PROCESS_MAIN], pid);

		TEST_EQ (job->trace_forks, 0);
		TEST_EQ (job->trace_state, TRACE_NORMAL);

		waitpid (job->pid[PROCESS_MAIN], &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
	}

	class->expect = EXPECT_NONE;


	/* Check that a new traced process which receives SIGTRAP doesn't
	 * have it delivered, and instead has its options set.
	 */
	TEST_FEATURE ("with trapped new traced process");
	class->expect = EXPECT_DAEMON;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");
			job->trace_state = TRACE_NEW;
		}

		TEST_CHILD (pid) {
			assert0 (ptrace (PTRACE_TRACEME, 0, NULL, 0));
			raise (SIGTRAP);
			exit (0);
		}

		assert0 (waitid (P_PID, pid, &info, WSTOPPED | WNOWAIT));

		job->goal = JOB_START;
		job->state = JOB_SPAWNED;
		job->pid[PROCESS_MAIN] = pid;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, pid,
					   NIH_CHILD_TRAPPED, SIGTRAP);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_SPAWNED);
		TEST_EQ (job->pid[PROCESS_MAIN], pid);

		TEST_EQ (job->trace_forks, 0);
		TEST_EQ (job->trace_state, TRACE_NORMAL);

		waitpid (job->pid[PROCESS_MAIN], &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
	}

	class->expect = EXPECT_NONE;


	/* Check that a new traced process child which receives SIGSTOP
	 * doesn't have it delivered, and instead has its fork count
	 * incremented and its options set.
	 */
	TEST_FEATURE ("with trapped new traced process");
	class->expect = EXPECT_DAEMON;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");
			job->trace_state = TRACE_NEW_CHILD;
		}

		TEST_CHILD (pid) {
			assert0 (ptrace (PTRACE_TRACEME, 0, NULL, 0));
			raise (SIGSTOP);
			exit (0);
		}

		assert0 (waitid (P_PID, pid, &info, WSTOPPED | WNOWAIT));

		job->goal = JOB_START;
		job->state = JOB_SPAWNED;
		job->pid[PROCESS_MAIN] = pid;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, pid,
					   NIH_CHILD_TRAPPED, SIGSTOP);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_SPAWNED);
		TEST_EQ (job->pid[PROCESS_MAIN], pid);

		TEST_EQ (job->trace_forks, 1);
		TEST_EQ (job->trace_state, TRACE_NORMAL);

		waitpid (job->pid[PROCESS_MAIN], &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
	}

	class->expect = EXPECT_NONE;


	/* Check that the second child of a daemon process is detached
	 * and ends the trace, moving the job into the running state.
	 */
	TEST_FEATURE ("with second child of daemon process");
	class->expect = EXPECT_DAEMON;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");
			job->trace_forks = 1;
			job->trace_state = TRACE_NEW_CHILD;
		}

		TEST_CHILD (pid) {
			assert0 (ptrace (PTRACE_TRACEME, 0, NULL, 0));
			raise (SIGSTOP);
			pause ();
			exit (0);
		}

		assert0 (waitid (P_PID, pid, &info, WSTOPPED | WNOWAIT));

		job->goal = JOB_START;
		job->state = JOB_SPAWNED;
		job->pid[PROCESS_MAIN] = pid;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, pid,
					   NIH_CHILD_TRAPPED, SIGSTOP);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_RUNNING);
		TEST_EQ (job->pid[PROCESS_MAIN], pid);

		TEST_EQ (job->trace_forks, 2);
		TEST_EQ (job->trace_state, TRACE_NONE);

		kill (job->pid[PROCESS_MAIN], SIGTERM);
		waitpid (job->pid[PROCESS_MAIN], &status, 0);
		TEST_TRUE (WIFSIGNALED (status));
		TEST_EQ (WTERMSIG (status), SIGTERM);

		nih_free (job);
	}

	class->expect = EXPECT_NONE;


	/* Check that the first child of a forking process is detached
	 * and ends the trace, moving the job into the running state.
	 */
	TEST_FEATURE ("with first child of forking process");
	class->expect = EXPECT_FORK;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");
			job->trace_forks = 0;
			job->trace_state = TRACE_NEW_CHILD;
		}

		TEST_CHILD (pid) {
			assert0 (ptrace (PTRACE_TRACEME, 0, NULL, 0));
			raise (SIGSTOP);
			pause ();
			exit (0);
		}

		assert0 (waitid (P_PID, pid, &info, WSTOPPED | WNOWAIT));

		job->goal = JOB_START;
		job->state = JOB_SPAWNED;
		job->pid[PROCESS_MAIN] = pid;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, pid,
					   NIH_CHILD_TRAPPED, SIGSTOP);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_RUNNING);
		TEST_EQ (job->pid[PROCESS_MAIN], pid);

		TEST_EQ (job->trace_forks, 1);
		TEST_EQ (job->trace_state, TRACE_NONE);

		kill (job->pid[PROCESS_MAIN], SIGTERM);
		waitpid (job->pid[PROCESS_MAIN], &status, 0);
		TEST_TRUE (WIFSIGNALED (status));
		TEST_EQ (WTERMSIG (status), SIGTERM);

		nih_free (job);
	}

	class->expect = EXPECT_NONE;


	/* Check that when a process forks and we receive the event for
	 * the parent before the child (faked by killing the child), the
	 * trace state is to expect a new child - with the state updated
	 * to have the new pid, and the parent detached.
	 */
	TEST_FEATURE ("with fork notification before child");
	class->expect = EXPECT_DAEMON;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");
			job->trace_state = TRACE_NORMAL;
		}

		TEST_CHILD (pid) {
			assert0 (ptrace (PTRACE_TRACEME, 0, NULL, 0));
			raise (SIGSTOP);
			fork ();
			exit (0);
		}

		assert0 (waitid (P_PID, pid, &info, WSTOPPED | WNOWAIT));
		assert0 (ptrace (PTRACE_SETOPTIONS, pid, NULL,
				 PTRACE_O_TRACEFORK | PTRACE_O_TRACEEXEC));
		assert0 (ptrace (PTRACE_CONT, pid, NULL, 0));

		assert0 (waitid (P_PID, pid, &info, WSTOPPED | WNOWAIT));

		/* Get the child process id now; it'll be stopped at a
		 * trapped SIGSTOP, so continue and let it die - thus
		 * simulating the event not having been received yet.
		 */
		assert0 (ptrace (PTRACE_GETEVENTMSG, pid, NULL, &data));

		assert0 (waitid (P_PID, (pid_t)data,
				 &info, WSTOPPED | WNOWAIT));
		TEST_EQ (info.si_pid, (pid_t)data);
		TEST_EQ (info.si_code, CLD_TRAPPED);
		TEST_EQ (info.si_status, SIGSTOP);

		assert0 (ptrace (PTRACE_CONT, (pid_t)data, NULL, 0));

		waitpid ((pid_t)data, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		/* Now carry on with the test */
		job->goal = JOB_START;
		job->state = JOB_SPAWNED;
		job->pid[PROCESS_MAIN] = pid;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, pid, NIH_CHILD_PTRACE,
					   PTRACE_EVENT_FORK);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_SPAWNED);
		TEST_NE (job->pid[PROCESS_MAIN], pid);

		TEST_EQ (job->trace_forks, 0);
		TEST_EQ (job->trace_state, TRACE_NEW_CHILD);

		waitpid (pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
	}

	class->expect = EXPECT_NONE;


	/* Check that when a process forks and we receive the event for
	 * the child before the parent (forced by deliberately waiting
	 * for the child and reaping its event first), the existing
	 * child is handled anyway and the trace state updated with the
	 * new pid, the parent detached and the new child being traced
	 * with a normal state.
	 */
	TEST_FEATURE ("with child notification before parent");
	class->expect = EXPECT_DAEMON;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");
			job->trace_state = TRACE_NORMAL;
		}

		TEST_CHILD (pid) {
			assert0 (ptrace (PTRACE_TRACEME, 0, NULL, 0));
			raise (SIGSTOP);
			fork ();
			exit (0);
		}

		assert0 (waitid (P_PID, pid, &info, WSTOPPED | WNOWAIT));
		assert0 (ptrace (PTRACE_SETOPTIONS, pid, NULL,
				 PTRACE_O_TRACEFORK | PTRACE_O_TRACEEXEC));
		assert0 (ptrace (PTRACE_CONT, pid, NULL, 0));

		assert0 (waitid (P_PID, pid, &info, WSTOPPED | WNOWAIT));

		/* Wait for the child process to reach SIGSTOP as well,
		 * taking it off the wait queue.
		 */
		assert0 (ptrace (PTRACE_GETEVENTMSG, pid, NULL, &data));

		assert0 (waitid (P_PID, (pid_t)data,
				 &info, WSTOPPED | WNOWAIT));
		TEST_EQ (info.si_pid, (pid_t)data);
		TEST_EQ (info.si_code, CLD_TRAPPED);
		TEST_EQ (info.si_status, SIGSTOP);

		/* Now carry on with the test */
		job->goal = JOB_START;
		job->state = JOB_SPAWNED;
		job->pid[PROCESS_MAIN] = pid;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, pid, NIH_CHILD_PTRACE,
					     PTRACE_EVENT_FORK);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_SPAWNED);
		TEST_NE (job->pid[PROCESS_MAIN], pid);

		TEST_EQ (job->trace_forks, 1);
		TEST_EQ (job->trace_state, TRACE_NORMAL);

		waitpid (pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		waitpid ((pid_t)data, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
	}

	class->expect = EXPECT_NONE;


	/* Check that should the process call exec() before the first fork()
	 * it's allowed since it's likely a shell script calling the real
	 * thing that we want to follow.
	 */
	TEST_FEATURE ("with exec call by initial process");
	class->expect = EXPECT_DAEMON;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");
			job->trace_forks = 0;
			job->trace_state = TRACE_NORMAL;
		}

		TEST_CHILD (pid) {
			assert0 (ptrace (PTRACE_TRACEME, 0, NULL, 0));
			raise (SIGSTOP);
			execl ("/bin/true", "true", NULL);
			exit (15);
		}

		assert0 (waitid (P_PID, pid, &info, WSTOPPED | WNOWAIT));
		assert0 (ptrace (PTRACE_SETOPTIONS, pid, NULL,
				 PTRACE_O_TRACEFORK | PTRACE_O_TRACEEXEC));
		assert0 (ptrace (PTRACE_CONT, pid, NULL, 0));

		assert0 (waitid (P_PID, pid, &info, WSTOPPED | WNOWAIT));

		job->goal = JOB_START;
		job->state = JOB_SPAWNED;
		job->pid[PROCESS_MAIN] = pid;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, pid, NIH_CHILD_PTRACE,
					     PTRACE_EVENT_EXEC);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_SPAWNED);
		TEST_EQ (job->pid[PROCESS_MAIN], pid);

		TEST_EQ (job->trace_forks, 0);
		TEST_EQ (job->trace_state, TRACE_NORMAL);

		waitpid (job->pid[PROCESS_MAIN], &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
	}

	class->expect = EXPECT_NONE;


	/* Check that should the process call exec() after fork() it ends
	 * the tracing even if we haven't had enough forks yet and moves
	 * the job into the running state.
	 */
	TEST_FEATURE ("with exec call by process after fork");
	class->expect = EXPECT_DAEMON;

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");
			job->trace_forks = 1;
			job->trace_state = TRACE_NORMAL;
		}

		TEST_CHILD (pid) {
			assert0 (ptrace (PTRACE_TRACEME, 0, NULL, 0));
			raise (SIGSTOP);
			execl ("/bin/true", "true", NULL);
			exit (15);
		}

		assert0 (waitid (P_PID, pid, &info, WSTOPPED | WNOWAIT));
		assert0 (ptrace (PTRACE_SETOPTIONS, pid, NULL,
				 PTRACE_O_TRACEFORK | PTRACE_O_TRACEEXEC));
		assert0 (ptrace (PTRACE_CONT, pid, NULL, 0));

		assert0 (waitid (P_PID, pid, &info, WSTOPPED | WNOWAIT));

		job->goal = JOB_START;
		job->state = JOB_SPAWNED;
		job->pid[PROCESS_MAIN] = pid;

		TEST_DIVERT_STDERR (output) {
			job_process_handler (NULL, pid, NIH_CHILD_PTRACE,
					   PTRACE_EVENT_EXEC);
		}
		rewind (output);

		TEST_EQ (job->goal, JOB_START);
		TEST_EQ (job->state, JOB_RUNNING);
		TEST_EQ (job->pid[PROCESS_MAIN], pid);

		TEST_EQ (job->trace_forks, 1);
		TEST_EQ (job->trace_state, TRACE_NONE);

		waitpid (job->pid[PROCESS_MAIN], &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
	}

	class->expect = EXPECT_NONE;
#if HAVE_VALGRIND_VALGRIND_H
	}
#endif


	fclose (output);

	nih_free (event);
	event_poll ();

	TEST_RESET_MAIN_LOOP ();

	TEST_NE_P (class->process[PROCESS_MAIN], NULL);
	TEST_EQ_P (class->process[PROCESS_PRE_START], NULL);
	TEST_EQ_P (class->process[PROCESS_POST_START], NULL);
	TEST_EQ_P (class->process[PROCESS_PRE_STOP], NULL);
	TEST_EQ_P (class->process[PROCESS_POST_STOP], NULL);
	TEST_EQ_P (class->process[PROCESS_SECURITY], NULL);

	/************************************************************/
	/* Ensure that if a child is setup successfully and then exits
	 * before the main loop detects the child fd has closed (due to
	 * the child calling execvp()), that the state is correct.
	 */
	TEST_FEATURE ("with child exit notification before child setup success notification");

	job = job_new (class, "");
	TEST_NE_P (job, NULL);

	job->goal = JOB_START;
	job->state = JOB_SPAWNING;

	assert0 (pipe (fds));

	job->process_data[PROCESS_MAIN] = job_process_data_new (job->process_data,
			job, PROCESS_MAIN, fds[0]);
	TEST_NE_P (job->process_data[PROCESS_MAIN], NULL);

	TEST_NE_P (class->process[PROCESS_MAIN], NULL);
	TEST_EQ_P (class->process[PROCESS_PRE_START], NULL);
	TEST_EQ_P (class->process[PROCESS_POST_START], NULL);
	TEST_EQ_P (class->process[PROCESS_PRE_STOP], NULL);
	TEST_EQ_P (class->process[PROCESS_POST_STOP], NULL);
	TEST_EQ_P (class->process[PROCESS_SECURITY], NULL);

	/* used to check if job_process_terminated() called */
	job->process_data[PROCESS_MAIN]->status = -1;

	TEST_CHILD (job->pid[PROCESS_MAIN]) {
		close (fds[0]);

		nih_io_set_cloexec (fds[1]);

		execl ("/bin/true", "/bin/true", NULL);
	}
	close (fds[1]);

	TEST_FREE_TAG (job);

	job_process_handler (NULL, job->pid[PROCESS_MAIN],
			NIH_CHILD_EXITED, 0);

	TEST_NOT_FREE (job);

	TEST_TRUE (job->process_data[PROCESS_MAIN]->valid);
	TEST_EQ (job->process_data[PROCESS_MAIN]->job_process_fd, fds[0]);
	TEST_EQ (job->process_data[PROCESS_MAIN]->shell_fd, -1);
	TEST_EQ_P (job->process_data[PROCESS_MAIN]->script, NULL);

	/* job_process_terminated() should have been called now and the
	 * status recorded.
	 */
	TEST_EQ (job->process_data[PROCESS_MAIN]->status, 0);

	/* goal should not change until the IO handlers have had a
	 * chance to run.
	 */
	TEST_EQ (job->goal, JOB_START);
	TEST_EQ (job->state, JOB_SPAWNED);

	TEST_NE_P (job->process_data[PROCESS_MAIN], NULL);

	close (fds[0]);

	pid = job->pid[PROCESS_MAIN];

	TEST_EQ (timed_waitpid (pid, 5), pid);

	nih_free (job);
	TEST_RESET_MAIN_LOOP ();

	/************************************************************/
	/* Ensure that if a child failed to be setup and then exits
	 * before the main loop detects the child fd has data to read
	 * that the state is correct.
	 */
	TEST_FEATURE ("with child exit notification before child setup failure notification");

	job = job_new (class, "");
	TEST_NE_P (job, NULL);

	job->goal = JOB_START;
	job->state = JOB_SPAWNING;

	assert0 (pipe (fds));

	job->process_data[PROCESS_MAIN] = job_process_data_new (job->process_data,
			job, PROCESS_MAIN, fds[0]);
	TEST_NE_P (job->process_data[PROCESS_MAIN], NULL);
	TEST_EQ (job->process_data[PROCESS_MAIN]->job_process_fd, fds[0]);
	TEST_EQ (job->process_data[PROCESS_MAIN]->process, PROCESS_MAIN);

	TEST_CHILD (job->pid[PROCESS_MAIN]) {
		close (fds[0]);

		nih_error_raise_no_memory ();
		job_process_error_abort (fds[1], JOB_PROCESS_ERROR_CGROUP_SETUP, 0);
	}
	close (fds[1]);

	TEST_FREE_TAG (job);

	job_process_handler (NULL, job->pid[PROCESS_MAIN],
			NIH_CHILD_DUMPED, 255);

	TEST_NOT_FREE (job);

	/* goal should not change until the IO handlers have had a
	 * chance to run.
	 */
	TEST_EQ (job->goal, JOB_START);

	TEST_EQ (job->state, JOB_SPAWNED);
	TEST_NE_P (job->process_data[PROCESS_MAIN], NULL);

	/* Still valid because the IO handlers haven't fired yet */
	TEST_TRUE (job->process_data[PROCESS_MAIN]->valid);
	TEST_EQ (job->process_data[PROCESS_MAIN]->job_process_fd, fds[0]);

	TEST_EQ (job->process_data[PROCESS_MAIN]->shell_fd, -1);
	TEST_EQ_P (job->process_data[PROCESS_MAIN]->script, NULL);

	/* job_process_terminated() will have been called now */
	status = job->process_data[PROCESS_MAIN]->status;
	TEST_GT (status, 0);

	TEST_TRUE (WIFEXITED (status));
	TEST_EQ (WEXITSTATUS (status), 255);

	/* slurp - don't care about content */
	buffer = read_from_fd (NULL, fds[0]);
	close (fds[0]);

	pid = job->pid[PROCESS_MAIN];
	TEST_EQ (timed_waitpid (pid, 5), pid);

	nih_free (job);
	TEST_RESET_MAIN_LOOP ();

	/************************************************************/
	TEST_FEATURE ("with child setup success notification before child exit notification");

	job = job_new (class, "");
	TEST_NE_P (job, NULL);

	job->goal = JOB_START;
	job->state = JOB_SPAWNING;

	assert0 (pipe (fds));

	job->process_data[PROCESS_MAIN] = job_process_data_new (job->process_data,
			job, PROCESS_MAIN, fds[0]);
	TEST_NE_P (job->process_data[PROCESS_MAIN], NULL);
	TEST_EQ (job->process_data[PROCESS_MAIN]->job_process_fd, fds[0]);
	TEST_EQ (job->process_data[PROCESS_MAIN]->process, PROCESS_MAIN);

	io = nih_io_reopen (job->process_data[PROCESS_MAIN],
			fds[0],
			NIH_IO_STREAM,
			(NihIoReader)job_process_child_reader,
			(NihIoCloseHandler)job_process_close_handler,
			NULL,
			job->process_data[PROCESS_MAIN]);
	TEST_NE_P (io, NULL);

	TEST_CHILD (job->pid[PROCESS_MAIN]) {
		close (fds[0]);

		nih_io_set_cloexec (fds[1]);

		execl ("/bin/true", "/bin/true", NULL);
	}
	close (fds[1]);

	job_process_close_handler (job->process_data[PROCESS_MAIN], io);

	TEST_EQ (job->goal, JOB_START);
	TEST_EQ (job->state, JOB_SPAWNED);
	TEST_NE_P (job->process_data[PROCESS_MAIN], NULL);

	/* Invalid because the IO handlers have now run */
	TEST_FALSE (job->process_data[PROCESS_MAIN]->valid);
	TEST_EQ (job->process_data[PROCESS_MAIN]->job_process_fd, -1);

	TEST_EQ (job->process_data[PROCESS_MAIN]->shell_fd, -1);
	TEST_EQ_P (job->process_data[PROCESS_MAIN]->script, NULL);
	TEST_EQ (job->process_data[PROCESS_MAIN]->status, 0);

	close (fds[0]);

	pid = job->pid[PROCESS_MAIN];
	TEST_EQ (timed_waitpid (pid, 5), pid);

	nih_free (job);
	TEST_RESET_MAIN_LOOP ();

	/************************************************************/
	TEST_FEATURE ("with child setup failure notification before child exit notification");

	job = job_new (class, "");
	TEST_NE_P (job, NULL);

	job->goal = JOB_START;
	job->state = JOB_SPAWNED;

	assert0 (pipe (fds));

	job->process_data[PROCESS_MAIN] = job_process_data_new (job->process_data,
			job, PROCESS_MAIN, fds[0]);
	TEST_NE_P (job->process_data[PROCESS_MAIN], NULL);
	TEST_EQ (job->process_data[PROCESS_MAIN]->job_process_fd, fds[0]);
	TEST_EQ (job->process_data[PROCESS_MAIN]->process, PROCESS_MAIN);

	/* Can't use job_register_child_handler() as we want the return
	 * value.
	 */
	io = nih_io_reopen (job->process_data[PROCESS_MAIN],
			fds[0],
			NIH_IO_STREAM,
			(NihIoReader)job_process_child_reader,
			(NihIoCloseHandler)job_process_close_handler,
			NULL,
			job->process_data[PROCESS_MAIN]);
	TEST_NE_P (io, NULL);

	RESILIENT_TEST_CHILD (job->pid[PROCESS_MAIN]) {
		close (fds[0]);
		nih_error_raise_no_memory ();
		job_process_error_abort (fds[1], JOB_PROCESS_ERROR_CGROUP_SETUP, 0);
	}
	close (fds[1]);
	pid = job->pid[PROCESS_MAIN];

	buffer = read_from_fd (NULL, fds[0]);

	job_process_child_reader (job->process_data[PROCESS_MAIN],
			io, buffer->buf, buffer->len);

	/* Setup failed, so goal should have changed to stop */
	TEST_EQ (job->goal, JOB_STOP);
	TEST_EQ (job->state, JOB_STOPPING);

	TEST_NE_P (job->process_data[PROCESS_MAIN], NULL);

	/* Invalid because the IO handlers have now run */
	TEST_FALSE (job->process_data[PROCESS_MAIN]->valid);
	TEST_EQ (job->process_data[PROCESS_MAIN]->job_process_fd, -1);

	TEST_EQ (job->process_data[PROCESS_MAIN]->shell_fd, -1);
	TEST_EQ_P (job->process_data[PROCESS_MAIN]->script, NULL);
	TEST_EQ (job->process_data[PROCESS_MAIN]->shell_fd, -1);

	/* Still zero because the process handler hasn't run yet */
	TEST_EQ (job->process_data[PROCESS_MAIN]->status, 0);

	close (fds[0]);

	TEST_EQ (timed_waitpid (pid, 5), pid);

	nih_free (job);

	TEST_RESET_MAIN_LOOP ();

	/************************************************************/

	nih_free (class);
	file->job = NULL;
	nih_free (source);

	TEST_EQ (rmdir (dirname), 0);
	TEST_EQ (unsetenv ("UPSTART_LOGDIR"), 0);
}


void
test_find (void)
{
	JobClass    *class1, *class2, *class3;
	Job         *job1, *job2, *job3, *job4, *job5, *ptr;
	ProcessType  process;

	TEST_FUNCTION ("job_process_find");
	class1 = job_class_new (NULL, "foo", NULL);
	class1->process[PROCESS_MAIN] = process_new (class1);
	class1->process[PROCESS_POST_START] = process_new (class1);
	class1->instance = "$FOO";
	nih_hash_add (job_classes, &class1->entry);

	class2 = job_class_new (NULL, "bar", NULL);
	class2->process[PROCESS_PRE_START] = process_new (class2);
	class2->process[PROCESS_MAIN] = process_new (class2);
	class2->process[PROCESS_PRE_STOP] = process_new (class2);
	class2->instance = "$FOO";
	nih_hash_add (job_classes, &class2->entry);

	class3 = job_class_new (NULL, "baz", NULL);
	class3->process[PROCESS_POST_STOP] = process_new (class3);
	nih_hash_add (job_classes, &class3->entry);

	job1 = job_new (class1, "foo");
	job1->pid[PROCESS_MAIN] = 10;
	job1->pid[PROCESS_POST_START] = 15;

	job2 = job_new (class1, "bar");

	job3 = job_new (class2, "foo");
	job3->pid[PROCESS_PRE_START] = 20;

	job4 = job_new (class2, "bar");
	job4->pid[PROCESS_MAIN] = 25;
	job4->pid[PROCESS_PRE_STOP] = 30;

	job5 = job_new (class3, "");
	job5->pid[PROCESS_POST_STOP] = 35;


	/* Check that we can find a job that exists by the pid of its
	 * primary process.
	 */
	TEST_FEATURE ("with pid we expect to find");
	ptr = job_process_find (10, &process);

	TEST_EQ_P (ptr, job1);
	TEST_EQ (process, PROCESS_MAIN);


	/* Check that we can find a job that exists by the pid of its
	 * pre-start process.
	 */
	TEST_FEATURE ("with pre-start pid we expect to find");
	ptr = job_process_find (20, &process);

	TEST_EQ_P (ptr, job3);
	TEST_EQ (process, PROCESS_PRE_START);


	/* Check that we can find a job that exists by the pid of its
	 * post-start process.
	 */
	TEST_FEATURE ("with post-start pid we expect to find");
	ptr = job_process_find (15, &process);

	TEST_EQ_P (ptr, job1);
	TEST_EQ (process, PROCESS_POST_START);


	/* Check that we can find a job that exists by the pid of its
	 * pre-stop process.
	 */
	TEST_FEATURE ("with pre-stop pid we expect to find");
	ptr = job_process_find (30, &process);

	TEST_EQ_P (ptr, job4);
	TEST_EQ (process, PROCESS_PRE_STOP);


	/* Check that we can find a job that exists by the pid of its
	 * pre-stop process.
	 */
	TEST_FEATURE ("with post-stop pid we expect to find");
	ptr = job_process_find (35, &process);

	TEST_EQ_P (ptr, job5);
	TEST_EQ (process, PROCESS_POST_STOP);


	/* Check that we get NULL if no job has a process with that pid. */
	TEST_FEATURE ("with pid we do not expect to find");
	ptr = job_process_find (100, NULL);

	TEST_EQ_P (ptr, NULL);


	/* Check that we get NULL if there are jobs in the hash, but none
	 * have pids.
	 */
	TEST_FEATURE ("with no pids in job table");
	nih_free (job5);
	nih_free (job4);
	nih_free (job3);
	nih_free (job1);
	ptr = job_process_find (20, NULL);

	TEST_EQ_P (ptr, NULL);


	/* Check that we get NULL if there are no instances running. */
	TEST_FEATURE ("with no instances");
	nih_free (job2);
	ptr = job_process_find (20, NULL);

	TEST_EQ_P (ptr, NULL);


	/* Check that we get NULL if there are no jobs in the hash. */
	TEST_FEATURE ("with empty job table");
	nih_free (class1);
	nih_free (class2);
	nih_free (class3);
	ptr = job_process_find (20, NULL);

	TEST_EQ_P (ptr, NULL);
}


void
test_utmp (void)
{
	JobClass *      class;
	Job *           job = NULL;
	Blocked *       blocked = NULL;
	Event *         event;
	FILE *          output;
	char            utmpname[PATH_MAX];
	struct utmpx    utmp, *utmptr;
	struct timeval  tv;

	TEST_FUNCTION ("job_process_handler");
	program_name = "test";

	class = job_class_new (NULL, "test", NULL);
	class->process[PROCESS_MAIN] = process_new (class);
	class->process[PROCESS_MAIN]->command = "echo";

	class->start_on = event_operator_new (class, EVENT_MATCH,
					       "foo", NULL);
	class->stop_on = event_operator_new (class, EVENT_MATCH,
					      "foo", NULL);
	nih_hash_add (job_classes, &class->entry);

	event = event_new (NULL, "foo", NULL);

	TEST_FILENAME(utmpname);

	/* Check that utmp record for the running task of the job terminating
	 * is properly changed to DEAD_PROCESS
	 */
	TEST_FEATURE ("with LOGIN_PROCESS utmp entry");
	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_RUNNING;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		output = fopen (utmpname, "w");
		fclose (output);

		/* set utmp file */
		utmpxname(utmpname);

		/* set up utmp entries */
		memset (&utmp, 0, sizeof utmp);

		strcpy(utmp.ut_id, "2");
		utmp.ut_type = LOGIN_PROCESS;
		utmp.ut_pid = 2;

		gettimeofday(&tv, NULL);
		utmp.ut_tv.tv_sec = tv.tv_sec;
		utmp.ut_tv.tv_usec = tv.tv_usec;

		setutxent();
		pututxline(&utmp);

		strcpy(utmp.ut_id, "1");
		utmp.ut_pid = 1;
		pututxline(&utmp);

		endutxent();

		job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);

		setutxent();

		utmptr = getutxent();
		TEST_NE_P(utmptr, NULL);
		TEST_EQ(utmptr->ut_pid, 2);
		TEST_EQ(utmptr->ut_type, LOGIN_PROCESS);

		utmptr = getutxent();
		TEST_NE_P(utmptr, NULL);
		TEST_EQ(utmptr->ut_pid, 1);
		TEST_EQ(utmptr->ut_type, DEAD_PROCESS);

		nih_free (job);
	}
	TEST_FEATURE ("with USER_PROCESS utmp entry");
	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_RUNNING;
		job->pid[PROCESS_MAIN] = 1;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		output = fopen (utmpname, "w");
		fclose (output);

		/* set utmp file */
		utmpxname(utmpname);

		/* set up utmp entries */
		memset (&utmp, 0, sizeof utmp);

		strcpy(utmp.ut_id, "2");
		utmp.ut_type = USER_PROCESS;
		utmp.ut_pid = 2;

		gettimeofday(&tv, NULL);
		utmp.ut_tv.tv_sec = tv.tv_sec;
		utmp.ut_tv.tv_usec = tv.tv_usec;

		setutxent();
		pututxline(&utmp);

		strcpy(utmp.ut_id, "1");
		utmp.ut_pid = 1;
		pututxline(&utmp);

		endutxent();

		job_process_handler (NULL, 1, NIH_CHILD_EXITED, 0);

		setutxent();

		utmptr = getutxent();
		TEST_NE_P(utmptr, NULL);
		TEST_EQ(utmptr->ut_pid, 2);
		TEST_EQ(utmptr->ut_type, USER_PROCESS);

		utmptr = getutxent();
		TEST_NE_P(utmptr, NULL);
		TEST_EQ(utmptr->ut_pid, 1);
		TEST_EQ(utmptr->ut_type, DEAD_PROCESS);

		nih_free (job);
	}

	/* new mingetty doesn't use entries with DEAD_PROCESS until it's last entry so
	 * we need to check if upstart sets DEAD_PROCESS for correct entry */
	TEST_FEATURE ("with multiple entries with same ut_id");
	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			job = job_new (class, "");

			blocked = blocked_new (job, BLOCKED_EVENT, event);
			event_block (event);
			nih_list_add (&job->blocking, &blocked->entry);
		}

		job->goal = JOB_START;
		job->state = JOB_RUNNING;
		job->pid[PROCESS_MAIN] = 2;

		TEST_FREE_TAG (blocked);

		job->blocker = NULL;
		event->failed = FALSE;

		job->failed = FALSE;
		job->failed_process = PROCESS_INVALID;
		job->exit_status = 0;

		output = fopen (utmpname, "w");
		fclose (output);

		/* set utmp file */
		utmpxname(utmpname);

		/* set up utmp entries */
		memset (&utmp, 0, sizeof utmp);

		strcpy(utmp.ut_id, "2");
		utmp.ut_type = DEAD_PROCESS;
		utmp.ut_pid = 1;

		gettimeofday(&tv, NULL);
		utmp.ut_time = 0;

		setutxent();
		pututxline(&utmp);

		strcpy(utmp.ut_id, "2");
		utmp.ut_type = USER_PROCESS;
		utmp.ut_pid = 2;
		utmp.ut_tv.tv_sec = tv.tv_sec;
		utmp.ut_tv.tv_usec = tv.tv_usec;
		pututxline(&utmp);

		endutxent();

		job_process_handler (NULL, 2, NIH_CHILD_EXITED, 0);

		setutxent();

		utmptr = getutxent();
		TEST_NE_P(utmptr, NULL);
		TEST_EQ(utmptr->ut_pid, 1);
		TEST_EQ(utmptr->ut_type, DEAD_PROCESS);

		utmptr = getutxent();
		TEST_NE_P(utmptr, NULL);
		TEST_EQ(utmptr->ut_pid, 2);
		TEST_EQ(utmptr->ut_type, DEAD_PROCESS);
		TEST_EQ(utmptr->ut_time, 0);

		nih_free (job);
	}

	unlink (utmpname);
}

void
run_tests (void)
{
	test_start ();
	test_spawn ();
	test_log_path ();
	test_kill ();
	test_handler ();
	test_utmp ();
	test_find ();
}

/**
 * io_reader:
 *
 * Write data received from child end of pty to stdout and
 * update the NihIo to reflect the consumed data.
 *
 * We could detect and replace the "\r\n" line-end combo added by the
 * pty line-discipline with a simple '\n', but for now lets leave the
 * data verbatim so it's clear from the log when pty usage kicks in.
 **/
static void
io_reader (void       *data,
	   NihIo      *io, 
	   const char *str,
	   size_t      len)
{
	ssize_t bytes;

	nih_assert (io);
	nih_assert (str);
	nih_assert (len);

	bytes = write (STDOUT_FILENO, str, len);
	TEST_NE (bytes, -1);

	/* consume */
	nih_io_buffer_shrink (io->recv_buf, bytes);
}

/**
 * io_error_handler:
 *
 * Deal with errors from child end of pty.
 **/
static void
io_error_handler (void   *data,
	   	  NihIo  *io)
{
	NihError *err;

	nih_assert (io);

	/* Consume */
	err = nih_error_get ();        

	/* error that's returned when child closes their end of a pty */
	nih_assert (err->number == EIO);

	nih_free (err);

	nih_free (io);
}

/* Grab child exit status and ask main loop to exit */
void
process_handler (void          *data,
		pid_t           pid,
		NihChildEvents  event,
		int             status)
{
	nih_assert (pid == pty_child_pid);

	nih_main_loop_exit (status);
}


/**
 * run_tests_in_pty:
 *
 * Create a pty and run tests in child process. Parent echoes childs
 * output.
 *
 * This shouldn't be required but for the fact that Upstart needs to
 * be able to run its test suite even in environments which
 * don't provide a controlling terminal (such as modern versions of
 * sbuild).
 *
 * See the following for the gory details:
 *
 *   - LP: #888910
 *   - Debian Bug:607844
 **/
void
run_tests_in_pty (void)
{
	int               pty_master;
	int               pty_slave;
	nih_local NihIo  *io = NULL;
	int               ret;

	ret = openpty (&pty_master, &pty_slave, NULL, NULL, NULL);
	TEST_NE (ret, -1);

	pty_child_pid = fork ();
	TEST_NE (pty_child_pid, (pid_t)-1);

	if (! pty_child_pid) {
		int   i;
		pid_t self;

		/* child */
		close (pty_master);

		self = getpid ();

		/* Ensure that the child is the process group leader
		 * such that is responds correctly to SIGTSTP.
		 */
		TEST_EQ (setpgid (self, self), 0);

		/* connect standard streams to the child end of the pty */
		for (i = 0; i < 3; i++)
			while (dup2 (pty_slave, i) == -1 && errno == EBUSY)
				;

		/* clean up */
		close (pty_slave);

		/* run tests within the pty */
		run_tests ();

		exit (EXIT_SUCCESS);
	}

	/* parent */

	close (pty_slave);

	io = nih_io_reopen (NULL, pty_master,
			NIH_IO_STREAM,
			io_reader, NULL,
			io_error_handler, NULL);
	TEST_NE_P (io, NULL);

	/* Watch child for events */
	NIH_MUST (nih_child_add_watch (NULL, pty_child_pid,
				(NIH_CHILD_EXITED|NIH_CHILD_KILLED|NIH_CHILD_DUMPED),
				process_handler, NULL)); 

	ret = nih_main_loop ();

	exit (ret ? EXIT_FAILURE : EXIT_SUCCESS);
}

/**
 * have_ctty:
 *
 * Returns: TRUE if we have a controlling terminal,
 * else FALSE.
 **/
int
have_ctty (void)
{
	int fd;

	fd = open ("/dev/tty", O_RDONLY | O_NOCTTY);

	if (fd < 0)
		return FALSE;
	close (fd);
	return TRUE;
}

int
main (int   argc,
      char *argv[])
{
	/* Note we do not set the UPSTART_NO_SESSIONS variable since this
	 * would cause these tests to fail (as they scrutinize the job
	 * environment).
	 */

	/* run tests in legacy (pre-session support) mode */
	setenv ("UPSTART_NO_SESSIONS", "1", 1);


	/* We re-exec this binary to test various children features.  To
	 * do that, we need to know the full path to the program.
	 */
	argv0 = argv[0];
	if (argv0[0] != '/') {
#ifdef TEST_PLAN
		TEST_PLAN(153);
#endif
		char *path = nih_alloc (NULL, PATH_MAX);

		assert (getcwd (path, PATH_MAX));
		strcat (path, "/");
		strcat (path, argv0);

		argv0 = path;
	}

	/* If three arguments are given, the first is the child enum,
	 * second is a filename to write the result to and the third is
	 * the number of times to fork.
	 */
	if (argc == 4) {
		int    forks;
		int    status;
		pid_t  pid;

		forks = atol (argv[3]);

		nih_assert (forks > 0);

		do {
			pid = fork ();
			if (pid < 0)
				exit (1);
			else if (pid) {
				nih_assert (waitpid (pid, &status, 0) == pid);
				exit (0);
			}

		} while (forks--);

		child (atoi (argv[1]), argv[2]);
		nih_assert_not_reached ();
	}

	/* If two arguments are given, the first is the child enum and the
	 * second is a filename to write the result to.
	 */
	if (argc == 3) {
		child (atoi (argv[1]), argv[2]);
		exit (1);
	}

	close_all_files (); 

	job_class_init ();
	nih_error_init ();
	nih_io_init ();

	if (! have_ctty ()) {
		fprintf (stderr,
				"\n\n"
				"INFO: Running tests in pty since environment "
				"does not provide needed controlling terminal\n"
				"\n\n");
		run_tests_in_pty ();
	} else {
		run_tests ();
	}

	return 0;
}
