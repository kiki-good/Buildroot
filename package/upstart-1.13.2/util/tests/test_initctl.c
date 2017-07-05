/* upstart
 *
 * test_initctl.c - test suite for util/initctl.c
 *
 * Copyright © 2010 Canonical Ltd.
 * Authors: Scott James Remnant <scott@netsplit.com>,
 *          James Hunt <james.hunt@canonical.com>.
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
#include <nih/file.h>
#include <nih-dbus/test_dbus.h>

#include <dbus/dbus.h>

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <regex.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

#include <nih-dbus/dbus_error.h>
#include <nih-dbus/dbus_connection.h>
#include <nih-dbus/dbus_proxy.h>
#include <nih-dbus/errors.h>

#include <nih/macros.h>
#include <nih/timer.h>
#include <nih/signal.h>
#include <nih/child.h>
#include <nih/main.h>
#include <nih/command.h>
#include <nih/error.h>
#include <nih/file.h>
#include <nih/string.h>

#include "dbus/upstart.h"

#include "com.ubuntu.Upstart.h"

#include "test_util_common.h"

extern int use_dbus;
extern int user_mode;
extern int dbus_bus_type;
extern char *dest_name;
extern const char *dest_address;
extern int no_wait;

extern NihDBusProxy *upstart_open (const void *parent)
	__attribute__ ((warn_unused_result));
extern char *        job_status   (const void *parent,
				   NihDBusProxy *job_class, NihDBusProxy *job)
	__attribute__ ((warn_unused_result));

extern int start_action                (NihCommand *command, char * const *args);
extern int stop_action                 (NihCommand *command, char * const *args);
extern int restart_action              (NihCommand *command, char * const *args);
extern int reload_action               (NihCommand *command, char * const *args);
extern int status_action               (NihCommand *command, char * const *args);
extern int list_action                 (NihCommand *command, char * const *args);
extern int emit_action                 (NihCommand *command, char * const *args);
extern int reload_configuration_action (NihCommand *command, char * const *args);
extern int version_action              (NihCommand *command, char * const *args);
extern int log_priority_action         (NihCommand *command, char * const *args);
extern int usage_action                (NihCommand *command, char * const *args);


static int my_connect_handler_called = FALSE;
static DBusConnection *last_connection = NULL;

static int
my_connect_handler (DBusServer *    server,
		    DBusConnection *connection)
{
	my_connect_handler_called++;

	last_connection = connection;

	nih_main_loop_exit (0);

	return TRUE;
}

void
test_upstart_open (void)
{
	DBusServer *    server = NULL;
	pid_t           dbus_pid;
	DBusConnection *server_conn = NULL;
	NihDBusProxy *  proxy = NULL;
	FILE *          output;

	TEST_FUNCTION ("upstart_open");
	output = tmpfile ();


	/* Check that we can create a proxy to Upstart's private internal
	 * server, and that this is the default behaviour if we don't
	 * fiddle with the other options.  The returned proxy should
	 * hold the only reference to the connection.
	 */
	TEST_FEATURE ("with private connection");
	unsetenv ("UPSTART_SESSION");

	TEST_ALLOC_FAIL {
		use_dbus = FALSE;
		dest_name = NULL;
		dest_address = "unix:abstract=/com/ubuntu/upstart/test_initctl";

		TEST_ALLOC_SAFE {
			server = nih_dbus_server (dest_address,
						  my_connect_handler,
						  NULL);
			assert (server != NULL);
		}

		my_connect_handler_called = FALSE;
		last_connection = NULL;

		TEST_DIVERT_STDERR (output) {
			proxy = upstart_open (NULL);
		}
		rewind (output);

		if (test_alloc_failed
		    && (proxy == NULL)) {
			TEST_FILE_EQ (output, "test: Cannot allocate memory\n");
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			if (last_connection) {
				dbus_connection_close (last_connection);
				dbus_connection_unref (last_connection);
			}

			dbus_server_disconnect (server);
			dbus_server_unref (server);

			dbus_shutdown ();
			continue;
		}

		nih_main_loop ();

		TEST_TRUE (my_connect_handler_called);
		TEST_NE_P (last_connection, NULL);

		TEST_NE_P (proxy, NULL);
		TEST_ALLOC_SIZE (proxy, sizeof (NihDBusProxy));

		TEST_NE_P (proxy->connection, NULL);
		TEST_EQ_P (proxy->name, NULL);
		TEST_EQ_P (proxy->owner, NULL);
		TEST_EQ_STR (proxy->path, DBUS_PATH_UPSTART);
		TEST_ALLOC_PARENT (proxy->path, proxy);
		TEST_FALSE (proxy->auto_start);

		TEST_EQ_P (proxy->lost_handler, NULL);
		TEST_EQ_P (proxy->data, NULL);

		nih_free (proxy);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		dbus_connection_close (last_connection);
		dbus_connection_unref (last_connection);

		dbus_server_disconnect (server);
		dbus_server_unref (server);

		dbus_shutdown ();
	}

	/* Check that we can create a proxy to Upstart's private internal
	 * server in user mode, and that this is the default behaviour if we don't
	 * fiddle with the other options.  The returned proxy should
	 * hold the only reference to the connection.
	 */
	TEST_FEATURE ("with user-mode");
	TEST_ALLOC_FAIL {
		use_dbus = -1;
		dbus_bus_type = -1;
		dest_name = NULL;
		dest_address = DBUS_ADDRESS_UPSTART;
		user_mode = TRUE;

		assert0 (setenv ("UPSTART_SESSION",
				 "unix:abstract=/com/ubuntu/upstart/test-session",
				 TRUE));

		TEST_ALLOC_SAFE {
			server = nih_dbus_server (getenv ("UPSTART_SESSION"),
						  my_connect_handler,
						  NULL);
			assert (server != NULL);
		}

		my_connect_handler_called = FALSE;
		last_connection = NULL;

		TEST_DIVERT_STDERR (output) {
			proxy = upstart_open (NULL);
		}
		rewind (output);

		if (test_alloc_failed
		    && (proxy == NULL)) {
			TEST_FILE_EQ (output, "test: Cannot allocate memory\n");
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			if (last_connection) {
				dbus_connection_close (last_connection);
				dbus_connection_unref (last_connection);
			}

			dbus_server_disconnect (server);
			dbus_server_unref (server);

			dbus_shutdown ();
			continue;
		}

		nih_main_loop ();

		TEST_TRUE (my_connect_handler_called);
		TEST_NE_P (last_connection, NULL);

		TEST_NE_P (proxy, NULL);
		TEST_ALLOC_SIZE (proxy, sizeof (NihDBusProxy));

		TEST_NE_P (proxy->connection, NULL);
		TEST_EQ_P (proxy->name, NULL);
		TEST_EQ_P (proxy->owner, NULL);
		TEST_EQ_STR (proxy->path, DBUS_PATH_UPSTART);
		TEST_ALLOC_PARENT (proxy->path, proxy);
		TEST_FALSE (proxy->auto_start);

		TEST_EQ_P (proxy->lost_handler, NULL);
		TEST_EQ_P (proxy->data, NULL);

		nih_free (proxy);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		dbus_connection_close (last_connection);
		dbus_connection_unref (last_connection);

		dbus_server_disconnect (server);
		dbus_server_unref (server);

		dbus_shutdown ();

		unsetenv ("UPSTART_SESSION");
		user_mode = FALSE;
	}


	/* Check that we can create a connection to Upstart via the system
	 * bus.  The returned proxy should use the default name on that
	 * bus.
	 */
	TEST_FEATURE ("with system bus connection");
	TEST_ALLOC_FAIL {
		use_dbus = TRUE;
		dbus_bus_type = DBUS_BUS_SYSTEM;
		dest_name = NULL;
		dest_address = DBUS_ADDRESS_UPSTART;

		TEST_DBUS (dbus_pid);
		TEST_DBUS_OPEN (server_conn);

		assert (dbus_bus_request_name (server_conn, DBUS_SERVICE_UPSTART,
					       0, NULL)
			== DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER);

		TEST_DIVERT_STDERR (output) {
			proxy = upstart_open (NULL);
		}
		rewind (output);

		if (test_alloc_failed
		    && (proxy == NULL)) {
			TEST_FILE_EQ (output, "test: Cannot allocate memory\n");
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_DBUS_CLOSE (server_conn);
			TEST_DBUS_END (dbus_pid);

			dbus_shutdown ();
			continue;
		}

		TEST_NE_P (proxy, NULL);
		TEST_ALLOC_SIZE (proxy, sizeof (NihDBusProxy));

		TEST_NE_P (proxy->connection, NULL);
		TEST_EQ_STR (proxy->name, DBUS_SERVICE_UPSTART);
		TEST_ALLOC_PARENT (proxy->name, proxy);
		TEST_EQ_STR (proxy->owner, dbus_bus_get_unique_name (server_conn));
		TEST_ALLOC_PARENT (proxy->owner, proxy);
		TEST_EQ_STR (proxy->path, DBUS_PATH_UPSTART);
		TEST_ALLOC_PARENT (proxy->path, proxy);
		TEST_FALSE (proxy->auto_start);

		TEST_EQ_P (proxy->lost_handler, NULL);
		TEST_EQ_P (proxy->data, NULL);

		nih_free (proxy);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_DBUS_CLOSE (server_conn);
		TEST_DBUS_END (dbus_pid);

		dbus_shutdown ();
	}


	/* Check that we can create a connection to Upstart via the system
	 * bus and a different well known name.
	 */
	TEST_FEATURE ("with system bus connection and different name");
	TEST_ALLOC_FAIL {
		use_dbus = TRUE;
		dbus_bus_type = DBUS_BUS_SYSTEM;
		dest_name = "com.ubuntu.UpstartTest";
		dest_address = DBUS_ADDRESS_UPSTART;

		TEST_DBUS (dbus_pid);
		TEST_DBUS_OPEN (server_conn);

		assert (dbus_bus_request_name (server_conn, "com.ubuntu.UpstartTest",
					       0, NULL)
			== DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER);

		TEST_DIVERT_STDERR (output) {
			proxy = upstart_open (NULL);
		}
		rewind (output);

		if (test_alloc_failed
		    && (proxy == NULL)) {
			TEST_FILE_EQ (output, "test: Cannot allocate memory\n");
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_DBUS_CLOSE (server_conn);
			TEST_DBUS_END (dbus_pid);

			dbus_shutdown ();
			continue;
		}

		TEST_NE_P (proxy, NULL);
		TEST_ALLOC_SIZE (proxy, sizeof (NihDBusProxy));

		TEST_NE_P (proxy->connection, NULL);
		TEST_EQ_STR (proxy->name, "com.ubuntu.UpstartTest");
		TEST_ALLOC_PARENT (proxy->name, proxy);
		TEST_EQ_STR (proxy->owner, dbus_bus_get_unique_name (server_conn));
		TEST_ALLOC_PARENT (proxy->owner, proxy);
		TEST_EQ_STR (proxy->path, DBUS_PATH_UPSTART);
		TEST_ALLOC_PARENT (proxy->path, proxy);
		TEST_FALSE (proxy->auto_start);

		TEST_EQ_P (proxy->lost_handler, NULL);
		TEST_EQ_P (proxy->data, NULL);

		nih_free (proxy);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_DBUS_CLOSE (server_conn);
		TEST_DBUS_END (dbus_pid);

		dbus_shutdown ();
	}


	/* Check that when we attempt to connect to Upstart's private
	 * internal server, and it's not listening, that an appropriate
	 * error is output.
	 */
	TEST_FEATURE ("with non-listening private connection");
	TEST_ALLOC_FAIL {
		use_dbus = FALSE;
		dest_name = NULL;
		dest_address = "unix:abstract=/com/ubuntu/upstart/test";

		TEST_DIVERT_STDERR (output) {
			proxy = upstart_open (NULL);
		}
		rewind (output);

		TEST_EQ_P (proxy, NULL);

		TEST_FILE_EQ (output, ("test: Unable to connect to Upstart: "
				       "Failed to connect to socket /com/ubuntu/upstart/test: "
				       "Connection refused\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		dbus_shutdown ();
	}


	/* Check that when we attempt to connect to the system bus,
	 * and it's not listening, that an appropriate error is output.
	 */
	TEST_FEATURE ("with non-listening system bus");
	TEST_ALLOC_FAIL {
		use_dbus = TRUE;
		dbus_bus_type = DBUS_BUS_SYSTEM;
		dest_name = NULL;
		dest_address = DBUS_ADDRESS_UPSTART;

		assert0 (setenv ("DBUS_SYSTEM_BUS_ADDRESS",
				 "unix:abstract=/com/ubuntu/upstart/test",
				 TRUE));

		TEST_DIVERT_STDERR (output) {
			proxy = upstart_open (NULL);
		}
		rewind (output);

		TEST_EQ_P (proxy, NULL);

		TEST_FILE_EQ (output, ("test: Unable to connect to system bus: "
				       "Failed to connect to socket /com/ubuntu/upstart/test: "
				       "Connection refused\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		dbus_shutdown ();

		unsetenv ("DBUS_SYSTEM_BUS_ADDRESS");
	}


	/* Check that an error and suggestion for help is output
	 * when --dest is given without --system.
	 */
	TEST_FEATURE ("with --dest but without --system");
	TEST_ALLOC_FAIL {
		use_dbus = FALSE;
		dest_name = "com.ubuntu.Upstart";
		dest_address = DBUS_ADDRESS_UPSTART;

		TEST_DIVERT_STDERR (output) {
			proxy = upstart_open (NULL);
		}
		rewind (output);

		TEST_EQ_P (proxy, NULL);

		TEST_FILE_EQ (output, "test: --dest given without --system\n");
		TEST_FILE_EQ (output, "Try `test --help' for more information.\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		dbus_shutdown ();
	}


	/* Check that when we attempt to connect to Upstart in user mode but
	 * without UPSTART_SESSION set in the environment, an appropriate
	 * error is output.
	 */
	TEST_FEATURE ("with user-mode and no target");
	TEST_ALLOC_FAIL {
		use_dbus = -1;
		dbus_bus_type = -1;
		dest_name = NULL;
		dest_address = DBUS_ADDRESS_UPSTART;
		user_mode = TRUE;

		unsetenv ("UPSTART_SESSION");

		TEST_DIVERT_STDERR (output) {
			proxy = upstart_open (NULL);
		}
		rewind (output);

		TEST_EQ_P (proxy, NULL);

		TEST_FILE_EQ (output, ("test: UPSTART_SESSION isn't set in the environment. "
				       "Unable to locate the Upstart instance.\n"));
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		dbus_shutdown ();
		user_mode = FALSE;
	}

	fclose (output);
}


void
test_job_status (void)
{
	pid_t           dbus_pid;
	DBusConnection *server_conn;
	DBusConnection *client_conn;
	pid_t           server_pid;
	DBusMessage *   method_call;
	const char *    interface;
	const char *    property;
	DBusMessage *   reply = NULL;
	DBusMessageIter iter;
	DBusMessageIter arrayiter;
	DBusMessageIter dictiter;
	DBusMessageIter subiter;
	DBusMessageIter prociter;
	DBusMessageIter structiter;
	const char *    str_value;
	int32_t         int32_value;
	NihDBusProxy *  job_class = NULL;
	NihDBusProxy *  job = NULL;
	char *          str;
	NihError *      err;
	NihDBusError *  dbus_err;
	int             status;

	TEST_FUNCTION ("job_status");
	TEST_DBUS (dbus_pid);
	TEST_DBUS_OPEN (server_conn);
	TEST_DBUS_OPEN (client_conn);


	/* Check that we can generate a string for a job instance that
	 * is running with a main process.  The function should request
	 * the name of the job class, and then request all of the
	 * properties of the job instance.
	 */
	TEST_FEATURE ("with running main process");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Get call for the name, reply with the
			 * name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "test";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAll call for the properties, reply
			 * with the properties.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"GetAll"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test/_");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_VARIANT_AS_STRING
								   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
								  &arrayiter);

				/* Name */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "name";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Goal */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "goal";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "start";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* State */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "state";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "running";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Processes */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "processes";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  (DBUS_TYPE_ARRAY_AS_STRING
								   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &subiter);

				dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
								  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &prociter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "main";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 3648;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_close_container (&subiter, &prociter);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (client_conn);
			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		TEST_ALLOC_SAFE {
			job_class = nih_dbus_proxy_new (NULL, client_conn,
							dbus_bus_get_unique_name (server_conn),
							DBUS_PATH_UPSTART "/jobs/test",
							NULL, NULL);
			job = nih_dbus_proxy_new (NULL, client_conn,
						  dbus_bus_get_unique_name (server_conn),
						  DBUS_PATH_UPSTART "/jobs/test/_",
						  NULL, NULL);
		}

		str = job_status (NULL, job_class, job);

		if (test_alloc_failed
		    && (str == NULL)) {
			err = nih_error_get ();
			TEST_EQ (err->number, ENOMEM);
			nih_free (err);

			nih_free (job);
			nih_free (job_class);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ_STR (str, "test start/running, process 3648");

		nih_free (str);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
		nih_free (job_class);
	}


	/* Check that we can generate a string for a named job instance,
	 * the name should be placed in the returned string in brackets
	 * after the job config name.
	 */
	TEST_FEATURE ("with named instance");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Get call for the name, reply with the
			 * name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "test";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAll call for the properties, reply
			 * with the properties.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"GetAll"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test/beetroot");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_VARIANT_AS_STRING
								   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
								  &arrayiter);

				/* Name */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "name";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "beetroot";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Goal */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "goal";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "start";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* State */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "state";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "running";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Processes */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "processes";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  (DBUS_TYPE_ARRAY_AS_STRING
								   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &subiter);

				dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
								  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &prociter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "main";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 3648;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_close_container (&subiter, &prociter);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (client_conn);
			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		TEST_ALLOC_SAFE {
			job_class = nih_dbus_proxy_new (NULL, client_conn,
							dbus_bus_get_unique_name (server_conn),
							DBUS_PATH_UPSTART "/jobs/test",
							NULL, NULL);
			job = nih_dbus_proxy_new (NULL, client_conn,
						  dbus_bus_get_unique_name (server_conn),
						  DBUS_PATH_UPSTART "/jobs/test/beetroot",
						  NULL, NULL);
		}

		str = job_status (NULL, job_class, job);

		if (test_alloc_failed
		    && (str == NULL)) {
			err = nih_error_get ();
			TEST_EQ (err->number, ENOMEM);
			nih_free (err);

			nih_free (job);
			nih_free (job_class);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ_STR (str, "test (beetroot) start/running, process 3648");

		nih_free (str);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
		nih_free (job_class);
	}


	/* Check that we can generate a string for a job instance in a
	 * state that doesn't come with a process, only the goal and
	 * state should be output.
	 */
	TEST_FEATURE ("with no process");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Get call for the name, reply with the
			 * name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "test";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAll call for the properties, reply
			 * with the properties.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"GetAll"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test/_");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_VARIANT_AS_STRING
								   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
								  &arrayiter);

				/* Name */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "name";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Goal */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "goal";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "stop";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* State */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "state";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "stopping";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Processes */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "processes";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  (DBUS_TYPE_ARRAY_AS_STRING
								   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &subiter);

				dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
								  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &prociter);

				dbus_message_iter_close_container (&subiter, &prociter);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (client_conn);
			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		TEST_ALLOC_SAFE {
			job_class = nih_dbus_proxy_new (NULL, client_conn,
							dbus_bus_get_unique_name (server_conn),
							DBUS_PATH_UPSTART "/jobs/test",
							NULL, NULL);
			job = nih_dbus_proxy_new (NULL, client_conn,
						  dbus_bus_get_unique_name (server_conn),
						  DBUS_PATH_UPSTART "/jobs/test/_",
						  NULL, NULL);
		}

		str = job_status (NULL, job_class, job);

		if (test_alloc_failed
		    && (str == NULL)) {
			err = nih_error_get ();
			TEST_EQ (err->number, ENOMEM);
			nih_free (err);

			nih_free (job);
			nih_free (job_class);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ_STR (str, "test stop/stopping");

		nih_free (str);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
		nih_free (job_class);
	}


	/* Check that we can generate a string for a job instance with
	 * a running pre-start process, since this is a standard state
	 * with a process, the pid should simply follow the state.
	 */
	TEST_FEATURE ("with running pre-start process");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Get call for the name, reply with the
			 * name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "test";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAll call for the properties, reply
			 * with the properties.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"GetAll"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test/_");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_VARIANT_AS_STRING
								   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
								  &arrayiter);

				/* Name */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "name";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Goal */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "goal";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "start";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* State */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "state";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "pre-start";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Processes */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "processes";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  (DBUS_TYPE_ARRAY_AS_STRING
								   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &subiter);

				dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
								  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &prociter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "pre-start";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 1014;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_close_container (&subiter, &prociter);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (client_conn);
			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		TEST_ALLOC_SAFE {
			job_class = nih_dbus_proxy_new (NULL, client_conn,
							dbus_bus_get_unique_name (server_conn),
							DBUS_PATH_UPSTART "/jobs/test",
							NULL, NULL);
			job = nih_dbus_proxy_new (NULL, client_conn,
						  dbus_bus_get_unique_name (server_conn),
						  DBUS_PATH_UPSTART "/jobs/test/_",
						  NULL, NULL);
		}

		str = job_status (NULL, job_class, job);

		if (test_alloc_failed
		    && (str == NULL)) {
			err = nih_error_get ();
			TEST_EQ (err->number, ENOMEM);
			nih_free (err);

			nih_free (job);
			nih_free (job_class);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ_STR (str, "test start/pre-start, process 1014");

		nih_free (str);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
		nih_free (job_class);
	}


	/* Check that we can generate a string for a job instance with
	 * a running post-stop process, since this is a standard state
	 * with a process, the pid should simply follow the state.
	 */
	TEST_FEATURE ("with running post-stop process");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Get call for the name, reply with the
			 * name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "test";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAll call for the properties, reply
			 * with the properties.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"GetAll"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test/_");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_VARIANT_AS_STRING
								   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
								  &arrayiter);

				/* Name */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "name";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Goal */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "goal";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "stop";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* State */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "state";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "post-stop";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Processes */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "processes";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  (DBUS_TYPE_ARRAY_AS_STRING
								   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &subiter);

				dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
								  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &prociter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "post-stop";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 9764;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_close_container (&subiter, &prociter);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (client_conn);
			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		TEST_ALLOC_SAFE {
			job_class = nih_dbus_proxy_new (NULL, client_conn,
							dbus_bus_get_unique_name (server_conn),
							DBUS_PATH_UPSTART "/jobs/test",
							NULL, NULL);
			job = nih_dbus_proxy_new (NULL, client_conn,
						  dbus_bus_get_unique_name (server_conn),
						  DBUS_PATH_UPSTART "/jobs/test/_",
						  NULL, NULL);
		}

		str = job_status (NULL, job_class, job);

		if (test_alloc_failed
		    && (str == NULL)) {
			err = nih_error_get ();
			TEST_EQ (err->number, ENOMEM);
			nih_free (err);

			nih_free (job);
			nih_free (job_class);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ_STR (str, "test stop/post-stop, process 9764");

		nih_free (str);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
		nih_free (job_class);
	}


	/* Check that we can generate a string for a job instance with
	 * a running post-start process, but no main process.  Since this
	 * is not a standard state process, the process name should be
	 * prefixed.
	 */
	TEST_FEATURE ("with running post-start process only");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Get call for the name, reply with the
			 * name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "test";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAll call for the properties, reply
			 * with the properties.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"GetAll"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test/_");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_VARIANT_AS_STRING
								   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
								  &arrayiter);

				/* Name */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "name";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Goal */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "goal";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "start";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* State */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "state";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "post-start";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Processes */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "processes";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  (DBUS_TYPE_ARRAY_AS_STRING
								   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &subiter);

				dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
								  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &prociter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "post-start";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 2137;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_close_container (&subiter, &prociter);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (client_conn);
			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		TEST_ALLOC_SAFE {
			job_class = nih_dbus_proxy_new (NULL, client_conn,
							dbus_bus_get_unique_name (server_conn),
							DBUS_PATH_UPSTART "/jobs/test",
							NULL, NULL);
			job = nih_dbus_proxy_new (NULL, client_conn,
						  dbus_bus_get_unique_name (server_conn),
						  DBUS_PATH_UPSTART "/jobs/test/_",
						  NULL, NULL);
		}

		str = job_status (NULL, job_class, job);

		if (test_alloc_failed
		    && (str == NULL)) {
			err = nih_error_get ();
			TEST_EQ (err->number, ENOMEM);
			nih_free (err);

			nih_free (job);
			nih_free (job_class);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ_STR (str, "test start/post-start, (post-start) process 2137");

		nih_free (str);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
		nih_free (job_class);
	}


	/* Check that we can generate a string for a job instance with
	 * a running pre-stop process, but no main process.  Since this
	 * is not a standard state process, the process name should be
	 * prefixed.
	 */
	TEST_FEATURE ("with running pre-stop process only");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Get call for the name, reply with the
			 * name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "test";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAll call for the properties, reply
			 * with the properties.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"GetAll"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test/_");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_VARIANT_AS_STRING
								   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
								  &arrayiter);

				/* Name */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "name";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Goal */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "goal";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "stop";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* State */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "state";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "pre-stop";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Processes */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "processes";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  (DBUS_TYPE_ARRAY_AS_STRING
								   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &subiter);

				dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
								  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &prociter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "pre-stop";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 7864;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_close_container (&subiter, &prociter);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (client_conn);
			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		TEST_ALLOC_SAFE {
			job_class = nih_dbus_proxy_new (NULL, client_conn,
							dbus_bus_get_unique_name (server_conn),
							DBUS_PATH_UPSTART "/jobs/test",
							NULL, NULL);
			job = nih_dbus_proxy_new (NULL, client_conn,
						  dbus_bus_get_unique_name (server_conn),
						  DBUS_PATH_UPSTART "/jobs/test/_",
						  NULL, NULL);
		}

		str = job_status (NULL, job_class, job);

		if (test_alloc_failed
		    && (str == NULL)) {
			err = nih_error_get ();
			TEST_EQ (err->number, ENOMEM);
			nih_free (err);

			nih_free (job);
			nih_free (job_class);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ_STR (str, "test stop/pre-stop, (pre-stop) process 7864");

		nih_free (str);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
		nih_free (job_class);
	}

	/* Check that we can generate a string for a job instance that
	 * is running with a main process and a simultaneous post-start
	 * process.  The main process should be output on the first line
	 * along with the state, the pid of the post-start process should
	 * follow indented on the next line.
	 */
	TEST_FEATURE ("with running main and post-start processes");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Get call for the name, reply with the
			 * name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "test";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAll call for the properties, reply
			 * with the properties.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"GetAll"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test/_");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_VARIANT_AS_STRING
								   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
								  &arrayiter);

				/* Name */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "name";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Goal */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "goal";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "start";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* State */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "state";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "post-start";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Processes */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "processes";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  (DBUS_TYPE_ARRAY_AS_STRING
								   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &subiter);

				dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
								  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &prociter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "main";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 3648;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "post-start";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 2137;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_close_container (&subiter, &prociter);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (client_conn);
			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		TEST_ALLOC_SAFE {
			job_class = nih_dbus_proxy_new (NULL, client_conn,
							dbus_bus_get_unique_name (server_conn),
							DBUS_PATH_UPSTART "/jobs/test",
							NULL, NULL);
			job = nih_dbus_proxy_new (NULL, client_conn,
						  dbus_bus_get_unique_name (server_conn),
						  DBUS_PATH_UPSTART "/jobs/test/_",
						  NULL, NULL);
		}

		str = job_status (NULL, job_class, job);

		if (test_alloc_failed
		    && (str == NULL)) {
			err = nih_error_get ();
			TEST_EQ (err->number, ENOMEM);
			nih_free (err);

			nih_free (job);
			nih_free (job_class);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ_STR (str, ("test start/post-start, process 3648\n"
				   "\tpost-start process 2137"));

		nih_free (str);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
		nih_free (job_class);
	}


	/* Check that we can generate a string for a job instance that
	 * is running with a main process and a simultaneous pre-stop
	 * process.  The main process should be output on the first line
	 * along with the state, the pid of the pre-stop process should
	 * follow indented on the next line.
	 */
	TEST_FEATURE ("with running main and pre-stop processes");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Get call for the name, reply with the
			 * name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "test";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAll call for the properties, reply
			 * with the properties.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"GetAll"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test/_");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_VARIANT_AS_STRING
								   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
								  &arrayiter);

				/* Name */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "name";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Goal */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "goal";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "stop";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* State */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "state";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "pre-stop";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Processes */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "processes";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  (DBUS_TYPE_ARRAY_AS_STRING
								   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &subiter);

				dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
								  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &prociter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "main";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 3648;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "pre-stop";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 7864;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_close_container (&subiter, &prociter);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (client_conn);
			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		TEST_ALLOC_SAFE {
			job_class = nih_dbus_proxy_new (NULL, client_conn,
							dbus_bus_get_unique_name (server_conn),
							DBUS_PATH_UPSTART "/jobs/test",
							NULL, NULL);
			job = nih_dbus_proxy_new (NULL, client_conn,
						  dbus_bus_get_unique_name (server_conn),
						  DBUS_PATH_UPSTART "/jobs/test/_",
						  NULL, NULL);
		}

		str = job_status (NULL, job_class, job);

		if (test_alloc_failed
		    && (str == NULL)) {
			err = nih_error_get ();
			TEST_EQ (err->number, ENOMEM);
			nih_free (err);

			nih_free (job);
			nih_free (job_class);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ_STR (str, ("test stop/pre-stop, process 3648\n"
				   "\tpre-stop process 7864"));

		nih_free (str);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
		nih_free (job_class);
	}


	/* Check that we can generate a string for a job instance that
	 * is running with a main process, but in one of the "unusual"
	 * states to catch the process in.  The process should be output
	 * as normal.
	 */
	TEST_FEATURE ("with running main process in spawned state");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Get call for the name, reply with the
			 * name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "test";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAll call for the properties, reply
			 * with the properties.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"GetAll"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test/_");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_VARIANT_AS_STRING
								   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
								  &arrayiter);

				/* Name */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "name";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Goal */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "goal";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "start";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* State */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "state";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "spawned";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Processes */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "processes";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  (DBUS_TYPE_ARRAY_AS_STRING
								   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &subiter);

				dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
								  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &prociter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "main";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 3648;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_close_container (&subiter, &prociter);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (client_conn);
			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		TEST_ALLOC_SAFE {
			job_class = nih_dbus_proxy_new (NULL, client_conn,
							dbus_bus_get_unique_name (server_conn),
							DBUS_PATH_UPSTART "/jobs/test",
							NULL, NULL);
			job = nih_dbus_proxy_new (NULL, client_conn,
						  dbus_bus_get_unique_name (server_conn),
						  DBUS_PATH_UPSTART "/jobs/test/_",
						  NULL, NULL);
		}

		str = job_status (NULL, job_class, job);

		if (test_alloc_failed
		    && (str == NULL)) {
			err = nih_error_get ();
			TEST_EQ (err->number, ENOMEM);
			nih_free (err);

			nih_free (job);
			nih_free (job_class);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ_STR (str, "test start/spawned, process 3648");

		nih_free (str);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
		nih_free (job_class);
	}


	/* Check that the function catches the job instance going away
	 * in the mean time (and the server returning the unknown method
	 * error), and handles that as an instance that has freshly
	 * stopped.
	 */
	TEST_FEATURE ("with unknown instance");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Get call for the name, reply with the
			 * name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "test";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAll call for the properties, reply
			 * with the unknown method error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"GetAll"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test/_");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (client_conn);
			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		TEST_ALLOC_SAFE {
			job_class = nih_dbus_proxy_new (NULL, client_conn,
							dbus_bus_get_unique_name (server_conn),
							DBUS_PATH_UPSTART "/jobs/test",
							NULL, NULL);
			job = nih_dbus_proxy_new (NULL, client_conn,
						  dbus_bus_get_unique_name (server_conn),
						  DBUS_PATH_UPSTART "/jobs/test/_",
						  NULL, NULL);
		}

		str = job_status (NULL, job_class, job);

		if (test_alloc_failed
		    && (str == NULL)) {
			err = nih_error_get ();
			TEST_EQ (err->number, ENOMEM);
			nih_free (err);

			nih_free (job);
			nih_free (job_class);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ_STR (str, "test stop/waiting");

		nih_free (str);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
		nih_free (job_class);
	}


	/* Check that NULL can be given as the job instance, and that the
	 * function only requests the name of the job class and outputs
	 * as if there was no instance.
	 */
	TEST_FEATURE ("with NULL for instance");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Get call for the name, reply with the
			 * name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "test";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (client_conn);
			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		TEST_ALLOC_SAFE {
			job_class = nih_dbus_proxy_new (NULL, client_conn,
							dbus_bus_get_unique_name (server_conn),
							DBUS_PATH_UPSTART "/jobs/test",
							NULL, NULL);
		}

		str = job_status (NULL, job_class, NULL);

		if (test_alloc_failed
		    && (str == NULL)) {
			err = nih_error_get ();
			TEST_EQ (err->number, ENOMEM);
			nih_free (err);

			nih_free (job_class);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ_STR (str, "test stop/waiting");

		nih_free (str);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job_class);
	}


	/* Check that when the function is passed a bad job class proxy,
	 * it returns the error received from the server.
	 */
	TEST_FEATURE ("with bad job class");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Get call for the name, reply with an
			 * error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (client_conn);
			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		TEST_ALLOC_SAFE {
			job_class = nih_dbus_proxy_new (NULL, client_conn,
							dbus_bus_get_unique_name (server_conn),
							DBUS_PATH_UPSTART "/jobs/test",
							NULL, NULL);
			job = nih_dbus_proxy_new (NULL, client_conn,
						  dbus_bus_get_unique_name (server_conn),
						  DBUS_PATH_UPSTART "/jobs/test/_",
						  NULL, NULL);
		}

		str = job_status (NULL, job_class, job);

		TEST_EQ_P (str, NULL);

		err = nih_error_get ();

		if (test_alloc_failed
		    && (err->number == ENOMEM)) {
			nih_free (err);

			nih_free (job);
			nih_free (job_class);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (err->number, NIH_DBUS_ERROR);
		TEST_ALLOC_SIZE (err, sizeof (NihDBusError));
		dbus_err = (NihDBusError *)err;

		TEST_EQ_STR (dbus_err->name, DBUS_ERROR_UNKNOWN_METHOD);
		nih_free (dbus_err);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		nih_free (job);
		nih_free (job_class);
	}


	TEST_DBUS_CLOSE (client_conn);
	TEST_DBUS_CLOSE (server_conn);
	TEST_DBUS_END (dbus_pid);

	dbus_shutdown ();
}


