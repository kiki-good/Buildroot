/* upstart
 *
 * Copyright (C) 2010 Scott James Remnant <scott@netsplit.com>.
 *
 * This file was automatically generated; see the source for copying
 * conditions.
 */

#ifndef UPSTART_COM_UBUNTU_UPSTART_INSTANCE_H
#define UPSTART_COM_UBUNTU_UPSTART_INSTANCE_H

#include <dbus/dbus.h>

#include <stdint.h>

#include <nih/macros.h>

#include <nih-dbus/dbus_interface.h>
#include <nih-dbus/dbus_message.h>


typedef struct job_processes_element {
	char *  item0;
	int32_t item1;
} JobProcessesElement;


NIH_BEGIN_EXTERN

extern const NihDBusInterface  job_com_ubuntu_Upstart0_6_Instance;
extern const NihDBusInterface *job_interfaces[];


int job_start_reply        (NihDBusMessage *message)
	__attribute__ ((warn_unused_result));
int job_stop_reply         (NihDBusMessage *message)
	__attribute__ ((warn_unused_result));
int job_restart_reply      (NihDBusMessage *message)
	__attribute__ ((warn_unused_result));
int job_reload_reply       (NihDBusMessage *message)
	__attribute__ ((warn_unused_result));
int job_emit_goal_changed  (DBusConnection *connection, const char *origin_path, const char *goal)
	__attribute__ ((warn_unused_result));
int job_emit_state_changed (DBusConnection *connection, const char *origin_path, const char *state)
	__attribute__ ((warn_unused_result));
int job_emit_failed        (DBusConnection *connection, const char *origin_path, int32_t status)
	__attribute__ ((warn_unused_result));

NIH_END_EXTERN

#endif /* UPSTART_COM_UBUNTU_UPSTART_INSTANCE_H */
