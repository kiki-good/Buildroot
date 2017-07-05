/* upstart
 *
 * com.ubuntu.Upstart.Job.c - auto-generated D-Bus bindings
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
#include <nih-dbus/dbus_pending_data.h>
#include <nih-dbus/dbus_proxy.h>
#include <nih-dbus/errors.h>

#include "com.ubuntu.Upstart.Job.h"


/* Prototypes for static functions */
static void              job_class_com_ubuntu_Upstart0_6_Job_GetInstance_notify       (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              job_class_com_ubuntu_Upstart0_6_Job_GetInstanceByName_notify (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              job_class_com_ubuntu_Upstart0_6_Job_GetAllInstances_notify   (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              job_class_com_ubuntu_Upstart0_6_Job_Start_notify             (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              job_class_com_ubuntu_Upstart0_6_Job_Stop_notify              (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              job_class_com_ubuntu_Upstart0_6_Job_Restart_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static DBusHandlerResult job_class_com_ubuntu_Upstart0_6_Job_InstanceAdded_signal     (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static DBusHandlerResult job_class_com_ubuntu_Upstart0_6_Job_InstanceRemoved_signal   (DBusConnection *connection, DBusMessage *signal, NihDBusProxySignal *proxied);
static void              job_class_com_ubuntu_Upstart0_6_Job_name_get_notify          (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              job_class_com_ubuntu_Upstart0_6_Job_description_get_notify   (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              job_class_com_ubuntu_Upstart0_6_Job_author_get_notify        (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              job_class_com_ubuntu_Upstart0_6_Job_version_get_notify       (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              job_class_com_ubuntu_Upstart0_6_Job_usage_get_notify         (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              job_class_com_ubuntu_Upstart0_6_Job_start_on_get_notify      (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              job_class_com_ubuntu_Upstart0_6_Job_stop_on_get_notify       (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              job_class_com_ubuntu_Upstart0_6_Job_emits_get_notify         (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);
static void              job_class_com_ubuntu_Upstart0_6_Job_get_all_notify           (DBusPendingCall *pending_call, NihDBusPendingData *pending_data);


static const NihDBusArg job_class_com_ubuntu_Upstart0_6_Job_GetInstance_method_args[] = {
	{ "env",      "as", NIH_DBUS_ARG_IN  },
	{ "instance", "o",  NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg job_class_com_ubuntu_Upstart0_6_Job_GetInstanceByName_method_args[] = {
	{ "name",     "s", NIH_DBUS_ARG_IN  },
	{ "instance", "o", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg job_class_com_ubuntu_Upstart0_6_Job_GetAllInstances_method_args[] = {
	{ "instances", "ao", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg job_class_com_ubuntu_Upstart0_6_Job_Start_method_args[] = {
	{ "env",      "as", NIH_DBUS_ARG_IN  },
	{ "wait",     "b",  NIH_DBUS_ARG_IN  },
	{ "instance", "o",  NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg job_class_com_ubuntu_Upstart0_6_Job_Stop_method_args[] = {
	{ "env",  "as", NIH_DBUS_ARG_IN  },
	{ "wait", "b",  NIH_DBUS_ARG_IN  },
	{ NULL }
};

static const NihDBusArg job_class_com_ubuntu_Upstart0_6_Job_Restart_method_args[] = {
	{ "env",      "as", NIH_DBUS_ARG_IN  },
	{ "wait",     "b",  NIH_DBUS_ARG_IN  },
	{ "instance", "o",  NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusMethod job_class_com_ubuntu_Upstart0_6_Job_methods[] = {
	{ "GetInstance",       job_class_com_ubuntu_Upstart0_6_Job_GetInstance_method_args,       NULL },
	{ "GetInstanceByName", job_class_com_ubuntu_Upstart0_6_Job_GetInstanceByName_method_args, NULL },
	{ "GetAllInstances",   job_class_com_ubuntu_Upstart0_6_Job_GetAllInstances_method_args,   NULL },
	{ "Start",             job_class_com_ubuntu_Upstart0_6_Job_Start_method_args,             NULL },
	{ "Stop",              job_class_com_ubuntu_Upstart0_6_Job_Stop_method_args,              NULL },
	{ "Restart",           job_class_com_ubuntu_Upstart0_6_Job_Restart_method_args,           NULL },
	{ NULL }
};

static const NihDBusArg job_class_com_ubuntu_Upstart0_6_Job_InstanceAdded_signal_args[] = {
	{ "instance", "o", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg job_class_com_ubuntu_Upstart0_6_Job_InstanceRemoved_signal_args[] = {
	{ "instance", "o", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusSignal job_class_com_ubuntu_Upstart0_6_Job_signals[] = {
	{ "InstanceAdded",   job_class_com_ubuntu_Upstart0_6_Job_InstanceAdded_signal_args,   job_class_com_ubuntu_Upstart0_6_Job_InstanceAdded_signal   },
	{ "InstanceRemoved", job_class_com_ubuntu_Upstart0_6_Job_InstanceRemoved_signal_args, job_class_com_ubuntu_Upstart0_6_Job_InstanceRemoved_signal },
	{ NULL }
};

static const NihDBusProperty job_class_com_ubuntu_Upstart0_6_Job_properties[] = {
	{ "name",        "s",   NIH_DBUS_READ, NULL, NULL },
	{ "description", "s",   NIH_DBUS_READ, NULL, NULL },
	{ "author",      "s",   NIH_DBUS_READ, NULL, NULL },
	{ "version",     "s",   NIH_DBUS_READ, NULL, NULL },
	{ "usage",       "s",   NIH_DBUS_READ, NULL, NULL },
	{ "start_on",    "aas", NIH_DBUS_READ, NULL, NULL },
	{ "stop_on",     "aas", NIH_DBUS_READ, NULL, NULL },
	{ "emits",       "as",  NIH_DBUS_READ, NULL, NULL },
	{ NULL }
};

const NihDBusInterface job_class_com_ubuntu_Upstart0_6_Job = {
	"com.ubuntu.Upstart0_6.Job",
	job_class_com_ubuntu_Upstart0_6_Job_methods,
	job_class_com_ubuntu_Upstart0_6_Job_signals,
	job_class_com_ubuntu_Upstart0_6_Job_properties
};

const NihDBusInterface *job_class_interfaces[] = {
	&job_class_com_ubuntu_Upstart0_6_Job,
	NULL
};


DBusPendingCall *
job_class_get_instance (NihDBusProxy *           proxy,
                        char * const *           env,
                        JobClassGetInstanceReply handler,
                        NihDBusErrorHandler      error_handler,
                        void *                   data,
                        int                      timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	DBusMessageIter     env_iter;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.ubuntu.Upstart0_6.Job", "GetInstance");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "s", &env_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (env) {
		for (size_t env_i = 0; env[env_i]; env_i++) {
			const char *env_element;

			env_element = env[env_i];

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&env_iter, DBUS_TYPE_STRING, &env_element)) {
				dbus_message_iter_abandon_container (&iter, &env_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &env_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)job_class_com_ubuntu_Upstart0_6_Job_GetInstance_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
job_class_com_ubuntu_Upstart0_6_Job_GetInstance_notify (DBusPendingCall *   pending_call,
                                                        NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          instance;
	const char *    instance_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_OBJECT_PATH) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &instance_dbus);

		instance = nih_strdup (message, instance_dbus);
		if (! instance) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((JobClassGetInstanceReply)pending_data->handler) (pending_data->data, message, instance);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
job_class_get_instance_sync (const void *  parent,
                             NihDBusProxy *proxy,
                             char * const *env,
                             char **       instance)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	DBusMessageIter env_iter;
	char *          instance_local;
	const char *    instance_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (instance != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.ubuntu.Upstart0_6.Job", "GetInstance");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "s", &env_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (env) {
		for (size_t env_i = 0; env[env_i]; env_i++) {
			const char *env_element;

			env_element = env[env_i];

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&env_iter, DBUS_TYPE_STRING, &env_element)) {
				dbus_message_iter_abandon_container (&iter, &env_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &env_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_OBJECT_PATH) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &instance_local_dbus);

		instance_local = nih_strdup (parent, instance_local_dbus);
		if (! instance_local) {
			*instance = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*instance = instance_local;
	enomem: __attribute__ ((unused));
	} while (! *instance);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (instance_local);
		*instance = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
job_class_get_instance_by_name (NihDBusProxy *                 proxy,
                                const char *                   name,
                                JobClassGetInstanceByNameReply handler,
                                NihDBusErrorHandler            error_handler,
                                void *                         data,
                                int                            timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert (name != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.ubuntu.Upstart0_6.Job", "GetInstanceByName");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &name)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)job_class_com_ubuntu_Upstart0_6_Job_GetInstanceByName_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
job_class_com_ubuntu_Upstart0_6_Job_GetInstanceByName_notify (DBusPendingCall *   pending_call,
                                                              NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          instance;
	const char *    instance_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_OBJECT_PATH) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &instance_dbus);

		instance = nih_strdup (message, instance_dbus);
		if (! instance) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((JobClassGetInstanceByNameReply)pending_data->handler) (pending_data->data, message, instance);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
job_class_get_instance_by_name_sync (const void *  parent,
                                     NihDBusProxy *proxy,
                                     const char *  name,
                                     char **       instance)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char *          instance_local;
	const char *    instance_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (name != NULL);
	nih_assert (instance != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.ubuntu.Upstart0_6.Job", "GetInstanceByName");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &name)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_OBJECT_PATH) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &instance_local_dbus);

		instance_local = nih_strdup (parent, instance_local_dbus);
		if (! instance_local) {
			*instance = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*instance = instance_local;
	enomem: __attribute__ ((unused));
	} while (! *instance);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (instance_local);
		*instance = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
job_class_get_all_instances (NihDBusProxy *               proxy,
                             JobClassGetAllInstancesReply handler,
                             NihDBusErrorHandler          error_handler,
                             void *                       data,
                             int                          timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.ubuntu.Upstart0_6.Job", "GetAllInstances");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)job_class_com_ubuntu_Upstart0_6_Job_GetAllInstances_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
job_class_com_ubuntu_Upstart0_6_Job_GetAllInstances_notify (DBusPendingCall *   pending_call,
                                                            NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char **         instances;
	DBusMessageIter instances_iter;
	size_t          instances_size;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &instances_iter);

		instances_size = 0;
		instances = NULL;

		instances = nih_alloc (message, sizeof (char *));
		if (! instances) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		instances[instances_size] = NULL;

		while (dbus_message_iter_get_arg_type (&instances_iter) != DBUS_TYPE_INVALID) {
			const char *instances_element_dbus;
			char **     instances_tmp;
			char *      instances_element;

			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&instances_iter) != DBUS_TYPE_OBJECT_PATH) {
				if (instances)
					nih_free (instances);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&instances_iter, &instances_element_dbus);

			instances_element = nih_strdup (instances, instances_element_dbus);
			if (! instances_element) {
				if (instances)
					nih_free (instances);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			dbus_message_iter_next (&instances_iter);

			if (instances_size + 2 > SIZE_MAX / sizeof (char *)) {
				if (instances)
					nih_free (instances);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			instances_tmp = nih_realloc (instances, message, sizeof (char *) * (instances_size + 2));
			if (! instances_tmp) {
				if (instances)
					nih_free (instances);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			instances = instances_tmp;
			instances[instances_size] = instances_element;
			instances[instances_size + 1] = NULL;

			instances_size++;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((JobClassGetAllInstancesReply)pending_data->handler) (pending_data->data, message, instances);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
job_class_get_all_instances_sync (const void *  parent,
                                  NihDBusProxy *proxy,
                                  char ***      instances)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	char **         instances_local;
	DBusMessageIter instances_local_iter;
	size_t          instances_local_size;

	nih_assert (proxy != NULL);
	nih_assert (instances != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.ubuntu.Upstart0_6.Job", "GetAllInstances");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&iter, &instances_local_iter);

		instances_local_size = 0;
		instances_local = NULL;

		instances_local = nih_alloc (parent, sizeof (char *));
		if (! instances_local) {
			*instances = NULL;
			goto enomem;
		}

		instances_local[instances_local_size] = NULL;

		while (dbus_message_iter_get_arg_type (&instances_local_iter) != DBUS_TYPE_INVALID) {
			const char *instances_local_element_dbus;
			char **     instances_local_tmp;
			char *      instances_local_element;

			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&instances_local_iter) != DBUS_TYPE_OBJECT_PATH) {
				if (instances_local)
					nih_free (instances_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&instances_local_iter, &instances_local_element_dbus);

			instances_local_element = nih_strdup (instances_local, instances_local_element_dbus);
			if (! instances_local_element) {
				if (instances_local)
					nih_free (instances_local);
				*instances = NULL;
				goto enomem;
			}

			dbus_message_iter_next (&instances_local_iter);

			if (instances_local_size + 2 > SIZE_MAX / sizeof (char *)) {
				if (instances_local)
					nih_free (instances_local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			instances_local_tmp = nih_realloc (instances_local, parent, sizeof (char *) * (instances_local_size + 2));
			if (! instances_local_tmp) {
				if (instances_local)
					nih_free (instances_local);
				*instances = NULL;
				goto enomem;
			}

			instances_local = instances_local_tmp;
			instances_local[instances_local_size] = instances_local_element;
			instances_local[instances_local_size + 1] = NULL;

			instances_local_size++;
		}

		dbus_message_iter_next (&iter);

		*instances = instances_local;
	enomem: __attribute__ ((unused));
	} while (! *instances);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (instances_local);
		*instances = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
job_class_start (NihDBusProxy *      proxy,
                 char * const *      env,
                 int                 wait,
                 JobClassStartReply  handler,
                 NihDBusErrorHandler error_handler,
                 void *              data,
                 int                 timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	DBusMessageIter     env_iter;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.ubuntu.Upstart0_6.Job", "Start");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "s", &env_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (env) {
		for (size_t env_i = 0; env[env_i]; env_i++) {
			const char *env_element;

			env_element = env[env_i];

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&env_iter, DBUS_TYPE_STRING, &env_element)) {
				dbus_message_iter_abandon_container (&iter, &env_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &env_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal a int onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_BOOLEAN, &wait)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)job_class_com_ubuntu_Upstart0_6_Job_Start_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
job_class_com_ubuntu_Upstart0_6_Job_Start_notify (DBusPendingCall *   pending_call,
                                                  NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          instance;
	const char *    instance_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_OBJECT_PATH) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &instance_dbus);

		instance = nih_strdup (message, instance_dbus);
		if (! instance) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((JobClassStartReply)pending_data->handler) (pending_data->data, message, instance);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
job_class_start_sync (const void *  parent,
                      NihDBusProxy *proxy,
                      char * const *env,
                      int           wait,
                      char **       instance)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	DBusMessageIter env_iter;
	char *          instance_local;
	const char *    instance_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (instance != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.ubuntu.Upstart0_6.Job", "Start");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "s", &env_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (env) {
		for (size_t env_i = 0; env[env_i]; env_i++) {
			const char *env_element;

			env_element = env[env_i];

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&env_iter, DBUS_TYPE_STRING, &env_element)) {
				dbus_message_iter_abandon_container (&iter, &env_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &env_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal a int onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_BOOLEAN, &wait)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_OBJECT_PATH) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &instance_local_dbus);

		instance_local = nih_strdup (parent, instance_local_dbus);
		if (! instance_local) {
			*instance = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*instance = instance_local;
	enomem: __attribute__ ((unused));
	} while (! *instance);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (instance_local);
		*instance = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
job_class_stop (NihDBusProxy *      proxy,
                char * const *      env,
                int                 wait,
                JobClassStopReply   handler,
                NihDBusErrorHandler error_handler,
                void *              data,
                int                 timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	DBusMessageIter     env_iter;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.ubuntu.Upstart0_6.Job", "Stop");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "s", &env_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (env) {
		for (size_t env_i = 0; env[env_i]; env_i++) {
			const char *env_element;

			env_element = env[env_i];

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&env_iter, DBUS_TYPE_STRING, &env_element)) {
				dbus_message_iter_abandon_container (&iter, &env_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &env_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal a int onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_BOOLEAN, &wait)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)job_class_com_ubuntu_Upstart0_6_Job_Stop_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
job_class_com_ubuntu_Upstart0_6_Job_Stop_notify (DBusPendingCall *   pending_call,
                                                 NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((JobClassStopReply)pending_data->handler) (pending_data->data, message);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
job_class_stop_sync (const void *  parent,
                     NihDBusProxy *proxy,
                     char * const *env,
                     int           wait)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	DBusMessageIter env_iter;

	nih_assert (proxy != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.ubuntu.Upstart0_6.Job", "Stop");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "s", &env_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (env) {
		for (size_t env_i = 0; env[env_i]; env_i++) {
			const char *env_element;

			env_element = env[env_i];

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&env_iter, DBUS_TYPE_STRING, &env_element)) {
				dbus_message_iter_abandon_container (&iter, &env_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &env_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal a int onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_BOOLEAN, &wait)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
job_class_restart (NihDBusProxy *       proxy,
                   char * const *       env,
                   int                  wait,
                   JobClassRestartReply handler,
                   NihDBusErrorHandler  error_handler,
                   void *               data,
                   int                  timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	DBusMessageIter     env_iter;

	nih_assert (proxy != NULL);
	nih_assert ((handler == NULL) || (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.ubuntu.Upstart0_6.Job", "Restart");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "s", &env_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	if (env) {
		for (size_t env_i = 0; env[env_i]; env_i++) {
			const char *env_element;

			env_element = env[env_i];

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&env_iter, DBUS_TYPE_STRING, &env_element)) {
				dbus_message_iter_abandon_container (&iter, &env_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (NULL);
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &env_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Marshal a int onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_BOOLEAN, &wait)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Handle a fire-and-forget message */
	if (! error_handler) {
		dbus_message_set_no_reply (method_call, TRUE);
		if (! dbus_connection_send (proxy->connection, method_call, NULL)) {
			dbus_message_unref (method_call);
			nih_return_no_memory_error (NULL);
		}

		dbus_message_unref (method_call);
		return (DBusPendingCall *)TRUE;
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)job_class_com_ubuntu_Upstart0_6_Job_Restart_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
job_class_com_ubuntu_Upstart0_6_Job_Restart_notify (DBusPendingCall *   pending_call,
                                                    NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	NihDBusMessage *message;
	DBusError       error;
	char *          instance;
	const char *    instance_dbus;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over its arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_OBJECT_PATH) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&iter, &instance_dbus);

		instance = nih_strdup (message, instance_dbus);
		if (! instance) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	if (pending_data->handler) {
		nih_error_push_context ();
		((JobClassRestartReply)pending_data->handler) (pending_data->data, message, instance);
		nih_error_pop_context ();
	}

	nih_free (message);
	dbus_message_unref (reply);
}

int
job_class_restart_sync (const void *  parent,
                        NihDBusProxy *proxy,
                        char * const *env,
                        int           wait,
                        char **       instance)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusError       error;
	DBusMessage *   reply;
	DBusMessageIter env_iter;
	char *          instance_local;
	const char *    instance_local_dbus;

	nih_assert (proxy != NULL);
	nih_assert (instance != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "com.ubuntu.Upstart0_6.Job", "Restart");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "s", &env_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	if (env) {
		for (size_t env_i = 0; env[env_i]; env_i++) {
			const char *env_element;

			env_element = env[env_i];

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&env_iter, DBUS_TYPE_STRING, &env_element)) {
				dbus_message_iter_abandon_container (&iter, &env_iter);
				dbus_message_unref (method_call);
				nih_return_no_memory_error (-1);
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &env_iter)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Marshal a int onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_BOOLEAN, &wait)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the arguments of the reply */
	dbus_message_iter_init (reply, &iter);

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_OBJECT_PATH) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&iter, &instance_local_dbus);

		instance_local = nih_strdup (parent, instance_local_dbus);
		if (! instance_local) {
			*instance = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&iter);

		*instance = instance_local;
	enomem: __attribute__ ((unused));
	} while (! *instance);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (instance_local);
		*instance = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}


static DBusHandlerResult
job_class_com_ubuntu_Upstart0_6_Job_InstanceAdded_signal (DBusConnection *    connection,
                                                          DBusMessage *       signal,
                                                          NihDBusProxySignal *proxied)
{
	DBusMessageIter iter;
	NihDBusMessage *message;
	char *          instance;
	const char *    instance_dbus;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_OBJECT_PATH) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &instance_dbus);

	instance = nih_strdup (message, instance_dbus);
	if (! instance) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((JobClassInstanceAddedHandler)proxied->handler) (proxied->data, message, instance);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static DBusHandlerResult
job_class_com_ubuntu_Upstart0_6_Job_InstanceRemoved_signal (DBusConnection *    connection,
                                                            DBusMessage *       signal,
                                                            NihDBusProxySignal *proxied)
{
	DBusMessageIter iter;
	NihDBusMessage *message;
	char *          instance;
	const char *    instance_dbus;

	nih_assert (connection != NULL);
	nih_assert (signal != NULL);
	nih_assert (proxied != NULL);
	nih_assert (connection == proxied->proxy->connection);

	if (! dbus_message_is_signal (signal, proxied->interface->name, proxied->signal->name))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (! dbus_message_has_path (signal, proxied->proxy->path))
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (proxied->proxy->name)
		if (! dbus_message_has_sender (signal, proxied->proxy->owner))
			return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	message = nih_dbus_message_new (NULL, connection, signal);
	if (! message)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	/* Iterate the arguments to the signal and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_OBJECT_PATH) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &instance_dbus);

	instance = nih_strdup (message, instance_dbus);
	if (! instance) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (message);
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((JobClassInstanceRemovedHandler)proxied->handler) (proxied->data, message, instance);
	nih_error_pop_context ();
	nih_free (message);

	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


DBusPendingCall *
job_class_get_name (NihDBusProxy *       proxy,
                    JobClassGetNameReply handler,
                    NihDBusErrorHandler  error_handler,
                    void *               data,
                    int                  timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.ubuntu.Upstart0_6.Job";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "name";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)job_class_com_ubuntu_Upstart0_6_Job_name_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
job_class_com_ubuntu_Upstart0_6_Job_name_get_notify (DBusPendingCall *   pending_call,
                                                     NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	const char *    value_dbus;
	char *          value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&variter, &value_dbus);

		value = nih_strdup (message, value_dbus);
		if (! value) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((JobClassGetNameReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
job_class_get_name_sync (const void *  parent,
                         NihDBusProxy *proxy,
                         char **       value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	const char *    local_dbus;
	char *          local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.ubuntu.Upstart0_6.Job";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "name";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&variter, &local_dbus);

		local = nih_strdup (parent, local_dbus);
		if (! local) {
			*value = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
job_class_get_description (NihDBusProxy *              proxy,
                           JobClassGetDescriptionReply handler,
                           NihDBusErrorHandler         error_handler,
                           void *                      data,
                           int                         timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.ubuntu.Upstart0_6.Job";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "description";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)job_class_com_ubuntu_Upstart0_6_Job_description_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
job_class_com_ubuntu_Upstart0_6_Job_description_get_notify (DBusPendingCall *   pending_call,
                                                            NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	const char *    value_dbus;
	char *          value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&variter, &value_dbus);

		value = nih_strdup (message, value_dbus);
		if (! value) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((JobClassGetDescriptionReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
job_class_get_description_sync (const void *  parent,
                                NihDBusProxy *proxy,
                                char **       value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	const char *    local_dbus;
	char *          local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.ubuntu.Upstart0_6.Job";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "description";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&variter, &local_dbus);

		local = nih_strdup (parent, local_dbus);
		if (! local) {
			*value = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
job_class_get_author (NihDBusProxy *         proxy,
                      JobClassGetAuthorReply handler,
                      NihDBusErrorHandler    error_handler,
                      void *                 data,
                      int                    timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.ubuntu.Upstart0_6.Job";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "author";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)job_class_com_ubuntu_Upstart0_6_Job_author_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
job_class_com_ubuntu_Upstart0_6_Job_author_get_notify (DBusPendingCall *   pending_call,
                                                       NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	const char *    value_dbus;
	char *          value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&variter, &value_dbus);

		value = nih_strdup (message, value_dbus);
		if (! value) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((JobClassGetAuthorReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
job_class_get_author_sync (const void *  parent,
                           NihDBusProxy *proxy,
                           char **       value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	const char *    local_dbus;
	char *          local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.ubuntu.Upstart0_6.Job";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "author";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&variter, &local_dbus);

		local = nih_strdup (parent, local_dbus);
		if (! local) {
			*value = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
job_class_get_version (NihDBusProxy *          proxy,
                       JobClassGetVersionReply handler,
                       NihDBusErrorHandler     error_handler,
                       void *                  data,
                       int                     timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.ubuntu.Upstart0_6.Job";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "version";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)job_class_com_ubuntu_Upstart0_6_Job_version_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
job_class_com_ubuntu_Upstart0_6_Job_version_get_notify (DBusPendingCall *   pending_call,
                                                        NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	const char *    value_dbus;
	char *          value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&variter, &value_dbus);

		value = nih_strdup (message, value_dbus);
		if (! value) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((JobClassGetVersionReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
job_class_get_version_sync (const void *  parent,
                            NihDBusProxy *proxy,
                            char **       value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	const char *    local_dbus;
	char *          local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.ubuntu.Upstart0_6.Job";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "version";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&variter, &local_dbus);

		local = nih_strdup (parent, local_dbus);
		if (! local) {
			*value = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
job_class_get_usage (NihDBusProxy *        proxy,
                     JobClassGetUsageReply handler,
                     NihDBusErrorHandler   error_handler,
                     void *                data,
                     int                   timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.ubuntu.Upstart0_6.Job";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "usage";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)job_class_com_ubuntu_Upstart0_6_Job_usage_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
job_class_com_ubuntu_Upstart0_6_Job_usage_get_notify (DBusPendingCall *   pending_call,
                                                      NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	const char *    value_dbus;
	char *          value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&variter, &value_dbus);

		value = nih_strdup (message, value_dbus);
		if (! value) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((JobClassGetUsageReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
job_class_get_usage_sync (const void *  parent,
                          NihDBusProxy *proxy,
                          char **       value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	const char *    local_dbus;
	char *          local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.ubuntu.Upstart0_6.Job";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "usage";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&variter, &local_dbus);

		local = nih_strdup (parent, local_dbus);
		if (! local) {
			*value = NULL;
			goto enomem;
		}

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
job_class_get_start_on (NihDBusProxy *          proxy,
                        JobClassGetStartOnReply handler,
                        NihDBusErrorHandler     error_handler,
                        void *                  data,
                        int                     timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.ubuntu.Upstart0_6.Job";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "start_on";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)job_class_com_ubuntu_Upstart0_6_Job_start_on_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
job_class_com_ubuntu_Upstart0_6_Job_start_on_get_notify (DBusPendingCall *   pending_call,
                                                         NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	DBusMessageIter value_iter;
	size_t          value_size;
	char ***        value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&variter, &value_iter);

		value_size = 0;
		value = NULL;

		value = nih_alloc (message, sizeof (char **));
		if (! value) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		value[value_size] = NULL;

		while (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INVALID) {
			DBusMessageIter value_element_iter;
			size_t          value_element_size;
			char ***        value_tmp;
			char **         value_element;

			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_ARRAY) {
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_recurse (&value_iter, &value_element_iter);

			value_element_size = 0;
			value_element = NULL;

			value_element = nih_alloc (value, sizeof (char *));
			if (! value_element) {
				if (value)
					nih_free (value);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			value_element[value_element_size] = NULL;

			while (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_INVALID) {
				const char *value_element_element_dbus;
				char **     value_element_tmp;
				char *      value_element_element;

				/* Demarshal a char * from the message */
				if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_STRING) {
					if (value_element)
						nih_free (value_element);
					if (value)
						nih_free (value);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dbus_message_iter_get_basic (&value_element_iter, &value_element_element_dbus);

				value_element_element = nih_strdup (value_element, value_element_element_dbus);
				if (! value_element_element) {
					if (value_element)
						nih_free (value_element);
					if (value)
						nih_free (value);
					nih_free (message);
					message = NULL;
					goto enomem;
				}

				dbus_message_iter_next (&value_element_iter);

				if (value_element_size + 2 > SIZE_MAX / sizeof (char *)) {
					if (value_element)
						nih_free (value_element);
					if (value)
						nih_free (value);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				value_element_tmp = nih_realloc (value_element, value, sizeof (char *) * (value_element_size + 2));
				if (! value_element_tmp) {
					if (value_element)
						nih_free (value_element);
					if (value)
						nih_free (value);
					nih_free (message);
					message = NULL;
					goto enomem;
				}

				value_element = value_element_tmp;
				value_element[value_element_size] = value_element_element;
				value_element[value_element_size + 1] = NULL;

				value_element_size++;
			}

			dbus_message_iter_next (&value_iter);

			if (value_size + 2 > SIZE_MAX / sizeof (char **)) {
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			value_tmp = nih_realloc (value, message, sizeof (char **) * (value_size + 2));
			if (! value_tmp) {
				if (value)
					nih_free (value);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			value = value_tmp;
			value[value_size] = value_element;
			value[value_size + 1] = NULL;

			value_size++;
		}

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((JobClassGetStartOnReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
job_class_get_start_on_sync (const void *  parent,
                             NihDBusProxy *proxy,
                             char ****     value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	DBusMessageIter local_iter;
	size_t          local_size;
	char ***        local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.ubuntu.Upstart0_6.Job";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "start_on";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&variter, &local_iter);

		local_size = 0;
		local = NULL;

		local = nih_alloc (parent, sizeof (char **));
		if (! local) {
			*value = NULL;
			goto enomem;
		}

		local[local_size] = NULL;

		while (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_INVALID) {
			DBusMessageIter local_element_iter;
			size_t          local_element_size;
			char ***        local_tmp;
			char **         local_element;

			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_ARRAY) {
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_recurse (&local_iter, &local_element_iter);

			local_element_size = 0;
			local_element = NULL;

			local_element = nih_alloc (local, sizeof (char *));
			if (! local_element) {
				if (local)
					nih_free (local);
				*value = NULL;
				goto enomem;
			}

			local_element[local_element_size] = NULL;

			while (dbus_message_iter_get_arg_type (&local_element_iter) != DBUS_TYPE_INVALID) {
				const char *local_element_element_dbus;
				char **     local_element_tmp;
				char *      local_element_element;

				/* Demarshal a char * from the message */
				if (dbus_message_iter_get_arg_type (&local_element_iter) != DBUS_TYPE_STRING) {
					if (local_element)
						nih_free (local_element);
					if (local)
						nih_free (local);
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dbus_message_iter_get_basic (&local_element_iter, &local_element_element_dbus);

				local_element_element = nih_strdup (local_element, local_element_element_dbus);
				if (! local_element_element) {
					if (local_element)
						nih_free (local_element);
					if (local)
						nih_free (local);
					*value = NULL;
					goto enomem;
				}

				dbus_message_iter_next (&local_element_iter);

				if (local_element_size + 2 > SIZE_MAX / sizeof (char *)) {
					if (local_element)
						nih_free (local_element);
					if (local)
						nih_free (local);
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				local_element_tmp = nih_realloc (local_element, local, sizeof (char *) * (local_element_size + 2));
				if (! local_element_tmp) {
					if (local_element)
						nih_free (local_element);
					if (local)
						nih_free (local);
					*value = NULL;
					goto enomem;
				}

				local_element = local_element_tmp;
				local_element[local_element_size] = local_element_element;
				local_element[local_element_size + 1] = NULL;

				local_element_size++;
			}

			dbus_message_iter_next (&local_iter);

			if (local_size + 2 > SIZE_MAX / sizeof (char **)) {
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			local_tmp = nih_realloc (local, parent, sizeof (char **) * (local_size + 2));
			if (! local_tmp) {
				if (local)
					nih_free (local);
				*value = NULL;
				goto enomem;
			}

			local = local_tmp;
			local[local_size] = local_element;
			local[local_size + 1] = NULL;

			local_size++;
		}

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
job_class_get_stop_on (NihDBusProxy *         proxy,
                       JobClassGetStopOnReply handler,
                       NihDBusErrorHandler    error_handler,
                       void *                 data,
                       int                    timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.ubuntu.Upstart0_6.Job";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "stop_on";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)job_class_com_ubuntu_Upstart0_6_Job_stop_on_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
job_class_com_ubuntu_Upstart0_6_Job_stop_on_get_notify (DBusPendingCall *   pending_call,
                                                        NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	DBusMessageIter value_iter;
	size_t          value_size;
	char ***        value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&variter, &value_iter);

		value_size = 0;
		value = NULL;

		value = nih_alloc (message, sizeof (char **));
		if (! value) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		value[value_size] = NULL;

		while (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INVALID) {
			DBusMessageIter value_element_iter;
			size_t          value_element_size;
			char ***        value_tmp;
			char **         value_element;

			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_ARRAY) {
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_recurse (&value_iter, &value_element_iter);

			value_element_size = 0;
			value_element = NULL;

			value_element = nih_alloc (value, sizeof (char *));
			if (! value_element) {
				if (value)
					nih_free (value);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			value_element[value_element_size] = NULL;

			while (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_INVALID) {
				const char *value_element_element_dbus;
				char **     value_element_tmp;
				char *      value_element_element;

				/* Demarshal a char * from the message */
				if (dbus_message_iter_get_arg_type (&value_element_iter) != DBUS_TYPE_STRING) {
					if (value_element)
						nih_free (value_element);
					if (value)
						nih_free (value);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dbus_message_iter_get_basic (&value_element_iter, &value_element_element_dbus);

				value_element_element = nih_strdup (value_element, value_element_element_dbus);
				if (! value_element_element) {
					if (value_element)
						nih_free (value_element);
					if (value)
						nih_free (value);
					nih_free (message);
					message = NULL;
					goto enomem;
				}

				dbus_message_iter_next (&value_element_iter);

				if (value_element_size + 2 > SIZE_MAX / sizeof (char *)) {
					if (value_element)
						nih_free (value_element);
					if (value)
						nih_free (value);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				value_element_tmp = nih_realloc (value_element, value, sizeof (char *) * (value_element_size + 2));
				if (! value_element_tmp) {
					if (value_element)
						nih_free (value_element);
					if (value)
						nih_free (value);
					nih_free (message);
					message = NULL;
					goto enomem;
				}

				value_element = value_element_tmp;
				value_element[value_element_size] = value_element_element;
				value_element[value_element_size + 1] = NULL;

				value_element_size++;
			}

			dbus_message_iter_next (&value_iter);

			if (value_size + 2 > SIZE_MAX / sizeof (char **)) {
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			value_tmp = nih_realloc (value, message, sizeof (char **) * (value_size + 2));
			if (! value_tmp) {
				if (value)
					nih_free (value);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			value = value_tmp;
			value[value_size] = value_element;
			value[value_size + 1] = NULL;

			value_size++;
		}

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((JobClassGetStopOnReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
job_class_get_stop_on_sync (const void *  parent,
                            NihDBusProxy *proxy,
                            char ****     value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	DBusMessageIter local_iter;
	size_t          local_size;
	char ***        local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.ubuntu.Upstart0_6.Job";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "stop_on";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&variter, &local_iter);

		local_size = 0;
		local = NULL;

		local = nih_alloc (parent, sizeof (char **));
		if (! local) {
			*value = NULL;
			goto enomem;
		}

		local[local_size] = NULL;

		while (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_INVALID) {
			DBusMessageIter local_element_iter;
			size_t          local_element_size;
			char ***        local_tmp;
			char **         local_element;

			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_ARRAY) {
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_recurse (&local_iter, &local_element_iter);

			local_element_size = 0;
			local_element = NULL;

			local_element = nih_alloc (local, sizeof (char *));
			if (! local_element) {
				if (local)
					nih_free (local);
				*value = NULL;
				goto enomem;
			}

			local_element[local_element_size] = NULL;

			while (dbus_message_iter_get_arg_type (&local_element_iter) != DBUS_TYPE_INVALID) {
				const char *local_element_element_dbus;
				char **     local_element_tmp;
				char *      local_element_element;

				/* Demarshal a char * from the message */
				if (dbus_message_iter_get_arg_type (&local_element_iter) != DBUS_TYPE_STRING) {
					if (local_element)
						nih_free (local_element);
					if (local)
						nih_free (local);
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dbus_message_iter_get_basic (&local_element_iter, &local_element_element_dbus);

				local_element_element = nih_strdup (local_element, local_element_element_dbus);
				if (! local_element_element) {
					if (local_element)
						nih_free (local_element);
					if (local)
						nih_free (local);
					*value = NULL;
					goto enomem;
				}

				dbus_message_iter_next (&local_element_iter);

				if (local_element_size + 2 > SIZE_MAX / sizeof (char *)) {
					if (local_element)
						nih_free (local_element);
					if (local)
						nih_free (local);
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				local_element_tmp = nih_realloc (local_element, local, sizeof (char *) * (local_element_size + 2));
				if (! local_element_tmp) {
					if (local_element)
						nih_free (local_element);
					if (local)
						nih_free (local);
					*value = NULL;
					goto enomem;
				}

				local_element = local_element_tmp;
				local_element[local_element_size] = local_element_element;
				local_element[local_element_size + 1] = NULL;

				local_element_size++;
			}

			dbus_message_iter_next (&local_iter);

			if (local_size + 2 > SIZE_MAX / sizeof (char **)) {
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			local_tmp = nih_realloc (local, parent, sizeof (char **) * (local_size + 2));
			if (! local_tmp) {
				if (local)
					nih_free (local);
				*value = NULL;
				goto enomem;
			}

			local = local_tmp;
			local[local_size] = local_element;
			local[local_size + 1] = NULL;

			local_size++;
		}

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
job_class_get_emits (NihDBusProxy *        proxy,
                     JobClassGetEmitsReply handler,
                     NihDBusErrorHandler   error_handler,
                     void *                data,
                     int                   timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;
	const char *        property;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.ubuntu.Upstart0_6.Job";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	property = "emits";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)job_class_com_ubuntu_Upstart0_6_Job_emits_get_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
job_class_com_ubuntu_Upstart0_6_Job_emits_get_notify (DBusPendingCall *   pending_call,
                                                      NihDBusPendingData *pending_data)
{
	DBusMessage *   reply;
	DBusMessageIter iter;
	DBusMessageIter variter;
	NihDBusMessage *message;
	DBusError       error;
	DBusMessageIter value_iter;
	size_t          value_size;
	char **         value;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	do {
		__label__ enomem;

		/* Create a message context for the reply, and iterate
		 * over and recurse into the arguments.
		 */
		message = nih_dbus_message_new (pending_data, pending_data->connection, reply);
		if (! message)
			goto enomem;

		dbus_message_iter_init (message->message, &iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&iter, &variter);

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&variter, &value_iter);

		value_size = 0;
		value = NULL;

		value = nih_alloc (message, sizeof (char *));
		if (! value) {
			nih_free (message);
			message = NULL;
			goto enomem;
		}

		value[value_size] = NULL;

		while (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_INVALID) {
			const char *value_element_dbus;
			char **     value_tmp;
			char *      value_element;

			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&value_iter) != DBUS_TYPE_STRING) {
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&value_iter, &value_element_dbus);

			value_element = nih_strdup (value, value_element_dbus);
			if (! value_element) {
				if (value)
					nih_free (value);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			dbus_message_iter_next (&value_iter);

			if (value_size + 2 > SIZE_MAX / sizeof (char *)) {
				if (value)
					nih_free (value);
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			value_tmp = nih_realloc (value, message, sizeof (char *) * (value_size + 2));
			if (! value_tmp) {
				if (value)
					nih_free (value);
				nih_free (message);
				message = NULL;
				goto enomem;
			}

			value = value_tmp;
			value[value_size] = value_element;
			value[value_size + 1] = NULL;

			value_size++;
		}

		dbus_message_iter_next (&variter);

		dbus_message_iter_next (&iter);

		if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

	enomem: __attribute__ ((unused));
	} while (! message);

	/* Call the handler function */
	nih_error_push_context ();
	((JobClassGetEmitsReply)pending_data->handler) (pending_data->data, message, value);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
job_class_get_emits_sync (const void *  parent,
                          NihDBusProxy *proxy,
                          char ***      value)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	const char *    interface;
	const char *    property;
	DBusMessageIter local_iter;
	size_t          local_size;
	char **         local;

	nih_assert (proxy != NULL);
	nih_assert (value != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "Get");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.ubuntu.Upstart0_6.Job";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	property = "emits";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &property)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the variant */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_VARIANT) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_iter_recurse (&iter, &variter);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	do {
		__label__ enomem;

		/* Demarshal an array from the message */
		if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&variter, &local_iter);

		local_size = 0;
		local = NULL;

		local = nih_alloc (parent, sizeof (char *));
		if (! local) {
			*value = NULL;
			goto enomem;
		}

		local[local_size] = NULL;

		while (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_INVALID) {
			const char *local_element_dbus;
			char **     local_tmp;
			char *      local_element;

			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&local_iter) != DBUS_TYPE_STRING) {
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&local_iter, &local_element_dbus);

			local_element = nih_strdup (local, local_element_dbus);
			if (! local_element) {
				if (local)
					nih_free (local);
				*value = NULL;
				goto enomem;
			}

			dbus_message_iter_next (&local_iter);

			if (local_size + 2 > SIZE_MAX / sizeof (char *)) {
				if (local)
					nih_free (local);
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			local_tmp = nih_realloc (local, parent, sizeof (char *) * (local_size + 2));
			if (! local_tmp) {
				if (local)
					nih_free (local);
				*value = NULL;
				goto enomem;
			}

			local = local_tmp;
			local[local_size] = local_element;
			local[local_size + 1] = NULL;

			local_size++;
		}

		dbus_message_iter_next (&variter);

		*value = local;
	enomem: __attribute__ ((unused));
	} while (! *value);

	dbus_message_unref (reply);

	return 0;
}


DBusPendingCall *
job_class_get_all (NihDBusProxy *      proxy,
                   JobClassGetAllReply handler,
                   NihDBusErrorHandler error_handler,
                   void *              data,
                   int                 timeout)
{
	DBusMessage *       method_call;
	DBusMessageIter     iter;
	DBusPendingCall *   pending_call;
	NihDBusPendingData *pending_data;
	const char *        interface;

	nih_assert (proxy != NULL);
	nih_assert ((handler != NULL) && (error_handler != NULL));

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "GetAll");
	if (! method_call)
		nih_return_no_memory_error (NULL);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.ubuntu.Upstart0_6.Job";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	/* Send the message and set up the reply notification. */
	pending_data = nih_dbus_pending_data_new (NULL, proxy->connection,
	                                          (NihDBusReplyHandler)handler,
	                                          error_handler, data);
	if (! pending_data) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (NULL);
	}

	pending_call = NULL;
	if (! dbus_connection_send_with_reply (proxy->connection, method_call,
	                                       &pending_call, timeout)) {
		dbus_message_unref (method_call);
		nih_free (pending_data);
		nih_return_no_memory_error (NULL);
	}

	dbus_message_unref (method_call);

	if (! pending_call) {
		nih_dbus_error_raise (DBUS_ERROR_DISCONNECTED,
		                      "Connection is closed");
		nih_free (pending_data);
		return NULL;
	}

	NIH_MUST (dbus_pending_call_set_notify (pending_call, (DBusPendingCallNotifyFunction)job_class_com_ubuntu_Upstart0_6_Job_get_all_notify,
	                                        pending_data, (DBusFreeFunction)nih_discard));

	return pending_call;
}

static void
job_class_com_ubuntu_Upstart0_6_Job_get_all_notify (DBusPendingCall *   pending_call,
                                                    NihDBusPendingData *pending_data)
{
	DBusMessage *       reply;
	DBusMessageIter     iter;
	DBusMessageIter     arrayiter;
	DBusMessageIter     dictiter;
	DBusMessageIter     variter;
	NihDBusMessage *    message;
	DBusError           error;
	const char *        property;
	JobClassProperties *properties;
	size_t              property_count;
	char *              name;
	const char *        name_dbus;
	char *              description;
	const char *        description_dbus;
	char *              author;
	const char *        author_dbus;
	char *              version;
	const char *        version_dbus;
	char *              usage;
	const char *        usage_dbus;
	char ***            start_on;
	DBusMessageIter     start_on_iter;
	size_t              start_on_size;
	char ***            stop_on;
	DBusMessageIter     stop_on_iter;
	size_t              stop_on_size;
	char **             emits;
	DBusMessageIter     emits_iter;
	size_t              emits_size;

	nih_assert (pending_call != NULL);
	nih_assert (pending_data != NULL);

	nih_assert (dbus_pending_call_get_completed (pending_call));

	/* Steal the reply from the pending call. */
	reply = dbus_pending_call_steal_reply (pending_call);
	nih_assert (reply != NULL);

	/* Handle error replies */
	if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR) {
		message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

		dbus_error_init (&error);
		dbus_set_error_from_message (&error, message->message);

		nih_error_push_context ();
		nih_dbus_error_raise (error.name, error.message);
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		dbus_error_free (&error);
		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	nih_assert (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_METHOD_RETURN);

	/* Create a message context for the reply, and iterate
	 * over and recurse into the arguments.
	 */
	message = NIH_MUST (nih_dbus_message_new (pending_data, pending_data->connection, reply));

	/* Iterate the method arguments, recursing into the array */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	properties = NIH_MUST (nih_new (message, JobClassProperties));
	property_count = 0;

	dbus_message_iter_recurse (&iter, &arrayiter);

	while (dbus_message_iter_get_arg_type (&arrayiter) != DBUS_TYPE_INVALID) {
		__label__ enomem;

		if (dbus_message_iter_get_arg_type (&arrayiter) != DBUS_TYPE_DICT_ENTRY) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&arrayiter, &dictiter);

		if (dbus_message_iter_get_arg_type (&dictiter) != DBUS_TYPE_STRING) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_get_basic (&dictiter, &property);

		dbus_message_iter_next (&dictiter);

		if (dbus_message_iter_get_arg_type (&dictiter) != DBUS_TYPE_VARIANT) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_recurse (&dictiter, &variter);

		if (! strcmp (property, "name")) {
			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&variter, &name_dbus);

			name = nih_strdup (properties, name_dbus);
			if (! name) {
				goto enomem;
			}

			dbus_message_iter_next (&variter);

			properties->name = name;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "description")) {
			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&variter, &description_dbus);

			description = nih_strdup (properties, description_dbus);
			if (! description) {
				goto enomem;
			}

			dbus_message_iter_next (&variter);

			properties->description = description;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "author")) {
			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&variter, &author_dbus);

			author = nih_strdup (properties, author_dbus);
			if (! author) {
				goto enomem;
			}

			dbus_message_iter_next (&variter);

			properties->author = author;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "version")) {
			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&variter, &version_dbus);

			version = nih_strdup (properties, version_dbus);
			if (! version) {
				goto enomem;
			}

			dbus_message_iter_next (&variter);

			properties->version = version;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "usage")) {
			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_get_basic (&variter, &usage_dbus);

			usage = nih_strdup (properties, usage_dbus);
			if (! usage) {
				goto enomem;
			}

			dbus_message_iter_next (&variter);

			properties->usage = usage;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "start_on")) {
			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_recurse (&variter, &start_on_iter);

			start_on_size = 0;
			start_on = NULL;

			start_on = nih_alloc (properties, sizeof (char **));
			if (! start_on) {
				goto enomem;
			}

			start_on[start_on_size] = NULL;

			while (dbus_message_iter_get_arg_type (&start_on_iter) != DBUS_TYPE_INVALID) {
				DBusMessageIter start_on_element_iter;
				size_t          start_on_element_size;
				char ***        start_on_tmp;
				char **         start_on_element;

				/* Demarshal an array from the message */
				if (dbus_message_iter_get_arg_type (&start_on_iter) != DBUS_TYPE_ARRAY) {
					if (start_on)
						nih_free (start_on);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dbus_message_iter_recurse (&start_on_iter, &start_on_element_iter);

				start_on_element_size = 0;
				start_on_element = NULL;

				start_on_element = nih_alloc (start_on, sizeof (char *));
				if (! start_on_element) {
					if (start_on)
						nih_free (start_on);
					goto enomem;
				}

				start_on_element[start_on_element_size] = NULL;

				while (dbus_message_iter_get_arg_type (&start_on_element_iter) != DBUS_TYPE_INVALID) {
					const char *start_on_element_element_dbus;
					char **     start_on_element_tmp;
					char *      start_on_element_element;

					/* Demarshal a char * from the message */
					if (dbus_message_iter_get_arg_type (&start_on_element_iter) != DBUS_TYPE_STRING) {
						if (start_on_element)
							nih_free (start_on_element);
						if (start_on)
							nih_free (start_on);
						nih_error_push_context ();
						nih_error_raise (NIH_DBUS_INVALID_ARGS,
						                 _(NIH_DBUS_INVALID_ARGS_STR));
						pending_data->error_handler (pending_data->data, message);
						nih_error_pop_context ();

						nih_free (message);
						dbus_message_unref (reply);
						return;
					}

					dbus_message_iter_get_basic (&start_on_element_iter, &start_on_element_element_dbus);

					start_on_element_element = nih_strdup (start_on_element, start_on_element_element_dbus);
					if (! start_on_element_element) {
						if (start_on_element)
							nih_free (start_on_element);
						if (start_on)
							nih_free (start_on);
						goto enomem;
					}

					dbus_message_iter_next (&start_on_element_iter);

					if (start_on_element_size + 2 > SIZE_MAX / sizeof (char *)) {
						if (start_on_element)
							nih_free (start_on_element);
						if (start_on)
							nih_free (start_on);
						nih_error_push_context ();
						nih_error_raise (NIH_DBUS_INVALID_ARGS,
						                 _(NIH_DBUS_INVALID_ARGS_STR));
						pending_data->error_handler (pending_data->data, message);
						nih_error_pop_context ();

						nih_free (message);
						dbus_message_unref (reply);
						return;
					}

					start_on_element_tmp = nih_realloc (start_on_element, start_on, sizeof (char *) * (start_on_element_size + 2));
					if (! start_on_element_tmp) {
						if (start_on_element)
							nih_free (start_on_element);
						if (start_on)
							nih_free (start_on);
						goto enomem;
					}

					start_on_element = start_on_element_tmp;
					start_on_element[start_on_element_size] = start_on_element_element;
					start_on_element[start_on_element_size + 1] = NULL;

					start_on_element_size++;
				}

				dbus_message_iter_next (&start_on_iter);

				if (start_on_size + 2 > SIZE_MAX / sizeof (char **)) {
					if (start_on)
						nih_free (start_on);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				start_on_tmp = nih_realloc (start_on, properties, sizeof (char **) * (start_on_size + 2));
				if (! start_on_tmp) {
					if (start_on)
						nih_free (start_on);
					goto enomem;
				}

				start_on = start_on_tmp;
				start_on[start_on_size] = start_on_element;
				start_on[start_on_size + 1] = NULL;

				start_on_size++;
			}

			dbus_message_iter_next (&variter);

			properties->start_on = start_on;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "stop_on")) {
			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_recurse (&variter, &stop_on_iter);

			stop_on_size = 0;
			stop_on = NULL;

			stop_on = nih_alloc (properties, sizeof (char **));
			if (! stop_on) {
				goto enomem;
			}

			stop_on[stop_on_size] = NULL;

			while (dbus_message_iter_get_arg_type (&stop_on_iter) != DBUS_TYPE_INVALID) {
				DBusMessageIter stop_on_element_iter;
				size_t          stop_on_element_size;
				char ***        stop_on_tmp;
				char **         stop_on_element;

				/* Demarshal an array from the message */
				if (dbus_message_iter_get_arg_type (&stop_on_iter) != DBUS_TYPE_ARRAY) {
					if (stop_on)
						nih_free (stop_on);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dbus_message_iter_recurse (&stop_on_iter, &stop_on_element_iter);

				stop_on_element_size = 0;
				stop_on_element = NULL;

				stop_on_element = nih_alloc (stop_on, sizeof (char *));
				if (! stop_on_element) {
					if (stop_on)
						nih_free (stop_on);
					goto enomem;
				}

				stop_on_element[stop_on_element_size] = NULL;

				while (dbus_message_iter_get_arg_type (&stop_on_element_iter) != DBUS_TYPE_INVALID) {
					const char *stop_on_element_element_dbus;
					char **     stop_on_element_tmp;
					char *      stop_on_element_element;

					/* Demarshal a char * from the message */
					if (dbus_message_iter_get_arg_type (&stop_on_element_iter) != DBUS_TYPE_STRING) {
						if (stop_on_element)
							nih_free (stop_on_element);
						if (stop_on)
							nih_free (stop_on);
						nih_error_push_context ();
						nih_error_raise (NIH_DBUS_INVALID_ARGS,
						                 _(NIH_DBUS_INVALID_ARGS_STR));
						pending_data->error_handler (pending_data->data, message);
						nih_error_pop_context ();

						nih_free (message);
						dbus_message_unref (reply);
						return;
					}

					dbus_message_iter_get_basic (&stop_on_element_iter, &stop_on_element_element_dbus);

					stop_on_element_element = nih_strdup (stop_on_element, stop_on_element_element_dbus);
					if (! stop_on_element_element) {
						if (stop_on_element)
							nih_free (stop_on_element);
						if (stop_on)
							nih_free (stop_on);
						goto enomem;
					}

					dbus_message_iter_next (&stop_on_element_iter);

					if (stop_on_element_size + 2 > SIZE_MAX / sizeof (char *)) {
						if (stop_on_element)
							nih_free (stop_on_element);
						if (stop_on)
							nih_free (stop_on);
						nih_error_push_context ();
						nih_error_raise (NIH_DBUS_INVALID_ARGS,
						                 _(NIH_DBUS_INVALID_ARGS_STR));
						pending_data->error_handler (pending_data->data, message);
						nih_error_pop_context ();

						nih_free (message);
						dbus_message_unref (reply);
						return;
					}

					stop_on_element_tmp = nih_realloc (stop_on_element, stop_on, sizeof (char *) * (stop_on_element_size + 2));
					if (! stop_on_element_tmp) {
						if (stop_on_element)
							nih_free (stop_on_element);
						if (stop_on)
							nih_free (stop_on);
						goto enomem;
					}

					stop_on_element = stop_on_element_tmp;
					stop_on_element[stop_on_element_size] = stop_on_element_element;
					stop_on_element[stop_on_element_size + 1] = NULL;

					stop_on_element_size++;
				}

				dbus_message_iter_next (&stop_on_iter);

				if (stop_on_size + 2 > SIZE_MAX / sizeof (char **)) {
					if (stop_on)
						nih_free (stop_on);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				stop_on_tmp = nih_realloc (stop_on, properties, sizeof (char **) * (stop_on_size + 2));
				if (! stop_on_tmp) {
					if (stop_on)
						nih_free (stop_on);
					goto enomem;
				}

				stop_on = stop_on_tmp;
				stop_on[stop_on_size] = stop_on_element;
				stop_on[stop_on_size + 1] = NULL;

				stop_on_size++;
			}

			dbus_message_iter_next (&variter);

			properties->stop_on = stop_on;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "emits")) {
			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
				nih_error_push_context ();
				nih_error_raise (NIH_DBUS_INVALID_ARGS,
				                 _(NIH_DBUS_INVALID_ARGS_STR));
				pending_data->error_handler (pending_data->data, message);
				nih_error_pop_context ();

				nih_free (message);
				dbus_message_unref (reply);
				return;
			}

			dbus_message_iter_recurse (&variter, &emits_iter);

			emits_size = 0;
			emits = NULL;

			emits = nih_alloc (properties, sizeof (char *));
			if (! emits) {
				goto enomem;
			}

			emits[emits_size] = NULL;

			while (dbus_message_iter_get_arg_type (&emits_iter) != DBUS_TYPE_INVALID) {
				const char *emits_element_dbus;
				char **     emits_tmp;
				char *      emits_element;

				/* Demarshal a char * from the message */
				if (dbus_message_iter_get_arg_type (&emits_iter) != DBUS_TYPE_STRING) {
					if (emits)
						nih_free (emits);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				dbus_message_iter_get_basic (&emits_iter, &emits_element_dbus);

				emits_element = nih_strdup (emits, emits_element_dbus);
				if (! emits_element) {
					if (emits)
						nih_free (emits);
					goto enomem;
				}

				dbus_message_iter_next (&emits_iter);

				if (emits_size + 2 > SIZE_MAX / sizeof (char *)) {
					if (emits)
						nih_free (emits);
					nih_error_push_context ();
					nih_error_raise (NIH_DBUS_INVALID_ARGS,
					                 _(NIH_DBUS_INVALID_ARGS_STR));
					pending_data->error_handler (pending_data->data, message);
					nih_error_pop_context ();

					nih_free (message);
					dbus_message_unref (reply);
					return;
				}

				emits_tmp = nih_realloc (emits, properties, sizeof (char *) * (emits_size + 2));
				if (! emits_tmp) {
					if (emits)
						nih_free (emits);
					goto enomem;
				}

				emits = emits_tmp;
				emits[emits_size] = emits_element;
				emits[emits_size + 1] = NULL;

				emits_size++;
			}

			dbus_message_iter_next (&variter);

			properties->emits = emits;

			nih_assert (++property_count);
		}

		dbus_message_iter_next (&dictiter);

		if (dbus_message_iter_get_arg_type (&dictiter) != DBUS_TYPE_INVALID) {
			nih_error_push_context ();
			nih_error_raise (NIH_DBUS_INVALID_ARGS,
			                 _(NIH_DBUS_INVALID_ARGS_STR));
			pending_data->error_handler (pending_data->data, message);
			nih_error_pop_context ();

			nih_free (message);
			dbus_message_unref (reply);
			return;
		}

		dbus_message_iter_next (&arrayiter);
	enomem: __attribute__ ((unused));
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	if (property_count < 8) {
		nih_error_push_context ();
		nih_error_raise (NIH_DBUS_INVALID_ARGS,
		                 _(NIH_DBUS_INVALID_ARGS_STR));
		pending_data->error_handler (pending_data->data, message);
		nih_error_pop_context ();

		nih_free (message);
		dbus_message_unref (reply);
		return;
	}

	/* Call the handler function */
	nih_error_push_context ();
	((JobClassGetAllReply)pending_data->handler) (pending_data->data, message, properties);
	nih_error_pop_context ();

	nih_free (message);
	dbus_message_unref (reply);
}

int
job_class_get_all_sync (const void *         parent,
                        NihDBusProxy *       proxy,
                        JobClassProperties **properties)
{
	DBusMessage *   method_call;
	DBusMessageIter iter;
	DBusMessageIter arrayiter;
	DBusMessageIter dictiter;
	DBusMessageIter variter;
	DBusError       error;
	DBusMessage *   reply;
	size_t          property_count;
	const char *    interface;
	const char *    property;
	char *          name;
	const char *    name_dbus;
	char *          description;
	const char *    description_dbus;
	char *          author;
	const char *    author_dbus;
	char *          version;
	const char *    version_dbus;
	char *          usage;
	const char *    usage_dbus;
	char ***        start_on;
	DBusMessageIter start_on_iter;
	size_t          start_on_size;
	char ***        stop_on;
	DBusMessageIter stop_on_iter;
	size_t          stop_on_size;
	char **         emits;
	DBusMessageIter emits_iter;
	size_t          emits_size;

	nih_assert (proxy != NULL);
	nih_assert (properties != NULL);

	/* Construct the method call message. */
	method_call = dbus_message_new_method_call (proxy->name, proxy->path, "org.freedesktop.DBus.Properties", "GetAll");
	if (! method_call)
		nih_return_no_memory_error (-1);

	dbus_message_set_auto_start (method_call, proxy->auto_start);

	dbus_message_iter_init_append (method_call, &iter);

	interface = "com.ubuntu.Upstart0_6.Job";
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &interface)) {
		dbus_message_unref (method_call);
		nih_return_no_memory_error (-1);
	}

	/* Send the message, and wait for the reply. */
	dbus_error_init (&error);

	reply = dbus_connection_send_with_reply_and_block (proxy->connection, method_call, -1, &error);
	if (! reply) {
		dbus_message_unref (method_call);

		if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY)) {
			nih_error_raise_no_memory ();
		} else {
			nih_dbus_error_raise (error.name, error.message);
		}

		dbus_error_free (&error);
		return -1;
	}

	dbus_message_unref (method_call);

	/* Iterate the method arguments, recursing into the array */
	dbus_message_iter_init (reply, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	*properties = NIH_MUST (nih_new (parent, JobClassProperties));
	property_count = 0;

	dbus_message_iter_recurse (&iter, &arrayiter);

	while (dbus_message_iter_get_arg_type (&arrayiter) != DBUS_TYPE_INVALID) {
		__label__ enomem;

		if (dbus_message_iter_get_arg_type (&arrayiter) != DBUS_TYPE_DICT_ENTRY) {
			nih_free (*properties);
			*properties = NULL;
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&arrayiter, &dictiter);

		if (dbus_message_iter_get_arg_type (&dictiter) != DBUS_TYPE_STRING) {
			nih_free (*properties);
			*properties = NULL;
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_get_basic (&dictiter, &property);

		dbus_message_iter_next (&dictiter);

		if (dbus_message_iter_get_arg_type (&dictiter) != DBUS_TYPE_VARIANT) {
			nih_free (*properties);
			*properties = NULL;
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_recurse (&dictiter, &variter);

		if (! strcmp (property, "name")) {
			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&variter, &name_dbus);

			name = nih_strdup (*properties, name_dbus);
			if (! name) {
				goto enomem;
			}

			dbus_message_iter_next (&variter);

			(*properties)->name = name;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "description")) {
			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&variter, &description_dbus);

			description = nih_strdup (*properties, description_dbus);
			if (! description) {
				goto enomem;
			}

			dbus_message_iter_next (&variter);

			(*properties)->description = description;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "author")) {
			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&variter, &author_dbus);

			author = nih_strdup (*properties, author_dbus);
			if (! author) {
				goto enomem;
			}

			dbus_message_iter_next (&variter);

			(*properties)->author = author;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "version")) {
			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&variter, &version_dbus);

			version = nih_strdup (*properties, version_dbus);
			if (! version) {
				goto enomem;
			}

			dbus_message_iter_next (&variter);

			(*properties)->version = version;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "usage")) {
			/* Demarshal a char * from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_get_basic (&variter, &usage_dbus);

			usage = nih_strdup (*properties, usage_dbus);
			if (! usage) {
				goto enomem;
			}

			dbus_message_iter_next (&variter);

			(*properties)->usage = usage;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "start_on")) {
			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_recurse (&variter, &start_on_iter);

			start_on_size = 0;
			start_on = NULL;

			start_on = nih_alloc (*properties, sizeof (char **));
			if (! start_on) {
				goto enomem;
			}

			start_on[start_on_size] = NULL;

			while (dbus_message_iter_get_arg_type (&start_on_iter) != DBUS_TYPE_INVALID) {
				DBusMessageIter start_on_element_iter;
				size_t          start_on_element_size;
				char ***        start_on_tmp;
				char **         start_on_element;

				/* Demarshal an array from the message */
				if (dbus_message_iter_get_arg_type (&start_on_iter) != DBUS_TYPE_ARRAY) {
					if (start_on)
						nih_free (start_on);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dbus_message_iter_recurse (&start_on_iter, &start_on_element_iter);

				start_on_element_size = 0;
				start_on_element = NULL;

				start_on_element = nih_alloc (start_on, sizeof (char *));
				if (! start_on_element) {
					if (start_on)
						nih_free (start_on);
					goto enomem;
				}

				start_on_element[start_on_element_size] = NULL;

				while (dbus_message_iter_get_arg_type (&start_on_element_iter) != DBUS_TYPE_INVALID) {
					const char *start_on_element_element_dbus;
					char **     start_on_element_tmp;
					char *      start_on_element_element;

					/* Demarshal a char * from the message */
					if (dbus_message_iter_get_arg_type (&start_on_element_iter) != DBUS_TYPE_STRING) {
						if (start_on_element)
							nih_free (start_on_element);
						if (start_on)
							nih_free (start_on);
						nih_free (*properties);
						*properties = NULL;
						dbus_message_unref (reply);
						nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
						                  _(NIH_DBUS_INVALID_ARGS_STR));
					}

					dbus_message_iter_get_basic (&start_on_element_iter, &start_on_element_element_dbus);

					start_on_element_element = nih_strdup (start_on_element, start_on_element_element_dbus);
					if (! start_on_element_element) {
						if (start_on_element)
							nih_free (start_on_element);
						if (start_on)
							nih_free (start_on);
						goto enomem;
					}

					dbus_message_iter_next (&start_on_element_iter);

					if (start_on_element_size + 2 > SIZE_MAX / sizeof (char *)) {
						if (start_on_element)
							nih_free (start_on_element);
						if (start_on)
							nih_free (start_on);
						nih_free (*properties);
						*properties = NULL;
						dbus_message_unref (reply);
						nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
						                  _(NIH_DBUS_INVALID_ARGS_STR));
					}

					start_on_element_tmp = nih_realloc (start_on_element, start_on, sizeof (char *) * (start_on_element_size + 2));
					if (! start_on_element_tmp) {
						if (start_on_element)
							nih_free (start_on_element);
						if (start_on)
							nih_free (start_on);
						goto enomem;
					}

					start_on_element = start_on_element_tmp;
					start_on_element[start_on_element_size] = start_on_element_element;
					start_on_element[start_on_element_size + 1] = NULL;

					start_on_element_size++;
				}

				dbus_message_iter_next (&start_on_iter);

				if (start_on_size + 2 > SIZE_MAX / sizeof (char **)) {
					if (start_on)
						nih_free (start_on);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				start_on_tmp = nih_realloc (start_on, *properties, sizeof (char **) * (start_on_size + 2));
				if (! start_on_tmp) {
					if (start_on)
						nih_free (start_on);
					goto enomem;
				}

				start_on = start_on_tmp;
				start_on[start_on_size] = start_on_element;
				start_on[start_on_size + 1] = NULL;

				start_on_size++;
			}

			dbus_message_iter_next (&variter);

			(*properties)->start_on = start_on;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "stop_on")) {
			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_recurse (&variter, &stop_on_iter);

			stop_on_size = 0;
			stop_on = NULL;

			stop_on = nih_alloc (*properties, sizeof (char **));
			if (! stop_on) {
				goto enomem;
			}

			stop_on[stop_on_size] = NULL;

			while (dbus_message_iter_get_arg_type (&stop_on_iter) != DBUS_TYPE_INVALID) {
				DBusMessageIter stop_on_element_iter;
				size_t          stop_on_element_size;
				char ***        stop_on_tmp;
				char **         stop_on_element;

				/* Demarshal an array from the message */
				if (dbus_message_iter_get_arg_type (&stop_on_iter) != DBUS_TYPE_ARRAY) {
					if (stop_on)
						nih_free (stop_on);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dbus_message_iter_recurse (&stop_on_iter, &stop_on_element_iter);

				stop_on_element_size = 0;
				stop_on_element = NULL;

				stop_on_element = nih_alloc (stop_on, sizeof (char *));
				if (! stop_on_element) {
					if (stop_on)
						nih_free (stop_on);
					goto enomem;
				}

				stop_on_element[stop_on_element_size] = NULL;

				while (dbus_message_iter_get_arg_type (&stop_on_element_iter) != DBUS_TYPE_INVALID) {
					const char *stop_on_element_element_dbus;
					char **     stop_on_element_tmp;
					char *      stop_on_element_element;

					/* Demarshal a char * from the message */
					if (dbus_message_iter_get_arg_type (&stop_on_element_iter) != DBUS_TYPE_STRING) {
						if (stop_on_element)
							nih_free (stop_on_element);
						if (stop_on)
							nih_free (stop_on);
						nih_free (*properties);
						*properties = NULL;
						dbus_message_unref (reply);
						nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
						                  _(NIH_DBUS_INVALID_ARGS_STR));
					}

					dbus_message_iter_get_basic (&stop_on_element_iter, &stop_on_element_element_dbus);

					stop_on_element_element = nih_strdup (stop_on_element, stop_on_element_element_dbus);
					if (! stop_on_element_element) {
						if (stop_on_element)
							nih_free (stop_on_element);
						if (stop_on)
							nih_free (stop_on);
						goto enomem;
					}

					dbus_message_iter_next (&stop_on_element_iter);

					if (stop_on_element_size + 2 > SIZE_MAX / sizeof (char *)) {
						if (stop_on_element)
							nih_free (stop_on_element);
						if (stop_on)
							nih_free (stop_on);
						nih_free (*properties);
						*properties = NULL;
						dbus_message_unref (reply);
						nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
						                  _(NIH_DBUS_INVALID_ARGS_STR));
					}

					stop_on_element_tmp = nih_realloc (stop_on_element, stop_on, sizeof (char *) * (stop_on_element_size + 2));
					if (! stop_on_element_tmp) {
						if (stop_on_element)
							nih_free (stop_on_element);
						if (stop_on)
							nih_free (stop_on);
						goto enomem;
					}

					stop_on_element = stop_on_element_tmp;
					stop_on_element[stop_on_element_size] = stop_on_element_element;
					stop_on_element[stop_on_element_size + 1] = NULL;

					stop_on_element_size++;
				}

				dbus_message_iter_next (&stop_on_iter);

				if (stop_on_size + 2 > SIZE_MAX / sizeof (char **)) {
					if (stop_on)
						nih_free (stop_on);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				stop_on_tmp = nih_realloc (stop_on, *properties, sizeof (char **) * (stop_on_size + 2));
				if (! stop_on_tmp) {
					if (stop_on)
						nih_free (stop_on);
					goto enomem;
				}

				stop_on = stop_on_tmp;
				stop_on[stop_on_size] = stop_on_element;
				stop_on[stop_on_size + 1] = NULL;

				stop_on_size++;
			}

			dbus_message_iter_next (&variter);

			(*properties)->stop_on = stop_on;

			nih_assert (++property_count);
		}

		if (! strcmp (property, "emits")) {
			/* Demarshal an array from the message */
			if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_ARRAY) {
				nih_free (*properties);
				*properties = NULL;
				dbus_message_unref (reply);
				nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
				                  _(NIH_DBUS_INVALID_ARGS_STR));
			}

			dbus_message_iter_recurse (&variter, &emits_iter);

			emits_size = 0;
			emits = NULL;

			emits = nih_alloc (*properties, sizeof (char *));
			if (! emits) {
				goto enomem;
			}

			emits[emits_size] = NULL;

			while (dbus_message_iter_get_arg_type (&emits_iter) != DBUS_TYPE_INVALID) {
				const char *emits_element_dbus;
				char **     emits_tmp;
				char *      emits_element;

				/* Demarshal a char * from the message */
				if (dbus_message_iter_get_arg_type (&emits_iter) != DBUS_TYPE_STRING) {
					if (emits)
						nih_free (emits);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				dbus_message_iter_get_basic (&emits_iter, &emits_element_dbus);

				emits_element = nih_strdup (emits, emits_element_dbus);
				if (! emits_element) {
					if (emits)
						nih_free (emits);
					goto enomem;
				}

				dbus_message_iter_next (&emits_iter);

				if (emits_size + 2 > SIZE_MAX / sizeof (char *)) {
					if (emits)
						nih_free (emits);
					nih_free (*properties);
					*properties = NULL;
					dbus_message_unref (reply);
					nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
					                  _(NIH_DBUS_INVALID_ARGS_STR));
				}

				emits_tmp = nih_realloc (emits, *properties, sizeof (char *) * (emits_size + 2));
				if (! emits_tmp) {
					if (emits)
						nih_free (emits);
					goto enomem;
				}

				emits = emits_tmp;
				emits[emits_size] = emits_element;
				emits[emits_size + 1] = NULL;

				emits_size++;
			}

			dbus_message_iter_next (&variter);

			(*properties)->emits = emits;

			nih_assert (++property_count);
		}

		dbus_message_iter_next (&dictiter);

		if (dbus_message_iter_get_arg_type (&dictiter) != DBUS_TYPE_INVALID) {
			nih_free (*properties);
			*properties = NULL;
			dbus_message_unref (reply);
			nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
			                  _(NIH_DBUS_INVALID_ARGS_STR));
		}

		dbus_message_iter_next (&arrayiter);
	enomem: __attribute__ ((unused));
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		nih_free (*properties);
		*properties = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	if (property_count < 8) {
		nih_free (*properties);
		*properties = NULL;
		dbus_message_unref (reply);
		nih_return_error (-1, NIH_DBUS_INVALID_ARGS,
		                  _(NIH_DBUS_INVALID_ARGS_STR));
	}

	dbus_message_unref (reply);

	return 0;
}