void
test_start_action (void)
{
	pid_t           dbus_pid;
	DBusConnection *server_conn;
	FILE *          output;
	FILE *          errors;
	pid_t           server_pid;
	DBusMessage *   method_call;
	DBusMessage *   reply = NULL;
	const char *    name_value;
	char **         args_value;
	int             args_elements;
	int             wait_value;
	const char *    str_value;
	const char *    interface;
	const char *    property;
	DBusMessageIter iter;
	DBusMessageIter subiter;
	DBusMessageIter arrayiter;
	DBusMessageIter dictiter;
	DBusMessageIter prociter;
	DBusMessageIter structiter;
	int32_t         int32_value;
	NihCommand      command;
	char *          args[4];
	int             ret = 0;
	int             status;

	TEST_FUNCTION ("start_action");
	TEST_DBUS (dbus_pid);
	TEST_DBUS_OPEN (server_conn);

	assert (dbus_bus_request_name (server_conn, DBUS_SERVICE_UPSTART,
				       0, NULL)
			== DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER);

	TEST_DBUS_MESSAGE (server_conn, method_call);
	assert (dbus_message_is_signal (method_call, DBUS_INTERFACE_DBUS,
					"NameAcquired"));
	dbus_message_unref (method_call);

	use_dbus = TRUE;
	dbus_bus_type = DBUS_BUS_SYSTEM;
	dest_name = DBUS_SERVICE_UPSTART;
	dest_address = DBUS_ADDRESS_UPSTART;

	output = tmpfile ();
	errors = tmpfile ();


	/* Check that the start action with a single argument given looks
	 * up a job with that name, and then calls the Start command
	 * passing a NULL array for the events and TRUE for wait.  Once
	 * it receives the reply, it will then make queries to obtain the
	 * status of the command and print the output.
	 */
	TEST_FEATURE ("with single argument");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Start method call on the job object,
			 * make sure the environment and wait arguments
			 * are right and reply with an instance path to
			 * acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"Start"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_TRUE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* We allow the client to get the properties as many
			 * times as it likes, since it repeats this in out
			 * of memory cases.
			 */
			for (;;) {
				void hup_handler (int signum) { _exit (0); }
				signal (SIGHUP, hup_handler);

				/* Expect the Get call for the job name, reply with
				 * the name.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"Get"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_STRING, &property,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
				TEST_EQ_STR (property, "name");

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "test";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&iter, &subiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);

				/* Expect the GetAll call for the instance properties,
				 * reply with the properties.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"GetAll"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test/_");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
									  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_VARIANT_AS_STRING
									   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
									  &arrayiter);

					/* Name */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "name";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* Goal */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "goal";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "start";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* State */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "state";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "running";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* Processes */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "processes";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  (DBUS_TYPE_ARRAY_AS_STRING
									   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_INT32_AS_STRING
									   DBUS_STRUCT_END_CHAR_AS_STRING),
									  &subiter);

					dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
									  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_INT32_AS_STRING
									   DBUS_STRUCT_END_CHAR_AS_STRING),
									  &prociter);

					dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
									  NULL,
									  &structiter);

					str_value = "main";
					dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
									&str_value);

					int32_value = 3648;
					dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
									&int32_value);

					dbus_message_iter_close_container (&prociter, &structiter);

					dbus_message_iter_close_container (&subiter, &prociter);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					dbus_message_iter_close_container (&iter, &arrayiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);
			}

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = start_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "test start/running, process 3648\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGHUP);
		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}


	/* Check that additional arguments to the start action are passed
	 * as entries in the environment argument of the command.
	 */
	TEST_FEATURE ("with multiple arguments");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Start method call on the job object,
			 * make sure the environment and wait arguments
			 * are right and reply with an instance path to
			 * acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"Start"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 2);
			TEST_EQ_STR (args_value[0], "FOO=foo");
			TEST_EQ_STR (args_value[1], "BAR=bar");
			dbus_free_string_array (args_value);

			TEST_TRUE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* We allow the client to get the properties as many
			 * times as it likes, since it repeats this in out
			 * of memory cases.
			 */
			for (;;) {
				void hup_handler (int signum) { _exit (0); }
				signal (SIGHUP, hup_handler);

				/* Expect the Get call for the job name, reply with
				 * the name.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"Get"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_STRING, &property,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
				TEST_EQ_STR (property, "name");

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "test";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&iter, &subiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);

				/* Expect the GetAll call for the instance properties,
				 * reply with the properties.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"GetAll"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test/_");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
									  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_VARIANT_AS_STRING
									   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
									  &arrayiter);

					/* Name */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "name";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* Goal */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "goal";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "start";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* State */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "state";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "running";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* Processes */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "processes";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  (DBUS_TYPE_ARRAY_AS_STRING
									   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_INT32_AS_STRING
									   DBUS_STRUCT_END_CHAR_AS_STRING),
									  &subiter);

					dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
									  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_INT32_AS_STRING
									   DBUS_STRUCT_END_CHAR_AS_STRING),
									  &prociter);

					dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
									  NULL,
									  &structiter);

					str_value = "main";
					dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
									&str_value);

					int32_value = 3648;
					dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
									&int32_value);

					dbus_message_iter_close_container (&prociter, &structiter);

					dbus_message_iter_close_container (&subiter, &prociter);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					dbus_message_iter_close_container (&iter, &arrayiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);
			}

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = "FOO=foo";
		args[2] = "BAR=bar";
		args[3] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = start_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "test start/running, process 3648\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGHUP);
		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}


	/* Check that the --no-wait option results in the method call
	 * being made with wait as FALSE.
	 */
	TEST_FEATURE ("with no wait");
	no_wait = TRUE;

	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Start method call on the job object,
			 * make sure the environment and wait arguments
			 * are right and reply with an instance path to
			 * acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"Start"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_FALSE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* We allow the client to get the properties as many
			 * times as it likes, since it repeats this in out
			 * of memory cases.
			 */
			for (;;) {
				void hup_handler (int signum) { _exit (0); }
				signal (SIGHUP, hup_handler);

				/* Expect the Get call for the job name, reply with
				 * the name.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"Get"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_STRING, &property,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
				TEST_EQ_STR (property, "name");

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "test";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&iter, &subiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);

				/* Expect the GetAll call for the instance properties,
				 * reply with the properties.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"GetAll"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test/_");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
									  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_VARIANT_AS_STRING
									   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
									  &arrayiter);

					/* Name */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "name";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* Goal */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "goal";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "start";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* State */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "state";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "running";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* Processes */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "processes";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  (DBUS_TYPE_ARRAY_AS_STRING
									   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_INT32_AS_STRING
									   DBUS_STRUCT_END_CHAR_AS_STRING),
									  &subiter);

					dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
									  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_INT32_AS_STRING
									   DBUS_STRUCT_END_CHAR_AS_STRING),
									  &prociter);

					dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
									  NULL,
									  &structiter);

					str_value = "main";
					dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
									&str_value);

					int32_value = 3648;
					dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
									&int32_value);

					dbus_message_iter_close_container (&prociter, &structiter);

					dbus_message_iter_close_container (&subiter, &prociter);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					dbus_message_iter_close_container (&iter, &arrayiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);
			}

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = start_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "test start/running, process 3648\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGHUP);
		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}

	no_wait = FALSE;


	/* Check that the start action may be called without arguments
	 * when inside an instance process, due to the environment variables
	 * set there.  The job should be stilled looked up, but then the
	 * instance should be looked up via GetInstanceByName and the Start
	 * command run directly on the instance instead in a no-wait fashion.
	 */
	TEST_FEATURE ("with no arguments when called from job process");
	setenv ("UPSTART_JOB", "test", TRUE);
	setenv ("UPSTART_INSTANCE", "foo", TRUE);

	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstanceByName method call on the
			 * job object, make sure the instance name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstanceByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "foo");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/foo";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Start method call on the instance object,
			 * make the wait argument is FALSE and reply to
			 * to acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_INSTANCE,
								"Start"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test/foo");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_FALSE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* We allow the client to get the properties as many
			 * times as it likes, since it repeats this in out
			 * of memory cases.
			 */
			for (;;) {
				void hup_handler (int signum) { _exit (0); }
				signal (SIGHUP, hup_handler);

				/* Expect the Get call for the job name, reply with
				 * the name.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"Get"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_STRING, &property,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
				TEST_EQ_STR (property, "name");

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "test";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&iter, &subiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);

				/* Expect the GetAll call for the instance properties,
				 * reply with the properties.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"GetAll"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test/foo");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
									  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_VARIANT_AS_STRING
									   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
									  &arrayiter);

					/* Name */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "name";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "foo";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* Goal */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "goal";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "start";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* State */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "state";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "running";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* Processes */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "processes";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  (DBUS_TYPE_ARRAY_AS_STRING
									   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_INT32_AS_STRING
									   DBUS_STRUCT_END_CHAR_AS_STRING),
									  &subiter);

					dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
									  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_INT32_AS_STRING
									   DBUS_STRUCT_END_CHAR_AS_STRING),
									  &prociter);

					dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
									  NULL,
									  &structiter);

					str_value = "main";
					dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
									&str_value);

					int32_value = 3648;
					dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
									&int32_value);

					dbus_message_iter_close_container (&prociter, &structiter);

					dbus_message_iter_close_container (&subiter, &prociter);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					dbus_message_iter_close_container (&iter, &arrayiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);
			}

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = start_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "test (foo) start/running, process 3648\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGHUP);
		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}

	unsetenv ("UPSTART_JOB");
	unsetenv ("UPSTART_INSTANCE");


	/* Check that if an error is received from the GetJobByName call,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply to GetJobByName");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = start_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	/* Check that if an error is received from the Start call,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply to Start");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Start method call on the job object,
			 * make sure the environment and wait arguments
			 * are right and reply with an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"Start"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_TRUE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = start_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	/* Check that if an error is received from the status query,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply to status query");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Start method call on the job object,
			 * make sure the environment and wait arguments
			 * are right and reply with an instance path to
			 * acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"Start"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_TRUE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Get call for the job name, reply with
			 * an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = start_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	/* Check that a missing argument results in an error being output
	 * to stderr along with a suggestion of help.
	 */
	TEST_FEATURE ("with missing argument");
	TEST_ALLOC_FAIL {
		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = start_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_EQ (errors, "test: missing job name\n");
		TEST_FILE_EQ (errors, "Try `test --help' for more information.\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);
	}


	fclose (errors);
	fclose (output);

	TEST_DBUS_CLOSE (server_conn);
	TEST_DBUS_END (dbus_pid);

	dbus_shutdown ();
}


void
test_stop_action (void)
{
	pid_t           dbus_pid;
	DBusConnection *server_conn;
	FILE *          output;
	FILE *          errors;
	pid_t           server_pid;
	DBusMessage *   method_call;
	DBusMessage *   reply = NULL;
	const char *    name_value;
	char **         args_value;
	int             args_elements;
	int             wait_value;
	const char *    str_value;
	const char *    interface;
	const char *    property;
	DBusMessageIter iter;
	DBusMessageIter subiter;
	NihCommand      command;
	char *          args[4];
	int             ret = 0;
	int             status;

	TEST_FUNCTION ("stop_action");
	TEST_DBUS (dbus_pid);
	TEST_DBUS_OPEN (server_conn);

	assert (dbus_bus_request_name (server_conn, DBUS_SERVICE_UPSTART,
				       0, NULL)
			== DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER);

	TEST_DBUS_MESSAGE (server_conn, method_call);
	assert (dbus_message_is_signal (method_call, DBUS_INTERFACE_DBUS,
					"NameAcquired"));
	dbus_message_unref (method_call);

	use_dbus = TRUE;
	dbus_bus_type = DBUS_BUS_SYSTEM;
	dest_name = DBUS_SERVICE_UPSTART;
	dest_address = DBUS_ADDRESS_UPSTART;

	output = tmpfile ();
	errors = tmpfile ();


	/* Check that the stop action with a single argument given looks
	 * up a job with that name, then looks up the instance with a NULL
	 * arguments array (to get the path for later) and then calls the
	 * Stop command passing a NULL array for the events and TRUE for wait.
	 * Once it receives the reply, it will then make queries to obtain the
	 * status of the command and print the output.
	 */
	TEST_FEATURE ("with single argument");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstance method call on the
			 * job object, make sure the environment args are
			 * passed and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstance"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Stop method call on the job object,
			 * make sure the environment and wait arguments
			 * are right and reply to acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"Stop"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_TRUE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* We allow the client to get the properties as many
			 * times as it likes, since it repeats this in out
			 * of memory cases.
			 */
			for (;;) {
				void hup_handler (int signum) { _exit (0); }
				signal (SIGHUP, hup_handler);

				/* Expect the Get call for the job name, reply with
				 * the name.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"Get"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_STRING, &property,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
				TEST_EQ_STR (property, "name");

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "test";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&iter, &subiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);

				/* Expect the GetAll call for the instance properties,
				 * reply with an unknown method error since
				 * there will be no instance at this point.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"GetAll"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test/_");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_error (method_call,
									DBUS_ERROR_UNKNOWN_METHOD,
									"Unknown method");
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);
			}

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = stop_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "test stop/waiting\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGHUP);
		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}


	/* Check that additional arguments to the stop action are passed
	 * as entries in the environment argument of the command.
	 */
	TEST_FEATURE ("with multiple arguments");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstance method call on the
			 * job object, make sure the environment args are
			 * passed and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstance"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 2);
			TEST_EQ_STR (args_value[0], "FOO=foo");
			TEST_EQ_STR (args_value[1], "BAR=bar");
			dbus_free_string_array (args_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Stop method call on the job object,
			 * make sure the environment and wait arguments
			 * are right and reply to acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"Stop"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 2);
			TEST_EQ_STR (args_value[0], "FOO=foo");
			TEST_EQ_STR (args_value[1], "BAR=bar");
			dbus_free_string_array (args_value);

			TEST_TRUE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* We allow the client to get the properties as many
			 * times as it likes, since it repeats this in out
			 * of memory cases.
			 */
			for (;;) {
				void hup_handler (int signum) { _exit (0); }
				signal (SIGHUP, hup_handler);

				/* Expect the Get call for the job name, reply with
				 * the name.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"Get"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_STRING, &property,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
				TEST_EQ_STR (property, "name");

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "test";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&iter, &subiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);

				/* Expect the GetAll call for the instance properties,
				 * reply with an unknown method error since
				 * there will be no instance at this point.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"GetAll"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test/_");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_error (method_call,
									DBUS_ERROR_UNKNOWN_METHOD,
									"Unknown method");
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);
			}

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = "FOO=foo";
		args[2] = "BAR=bar";
		args[3] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = stop_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "test stop/waiting\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGHUP);
		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}


	/* Check that the --no-wait option results in the method call
	 * being made with wait as FALSE.
	 */
	TEST_FEATURE ("with no wait");
	no_wait = TRUE;

	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstance method call on the
			 * job object, make sure the environment args are
			 * passed and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstance"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Stop method call on the job object,
			 * make sure the environment and wait arguments
			 * are right and reply to acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"Stop"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_FALSE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* We allow the client to get the properties as many
			 * times as it likes, since it repeats this in out
			 * of memory cases.
			 */
			for (;;) {
				void hup_handler (int signum) { _exit (0); }
				signal (SIGHUP, hup_handler);

				/* Expect the Get call for the job name, reply with
				 * the name.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"Get"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_STRING, &property,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
				TEST_EQ_STR (property, "name");

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "test";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&iter, &subiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);

				/* Expect the GetAll call for the instance properties,
				 * reply with an unknown method error since
				 * there will be no instance at this point.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"GetAll"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test/_");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_error (method_call,
									DBUS_ERROR_UNKNOWN_METHOD,
									"Unknown method");
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);
			}

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = stop_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "test stop/waiting\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGHUP);
		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}

	no_wait = FALSE;


	/* Check that the stop action may be called without arguments
	 * when inside an instance process, due to the environment variables
	 * set there.  The job should be still looked up, but then the
	 * instance should be looked up via GetInstanceByName and the Stop
	 * command run directly on the instance instead in a no-wait fashion.
	 */
	TEST_FEATURE ("with no arguments when called from job process");
	setenv ("UPSTART_JOB", "test", TRUE);
	setenv ("UPSTART_INSTANCE", "foo", TRUE);

	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstanceByName method call on the
			 * job object, make sure the instance name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstanceByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "foo");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/foo";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Stop method call on the instance object,
			 * make the wait argument is FALSE and reply to
			 * to acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_INSTANCE,
								"Stop"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test/foo");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_FALSE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* We allow the client to get the properties as many
			 * times as it likes, since it repeats this in out
			 * of memory cases.
			 */
			for (;;) {
				void hup_handler (int signum) { _exit (0); }
				signal (SIGHUP, hup_handler);

				/* Expect the Get call for the job name, reply with
				 * the name.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"Get"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_STRING, &property,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
				TEST_EQ_STR (property, "name");

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "test";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&iter, &subiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);

				/* Expect the GetAll call for the instance properties,
				 * reply with an unknown method error since
				 * there will be no instance at this point.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"GetAll"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test/foo");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_error (method_call,
									DBUS_ERROR_UNKNOWN_METHOD,
									"Unknown method");
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);
			}

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = stop_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "test stop/waiting\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGHUP);
		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}

	unsetenv ("UPSTART_JOB");
	unsetenv ("UPSTART_INSTANCE");


	/* Check that if an error is received from the GetJobByName call,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply to GetJobByName");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = stop_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	/* Check that if an error is received from the GetInstance call,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply to GetInstance");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstance method call on the
			 * job object, make sure the environment args are
			 * passed and reply with an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstance"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = stop_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	/* Check that if an error is received from the Stop call,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply to Stop");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstance method call on the
			 * job object, make sure the environment args are
			 * passed and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstance"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Stop method call on the job object,
			 * make sure the environment and wait arguments
			 * are right and reply with an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"Stop"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_TRUE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = stop_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	/* Check that if an error is received from the status query,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply to status query");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstance method call on the
			 * job object, make sure the environment args are
			 * passed and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstance"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Stop method call on the job object,
			 * make sure the environment and wait arguments
			 * are right and reply with an instance path to
			 * acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"Stop"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_TRUE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Get call for the job name, reply with
			 * an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = stop_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	/* Check that a missing argument results in an error being output
	 * to stderr along with a suggestion of help.
	 */
	TEST_FEATURE ("with missing argument");
	TEST_ALLOC_FAIL {
		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = stop_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_EQ (errors, "test: missing job name\n");
		TEST_FILE_EQ (errors, "Try `test --help' for more information.\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);
	}


	fclose (errors);
	fclose (output);

	TEST_DBUS_CLOSE (server_conn);
	TEST_DBUS_END (dbus_pid);

	dbus_shutdown ();
}


void
test_restart_action (void)
{
	pid_t           dbus_pid;
	DBusConnection *server_conn;
	FILE *          output;
	FILE *          errors;
	pid_t           server_pid;
	DBusMessage *   method_call;
	DBusMessage *   reply = NULL;
	const char *    name_value;
	char **         args_value;
	int             args_elements;
	int             wait_value;
	const char *    str_value;
	const char *    interface;
	const char *    property;
	DBusMessageIter iter;
	DBusMessageIter subiter;
	DBusMessageIter arrayiter;
	DBusMessageIter dictiter;
	DBusMessageIter prociter;
	DBusMessageIter structiter;
	int32_t         int32_value;
	NihCommand      command;
	char *          args[4];
	int             ret = 0;
	int             status;

	TEST_FUNCTION ("restart_action");
	TEST_DBUS (dbus_pid);
	TEST_DBUS_OPEN (server_conn);

	assert (dbus_bus_request_name (server_conn, DBUS_SERVICE_UPSTART,
				       0, NULL)
			== DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER);

	TEST_DBUS_MESSAGE (server_conn, method_call);
	assert (dbus_message_is_signal (method_call, DBUS_INTERFACE_DBUS,
					"NameAcquired"));
	dbus_message_unref (method_call);

	use_dbus = TRUE;
	dbus_bus_type = DBUS_BUS_SYSTEM;
	dest_name = DBUS_SERVICE_UPSTART;
	dest_address = DBUS_ADDRESS_UPSTART;

	output = tmpfile ();
	errors = tmpfile ();


	/* Check that the restart action with a single argument given looks
	 * up a job with that name, and then calls the Restart command
	 * passing a NULL array for the events and TRUE for wait.  Once
	 * it receives the reply, it will then make queries to obtain the
	 * status of the command and print the output.
	 */
	TEST_FEATURE ("with single argument");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Start method call on the job object,
			 * make sure the environment and wait arguments
			 * are right and reply with an instance path to
			 * acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"Restart"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_TRUE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* We allow the client to get the properties as many
			 * times as it likes, since it repeats this in out
			 * of memory cases.
			 */
			for (;;) {
				void hup_handler (int signum) { _exit (0); }
				signal (SIGHUP, hup_handler);

				/* Expect the Get call for the job name, reply with
				 * the name.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"Get"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_STRING, &property,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
				TEST_EQ_STR (property, "name");

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "test";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&iter, &subiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);

				/* Expect the GetAll call for the instance properties,
				 * reply with the properties.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"GetAll"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test/_");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
									  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_VARIANT_AS_STRING
									   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
									  &arrayiter);

					/* Name */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "name";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* Goal */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "goal";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "start";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* State */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "state";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "running";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* Processes */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "processes";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  (DBUS_TYPE_ARRAY_AS_STRING
									   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_INT32_AS_STRING
									   DBUS_STRUCT_END_CHAR_AS_STRING),
									  &subiter);

					dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
									  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_INT32_AS_STRING
									   DBUS_STRUCT_END_CHAR_AS_STRING),
									  &prociter);

					dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
									  NULL,
									  &structiter);

					str_value = "main";
					dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
									&str_value);

					int32_value = 3648;
					dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
									&int32_value);

					dbus_message_iter_close_container (&prociter, &structiter);

					dbus_message_iter_close_container (&subiter, &prociter);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					dbus_message_iter_close_container (&iter, &arrayiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);
			}

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = restart_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "test start/running, process 3648\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGHUP);
		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}


	/* Check that additional arguments to the restart action are passed
	 * as entries in the environment argument of the command.
	 */
	TEST_FEATURE ("with multiple arguments");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Restart method call on the job object,
			 * make sure the environment and wait arguments
			 * are right and reply with an instance path to
			 * acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"Restart"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 2);
			TEST_EQ_STR (args_value[0], "FOO=foo");
			TEST_EQ_STR (args_value[1], "BAR=bar");
			dbus_free_string_array (args_value);

			TEST_TRUE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* We allow the client to get the properties as many
			 * times as it likes, since it repeats this in out
			 * of memory cases.
			 */
			for (;;) {
				void hup_handler (int signum) { _exit (0); }
				signal (SIGHUP, hup_handler);

				/* Expect the Get call for the job name, reply with
				 * the name.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"Get"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_STRING, &property,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
				TEST_EQ_STR (property, "name");

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "test";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&iter, &subiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);

				/* Expect the GetAll call for the instance properties,
				 * reply with the properties.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"GetAll"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test/_");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
									  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_VARIANT_AS_STRING
									   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
									  &arrayiter);

					/* Name */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "name";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* Goal */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "goal";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "start";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* State */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "state";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "running";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* Processes */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "processes";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  (DBUS_TYPE_ARRAY_AS_STRING
									   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_INT32_AS_STRING
									   DBUS_STRUCT_END_CHAR_AS_STRING),
									  &subiter);

					dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
									  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_INT32_AS_STRING
									   DBUS_STRUCT_END_CHAR_AS_STRING),
									  &prociter);

					dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
									  NULL,
									  &structiter);

					str_value = "main";
					dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
									&str_value);

					int32_value = 3648;
					dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
									&int32_value);

					dbus_message_iter_close_container (&prociter, &structiter);

					dbus_message_iter_close_container (&subiter, &prociter);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					dbus_message_iter_close_container (&iter, &arrayiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);
			}

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = "FOO=foo";
		args[2] = "BAR=bar";
		args[3] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = restart_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "test start/running, process 3648\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGHUP);
		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}


	/* Check that the --no-wait option results in the method call
	 * being made with wait as FALSE.
	 */
	TEST_FEATURE ("with no wait");
	no_wait = TRUE;

	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Restart method call on the job object,
			 * make sure the environment and wait arguments
			 * are right and reply with an instance path to
			 * acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"Restart"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_FALSE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* We allow the client to get the properties as many
			 * times as it likes, since it repeats this in out
			 * of memory cases.
			 */
			for (;;) {
				void hup_handler (int signum) { _exit (0); }
				signal (SIGHUP, hup_handler);

				/* Expect the Get call for the job name, reply with
				 * the name.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"Get"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_STRING, &property,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
				TEST_EQ_STR (property, "name");

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "test";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&iter, &subiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);

				/* Expect the GetAll call for the instance properties,
				 * reply with the properties.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"GetAll"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test/_");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
									  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_VARIANT_AS_STRING
									   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
									  &arrayiter);

					/* Name */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "name";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* Goal */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "goal";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "start";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* State */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "state";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "running";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* Processes */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "processes";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  (DBUS_TYPE_ARRAY_AS_STRING
									   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_INT32_AS_STRING
									   DBUS_STRUCT_END_CHAR_AS_STRING),
									  &subiter);

					dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
									  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_INT32_AS_STRING
									   DBUS_STRUCT_END_CHAR_AS_STRING),
									  &prociter);

					dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
									  NULL,
									  &structiter);

					str_value = "main";
					dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
									&str_value);

					int32_value = 3648;
					dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
									&int32_value);

					dbus_message_iter_close_container (&prociter, &structiter);

					dbus_message_iter_close_container (&subiter, &prociter);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					dbus_message_iter_close_container (&iter, &arrayiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);
			}

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = restart_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "test start/running, process 3648\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGHUP);
		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}

	no_wait = FALSE;


	/* Check that the restart action may be called without arguments
	 * when inside an instance process, due to the environment variables
	 * set there.  The job should be stilled looked up, but then the
	 * instance should be looked up via GetInstanceByName and the Restart
	 * command run directly on the instance instead in a no-wait fashion.
	 */
	TEST_FEATURE ("with no arguments when called from job process");
	setenv ("UPSTART_JOB", "test", TRUE);
	setenv ("UPSTART_INSTANCE", "foo", TRUE);

	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstanceByName method call on the
			 * job object, make sure the instance name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstanceByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "foo");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/foo";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Restart method call on the instance
			 * object, make the wait argument is FALSE and reply to
			 * to acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_INSTANCE,
								"Restart"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test/foo");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_FALSE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* We allow the client to get the properties as many
			 * times as it likes, since it repeats this in out
			 * of memory cases.
			 */
			for (;;) {
				void hup_handler (int signum) { _exit (0); }
				signal (SIGHUP, hup_handler);

				/* Expect the Get call for the job name, reply with
				 * the name.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"Get"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_STRING, &property,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
				TEST_EQ_STR (property, "name");

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "test";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&iter, &subiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);

				/* Expect the GetAll call for the instance properties,
				 * reply with the properties.
				 */
				TEST_DBUS_MESSAGE (server_conn, method_call);

				TEST_TRUE (dbus_message_is_method_call (method_call,
									DBUS_INTERFACE_PROPERTIES,
									"GetAll"));

				TEST_EQ_STR (dbus_message_get_path (method_call),
					     DBUS_PATH_UPSTART "/jobs/test/foo");

				TEST_TRUE (dbus_message_get_args (method_call, NULL,
								  DBUS_TYPE_STRING, &interface,
								  DBUS_TYPE_INVALID));

				TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

				TEST_ALLOC_SAFE {
					reply = dbus_message_new_method_return (method_call);

					dbus_message_iter_init_append (reply, &iter);

					dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
									  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_VARIANT_AS_STRING
									   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
									  &arrayiter);

					/* Name */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "name";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "foo";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* Goal */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "goal";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "start";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* State */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "state";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  DBUS_TYPE_STRING_AS_STRING,
									  &subiter);

					str_value = "running";
					dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					/* Processes */
					dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
									  NULL,
									  &dictiter);

					str_value = "processes";
					dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
									&str_value);

					dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
									  (DBUS_TYPE_ARRAY_AS_STRING
									   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_INT32_AS_STRING
									   DBUS_STRUCT_END_CHAR_AS_STRING),
									  &subiter);

					dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
									  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
									   DBUS_TYPE_STRING_AS_STRING
									   DBUS_TYPE_INT32_AS_STRING
									   DBUS_STRUCT_END_CHAR_AS_STRING),
									  &prociter);

					dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
									  NULL,
									  &structiter);

					str_value = "main";
					dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
									&str_value);

					int32_value = 3648;
					dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
									&int32_value);

					dbus_message_iter_close_container (&prociter, &structiter);

					dbus_message_iter_close_container (&subiter, &prociter);

					dbus_message_iter_close_container (&dictiter, &subiter);

					dbus_message_iter_close_container (&arrayiter, &dictiter);

					dbus_message_iter_close_container (&iter, &arrayiter);
				}

				dbus_connection_send (server_conn, reply, NULL);
				dbus_connection_flush (server_conn);

				dbus_message_unref (method_call);
				dbus_message_unref (reply);
			}

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = restart_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "test (foo) start/running, process 3648\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGHUP);
		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}

	unsetenv ("UPSTART_JOB");
	unsetenv ("UPSTART_INSTANCE");


	/* Check that if an error is received from the GetJobByName call,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply to GetJobByName");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = restart_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	/* Check that if an error is received from the Restart call,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply to Restart");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Restart method call on the job object,
			 * make sure the environment and wait arguments
			 * are right and reply with an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"Restart"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_TRUE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = restart_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	/* Check that if an error is received from the status query,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply to status query");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Restart method call on the job object,
			 * make sure the environment and wait arguments
			 * are right and reply with an instance path to
			 * acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"Restart"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_TRUE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Get call for the job name, reply with
			 * an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = restart_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	/* Check that a missing argument results in an error being output
	 * to stderr along with a suggestion of help.
	 */
	TEST_FEATURE ("with missing argument");
	TEST_ALLOC_FAIL {
		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = restart_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_EQ (errors, "test: missing job name\n");
		TEST_FILE_EQ (errors, "Try `test --help' for more information.\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);
	}


	fclose (errors);
	fclose (output);

	TEST_DBUS_CLOSE (server_conn);
	TEST_DBUS_END (dbus_pid);

	dbus_shutdown ();
}


