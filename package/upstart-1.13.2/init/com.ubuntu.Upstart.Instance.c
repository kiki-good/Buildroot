/* upstart
 *
 * com.ubuntu.Upstart.Instance.c - auto-generated D-Bus bindings
 *
 * Copyright (C) 2010 Scott James Remnant <scott@netsplit.com>.
 *
 * This file was automatically generated; see the source for copying
 * conditions.
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif /* HAVE_CONFIG_H */


#include <dbus/dbus.h>

#include <stdint.h>
#include <string.h>

#include <nih/macros.h>
#include <nih/alloc.h>
#include <nih/string.h>
#include <nih/logging.h>
#include <nih/error.h>

#include <nih-dbus/dbus_error.h>
#include <nih-dbus/dbus_message.h>
#include <nih-dbus/dbus_object.h>
#include <nih-dbus/errors.h>

#include "com.ubuntu.Upstart.Instance.h"


/* Prototypes for static functions */
static DBusHandlerResult job_com_ubuntu_Upstart0_6_Instance_Start_method   (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult job_com_ubuntu_Upstart0_6_Instance_Stop_method    (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult job_com_ubuntu_Upstart0_6_Instance_Restart_method (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult job_com_ubuntu_Upstart0_6_Instance_Reload_method  (NihDBusObject *object, NihDBusMessage *message);
static int               job_com_ubuntu_Upstart0_6_Instance_name_get       (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               job_com_ubuntu_Upstart0_6_Instance_goal_get       (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               job_com_ubuntu_Upstart0_6_Instance_state_get      (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               job_com_ubuntu_Upstart0_6_Instance_processes_get  (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);


/* Prototypes for externally implemented handler functions */
extern int job_start         (void *data, NihDBusMessage *message, int wait)
	__attribute__ ((warn_unused_result));
extern int job_stop          (void *data, NihDBusMessage *message, int wait)
	__attribute__ ((warn_unused_result));
extern int job_restart       (void *data, NihDBusMessage *message, int wait)
	__attribute__ ((warn_unused_result));
extern int job_reload        (void *data, NihDBusMessage *message)
	__attribute__ ((warn_unused_result));
extern int job_get_name      (void *data, NihDBusMessage *message, char **value)
	__attribute__ ((warn_unused_result));
extern int job_get_goal      (void *data, NihDBusMessage *message, char **value)
	__attribute__ ((warn_unused_result));
extern int job_get_state     (void *data, NihDBusMessage *message, char **value)
	__attribute__ ((warn_unused_result));
extern int job_get_processes (void *data, NihDBusMessage *message, JobProcessesElement ***value)
	__attribute__ ((warn_unused_result));


static const NihDBusArg job_com_ubuntu_Upstart0_6_Instance_Start_method_args[] = {
	{ "wait", "b", NIH_DBUS_ARG_IN  },
	{ NULL }
};

static const NihDBusArg job_com_ubuntu_Upstart0_6_Instance_Stop_method_args[] = {
	{ "wait", "b", NIH_DBUS_ARG_IN  },
	{ NULL }
};

static const NihDBusArg job_com_ubuntu_Upstart0_6_Instance_Restart_method_args[] = {
	{ "wait", "b", NIH_DBUS_ARG_IN  },
	{ NULL }
};

static const NihDBusArg job_com_ubuntu_Upstart0_6_Instance_Reload_method_args[] = {
	{ NULL }
};

static const NihDBusMethod job_com_ubuntu_Upstart0_6_Instance_methods[] = {
	{ "Start",   job_com_ubuntu_Upstart0_6_Instance_Start_method_args,   job_com_ubuntu_Upstart0_6_Instance_Start_method   },
	{ "Stop",    job_com_ubuntu_Upstart0_6_Instance_Stop_method_args,    job_com_ubuntu_Upstart0_6_Instance_Stop_method    },
	{ "Restart", job_com_ubuntu_Upstart0_6_Instance_Restart_method_args, job_com_ubuntu_Upstart0_6_Instance_Restart_method },
	{ "Reload",  job_com_ubuntu_Upstart0_6_Instance_Reload_method_args,  job_com_ubuntu_Upstart0_6_Instance_Reload_method  },
	{ NULL }
};

static const NihDBusArg job_com_ubuntu_Upstart0_6_Instance_GoalChanged_signal_args[] = {
	{ "goal", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg job_com_ubuntu_Upstart0_6_Instance_StateChanged_signal_args[] = {
	{ "state", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg job_com_ubuntu_Upstart0_6_Instance_Failed_signal_args[] = {
	{ "status", "i", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusSignal job_com_ubuntu_Upstart0_6_Instance_signals[] = {
	{ "GoalChanged",  job_com_ubuntu_Upstart0_6_Instance_GoalChanged_signal_args,  NULL },
	{ "StateChanged", job_com_ubuntu_Upstart0_6_Instance_StateChanged_signal_args, NULL },
	{ "Failed",       job_com_ubuntu_Upstart0_6_Instance_Failed_signal_args,       NULL },
	{ NULL }
};

static const NihDBusProperty job_com_ubuntu_Upstart0_6_Instance_properties[] = {
	{ "name",      "s",     NIH_DBUS_READ, job_com_ubuntu_Upstart0_6_Instance_name_get,      NULL },
	{ "goal",      "s",     NIH_DBUS_READ, job_com_ubuntu_Upstart0_6_Instance_goal_get,      NULL },
	{ "state",     "s",     NIH_DBUS_READ, job_com_ubuntu_Upstart0_6_Instance_state_get,     NULL },
	{ "processes", "a(si)", NIH_DBUS_READ, job_com_ubuntu_Upstart0_6_Instance_processes_get, NULL },
	{ NULL }
};

const NihDBusInterface job_com_ubuntu_Upstart0_6_Instance = {
	"com.ubuntu.Upstart0_6.Instance",
	job_com_ubuntu_Upstart0_6_Instance_methods,
	job_com_ubuntu_Upstart0_6_Instance_signals,
	job_com_ubuntu_Upstart0_6_Instance_properties
};

const NihDBusInterface *job_interfaces[] = {
	&job_com_ubuntu_Upstart0_6_Instance,
	NULL
};


static DBusHandlerResult
job_com_ubuntu_Upstart0_6_Instance_Start_method (NihDBusObject * object,
                                                 NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	int             wait;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a int from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_BOOLEAN) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to Start method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &wait);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to Start method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (job_start (object->data, message, wait) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	return DBUS_HANDLER_RESULT_HANDLED;
}

int
job_start_reply (NihDBusMessage *message)
{
	DBusMessage *   reply;
	DBusMessageIter iter;

	nih_assert (message != NULL);

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return 0;

	/* Construct the reply message. */
	reply = dbus_message_new_method_return (message->message);
	if (! reply)
		return -1;

	dbus_message_iter_init_append (reply, &iter);

	/* Send the reply, appending it to the outgoing queue. */
	if (! dbus_connection_send (message->connection, reply, NULL)) {
		dbus_message_unref (reply);
		return -1;
	}

	dbus_message_unref (reply);

	return 0;
}


static DBusHandlerResult
job_com_ubuntu_Upstart0_6_Instance_Stop_method (NihDBusObject * object,
                                                NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	int             wait;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a int from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_BOOLEAN) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to Stop method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &wait);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to Stop method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (job_stop (object->data, message, wait) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	return DBUS_HANDLER_RESULT_HANDLED;
}

int
job_stop_reply (NihDBusMessage *message)
{
	DBusMessage *   reply;
	DBusMessageIter iter;

	nih_assert (message != NULL);

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return 0;

	/* Construct the reply message. */
	reply = dbus_message_new_method_return (message->message);
	if (! reply)
		return -1;

	dbus_message_iter_init_append (reply, &iter);

	/* Send the reply, appending it to the outgoing queue. */
	if (! dbus_connection_send (message->connection, reply, NULL)) {
		dbus_message_unref (reply);
		return -1;
	}

	dbus_message_unref (reply);

	return 0;
}


static DBusHandlerResult
job_com_ubuntu_Upstart0_6_Instance_Restart_method (NihDBusObject * object,
                                                   NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	int             wait;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a int from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_BOOLEAN) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to Restart method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &wait);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to Restart method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (job_restart (object->data, message, wait) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	return DBUS_HANDLER_RESULT_HANDLED;
}

int
job_restart_reply (NihDBusMessage *message)
{
	DBusMessage *   reply;
	DBusMessageIter iter;

	nih_assert (message != NULL);

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return 0;

	/* Construct the reply message. */
	reply = dbus_message_new_method_return (message->message);
	if (! reply)
		return -1;

	dbus_message_iter_init_append (reply, &iter);

	/* Send the reply, appending it to the outgoing queue. */
	if (! dbus_connection_send (message->connection, reply, NULL)) {
		dbus_message_unref (reply);
		return -1;
	}

	dbus_message_unref (reply);

	return 0;
}


static DBusHandlerResult
job_com_ubuntu_Upstart0_6_Instance_Reload_method (NihDBusObject * object,
                                                  NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to Reload method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	if (job_reload (object->data, message) < 0) {
		NihError *err;

		err = nih_error_get ();
		if (err->number == ENOMEM) {
			nih_free (err);
			nih_error_pop_context ();

			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		} else if (err->number == NIH_DBUS_ERROR) {
			NihDBusError *dbus_err = (NihDBusError *)err;

			reply = NIH_MUST (dbus_message_new_error (message->message, dbus_err->name, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		} else {
			reply = NIH_MUST (dbus_message_new_error (message->message, DBUS_ERROR_FAILED, err->message));
			nih_free (err);
			nih_error_pop_context ();

			NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}
	}
	nih_error_pop_context ();

	return DBUS_HANDLER_RESULT_HANDLED;
}

int
job_reload_reply (NihDBusMessage *message)
{
	DBusMessage *   reply;
	DBusMessageIter iter;

	nih_assert (message != NULL);

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return 0;

	/* Construct the reply message. */
	reply = dbus_message_new_method_return (message->message);
	if (! reply)
		return -1;

	dbus_message_iter_init_append (reply, &iter);

	/* Send the reply, appending it to the outgoing queue. */
	if (! dbus_connection_send (message->connection, reply, NULL)) {
		dbus_message_unref (reply);
		return -1;
	}

	dbus_message_unref (reply);

	return 0;
}


int
job_emit_goal_changed (DBusConnection *connection,
                       const char *    origin_path,
                       const char *    goal)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);
	nih_assert (goal != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.ubuntu.Upstart0_6.Instance", "GoalChanged");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &goal)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
job_emit_state_changed (DBusConnection *connection,
                        const char *    origin_path,
                        const char *    state)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);
	nih_assert (state != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.ubuntu.Upstart0_6.Instance", "StateChanged");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &state)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


int
job_emit_failed (DBusConnection *connection,
                 const char *    origin_path,
                 int32_t         status)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.ubuntu.Upstart0_6.Instance", "Failed");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a int32_t onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_INT32, &status)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


static int
job_com_ubuntu_Upstart0_6_Instance_name_get (NihDBusObject *  object,
                                             NihDBusMessage * message,
                                             DBusMessageIter *iter)
{
	DBusMessageIter variter;
	char *          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (job_get_name (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "s", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_STRING, &value)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}


static int
job_com_ubuntu_Upstart0_6_Instance_goal_get (NihDBusObject *  object,
                                             NihDBusMessage * message,
                                             DBusMessageIter *iter)
{
	DBusMessageIter variter;
	char *          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (job_get_goal (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "s", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_STRING, &value)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}


static int
job_com_ubuntu_Upstart0_6_Instance_state_get (NihDBusObject *  object,
                                              NihDBusMessage * message,
                                              DBusMessageIter *iter)
{
	DBusMessageIter variter;
	char *          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (job_get_state (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "s", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&variter, DBUS_TYPE_STRING, &value)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}


static int
job_com_ubuntu_Upstart0_6_Instance_processes_get (NihDBusObject *  object,
                                                  NihDBusMessage * message,
                                                  DBusMessageIter *iter)
{
	DBusMessageIter       variter;
	DBusMessageIter       value_iter;
	JobProcessesElement **value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (job_get_processes (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "a(si)", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "(si)", &value_iter)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	if (value) {
		for (size_t value_i = 0; value[value_i]; value_i++) {
			DBusMessageIter            value_element_iter;
			const char *               value_element_item0;
			int32_t                    value_element_item1;
			const JobProcessesElement *value_element;

			value_element = value[value_i];

			/* Marshal a structure onto the message */
			if (! dbus_message_iter_open_container (&value_iter, DBUS_TYPE_STRUCT, NULL, &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (iter, &variter);
				nih_error_raise_no_memory ();
				return -1;
			}

			value_element_item0 = value_element->item0;

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_STRING, &value_element_item0)) {
				dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (iter, &variter);
				nih_error_raise_no_memory ();
				return -1;
			}

			value_element_item1 = value_element->item1;

			/* Marshal a int32_t onto the message */
			if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_INT32, &value_element_item1)) {
				dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (iter, &variter);
				nih_error_raise_no_memory ();
				return -1;
			}

			if (! dbus_message_iter_close_container (&value_iter, &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (iter, &variter);
				nih_error_raise_no_memory ();
				return -1;
			}
		}
	}

	if (! dbus_message_iter_close_container (&variter, &value_iter)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Finish the variant */
	if (! dbus_message_iter_close_container (iter, &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	return 0;
}
