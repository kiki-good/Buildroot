/* upstart
 *
 * Copyright (C) 2010 Scott James Remnant <scott@netsplit.com>.
 *
 * This file was automatically generated; see the source for copying
 * conditions.
 */

#ifndef UPSTART_COM_UBUNTU_UPSTART_JOB_H
#define UPSTART_COM_UBUNTU_UPSTART_JOB_H

#include <dbus/dbus.h>

#include <stdint.h>

#include <nih/macros.h>

#include <nih-dbus/dbus_interface.h>
#include <nih-dbus/dbus_message.h>


NIH_BEGIN_EXTERN

extern const NihDBusInterface  job_class_com_ubuntu_Upstart0_6_Job;
extern const NihDBusInterface *job_class_interfaces[];


int job_class_start_reply           (NihDBusMessage *message, const char *instance)
	__attribute__ ((warn_unused_result));
int job_class_stop_reply            (NihDBusMessage *message)
	__attribute__ ((warn_unused_result));
int job_class_restart_reply         (NihDBusMessage *message, const char *instance)
	__attribute__ ((warn_unused_result));
int job_class_emit_instance_added   (DBusConnection *connection, const char *origin_path, const char *instance)
	__attribute__ ((warn_unused_result));
int job_class_emit_instance_removed (DBusConnection *connection, const char *origin_path, const char *instance)
	__attribute__ ((warn_unused_result));

NIH_END_EXTERN

#endif /* UPSTART_COM_UBUNTU_UPSTART_JOB_H */
