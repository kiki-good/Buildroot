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
#include <nih-dbus/dbus_object.h>
#include <nih-dbus/errors.h>

#include "com.ubuntu.Upstart.Job.h"


/* Prototypes for static functions */
static DBusHandlerResult job_class_com_ubuntu_Upstart0_6_Job_GetInstance_method       (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult job_class_com_ubuntu_Upstart0_6_Job_GetInstanceByName_method (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult job_class_com_ubuntu_Upstart0_6_Job_GetAllInstances_method   (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult job_class_com_ubuntu_Upstart0_6_Job_Start_method             (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult job_class_com_ubuntu_Upstart0_6_Job_Stop_method              (NihDBusObject *object, NihDBusMessage *message);
static DBusHandlerResult job_class_com_ubuntu_Upstart0_6_Job_Restart_method           (NihDBusObject *object, NihDBusMessage *message);
static int               job_class_com_ubuntu_Upstart0_6_Job_name_get                 (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               job_class_com_ubuntu_Upstart0_6_Job_description_get          (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               job_class_com_ubuntu_Upstart0_6_Job_author_get               (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               job_class_com_ubuntu_Upstart0_6_Job_version_get              (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               job_class_com_ubuntu_Upstart0_6_Job_usage_get                (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               job_class_com_ubuntu_Upstart0_6_Job_start_on_get             (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               job_class_com_ubuntu_Upstart0_6_Job_stop_on_get              (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);
static int               job_class_com_ubuntu_Upstart0_6_Job_emits_get                (NihDBusObject *object, NihDBusMessage *message, DBusMessageIter *iter);


/* Prototypes for externally implemented handler functions */
extern int job_class_get_instance         (void *data, NihDBusMessage *message, char * const *env, char **instance)
	__attribute__ ((warn_unused_result));
extern int job_class_get_instance_by_name (void *data, NihDBusMessage *message, const char *name, char **instance)
	__attribute__ ((warn_unused_result));
extern int job_class_get_all_instances    (void *data, NihDBusMessage *message, char ***instances)
	__attribute__ ((warn_unused_result));
extern int job_class_start                (void *data, NihDBusMessage *message, char * const *env, int wait)
	__attribute__ ((warn_unused_result));
extern int job_class_stop                 (void *data, NihDBusMessage *message, char * const *env, int wait)
	__attribute__ ((warn_unused_result));
extern int job_class_restart              (void *data, NihDBusMessage *message, char * const *env, int wait)
	__attribute__ ((warn_unused_result));
extern int job_class_get_name             (void *data, NihDBusMessage *message, char **value)
	__attribute__ ((warn_unused_result));
extern int job_class_get_description      (void *data, NihDBusMessage *message, char **value)
	__attribute__ ((warn_unused_result));
extern int job_class_get_author           (void *data, NihDBusMessage *message, char **value)
	__attribute__ ((warn_unused_result));
extern int job_class_get_version          (void *data, NihDBusMessage *message, char **value)
	__attribute__ ((warn_unused_result));
extern int job_class_get_usage            (void *data, NihDBusMessage *message, char **value)
	__attribute__ ((warn_unused_result));
extern int job_class_get_start_on         (void *data, NihDBusMessage *message, char ****value)
	__attribute__ ((warn_unused_result));
extern int job_class_get_stop_on          (void *data, NihDBusMessage *message, char ****value)
	__attribute__ ((warn_unused_result));
extern int job_class_get_emits            (void *data, NihDBusMessage *message, char ***value)
	__attribute__ ((warn_unused_result));


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
	{ "GetInstance",       job_class_com_ubuntu_Upstart0_6_Job_GetInstance_method_args,       job_class_com_ubuntu_Upstart0_6_Job_GetInstance_method       },
	{ "GetInstanceByName", job_class_com_ubuntu_Upstart0_6_Job_GetInstanceByName_method_args, job_class_com_ubuntu_Upstart0_6_Job_GetInstanceByName_method },
	{ "GetAllInstances",   job_class_com_ubuntu_Upstart0_6_Job_GetAllInstances_method_args,   job_class_com_ubuntu_Upstart0_6_Job_GetAllInstances_method   },
	{ "Start",             job_class_com_ubuntu_Upstart0_6_Job_Start_method_args,             job_class_com_ubuntu_Upstart0_6_Job_Start_method             },
	{ "Stop",              job_class_com_ubuntu_Upstart0_6_Job_Stop_method_args,              job_class_com_ubuntu_Upstart0_6_Job_Stop_method              },
	{ "Restart",           job_class_com_ubuntu_Upstart0_6_Job_Restart_method_args,           job_class_com_ubuntu_Upstart0_6_Job_Restart_method           },
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
	{ "InstanceAdded",   job_class_com_ubuntu_Upstart0_6_Job_InstanceAdded_signal_args,   NULL },
	{ "InstanceRemoved", job_class_com_ubuntu_Upstart0_6_Job_InstanceRemoved_signal_args, NULL },
	{ NULL }
};

static const NihDBusProperty job_class_com_ubuntu_Upstart0_6_Job_properties[] = {
	{ "name",        "s",   NIH_DBUS_READ, job_class_com_ubuntu_Upstart0_6_Job_name_get,        NULL },
	{ "description", "s",   NIH_DBUS_READ, job_class_com_ubuntu_Upstart0_6_Job_description_get, NULL },
	{ "author",      "s",   NIH_DBUS_READ, job_class_com_ubuntu_Upstart0_6_Job_author_get,      NULL },
	{ "version",     "s",   NIH_DBUS_READ, job_class_com_ubuntu_Upstart0_6_Job_version_get,     NULL },
	{ "usage",       "s",   NIH_DBUS_READ, job_class_com_ubuntu_Upstart0_6_Job_usage_get,       NULL },
	{ "start_on",    "aas", NIH_DBUS_READ, job_class_com_ubuntu_Upstart0_6_Job_start_on_get,    NULL },
	{ "stop_on",     "aas", NIH_DBUS_READ, job_class_com_ubuntu_Upstart0_6_Job_stop_on_get,     NULL },
	{ "emits",       "as",  NIH_DBUS_READ, job_class_com_ubuntu_Upstart0_6_Job_emits_get,       NULL },
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


static DBusHandlerResult
job_class_com_ubuntu_Upstart0_6_Job_GetInstance_method (NihDBusObject * object,
                                                        NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char **         env;
	DBusMessageIter env_iter;
	size_t          env_size;
	char *          instance;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to GetInstance method");
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
			                                "Invalid arguments to GetInstance method");
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
			                                "Invalid arguments to GetInstance method");
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

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to GetInstance method");
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
	if (job_class_get_instance (object->data, message, env, &instance) < 0) {
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
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_OBJECT_PATH, &instance)) {
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
job_class_com_ubuntu_Upstart0_6_Job_GetInstanceByName_method (NihDBusObject * object,
                                                              NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char *          name;
	const char *    name_dbus;
	char *          instance;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	/* Demarshal a char * from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_STRING) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to GetInstanceByName method");
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
		                                "Invalid arguments to GetInstanceByName method");
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
	if (job_class_get_instance_by_name (object->data, message, name, &instance) < 0) {
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
		if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_OBJECT_PATH, &instance)) {
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
job_class_com_ubuntu_Upstart0_6_Job_GetAllInstances_method (NihDBusObject * object,
                                                            NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
	char **         instances;
	DBusMessageIter instances_iter;

	nih_assert (object != NULL);
	nih_assert (message != NULL);

	/* Iterate the arguments to the message and demarshal into arguments
	 * for our own function call.
	 */
	dbus_message_iter_init (message->message, &iter);

	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_INVALID) {
		reply = dbus_message_new_error (message->message, DBUS_ERROR_INVALID_ARGS,
		                                "Invalid arguments to GetAllInstances method");
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
	if (job_class_get_all_instances (object->data, message, &instances) < 0) {
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
		if (! dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "o", &instances_iter)) {
			dbus_message_unref (reply);
			reply = NULL;
			goto enomem;
		}

		if (instances) {
			for (size_t instances_i = 0; instances[instances_i]; instances_i++) {
				const char *instances_element;

				instances_element = instances[instances_i];

				/* Marshal a char * onto the message */
				if (! dbus_message_iter_append_basic (&instances_iter, DBUS_TYPE_OBJECT_PATH, &instances_element)) {
					dbus_message_iter_abandon_container (&iter, &instances_iter);
					dbus_message_unref (reply);
					reply = NULL;
					goto enomem;
				}
			}
		}

		if (! dbus_message_iter_close_container (&iter, &instances_iter)) {
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
job_class_com_ubuntu_Upstart0_6_Job_Start_method (NihDBusObject * object,
                                                  NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
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

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
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
	if (job_class_start (object->data, message, env, wait) < 0) {
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
job_class_start_reply (NihDBusMessage *message,
                       const char *    instance)
{
	DBusMessage *   reply;
	DBusMessageIter iter;

	nih_assert (message != NULL);
	nih_assert (instance != NULL);

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

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_OBJECT_PATH, &instance)) {
		dbus_message_unref (reply);
		return -1;
	}

	/* Send the reply, appending it to the outgoing queue. */
	if (! dbus_connection_send (message->connection, reply, NULL)) {
		dbus_message_unref (reply);
		return -1;
	}

	dbus_message_unref (reply);

	return 0;
}


static DBusHandlerResult
job_class_com_ubuntu_Upstart0_6_Job_Stop_method (NihDBusObject * object,
                                                 NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
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

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
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
	if (job_class_stop (object->data, message, env, wait) < 0) {
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
job_class_stop_reply (NihDBusMessage *message)
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
job_class_com_ubuntu_Upstart0_6_Job_Restart_method (NihDBusObject * object,
                                                    NihDBusMessage *message)
{
	DBusMessageIter iter;
	DBusMessage *   reply;
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

	/* Demarshal an array from the message */
	if (dbus_message_iter_get_arg_type (&iter) != DBUS_TYPE_ARRAY) {
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
	if (job_class_restart (object->data, message, env, wait) < 0) {
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
job_class_restart_reply (NihDBusMessage *message,
                         const char *    instance)
{
	DBusMessage *   reply;
	DBusMessageIter iter;

	nih_assert (message != NULL);
	nih_assert (instance != NULL);

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

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_OBJECT_PATH, &instance)) {
		dbus_message_unref (reply);
		return -1;
	}

	/* Send the reply, appending it to the outgoing queue. */
	if (! dbus_connection_send (message->connection, reply, NULL)) {
		dbus_message_unref (reply);
		return -1;
	}

	dbus_message_unref (reply);

	return 0;
}


int
job_class_emit_instance_added (DBusConnection *connection,
                               const char *    origin_path,
                               const char *    instance)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);
	nih_assert (instance != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.ubuntu.Upstart0_6.Job", "InstanceAdded");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_OBJECT_PATH, &instance)) {
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
job_class_emit_instance_removed (DBusConnection *connection,
                                 const char *    origin_path,
                                 const char *    instance)
{
	DBusMessage *   signal;
	DBusMessageIter iter;

	nih_assert (connection != NULL);
	nih_assert (origin_path != NULL);
	nih_assert (instance != NULL);

	/* Construct the message. */
	signal = dbus_message_new_signal (origin_path, "com.ubuntu.Upstart0_6.Job", "InstanceRemoved");
	if (! signal)
		return -1;

	dbus_message_iter_init_append (signal, &iter);

	/* Marshal a char * onto the message */
	if (! dbus_message_iter_append_basic (&iter, DBUS_TYPE_OBJECT_PATH, &instance)) {
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
job_class_com_ubuntu_Upstart0_6_Job_name_get (NihDBusObject *  object,
                                              NihDBusMessage * message,
                                              DBusMessageIter *iter)
{
	DBusMessageIter variter;
	char *          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (job_class_get_name (object->data, message, &value) < 0)
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
job_class_com_ubuntu_Upstart0_6_Job_description_get (NihDBusObject *  object,
                                                     NihDBusMessage * message,
                                                     DBusMessageIter *iter)
{
	DBusMessageIter variter;
	char *          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (job_class_get_description (object->data, message, &value) < 0)
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
job_class_com_ubuntu_Upstart0_6_Job_author_get (NihDBusObject *  object,
                                                NihDBusMessage * message,
                                                DBusMessageIter *iter)
{
	DBusMessageIter variter;
	char *          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (job_class_get_author (object->data, message, &value) < 0)
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
job_class_com_ubuntu_Upstart0_6_Job_version_get (NihDBusObject *  object,
                                                 NihDBusMessage * message,
                                                 DBusMessageIter *iter)
{
	DBusMessageIter variter;
	char *          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (job_class_get_version (object->data, message, &value) < 0)
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
job_class_com_ubuntu_Upstart0_6_Job_usage_get (NihDBusObject *  object,
                                               NihDBusMessage * message,
                                               DBusMessageIter *iter)
{
	DBusMessageIter variter;
	char *          value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (job_class_get_usage (object->data, message, &value) < 0)
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
job_class_com_ubuntu_Upstart0_6_Job_start_on_get (NihDBusObject *  object,
                                                  NihDBusMessage * message,
                                                  DBusMessageIter *iter)
{
	DBusMessageIter variter;
	DBusMessageIter value_iter;
	char ***        value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (job_class_get_start_on (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "aas", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "as", &value_iter)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	if (value) {
		for (size_t value_i = 0; value[value_i]; value_i++) {
			DBusMessageIter value_element_iter;
			char * const *  value_element;

			value_element = value[value_i];

			/* Marshal an array onto the message */
			if (! dbus_message_iter_open_container (&value_iter, DBUS_TYPE_ARRAY, "s", &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (iter, &variter);
				nih_error_raise_no_memory ();
				return -1;
			}

			if (value_element) {
				for (size_t value_element_i = 0; value_element[value_element_i]; value_element_i++) {
					const char *value_element_element;

					value_element_element = value_element[value_element_i];

					/* Marshal a char * onto the message */
					if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_STRING, &value_element_element)) {
						dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
						dbus_message_iter_abandon_container (&variter, &value_iter);
						dbus_message_iter_abandon_container (iter, &variter);
						nih_error_raise_no_memory ();
						return -1;
					}
				}
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


static int
job_class_com_ubuntu_Upstart0_6_Job_stop_on_get (NihDBusObject *  object,
                                                 NihDBusMessage * message,
                                                 DBusMessageIter *iter)
{
	DBusMessageIter variter;
	DBusMessageIter value_iter;
	char ***        value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (job_class_get_stop_on (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "aas", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "as", &value_iter)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	if (value) {
		for (size_t value_i = 0; value[value_i]; value_i++) {
			DBusMessageIter value_element_iter;
			char * const *  value_element;

			value_element = value[value_i];

			/* Marshal an array onto the message */
			if (! dbus_message_iter_open_container (&value_iter, DBUS_TYPE_ARRAY, "s", &value_element_iter)) {
				dbus_message_iter_abandon_container (&variter, &value_iter);
				dbus_message_iter_abandon_container (iter, &variter);
				nih_error_raise_no_memory ();
				return -1;
			}

			if (value_element) {
				for (size_t value_element_i = 0; value_element[value_element_i]; value_element_i++) {
					const char *value_element_element;

					value_element_element = value_element[value_element_i];

					/* Marshal a char * onto the message */
					if (! dbus_message_iter_append_basic (&value_element_iter, DBUS_TYPE_STRING, &value_element_element)) {
						dbus_message_iter_abandon_container (&value_iter, &value_element_iter);
						dbus_message_iter_abandon_container (&variter, &value_iter);
						dbus_message_iter_abandon_container (iter, &variter);
						nih_error_raise_no_memory ();
						return -1;
					}
				}
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


static int
job_class_com_ubuntu_Upstart0_6_Job_emits_get (NihDBusObject *  object,
                                               NihDBusMessage * message,
                                               DBusMessageIter *iter)
{
	DBusMessageIter variter;
	DBusMessageIter value_iter;
	char **         value;

	nih_assert (object != NULL);
	nih_assert (message != NULL);
	nih_assert (iter != NULL);

	/* Call the handler function */
	if (job_class_get_emits (object->data, message, &value) < 0)
		return -1;

	/* Append a variant onto the message to contain the property value. */
	if (! dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "as", &variter)) {
		nih_error_raise_no_memory ();
		return -1;
	}

	/* Marshal an array onto the message */
	if (! dbus_message_iter_open_container (&variter, DBUS_TYPE_ARRAY, "s", &value_iter)) {
		dbus_message_iter_abandon_container (iter, &variter);
		nih_error_raise_no_memory ();
		return -1;
	}

	if (value) {
		for (size_t value_i = 0; value[value_i]; value_i++) {
			const char *value_element;

			value_element = value[value_i];

			/* Marshal a char * onto the message */
			if (! dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_STRING, &value_element)) {
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
