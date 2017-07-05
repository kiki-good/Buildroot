/* upstart
 *
 * test_xdg.c - test suite for init/xdg.c
 *
 * Copyright © 2012 Canonical Ltd.
 * Author: Dmitrijs Ledkovs <dmitrijs.ledkovs@canonical.com>
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

#include <nih/string.h>
#include <nih/test.h>

#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "xdg.h"

#include "test_util_common.h"

void
_test_dir_created (char * dirname) {
	struct stat statbuf;

	TEST_EQ (lstat (dirname, &statbuf), 0);
	TEST_TRUE (S_ISDIR (statbuf.st_mode));
	
	/* Check that the created directory has 0700 permissions, as per XDG spec */
	TEST_EQ (0700, statbuf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
}

void
test_get_home_subdir (void)
{
	char    dirname[PATH_MAX];
	char       *dir;
	char * expected=NULL;

	TEST_FUNCTION ("get_home_subdir");

	TEST_FEATURE ("with HOME not set");
	TEST_EQ (unsetenv ("HOME"), 0);

	TEST_ALLOC_FAIL {
		dir = get_home_subdir ("test", FALSE);
		TEST_EQ_P (dir, NULL);
	}

	TEST_FEATURE ("with HOME set");
	TEST_FILENAME (dirname);
	TEST_EQ (setenv ("HOME", dirname, 1), 0);

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			dir = NULL;
			expected = NIH_MUST (nih_sprintf (NULL, "%s/test", dirname));
		}

		dir = get_home_subdir ("test", FALSE);

		if (test_alloc_failed) {
			TEST_EQ_P (dir, NULL);
		} else {
			TEST_EQ_STR (dir, expected);
			nih_free (dir);
		}

		if (expected)
			nih_free (expected);
	}
}

void
_test_get_home (char * env_var_name, char * dir_name, char * (*function)(void))
{
	char   dirname[PATH_MAX];
	char   onemore[PATH_MAX];
	char * outname;
	char * expected;

	TEST_FEATURE ("with HOME set and without environment override");
	TEST_FILENAME (dirname);
	TEST_EQ (setenv ("HOME", dirname, 1), 0);
	TEST_EQ (mkdir (dirname, 0755), 0);
	TEST_EQ (unsetenv (env_var_name), 0);
	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			expected = NIH_MUST (nih_sprintf (NULL, "%s/%s", dirname, dir_name));
		}

		outname = NULL;
		outname = function ();

		if (! test_alloc_failed) {
			TEST_EQ_STR (outname, expected);
			_test_dir_created (expected);
		} else {
			TEST_EQ_P (outname, NULL);
		}

		if (outname)
			nih_free (outname);

		rmdir (expected);
		nih_free (expected);
	}

	TEST_FEATURE ("with HOME set and with empty environment override");
	TEST_EQ (setenv (env_var_name, "", 1), 0);


	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			expected = NIH_MUST (nih_sprintf (NULL, "%s/%s", dirname, dir_name));
		}
		outname = NULL;
		outname = function ();

		if (test_alloc_failed) {
			TEST_EQ_P (outname, NULL);
		} else {
			TEST_EQ_STR (outname, expected);
			_test_dir_created (expected);
		}
		if (outname)
			nih_free (outname);
		rmdir (expected);
		nih_free (expected);
	}

	TEST_FEATURE ("with HOME set and with relative environment override");
	TEST_EQ (setenv (env_var_name, "../", 1), 0);


	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			expected = NIH_MUST (nih_sprintf (NULL, "%s/%s", dirname, dir_name));
		}
		outname = NULL;
		outname = function ();

		if (test_alloc_failed) {
			TEST_EQ_P (outname, NULL);
		} else {
			TEST_EQ_STR (outname, expected);
			_test_dir_created (expected);
		}
		if (outname)
			nih_free (outname);
		rmdir (expected);
		nih_free (expected);
	}

	TEST_FEATURE ("with HOME set and with environment override");
	TEST_FILENAME (onemore);
	expected = NIH_MUST (nih_sprintf (NULL, "%s", onemore));
	TEST_EQ (setenv (env_var_name, expected, 1), 0);

	TEST_ALLOC_FAIL {
		outname = NULL;
		outname = function ();

		if (test_alloc_failed) {
			TEST_EQ_P (outname, NULL);
		} else {
			TEST_EQ_STR (outname, expected);
			_test_dir_created (expected);
		}
		if (outname)
			nih_free (outname);
		rmdir (expected);
	}

	TEST_EQ (rmdir (dirname), 0);

	TEST_FEATURE ("without HOME set and with environment override");
	TEST_EQ (unsetenv ("HOME"), 0);

	TEST_ALLOC_FAIL {
		outname = NULL;
		outname = function ();

		if (test_alloc_failed) {
			TEST_EQ_P (outname, NULL);
		} else {
			TEST_EQ_STR (outname, expected);
			_test_dir_created (expected);
		}
		if (outname)
			nih_free (outname);
		rmdir (expected);
	}
	nih_free(expected);

	TEST_FEATURE ("without HOME set and with empty environment override");
	TEST_EQ (setenv (env_var_name, "", 1), 0);

	TEST_ALLOC_FAIL {
		outname = NULL;
		outname = function ();
		TEST_EQ_P (outname, NULL);
	}

	TEST_FEATURE ("without HOME set and without environment override");
	TEST_EQ (unsetenv (env_var_name), 0);
	TEST_ALLOC_FAIL {
		outname = NULL;
		outname = function ();
		TEST_EQ_P (outname, NULL);
	}
}