void
test_reload_action (void)
{
	pid_t           dbus_pid;
	DBusConnection *server_conn;
	FILE *          output;
	FILE *          errors;
	pid_t           server_pid;
	pid_t           proc_pid;
	DBusMessage *   method_call;
	DBusMessage *   reply = NULL;
	const char *    name_value;
	char **         args_value;
	int             args_elements;
	const char *    str_value;
	const char *    interface;
	const char *    property;
	DBusMessageIter iter;
	DBusMessageIter subiter;
	DBusMessageIter arrayiter;
	DBusMessageIter structiter;
	int32_t         int32_value;
	NihCommand      command;
	char *          args[4];
	int             ret = 0;
	int             status;

	TEST_FUNCTION ("reload_action");
	TEST_DBUS (dbus_pid);
	TEST_DBUS_OPEN (server_conn);

	assert (dbus_bus_request_name (server_conn, DBUS_SERVICE_UPSTART,
				       0, NULL)
			== DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER);

	TEST_DBUS_MESSAGE (server_conn, method_call);
	assert (dbus_message_is_signal (method_call, DBUS_INTERFACE_DBUS,
					"NameAcquired"));
	dbus_message_unref (method_call);

	use_dbus = TRUE;
	dbus_bus_type = DBUS_BUS_SYSTEM;
	dest_name = DBUS_SERVICE_UPSTART;
	dest_address = DBUS_ADDRESS_UPSTART;

	output = tmpfile ();
	errors = tmpfile ();


	/* Check that the reload action with a single argument given looks
	 * up a job with that name, then requests the list of processes
	 * sending a SIGHUP signal to the main process.
	 */
	TEST_FEATURE ("with single argument");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstance method call on the
			 * job object, make sure the environment args are
			 * passed and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstance"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Reload call against job instance
			 * and reply with an instance path to
			 * acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_INSTANCE,
								"Reload"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test/_");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_INVALID));

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = reload_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}


	/* Check that additional arguments to the restart action are passed
	 * as entries in the environment argument of the command.
	 */
	TEST_FEATURE ("with multiple arguments");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstance method call on the
			 * job object, make sure the environment args are
			 * passed and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstance"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 2);
			TEST_EQ_STR (args_value[0], "FOO=foo");
			TEST_EQ_STR (args_value[1], "BAR=bar");
			dbus_free_string_array (args_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Reload call against job instance
			 * and reply with an instance path to
			 * acknowledge
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_INSTANCE,
								"Reload"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test/_");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_INVALID));

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = "FOO=foo";
		args[2] = "BAR=bar";
		args[3] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = reload_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}


	/* Check that the reload action may be called without arguments
	 * when inside an instance process, due to the environment variables
	 * set there.  The job should be stilled looked up, but then the
	 * instance should be looked up via GetInstanceByName instead.
	 */
	TEST_FEATURE ("with no arguments when called from job process");
	setenv ("UPSTART_JOB", "test", TRUE);
	setenv ("UPSTART_INSTANCE", "foo", TRUE);

	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstanceByName method call on the
			 * job object, make sure the instance name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstanceByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "foo");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/foo";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Reload call against job instance
			 * and reply with an instance path to
			 * acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_INSTANCE,
								"Reload"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test/foo");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_INVALID));

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = reload_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}

	unsetenv ("UPSTART_JOB");
	unsetenv ("UPSTART_INSTANCE");


	/* Check that if an error is received from the GetJobByName call,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply to GetJobByName");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = reload_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	/* Check that if an error is received from the GetInstance call,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply to GetInstance");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstance method call on the
			 * job object, make sure the environment args are
			 * passed and reply with an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstance"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = reload_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	/* Check that if an error is received from the Reload call,
	 * the fallback path is used to query main pid and SIGHUP
	 * that.
	 */
	TEST_FEATURE ("with error reply to Reload");
	TEST_ALLOC_FAIL {
		TEST_CHILD (proc_pid) {
			pause ();
		}

		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstance method call on the
			 * job object, make sure the environment args are
			 * passed and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstance"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Reload method call against job
			 * instance and reply with an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_INSTANCE,
								"Reload"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test/_");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_INVALID));

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Get call for the processes, reply with
			 * a main process pid.
			 */
 			TEST_DBUS_MESSAGE (server_conn, method_call);
 
 			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));
 			TEST_EQ_STR (dbus_message_get_path (method_call),
 							    DBUS_PATH_UPSTART "/jobs/test/_");
 
 			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
 							  DBUS_TYPE_INVALID));

 			TEST_ALLOC_SAFE {
 				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  (DBUS_TYPE_ARRAY_AS_STRING
								   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &subiter);

				dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
								  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &arrayiter);

				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "main";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = proc_pid;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&arrayiter, &structiter);

				dbus_message_iter_close_container (&subiter, &arrayiter);

				dbus_message_iter_close_container (&iter, &subiter);
 			}
 
 			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = reload_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			kill (proc_pid, SIGTERM);
			waitpid (proc_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);

		kill (proc_pid, SIGTERM);
		waitpid (proc_pid, NULL, 0);
		continue;

	}


	/* Check that a missing argument results in an error being output
	 * to stderr along with a suggestion of help.
	 */
	TEST_FEATURE ("with missing argument");
	TEST_ALLOC_FAIL {
		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = reload_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_EQ (errors, "test: missing job name\n");
		TEST_FILE_EQ (errors, "Try `test --help' for more information.\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);
	}


	fclose (errors);
	fclose (output);

	TEST_DBUS_CLOSE (server_conn);
	TEST_DBUS_END (dbus_pid);

	dbus_shutdown ();
}


void
test_status_action (void)
{
	pid_t           dbus_pid;
	DBusConnection *server_conn;
	FILE *          output;
	FILE *          errors;
	pid_t           server_pid;
	DBusMessage *   method_call;
	DBusMessage *   reply = NULL;
	const char *    name_value;
	char **         args_value;
	int             args_elements;
	const char *    str_value;
	const char *    interface;
	const char *    property;
	DBusMessageIter iter;
	DBusMessageIter subiter;
	DBusMessageIter arrayiter;
	DBusMessageIter dictiter;
	DBusMessageIter prociter;
	DBusMessageIter structiter;
	int32_t         int32_value;
	NihCommand      command;
	char *          args[4];
	int             ret = 0;
	int             status;

	TEST_FUNCTION ("status_action");
	TEST_DBUS (dbus_pid);
	TEST_DBUS_OPEN (server_conn);

	assert (dbus_bus_request_name (server_conn, DBUS_SERVICE_UPSTART,
				       0, NULL)
			== DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER);

	TEST_DBUS_MESSAGE (server_conn, method_call);
	assert (dbus_message_is_signal (method_call, DBUS_INTERFACE_DBUS,
					"NameAcquired"));
	dbus_message_unref (method_call);

	use_dbus = TRUE;
	dbus_bus_type = DBUS_BUS_SYSTEM;
	dest_name = DBUS_SERVICE_UPSTART;
	dest_address = DBUS_ADDRESS_UPSTART;

	output = tmpfile ();
	errors = tmpfile ();


	/* Check that the status action with a single argument given looks
	 * up a job with that name, then looks up the instance with a NULL
	 * arguments array (to get the path for later) and then makes
	 * queries to obtain the status of that instance printing the
	 * output.
	 */
	TEST_FEATURE ("with single argument");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstance method call on the
			 * job object, make sure the environment args are
			 * passed and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstance"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Get call for the job name, reply with
			 * the name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "test";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAll call for the instance properties,
			 * reply with the properties.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"GetAll"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/test/_");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_VARIANT_AS_STRING
								   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
								  &arrayiter);

				/* Name */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "name";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Goal */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "goal";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "start";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* State */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "state";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "running";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Processes */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "processes";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  (DBUS_TYPE_ARRAY_AS_STRING
								   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &subiter);

				dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
								  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &prociter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "main";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 3648;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_close_container (&subiter, &prociter);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = status_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "test start/running, process 3648\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}


	/* Check that additional arguments to the status action are passed
	 * as entries in the environment to GetInstance.
	 */
	TEST_FEATURE ("with multiple arguments");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstance method call on the
			 * job object, make sure the environment args are
			 * passed and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstance"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 2);
			TEST_EQ_STR (args_value[0], "FOO=foo");
			TEST_EQ_STR (args_value[1], "BAR=bar");
			dbus_free_string_array (args_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Get call for the job name, reply with
			 * the name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "test";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAll call for the instance properties,
			 * reply with the properties.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"GetAll"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/test/_");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_VARIANT_AS_STRING
								   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
								  &arrayiter);

				/* Name */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "name";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Goal */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "goal";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "start";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* State */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "state";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "running";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Processes */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "processes";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  (DBUS_TYPE_ARRAY_AS_STRING
								   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &subiter);

				dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
								  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &prociter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "main";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 3648;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_close_container (&subiter, &prociter);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = "FOO=foo";
		args[2] = "BAR=bar";
		args[3] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = status_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "test start/running, process 3648\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}


	/* Check that the status action may be called without arguments
	 * when inside an instance process, due to the environment variables
	 * set there.  The job should be still looked up, but then the
	 * instance should be looked up via GetInstanceByName and the
	 * queries run on that instance.
	 */
	TEST_FEATURE ("with no arguments when called from job process");
	setenv ("UPSTART_JOB", "test", TRUE);
	setenv ("UPSTART_INSTANCE", "foo", TRUE);

	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstanceByName method call on the
			 * job object, make sure the instance name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstanceByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "foo");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/foo";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Get call for the job name, reply with
			 * the name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "test";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAll call for the instance properties,
			 * reply with the properties.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"GetAll"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/test/foo");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_VARIANT_AS_STRING
								   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
								  &arrayiter);

				/* Name */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "name";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "foo";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Goal */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "goal";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "start";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* State */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "state";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "running";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Processes */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "processes";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  (DBUS_TYPE_ARRAY_AS_STRING
								   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &subiter);

				dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
								  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &prociter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "main";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 3648;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_close_container (&subiter, &prociter);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = status_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "test (foo) start/running, process 3648\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}

	unsetenv ("UPSTART_JOB");
	unsetenv ("UPSTART_INSTANCE");


	/* Check that an unknown instance error from the GetInstance call
	 * is treated as a stopped job; the job name should still be
	 * queried but not the instance properties.
	 */
	TEST_FEATURE ("with unknown instance");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstance method call on the
			 * job object, make sure the environment args are
			 * passed and reply with an error
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstance"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_INTERFACE_UPSTART ".Error.UnknownInstance",
								"Unknown instance");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Get call for the job name, reply with
			 * the name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "test";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = status_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "test stop/waiting\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}


	/* Check that if an error is received from the GetJobByName call,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply to GetJobByName");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = status_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	/* Check that if an error is received from the GetInstance command,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply to GetInstance");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstance method call on the
			 * job object, make sure the environment args are
			 * passed and reply with an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstance"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = status_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	/* Check that if an error is received from the status query,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply to status query");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetJobByName method call on the
			 * manager object, make sure the job name is passed
			 * and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetJobByName"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "test");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetInstance method call on the
			 * job object, make sure the environment args are
			 * passed and reply with a path.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetInstance"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_INVALID));

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				str_value = DBUS_PATH_UPSTART "/jobs/test/_";

				dbus_message_append_args (reply,
							  DBUS_TYPE_OBJECT_PATH, &str_value,
							  DBUS_TYPE_INVALID);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Get call for the job name, reply with
			 * an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/test");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "test";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = status_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	/* Check that a missing argument results in an error being output
	 * to stderr along with a suggestion of help.
	 */
	TEST_FEATURE ("with missing argument");
	TEST_ALLOC_FAIL {
		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = status_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_EQ (errors, "test: missing job name\n");
		TEST_FILE_EQ (errors, "Try `test --help' for more information.\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);
	}


	fclose (errors);
	fclose (output);

	TEST_DBUS_CLOSE (server_conn);
	TEST_DBUS_END (dbus_pid);

	dbus_shutdown ();
}

void
test_list (void)
{
	char             dirname[PATH_MAX];
	nih_local char  *cmd = NULL;
	pid_t            upstart_pid = 0;
	pid_t            dbus_pid    = 0;
	char           **output;
	size_t           lines;
	char             expected_output[] = "foo stop/waiting";

	TEST_GROUP ("list");

        TEST_FILENAME (dirname);
        TEST_EQ (mkdir (dirname, 0755), 0);

	/* Use the "secret" interface */
	TEST_EQ (setenv ("UPSTART_CONFDIR", dirname, 1), 0);

	TEST_DBUS (dbus_pid);

	/*******************************************************************/
	TEST_FEATURE ("single job");

	CREATE_FILE (dirname, "foo.conf",
			"exec echo hello");
	START_UPSTART (upstart_pid, FALSE);

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ (lines, 1);
	nih_free (output);
	DELETE_FILE (dirname, "foo.conf");
	STOP_UPSTART (upstart_pid);

	/*******************************************************************/
	TEST_FEATURE ("3 jobs and re-exec");

        CREATE_FILE (dirname, "foo.conf", "exec echo foo");
	CREATE_FILE (dirname, "bar.conf", "exec echo bar");
	CREATE_FILE (dirname, "baz.conf", "exec echo bar");
	START_UPSTART (upstart_pid, FALSE);

	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);

	RUN_COMMAND (NULL, cmd, &output, &lines);

	/* guarantee output ordering */
	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	TEST_EQ_STR (output[0], "bar stop/waiting");
	TEST_EQ_STR (output[1], "baz stop/waiting");
	TEST_EQ_STR (output[2], "foo stop/waiting");
	TEST_EQ (lines, 3);
	nih_free (output);

	REEXEC_UPSTART (upstart_pid, FALSE);

	/* Ensure we can still list jobs after a re-exec */
	cmd = nih_sprintf (NULL, "%s list 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);

	RUN_COMMAND (NULL, cmd, &output, &lines);

	/* guarantee output ordering */
	qsort (output, lines, sizeof (output[0]), strcmp_compar);

	TEST_EQ_STR (output[0], "bar stop/waiting");
	TEST_EQ_STR (output[1], "baz stop/waiting");
	TEST_EQ_STR (output[2], "foo stop/waiting");
	TEST_EQ (lines, 3);
	nih_free (output);

	DELETE_FILE (dirname, "foo.conf");
	DELETE_FILE (dirname, "bar.conf");
	DELETE_FILE (dirname, "baz.conf");

	STOP_UPSTART (upstart_pid);

	/*******************************************************************/

	TEST_EQ (unsetenv ("UPSTART_CONFDIR"), 0);
	TEST_DBUS_END (dbus_pid);
        TEST_EQ (rmdir (dirname), 0);
}

