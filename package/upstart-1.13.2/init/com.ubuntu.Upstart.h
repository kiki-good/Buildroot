/* upstart
 *
 * Copyright (C) 2010 Scott James Remnant <scott@netsplit.com>.
 *
 * This file was automatically generated; see the source for copying
 * conditions.
 */

#ifndef UPSTART_COM_UBUNTU_UPSTART_H
#define UPSTART_COM_UBUNTU_UPSTART_H

#include <dbus/dbus.h>

#include <stdint.h>

#include <nih/macros.h>

#include <nih-dbus/dbus_interface.h>
#include <nih-dbus/dbus_message.h>


NIH_BEGIN_EXTERN

extern const NihDBusInterface  control_com_ubuntu_Upstart0_6;
extern const NihDBusInterface *control_interfaces[];


int control_restart_reply              (NihDBusMessage *message)
	__attribute__ ((warn_unused_result));
int control_emit_event_reply           (NihDBusMessage *message)
	__attribute__ ((warn_unused_result));
int control_emit_event_with_file_reply (NihDBusMessage *message)
	__attribute__ ((warn_unused_result));
int control_emit_job_added             (DBusConnection *connection, const char *origin_path, const char *job)
	__attribute__ ((warn_unused_result));
int control_emit_job_removed           (DBusConnection *connection, const char *origin_path, const char *job)
	__attribute__ ((warn_unused_result));
int control_emit_event_emitted         (DBusConnection *connection, const char *origin_path, const char *name, char * const *env)
	__attribute__ ((warn_unused_result));
int control_emit_restarted             (DBusConnection *connection, const char *origin_path)
	__attribute__ ((warn_unused_result));

NIH_END_EXTERN

#endif /* UPSTART_COM_UBUNTU_UPSTART_H */