void
test_get_config_home (void)
{
	TEST_FUNCTION ("xdg_get_config_home");
	_test_get_home ("XDG_CONFIG_HOME", ".config", &xdg_get_config_home);

}

void
test_get_cache_home (void)
{
	TEST_FUNCTION ("xdg_get_cache_home");
	_test_get_home ("XDG_CACHE_HOME", ".cache", &xdg_get_cache_home);
}

void
test_get_config_dirs (void)
{
	char   **dirs = NULL;

	TEST_FUNCTION ("xdg_get_config_dirs");
	TEST_FEATURE ("without environment override set");
	TEST_EQ (unsetenv ("XDG_CONFIG_DIRS"), 0);

	TEST_ALLOC_FAIL {
		dirs = NULL;
		dirs = xdg_get_config_dirs();

		if (test_alloc_failed) {
			TEST_EQ_P (dirs, NULL);
		} else {
			TEST_EQ_STR (dirs[0], "/etc/xdg");
			TEST_EQ (dirs[1], NULL);
			nih_free (dirs);
		}
	}

	TEST_FEATURE ("with empty environment override");
	TEST_EQ (setenv ("XDG_CONFIG_DIRS", "", 1), 0);
	TEST_ALLOC_FAIL {
		dirs = NULL;
		dirs = xdg_get_config_dirs();

		if (test_alloc_failed) {
			TEST_EQ_P (dirs, NULL);
		} else {
			TEST_EQ_STR (dirs[0], "/etc/xdg");
			TEST_EQ (dirs[1], NULL);
			nih_free (dirs);
		}
	}

	TEST_FEATURE ("with environment override set to single path");
	TEST_EQ (setenv ("XDG_CONFIG_DIRS", "/etc/xdg/xdg-test", 1), 0);
	TEST_ALLOC_FAIL {
		dirs = NULL;
		dirs = xdg_get_config_dirs();

		if (test_alloc_failed) {
			TEST_EQ_P (dirs, NULL);
		} else {
			TEST_EQ_STR (dirs[0], "/etc/xdg/xdg-test");
			TEST_EQ (dirs[1], NULL);
			nih_free (dirs);
		}
	}

	TEST_FEATURE ("with environment override set to multiple paths");
	TEST_FEATURE ("with environment override set to single path");
	TEST_EQ (setenv ("XDG_CONFIG_DIRS", "/etc/xdg/xdg-test:/etc/xdg/xdg-other", 1), 0);
	TEST_ALLOC_FAIL {
		dirs = NULL;
		dirs = xdg_get_config_dirs();

		if (test_alloc_failed) {
			TEST_EQ_P (dirs, NULL);
		} else {
			TEST_EQ_STR (dirs[0], "/etc/xdg/xdg-test");
			TEST_EQ_STR (dirs[1], "/etc/xdg/xdg-other");
			TEST_EQ (dirs[2], NULL);
			nih_free (dirs);
		}
	}
}