void
test_reexec (void)
{
	char             confdir[PATH_MAX];
	char             logdir[PATH_MAX];
	char             flagfile[PATH_MAX];
	nih_local char  *cmd = NULL;
	pid_t            job_pid     = 0;
	pid_t            tmp = 0;
	pid_t            dbus_pid = 0;
	pid_t            upstart_pid = 0;
	char           **output;
	size_t           lines;
	nih_local char  *logfile = NULL;
	struct stat      statbuf;
	nih_local char  *contents = NULL;
	FILE            *file;
	int              ok;
	int              ret;
	mode_t           expected_umask;
	size_t           len;

	TEST_GROUP ("re-exec support");

        TEST_FILENAME (confdir);
        TEST_EQ (mkdir (confdir, 0755), 0);

        TEST_FILENAME (logdir);
        TEST_EQ (mkdir (logdir, 0755), 0);

        TEST_FILENAME (flagfile);

	/* Use the "secret" interface */
	TEST_EQ (setenv ("UPSTART_CONFDIR", confdir, 1), 0);
	TEST_EQ (setenv ("UPSTART_LOGDIR", logdir, 1), 0);

	TEST_DBUS (dbus_pid);

	/*******************************************************************/
	TEST_FEATURE ("single job producing output across a re-exec");

	start_upstart_common (&upstart_pid, FALSE, FALSE, confdir, logdir, NULL);

	contents = nih_sprintf (NULL, 
			"pre-start exec echo pre-start\n"
			"script\n"
			"\n"
			"# Write first half of data\n"
			"for i in 1 2 3 4 5\n"
			"do\n"
			"    echo $i\n"
			"done\n"
			"\n"
			"# hack to wait for notification that Upstart has re-exec'ed\n"
			"while [ ! -f \"%s\" ]\n"
			"do\n"
			"    sleep 0.1\n"
			"done\n"
			"\n"
			"# remove flag file\n"
			"rm -f \"%s\"\n"
			"\n"
			"# Write remaining data\n"
			"for i in 6 7 8 9 10\n"
			"do\n"
			"    echo $i\n"
			"done\n"
			"\n"
			"# hang around until killed\n"
			"sleep 999\n"
			"\n"
			"end script\n",
		flagfile, flagfile);
	TEST_NE_P (contents, NULL);

	CREATE_FILE (confdir, "foo.conf", contents);

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s start foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	nih_free (output);

	/* check job is running */
	job_pid = job_to_pid ("foo");
	TEST_NE (job_pid, -1);

	logfile = NIH_MUST (nih_sprintf (NULL, "%s/%s",
				logdir,
				"foo.log"));

	/* Wait for log to be created */
	ok = FALSE;
	for (int i = 0; i < 5; i++) {
		sleep (1);
		if (! stat (logfile, &statbuf)) {
			ok = TRUE;
			break;
		}
	}
	TEST_EQ (ok, TRUE);

	file = fopen (logfile, "r");
	TEST_NE_P (file, NULL);

	/* check contents of log file */
	TEST_FILE_EQ (file, "pre-start\r\n");
	for (int i = 1; i < 6; i++) {
		nih_local char *line = NIH_MUST (nih_sprintf (NULL, "%d\r\n", i));
		TEST_FILE_EQ (file, line);
	}
	TEST_FILE_END (file);
	fclose (file);

	REEXEC_UPSTART (upstart_pid, FALSE);
	
	/* Create flag file to allow job to proceed */
	{
		FILE *f;
		f = fopen (flagfile, "w");
		TEST_NE_P (f, NULL);
		fclose (f);
	}

	/* ensure job is still running */
	tmp = job_to_pid ("foo");
	TEST_NE (tmp, -1);

	/* ensure it hasn't changed pid */
	TEST_EQ (job_pid, tmp);

	/* wait for script to remove flag file */
	ok = FALSE;
	for (int i = 1; i < 6; i++) {
		ret = stat (flagfile, &statbuf);
	       
		if (ret	< 0 && errno == ENOENT) {
			ok = TRUE;
			break;
		}
		sleep (1);
	}

	TEST_EQ (ok, TRUE);

	cmd = nih_sprintf (NULL, "%s stop %s 2>&1",
			get_initctl (), "foo");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	nih_free (output);

	/* Wait for job to finish. We can't waitpid() for it as it's not one
	 * of our children.
	 */
	ok = FALSE;
	for (int i = 0; i < 5; i++) {
		nih_local char *path = NIH_MUST (nih_sprintf (NULL, "/proc/%d", job_pid));
		if (stat (path, &statbuf) < 0 && errno == ENOENT) {
			ok = TRUE;
			break;
		}
		sleep (1);
	}
	TEST_EQ (ok, TRUE);
	tmp = job_to_pid ("foo");
	TEST_EQ (tmp, -1);

	TEST_EQ (stat (logfile, &statbuf), 0);

	file = fopen (logfile, "r");
	TEST_NE_P (file, NULL);

	/* check contents of log file */
	TEST_FILE_EQ (file, "pre-start\r\n");
	for (int i = 1; i < 11; i++) {
		nih_local char *line = NIH_MUST (nih_sprintf (NULL, "%d\r\n", i));
		TEST_FILE_EQ (file, line);
	}
	TEST_FILE_END (file);
	fclose (file);

	/* ensure script removed flagfile */
	TEST_LT (stat (flagfile, &statbuf), 0);

	DELETE_FILE (confdir, "foo.conf");
	DELETE_FILE (logdir, "foo.log");
	STOP_UPSTART (upstart_pid);

	TEST_EQ (unsetenv ("UPSTART_CONFDIR"), 0);
	TEST_EQ (unsetenv ("UPSTART_LOGDIR"), 0);

	/*******************************************************************/
	TEST_FEATURE ("ensure 'set-env' persists across session-init re-exec");

	TEST_TRUE (getenv ("XDG_RUNTIME_DIR"));

	contents = nih_sprintf (NULL, 
			"start on startup\n"
			"\n"
			"pre-start script\n"
			"%s set-env foo=bar\n"
			"\n"
			"# create flag file\n"
			"touch \"%s\"\n"
			"\n"
			"end script\n"
			"\n"
			"# a minimal main process\n"
			"exec true\n"
			"\n"
			"post-stop script\n"
			"\n"
			"# wait for upstart to notify us that it has re-execed\n"
			"while [ -f \"%s\" ]\n"
			"do\n"
			"    sleep 0.1\n"
			"done\n"
			"\n"
			"# query value post-re-exec\n"
			"%s get-env foo\n"
			"\n"
			"end script\n",
			get_initctl_binary(), flagfile, flagfile, get_initctl_binary());
	TEST_NE_P (contents, NULL);

	CREATE_FILE (confdir, "foo.conf", contents);

	start_upstart_common (&upstart_pid, TRUE, TRUE, confdir, logdir, NULL);

	WAIT_FOR_FILE (flagfile);

	/* check job is running */
	job_pid = job_to_pid ("foo");
	TEST_NE (job_pid, -1);

	REEXEC_UPSTART (upstart_pid, TRUE);

	/* Notify job that upstart has re-exec'd */
	assert0 (unlink (flagfile));

	logfile = NIH_MUST (nih_sprintf (NULL, "%s/%s",
				logdir,
				"foo.log"));

	WAIT_FOR_FILE (logfile);
	file = fopen (logfile, "r");
	TEST_NE_P (file, NULL);
	TEST_FILE_EQ (file, "bar\r\n");
	fclose (file);

	STOP_UPSTART (upstart_pid);
	assert0 (unlink (logfile));
	DELETE_FILE (confdir, "foo.conf");

	/*******************************************************************/
	TEST_FEATURE ("ensure 'set-env --global' persists across session-init re-exec");

	START_UPSTART (upstart_pid, TRUE);

	/* Set variable. Use confdir as a random value */
	cmd = nih_sprintf (NULL, "%s set-env --global path='%s' 2>&1", get_initctl (), confdir);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);

	/* Check it */
	cmd = nih_sprintf (NULL, "%s get-env --global path 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], confdir);
	nih_free (output);

	/* Restart */
	REEXEC_UPSTART (upstart_pid, TRUE);

	/* Re-check */
	cmd = nih_sprintf (NULL, "%s get-env --global path 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], confdir);
	nih_free (output);

	STOP_UPSTART (upstart_pid);

	/*******************************************************************/
	TEST_FEATURE ("ensure re-exec does not disrupt umask");

	contents = nih_sprintf (NULL, "exec sh -c umask");
	TEST_NE_P (contents, NULL);

	CREATE_FILE (confdir, "umask.conf", contents);
	nih_free (contents);

	start_upstart_common (&upstart_pid, TRUE, TRUE, confdir, logdir, NULL);

	cmd = nih_sprintf (NULL, "%s start umask 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	nih_free (output);

	logfile = NIH_MUST (nih_sprintf (NULL, "%s/%s",
				logdir,
				"umask.log"));

	/* Wait for log to be created */
	ok = FALSE;
	for (int i = 0; i < 5; i++) {
		sleep (1);
		if (! stat (logfile, &statbuf)) {
			ok = TRUE;
			break;
		}
	}
	TEST_EQ (ok, TRUE);

	contents = nih_file_read (NULL, logfile, &len);
	TEST_NE_P (contents, NULL);
	TEST_TRUE (len);

	/* overwrite '\n' */
	contents[len-1] = '\0';

	expected_umask = (mode_t)atoi (contents);
	assert0 (unlink (logfile));
	nih_free (contents);

	/* Restart */
	REEXEC_UPSTART (upstart_pid, TRUE);

	/* Re-run job */
	RUN_COMMAND (NULL, cmd, &output, &lines);
	nih_free (output);

	/* Wait for log to be recreated */
	ok = FALSE;
	for (int i = 0; i < 5; i++) {
		sleep (1);
		if (! stat (logfile, &statbuf)) {
			ok = TRUE;
			break;
		}
	}
	TEST_EQ (ok, TRUE);

	contents = nih_file_read (NULL, logfile, &len);
	TEST_NE_P (contents, NULL);
	TEST_TRUE (len);

	/* overwrite '\n' */
	contents[len-1] = '\0';

	TEST_EQ (expected_umask, (mode_t)atoi (contents));

	STOP_UPSTART (upstart_pid);

	DELETE_FILE (confdir, "umask.conf");
	assert0 (unlink (logfile));

	/*******************************************************************/

	TEST_DBUS_END (dbus_pid);

        TEST_EQ (rmdir (confdir), 0);
        TEST_EQ (rmdir (logdir), 0);

	/*******************************************************************/
}

void
test_list_sessions (void)
{
	char             dirname[PATH_MAX];
	char             confdir[PATH_MAX];
	nih_local char  *cmd = NULL;
	pid_t            upstart_pid = 0;
	char           **output;
	size_t           lines;
	struct stat      statbuf;
	nih_local char  *contents = NULL;
	nih_local char  *session_file = NULL;
	nih_local char  *path = NULL;
	nih_local char  *expected = NULL;
	nih_local char  *original_runtime = NULL;
	size_t           len;
	char            *value;

	TEST_GROUP ("list-sessions");

	original_runtime = nih_strdup (NULL, getenv("XDG_RUNTIME_DIR"));
	TEST_NE_P (original_runtime, NULL);

	TEST_FILENAME (dirname);
	TEST_EQ (mkdir (dirname, 0755), 0);

	TEST_FILENAME (confdir);
	TEST_EQ (mkdir (confdir, 0755), 0);

	/*******************************************************************/
	TEST_FEATURE ("with no instances and XDG_RUNTIME_DIR unset");

	assert0 (unsetenv ("XDG_RUNTIME_DIR"));
	cmd = nih_sprintf (NULL, "%s list-sessions 2>&1", get_initctl_binary ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	TEST_EQ_STR (output[0], "initctl: Unable to query session directory");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("with no instances and XDG_RUNTIME_DIR set");

	TEST_EQ (setenv ("XDG_RUNTIME_DIR", dirname, 1), 0);

	cmd = nih_sprintf (NULL, "%s list-sessions 2>&1", get_initctl_binary ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);

	/*******************************************************************/
	TEST_FEATURE ("with 1 running instance");

	/* Use the "secret" interface */
	TEST_EQ (setenv ("UPSTART_CONFDIR", confdir, 1), 0);
	TEST_EQ (setenv ("XDG_RUNTIME_DIR", dirname, 1), 0);

	/* Reset initctl global from previous tests */
	dest_name = NULL;

	start_upstart_common (&upstart_pid, TRUE, FALSE, NULL, NULL, NULL);

	session_file = get_session_file (dirname, upstart_pid);

	/* session file should now have been created by Upstart */
	TEST_EQ (stat (session_file, &statbuf), 0);

	contents = nih_file_read (NULL, session_file, &len);
	TEST_NE_P (contents, NULL);
	TEST_TRUE (len);

	/* overwrite '\n' */
	contents[len-1] = '\0';

	TEST_EQ_P (strstr (contents, "UPSTART_SESSION="), contents);
	value  = strchr (contents, '=');
	TEST_NE_P (value, NULL);

	/* jump over '=' */
	value++;
	TEST_NE_P (value, NULL);

	expected = nih_sprintf (NULL, "%d %s", (int)upstart_pid, value);

	cmd = nih_sprintf (NULL, "%s list-sessions 2>&1", get_initctl_binary ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	TEST_EQ_STR (output[0], expected);
	nih_free (output);

	STOP_UPSTART (upstart_pid);

	/* Upstart cannot yet be instructed to shutdown cleanly, so for
	 * now we have to remove the session file manually.
	 */
	TEST_EQ (unlink (session_file), 0);

	/* Remove the directory tree the Session Init created */
	path = NIH_MUST (nih_sprintf (NULL, "%s/upstart/sessions", dirname));
        TEST_EQ (rmdir (path), 0);
	path = NIH_MUST (nih_sprintf (NULL, "%s/upstart", dirname));
        TEST_EQ (rmdir (path), 0);

	/*******************************************************************/

	assert0 (unsetenv ("UPSTART_CONFDIR"));

        TEST_EQ (rmdir (dirname), 0);
        TEST_EQ (rmdir (confdir), 0);

	TEST_EQ (setenv ("XDG_RUNTIME_DIR", original_runtime, 1), 0);

	/*******************************************************************/
}

void
test_no_dbus (void)
{
	nih_local char  *cmd = NULL;
	char           **output;
	size_t           lines;
	pid_t            upstart_pid = 0;
	pid_t            dbus_pid = 0;
	char            *extra[] = { "--no-dbus", NULL };

	TEST_GROUP ("Test '--no-dbus'");

	TEST_DBUS (dbus_pid);

	/*******************************************************************/
	/* First perform a sanity check */

	TEST_FEATURE ("Ensure version can be queried normally");

	start_upstart_common (&upstart_pid, FALSE, FALSE, NULL, NULL, NULL);

	cmd = nih_sprintf (NULL, "%s version 2>/dev/null", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], "init*(upstart [0-9]*");
	nih_free (output);

	STOP_UPSTART (upstart_pid);

	/*******************************************************************/
	/* Now, try with dbus disabled */

	TEST_FEATURE ("Ensure '--no-dbus' disables D-Bus");

	start_upstart_common (&upstart_pid, FALSE, FALSE, NULL, NULL, extra);

	cmd = nih_sprintf (NULL, "%s version 2>/dev/null", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	/* No output on stdout expected */
	TEST_EQ (lines, 0);

	/*******************************************************************/
	TEST_FEATURE ("Ensure D-Bus still disabled on SIGUSR1");

	assert0 (kill (upstart_pid, SIGUSR1));

	cmd = nih_sprintf (NULL, "%s version 2>/dev/null", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	/* No output on stdout expected */
	TEST_EQ (lines, 0);

	STOP_UPSTART (upstart_pid);

	/*******************************************************************/

	TEST_DBUS_END (dbus_pid);
}

void
test_quiesce (void)
{
	char                      confdir[PATH_MAX];
	char                      logdir[PATH_MAX];
	char                      pid_file[PATH_MAX];
	nih_local char           *sessiondir;
	nih_local char           *cmd = NULL;
	pid_t                     upstart_pid = 0;
	nih_local char           *logfile = NULL;
	FILE                     *file;
	char                    **output;
	size_t                    lines;
	nih_local NihDBusProxy   *upstart = NULL;
	nih_local char           *session_file = NULL;
	nih_local char           *job = NULL;
	pid_t                     job_pid;

	TEST_GROUP ("Session Init quiesce");

	TEST_FILENAME (confdir);
	TEST_EQ (mkdir (confdir, 0755), 0);

	TEST_FILENAME (logdir);
	TEST_EQ (mkdir (logdir, 0755), 0);

	sessiondir = nih_strdup (NULL, getenv ("XDG_RUNTIME_DIR"));
	TEST_NE_P (sessiondir, NULL);
	
	cmd = nih_sprintf (NULL, "rm %s/upstart/sessions/*.session 2>/dev/null", sessiondir);
	assert0 (system (cmd));

	/* Use the "secret" interface */
	TEST_EQ (setenv ("UPSTART_CONFDIR", confdir, 1), 0);
	TEST_EQ (setenv ("UPSTART_LOGDIR", logdir, 1), 0);

	/* Reset initctl global from previous tests */
	dest_name = NULL;

	/*******************************************************************/
	TEST_FEATURE ("system shutdown: no jobs");

	start_upstart_common (&upstart_pid, TRUE, FALSE, confdir, logdir, NULL);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	/* Trigger shutdown */
	assert0 (kill (upstart_pid, SIGTERM));

	/* Force reset */
	test_user_mode = FALSE;

	TEST_EQ (timed_waitpid (upstart_pid, TEST_QUIESCE_KILL_PHASE), upstart_pid);

	/* Should not now be running */
	TEST_EQ (kill (upstart_pid, 0), -1);

	session_file = NIH_MUST (nih_sprintf (NULL, "%s/upstart/sessions/%d.session",
				sessiondir, (int)upstart_pid));
	unlink (session_file);

	/*******************************************************************/
	TEST_FEATURE ("system shutdown: one long-running job");

	CREATE_FILE (confdir, "long-running.conf",
			"exec sleep 999");

	start_upstart_common (&upstart_pid, TRUE, FALSE, confdir, logdir, NULL);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	cmd = nih_sprintf (NULL, "%s start %s 2>&1",
			get_initctl (), "long-running");
	TEST_NE_P (cmd, NULL);

	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	nih_free (output);

	job_pid = job_to_pid ("long-running");
	TEST_NE (job_pid, -1);

	/* Trigger shutdown */
	assert0 (kill (upstart_pid, SIGTERM));

	/* Force reset */
	test_user_mode = FALSE;

	/* Wait for longer than we expect the Session Init to take to
	 * shutdown to give it time to send SIGKILL to all job
	 * processes. This is unrealistic, but safer for the tests since
	 * the exact behaviour can be checked.
	 *
	 * In reality, the following steps either side of the markers *will*
	 * occur and those within the markers *may* occur:
	 *
	 * 1) A System Shutdown is triggered.
	 * 2) The Display Manager receives SIGTERM.
	 * 3) The Display Manager sends SIGTERM to all its clients.
	 *    (including the Session Init).
	 * 4) The Session Init sends SIGTERM to all running job
	 *    processes.
	 *
	 *  --- :XXX: START MARKER :XXX: ---
	 *
	 * 5) The Session Init will attempt to wait for
	 *    MAX(kill_timeout) seconds.
	 * 6) The Session Init will send all running job processes
	 *    SIGKILL.
	 * 7) The Session Init will wait for all remaining job processes
	 *    to end.
	 * 8) The Session Init will exit.
	 *
	 *  --- :XXX: END MARKER :XXX: ---
	 *
	 * 9) The Display Manager sends SIGKILL to all its clients.
	 * 10) If still running, the Session Init is killed and exits.
	 *
	 * The problem is that the Session Init cannot know when the
	 * Display Manager will kill *it* so it may be that the Session
	 * Init cannot send SIGKILL to each job process instead relying
	 * on the System Init to clean up.
	 */
	TEST_EQ (timed_waitpid (upstart_pid, 1+TEST_QUIESCE_KILL_PHASE), upstart_pid);

	/* Should not now be running */
	TEST_EQ (kill (upstart_pid, 0), -1);
	TEST_EQ (errno, ESRCH);

	session_file = NIH_MUST (nih_sprintf (NULL, "%s/upstart/sessions/%d.session",
				sessiondir, (int)upstart_pid));
	unlink (session_file);

	/* pid should no longer exist */
	TEST_EQ (kill (job_pid, SIGKILL), -1);
	TEST_EQ (errno, ESRCH);

	DELETE_FILE (confdir, "long-running.conf");

	/*******************************************************************/
	TEST_FEATURE ("system shutdown: one long-running job which ignores SIGTERM");

	CREATE_FILE (confdir, "long-running-term.conf",
			"script\n"
			"  trap '' TERM\n"
		        "  sleep 999\n"
			"end script");

	start_upstart_common (&upstart_pid, TRUE, FALSE, confdir, logdir, NULL);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	cmd = nih_sprintf (NULL, "%s start %s 2>&1",
			get_initctl (), "long-running-term");
	TEST_NE_P (cmd, NULL);

	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	nih_free (output);

	job_pid = job_to_pid ("long-running-term");
	TEST_NE (job_pid, -1);

	/* Trigger shutdown */
	assert0 (kill (upstart_pid, SIGTERM));

	/* Force reset */
	test_user_mode = FALSE;

	TEST_EQ (timed_waitpid (upstart_pid, 1+TEST_QUIESCE_KILL_PHASE), upstart_pid);

	/* Should not now be running */
	TEST_EQ (kill (upstart_pid, 0), -1);
	TEST_EQ (errno, ESRCH);

	session_file = NIH_MUST (nih_sprintf (NULL, "%s/upstart/sessions/%d.session",
				sessiondir, (int)upstart_pid));
	unlink (session_file);

	/* pid should no longer exist */
	TEST_EQ (kill (job_pid, SIGKILL), -1);
	TEST_EQ (errno, ESRCH);

	DELETE_FILE (confdir, "long-running-term.conf");

	/*******************************************************************/
	TEST_FEATURE ("system shutdown: one job which starts on session-end");

	TEST_FILENAME (pid_file);

	job = NIH_MUST (nih_sprintf (NULL, "start on session-end\n"
				"\n"
				"script\n"
				"  echo hello\n"
				"  echo $$ >\"%s\"\n"
				"  exec sleep 999\n"
				"end script", pid_file));

	CREATE_FILE (confdir, "session-end.conf", job);

	start_upstart_common (&upstart_pid, TRUE, FALSE, confdir, logdir, NULL);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	/* Trigger shutdown */
	assert0 (kill (upstart_pid, SIGTERM));

	/* Force reset */
	test_user_mode = FALSE;

	TEST_EQ (timed_waitpid (upstart_pid, 1+TEST_QUIESCE_KILL_PHASE), upstart_pid);

	/* Should not now be running */
	TEST_EQ (kill (upstart_pid, 0), -1);
	TEST_EQ (errno, ESRCH);

	logfile = NIH_MUST (nih_sprintf (NULL, "%s/%s",
				logdir,
				"session-end.log"));

	file = fopen (logfile, "r");
	TEST_NE_P (file, NULL);
	TEST_FILE_EQ (file, "hello\r\n");
	TEST_FILE_END (file);
	TEST_EQ (fclose (file), 0);
	assert0 (unlink (logfile));

	session_file = NIH_MUST (nih_sprintf (NULL, "%s/upstart/sessions/%d.session",
				sessiondir, (int)upstart_pid));
	unlink (session_file);

	file = fopen (pid_file, "r");
	TEST_NE_P (file, NULL);
	TEST_EQ (fscanf (file, "%d", &job_pid), 1);
	fclose (file);

	/* pid should be running since Upstart won't have signalled it
	 * to stop (since it started as a result of session-end being
	 * emitted _after_ the job pids were sent SIGTERM).
	 */
	TEST_EQ (kill (job_pid, SIGKILL), 0);

	assert0 (unlink (pid_file));

	DELETE_FILE (confdir, "session-end.conf");

	/*******************************************************************/
	TEST_FEATURE ("system shutdown: one job which starts on session-end and ignores SIGTERM");

	TEST_FILENAME (pid_file);

	job = NIH_MUST (nih_sprintf (NULL, "start on session-end\n"
				"\n"
				"script\n"
				"  trap '' TERM\n"
				"  echo hello\n"
				"  echo $$ >\"%s\"\n"
				"  exec sleep 999\n"
				"end script", pid_file));

	CREATE_FILE (confdir, "session-end-term.conf", job);

	start_upstart_common (&upstart_pid, TRUE, FALSE, confdir, logdir, NULL);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	/* Trigger shutdown */
	assert0 (kill (upstart_pid, SIGTERM));

	/* Force reset */
	test_user_mode = FALSE;

	TEST_EQ (timed_waitpid (upstart_pid, 1+TEST_QUIESCE_KILL_PHASE), upstart_pid);

	/* Should not now be running */
	TEST_EQ (kill (upstart_pid, 0), -1);
	TEST_EQ (errno, ESRCH);

	logfile = NIH_MUST (nih_sprintf (NULL, "%s/%s",
				logdir,
				"session-end-term.log"));

	file = fopen (logfile, "r");
	TEST_NE_P (file, NULL);
	TEST_FILE_EQ (file, "hello\r\n");
	TEST_FILE_END (file);
	TEST_EQ (fclose (file), 0);
	assert0 (unlink (logfile));

	session_file = NIH_MUST (nih_sprintf (NULL, "%s/upstart/sessions/%d.session",
				sessiondir, (int)upstart_pid));
	unlink (session_file);

	/* kill job pid if not already dead */
	file = fopen (pid_file, "r");
	TEST_NE_P (file, NULL);
	TEST_EQ (fscanf (file, "%d", &job_pid), 1);
	fclose (file);

	/* pid should still be running */
	TEST_EQ (kill (job_pid, SIGKILL), 0);

	assert0 (unlink (pid_file));

	DELETE_FILE (confdir, "session-end-term.conf");

	/*******************************************************************/
	TEST_FEATURE ("system shutdown: 2 jobs "
			"(1 long-running job which ignores SIGTERM, "
			"1 which starts on session-end and ignores SIGTERM)");

	CREATE_FILE (confdir, "long-running-term.conf",
			"script\n"
			"  trap '' TERM\n"
		        "  exec sleep 999\n"
			"end script");

	TEST_FILENAME (pid_file);

	job = NIH_MUST (nih_sprintf (NULL, "start on session-end\n"
				"\n"
				"script\n"
				"  trap '' TERM\n"
				"  echo $$ >\"%s\"\n"
				"  exec sleep 999\n"
				"end script", pid_file));

	CREATE_FILE (confdir, "session-end-term.conf", job);

	start_upstart_common (&upstart_pid, TRUE, FALSE, confdir, logdir, NULL);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	cmd = nih_sprintf (NULL, "%s start %s 2>&1",
			get_initctl (), "long-running-term");
	TEST_NE_P (cmd, NULL);

	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	nih_free (output);

	job_pid = job_to_pid ("long-running-term");
	TEST_NE (job_pid, -1);

	/* Trigger shutdown */
	assert0 (kill (upstart_pid, SIGTERM));

	/* Force reset */
	test_user_mode = FALSE;

	TEST_EQ (timed_waitpid (upstart_pid, 1+TEST_QUIESCE_KILL_PHASE), upstart_pid);

	/* Should not now be running */
	TEST_EQ (kill (upstart_pid, 0), -1);
	TEST_EQ (errno, ESRCH);

	session_file = NIH_MUST (nih_sprintf (NULL, "%s/upstart/sessions/%d.session",
				sessiondir, (int)upstart_pid));
	unlink (session_file);

	/* the long-running job pid should no longer exist */
	kill (job_pid, SIGKILL);
	TEST_EQ (errno, ESRCH);

	file = fopen (pid_file, "r");
	TEST_NE_P (file, NULL);
	TEST_EQ (fscanf (file, "%d", &job_pid), 1);
	fclose (file);

	/* .... but the session-end job pid should still be running */
	TEST_EQ (kill (job_pid, SIGKILL), 0);

	assert0 (unlink (pid_file));

	DELETE_FILE (confdir, "long-running-term.conf");
	DELETE_FILE (confdir, "session-end-term.conf");

	/*******************************************************************/
	TEST_FEATURE ("session shutdown: no jobs");

	start_upstart_common (&upstart_pid, TRUE, FALSE, confdir, logdir, NULL);

	/* Further required initctl global resets. Shudder. */
	user_mode = TRUE;
	use_dbus = -1;
	dbus_bus_type = DBUS_BUS_SESSION;
	dbus_bus_type = -1;

	upstart = upstart_open (NULL);
	TEST_NE_P (upstart, NULL);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	/* Force reset */
	test_user_mode = FALSE;

	/* Trigger session shutdown */
	assert0 (upstart_end_session_sync (NULL, upstart));

	/* no jobs, so Session Init should shutdown "immediately" */
	TEST_EQ (timed_waitpid (upstart_pid, TEST_QUIESCE_KILL_PHASE), upstart_pid);

	/* Should not now be running */
	TEST_EQ (kill (upstart_pid, 0), -1);

	session_file = NIH_MUST (nih_sprintf (NULL, "%s/upstart/sessions/%d.session",
				sessiondir, (int)upstart_pid));
	unlink (session_file);

	/*******************************************************************/
	TEST_FEATURE ("session shutdown: one long-running job");

	CREATE_FILE (confdir, "long-running.conf",
			"exec sleep 999");

	start_upstart_common (&upstart_pid, TRUE, FALSE, confdir, logdir, NULL);

	cmd = nih_sprintf (NULL, "%s start %s 2>&1",
			get_initctl (), "long-running");
	TEST_NE_P (cmd, NULL);

	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	nih_free (output);

	job_pid = job_to_pid ("long-running");
	TEST_NE (job_pid, -1);

	upstart = upstart_open (NULL);
	TEST_NE_P (upstart, NULL);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	/* Force reset */
	test_user_mode = FALSE;

	/* Trigger session shutdown */
	assert0 (upstart_end_session_sync (NULL, upstart));

	TEST_EQ (timed_waitpid (upstart_pid, TEST_QUIESCE_KILL_PHASE), upstart_pid);

	/* Should not now be running */
	TEST_EQ (kill (upstart_pid, 0), -1);
	TEST_EQ (errno, ESRCH);

	session_file = NIH_MUST (nih_sprintf (NULL, "%s/upstart/sessions/%d.session",
				sessiondir, (int)upstart_pid));
	unlink (session_file);

	/* pid should no longer exist */
	TEST_EQ (kill (job_pid, SIGKILL), -1);
	TEST_EQ (errno, ESRCH);

	DELETE_FILE (confdir, "long-running.conf");

	/*******************************************************************/
	TEST_FEATURE ("session shutdown: one long-running job which starts on startup");

	CREATE_FILE (confdir, "startup.conf",
			"start on startup\n"
			"exec sleep 999");

	start_upstart_common (&upstart_pid, TRUE, FALSE, confdir, logdir, NULL);

	upstart = upstart_open (NULL);
	TEST_NE_P (upstart, NULL);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	job_pid = job_to_pid ("startup");
	TEST_NE (job_pid, -1);

	/* Force reset */
	test_user_mode = FALSE;

	/* Trigger session shutdown */
	assert0 (upstart_end_session_sync (NULL, upstart));

	/* Session Init should end very quickly since there will be no
	 * wait phase.
	 */
	TEST_EQ (timed_waitpid (upstart_pid, TEST_QUIESCE_KILL_PHASE), upstart_pid);

	/* Should not now be running */
	TEST_EQ (kill (upstart_pid, 0), -1);
	TEST_EQ (errno, ESRCH);

	session_file = NIH_MUST (nih_sprintf (NULL, "%s/upstart/sessions/%d.session",
				sessiondir, (int)upstart_pid));
	unlink (session_file);

	/* pid should no longer exist */
	TEST_EQ (kill (job_pid, SIGKILL), -1);
	TEST_EQ (errno, ESRCH);

	DELETE_FILE (confdir, "startup.conf");

	/*******************************************************************/
	TEST_FEATURE ("session shutdown: one long-running job which ignores SIGTERM");

	CREATE_FILE (confdir, "long-running-term.conf",
			"script\n"
			"  trap '' TERM\n"
		        "  sleep 999\n"
			"end script");

	start_upstart_common (&upstart_pid, TRUE, FALSE, confdir, logdir, NULL);

	cmd = nih_sprintf (NULL, "%s start %s 2>&1",
			get_initctl (), "long-running-term");
	TEST_NE_P (cmd, NULL);

	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	nih_free (output);

	job_pid = job_to_pid ("long-running-term");
	TEST_NE (job_pid, -1);

	upstart = upstart_open (NULL);
	TEST_NE_P (upstart, NULL);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	/* Force reset */
	test_user_mode = FALSE;

	/* Trigger session shutdown */
	assert0 (upstart_end_session_sync (NULL, upstart));

	TEST_EQ (timed_waitpid (upstart_pid, TEST_QUIESCE_KILL_PHASE), upstart_pid);

	/* Should not now be running */
	TEST_EQ (kill (upstart_pid, 0), -1);
	TEST_EQ (errno, ESRCH);

	session_file = NIH_MUST (nih_sprintf (NULL, "%s/upstart/sessions/%d.session",
				sessiondir, (int)upstart_pid));
	unlink (session_file);

	/* pid should no longer exist */
	TEST_EQ (kill (job_pid, SIGKILL), -1);
	TEST_EQ (errno, ESRCH);

	DELETE_FILE (confdir, "long-running-term.conf");

	/*******************************************************************/
	TEST_FEATURE ("session shutdown: one job which starts on session-end");

	TEST_FILENAME (pid_file);

	job = NIH_MUST (nih_sprintf (NULL, "start on session-end\n"
				"\n"
				"script\n"
				"  echo hello\n"
				"  echo $$ >\"%s\"\n"
				"  exec sleep 999\n"
				"end script", pid_file));

	CREATE_FILE (confdir, "session-end.conf", job);

	start_upstart_common (&upstart_pid, TRUE, FALSE, confdir, logdir, NULL);

	upstart = upstart_open (NULL);
	TEST_NE_P (upstart, NULL);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	/* Force reset */
	test_user_mode = FALSE;

	/* Trigger session shutdown */
	assert0 (upstart_end_session_sync (NULL, upstart));

	TEST_EQ (timed_waitpid (upstart_pid, TEST_QUIESCE_TOTAL_WAIT_TIME), upstart_pid);

	/* Should not now be running */
	TEST_EQ (kill (upstart_pid, 0), -1);

	logfile = NIH_MUST (nih_sprintf (NULL, "%s/%s",
				logdir,
				"session-end.log"));

	file = fopen (logfile, "r");
	TEST_NE_P (file, NULL);
	TEST_FILE_EQ (file, "hello\r\n");
	TEST_FILE_END (file);
	TEST_EQ (fclose (file), 0);
	assert0 (unlink (logfile));

	file = fopen (pid_file, "r");
	TEST_NE_P (file, NULL);
	TEST_EQ (fscanf (file, "%d", &job_pid), 1);
	fclose (file);

	/* pid should no longer exist */
	TEST_EQ (kill (job_pid, SIGKILL), -1);
	TEST_EQ (errno, ESRCH);

	assert0 (unlink (pid_file));

	session_file = NIH_MUST (nih_sprintf (NULL, "%s/upstart/sessions/%d.session",
				sessiondir, (int)upstart_pid));
	unlink (session_file);

	DELETE_FILE (confdir, "session-end.conf");

	/*******************************************************************/
	TEST_FEATURE ("session shutdown: one job which starts on session-end");

	TEST_FILENAME (pid_file);

	job = NIH_MUST (nih_sprintf (NULL, "start on session-end\n"
				"\n"
				"script\n"
				"  trap '' TERM\n"
				"  echo hello\n"
				"  echo $$ >\"%s\"\n"
				"  exec sleep 999\n"
				"end script", pid_file));

	CREATE_FILE (confdir, "session-end-term.conf", job);

	start_upstart_common (&upstart_pid, TRUE, FALSE, confdir, logdir, NULL);

	upstart = upstart_open (NULL);
	TEST_NE_P (upstart, NULL);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	/* Force reset */
	test_user_mode = FALSE;

	/* Trigger session shutdown */
	assert0 (upstart_end_session_sync (NULL, upstart));

	TEST_EQ (timed_waitpid (upstart_pid, TEST_QUIESCE_TOTAL_WAIT_TIME), upstart_pid);

	/* Should not now be running */
	TEST_EQ (kill (upstart_pid, 0), -1);

	logfile = NIH_MUST (nih_sprintf (NULL, "%s/%s",
				logdir,
				"session-end-term.log"));

	file = fopen (logfile, "r");
	TEST_NE_P (file, NULL);
	TEST_FILE_EQ (file, "hello\r\n");
	TEST_FILE_END (file);
	TEST_EQ (fclose (file), 0);
	assert0 (unlink (logfile));

	file = fopen (pid_file, "r");
	TEST_NE_P (file, NULL);
	TEST_EQ (fscanf (file, "%d", &job_pid), 1);
	fclose (file);

	/* pid should no longer exist */
	TEST_EQ (kill (job_pid, SIGKILL), -1);
	TEST_EQ (errno, ESRCH);

	assert0 (unlink (pid_file));

	session_file = NIH_MUST (nih_sprintf (NULL, "%s/upstart/sessions/%d.session",
				sessiondir, (int)upstart_pid));
	unlink (session_file);

	DELETE_FILE (confdir, "session-end-term.conf");

	/*******************************************************************/
	TEST_FEATURE ("session shutdown: 2 jobs "
			"(1 long-running job which ignores SIGTERM, "
			"1 which starts on session-end and ignores SIGTERM)");

	CREATE_FILE (confdir, "long-running-term.conf",
			"script\n"
			"  trap '' TERM\n"
		        "  sleep 999\n"
			"end script");

	TEST_FILENAME (pid_file);

	job = NIH_MUST (nih_sprintf (NULL, "start on session-end\n"
				"\n"
				"script\n"
				"  trap '' TERM\n"
				"  echo $$ >\"%s\"\n"
				"  sleep 999\n"
				"end script", pid_file));

	CREATE_FILE (confdir, "session-end-term.conf", job);

	start_upstart_common (&upstart_pid, TRUE, FALSE, confdir, logdir, NULL);

	cmd = nih_sprintf (NULL, "%s start %s 2>&1",
			get_initctl (), "long-running-term");
	TEST_NE_P (cmd, NULL);

	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	nih_free (output);

	job_pid = job_to_pid ("long-running-term");
	TEST_NE (job_pid, -1);

	upstart = upstart_open (NULL);
	TEST_NE_P (upstart, NULL);

	/* Should be running */
	assert0 (kill (upstart_pid, 0));

	/* Force reset */
	test_user_mode = FALSE;

	/* Trigger session shutdown */
	assert0 (upstart_end_session_sync (NULL, upstart));

	TEST_EQ (timed_waitpid (upstart_pid, TEST_QUIESCE_TOTAL_WAIT_TIME), upstart_pid);

	/* Should not now be running */
	TEST_EQ (kill (upstart_pid, 0), -1);

	session_file = NIH_MUST (nih_sprintf (NULL, "%s/upstart/sessions/%d.session",
				sessiondir, (int)upstart_pid));
	unlink (session_file);

	/* pid should no longer exist */
	TEST_EQ (kill (job_pid, SIGKILL), -1);
	TEST_EQ (errno, ESRCH);

	file = fopen (pid_file, "r");
	TEST_NE_P (file, NULL);
	TEST_EQ (fscanf (file, "%d", &job_pid), 1);
	fclose (file);

	/* pid should no longer exist */
	TEST_EQ (kill (job_pid, SIGKILL), -1);
	TEST_EQ (errno, ESRCH);

	assert0 (unlink (pid_file));

	DELETE_FILE (confdir, "long-running-term.conf");
	DELETE_FILE (confdir, "session-end-term.conf");

	/*******************************************************************/
	assert0 (unsetenv ("UPSTART_CONFDIR"));
	assert0 (unsetenv ("UPSTART_LOGDIR"));

        TEST_EQ (rmdir (logdir), 0);
        TEST_EQ (rmdir (confdir), 0);

	session_file = NIH_MUST (nih_sprintf (NULL, "%s/upstart/sessions", sessiondir));
        TEST_EQ (rmdir (session_file), 0);
	session_file = NIH_MUST (nih_sprintf (NULL, "%s/upstart", sessiondir));
        TEST_EQ (rmdir (session_file), 0);

	/*******************************************************************/
}

void
test_umask (void)
{
	char             confdir[PATH_MAX];
	char             dirname[PATH_MAX];
	char             logdir[PATH_MAX];
	pid_t            upstart_pid = 0;
	nih_local char  *logfile = NULL;
	nih_local char  *original_runtime = NULL;
	mode_t           job_umask;
	nih_local char  *job_umask_str = NULL;
	size_t           length;
	int              ret;
	mode_t           original_umask;
	mode_t           test_umask = 0077;
	mode_t           default_umask = 022;

	original_runtime = nih_strdup (NULL, getenv ("XDG_RUNTIME_DIR"));
	TEST_NE_P (original_runtime, NULL);

	TEST_FILENAME (dirname);
	TEST_EQ (mkdir (dirname, 0755), 0);
	TEST_EQ (setenv ("XDG_RUNTIME_DIR", dirname, 1), 0);

	TEST_FILENAME (confdir);
	TEST_EQ (mkdir (confdir, 0755), 0);
	TEST_EQ (setenv ("UPSTART_CONFDIR", confdir, 1), 0);

	TEST_FILENAME (logdir);
	TEST_EQ (mkdir (logdir, 0755), 0);

	original_umask = umask (test_umask);

	TEST_GROUP ("Session Init umask value");

	/**********************************************************************/
	TEST_FEATURE ("ensure Session Init inherits umask by default");

	/* Has to be a script since umask is a shell built-in */
	CREATE_FILE (confdir, "umask.conf",
			"start on startup\n"
			"script\n"
			"umask\n"
			"end script");

	start_upstart_common (&upstart_pid, TRUE, TRUE, confdir, logdir, NULL);

	logfile = NIH_MUST (nih_sprintf (NULL, "%s/%s",
				logdir,
				"umask.log"));

	WAIT_FOR_FILE (logfile);

	job_umask_str = nih_file_read (NULL, logfile, &length);

	ret = sscanf (job_umask_str, "%o", (unsigned int *)&job_umask);
	TEST_EQ (ret, 1);
	TEST_EQ (job_umask, test_umask);

	DELETE_FILE (confdir, "umask.conf");
	assert0 (unlink (logfile));

	STOP_UPSTART (upstart_pid);

	/**********************************************************************/
	TEST_FEATURE ("ensure Session Init defaults umask with '--no-inherit-env'");

	/* Has to be a script since umask is a shell built-in */
	CREATE_FILE (confdir, "umask.conf",
			"start on startup\n"
			"script\n"
			"umask\n"
			"end script");

	start_upstart_common (&upstart_pid, TRUE, FALSE, confdir, logdir, NULL);

	logfile = NIH_MUST (nih_sprintf (NULL, "%s/%s",
				logdir,
				"umask.log"));

	WAIT_FOR_FILE (logfile);

	job_umask_str = nih_file_read (NULL, logfile, &length);

	ret = sscanf (job_umask_str, "%o", (unsigned int *)&job_umask);
	TEST_EQ (ret, 1);
	TEST_EQ (job_umask, default_umask);

	DELETE_FILE (confdir, "umask.conf");
	assert0 (unlink (logfile));

	STOP_UPSTART (upstart_pid);

	/**********************************************************************/

	/* Restore */
	(void)umask (original_umask);
	TEST_EQ (setenv ("XDG_RUNTIME_DIR", original_runtime, 1), 0);

	assert0 (rmdir (confdir));
	assert0 (rmdir (logdir));
}

void
test_show_config (void)
{
	char             dirname[PATH_MAX];
	nih_local char  *cmd = NULL;
	pid_t            upstart_pid = 0;
	pid_t            dbus_pid    = 0;
	char           **output;
	size_t           lines;
	char             expected_output[] = "foo";

	TEST_GROUP ("show_config");

	TEST_FILENAME (dirname);
	TEST_EQ (mkdir (dirname, 0755), 0);

	/* Use the "secret" interface */
	TEST_EQ (setenv ("UPSTART_CONFDIR", dirname, 1), 0);

	TEST_DBUS (dbus_pid);
	START_UPSTART (upstart_pid, FALSE);

	TEST_FEATURE ("no emits, no start on, no stop on");
	CREATE_FILE (dirname, "foo.conf",
			"author \"foo\"\n"
			"description \"wibble\"");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ (lines, 1);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config -e foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ (lines, 1);
	nih_free (output);

	DELETE_FILE (dirname, "foo.conf");

	/*******************************************************************/

	TEST_FEATURE ("1 emits, no start on, no stop on");

	CREATE_FILE (dirname, "foo.conf",
			"author \"foo\"\n"
			"emits \"thing\"\n"
			"description \"wibble\"");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits thing");
	TEST_EQ (lines, 2);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config -e foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits thing");
	TEST_EQ (lines, 2);
	nih_free (output);

	DELETE_FILE (dirname, "foo.conf");

	/*******************************************************************/

	TEST_FEATURE ("2 emits, no start on, no stop on");

	CREATE_FILE (dirname, "foo.conf",
			"author \"foo\"\n"
			"emits \"thing\"\n"
			"emits \"thong\"\n"
			"description \"wibble\"");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits thing");
	TEST_EQ_STR (output[2], "  emits thong");
	TEST_EQ (lines, 3);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config -e foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits thing");
	TEST_EQ_STR (output[2], "  emits thong");
	TEST_EQ (lines, 3);
	nih_free (output);

	DELETE_FILE (dirname, "foo.conf");

	/*******************************************************************/

	TEST_FEATURE ("no emits, start on, no stop on");

	CREATE_FILE (dirname, "foo.conf",
			"author \"foo\"\n"
			"start on (A and B)\n"
			"description \"wibble\"");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  start on (A and B)");
	TEST_EQ (lines, 2);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config -e foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  start on A (job:, env:)");
	TEST_EQ_STR (output[2], "  start on B (job:, env:)");
	TEST_EQ (lines, 3);
	nih_free (output);

	DELETE_FILE (dirname, "foo.conf");

	/*******************************************************************/

	TEST_FEATURE ("1 emits, start on, no stop on");

	CREATE_FILE (dirname, "foo.conf",
			"author \"foo\"\n"
			"emits \"bong\"\n"
			"start on (A and B)\n"
			"description \"wibble\"");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits bong");
	TEST_EQ_STR (output[2], "  start on (A and B)");
	TEST_EQ (lines, 3);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config -e foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits bong");
	TEST_EQ_STR (output[2], "  start on A (job:, env:)");
	TEST_EQ_STR (output[3], "  start on B (job:, env:)");
	TEST_EQ (lines, 4);
	nih_free (output);

	DELETE_FILE (dirname, "foo.conf");

	/*******************************************************************/

	TEST_FEATURE ("2 emits, start on, no stop on");

	CREATE_FILE (dirname, "foo.conf",
			"emits \"bong\"\n"
			"author \"foo\"\n"
			"start on (A and B)\n"
			"emits \"stime\"\n"
			"description \"wibble\"");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits bong");
	TEST_EQ_STR (output[2], "  emits stime");
	TEST_EQ_STR (output[3], "  start on (A and B)");
	TEST_EQ (lines, 4);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config -e foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits bong");
	TEST_EQ_STR (output[2], "  emits stime");
	TEST_EQ_STR (output[3], "  start on A (job:, env:)");
	TEST_EQ_STR (output[4], "  start on B (job:, env:)");
	TEST_EQ (lines, 5);
	nih_free (output);

	DELETE_FILE (dirname, "foo.conf");

	/*******************************************************************/

	TEST_FEATURE ("no emits, no start on, stop on");

	CREATE_FILE (dirname, "foo.conf",
			"author \"foo\"\n"
			"stop on (A or B)\n"
			"description \"wibble\"");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  stop on (A or B)");
	TEST_EQ (lines, 2);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config -e foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  stop on A (job:, env:)");
	TEST_EQ_STR (output[2], "  stop on B (job:, env:)");
	TEST_EQ (lines, 3);
	nih_free (output);

	DELETE_FILE (dirname, "foo.conf");

	/*******************************************************************/

	TEST_FEATURE ("1 emits, no start on, stop on");

	CREATE_FILE (dirname, "foo.conf",
			"author \"foo\"\n"
			"emits \"bong\"\n"
			"stop on (A or B)\n"
			"description \"wibble\"");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits bong");
	TEST_EQ_STR (output[2], "  stop on (A or B)");
	TEST_EQ (lines, 3);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config -e foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits bong");
	TEST_EQ_STR (output[2], "  stop on A (job:, env:)");
	TEST_EQ_STR (output[3], "  stop on B (job:, env:)");
	TEST_EQ (lines, 4);
	nih_free (output);

	DELETE_FILE (dirname, "foo.conf");

	/*******************************************************************/

	TEST_FEATURE ("2 emits, no start on, stop on");

	CREATE_FILE (dirname, "foo.conf",
			"emits \"bong\"\n"
			"author \"foo\"\n"
			"stop on (A or B)\n"
			"emits \"stime\"\n"
			"description \"wibble\"");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits bong");
	TEST_EQ_STR (output[2], "  emits stime");
	TEST_EQ_STR (output[3], "  stop on (A or B)");
	TEST_EQ (lines, 4);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config -e foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits bong");
	TEST_EQ_STR (output[2], "  emits stime");
	TEST_EQ_STR (output[3], "  stop on A (job:, env:)");
	TEST_EQ_STR (output[4], "  stop on B (job:, env:)");
	TEST_EQ (lines, 5);
	nih_free (output);

	DELETE_FILE (dirname, "foo.conf");

	/*******************************************************************/

	TEST_FEATURE ("2 emits, start on with only initial JOB, stop on with JOB at end of env");

	CREATE_FILE (dirname, "foo.conf",
			"emits \"bong\"\n"
			"author \"foo\"\n"
			"stop on (A or stopping c=d e=f g=h JOB=\"bang\")\n"
			"emits \"stime\"\n"
			"start on (starting JOB=\"boo\" or B x=y)\n"
			"description \"wibble\"");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits bong");
	TEST_EQ_STR (output[2], "  emits stime");
	TEST_EQ_STR (output[3], "  start on (starting JOB=boo or B x=y)");
	TEST_EQ_STR (output[4], "  stop on (A or stopping c=d e=f g=h JOB=bang)");
	TEST_EQ (lines, 5);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config -e foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits bong");
	TEST_EQ_STR (output[2], "  emits stime");
	TEST_EQ_STR (output[3], "  start on starting (job: boo, env:)");
	TEST_EQ_STR (output[4], "  start on B (job:, env: x=y)");
	TEST_EQ_STR (output[5], "  stop on A (job:, env:)");
	TEST_EQ_STR (output[6], "  stop on stopping (job: bang, env: c=d e=f g=h)");
	TEST_EQ (lines, 7);
	nih_free (output);

	DELETE_FILE (dirname, "foo.conf");

	/*******************************************************************/

	TEST_FEATURE ("2 emits, start on with initial JOB+env, stop on with JOB at end of env");

	CREATE_FILE (dirname, "foo.conf",
			"emits \"bong\"\n"
			"author \"foo\"\n"
			"stop on (A or stopping c=d e=f g=h JOB=\"bang\")\n"
			"emits \"stime\"\n"
			"start on (starting JOB=\"boo\" P=Q c=sea or B x=y)\n"
			"description \"wibble\"");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits bong");
	TEST_EQ_STR (output[2], "  emits stime");
	TEST_EQ_STR (output[3], "  start on (starting JOB=boo P=Q c=sea or B x=y)");
	TEST_EQ_STR (output[4], "  stop on (A or stopping c=d e=f g=h JOB=bang)");
	TEST_EQ (lines, 5);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config -e foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits bong");
	TEST_EQ_STR (output[2], "  emits stime");
	TEST_EQ_STR (output[3], "  start on starting (job: boo, env: P=Q c=sea)");
	TEST_EQ_STR (output[4], "  start on B (job:, env: x=y)");
	TEST_EQ_STR (output[5], "  stop on A (job:, env:)");
	TEST_EQ_STR (output[6], "  stop on stopping (job: bang, env: c=d e=f g=h)");
	TEST_EQ (lines, 7);
	nih_free (output);

	DELETE_FILE (dirname, "foo.conf");

	/*******************************************************************/

	TEST_FEATURE ("3 emits, start on (with env), stop on (with env)");

	CREATE_FILE (dirname, "foo.conf",
			"emits \"bong\"\n"
			"stop on starting D and (stopping E or F hello=world)\n"
			"author \"foo\"\n"
			"emits \"bar\"\n"
			"emits \"stime\"\n"
			"start on A and (B FOO=BAR or starting C x=y)\n"
			"description \"wibble\"");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits bong");
	TEST_EQ_STR (output[2], "  emits bar");
	TEST_EQ_STR (output[3], "  emits stime");
	/* note the extra brackets! */
	TEST_EQ_STR (output[4], "  start on (A and (B FOO=BAR or starting C x=y))");
	/* note the extra brackets! */
	TEST_EQ_STR (output[5], "  stop on (starting D and (stopping E or F hello=world))");
	TEST_EQ (lines, 6);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config -e foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits bong");
	TEST_EQ_STR (output[2], "  emits bar");
	TEST_EQ_STR (output[3], "  emits stime");
	TEST_EQ_STR (output[4], "  start on A (job:, env:)");
	TEST_EQ_STR (output[5], "  start on B (job:, env: FOO=BAR)");
	TEST_EQ_STR (output[6], "  start on starting (job: C, env: x=y)");
	TEST_EQ_STR (output[7], "  stop on starting (job: D, env:)");
	TEST_EQ_STR (output[8], "  stop on stopping (job: E, env:)");
	TEST_EQ_STR (output[9], "  stop on F (job:, env: hello=world)");
	TEST_EQ (lines, 10);
	nih_free (output);

	DELETE_FILE (dirname, "foo.conf");

	/*******************************************************************/

	TEST_FEATURE ("3 emits, complex start on (with env), complex stop on (with env)");

	CREATE_FILE (dirname, "foo.conf",
			"emits \"bong\"\n"
			"stop on runlevel [!2345] colour=blue or starting rocket\n"
			"author \"foo\"\n"
			"emits \"bar\"\n"
			"emits \"stime\"\n"
			"start on (starting mountall or (runlevel [016] and "
			"(stopped gdm or stopped kdm or stopped xdm A=B or stopping lxdm)))\n"
			"description \"wibble\"");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], expected_output);
	TEST_EQ_STR (output[1], "  emits bong");
	TEST_EQ_STR (output[2], "  emits bar");
	TEST_EQ_STR (output[3], "  emits stime");
	/* note the extra brackets! */
	TEST_EQ_STR (output[4], "  start on (starting mountall or (runlevel [016] and "
			"(((stopped gdm or stopped kdm) or stopped xdm A=B) or stopping lxdm)))");
	/* note the extra brackets! */
	TEST_EQ_STR (output[5], "  stop on (runlevel [!2345] colour=blue or starting rocket)");
	TEST_EQ (lines, 6);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s show-config -e foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0],  expected_output);
	TEST_EQ_STR (output[1],  "  emits bong");
	TEST_EQ_STR (output[2],  "  emits bar");
	TEST_EQ_STR (output[3],  "  emits stime");
	TEST_EQ_STR (output[4],  "  start on starting (job: mountall, env:)");
	TEST_EQ_STR (output[5],  "  start on runlevel (job:, env: [016])");
	TEST_EQ_STR (output[6],  "  start on stopped (job: gdm, env:)");
	TEST_EQ_STR (output[7],  "  start on stopped (job: kdm, env:)");
	TEST_EQ_STR (output[8],  "  start on stopped (job: xdm, env: A=B)");
	TEST_EQ_STR (output[9],  "  start on stopping (job: lxdm, env:)");
	TEST_EQ_STR (output[10], "  stop on runlevel (job:, env: [!2345] colour=blue)");
	TEST_EQ_STR (output[11], "  stop on starting (job: rocket, env:)");
	TEST_EQ (lines, 12);
	nih_free (output);

	DELETE_FILE (dirname, "foo.conf");

	/*******************************************************************/

	STOP_UPSTART (upstart_pid);
	TEST_EQ (unsetenv ("UPSTART_CONFDIR"), 0);
	TEST_DBUS_END (dbus_pid);
        TEST_EQ (rmdir (dirname), 0);
}

void
test_check_config (void)
{
	char             dirname[PATH_MAX];
	nih_local char  *cmd = NULL;
	pid_t            upstart_pid = 0;
	pid_t            dbus_pid    = 0;
	char           **output;
	size_t           lines;

	TEST_GROUP ("check_config");

        TEST_FILENAME (dirname);
        TEST_EQ (mkdir (dirname, 0755), 0);

	/* Use the "secret" interface */
	TEST_EQ (setenv ("UPSTART_CONFDIR", dirname, 1), 0);

	TEST_DBUS (dbus_pid);
	START_UPSTART (upstart_pid, FALSE);

	/*******************************************************************/

	TEST_FEATURE ("no unreachable jobs/events (satisfied by job or event)");

	CREATE_FILE (dirname, "foo.conf",
			"start on (starting bar or wibble)");

	CREATE_FILE (dirname, "bar.conf",
			"task\n"
			"exec true");

	CREATE_FILE (dirname, "baz.conf",
			"emits wibble");

	cmd = nih_sprintf (NULL, "%s check-config 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);

	DELETE_FILE (dirname, "foo.conf");
	DELETE_FILE (dirname, "bar.conf");
	DELETE_FILE (dirname, "baz.conf");

	/*******************************************************************/

	TEST_FEATURE ("no unreachable jobs/events (satisfied by job)");

	CREATE_FILE (dirname, "foo.conf",
			"start on (starting bar or wibble)");

	CREATE_FILE (dirname, "bar.conf",
			"task\n"
			"exec true");

	cmd = nih_sprintf (NULL, "%s check-config 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);

	DELETE_FILE (dirname, "foo.conf");
	DELETE_FILE (dirname, "bar.conf");

	/*******************************************************************/

	TEST_FEATURE ("no unreachable jobs/events (satisfied by event)");

	CREATE_FILE (dirname, "foo.conf",
			"start on (starting bar or wibble)");

	CREATE_FILE (dirname, "baz.conf",
			"emits wibble");

	cmd = nih_sprintf (NULL, "%s check-config 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);

	DELETE_FILE (dirname, "foo.conf");
	DELETE_FILE (dirname, "baz.conf");

	/*******************************************************************/

	TEST_FEATURE ("unreachable event");

	CREATE_FILE (dirname, "foo.conf",
			"start on (starting bar and wibble)");

	CREATE_FILE (dirname, "bar.conf",
			"task\n"
			"exec true");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s check-config 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], "foo");
	TEST_EQ_STR (output[1], "  start on: unknown event wibble");
	TEST_EQ (lines, 2);

	DELETE_FILE (dirname, "foo.conf");
	DELETE_FILE (dirname, "bar.conf");

	/*******************************************************************/

	TEST_FEATURE ("unreachable job");

	CREATE_FILE (dirname, "foo.conf",
			"start on (starting bar and wibble)");

	CREATE_FILE (dirname, "baz.conf",
			"emits wibble");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s check-config 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], "foo");
	TEST_EQ_STR (output[1], "  start on: unknown job bar");
	TEST_EQ (lines, 2);

	DELETE_FILE (dirname, "foo.conf");
	DELETE_FILE (dirname, "baz.conf");

	/*******************************************************************/

	TEST_FEATURE ("unreachable event with forced ignore");

	CREATE_FILE (dirname, "foo.conf",
			"start on (starting bar and wibble)");

	CREATE_FILE (dirname, "bar.conf",
			"task\n"
			"exec true");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s check-config --ignore-events=wibble 2>&1",
			get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);

	DELETE_FILE (dirname, "bar.conf");

	/*******************************************************************/

	TEST_FEATURE ("unreachable events with forced ignores");

	CREATE_FILE (dirname, "foo.conf",
			"start on (fred and wilma)");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s check-config --ignore-events=wilma,foo,fred 2>&1",
			get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);

	DELETE_FILE (dirname, "foo.conf");

	/*******************************************************************/

	TEST_FEATURE ("satisfiable complex start on");

	/* Yes folks, it's the classic */
	CREATE_FILE (dirname, "plymouth.conf",
			"start on (starting mountall\n"
			"      or (runlevel [016]\n"
              		"          and (stopped gdm\n"
                   	"              or stopped kdm\n"
			"              or stopped xdm\n"
                   	"              or stopped lxdm)))");

	CREATE_FILE (dirname, "mountall.conf", "exec true");
	CREATE_FILE (dirname, "gdm.conf"     , "exec true");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s check-config --ignore-events=runlevel 2>&1",
			get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);

	DELETE_FILE (dirname, "plymouth.conf");
	DELETE_FILE (dirname, "mountall.conf");
	DELETE_FILE (dirname, "gdm.conf");

	/*******************************************************************/

	TEST_FEATURE ("unsatisfiable complex start on");

	CREATE_FILE (dirname, "plymouth.conf",
			"start on (starting mountall\n"
			"      or (runlevel [016]\n"
              		"          and (stopped gdm\n"
                   	"              or stopped kdm\n"
			"              or stopped xdm\n"
                   	"              or stopped lxdm)))");

	CREATE_FILE (dirname, "mountall.conf", "exec true");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s check-config --ignore-events=runlevel 2>&1",
			get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	TEST_EQ_STR (output[0], "plymouth");
	TEST_EQ_STR (output[1], "  start on: unknown job lxdm");
	TEST_EQ_STR (output[2], "  start on: unknown job xdm");
	TEST_EQ_STR (output[3], "  start on: unknown job kdm");
	TEST_EQ_STR (output[4], "  start on: unknown job gdm");
	TEST_EQ (lines, 5);

	DELETE_FILE (dirname, "plymouth.conf");
	DELETE_FILE (dirname, "mountall.conf");

	/*******************************************************************/

	TEST_FEATURE ("satisfiable complex stop on");

	/* Yes folks, it's the classic */
	CREATE_FILE (dirname, "plymouth.conf",
			"stop on (starting mountall\n"
			"      or (runlevel [016]\n"
              		"          and (stopped gdm\n"
                   	"              or stopped kdm\n"
			"              or stopped xdm\n"
                   	"              or stopped lxdm)))");

	CREATE_FILE (dirname, "mountall.conf", "exec true");
	CREATE_FILE (dirname, "gdm.conf"     , "exec true");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s check-config --ignore-events=runlevel 2>&1",
			get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);

	DELETE_FILE (dirname, "plymouth.conf");
	DELETE_FILE (dirname, "mountall.conf");
	DELETE_FILE (dirname, "gdm.conf");

	/*******************************************************************/

	TEST_FEATURE ("unsatisfiable complex stop on");

	CREATE_FILE (dirname, "plymouth.conf",
			"stop on (starting mountall\n"
			"      or (runlevel [016]\n"
              		"          and (stopped gdm\n"
                   	"              or stopped kdm\n"
			"              or stopped xdm\n"
                   	"              or stopped lxdm)))");

	CREATE_FILE (dirname, "mountall.conf", "exec true");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s check-config --ignore-events=runlevel 2>&1",
			get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	TEST_EQ_STR (output[0], "plymouth");
	TEST_EQ_STR (output[1], "  stop on: unknown job lxdm");
	TEST_EQ_STR (output[2], "  stop on: unknown job xdm");
	TEST_EQ_STR (output[3], "  stop on: unknown job kdm");
	TEST_EQ_STR (output[4], "  stop on: unknown job gdm");
	TEST_EQ (lines, 5);

	DELETE_FILE (dirname, "plymouth.conf");
	DELETE_FILE (dirname, "mountall.conf");

	/*******************************************************************/

	TEST_FEATURE ("unsatisfiable complex stop on, satisfiable complex start on");

	CREATE_FILE (dirname, "plymouth.conf",
			"stop on (starting mountall\n"
			"      or (runlevel [016]\n"
              		"          and (stopped gdm\n"
                   	"              or stopped kdm\n"
			"              or stopped xdm\n"
                   	"              or stopped lxdm)))\n"
                   	"start on (stopping portmap\n"
			"         or (runlevel [06] or starting beano))\n");

	CREATE_FILE (dirname, "mountall.conf", "exec true");
	CREATE_FILE (dirname, "portmap.conf", "exec true");
	CREATE_FILE (dirname, "beano.conf", "exec true");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s check-config --ignore-events=runlevel 2>&1",
			get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	TEST_EQ_STR (output[0], "plymouth");
	TEST_EQ_STR (output[1], "  stop on: unknown job lxdm");
	TEST_EQ_STR (output[2], "  stop on: unknown job xdm");
	TEST_EQ_STR (output[3], "  stop on: unknown job kdm");
	TEST_EQ_STR (output[4], "  stop on: unknown job gdm");
	TEST_EQ (lines, 5);

	DELETE_FILE (dirname, "plymouth.conf");
	DELETE_FILE (dirname, "mountall.conf");
	DELETE_FILE (dirname, "portmap.conf");
	DELETE_FILE (dirname, "beano.conf");

	/*******************************************************************/

	TEST_FEATURE ("satisfiable complex start on, unsatisfiable complex stop on");

	CREATE_FILE (dirname, "plymouth.conf",
			"start on (starting mountall\n"
			"      or (hello\n"
              		"          and (stopped gdm\n"
                   	"              or stopped kdm\n"
			"              or stopped xdm\n"
                   	"              or stopped lxdm)))\n"
                   	"stop on (stopping portmap\n"
			"         or (wibble or starting beano))\n");

	CREATE_FILE (dirname, "mountall.conf", "exec true");
	CREATE_FILE (dirname, "portmap.conf",
			"exec true\n"
			"emits hello");
	CREATE_FILE (dirname, "gdm.conf", "exec true");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s check-config >&1",
			get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	TEST_EQ_STR (output[0], "plymouth");
	TEST_EQ_STR (output[1], "  stop on: unknown job beano");
	TEST_EQ_STR (output[2], "  stop on: unknown event wibble");
	TEST_EQ (lines, 3);

	DELETE_FILE (dirname, "plymouth.conf");
	DELETE_FILE (dirname, "mountall.conf");
	DELETE_FILE (dirname, "portmap.conf");
	DELETE_FILE (dirname, "gdm.conf");

	/*******************************************************************/

	TEST_FEATURE ("unsatisfiable complex start on, unsatisfiable complex stop on");

	CREATE_FILE (dirname, "plymouth.conf",
			"start on (starting mountall\n"
			"      or (hello\n"
              		"          and (stopped gdm\n"
                   	"              or stopped kdm\n"
			"              or stopped xdm\n"
                   	"              or stopped lxdm)))\n"
                   	"stop on (stopping portmap\n"
			"         or (wibble or starting beano))\n");

	CREATE_FILE (dirname, "mountall.conf", "exec true");
	CREATE_FILE (dirname, "portmap.conf", "exec true");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s check-config 2>&1",
			get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	TEST_EQ_STR (output[0], "plymouth");
	TEST_EQ_STR (output[1], "  start on: unknown job lxdm");
	TEST_EQ_STR (output[2], "  start on: unknown job xdm");
	TEST_EQ_STR (output[3], "  start on: unknown job kdm");
	TEST_EQ_STR (output[4], "  start on: unknown job gdm");
	TEST_EQ_STR (output[5], "  start on: unknown event hello");
	TEST_EQ_STR (output[6], "  stop on: unknown job beano");
	TEST_EQ_STR (output[7], "  stop on: unknown event wibble");
	TEST_EQ (lines, 8);

	DELETE_FILE (dirname, "plymouth.conf");
	DELETE_FILE (dirname, "mountall.conf");
	DELETE_FILE (dirname, "portmap.conf");

	/*******************************************************************/

	TEST_FEATURE ("satisfiable complex start on, satisfiable complex stop on");

	CREATE_FILE (dirname, "plymouth.conf",
			"start on (starting mountall\n"
			"      or (hello\n"
              		"          and (stopped gdm\n"
                   	"              or (stopped kdm\n"
			"              or (stopped xdm\n"
                   	"              or stopped lxdm)))))\n"
                   	"stop on (stopping portmap\n"
			"         or (wibble or starting beano))\n");

	CREATE_FILE (dirname, "mountall.conf", "exec true\n");
	CREATE_FILE (dirname, "portmap.conf",
			"exec true\n"
			"emits hello");
	CREATE_FILE (dirname, "lxdm.conf", "exec true");
	CREATE_FILE (dirname, "wibble.conf", "emits wibble");
	CREATE_FILE (dirname, "beano.conf", "exec true");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s check-config 2>&1",
			get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	TEST_EQ (lines, 0);

	DELETE_FILE (dirname, "plymouth.conf");
	DELETE_FILE (dirname, "mountall.conf");
	DELETE_FILE (dirname, "portmap.conf");
	DELETE_FILE (dirname, "lxdm.conf");
	DELETE_FILE (dirname, "beano.conf");
	DELETE_FILE (dirname, "wibble.conf");

	/*******************************************************************/

	TEST_FEATURE (
		"satisfiable complex start on, satisfiable complex stop on with warnings");

	CREATE_FILE (dirname, "plymouth.conf",
			"start on (starting mountall\n"
			"      or (hello\n"
              		"          and (stopped gdm\n"
                   	"              or (stopped kdm\n"
			"              or (stopped xdm\n"
                   	"              or stopped lxdm)))))\n"
                   	"stop on (stopping portmap\n"
			"         or (wibble or starting beano))\n");

	CREATE_FILE (dirname, "mountall.conf", "exec true\n");
	CREATE_FILE (dirname, "portmap.conf",
			"exec true\n"
			"emits hello");
	CREATE_FILE (dirname, "lxdm.conf", "exec true");
	CREATE_FILE (dirname, "wibble.conf", "emits wibble");
	CREATE_FILE (dirname, "beano.conf", "exec true");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s check-config --warn 2>&1",
			get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	TEST_EQ_STR (output[0], "plymouth");
	TEST_EQ_STR (output[1], "  start on: unknown job xdm");
	TEST_EQ_STR (output[2], "  start on: unknown job kdm");
	TEST_EQ_STR (output[3], "  start on: unknown job gdm");
	TEST_EQ (lines, 4);

	DELETE_FILE (dirname, "plymouth.conf");
	DELETE_FILE (dirname, "mountall.conf");
	DELETE_FILE (dirname, "portmap.conf");
	DELETE_FILE (dirname, "lxdm.conf");
	DELETE_FILE (dirname, "beano.conf");
	DELETE_FILE (dirname, "wibble.conf");

	/*******************************************************************/

	STOP_UPSTART (upstart_pid);
	TEST_EQ (unsetenv ("UPSTART_CONFDIR"), 0);
	TEST_DBUS_END (dbus_pid);
        TEST_EQ (rmdir (dirname), 0);
}

