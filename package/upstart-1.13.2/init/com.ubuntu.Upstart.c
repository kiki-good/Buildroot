/* upstart
 *
 * com.ubuntu.Upstart.c - auto-generated D-Bus bindings
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

#include "com.ubuntu.Upstart.h"


/* Prototypes for static functions */
static DBusHandlerResult control_com_ubuntu_Upstart0_6_ReloadConfiguration_method        (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult control_com_ubuntu_Upstart0_6_GetJobByName_method               (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult control_com_ubuntu_Upstart0_6_GetAllJobs_method                 (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult control_com_ubuntu_Upstart0_6_GetState_method                   (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult control_com_ubuntu_Upstart0_6_Restart_method                    (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult control_com_ubuntu_Upstart0_6_GetEnv_method                     (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult control_com_ubuntu_Upstart0_6_SetEnv_method                     (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult control_com_ubuntu_Upstart0_6_SetEnvList_method                 (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult control_com_ubuntu_Upstart0_6_UnsetEnv_method                   (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult control_com_ubuntu_Upstart0_6_UnsetEnvList_method               (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult control_com_ubuntu_Upstart0_6_ListEnv_method                    (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult control_com_ubuntu_Upstart0_6_ResetEnv_method                   (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult control_com_ubuntu_Upstart0_6_EmitEvent_method                  (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult control_com_ubuntu_Upstart0_6_EmitEventWithFile_method          (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult control_com_ubuntu_Upstart0_6_NotifyDiskWriteable_method        (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult control_com_ubuntu_Upstart0_6_NotifyDBusAddress_method          (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult control_com_ubuntu_Upstart0_6_NotifyCGroupManagerAddress_method (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult control_com_ubuntu_Upstart0_6_EndSession_method                 (NihDBusObject *object, NihDBusMessage *message);
static int               control_com_ubuntu_Upstart0_6_version_get                       (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               control_com_ubuntu_Upstart0_6_log_priority_get                  (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               control_com_ubuntu_Upstart0_6_log_priority_set                  (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);


/* Prototypes for externally implemented handler functions */
extern int control_reload_configuration          (void *data, NihDBusMessage *message)
	__attribute__ ((warn_unused_result));
extern int control_get_job_by_name               (void *data, NihDBusMessage *message, const char *name, char **job)
	__attribute__ ((warn_unused_result));
extern int control_get_all_jobs                  (void *data, NihDBusMessage *message, char ***jobs)
	__attribute__ ((warn_unused_result));
extern int control_get_state                     (void *data, NihDBusMessage *message, char **state)
	__attribute__ ((warn_unused_result));
extern int control_restart                       (void *data, NihDBusMessage *message)
	__attribute__ ((warn_unused_result));
extern int control_get_env                       (void *data, NihDBusMessage *message, char * const *job_details, const char *name, char **value)
	__attribute__ ((warn_unused_result));
extern int control_set_env                       (void *data, NihDBusMessage *message, char * const *job_details, const char *var, int replace)
	__attribute__ ((warn_unused_result));
extern int control_set_env_list                  (void *data, NihDBusMessage *message, char * const *job_details, char * const *vars, int replace)
	__attribute__ ((warn_unused_result));
extern int control_unset_env                     (void *data, NihDBusMessage *message, char * const *job_details, const char *name)
	__attribute__ ((warn_unused_result));
extern int control_unset_env_list                (void *data, NihDBusMessage *message, char * const *job_details, char * const *name)
	__attribute__ ((warn_unused_result));
extern int control_list_env                      (void *data, NihDBusMessage *message, char * const *job_details, char ***env)
	__attribute__ ((warn_unused_result));
extern int control_reset_env                     (void *data, NihDBusMessage *message, char * const *job_details)
	__attribute__ ((warn_unused_result));
extern int control_emit_event                    (void *data, NihDBusMessage *message, const char *name, char * const *env, int wait)
	__attribute__ ((warn_unused_result));
extern int control_emit_event_with_file          (void *data, NihDBusMessage *message, const char *name, char * const *env, int wait, int file)
	__attribute__ ((warn_unused_result));
extern int control_notify_disk_writeable         (void *data, NihDBusMessage *message)
	__attribute__ ((warn_unused_result));
extern int control_notify_dbus_address           (void *data, NihDBusMessage *message, const char *address)
	__attribute__ ((warn_unused_result));
extern int control_notify_cgroup_manager_address (void *data, NihDBusMessage *message, const char *address)
	__attribute__ ((warn_unused_result));
extern int control_end_session                   (void *data, NihDBusMessage *message)
	__attribute__ ((warn_unused_result));
extern int control_get_version                   (void *data, NihDBusMessage *message, char **value)
	__attribute__ ((warn_unused_result));
extern int control_get_log_priority              (void *data, NihDBusMessage *message, char **value)
	__attribute__ ((warn_unused_result));
extern int control_set_log_priority              (void *data, NihDBusMessage *message, const char *value)
	__attribute__ ((warn_unused_result));


static const NihDBusArg control_com_ubuntu_Upstart0_6_ReloadConfiguration_method_args[] = {
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_GetJobByName_method_args[] = {
	{ "name", "s", NIH_DBUS_ARG_IN  },
	{ "job",  "o", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_GetAllJobs_method_args[] = {
	{ "jobs", "ao", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_GetState_method_args[] = {
	{ "state", "s", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_Restart_method_args[] = {
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_GetEnv_method_args[] = {
	{ "job_details", "as", NIH_DBUS_ARG_IN  },
	{ "name",        "s",  NIH_DBUS_ARG_IN  },
	{ "value",       "s",  NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_SetEnv_method_args[] = {
	{ "job_details", "as", NIH_DBUS_ARG_IN  },
	{ "var",         "s",  NIH_DBUS_ARG_IN  },
	{ "replace",     "b",  NIH_DBUS_ARG_IN  },
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_SetEnvList_method_args[] = {
	{ "job_details", "as", NIH_DBUS_ARG_IN  },
	{ "vars",        "as", NIH_DBUS_ARG_IN  },
	{ "replace",     "b",  NIH_DBUS_ARG_IN  },
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_UnsetEnv_method_args[] = {
	{ "job_details", "as", NIH_DBUS_ARG_IN  },
	{ "name",        "s",  NIH_DBUS_ARG_IN  },
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_UnsetEnvList_method_args[] = {
	{ "job_details", "as", NIH_DBUS_ARG_IN  },
	{ "name",        "as", NIH_DBUS_ARG_IN  },
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_ListEnv_method_args[] = {
	{ "job_details", "as", NIH_DBUS_ARG_IN  },
	{ "env",         "as", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_ResetEnv_method_args[] = {
	{ "job_details", "as", NIH_DBUS_ARG_IN  },
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_EmitEvent_method_args[] = {
	{ "name", "s",  NIH_DBUS_ARG_IN  },
	{ "env",  "as", NIH_DBUS_ARG_IN  },
	{ "wait", "b",  NIH_DBUS_ARG_IN  },
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_EmitEventWithFile_method_args[] = {
	{ "name", "s",  NIH_DBUS_ARG_IN  },
	{ "env",  "as", NIH_DBUS_ARG_IN  },
	{ "wait", "b",  NIH_DBUS_ARG_IN  },
	{ "file", "h",  NIH_DBUS_ARG_IN  },
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_NotifyDiskWriteable_method_args[] = {
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_NotifyDBusAddress_method_args[] = {
	{ "address", "s", NIH_DBUS_ARG_IN  },
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_NotifyCGroupManagerAddress_method_args[] = {
	{ "address", "s", NIH_DBUS_ARG_IN  },
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_EndSession_method_args[] = {
	{ NULL }
};

static const NihDBusMethod control_com_ubuntu_Upstart0_6_methods[] = {
	{ "ReloadConfiguration",        control_com_ubuntu_Upstart0_6_ReloadConfiguration_method_args,        control_com_ubuntu_Upstart0_6_ReloadConfiguration_method        },
	{ "GetJobByName",               control_com_ubuntu_Upstart0_6_GetJobByName_method_args,               control_com_ubuntu_Upstart0_6_GetJobByName_method               },
	{ "GetAllJobs",                 control_com_ubuntu_Upstart0_6_GetAllJobs_method_args,                 control_com_ubuntu_Upstart0_6_GetAllJobs_method                 },
	{ "GetState",                   control_com_ubuntu_Upstart0_6_GetState_method_args,                   control_com_ubuntu_Upstart0_6_GetState_method                   },
	{ "Restart",                    control_com_ubuntu_Upstart0_6_Restart_method_args,                    control_com_ubuntu_Upstart0_6_Restart_method                    },
	{ "GetEnv",                     control_com_ubuntu_Upstart0_6_GetEnv_method_args,                     control_com_ubuntu_Upstart0_6_GetEnv_method                     },
	{ "SetEnv",                     control_com_ubuntu_Upstart0_6_SetEnv_method_args,                     control_com_ubuntu_Upstart0_6_SetEnv_method                     },
	{ "SetEnvList",                 control_com_ubuntu_Upstart0_6_SetEnvList_method_args,                 control_com_ubuntu_Upstart0_6_SetEnvList_method                 },
	{ "UnsetEnv",                   control_com_ubuntu_Upstart0_6_UnsetEnv_method_args,                   control_com_ubuntu_Upstart0_6_UnsetEnv_method                   },
	{ "UnsetEnvList",               control_com_ubuntu_Upstart0_6_UnsetEnvList_method_args,               control_com_ubuntu_Upstart0_6_UnsetEnvList_method               },
	{ "ListEnv",                    control_com_ubuntu_Upstart0_6_ListEnv_method_args,                    control_com_ubuntu_Upstart0_6_ListEnv_method                    },
	{ "ResetEnv",                   control_com_ubuntu_Upstart0_6_ResetEnv_method_args,                   control_com_ubuntu_Upstart0_6_ResetEnv_method                   },
	{ "EmitEvent",                  control_com_ubuntu_Upstart0_6_EmitEvent_method_args,                  control_com_ubuntu_Upstart0_6_EmitEvent_method                  },
	{ "EmitEventWithFile",          control_com_ubuntu_Upstart0_6_EmitEventWithFile_method_args,          control_com_ubuntu_Upstart0_6_EmitEventWithFile_method          },
	{ "NotifyDiskWriteable",        control_com_ubuntu_Upstart0_6_NotifyDiskWriteable_method_args,        control_com_ubuntu_Upstart0_6_NotifyDiskWriteable_method        },
	{ "NotifyDBusAddress",          control_com_ubuntu_Upstart0_6_NotifyDBusAddress_method_args,          control_com_ubuntu_Upstart0_6_NotifyDBusAddress_method          },
	{ "NotifyCGroupManagerAddress", control_com_ubuntu_Upstart0_6_NotifyCGroupManagerAddress_method_args, control_com_ubuntu_Upstart0_6_NotifyCGroupManagerAddress_method },
	{ "EndSession",                 control_com_ubuntu_Upstart0_6_EndSession_method_args,                 control_com_ubuntu_Upstart0_6_EndSession_method                 },
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_JobAdded_signal_args[] = {
	{ "job", "o", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_JobRemoved_signal_args[] = {
	{ "job", "o", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_EventEmitted_signal_args[] = {
	{ "name", "s",  NIH_DBUS_ARG_OUT },
	{ "env",  "as", NIH_DBUS_ARG_OUT },
	{ NULL }
};

static const NihDBusArg control_com_ubuntu_Upstart0_6_Restarted_signal_args[] = {
	{ NULL }
};

static const NihDBusSignal control_com_ubuntu_Upstart0_6_signals[] = {
	{ "JobAdded",     control_com_ubuntu_Upstart0_6_JobAdded_signal_args,     NULL },
	{ "JobRemoved",   control_com_ubuntu_Upstart0_6_JobRemoved_signal_args,   NULL },
	{ "EventEmitted", control_com_ubuntu_Upstart0_6_EventEmitted_signal_args, NULL },
	{ "Restarted",    control_com_ubuntu_Upstart0_6_Restarted_signal_args,    NULL },
	{ NULL }
};

static const NihDBusProperty control_com_ubuntu_Upstart0_6_properties[] = {
	{ "version",      "s", NIH_DBUS_READ,      control_com_ubuntu_Upstart0_6_version_get,      NULL                                           },
	{ "log_priority", "s", NIH_DBUS_READWRITE, control_com_ubuntu_Upstart0_6_log_priority_get, control_com_ubuntu_Upstart0_6_log_priority_set },
	{ NULL }
};

const NihDBusInterface control_com_ubuntu_Upstart0_6 = {
	"com.ubuntu.Upstart0_6",
	control_com_ubuntu_Upstart0_6_methods,
	control_com_ubuntu_Upstart0_6_signals,
	control_com_ubuntu_Upstart0_6_properties
};

const NihDBusInterface *control_interfaces[] = {
	&control_com_ubuntu_Upstart0_6,
	NULL
};


static DBusHandlerResult
control_com_ubuntu_Upstart0_6_ReloadConfiguration_method (NihDBusObject * object,
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
		                                "Invalid arguments to ReloadConfiguration method");
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
	if (control_reload_configuration (object->data, message) < 0) {
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

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
control_com_ubuntu_Upstart0_6_GetJobByName_method (NihDBusObject * object,
                                                   NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          name;
	const char *    name_dbus;
	char *          job;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to GetJobByName method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &name_dbus);

	name = nih_strdup (message, name_dbus);
	if (! name) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to GetJobByName method");
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
	if (control_get_job_by_name (object->data, message, name, &job) < 0) {
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

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_OBJECT_PATH, &job)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
control_com_ubuntu_Upstart0_6_GetAllJobs_method (NihDBusObject * object,
                                                 NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char **         jobs;
	DBusMessageIter jobs_iter;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to GetAllJobs method");
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
	if (control_get_all_jobs (object->data, message, &jobs) < 0) {
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

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal an array onto the message */
		if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "o", &jobs_iter)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}

		if (jobs) {
			for (size_t jobs_i = 0; jobs[jobs_i]; jobs_i++) {
				const char *jobs_element;

				jobs_element = jobs[jobs_i];

				/* Marshal a char * onto the message */
				if (! dbus_message_iter_append_basic (&jobs_iter, DBUS_TYPE_OBJECT_PATH, &jobs_element)) {
					dbus_message_iter_abandon_container (&iter, &jobs_iter);
					dbus_message_unref (reply);
					reply = NULL;
					goto enomem;
				}
			}
		}

		if (! dbus_message_iter_close_container (&iter, &jobs_iter)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
control_com_ubuntu_Upstart0_6_GetState_method (NihDBusObject * object,
                                               NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          state;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to GetState method");
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
	if (control_get_state (object->data, message, &state) < 0) {
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

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &state)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
control_com_ubuntu_Upstart0_6_Restart_method (NihDBusObject * object,
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
	if (control_restart (object->data, message) < 0) {
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
control_restart_reply (NihDBusMessage *message)
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
control_com_ubuntu_Upstart0_6_GetEnv_method (NihDBusObject * object,
                                             NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char **         job_details;
	DBusMessageIter job_details_iter;
	size_t          job_details_size;
	char *          name;
	const char *    name_dbus;
	char *          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to GetEnv method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &job_details_iter);

	job_details_size = 0;
	job_details = NULL;

	job_details = nih_alloc (message, sizeof (char *));
	if (! job_details) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	job_details[job_details_size] = NULL;

	while (dbus_message_iter_get_arg_type (&job_details_iter) != DBUS_TYPE_INVALID) {
		const char *job_details_element_dbus;
		char **     job_details_tmp;
		char *      job_details_element;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&job_details_iter) != DBUS_TYPE_STRING) {
			if (job_details)
				nih_free (job_details);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to GetEnv method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_get_basic (&job_details_iter, &job_details_element_dbus);

		job_details_element = nih_strdup (job_details, job_details_element_dbus);
		if (! job_details_element) {
			if (job_details)
				nih_free (job_details);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_iter_next (&job_details_iter);

		if (job_details_size + 2 > SIZE_MAX / sizeof (char *)) {
			if (job_details)
				nih_free (job_details);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to GetEnv method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		job_details_tmp = nih_realloc (job_details, message, sizeof (char *) * (job_details_size + 2));
		if (! job_details_tmp) {
			if (job_details)
				nih_free (job_details);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		job_details = job_details_tmp;
		job_details[job_details_size] = job_details_element;
		job_details[job_details_size + 1] = NULL;

		job_details_size++;
	}

	dbus_message_iter_next (&iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to GetEnv method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &name_dbus);

	name = nih_strdup (message, name_dbus);
	if (! name) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to GetEnv method");
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
	if (control_get_env (object->data, message, job_details, name, &value) < 0) {
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

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal a char * onto the message */
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &value)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
control_com_ubuntu_Upstart0_6_SetEnv_method (NihDBusObject * object,
                                             NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char **         job_details;
	DBusMessageIter job_details_iter;
	size_t          job_details_size;
	char *          var;
	const char *    var_dbus;
	int             replace;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to SetEnv method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &job_details_iter);

	job_details_size = 0;
	job_details = NULL;

	job_details = nih_alloc (message, sizeof (char *));
	if (! job_details) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	job_details[job_details_size] = NULL;

	while (dbus_message_iter_get_arg_type (&job_details_iter) != DBUS_TYPE_INVALID) {
		const char *job_details_element_dbus;
		char **     job_details_tmp;
		char *      job_details_element;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&job_details_iter) != DBUS_TYPE_STRING) {
			if (job_details)
				nih_free (job_details);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to SetEnv method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_get_basic (&job_details_iter, &job_details_element_dbus);

		job_details_element = nih_strdup (job_details, job_details_element_dbus);
		if (! job_details_element) {
			if (job_details)
				nih_free (job_details);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_iter_next (&job_details_iter);

		if (job_details_size + 2 > SIZE_MAX / sizeof (char *)) {
			if (job_details)
				nih_free (job_details);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to SetEnv method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		job_details_tmp = nih_realloc (job_details, message, sizeof (char *) * (job_details_size + 2));
		if (! job_details_tmp) {
			if (job_details)
				nih_free (job_details);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		job_details = job_details_tmp;
		job_details[job_details_size] = job_details_element;
		job_details[job_details_size + 1] = NULL;

		job_details_size++;
	}

	dbus_message_iter_next (&iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to SetEnv method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &var_dbus);

	var = nih_strdup (message, var_dbus);
	if (! var) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	/* Demarshal a int from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_BOOLEAN) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to SetEnv method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &replace);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to SetEnv method");
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
	if (control_set_env (object->data, message, job_details, var, replace) < 0) {
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

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
control_com_ubuntu_Upstart0_6_SetEnvList_method (NihDBusObject * object,
                                                 NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char **         job_details;
	DBusMessageIter job_details_iter;
	size_t          job_details_size;
	char **         vars;
	DBusMessageIter vars_iter;
	size_t          vars_size;
	int             replace;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to SetEnvList method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &job_details_iter);

	job_details_size = 0;
	job_details = NULL;

	job_details = nih_alloc (message, sizeof (char *));
	if (! job_details) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	job_details[job_details_size] = NULL;

	while (dbus_message_iter_get_arg_type (&job_details_iter) != DBUS_TYPE_INVALID) {
		const char *job_details_element_dbus;
		char **     job_details_tmp;
		char *      job_details_element;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&job_details_iter) != DBUS_TYPE_STRING) {
			if (job_details)
				nih_free (job_details);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to SetEnvList method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_get_basic (&job_details_iter, &job_details_element_dbus);

		job_details_element = nih_strdup (job_details, job_details_element_dbus);
		if (! job_details_element) {
			if (job_details)
				nih_free (job_details);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_iter_next (&job_details_iter);

		if (job_details_size + 2 > SIZE_MAX / sizeof (char *)) {
			if (job_details)
				nih_free (job_details);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to SetEnvList method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		job_details_tmp = nih_realloc (job_details, message, sizeof (char *) * (job_details_size + 2));
		if (! job_details_tmp) {
			if (job_details)
				nih_free (job_details);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		job_details = job_details_tmp;
		job_details[job_details_size] = job_details_element;
		job_details[job_details_size + 1] = NULL;

		job_details_size++;
	}

	dbus_message_iter_next (&iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to SetEnvList method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &vars_iter);

	vars_size = 0;
	vars = NULL;

	vars = nih_alloc (message, sizeof (char *));
	if (! vars) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	vars[vars_size] = NULL;

	while (dbus_message_iter_get_arg_type (&vars_iter) != DBUS_TYPE_INVALID) {
		const char *vars_element_dbus;
		char **     vars_tmp;
		char *      vars_element;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&vars_iter) != DBUS_TYPE_STRING) {
			if (vars)
				nih_free (vars);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to SetEnvList method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_get_basic (&vars_iter, &vars_element_dbus);

		vars_element = nih_strdup (vars, vars_element_dbus);
		if (! vars_element) {
			if (vars)
				nih_free (vars);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_iter_next (&vars_iter);

		if (vars_size + 2 > SIZE_MAX / sizeof (char *)) {
			if (vars)
				nih_free (vars);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to SetEnvList method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		vars_tmp = nih_realloc (vars, message, sizeof (char *) * (vars_size + 2));
		if (! vars_tmp) {
			if (vars)
				nih_free (vars);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		vars = vars_tmp;
		vars[vars_size] = vars_element;
		vars[vars_size + 1] = NULL;

		vars_size++;
	}

	dbus_message_iter_next (&iter);

	/* Demarshal a int from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_BOOLEAN) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to SetEnvList method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &replace);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to SetEnvList method");
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
	if (control_set_env_list (object->data, message, job_details, vars, replace) < 0) {
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

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
control_com_ubuntu_Upstart0_6_UnsetEnv_method (NihDBusObject * object,
                                               NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char **         job_details;
	DBusMessageIter job_details_iter;
	size_t          job_details_size;
	char *          name;
	const char *    name_dbus;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to UnsetEnv method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &job_details_iter);

	job_details_size = 0;
	job_details = NULL;

	job_details = nih_alloc (message, sizeof (char *));
	if (! job_details) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	job_details[job_details_size] = NULL;

	while (dbus_message_iter_get_arg_type (&job_details_iter) != DBUS_TYPE_INVALID) {
		const char *job_details_element_dbus;
		char **     job_details_tmp;
		char *      job_details_element;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&job_details_iter) != DBUS_TYPE_STRING) {
			if (job_details)
				nih_free (job_details);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to UnsetEnv method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_get_basic (&job_details_iter, &job_details_element_dbus);

		job_details_element = nih_strdup (job_details, job_details_element_dbus);
		if (! job_details_element) {
			if (job_details)
				nih_free (job_details);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_iter_next (&job_details_iter);

		if (job_details_size + 2 > SIZE_MAX / sizeof (char *)) {
			if (job_details)
				nih_free (job_details);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to UnsetEnv method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		job_details_tmp = nih_realloc (job_details, message, sizeof (char *) * (job_details_size + 2));
		if (! job_details_tmp) {
			if (job_details)
				nih_free (job_details);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		job_details = job_details_tmp;
		job_details[job_details_size] = job_details_element;
		job_details[job_details_size + 1] = NULL;

		job_details_size++;
	}

	dbus_message_iter_next (&iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to UnsetEnv method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &name_dbus);

	name = nih_strdup (message, name_dbus);
	if (! name) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to UnsetEnv method");
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
	if (control_unset_env (object->data, message, job_details, name) < 0) {
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

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
control_com_ubuntu_Upstart0_6_UnsetEnvList_method (NihDBusObject * object,
                                                   NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char **         job_details;
	DBusMessageIter job_details_iter;
	size_t          job_details_size;
	char **         name;
	DBusMessageIter name_iter;
	size_t          name_size;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to UnsetEnvList method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &job_details_iter);

	job_details_size = 0;
	job_details = NULL;

	job_details = nih_alloc (message, sizeof (char *));
	if (! job_details) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	job_details[job_details_size] = NULL;

	while (dbus_message_iter_get_arg_type (&job_details_iter) != DBUS_TYPE_INVALID) {
		const char *job_details_element_dbus;
		char **     job_details_tmp;
		char *      job_details_element;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&job_details_iter) != DBUS_TYPE_STRING) {
			if (job_details)
				nih_free (job_details);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to UnsetEnvList method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_get_basic (&job_details_iter, &job_details_element_dbus);

		job_details_element = nih_strdup (job_details, job_details_element_dbus);
		if (! job_details_element) {
			if (job_details)
				nih_free (job_details);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_iter_next (&job_details_iter);

		if (job_details_size + 2 > SIZE_MAX / sizeof (char *)) {
			if (job_details)
				nih_free (job_details);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to UnsetEnvList method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		job_details_tmp = nih_realloc (job_details, message, sizeof (char *) * (job_details_size + 2));
		if (! job_details_tmp) {
			if (job_details)
				nih_free (job_details);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		job_details = job_details_tmp;
		job_details[job_details_size] = job_details_element;
		job_details[job_details_size + 1] = NULL;

		job_details_size++;
	}

	dbus_message_iter_next (&iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to UnsetEnvList method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &name_iter);

	name_size = 0;
	name = NULL;

	name = nih_alloc (message, sizeof (char *));
	if (! name) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	name[name_size] = NULL;

	while (dbus_message_iter_get_arg_type (&name_iter) != DBUS_TYPE_INVALID) {
		const char *name_element_dbus;
		char **     name_tmp;
		char *      name_element;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&name_iter) != DBUS_TYPE_STRING) {
			if (name)
				nih_free (name);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to UnsetEnvList method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_get_basic (&name_iter, &name_element_dbus);

		name_element = nih_strdup (name, name_element_dbus);
		if (! name_element) {
			if (name)
				nih_free (name);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_iter_next (&name_iter);

		if (name_size + 2 > SIZE_MAX / sizeof (char *)) {
			if (name)
				nih_free (name);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to UnsetEnvList method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		name_tmp = nih_realloc (name, message, sizeof (char *) * (name_size + 2));
		if (! name_tmp) {
			if (name)
				nih_free (name);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		name = name_tmp;
		name[name_size] = name_element;
		name[name_size + 1] = NULL;

		name_size++;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to UnsetEnvList method");
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
	if (control_unset_env_list (object->data, message, job_details, name) < 0) {
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

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
control_com_ubuntu_Upstart0_6_ListEnv_method (NihDBusObject * object,
                                              NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char **         job_details;
	DBusMessageIter job_details_iter;
	size_t          job_details_size;
	char **         env;
	DBusMessageIter env_iter;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to ListEnv method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &job_details_iter);

	job_details_size = 0;
	job_details = NULL;

	job_details = nih_alloc (message, sizeof (char *));
	if (! job_details) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	job_details[job_details_size] = NULL;

	while (dbus_message_iter_get_arg_type (&job_details_iter) != DBUS_TYPE_INVALID) {
		const char *job_details_element_dbus;
		char **     job_details_tmp;
		char *      job_details_element;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&job_details_iter) != DBUS_TYPE_STRING) {
			if (job_details)
				nih_free (job_details);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to ListEnv method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_get_basic (&job_details_iter, &job_details_element_dbus);

		job_details_element = nih_strdup (job_details, job_details_element_dbus);
		if (! job_details_element) {
			if (job_details)
				nih_free (job_details);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_iter_next (&job_details_iter);

		if (job_details_size + 2 > SIZE_MAX / sizeof (char *)) {
			if (job_details)
				nih_free (job_details);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to ListEnv method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		job_details_tmp = nih_realloc (job_details, message, sizeof (char *) * (job_details_size + 2));
		if (! job_details_tmp) {
			if (job_details)
				nih_free (job_details);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		job_details = job_details_tmp;
		job_details[job_details_size] = job_details_element;
		job_details[job_details_size + 1] = NULL;

		job_details_size++;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to ListEnv method");
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
	if (control_list_env (object->data, message, job_details, &env) < 0) {
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

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);

		/* Marshal an array onto the message */
		if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "s", &env_iter)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}

		if (env) {
			for (size_t env_i = 0; env[env_i]; env_i++) {
				const char *env_element;

				env_element = env[env_i];

				/* Marshal a char * onto the message */
				if (! dbus_message_iter_append_basic (&env_iter, DBUS_TYPE_STRING, &env_element)) {
					dbus_message_iter_abandon_container (&iter, &env_iter);
					dbus_message_unref (reply);
					reply = NULL;
					goto enomem;
				}
			}
		}

		if (! dbus_message_iter_close_container (&iter, &env_iter)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
control_com_ubuntu_Upstart0_6_ResetEnv_method (NihDBusObject * object,
                                               NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char **         job_details;
	DBusMessageIter job_details_iter;
	size_t          job_details_size;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to ResetEnv method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &job_details_iter);

	job_details_size = 0;
	job_details = NULL;

	job_details = nih_alloc (message, sizeof (char *));
	if (! job_details) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	job_details[job_details_size] = NULL;

	while (dbus_message_iter_get_arg_type (&job_details_iter) != DBUS_TYPE_INVALID) {
		const char *job_details_element_dbus;
		char **     job_details_tmp;
		char *      job_details_element;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&job_details_iter) != DBUS_TYPE_STRING) {
			if (job_details)
				nih_free (job_details);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to ResetEnv method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_get_basic (&job_details_iter, &job_details_element_dbus);

		job_details_element = nih_strdup (job_details, job_details_element_dbus);
		if (! job_details_element) {
			if (job_details)
				nih_free (job_details);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_iter_next (&job_details_iter);

		if (job_details_size + 2 > SIZE_MAX / sizeof (char *)) {
			if (job_details)
				nih_free (job_details);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to ResetEnv method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		job_details_tmp = nih_realloc (job_details, message, sizeof (char *) * (job_details_size + 2));
		if (! job_details_tmp) {
			if (job_details)
				nih_free (job_details);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		job_details = job_details_tmp;
		job_details[job_details_size] = job_details_element;
		job_details[job_details_size + 1] = NULL;

		job_details_size++;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to ResetEnv method");
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
	if (control_reset_env (object->data, message, job_details) < 0) {
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

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
control_com_ubuntu_Upstart0_6_EmitEvent_method (NihDBusObject * object,
                                                NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          name;
	const char *    name_dbus;
	char **         env;
	DBusMessageIter env_iter;
	size_t          env_size;
	int             wait;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to EmitEvent method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &name_dbus);

	name = nih_strdup (message, name_dbus);
	if (! name) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to EmitEvent method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &env_iter);

	env_size = 0;
	env = NULL;

	env = nih_alloc (message, sizeof (char *));
	if (! env) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	env[env_size] = NULL;

	while (dbus_message_iter_get_arg_type (&env_iter) != DBUS_TYPE_INVALID) {
		const char *env_element_dbus;
		char **     env_tmp;
		char *      env_element;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&env_iter) != DBUS_TYPE_STRING) {
			if (env)
				nih_free (env);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to EmitEvent method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_get_basic (&env_iter, &env_element_dbus);

		env_element = nih_strdup (env, env_element_dbus);
		if (! env_element) {
			if (env)
				nih_free (env);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_iter_next (&env_iter);

		if (env_size + 2 > SIZE_MAX / sizeof (char *)) {
			if (env)
				nih_free (env);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to EmitEvent method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		env_tmp = nih_realloc (env, message, sizeof (char *) * (env_size + 2));
		if (! env_tmp) {
			if (env)
				nih_free (env);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		env = env_tmp;
		env[env_size] = env_element;
		env[env_size + 1] = NULL;

		env_size++;
	}

	dbus_message_iter_next (&iter);

	/* Demarshal a int from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_BOOLEAN) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to EmitEvent method");
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
		                                "Invalid arguments to EmitEvent method");
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
	if (control_emit_event (object->data, message, name, env, wait) < 0) {
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
control_emit_event_reply (NihDBusMessage *message)
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
control_com_ubuntu_Upstart0_6_EmitEventWithFile_method (NihDBusObject * object,
                                                        NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          name;
	const char *    name_dbus;
	char **         env;
	DBusMessageIter env_iter;
	size_t          env_size;
	int             wait;
	int             file;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to EmitEventWithFile method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &name_dbus);

	name = nih_strdup (message, name_dbus);
	if (! name) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to EmitEventWithFile method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_recurse (&iter, &env_iter);

	env_size = 0;
	env = NULL;

	env = nih_alloc (message, sizeof (char *));
	if (! env) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	env[env_size] = NULL;

	while (dbus_message_iter_get_arg_type (&env_iter) != DBUS_TYPE_INVALID) {
		const char *env_element_dbus;
		char **     env_tmp;
		char *      env_element;

		/* Demarshal a char * from the message */
		if (dbus_message_iter_get_arg_type (&env_iter) != DBUS_TYPE_STRING) {
			if (env)
				nih_free (env);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to EmitEventWithFile method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		dbus_message_iter_get_basic (&env_iter, &env_element_dbus);

		env_element = nih_strdup (env, env_element_dbus);
		if (! env_element) {
			if (env)
				nih_free (env);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_iter_next (&env_iter);

		if (env_size + 2 > SIZE_MAX / sizeof (char *)) {
			if (env)
				nih_free (env);
			reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
			                                "Invalid arguments to EmitEventWithFile method");
			if (! reply)
				return DBUS_HANDLER_RESULT_NEED_MEMORY;

			if (! dbus_connection_send (message->connection, reply, NULL)) {
				dbus_message_unref (reply);
				return DBUS_HANDLER_RESULT_NEED_MEMORY;
			}

			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_HANDLED;
		}

		env_tmp = nih_realloc (env, message, sizeof (char *) * (env_size + 2));
		if (! env_tmp) {
			if (env)
				nih_free (env);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		env = env_tmp;
		env[env_size] = env_element;
		env[env_size + 1] = NULL;

		env_size++;
	}

	dbus_message_iter_next (&iter);

	/* Demarshal a int from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_BOOLEAN) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to EmitEventWithFile method");
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

	/* Demarshal a int from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_UNIX_FD) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to EmitEventWithFile method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &file);

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to EmitEventWithFile method");
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
	if (control_emit_event_with_file (object->data, message, name, env, wait, file) < 0) {
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
control_emit_event_with_file_reply (NihDBusMessage *message)
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
control_com_ubuntu_Upstart0_6_NotifyDiskWriteable_method (NihDBusObject * object,
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
		                                "Invalid arguments to NotifyDiskWriteable method");
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
	if (control_notify_disk_writeable (object->data, message) < 0) {
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

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
control_com_ubuntu_Upstart0_6_NotifyDBusAddress_method (NihDBusObject * object,
                                                        NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          address;
	const char *    address_dbus;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to NotifyDBusAddress method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &address_dbus);

	address = nih_strdup (message, address_dbus);
	if (! address) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to NotifyDBusAddress method");
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
	if (control_notify_dbus_address (object->data, message, address) < 0) {
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

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
control_com_ubuntu_Upstart0_6_NotifyCGroupManagerAddress_method (NihDBusObject * object,
                                                                 NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          address;
	const char *    address_dbus;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to NotifyCGroupManagerAddress method");
		if (! reply)
			return DBUS_HANDLER_RESULT_NEED_MEMORY;

		if (! dbus_connection_send (message->connection, reply, NULL)) {
			dbus_message_unref (reply);
			return DBUS_HANDLER_RESULT_NEED_MEMORY;
		}

		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	}

	dbus_message_iter_get_basic (&iter, &address_dbus);

	address = nih_strdup (message, address_dbus);
	if (! address) {
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	dbus_message_iter_next (&iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to NotifyCGroupManagerAddress method");
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
	if (control_notify_cgroup_manager_address (object->data, message, address) < 0) {
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

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


static DBusHandlerResult
control_com_ubuntu_Upstart0_6_EndSession_method (NihDBusObject * object,
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
		                                "Invalid arguments to EndSession method");
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
	if (control_end_session (object->data, message) < 0) {
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

	/* If the sender doesn't care about a reply, don't bother wasting
	 * effort constructing and sending one.
	 */
	if (dbus_message_get_no_reply (message->message))
		return DBUS_HANDLER_RESULT_HANDLED;

	do {
		__label__ enomem;

		/* Construct the reply message. */
		reply = dbus_message_new_method_return (message->message);
		if (! reply)
			goto enomem;

		dbus_message_iter_init_append (reply, &iter);
	enomem: __attribute__ ((unused));
	} while (! reply);

	/* Send the reply, appending it to the outgoing queue. */
	NIH_MUST (dbus_connection_send (message->connection, reply, NULL));

	dbus_message_unref (reply);

	return DBUS_HANDLER_RESULT_HANDLED;
}


int
control_emit_job_added (DBusConnection *connection,
                        const char *    origin_path,
                        const char *    job)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);
	nih_assert (job != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.ubuntu.Upstart0_6", "JobAdded");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_OBJECT_PATH, &job)) {
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
control_emit_job_removed (DBusConnection *connection,
                          const char *    origin_path,
                          const char *    job)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);
	nih_assert (job != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.ubuntu.Upstart0_6", "JobRemoved");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_OBJECT_PATH, &job)) {
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
control_emit_event_emitted (DBusConnection *connection,
                            const char *    origin_path,
                            const char *    name,
                            char * const *  env)
{
	DBusMessage *   signal;
	DBusMessageIter iter;
	DBusMessageIter env_iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);
	nih_assert (name != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.ubuntu.Upstart0_6", "EventEmitted");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &name)) {
		dbus_message_unref (signal);
		return -1;
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "s", &env_iter)) {
		dbus_message_unref (signal);
		return -1;
	}

	if (env) {
		for (size_t env_i = 0; env[env_i]; env_i++) {
			const char *env_element;

			env_element = env[env_i];

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&env_iter, DBUS_TYPE_STRING, &env_element)) {
				dbus_message_iter_abandon_container (&iter, &env_iter);
				dbus_message_unref (signal);
				return -1;
			}
		}
	}

	if (! dbus_message_iter_close_container (&iter, &env_iter)) {
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
control_emit_restarted (DBusConnection *connection,
                        const char *    origin_path)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.ubuntu.Upstart0_6", "Restarted");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Send the signal, appending it to the outgoing queue. */
	if (! dbus_connection_send (connection, signal, NULL)) {
		dbus_message_unref (signal);
		return -1;
	}

	dbus_message_unref (signal);

	return 0;
}


static int
control_com_ubuntu_Upstart0_6_version_get (NihDBusObject *  object,
                                           NihDBusMessage * message,
                                           DBusMessageIter *iter)
{
	DBusMessageIter variter;
	char *          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (control_get_version (object->data, message, &value) < 0)
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
control_com_ubuntu_Upstart0_6_log_priority_get (NihDBusObject *  object,
                                                NihDBusMessage * message,
                                                DBusMessageIter *iter)
{
	DBusMessageIter variter;
	char *          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (control_get_log_priority (object->data, message, &value) < 0)
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
control_com_ubuntu_Upstart0_6_log_priority_set (NihDBusObject *  object,
                                                NihDBusMessage * message,
                                                DBusMessageIter *iter)
{
	DBusMessageIter variter;
	const char *    value_dbus;
	char *          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Recurse into the variant */
	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_VARIANT) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to log_priority property");
		return -1;
	}

	dbus_message_iter_recurse (iter, &variter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&variter) != DBUS_TYPE_STRING) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to log_priority property");
		return -1;
	}

	dbus_message_iter_get_basic (&variter, &value_dbus);

	value = nih_strdup (message, value_dbus);
	if (! value) {
		nih_error_raise_no_memory ();
		return -1;
	}

	dbus_message_iter_next (&variter);

	dbus_message_iter_next (iter);

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_INVALID) {
		nih_dbus_error_raise_printf (DBUS_ERROR_INVALID_ARGS,
		                             "Invalid arguments to log_priority property");
		return -1;
	}

	/* Call the handler function */
	if (control_set_log_priority (object->data, message, value) < 0)
		return -1;

	return 0;
}