void
test_get_user_upstart_dirs (void)
{
	char   dirname[PATH_MAX];
	char      ** dirs = NULL;
	char       * path = NULL;
	char  ** expected = NULL;

	/* Currently only one test for "typical" output.
         * Not sure what else to test here.
         */
	TEST_FUNCTION ("get_user_upstart_dirs");

	TEST_FEATURE ("with HOME set");
	TEST_FILENAME (dirname);
	TEST_EQ (setenv ("HOME", dirname, 1), 0);
	TEST_EQ (mkdir (dirname, 0755), 0);
	TEST_EQ (unsetenv ("XDG_CONFIG_HOME"), 0);
	TEST_EQ (unsetenv ("XDG_CONFIG_DIRS"), 0);

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			expected = nih_str_array_new (NULL);
			path = NIH_MUST (nih_sprintf (NULL, "%s/.config/upstart", dirname));
			assert (nih_str_array_add (&expected, NULL, NULL, path));
			nih_free(path);
			path = NIH_MUST (nih_sprintf (NULL, "%s/.init", dirname));
			assert (nih_str_array_add (&expected, NULL, NULL, path));
			nih_free(path);
		}

		dirs = NULL;
		dirs = get_user_upstart_dirs ();

		if (test_alloc_failed) {
			TEST_EQ_P (dirs, NULL);
		} else {
			TEST_EQ_STR (dirs[0], expected[0]);
			//_test_dir_created (expected[0]);
			TEST_EQ_STR (dirs[1], expected[1]);
			TEST_EQ_STR (dirs[2], "/etc/xdg/upstart");
			TEST_EQ_STR (dirs[3], SYSTEM_USERCONFDIR);
			TEST_EQ (dirs[4], NULL);
			nih_free (dirs);
		}
		TEST_ALLOC_SAFE {
			rmdir (expected[0]);
			path = nih_sprintf (NULL, "%s/.config", dirname);
			rmdir (path);
			nih_free (path);
			nih_free (expected);
		}
	}

	TEST_FEATURE ("with some invalid XDG_CONFIG_DIRS");
	TEST_EQ (setenv ("XDG_CONFIG_DIRS", "/etc/xdg/xdg-subdir:../haha:/etc/xdg", 1), 0);

	TEST_ALLOC_FAIL {
		TEST_ALLOC_SAFE {
			expected = nih_str_array_new (NULL);
			path = NIH_MUST (nih_sprintf (NULL, "%s/.config/upstart", dirname));
			assert (nih_str_array_add (&expected, NULL, NULL, path));
			nih_free(path);
			path = NIH_MUST (nih_sprintf (NULL, "%s/.init", dirname));
			assert (nih_str_array_add (&expected, NULL, NULL, path));
			nih_free(path);
		}

		dirs = NULL;
		dirs = get_user_upstart_dirs ();

		if (test_alloc_failed) {
			TEST_EQ_P (dirs, NULL);
		} else {
			TEST_EQ_STR (dirs[0], expected[0]);
			_test_dir_created (expected[0]);
			TEST_EQ_STR (dirs[1], expected[1]);
			TEST_EQ_STR (dirs[2], "/etc/xdg/xdg-subdir/upstart");
			TEST_EQ_STR (dirs[3], "/etc/xdg/upstart");
			TEST_EQ_STR (dirs[4], SYSTEM_USERCONFDIR);
			TEST_EQ (dirs[5], NULL);
			nih_free (dirs);
		}
		TEST_ALLOC_SAFE {
			rmdir (expected[0]);
			path = nih_sprintf (NULL, "%s/.config", dirname);
			rmdir (path);
			nih_free (path);
			nih_free (expected);
		}
	}
	TEST_EQ (rmdir (dirname), 0);
}

void
test_get_user_log_dir (void)
{
	char dirname[PATH_MAX];
	char         *expected;
	char             *path;

	TEST_FUNCTION ("get_user_log_dir");
	TEST_FEATURE ("with HOME set");
	TEST_FILENAME (dirname);
	TEST_EQ (setenv ("HOME", dirname, 1), 0);
	TEST_EQ (mkdir (dirname, 0755), 0);
	TEST_EQ (unsetenv ("XDG_CACHE_HOME"), 0);

	expected = nih_sprintf (NULL, "%s/.cache/upstart", dirname);

	TEST_ALLOC_FAIL {
		path = get_user_log_dir ();
		if (test_alloc_failed) {
			TEST_EQ_P (path, NULL);
		} else {
			TEST_EQ_STR (path, expected);
			_test_dir_created (expected);
			nih_free (path);
		}
	}
	rmdir (expected);
	nih_free (expected);
	path = nih_sprintf (NULL, "%s/.cache", dirname);
	rmdir (path);
	nih_free (path);
	rmdir (dirname);
}

void
test_get_session_dir (void)
{
	char   dirname[PATH_MAX];
	char  *expected;
	char  *path;
	char  *orig_xdg_runtime_dir;

	orig_xdg_runtime_dir = getenv ("XDG_RUNTIME_DIR");

	TEST_FUNCTION ("get_session_dir");

	TEST_FEATURE ("with XDG_RUNTIME_DIR set");

	TEST_FILENAME (dirname);
	assert0 (setenv ("XDG_RUNTIME_DIR", dirname, 1));
	TEST_EQ (mkdir (dirname, 0755), 0);

	expected = nih_sprintf (NULL, "%s/upstart/sessions", dirname);

	TEST_ALLOC_FAIL {
		path = get_session_dir ();
		if (test_alloc_failed) {
			TEST_EQ_P (path, NULL);
		} else {
			TEST_EQ_STR (path, expected);
			_test_dir_created (expected);
			nih_free (path);
		}
	}

	if (orig_xdg_runtime_dir)
		setenv ("XDG_RUNTIME_DIR", orig_xdg_runtime_dir, 1);

	TEST_FEATURE ("with XDG_RUNTIME_DIR unset");
	assert0 (unsetenv ("XDG_RUNTIME_DIR"));

	/* no fallback */
	path = get_session_dir ();
	TEST_EQ_P (path, NULL);

	rmdir (expected);
	nih_free (expected);
	path = nih_sprintf (NULL, "%s/upstart", dirname);
	rmdir (path);
	nih_free (path);
	rmdir (dirname);

	if (orig_xdg_runtime_dir)
		setenv ("XDG_RUNTIME_DIR", orig_xdg_runtime_dir, 1);
}

int
main (int   argc,
      char *argv[])
{
	test_common_setup ();

	test_get_home_subdir ();
	test_get_config_home ();
	test_get_config_dirs ();
	test_get_user_upstart_dirs ();
	test_get_cache_home ();
	test_get_user_log_dir ();
	test_get_session_dir ();

	test_common_cleanup ();

	return 0;
}