void
test_notify_disk_writeable (void)
{
	char             confdir_name[PATH_MAX];
	char             logdir_name[PATH_MAX];
	nih_local char  *logfile_name = NULL;
	pid_t            upstart_pid = 0;
	pid_t            dbus_pid;
	nih_local char  *cmd = NULL;
	char           **output;
	size_t           lines;
	struct stat      statbuf;
	mode_t           old_perms;
	FILE            *file;

        TEST_FILENAME (confdir_name);
        TEST_EQ (mkdir (confdir_name, 0755), 0);

        TEST_FILENAME (logdir_name);
        TEST_EQ (mkdir (logdir_name, 0755), 0);

	TEST_EQ (stat (logdir_name, &statbuf), 0);
	old_perms = statbuf.st_mode;

	/* Make inaccessible */
	TEST_EQ (chmod (logdir_name, 0x0), 0);

	/* Use the "secret" interfaces */
	TEST_EQ (setenv ("UPSTART_CONFDIR", confdir_name, 1), 0);
	TEST_EQ (setenv ("UPSTART_LOGDIR", logdir_name, 1), 0);

	TEST_FUNCTION ("notify-disk-writeable");

	TEST_FEATURE ("with job ending before log disk writeable");

	CREATE_FILE (confdir_name, "foo.conf",
			"console log\n"
			"exec echo hello world\n");

	logfile_name = NIH_MUST (nih_sprintf (NULL, "%s/%s",
				logdir_name,
				"foo.log"));

	TEST_DBUS (dbus_pid);
	START_UPSTART (upstart_pid, FALSE);

	cmd = nih_sprintf (NULL, "%s start %s 2>&1",
			get_initctl (), "foo");
	TEST_NE_P (cmd, NULL);

	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);

	/* Give Upstart a chance to respond */
	{
		int i   = 0;
		int max = 5;
		int ret;

		for (i=0; i < max; ++i) {
			nih_free (output);
			cmd = nih_sprintf (NULL, "%s status %s 2>&1",
					get_initctl (), "foo");
			TEST_NE_P (cmd, NULL);

			RUN_COMMAND (NULL, cmd, &output, &lines);
			TEST_EQ (lines, 1);

			ret = fnmatch ("foo stop/waiting", output[0], 0);

			if (! ret) {
				break;
			}

			sleep (1);
		}
	}

	TEST_EQ (fnmatch ("foo stop/waiting", output[0], 0), 0);

	/* Ensure no log file written */
	TEST_LT (stat (logfile_name, &statbuf), 0);

	/* Restore access */
	TEST_EQ (chmod (logdir_name, old_perms), 0);

	/* Ensure again that no log file written */
	TEST_LT (stat (logfile_name, &statbuf), 0);

	/* Must not be run as root */
	TEST_TRUE (getuid ());

	cmd = nih_sprintf (NULL, "%s notify-disk-writeable 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);

	/* Ensure file written now */
	TEST_EQ (stat (logfile_name, &statbuf), 0);

	file = fopen (logfile_name, "r");
	TEST_NE_P (file, NULL);
	TEST_FILE_EQ (file, "hello world\r\n");
	TEST_FILE_END (file);
	TEST_EQ (fclose (file), 0);

	STOP_UPSTART (upstart_pid);
	TEST_EQ (unsetenv ("UPSTART_CONFDIR"), 0);
	TEST_EQ (unsetenv ("UPSTART_LOGDIR"), 0);
	TEST_DBUS_END (dbus_pid);

	DELETE_FILE (confdir_name, "foo.conf");
	DELETE_FILE (logdir_name, "foo.log");

	TEST_EQ (rmdir (confdir_name), 0);
	TEST_EQ (rmdir (logdir_name), 0);
}


void
test_list_action (void)
{
	pid_t           dbus_pid;
	DBusConnection *server_conn;
	FILE *          output;
	FILE *          errors;
	pid_t           server_pid;
	DBusMessage *   method_call;
	DBusMessage *   reply = NULL;
	const char *    str_value;
	const char *    interface;
	const char *    property;
	DBusMessageIter iter;
	DBusMessageIter subiter;
	DBusMessageIter arrayiter;
	DBusMessageIter dictiter;
	DBusMessageIter prociter;
	DBusMessageIter structiter;
	int32_t         int32_value;
	NihCommand      command;
	char *          args[1];
	int             ret = 0;
	int             status;

	TEST_FUNCTION ("list_action");
	TEST_DBUS (dbus_pid);
	TEST_DBUS_OPEN (server_conn);

	assert (dbus_bus_request_name (server_conn, DBUS_SERVICE_UPSTART,
				       0, NULL)
			== DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER);

	TEST_DBUS_MESSAGE (server_conn, method_call);
	assert (dbus_message_is_signal (method_call, DBUS_INTERFACE_DBUS,
					"NameAcquired"));
	dbus_message_unref (method_call);

	dbus_bus_type = DBUS_BUS_SYSTEM;
	dest_name = DBUS_SERVICE_UPSTART;
	dest_address = DBUS_ADDRESS_UPSTART;

	output = tmpfile ();
	errors = tmpfile ();


	/* Check that the list action makes the GetAllJobs method call
	 * to obtain a list of paths, then for each job calls the
	 * GetAllInstances method call to obtain a list of the instances.
	 * If there are instances, the job name and instance properties are
	 * requested and output; if there are not instances, only the
	 * job name is requested and output.
	 */
	TEST_FEATURE ("with valid reply");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetAllJobs method call on the
			 * manager object, reply with a list of interesting
			 * paths.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetAllJobs"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  DBUS_TYPE_OBJECT_PATH_AS_STRING,
								  &arrayiter);

				str_value = DBUS_PATH_UPSTART "/jobs/frodo";
				dbus_message_iter_append_basic (&arrayiter,
								DBUS_TYPE_OBJECT_PATH,
								&str_value);

				str_value = DBUS_PATH_UPSTART "/jobs/bilbo";
				dbus_message_iter_append_basic (&arrayiter,
								DBUS_TYPE_OBJECT_PATH,
								&str_value);

				str_value = DBUS_PATH_UPSTART "/jobs/drogo";
				dbus_message_iter_append_basic (&arrayiter,
								DBUS_TYPE_OBJECT_PATH,
								&str_value);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAllInstances method call on the
			 * first job object, reply with an empty list.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetAllInstances"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/frodo");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  DBUS_TYPE_OBJECT_PATH_AS_STRING,
								  &arrayiter);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Get call for the name of the
			 * first job, reply with the name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/frodo");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "frodo";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAllInstances method call on the
			 * second job object, reply with a single instance.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetAllInstances"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/bilbo");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  DBUS_TYPE_OBJECT_PATH_AS_STRING,
								  &arrayiter);

				str_value = DBUS_PATH_UPSTART "/jobs/bilbo/_";
				dbus_message_iter_append_basic (&arrayiter,
								DBUS_TYPE_OBJECT_PATH,
								&str_value);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Get call for the name of the
			 * second job, reply with the name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/bilbo");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "bilbo";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAll call for the instance properties,
			 * reply with the properties.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"GetAll"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/bilbo/_");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_VARIANT_AS_STRING
								   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
								  &arrayiter);

				/* Name */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "name";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Goal */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "goal";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "start";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* State */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "state";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "running";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Processes */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "processes";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  (DBUS_TYPE_ARRAY_AS_STRING
								   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &subiter);

				dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
								  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &prociter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "main";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 3648;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_close_container (&subiter, &prociter);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAllInstances method call on the
			 * third job object, reply with a couple of
			 * named instances
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetAllInstances"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/drogo");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  DBUS_TYPE_OBJECT_PATH_AS_STRING,
								  &arrayiter);

				str_value = DBUS_PATH_UPSTART "/jobs/drogo/foo";
				dbus_message_iter_append_basic (&arrayiter,
								DBUS_TYPE_OBJECT_PATH,
								&str_value);

				str_value = DBUS_PATH_UPSTART "/jobs/drogo/bar";
				dbus_message_iter_append_basic (&arrayiter,
								DBUS_TYPE_OBJECT_PATH,
								&str_value);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Get call for the name of the
			 * third job, reply with the name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/drogo");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "drogo";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAll call for the first of its
			 * instances, reply with the properties.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"GetAll"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/drogo/foo");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_VARIANT_AS_STRING
								   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
								  &arrayiter);

				/* Name */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "name";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "foo";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Goal */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "goal";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "stop";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* State */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "state";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "pre-stop";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Processes */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "processes";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  (DBUS_TYPE_ARRAY_AS_STRING
								   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &subiter);

				dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
								  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &prociter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "main";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 6312;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "pre-stop";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 8609;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_close_container (&subiter, &prociter);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Get call for the name of the
			 * third job, reply with the name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/drogo");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "drogo";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAll call for the second of its
			 * instances, reply with its properties.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"GetAll"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/drogo/bar");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_VARIANT_AS_STRING
								   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
								  &arrayiter);

				/* Name */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "name";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "bar";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Goal */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "goal";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "start";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* State */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "state";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "post-stop";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Processes */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "processes";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  (DBUS_TYPE_ARRAY_AS_STRING
								   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &subiter);

				dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
								  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &prociter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "post-stop";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 7465;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_close_container (&subiter, &prociter);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = list_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			/* May have had some output */
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "frodo stop/waiting\n");
		TEST_FILE_EQ (output, "bilbo start/running, process 3648\n");
		TEST_FILE_EQ (output, "drogo (foo) stop/pre-stop, process 6312\n");
		TEST_FILE_EQ (output, "\tpre-stop process 8609\n");
		TEST_FILE_EQ (output, "drogo (bar) start/post-stop, process 7465\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}


	/* Check that an error reply from the GetAllInstances command
	 * is assumed to mean that the job went away, and thus the job
	 * is simply not printed rather than causing the function to end,
	 */
	TEST_FEATURE ("with error reply to GetAllInstances");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetAllJobs method call on the
			 * manager object, reply with a list of interesting
			 * paths.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetAllJobs"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  DBUS_TYPE_OBJECT_PATH_AS_STRING,
								  &arrayiter);

				str_value = DBUS_PATH_UPSTART "/jobs/foo";
				dbus_message_iter_append_basic (&arrayiter,
								DBUS_TYPE_OBJECT_PATH,
								&str_value);

				str_value = DBUS_PATH_UPSTART "/jobs/bar";
				dbus_message_iter_append_basic (&arrayiter,
								DBUS_TYPE_OBJECT_PATH,
								&str_value);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAllInstances method call on the
			 * first job object, reply with an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetAllInstances"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/foo");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAllInstances method call on the
			 * second job object, reply with a single instance.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART_JOB,
								"GetAllInstances"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART "/jobs/bar");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  DBUS_TYPE_OBJECT_PATH_AS_STRING,
								  &arrayiter);

				str_value = DBUS_PATH_UPSTART "/jobs/bar/_";
				dbus_message_iter_append_basic (&arrayiter,
								DBUS_TYPE_OBJECT_PATH,
								&str_value);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the Get call for the name of the
			 * second job, reply with the name.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/bar");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_JOB);
			TEST_EQ_STR (property, "name");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "bar";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			/* Expect the GetAll call for the instance properties,
			 * reply with the properties.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"GetAll"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
				     DBUS_PATH_UPSTART "/jobs/bar/_");

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART_INSTANCE);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
								  (DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_VARIANT_AS_STRING
								   DBUS_DICT_ENTRY_END_CHAR_AS_STRING),
								  &arrayiter);

				/* Name */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "name";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Goal */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "goal";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "start";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* State */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "state";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "running";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				/* Processes */
				dbus_message_iter_open_container (&arrayiter, DBUS_TYPE_DICT_ENTRY,
								  NULL,
								  &dictiter);

				str_value = "processes";
				dbus_message_iter_append_basic (&dictiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_open_container (&dictiter, DBUS_TYPE_VARIANT,
								  (DBUS_TYPE_ARRAY_AS_STRING
								   DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &subiter);

				dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY,
								  (DBUS_STRUCT_BEGIN_CHAR_AS_STRING
								   DBUS_TYPE_STRING_AS_STRING
								   DBUS_TYPE_INT32_AS_STRING
								   DBUS_STRUCT_END_CHAR_AS_STRING),
								  &prociter);

				dbus_message_iter_open_container (&prociter, DBUS_TYPE_STRUCT,
								  NULL,
								  &structiter);

				str_value = "main";
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_STRING,
								&str_value);

				int32_value = 3648;
				dbus_message_iter_append_basic (&structiter, DBUS_TYPE_INT32,
								&int32_value);

				dbus_message_iter_close_container (&prociter, &structiter);

				dbus_message_iter_close_container (&subiter, &prociter);

				dbus_message_iter_close_container (&dictiter, &subiter);

				dbus_message_iter_close_container (&arrayiter, &dictiter);

				dbus_message_iter_close_container (&iter, &arrayiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = list_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			/* May have had some output */
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "bar start/running, process 3648\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}


	/* Check that if an error is received from the GetAllJobs call,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply to GetAllJobs");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the GetAllJobs method call on the
			 * manager object, reply with an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"GetAllJobs"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = list_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	fclose (errors);
	fclose (output);

	TEST_DBUS_CLOSE (server_conn);
	TEST_DBUS_END (dbus_pid);

	dbus_shutdown ();
}


void
test_emit_action (void)
{
	pid_t           dbus_pid;
	DBusConnection *server_conn;
	FILE *          output;
	FILE *          errors;
	pid_t           server_pid;
	DBusMessage *   method_call;
	DBusMessage *   reply = NULL;
	const char *    name_value;
	char **         args_value;
	int             args_elements;
	int             wait_value;
	NihCommand      command;
	char *          args[4];
	int             ret = 0;
	int             status;

	TEST_FUNCTION ("emit_action");
	TEST_DBUS (dbus_pid);
	TEST_DBUS_OPEN (server_conn);

	assert (dbus_bus_request_name (server_conn, DBUS_SERVICE_UPSTART,
				       0, NULL)
			== DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER);

	TEST_DBUS_MESSAGE (server_conn, method_call);
	assert (dbus_message_is_signal (method_call, DBUS_INTERFACE_DBUS,
					"NameAcquired"));
	dbus_message_unref (method_call);

	dbus_bus_type = DBUS_BUS_SYSTEM;
	dest_name = DBUS_SERVICE_UPSTART;
	dest_address = DBUS_ADDRESS_UPSTART;

	output = tmpfile ();
	errors = tmpfile ();


	/* Check that the emit action passes a single argument to the
	 * server in the EmitEvent command as the name of the event,
	 * along with a NULL array for the events.  Make sure that wait
	 * is TRUE by default.
	 */
	TEST_FEATURE ("with single argument");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the EmitEvent method call on the manager
			 * object, make sure the arguments are right and
			 * reply to acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"EmitEvent"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "wibble");

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_TRUE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "wibble";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = emit_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}


	/* Check that additional arguments to the emit action are passed
	 * as entries in the environment argument of the command.
	 */
	TEST_FEATURE ("with multiple arguments");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the EmitEvent method call on the manager
			 * object, make sure the arguments are right and
			 * reply to acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"EmitEvent"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "wibble");

			TEST_EQ (args_elements, 2);
			TEST_EQ_STR (args_value[0], "FOO=foo");
			TEST_EQ_STR (args_value[1], "BAR=bar");
			dbus_free_string_array (args_value);

			TEST_TRUE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "wibble";
		args[1] = "FOO=foo";
		args[2] = "BAR=bar";
		args[3] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = emit_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}


	/* Check that the --no-wait option results in the method call
	 * being made with wait as FALSE.
	 */
	TEST_FEATURE ("with no wait");
	no_wait = TRUE;

	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the EmitEvent method call on the manager
			 * object, make sure the arguments are right and
			 * reply to acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"EmitEvent"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "wibble");

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_FALSE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "wibble";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = emit_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}

	no_wait = FALSE;


	/* Check that if an error is received from the command,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the EmitEvent method call on the manager
			 * object, make sure the arguments are right and
			 * reply with an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"EmitEvent"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &name_value,
							  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &args_value, &args_elements,
							  DBUS_TYPE_BOOLEAN, &wait_value,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (name_value, "wibble");

			TEST_EQ (args_elements, 0);
			dbus_free_string_array (args_value);

			TEST_TRUE (wait_value);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "wibble";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = emit_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	/* Check that a missing argument results in an error being output
	 * to stderr along with a suggestion of help.
	 */
	TEST_FEATURE ("with missing argument");
	TEST_ALLOC_FAIL {
		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = emit_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_EQ (errors, "test: missing event name\n");
		TEST_FILE_EQ (errors, "Try `test --help' for more information.\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);
	}


	fclose (errors);
	fclose (output);

	TEST_DBUS_CLOSE (server_conn);
	TEST_DBUS_END (dbus_pid);

	dbus_shutdown ();
}


void
test_reload_configuration_action (void)
{
	pid_t           dbus_pid;
	DBusConnection *server_conn;
	FILE *          output;
	FILE *          errors;
	pid_t           server_pid;
	DBusMessage *   method_call;
	DBusMessage *   reply = NULL;
	NihCommand      command;
	char *          args[1];
	int             ret = 0;
	int             status;

	TEST_FUNCTION ("reload_configuration_action");
	TEST_DBUS (dbus_pid);
	TEST_DBUS_OPEN (server_conn);

	assert (dbus_bus_request_name (server_conn, DBUS_SERVICE_UPSTART,
				       0, NULL)
			== DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER);

	TEST_DBUS_MESSAGE (server_conn, method_call);
	assert (dbus_message_is_signal (method_call, DBUS_INTERFACE_DBUS,
					"NameAcquired"));
	dbus_message_unref (method_call);

	dbus_bus_type = DBUS_BUS_SYSTEM;
	dest_name = DBUS_SERVICE_UPSTART;
	dest_address = DBUS_ADDRESS_UPSTART;

	output = tmpfile ();
	errors = tmpfile ();


	/* Check that the reload_configuration sends the method call to the
	 * server.
	 */
	TEST_FEATURE ("with command");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the ReloadConfiguration method call for
			 * the manager object, reply to acknowledge.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"ReloadConfiguration"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = reload_configuration_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}


	/* Check that if an error is received from the command,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the ReloadConfiguration method call for
			 * the manager object, reply with an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_UPSTART,
								"ReloadConfiguration"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = reload_configuration_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	fclose (errors);
	fclose (output);

	TEST_DBUS_CLOSE (server_conn);
	TEST_DBUS_END (dbus_pid);

	dbus_shutdown ();
}


void
test_version_action (void)
{
	pid_t           dbus_pid;
	DBusConnection *server_conn;
	FILE *          output;
	FILE *          errors;
	pid_t           server_pid;
	DBusMessage *   method_call;
	const char *    interface;
	const char *    property;
	DBusMessage *   reply = NULL;
	DBusMessageIter iter;
	DBusMessageIter subiter;
	const char *    str_value;
	NihCommand      command;
	char *          args[1];
	int             ret = 0;
	int             status;

	TEST_FUNCTION ("version_action");
	TEST_DBUS (dbus_pid);
	TEST_DBUS_OPEN (server_conn);

	assert (dbus_bus_request_name (server_conn, DBUS_SERVICE_UPSTART,
				       0, NULL)
			== DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER);

	TEST_DBUS_MESSAGE (server_conn, method_call);
	assert (dbus_message_is_signal (method_call, DBUS_INTERFACE_DBUS,
					"NameAcquired"));
	dbus_message_unref (method_call);

	dbus_bus_type = DBUS_BUS_SYSTEM;
	dest_name = DBUS_SERVICE_UPSTART;
	dest_address = DBUS_ADDRESS_UPSTART;

	output = tmpfile ();
	errors = tmpfile ();


	/* Check that the version action queries the server for its
	 * version property, and prints the result to standard output.
	 */
	TEST_FEATURE ("with valid reply");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Get call for the version property,
			 * reply with the string we want printed.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART);
			TEST_EQ_STR (property, "version");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "init (upstart 1.0.0)";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = version_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "init (upstart 1.0.0)\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}


	/* Check that if an error is received from the query command,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with error reply");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Get call for the version property,
			 * reply with an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART);
			TEST_EQ_STR (property, "version");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = version_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	fclose (errors);
	fclose (output);

	TEST_DBUS_CLOSE (server_conn);
	TEST_DBUS_END (dbus_pid);

	dbus_shutdown ();
}


void
test_log_priority_action (void)
{
	pid_t           dbus_pid;
	DBusConnection *server_conn;
	FILE *          output;
	FILE *          errors;
	pid_t           server_pid;
	DBusMessage *   method_call;
	const char *    interface;
	const char *    property;
	DBusMessage *   reply = NULL;
	DBusMessageIter iter;
	DBusMessageIter subiter;
	const char *    str_value;
	char *          signature;
	NihCommand      command;
	char *          args[2];
	int             ret = 0;
	int             status;

	TEST_FUNCTION ("log_priority_action");
	TEST_DBUS (dbus_pid);
	TEST_DBUS_OPEN (server_conn);

	assert (dbus_bus_request_name (server_conn, DBUS_SERVICE_UPSTART,
				       0, NULL)
			== DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER);

	TEST_DBUS_MESSAGE (server_conn, method_call);
	assert (dbus_message_is_signal (method_call, DBUS_INTERFACE_DBUS,
					"NameAcquired"));
	dbus_message_unref (method_call);

	dbus_bus_type = DBUS_BUS_SYSTEM;
	dest_name = DBUS_SERVICE_UPSTART;
	dest_address = DBUS_ADDRESS_UPSTART;

	output = tmpfile ();
	errors = tmpfile ();


	/* Check that, when called without arguments, the log_priority action
	 * queries the server for its log_priority property and prints the
	 * result to standard output.
	 */
	TEST_FEATURE ("with no arguments");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Get call for the log_priority property,
			 * reply with the string we want printed.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART);
			TEST_EQ_STR (property, "log_priority");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);

				dbus_message_iter_init_append (reply, &iter);

				dbus_message_iter_open_container (&iter, DBUS_TYPE_VARIANT,
								  DBUS_TYPE_STRING_AS_STRING,
								  &subiter);

				str_value = "message";
				dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING,
								&str_value);

				dbus_message_iter_close_container (&iter, &subiter);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = log_priority_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_EQ (output, "message\n");
		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}



	/* Check that, when called with an argument, the log_priority action
	 * passes that to the server to set its log_priority property.
	 */
	TEST_FEATURE ("with argument");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Set call for the log_priority property,
			 * send an acknowledgement reply.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Set"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);
			TEST_EQ_STR (dbus_message_get_signature (method_call),
				     (DBUS_TYPE_STRING_AS_STRING
				      DBUS_TYPE_STRING_AS_STRING
				      DBUS_TYPE_VARIANT_AS_STRING));

			dbus_message_iter_init (method_call, &iter);

			dbus_message_iter_get_basic (&iter, &interface);
			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART);

			dbus_message_iter_next (&iter);

			dbus_message_iter_get_basic (&iter, &property);
			TEST_EQ_STR (property, "log_priority");

			dbus_message_iter_next (&iter);
			dbus_message_iter_recurse (&iter, &subiter);

			signature = dbus_message_iter_get_signature (&subiter);
			TEST_EQ_STR (signature, DBUS_TYPE_STRING_AS_STRING);
			dbus_free (signature);

			dbus_message_iter_get_basic (&subiter, &str_value);
			TEST_EQ_STR (str_value, "info");


			TEST_ALLOC_SAFE {
				reply = dbus_message_new_method_return (method_call);
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "info";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = log_priority_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		if (test_alloc_failed
		    && (ret != 0)) {
			TEST_FILE_END (output);
			TEST_FILE_RESET (output);

			TEST_FILE_EQ (errors, "test: Cannot allocate memory\n");
			TEST_FILE_END (errors);
			TEST_FILE_RESET (errors);

			kill (server_pid, SIGTERM);
			waitpid (server_pid, NULL, 0);
			continue;
		}

		TEST_EQ (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		waitpid (server_pid, &status, 0);
		TEST_TRUE (WIFEXITED (status));
		TEST_EQ (WEXITSTATUS (status), 0);
	}


	/* Check that if an error is received from the query command,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with no arguments and error reply");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Get call for the log_priority property,
			 * reply with an error.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Get"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);

			TEST_TRUE (dbus_message_get_args (method_call, NULL,
							  DBUS_TYPE_STRING, &interface,
							  DBUS_TYPE_STRING, &property,
							  DBUS_TYPE_INVALID));

			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART);
			TEST_EQ_STR (property, "log_priority");

			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = log_priority_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	/* Check that if an error is received from the query command,
	 * the message attached is printed to standard error and the
	 * command exits.
	 */
	TEST_FEATURE ("with argument and error reply");
	TEST_ALLOC_FAIL {
		TEST_CHILD (server_pid) {
			/* Expect the Set call for the log_priority property,
			 * send an error back.
			 */
			TEST_DBUS_MESSAGE (server_conn, method_call);

			TEST_TRUE (dbus_message_is_method_call (method_call,
								DBUS_INTERFACE_PROPERTIES,
								"Set"));

			TEST_EQ_STR (dbus_message_get_path (method_call),
							    DBUS_PATH_UPSTART);
			TEST_EQ_STR (dbus_message_get_signature (method_call),
				     (DBUS_TYPE_STRING_AS_STRING
				      DBUS_TYPE_STRING_AS_STRING
				      DBUS_TYPE_VARIANT_AS_STRING));

			dbus_message_iter_init (method_call, &iter);

			dbus_message_iter_get_basic (&iter, &interface);
			TEST_EQ_STR (interface, DBUS_INTERFACE_UPSTART);

			dbus_message_iter_next (&iter);

			dbus_message_iter_get_basic (&iter, &property);
			TEST_EQ_STR (property, "log_priority");

			dbus_message_iter_next (&iter);
			dbus_message_iter_recurse (&iter, &subiter);

			signature = dbus_message_iter_get_signature (&subiter);
			TEST_EQ_STR (signature, DBUS_TYPE_STRING_AS_STRING);
			dbus_free (signature);

			dbus_message_iter_get_basic (&subiter, &str_value);
			TEST_EQ_STR (str_value, "info");


			TEST_ALLOC_SAFE {
				reply = dbus_message_new_error (method_call,
								DBUS_ERROR_UNKNOWN_METHOD,
								"Unknown method");
			}

			dbus_connection_send (server_conn, reply, NULL);
			dbus_connection_flush (server_conn);

			dbus_message_unref (method_call);
			dbus_message_unref (reply);

			TEST_DBUS_CLOSE (server_conn);

			dbus_shutdown ();

			exit (0);
		}

		memset (&command, 0, sizeof command);

		args[0] = "info";
		args[1] = NULL;

		TEST_DIVERT_STDOUT (output) {
			TEST_DIVERT_STDERR (errors) {
				ret = log_priority_action (&command, args);
			}
		}
		rewind (output);
		rewind (errors);

		TEST_GT (ret, 0);

		TEST_FILE_END (output);
		TEST_FILE_RESET (output);

		TEST_FILE_MATCH (errors, "test: *\n");
		TEST_FILE_END (errors);
		TEST_FILE_RESET (errors);

		kill (server_pid, SIGTERM);
		waitpid (server_pid, NULL, 0);
	}


	fclose (errors);
	fclose (output);

	TEST_DBUS_CLOSE (server_conn);
	TEST_DBUS_END (dbus_pid);

	dbus_shutdown ();
}


void
test_usage (void)
{
	char             dirname[PATH_MAX];
	nih_local char  *cmd = NULL;
	pid_t            upstart_pid = 0;
	pid_t            dbus_pid    = 0;
	char           **output;
	size_t           lines;
	FILE            *out;
	FILE            *err;
	NihCommand       command;
	char            *args[2];
	int              ret = 0;			  

	TEST_TRUE (getenv ("XDG_RUNTIME_DIR"));

	TEST_GROUP ("usage");

        TEST_FILENAME (dirname);
        TEST_EQ (mkdir (dirname, 0755), 0);

	/* Use the "secret" interface */
	TEST_EQ (setenv ("UPSTART_CONFDIR", dirname, 1), 0);

	TEST_DBUS (dbus_pid);
	START_UPSTART (upstart_pid, FALSE);

	TEST_FEATURE ("no usage");
	CREATE_FILE (dirname, "foo.conf",
			"author \"foo\"\n"
			"description \"wibble\"");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s usage foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], "Usage: ");
	TEST_EQ (lines, 1);
	nih_free (output);

	DELETE_FILE (dirname, "foo.conf");

	/*******************************************************************/

	TEST_FEATURE ("with usage");

	CREATE_FILE (dirname, "foo.conf",
			"usage \"this is usage\"");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s usage foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ_STR (output[0], "Usage: this is usage");
	TEST_EQ (lines, 1);
	nih_free (output);

	DELETE_FILE (dirname, "foo.conf");

	/*******************************************************************/

	TEST_FEATURE ("failed status with usage");

	CREATE_FILE (dirname, "foo.conf",
			"instance $FOO\n"
			"usage \"this is usage\"");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	memset (&command, 0, sizeof command);
	args[0] = "foo";
	args[1] = NULL;

	out = tmpfile ();
	err = tmpfile ();

	TEST_NE_P (out, NULL);
	TEST_NE_P (err, NULL);

	TEST_DIVERT_STDOUT (out) {
		TEST_DIVERT_STDERR (err) {
			ret = status_action (&command, args);
		}
	}
	rewind (out);
	rewind (err);

	TEST_GT (ret, 0);

	TEST_FILE_END (out);
	TEST_FILE_RESET (out);

	TEST_FILE_EQ (err, "test: Unknown parameter: FOO\n");
	TEST_FILE_EQ (err, "Usage: this is usage\n");
	TEST_FILE_END (err);
	TEST_FILE_RESET (err);

	assert0 (fclose (out));
	assert0 (fclose (err));

	DELETE_FILE (dirname, "foo.conf");

	STOP_UPSTART (upstart_pid);
	TEST_EQ (unsetenv ("UPSTART_CONFDIR"), 0);
	TEST_DBUS_END (dbus_pid);

	assert0 (rmdir (dirname));
}

void
test_default_job_env (const char *confdir, const char *logdir,
		      pid_t upstart_pid, pid_t dbus_pid)
{
	nih_local char  *cmd = NULL;
	char           **output;
	nih_local char  *logfile = NULL;
	size_t           line_count;
	FILE            *fi;

	assert (confdir);
	assert (logdir);
	assert (upstart_pid);
	assert (dbus_pid);

	cmd = nih_sprintf (NULL, "%s reset-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	assert0 (line_count);

	/*******************************************************************/
	TEST_FEATURE ("ensure list-env returns default environment");

	cmd = nih_sprintf (NULL, "%s list-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	TEST_GE (line_count, 2);
	TEST_STR_ARRAY_CONTAINS (output, "PATH=*");
	TEST_STR_ARRAY_CONTAINS (output, "TERM=*");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("ensure 'list-env --global' returns default environment");

	cmd = nih_sprintf (NULL, "%s list-env --global 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	TEST_GE (line_count, 2);
	TEST_STR_ARRAY_CONTAINS (output, "PATH=*");
	TEST_STR_ARRAY_CONTAINS (output, "TERM=*");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("ensure get-env returns expected TERM variable");

	cmd = nih_sprintf (NULL, "%s get-env TERM 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	TEST_EQ_STR (output[0], getenv ("TERM"));
	TEST_EQ (line_count, 1);
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("ensure 'get-env --global' returns expected TERM variable");

	cmd = nih_sprintf (NULL, "%s get-env --global TERM 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	TEST_EQ_STR (output[0], getenv ("TERM"));
	TEST_EQ (line_count, 1);
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("ensure get-env returns expected PATH variable");

	cmd = nih_sprintf (NULL, "%s get-env PATH 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], getenv ("PATH"));
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("ensure 'get-env --global' returns expected PATH variable");

	cmd = nih_sprintf (NULL, "%s get-env --global PATH 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], getenv ("PATH"));
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("ensure job gets given default environment");

	CREATE_FILE (confdir, "foo.conf", "exec env");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s start foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	nih_free (output);

	logfile = NIH_MUST (nih_sprintf (NULL, "%s/%s",
				logdir,
				"foo.log"));

	WAIT_FOR_FILE (logfile);

	fi = fopen (logfile, "r");
	TEST_NE_P (fi, NULL);
	TEST_FILE_CONTAINS (fi, "PATH=*");
	TEST_FILE_CONTAINS (fi, "TERM=*");

	/* asterisk required to match '\r\n' */
	TEST_FILE_CONTAINS (fi, "UPSTART_JOB=foo*");
	TEST_FILE_CONTAINS (fi, "UPSTART_INSTANCE=*");
	TEST_FILE_CONTAINS (fi, "UPSTART_SESSION=*");
	fclose (fi);

	DELETE_FILE (confdir, "foo.conf");
	TEST_EQ (unlink (logfile), 0);

	/*******************************************************************/
	TEST_FEATURE ("ensure invalid query shows unknown variable");

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			"foo-bar-baz");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: foo-bar-baz");

	/*******************************************************************/
}

void
clear_job_env (void)
{
	nih_local char  *cmd = NULL;
	char           **output;
	nih_local char  *logfile = NULL;
	size_t           line_count;
	size_t           i;

	cmd = nih_sprintf (NULL, "%s list-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	TEST_GT (line_count, 0);

	/* Remove all variables from the job environment table */
	for (i = 0; i < line_count; i++) {
		char    **output2;
		size_t    line_count2;
		char      *p;
		nih_local char *name = NULL;

		/* Every variable is expected to be returned with a
		 * delimiter, even if one was not specified when
		 * variable was set.
		 */
		p = strchr (output[i], '=');
		TEST_NE_P (p, NULL);

		name = NIH_MUST (nih_strdup (NULL, ""));
		TEST_TRUE (nih_strncat (&name, NULL, output[i], p - output[i]));

		/* Clear the variable */
		cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name);
		TEST_NE_P (cmd, NULL);
		RUN_COMMAND (NULL, cmd, &output2, &line_count2);
		TEST_EQ (line_count2, 0);
	}

	nih_free (output);

	/* No variables should remain */
	cmd = nih_sprintf (NULL, "%s list-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	assert0 (line_count);
}

/**
 * Clear the job process table, then reset it back to defaults.
 **/
void
test_clear_job_env (const char *confdir, const char *logdir,
		      pid_t upstart_pid, pid_t dbus_pid)
{
	nih_local char  *cmd = NULL;
	char           **output;
	nih_local char  *logfile = NULL;
	nih_local char  *contents = NULL;
	size_t           line_count;
	FILE            *fi;

	assert (confdir);
	assert (logdir);
	assert (upstart_pid);
	assert (dbus_pid);

	clear_job_env ();

	/* ensure get-env tolerates empty environment */
	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			"foo");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: foo");

	/* ensure unset-env tolerates empty environment */
	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), "foo");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: foo");

	/* ensure unset-env (multiple variables) tolerates empty environment */
	cmd = nih_sprintf (NULL, "%s unset-env %s %s 2>&1", get_initctl (), "foo", "bar");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	/* Although 2 variables have been specified, since neither is
	 * set, we only expect 1 error for the first variable.
	 */
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: foo");

	/*******************************************************************/
	TEST_FEATURE ("ensure job runs in empty environment");

	/* we have to cheat by setting PATH to allow 'env' to be found.
	 * Add a silly entry at the end so we can check our version has
	 * been set.
	 */
	contents = nih_sprintf (NULL,
			"env PATH=%s\n"
			"exec env", TEST_INITCTL_DEFAULT_PATH);
	TEST_NE_P (contents, NULL);

	CREATE_FILE (confdir, "empty-env.conf", contents);

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s start empty-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	nih_free (output);

	logfile = NIH_MUST (nih_sprintf (NULL, "%s/%s",
				logdir,
				"empty-env.log"));

	WAIT_FOR_FILE (logfile);

	fi = fopen (logfile, "r");
	TEST_NE_P (fi, NULL);

	/* Ensure it looks like our PATH */
	TEST_FILE_MATCH (fi, "PATH=*/wibble*");

	/* Although the environment is empty (except for PATH now), we
	 * still expect the special variables to be set.
	 */
	TEST_FILE_MATCH (fi, "UPSTART_JOB=empty-env*");
	TEST_FILE_MATCH (fi, "UPSTART_INSTANCE=*");
	TEST_FILE_MATCH (fi, "UPSTART_SESSION=*");
	TEST_FILE_END (fi);
	fclose (fi);

	DELETE_FILE (confdir, "empty-env.conf");
	TEST_EQ (unlink (logfile), 0);

	/* reset environment */
	cmd = nih_sprintf (NULL, "%s reset-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	assert0 (line_count);

	/* re-check */
	test_default_job_env (confdir, logdir, upstart_pid, dbus_pid);
}

void
test_modified_job_env (const char *confdir, const char *logdir,
		pid_t upstart_pid, pid_t dbus_pid)
{
	nih_local char  *cmd = NULL;
	nih_local char  *name = NULL;
	nih_local char  *value = NULL;
	nih_local char  *name2 = NULL;
	nih_local char  *value2 = NULL;
	nih_local char  *name3 = NULL;
	nih_local char  *value3 = NULL;
	nih_local char  *name4 = NULL;
	nih_local char  *value4 = NULL;
	char           **output;
	nih_local char  *logfile = NULL;
	size_t           line_count;
	FILE            *fi;

	assert (confdir);
	assert (logdir);
	assert (upstart_pid);
	assert (dbus_pid);

	/*******************************************************************/
	TEST_FEATURE ("call reset-env with default environment");

	cmd = nih_sprintf (NULL, "%s reset-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);
	nih_free (output);

	/* Ensure nothing changed */
	test_default_job_env (confdir, logdir, upstart_pid, dbus_pid);

	test_clear_job_env (confdir, logdir, upstart_pid, dbus_pid);

	/*******************************************************************/
	TEST_FEATURE ("set-env in 'name=value' form");

	name = NIH_MUST (nih_strdup (NULL, "foo"));
	value = NIH_MUST (nih_strdup (NULL, "bar"));
	name2 = NIH_MUST (nih_strdup (NULL, "baz"));
	value2 = NIH_MUST (nih_strdup (NULL, "qux"));

	cmd = nih_sprintf (NULL, "%s set-env %s=%s 2>&1", get_initctl (),
			name, value);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s set-env %s=%s 2>&1", get_initctl (),
			name2, value2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], value);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], value2);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s unset-env %s %s 2>&1", get_initctl (), name, name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: foo");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: baz");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("multiple set-env in 'name=value' form");

	name = NIH_MUST (nih_strdup (NULL, "foo"));
	value = NIH_MUST (nih_strdup (NULL, "bar"));
	name2 = NIH_MUST (nih_strdup (NULL, "baz"));
	value2 = NIH_MUST (nih_strdup (NULL, "qux"));

	cmd = nih_sprintf (NULL, "%s set-env %s=%s %s=%s 2>&1", get_initctl (),
			name, value, name2, value2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], value);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], value2);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s unset-env %s %s 2>&1", get_initctl (), name, name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: foo");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: baz");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("set-env in 'name=' form");

	name = NIH_MUST (nih_strdup (NULL, "foo"));

	cmd = nih_sprintf (NULL, "%s set-env %s= 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	TEST_EQ (line_count, 1);

	/* nul string value expected if none specified when set */
	TEST_EQ_STR (output[0], "");

	nih_free (output);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: foo");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("multiple set-env in 'name=' form");

	name = NIH_MUST (nih_strdup (NULL, "foo"));
	name2 = NIH_MUST (nih_strdup (NULL, "baz"));

	cmd = nih_sprintf (NULL, "%s set-env %s= %s= 2>&1", get_initctl (),
			name, name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);

	/* nul string value expected if none specified when set */
	TEST_EQ_STR (output[0], "");

	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);

	/* nul string value expected if none specified when set */
	TEST_EQ_STR (output[0], "");

	nih_free (output);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: foo");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: baz");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("set-env in 'name' form");

	name = NIH_MUST (nih_strdup (NULL, "foo"));

	cmd = nih_sprintf (NULL, "%s set-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	TEST_EQ (line_count, 1);

	/* nul string value expected if none specified when set */
	TEST_EQ_STR (output[0], "");

	nih_free (output);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: foo");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("multiple set-env in 'name' form");

	name = NIH_MUST (nih_strdup (NULL, "foo"));
	name2 = NIH_MUST (nih_strdup (NULL, "baz"));

	cmd = nih_sprintf (NULL, "%s set-env %s %s 2>&1", get_initctl (),
			name, name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	TEST_EQ (line_count, 1);

	/* nul string value expected if none specified when set */
	TEST_EQ_STR (output[0], "");

	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	TEST_EQ (line_count, 1);

	/* nul string value expected if none specified when set */
	TEST_EQ_STR (output[0], "");

	nih_free (output);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: foo");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: baz");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("set-env for already set variable");

	name = NIH_MUST (nih_strdup (NULL, "foo"));
	value = NIH_MUST (nih_strdup (NULL, "bar"));

	/* set it */
	cmd = nih_sprintf (NULL, "%s set-env %s=%s 2>&1", get_initctl (),
			name, value);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	/* check it */
	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);

	TEST_EQ_STR (output[0], value);
	nih_free (output);

	/* set it again */
	cmd = nih_sprintf (NULL, "%s set-env %s=%s 2>&1", get_initctl (),
			name, value);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	/* check it again */
	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);

	TEST_EQ_STR (output[0], value);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: foo");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("set-env for multiple already set variables");

	name = NIH_MUST (nih_strdup (NULL, "foo"));
	value = NIH_MUST (nih_strdup (NULL, "bar"));
	name2 = NIH_MUST (nih_strdup (NULL, "baz"));
	value2 = NIH_MUST (nih_strdup (NULL, "qux"));

	/* set them */
	cmd = nih_sprintf (NULL, "%s set-env %s=%s %s=%s 2>&1", get_initctl (),
			name, value, name2, value2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	/* check them */
	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);

	TEST_EQ_STR (output[0], value);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);

	TEST_EQ_STR (output[0], value2);
	nih_free (output);

	/* set them again */
	cmd = nih_sprintf (NULL, "%s set-env %s=%s %s=%s 2>&1", get_initctl (),
			name, value, name2, value2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	/* check again */
	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);

	TEST_EQ_STR (output[0], value);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);

	TEST_EQ_STR (output[0], value2);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: foo");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: baz");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("set-env with multiple variables, some already set");

	name = NIH_MUST (nih_strdup (NULL, "foo"));
	value = NIH_MUST (nih_strdup (NULL, "bar"));
	name2 = NIH_MUST (nih_strdup (NULL, "baz"));
	value2 = NIH_MUST (nih_strdup (NULL, "qux"));
	name3 = NIH_MUST (nih_strdup (NULL, "hello"));
	value3 = NIH_MUST (nih_strdup (NULL, "world"));
	name4 = NIH_MUST (nih_strdup (NULL, "bonjour"));
	value4 = NIH_MUST (nih_strdup (NULL, "tout le monde"));

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name3);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: hello");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name4);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: bonjour");
	nih_free (output);

	/* set 2 variables initially */
	cmd = nih_sprintf (NULL, "%s set-env %s='%s' %s='%s' 2>&1", get_initctl (),
			name3, value3, name4, value4);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	/* check them */
	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name3);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);

	TEST_EQ_STR (output[0], value3);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name4);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);

	TEST_EQ_STR (output[0], value4);
	nih_free (output);

	/* set them all */
	cmd = nih_sprintf (NULL, "%s set-env %s='%s' %s='%s' %s='%s' %s='%s' 2>&1", get_initctl (),
			name, value, name3, value3, name2, value2, name4, value4);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	/* check again */
	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], value);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], value2);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name3);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], value3);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name4);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], value4);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name3);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name4);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: foo");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: baz");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name3);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: hello");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name4);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: bonjour");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("set-env with multiple variables in different forms");

	name = NIH_MUST (nih_strdup (NULL, "foo"));
	value = NIH_MUST (nih_strdup (NULL, "bar"));
	name2 = NIH_MUST (nih_strdup (NULL, "baz"));
	value2 = NIH_MUST (nih_strdup (NULL, "qux"));

	name3 = NIH_MUST (nih_strdup (NULL, "name-equals"));
	name4 = NIH_MUST (nih_strdup (NULL, "just-name"));

	/* set them all */
	cmd = nih_sprintf (NULL, "%s set-env %s='%s' %s= %s %s='%s' 2>&1", get_initctl (),
			name, value, name3, name4, name2, value2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], value);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], value2);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name3);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);

	/* nul string value expected if none specified when set */
	TEST_EQ_STR (output[0], "");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name4);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);

	/* nul string value expected if none specified when set */
	TEST_EQ_STR (output[0], "");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name3);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name4);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: foo");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: baz");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name3);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: name-equals");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name4);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: just-name");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("set-env --retain");

	name = NIH_MUST (nih_strdup (NULL, "foo"));
	value = NIH_MUST (nih_strdup (NULL, "bar"));

	/* set it */
	cmd = nih_sprintf (NULL, "%s set-env %s=%s 2>&1", get_initctl (),
			name, value);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	/* check it */
	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);

	TEST_EQ_STR (output[0], value);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s set-env --retain %s=%s 2>&1",
			get_initctl (), name, "HELLO");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	/* check that value did *NOT* change */
	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], value);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: foo");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("set-env --retain with multiple variables, some already set");

	name = NIH_MUST (nih_strdup (NULL, "foo"));
	value = NIH_MUST (nih_strdup (NULL, "bar"));
	name3 = NIH_MUST (nih_strdup (NULL, "hello"));
	value3 = NIH_MUST (nih_strdup (NULL, "world"));
	name4 = NIH_MUST (nih_strdup (NULL, "bonjour"));
	value4 = NIH_MUST (nih_strdup (NULL, "tout le monde"));

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name3);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: hello");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name4);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: bonjour");
	nih_free (output);

	/* set 2 variables initially */
	cmd = nih_sprintf (NULL, "%s set-env %s='%s' %s='%s' 2>&1", get_initctl (),
			name3, value3, name4, value4);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	/* check them */
	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name3);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);

	TEST_EQ_STR (output[0], value3);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name4);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);

	TEST_EQ_STR (output[0], value4);
	nih_free (output);

	/* set them all */
	cmd = nih_sprintf (NULL, "%s set-env --retain %s='%s' %s='%s' %s='%s' %s='%s' 2>&1",
			get_initctl (), name, value, name3, "AAAA", name2, value2, name4, "BBBB");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	/* check that the original values did *NOT* change */
	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name3);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], value3);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name4);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], value4);
	nih_free (output);

	/* Check that the initially-not set variables were set */
	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], value);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], value2);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name3);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name4);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: foo");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: baz");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name3);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: hello");
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name4);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: bonjour");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("set-env with space within value and trailing tab");

	name = NIH_MUST (nih_strdup (NULL, "foo"));
	value = NIH_MUST (nih_sprintf (NULL, "space tab\t"));

	cmd = nih_sprintf (NULL, "%s set-env %s='%s' 2>&1", get_initctl (),
			name, value);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], value);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s get-env %s 2>&1", get_initctl (),
			name);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	TEST_EQ_STR (output[0], "initctl: No such variable: foo");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("list-env output order");

	clear_job_env ();

	cmd = nih_sprintf (NULL, "%s set-env %s='%s' 2>&1", get_initctl (),
			"zygote", "cell");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s set-env %s='%s' 2>&1", get_initctl (),
			"median", "middle");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s set-env %s='%s' 2>&1", get_initctl (),
			"aardvark", "mammal");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s list-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	TEST_EQ_STR (output[0], "aardvark=mammal");
	TEST_EQ_STR (output[1], "median=middle");
	TEST_EQ_STR (output[2], "zygote=cell");
	TEST_EQ (line_count, 3);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), "aardvark");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s list-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	TEST_EQ_STR (output[0], "median=middle");
	TEST_EQ_STR (output[1], "zygote=cell");
	TEST_EQ (line_count, 2);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s unset-env %s 2>&1", get_initctl (), "zygote");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s list-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	TEST_EQ_STR (output[0], "median=middle");
	TEST_EQ (line_count, 1);
	nih_free (output);

	/* re-add */
	cmd = nih_sprintf (NULL, "%s set-env %s='%s' 2>&1", get_initctl (),
			"aardvark", "mammal");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s set-env %s='%s' 2>&1", get_initctl (),
			"zygote", "cell");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s list-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	TEST_EQ_STR (output[0], "aardvark=mammal");
	TEST_EQ_STR (output[1], "median=middle");
	TEST_EQ_STR (output[2], "zygote=cell");
	TEST_EQ (line_count, 3);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s reset-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	assert0 (line_count);

	/*******************************************************************/
	TEST_FEATURE ("ensure job runs in modified environment");

	cmd = nih_sprintf (NULL, "%s set-env %s='%s' 2>&1", get_initctl (),
			"aardvark", "mammal");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s set-env %s='%s' 2>&1", get_initctl (),
			"FOO", "BAR");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	cmd = nih_sprintf (NULL, "%s set-env %s='%s' 2>&1", get_initctl (),
			"_________", "_________");
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);

	CREATE_FILE (confdir, "modified-env.conf", "exec env");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s start modified-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	nih_free (output);

	logfile = NIH_MUST (nih_sprintf (NULL, "%s/%s",
				logdir,
				"modified-env.log"));

	WAIT_FOR_FILE (logfile);

	fi = fopen (logfile, "r");
	TEST_NE_P (fi, NULL);

	/* defaults */
	TEST_FILE_MATCH (fi, "PATH=*");
	TEST_FILE_MATCH (fi, "TERM=*");

	/* variables we added */
	TEST_FILE_MATCH (fi, "aardvark=mammal*");
	TEST_FILE_MATCH (fi, "FOO=BAR*");
	TEST_FILE_MATCH (fi, "_________=_________*");

	/* special vars */
	TEST_FILE_MATCH (fi, "UPSTART_JOB=modified-env*");
	TEST_FILE_MATCH (fi, "UPSTART_INSTANCE=*");
	TEST_FILE_MATCH (fi, "UPSTART_SESSION=*");

	TEST_FILE_END (fi);
	fclose (fi);

	DELETE_FILE (confdir, "modified-env.conf");
	TEST_EQ (unlink (logfile), 0);

	/* reset environment */
	cmd = nih_sprintf (NULL, "%s reset-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	assert0 (line_count);

	/*******************************************************************/
}

void
test_job_env_invalid_args (const char *confdir, const char *logdir,
		pid_t upstart_pid, pid_t dbus_pid)
{
	nih_local char  *cmd = NULL;
	nih_local char  *name = NULL;
	nih_local char  *value = NULL;
	char           **output;
	size_t           line_count;

	assert (confdir);
	assert (logdir);
	assert (upstart_pid);
	assert (dbus_pid);

	/*******************************************************************/
	TEST_FEATURE ("call get-env without specifying a variable");

	cmd = nih_sprintf (NULL, "%s get-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 2);
	TEST_EQ_STR (output[0], "initctl: missing variable name");
	TEST_EQ_STR (output[1], "Try `initctl --help\' for more information.");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("call set-env without specifying a variable");

	cmd = nih_sprintf (NULL, "%s set-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 2);
	TEST_EQ_STR (output[0], "initctl: missing variable value");
	TEST_EQ_STR (output[1], "Try `initctl --help\' for more information.");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("call unset-env without specifying a variable");

	cmd = nih_sprintf (NULL, "%s unset-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 2);
	TEST_EQ_STR (output[0], "initctl: missing variable name");
	TEST_EQ_STR (output[1], "Try `initctl --help\' for more information.");
	nih_free (output);

	/*******************************************************************/
}

void
test_global_and_local_job_env (const char *confdir, const char *logdir,
		pid_t upstart_pid, pid_t dbus_pid)
{
	nih_local char  *cmd = NULL;
	nih_local char  *name = NULL;
	nih_local char  *value = NULL;
	nih_local char  *logfile = NULL;
	nih_local char  *contents = NULL;
	char           **output;
	size_t           line_count;
	FILE            *fi;

	assert (confdir);
	assert (logdir);
	assert (upstart_pid);
	assert (dbus_pid);

	/*******************************************************************/
	TEST_FEATURE ("ensure pre-start can inject variable into main process");

	contents = nih_sprintf (NULL, 
			"pre-start exec %s set-env hello=world\n"
			"exec %s list-env\n",
			get_initctl (), get_initctl ());

	TEST_NE_P (contents, NULL);

	CREATE_FILE (confdir, "foo.conf", contents);

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s start foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);

	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	nih_free (output);

	logfile = NIH_MUST (nih_sprintf (NULL, "%s/%s",
				logdir,
				"foo.log"));

	WAIT_FOR_FILE (logfile);

	fi = fopen (logfile, "r");
	TEST_FILE_CONTAINS (fi, "hello=world*");
	TEST_NE_P (fi, NULL);

	fclose (fi);

	TEST_EQ (unlink (logfile), 0);
	DELETE_FILE (confdir, "foo.conf");

	/*******************************************************************/
	TEST_FEATURE ("ensure 'set-env --global' can inject a variable into main process");

	cmd = nih_sprintf (NULL, "%s list-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	/* ensure variable not set initially */
	TEST_EQ (line_count, 2);
	TEST_STR_MATCH (output[0], "PATH=*");
	TEST_STR_MATCH (output[1], "TERM=*");
	nih_free (output);

	contents = nih_sprintf (NULL, 
			"script\n"
			"  %s set-env --global hello=world\n"
			"  %s get-env hello\n"
			"end script",
			get_initctl (), get_initctl ());
	TEST_NE_P (contents, NULL);

	CREATE_FILE (confdir, "foo.conf", contents);

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s start foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 1);
	nih_free (output);

	logfile = NIH_MUST (nih_sprintf (NULL, "%s/%s",
				logdir,
				"foo.log"));

	WAIT_FOR_FILE (logfile);

	fi = fopen (logfile, "r");
	TEST_NE_P (fi, NULL);

	/* we don't expect output from either set-env or get-env
	 * (since 'hello' variable should not be set).
	 */
	TEST_FILE_MATCH (fi, "world*\n");
	TEST_FILE_END (fi);
	fclose (fi);

	TEST_EQ (unlink (logfile), 0);
	DELETE_FILE (confdir, "foo.conf");

	/* Create a new job */
	contents = nih_sprintf (NULL, "exec %s list-env", get_initctl ());
	TEST_NE_P (contents, NULL);

	CREATE_FILE (confdir, "bar.conf", contents);

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	TEST_EQ (line_count, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s start bar 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	nih_free (output);

	logfile = NIH_MUST (nih_sprintf (NULL, "%s/%s",
				logdir,
				"bar.log"));

	WAIT_FOR_FILE (logfile);

	fi = fopen (logfile, "r");
	TEST_NE_P (fi, NULL);

	/* Since foo.conf modified the global table, a subsequent job
	 * should pick up the change.
	 */
	TEST_FILE_CONTAINS (fi, "hello=world*");

	fclose (fi);

	cmd = nih_sprintf (NULL, "%s list-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	/* ensure variable still returned by list-env */
	TEST_GT (line_count, 2);
	TEST_STR_ARRAY_CONTAINS (output, "hello=world");
	nih_free (output);

	/* reset environment */
	cmd = nih_sprintf (NULL, "%s reset-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);
	assert0 (line_count);

	cmd = nih_sprintf (NULL, "%s list-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &line_count);

	/* ensure variable no longer set */
	TEST_GT (line_count, 0);
	TEST_STR_ARRAY_NOT_CONTAINS (output, "hello=world");
	nih_free (output);

	assert0 (unlink (logfile));
	DELETE_FILE (confdir, "bar.conf");

	/*******************************************************************/
}

void
test_no_inherit_job_env (const char *runtimedir, const char *confdir, const char *logdir)
{
	nih_local char  *cmd = NULL;
	char           **output;
	size_t           lines;
	pid_t            upstart_pid = 0;
	char            *extra[] = { "--no-inherit-env", NULL };
	nih_local char  *logfile = NULL;
	nih_local char  *session_file = NULL;
	FILE            *fi;

	start_upstart_common (&upstart_pid, TRUE, FALSE, confdir, logdir, extra);

	/*******************************************************************/
	TEST_FEATURE ("ensure list-env in '--user --no-inherit-env' environment gives expected output");

	cmd = nih_sprintf (NULL, "%s list-env 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);

	/* environment should comprise the default environment only */
	TEST_EQ (lines, 2);
	TEST_STR_MATCH (output[0], "PATH=*");
	TEST_STR_MATCH (output[1], "TERM=*");
	nih_free (output);

	/*******************************************************************/
	TEST_FEATURE ("ensure '--user --no-inherit-env' provides expected job environment");

	CREATE_FILE (confdir, "foo.conf", "exec env");

	cmd = nih_sprintf (NULL, "%s reload-configuration 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);
	nih_free (output);

	cmd = nih_sprintf (NULL, "%s start foo 2>&1", get_initctl ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	nih_free (output);

	logfile = NIH_MUST (nih_sprintf (NULL, "%s/%s",
				logdir,
				"foo.log"));

	WAIT_FOR_FILE (logfile);

	fi = fopen (logfile, "r");
	TEST_NE_P (fi, NULL);
	TEST_FILE_CONTAINS (fi, "PATH=*");
	TEST_FILE_CONTAINS (fi, "TERM=*");

	/* asterisk required to match '\r\n' */
	TEST_FILE_CONTAINS (fi, "UPSTART_JOB=foo*");
	TEST_FILE_CONTAINS (fi, "UPSTART_INSTANCE=*");
	TEST_FILE_CONTAINS (fi, "UPSTART_SESSION=*");
	fclose (fi);

	DELETE_FILE (confdir, "foo.conf");
	TEST_EQ (unlink (logfile), 0);

	/*******************************************************************/

	session_file = NIH_MUST (nih_sprintf (NULL, "%s/upstart/sessions/%d.session",
				runtimedir, (int)upstart_pid));

	STOP_UPSTART (upstart_pid);

	unlink (session_file);
}

/*
 * Test all the commands which affect the job environment table together
 * as they are so closely related.
 */
void
test_job_env (void)
{
	char             confdir[PATH_MAX];
	char             logdir[PATH_MAX];
	size_t           lines;
	pid_t            dbus_pid = 0;
	pid_t            upstart_pid = 0;
	char            *value;
	nih_local char  *cmd = NULL;
	char           **output;
	nih_local char  *session_file = NULL;
	char            *xdg_runtime_dir;

	xdg_runtime_dir = getenv ("XDG_RUNTIME_DIR");
	TEST_TRUE (xdg_runtime_dir);

	TEST_GROUP ("job process table commands");

        TEST_FILENAME (confdir);
        TEST_EQ (mkdir (confdir, 0755), 0);

        TEST_FILENAME (logdir);
        TEST_EQ (mkdir (logdir, 0755), 0);

	/* Use the "secret" interface */
	TEST_EQ (setenv ("UPSTART_CONFDIR", confdir, 1), 0);
	TEST_EQ (setenv ("UPSTART_LOGDIR", logdir, 1), 0);

	/*******************************************************************/
	/* Ensure basic variables are set in the current environment */

	if (! getenv ("TERM")) {
		fprintf (stderr, "WARNING: setting TERM to '%s' as not set\n",
				TEST_INITCTL_DEFAULT_TERM);
		assert0 (setenv ("TERM", TEST_INITCTL_DEFAULT_TERM, 1));
	}

	if (! getenv ("PATH")) {
		fprintf (stderr, "WARNING: setting PATH to '%s' as not set\n",
				TEST_INITCTL_DEFAULT_PATH);
		assert0 (setenv ("PATH", TEST_INITCTL_DEFAULT_PATH, 1));
	}

	TEST_DBUS (dbus_pid);
	start_upstart_common (&upstart_pid, TRUE, FALSE, confdir, logdir, NULL);

	cmd = nih_sprintf (NULL, "%s list-sessions 2>&1", get_initctl_binary ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);

	/* look for separator between pid and value of
	 * UPSTART_SESSION.
	 */
	value = strstr (output[0], " ");
	TEST_NE_P (value, NULL);

	/* jump over space */
	value  += 1;
	TEST_NE_P (value, NULL);

	assert0 (setenv ("UPSTART_SESSION", value, 1));
	nih_free (output);

	/*******************************************************************/

	test_job_env_invalid_args (confdir, logdir, upstart_pid, dbus_pid);

	test_default_job_env (confdir, logdir, upstart_pid, dbus_pid);

	test_modified_job_env (confdir, logdir, upstart_pid, dbus_pid);

	test_global_and_local_job_env (confdir, logdir, upstart_pid, dbus_pid);

	/*******************************************************************/

	STOP_UPSTART (upstart_pid);
	session_file = NIH_MUST (nih_sprintf (NULL, "%s/upstart/sessions/%d.session",
				xdg_runtime_dir, (int)upstart_pid));
	unlink (session_file);

	/*******************************************************************/

	test_no_inherit_job_env (xdg_runtime_dir, confdir, logdir);

	/*******************************************************************/

	TEST_DBUS_END (dbus_pid);
	assert0 (unsetenv ("UPSTART_CONFDIR"));
	assert0 (unsetenv ("UPSTART_LOGDIR"));
	assert0 (unsetenv ("UPSTART_SESSION"));

        TEST_EQ (rmdir (confdir), 0);
        TEST_EQ (rmdir (logdir), 0);
}

void
test_dbus_connection (void)
{
	size_t           lines;
	pid_t            dbus_pid = 0;
	pid_t            dbus_pid2 = 0;
	pid_t            upstart_pid = 0;
	nih_local char  *cmd = NULL;
	char           **output;
	nih_local char  *dbus_session_address = NULL;
	nih_local char  *dbus_session_address2 = NULL;
	nih_local char  *upstart_session = NULL;
	nih_local char  *original_runtime = NULL;
	char             dirname[PATH_MAX];
	char            *address;

	original_runtime = nih_strdup (NULL, getenv("XDG_RUNTIME_DIR"));
	TEST_NE_P (original_runtime, NULL);

	TEST_FILENAME (dirname);
	TEST_EQ (mkdir (dirname, 0755), 0);

	TEST_EQ (setenv ("XDG_RUNTIME_DIR", dirname, 1), 0);

	TEST_GROUP ("D-Bus connection");

	/*********************************************************************/
	TEST_FEATURE ("ensure non-priv non-Session Init connects to D-Bus session bus on startup");

	/* Start a dbus-daemon */
	TEST_DBUS (dbus_pid);

	/* Not required */
	assert0 (unsetenv ("DBUS_SYSTEM_BUS_ADDRESS"));

	TEST_TRUE (getenv ("DBUS_SESSION_BUS_ADDRESS"));

	START_UPSTART (upstart_pid, FALSE);

	cmd = nih_sprintf (NULL, "%s --session version 2>&1", get_initctl_binary ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], "init (upstart [0-9.][0-9.]*");
	nih_free (output);

	STOP_UPSTART (upstart_pid);
	TEST_DBUS_END (dbus_pid);

	/*********************************************************************/
	TEST_FEATURE ("ensure Session Init does not connect to D-Bus session bus on startup");

	/* Start a dbus-daemon */
	TEST_DBUS (dbus_pid);

	/* Not required */
	assert0 (unsetenv ("DBUS_SYSTEM_BUS_ADDRESS"));

	TEST_TRUE (getenv ("DBUS_SESSION_BUS_ADDRESS"));

	START_UPSTART (upstart_pid, TRUE);

	address = getenv ("DBUS_SESSION_BUS_ADDRESS");
	TEST_NE_P (address, NULL);
	dbus_session_address = nih_strdup (NULL, address);
	TEST_NE_P (dbus_session_address, NULL);

	/* Stop initctl using this route */
	assert0 (unsetenv ("DBUS_SESSION_BUS_ADDRESS"));

	/* Check we can query the version via the private socket */
	cmd = nih_sprintf (NULL, "%s version 2>&1", get_initctl_binary ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], "init (upstart [0-9.][0-9.]*");
	nih_free (output);

	/* Unset to stop initctl finding upstart via this route */
	assert0 (unsetenv ("UPSTART_SESSION"));

	/* Re-apply in the test environment */
	assert0 (setenv ("DBUS_SESSION_BUS_ADDRESS", dbus_session_address, 1));

	/* Although there is a D-Bus session bus available, the Session
	 * Init should not connect to it. Check this by trying to query
	 * the running version via the D-Bus session bus.
	 */
	cmd = nih_sprintf (NULL, "%s --session version 2>&1", get_initctl_binary ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], "initctl: Name \"com.ubuntu.Upstart\" does not exist*");
	nih_free (output);

	STOP_UPSTART (upstart_pid);
	TEST_DBUS_END (dbus_pid);

	/*********************************************************************/
	TEST_FEATURE ("ensure Session Init connects to D-Bus session bus when notified");

	/* Start a dbus-daemon */
	TEST_DBUS (dbus_pid);

	address = getenv ("DBUS_SESSION_BUS_ADDRESS");
	TEST_NE_P (address, NULL);
	dbus_session_address = nih_strdup (NULL, address);
	TEST_NE_P (dbus_session_address, NULL);

	/* Not required */
	assert0 (unsetenv ("DBUS_SYSTEM_BUS_ADDRESS"));
	assert0 (unsetenv ("DBUS_SESSION_BUS_ADDRESS"));

	nih_local char  **extra = NULL;
	extra = NIH_MUST (nih_str_array_new (NULL));
	NIH_MUST (nih_str_array_add (&extra, NULL, NULL,"--no-startup-event"));
	start_upstart_common (&(upstart_pid), TRUE, FALSE, NULL, NULL, extra);

	/* Pass the D-Bus session bus address to the Session Init */
	cmd = nih_sprintf (NULL, "%s notify-dbus-address \"%s\" 2>&1",
			get_initctl_binary (), dbus_session_address);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);

	/* Re-apply in the test environment */
	assert0 (setenv ("DBUS_SESSION_BUS_ADDRESS", dbus_session_address, 1));

	/* It should now be possible to query the running version via
	 * the D-Bus session bus.
	 */
	cmd = nih_sprintf (NULL, "%s --session version 2>&1", get_initctl_binary ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], "init (upstart [0-9.][0-9.]*");
	nih_free (output);

	/*********************************************************************/
	TEST_FEATURE ("ensure Session Init retains D-Bus address across a re-exec");

	assert0 (unsetenv ("DBUS_SESSION_BUS_ADDRESS"));

	REEXEC_UPSTART (upstart_pid, TRUE);

	/* Re-apply in the test environment */
	assert0 (setenv ("DBUS_SESSION_BUS_ADDRESS", dbus_session_address, 1));

	/* It should still be possible to query the running version via
	 * the D-Bus session bus since Upstart should have reconnected
	 * since it was previously notified of the D-Bus address.
	 */
	cmd = nih_sprintf (NULL, "%s --session version 2>&1", get_initctl_binary ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], "init (upstart [0-9.][0-9.]*");
	nih_free (output);

	STOP_UPSTART (upstart_pid);
	TEST_DBUS_END (dbus_pid);

	/*********************************************************************/
	TEST_FEATURE ("ensure Session Init does not connect to another bus when notified twice");

	/* Start first dbus-daemon */
	TEST_DBUS (dbus_pid);

	/* Save its address */
	address = getenv ("DBUS_SESSION_BUS_ADDRESS");
	TEST_NE_P (address, NULL);
	dbus_session_address = nih_strdup (NULL, address);
	TEST_NE_P (dbus_session_address, NULL);

	/* Start second dbus-daemon */
	TEST_DBUS (dbus_pid2);

	/* Save its address */
	address = getenv ("DBUS_SESSION_BUS_ADDRESS");
	TEST_NE_P (address, NULL);
	dbus_session_address2 = nih_strdup (NULL, address);
	TEST_NE_P (dbus_session_address2, NULL);

	assert0 (unsetenv ("DBUS_SYSTEM_BUS_ADDRESS"));
	assert0 (unsetenv ("DBUS_SESSION_BUS_ADDRESS"));

	start_upstart_common (&(upstart_pid), TRUE, FALSE, NULL, NULL, extra);

	/* Pass the first D-Bus session bus address to the Session Init */
	cmd = nih_sprintf (NULL, "%s notify-dbus-address \"%s\" 2>&1",
			get_initctl_binary (), dbus_session_address);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);

	/* Re-apply in the test environment */
	assert0 (setenv ("DBUS_SESSION_BUS_ADDRESS", dbus_session_address, 1));

	/* It should now be possible to query the running version via
	 * the D-Bus session bus.
	 */
	cmd = nih_sprintf (NULL, "%s --session version 2>&1", get_initctl_binary ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], "init (upstart [0-9.][0-9.]*");
	nih_free (output);

	/* Pass the second D-Bus session bus address to the Session Init */
	cmd = nih_sprintf (NULL, "%s notify-dbus-address \"%s\" 2>&1",
			get_initctl_binary (), dbus_session_address2);
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 0);

	/* Check that the Session Init still responds on the first address */
	cmd = nih_sprintf (NULL, "%s --session version 2>&1", get_initctl_binary ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], "init (upstart [0-9.][0-9.]*");
	nih_free (output);

	/* Stop the 1st daemon */
	TEST_DBUS_END (dbus_pid);

	/* Switch to the 2nd daemon */
	assert0 (setenv ("DBUS_SESSION_BUS_ADDRESS", dbus_session_address2, 1));

	/* Ensure the Session Init isn't responding on this address */
	cmd = nih_sprintf (NULL, "%s --session version 2>&1", get_initctl_binary ());
	TEST_NE_P (cmd, NULL);
	RUN_COMMAND (NULL, cmd, &output, &lines);
	TEST_EQ (lines, 1);
	TEST_STR_MATCH (output[0], "initctl: Name \"com.ubuntu.Upstart\" does not exist*");
	nih_free (output);

	STOP_UPSTART (upstart_pid);

	/* Stop the 2nd daemon */
	TEST_DBUS_END (dbus_pid2);

	TEST_EQ (setenv ("XDG_RUNTIME_DIR", original_runtime, 1), 0);
}

int
main (int   argc,
      char *argv[])
{
	nih_error_init ();
	nih_timer_init ();
	nih_signal_init ();
	nih_child_init ();
	nih_main_loop_init ();
	program_name = "test";

	test_common_setup ();

	test_upstart_open ();
	test_job_status ();

	test_start_action ();
	test_stop_action ();
	test_restart_action ();
	test_reload_action ();
	test_status_action ();
	test_list_action ();
	test_emit_action ();
	test_reload_configuration_action ();
	test_version_action ();
	test_log_priority_action ();
	test_usage ();

	test_job_env ();
	test_reexec ();

	test_list_sessions ();
	if (have_timed_waitpid ()) {
		test_quiesce ();
	} else {
		fprintf (stderr, "\n\n"
				"WARNING: not running quiesce tests, "
				"as no precise timing information available "
				"\n\n");
	}

	test_umask ();
	test_no_dbus ();

	if (in_chroot () && !dbus_configured ()) {
		fprintf (stderr, "\n\n"
				"WARNING: not running show-config, "
				"check-config & notify-disk-writeable tests within chroot "
				"as no D-Bus, or D-Bus not configured (lp:#728988)"
				"\n\n");
	} else {
		test_list ();
		test_show_config ();
		test_check_config ();
		test_notify_disk_writeable ();
	}

	test_dbus_connection ();

	test_common_cleanup ();

	return 0;
}
