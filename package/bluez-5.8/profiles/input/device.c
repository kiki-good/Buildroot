/*
 *
 *  BlueZ - Bluetooth protocol stack for Linux
 *
 *  Copyright (C) 2004-2010  Marcel Holtmann <marcel@holtmann.org>
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hidp.h>
#include <bluetooth/sdp.h>
#include <bluetooth/sdp_lib.h>

#include <gdbus/gdbus.h>

#include "log.h"

#include "lib/uuid.h"
#include "../src/adapter.h"
#include "../src/device.h"
#include "../src/profile.h"
#include "../src/service.h"
#include "../src/storage.h"
#include "../src/dbus-common.h"

#include "device.h"
#include "error.h"
#include <btio/btio.h>

#include "sdp-client.h"

#define INPUT_INTERFACE "org.bluez.Input1"

enum reconnect_mode_t {
	RECONNECT_NONE = 0,
	RECONNECT_DEVICE,
	RECONNECT_HOST,
	RECONNECT_ANY
};

struct input_device {
	struct btd_service	*service;
	struct btd_device	*device;
	char			*path;
	bdaddr_t		src;
	bdaddr_t		dst;
	uint32_t		handle;
	GIOChannel		*ctrl_io;
	GIOChannel		*intr_io;
	guint			ctrl_watch;
	guint			intr_watch;
	guint			sec_watch;
	struct hidp_connadd_req *req;
	guint			dc_id;
	bool			disable_sdp;
	char			*name;
	enum reconnect_mode_t	reconnect_mode;
	guint			reconnect_timer;
	uint32_t		reconnect_attempt;
};

static int idle_timeout = 0;

void input_set_idle_timeout(int timeout)
{
	idle_timeout = timeout;
}

static void input_device_enter_reconnect_mode(struct input_device *idev);

static void input_device_free(struct input_device *idev)
{
	if (idev->dc_id)
		device_remove_disconnect_watch(idev->device, idev->dc_id);

	btd_service_unref(idev->service);
	btd_device_unref(idev->device);
	g_free(idev->name);
	g_free(idev->path);

	if (idev->ctrl_watch > 0)
		g_source_remove(idev->ctrl_watch);

	if (idev->intr_watch > 0)
		g_source_remove(idev->intr_watch);

	if (idev->sec_watch > 0)
		g_source_remove(idev->sec_watch);

	if (idev->intr_io)
		g_io_channel_unref(idev->intr_io);

	if (idev->ctrl_io)
		g_io_channel_unref(idev->ctrl_io);

	if (idev->req) {
		g_free(idev->req->rd_data);
		g_free(idev->req);
	}

	if (idev->reconnect_timer > 0)
		g_source_remove(idev->reconnect_timer);

	g_free(idev);
}

static gboolean intr_watch_cb(GIOChannel *chan, GIOCondition cond, gpointer data)
{
	struct input_device *idev = data;
	char address[18];

	ba2str(&idev->dst, address);

	DBG("Device %s disconnected", address);

	/* Checking for ctrl_watch avoids a double g_io_channel_shutdown since
	 * it's likely that ctrl_watch_cb has been queued for dispatching in
	 * this mainloop iteration */
	if ((cond & (G_IO_HUP | G_IO_ERR)) && idev->ctrl_watch)
		g_io_channel_shutdown(chan, TRUE, NULL);

	device_remove_disconnect_watch(idev->device, idev->dc_id);
	idev->dc_id = 0;

	idev->intr_watch = 0;

	if (idev->intr_io) {
		g_io_channel_unref(idev->intr_io);
		idev->intr_io = NULL;
	}

	/* Close control channel */
	if (idev->ctrl_io && !(cond & G_IO_NVAL))
		g_io_channel_shutdown(idev->ctrl_io, TRUE, NULL);

	btd_service_disconnecting_complete(idev->service, 0);

	/* Enter the auto-reconnect mode if needed */
	input_device_enter_reconnect_mode(idev);

	return FALSE;
}

static gboolean ctrl_watch_cb(GIOChannel *chan, GIOCondition cond, gpointer data)
{
	struct input_device *idev = data;
	char address[18];

	ba2str(&idev->dst, address);

	DBG("Device %s disconnected", address);

	/* Checking for intr_watch avoids a double g_io_channel_shutdown since
	 * it's likely that intr_watch_cb has been queued for dispatching in
	 * this mainloop iteration */
	if ((cond & (G_IO_HUP | G_IO_ERR)) && idev->intr_watch)
		g_io_channel_shutdown(chan, TRUE, NULL);

	idev->ctrl_watch = 0;

	if (idev->ctrl_io) {
		g_io_channel_unref(idev->ctrl_io);
		idev->ctrl_io = NULL;
	}

	/* Close interrupt channel */
	if (idev->intr_io && !(cond & G_IO_NVAL))
		g_io_channel_shutdown(idev->intr_io, TRUE, NULL);

	return FALSE;
}

static void epox_endian_quirk(unsigned char *data, int size)
{
	/* USAGE_PAGE (Keyboard)	05 07
	 * USAGE_MINIMUM (0)		19 00
	 * USAGE_MAXIMUM (65280)	2A 00 FF   <= must be FF 00
	 * LOGICAL_MINIMUM (0)		15 00
	 * LOGICAL_MAXIMUM (65280)	26 00 FF   <= must be FF 00
	 */
	unsigned char pattern[] = { 0x05, 0x07, 0x19, 0x00, 0x2a, 0x00, 0xff,
						0x15, 0x00, 0x26, 0x00, 0xff };
	unsigned int i;

	if (!data)
		return;

	for (i = 0; i < size - sizeof(pattern); i++) {
		if (!memcmp(data + i, pattern, sizeof(pattern))) {
			data[i + 5] = 0xff;
			data[i + 6] = 0x00;
			data[i + 10] = 0xff;
			data[i + 11] = 0x00;
		}
	}
}

static int create_hid_dev_name(sdp_record_t *rec, struct hidp_connadd_req *req)
{
	char sdesc[sizeof(req->name)];

	if (sdp_get_service_desc(rec, sdesc, sizeof(sdesc)) == 0) {
		char pname[sizeof(req->name)];

		if (sdp_get_provider_name(rec, pname, sizeof(pname)) == 0 &&
						strncmp(sdesc, pname, 5) != 0)
			snprintf(req->name, sizeof(req->name), "%s %s", pname,
									sdesc);
		else
			snprintf(req->name, sizeof(req->name), "%s", sdesc);
	} else {
		return sdp_get_service_name(rec, req->name, sizeof(req->name));
	}

	return 0;
}

/* See HID profile specification v1.0, "7.11.6 HIDDescriptorList" for details
 * on the attribute format. */
static int extract_hid_desc_data(sdp_record_t *rec,
						struct hidp_connadd_req *req)
{
	sdp_data_t *d;

	d = sdp_data_get(rec, SDP_ATTR_HID_DESCRIPTOR_LIST);
	if (!d)
		goto invalid_desc;

	if (!SDP_IS_SEQ(d->dtd))
		goto invalid_desc;

	/* First HIDDescriptor */
	d = d->val.dataseq;
	if (!SDP_IS_SEQ(d->dtd))
		goto invalid_desc;

	/* ClassDescriptorType */
	d = d->val.dataseq;
	if (d->dtd != SDP_UINT8)
		goto invalid_desc;

	/* ClassDescriptorData */
	d = d->next;
	if (!d || !SDP_IS_TEXT_STR(d->dtd))
		goto invalid_desc;

	req->rd_data = g_try_malloc0(d->unitSize);
	if (req->rd_data) {
		memcpy(req->rd_data, d->val.str, d->unitSize);
		req->rd_size = d->unitSize;
		epox_endian_quirk(req->rd_data, req->rd_size);
	}

	return 0;

invalid_desc:
	error("Missing or invalid HIDDescriptorList SDP attribute");
	return -EINVAL;
}

static int extract_hid_record(sdp_record_t *rec, struct hidp_connadd_req *req)
{
	sdp_data_t *pdlist;
	uint8_t attr_val;
	int err;

	err = create_hid_dev_name(rec, req);
	if (err < 0)
		DBG("No valid Service Name or Service Description found");

	pdlist = sdp_data_get(rec, SDP_ATTR_HID_PARSER_VERSION);
	req->parser = pdlist ? pdlist->val.uint16 : 0x0100;

	pdlist = sdp_data_get(rec, SDP_ATTR_HID_DEVICE_SUBCLASS);
	req->subclass = pdlist ? pdlist->val.uint8 : 0;

	pdlist = sdp_data_get(rec, SDP_ATTR_HID_COUNTRY_CODE);
	req->country = pdlist ? pdlist->val.uint8 : 0;

	pdlist = sdp_data_get(rec, SDP_ATTR_HID_VIRTUAL_CABLE);
	attr_val = pdlist ? pdlist->val.uint8 : 0;
	if (attr_val)
		req->flags |= (1 << HIDP_VIRTUAL_CABLE_UNPLUG);

	pdlist = sdp_data_get(rec, SDP_ATTR_HID_BOOT_DEVICE);
	attr_val = pdlist ? pdlist->val.uint8 : 0;
	if (attr_val)
		req->flags |= (1 << HIDP_BOOT_PROTOCOL_MODE);

	err = extract_hid_desc_data(rec, req);
	if (err < 0)
		return err;

	return 0;
}

static int ioctl_connadd(struct hidp_connadd_req *req)
{
	int ctl, err = 0;

	ctl = socket(AF_BLUETOOTH, SOCK_RAW, BTPROTO_HIDP);
	if (ctl < 0)
		return -errno;

	if (ioctl(ctl, HIDPCONNADD, req) < 0)
		err = -errno;

	close(ctl);

	return err;
}

static gboolean encrypt_notify(GIOChannel *io, GIOCondition condition,
								gpointer data)
{
	struct input_device *idev = data;
	int err;

	DBG("");

	err = ioctl_connadd(idev->req);
	if (err < 0) {
		error("ioctl_connadd(): %s (%d)", strerror(-err), -err);

		if (idev->ctrl_io) {
			g_io_channel_shutdown(idev->ctrl_io, FALSE, NULL);
			g_io_channel_unref(idev->ctrl_io);
			idev->ctrl_io = NULL;
		}

		if (idev->intr_io) {
			g_io_channel_shutdown(idev->intr_io, FALSE, NULL);
			g_io_channel_unref(idev->intr_io);
			idev->intr_io = NULL;
		}
	}

	idev->sec_watch = 0;

	g_free(idev->req->rd_data);
	g_free(idev->req);
	idev->req = NULL;

	return FALSE;
}

static int hidp_add_connection(struct input_device *idev)
{
	struct hidp_connadd_req *req;
	sdp_record_t *rec;
	char src_addr[18], dst_addr[18];
	char filename[PATH_MAX + 1];
	GKeyFile *key_file;
	char handle[11], *str;
	GError *gerr = NULL;
	int err;

	req = g_new0(struct hidp_connadd_req, 1);
	req->ctrl_sock = g_io_channel_unix_get_fd(idev->ctrl_io);
	req->intr_sock = g_io_channel_unix_get_fd(idev->intr_io);
	req->flags     = 0;
	req->idle_to   = idle_timeout;

	ba2str(&idev->src, src_addr);
	ba2str(&idev->dst, dst_addr);

	snprintf(filename, PATH_MAX, STORAGEDIR "/%s/cache/%s", src_addr,
								dst_addr);
	filename[PATH_MAX] = '\0';
	sprintf(handle, "0x%8.8X", idev->handle);

	key_file = g_key_file_new();
	g_key_file_load_from_file(key_file, filename, 0, NULL);
	str = g_key_file_get_string(key_file, "ServiceRecords", handle, NULL);
	g_key_file_free(key_file);

	if (!str) {
		error("Rejected connection from unknown device %s", dst_addr);
		err = -EPERM;
		goto cleanup;
	}

	rec = record_from_string(str);
	g_free(str);

	err = extract_hid_record(rec, req);
	sdp_record_free(rec);
	if (err < 0) {
		error("Could not parse HID SDP record: %s (%d)", strerror(-err),
									-err);
		goto cleanup;
	}

	req->vendor = btd_device_get_vendor(idev->device);
	req->product = btd_device_get_product(idev->device);
	req->version = btd_device_get_version(idev->device);

	if (idev->name)
		strncpy(req->name, idev->name, sizeof(req->name) - 1);

	/* Encryption is mandatory for keyboards */
	if (req->subclass & 0x40) {
		if (!bt_io_set(idev->intr_io, &gerr,
					BT_IO_OPT_SEC_LEVEL, BT_IO_SEC_MEDIUM,
					BT_IO_OPT_INVALID)) {
			error("btio: %s", gerr->message);
			g_error_free(gerr);
			err = -EFAULT;
			goto cleanup;
		}

		idev->req = req;
		idev->sec_watch = g_io_add_watch(idev->intr_io, G_IO_OUT,
							encrypt_notify, idev);

		return 0;
	}

	err = ioctl_connadd(req);

cleanup:
	g_free(req->rd_data);
	g_free(req);

	return err;
}

static int is_connected(struct input_device *idev)
{
	struct hidp_conninfo ci;
	int ctl;

	/* Standard HID */
	ctl = socket(AF_BLUETOOTH, SOCK_RAW, BTPROTO_HIDP);
	if (ctl < 0)
		return 0;

	memset(&ci, 0, sizeof(ci));
	bacpy(&ci.bdaddr, &idev->dst);
	if (ioctl(ctl, HIDPGETCONNINFO, &ci) < 0) {
		close(ctl);
		return 0;
	}

	close(ctl);

	if (ci.state != BT_CONNECTED)
		return 0;
	else
		return 1;
}

static int connection_disconnect(struct input_device *idev, uint32_t flags)
{
	struct hidp_conndel_req req;
	struct hidp_conninfo ci;
	int ctl, err = 0;

	if (!is_connected(idev))
		return -ENOTCONN;

	/* Standard HID disconnect */
	if (idev->intr_io)
		g_io_channel_shutdown(idev->intr_io, TRUE, NULL);
	if (idev->ctrl_io)
		g_io_channel_shutdown(idev->ctrl_io, TRUE, NULL);

	ctl = socket(AF_BLUETOOTH, SOCK_RAW, BTPROTO_HIDP);
	if (ctl < 0) {
		error("Can't open HIDP control socket");
		return -errno;
	}

	memset(&ci, 0, sizeof(ci));
	bacpy(&ci.bdaddr, &idev->dst);
	if ((ioctl(ctl, HIDPGETCONNINFO, &ci) < 0) ||
				(ci.state != BT_CONNECTED)) {
		err = -ENOTCONN;
		goto fail;
	}

	memset(&req, 0, sizeof(req));
	bacpy(&req.bdaddr, &idev->dst);
	req.flags = flags;
	if (ioctl(ctl, HIDPCONNDEL, &req) < 0) {
		err = -errno;
		error("Can't delete the HID device: %s(%d)",
				strerror(-err), -err);
		goto fail;
	}

fail:
	close(ctl);

	return err;
}

static void disconnect_cb(struct btd_device *device, gboolean removal,
				void *user_data)
{
	struct input_device *idev = user_data;
	int flags;

	info("Input: disconnect %s", idev->path);

	flags = removal ? (1 << HIDP_VIRTUAL_CABLE_UNPLUG) : 0;

	connection_disconnect(idev, flags);
}

static int input_device_connected(struct input_device *idev)
{
	int err;

	if (idev->intr_io == NULL || idev->ctrl_io == NULL)
		return -ENOTCONN;

	err = hidp_add_connection(idev);
	if (err < 0)
		return err;

	idev->dc_id = device_add_disconnect_watch(idev->device, disconnect_cb,
							idev, NULL);

	btd_service_connecting_complete(idev->service, 0);

	return 0;
}

static void interrupt_connect_cb(GIOChannel *chan, GError *conn_err,
							gpointer user_data)
{
	struct input_device *idev = user_data;
	int err;

	if (conn_err) {
		err = -EIO;
		goto failed;
	}

	err = input_device_connected(idev);
	if (err < 0)
		goto failed;

	idev->intr_watch = g_io_add_watch(idev->intr_io,
					G_IO_HUP | G_IO_ERR | G_IO_NVAL,
					intr_watch_cb, idev);

	return;

failed:
	btd_service_connecting_complete(idev->service, err);

	/* So we guarantee the interrupt channel is closed before the
	 * control channel (if we only do unref GLib will close it only
	 * after returning control to the mainloop */
	if (!conn_err)
		g_io_channel_shutdown(idev->intr_io, FALSE, NULL);

	g_io_channel_unref(idev->intr_io);
	idev->intr_io = NULL;

	if (idev->ctrl_io) {
		g_io_channel_unref(idev->ctrl_io);
		idev->ctrl_io = NULL;
	}
}

static void control_connect_cb(GIOChannel *chan, GError *conn_err,
							gpointer user_data)
{
	struct input_device *idev = user_data;
	GIOChannel *io;
	GError *err = NULL;

	if (conn_err) {
		error("%s", conn_err->message);
		goto failed;
	}

	/* Connect to the HID interrupt channel */
	io = bt_io_connect(interrupt_connect_cb, idev,
				NULL, &err,
				BT_IO_OPT_SOURCE_BDADDR, &idev->src,
				BT_IO_OPT_DEST_BDADDR, &idev->dst,
				BT_IO_OPT_PSM, L2CAP_PSM_HIDP_INTR,
				BT_IO_OPT_SEC_LEVEL, BT_IO_SEC_LOW,
				BT_IO_OPT_INVALID);
	if (!io) {
		error("%s", err->message);
		g_error_free(err);
		goto failed;
	}

	idev->intr_io = io;

	idev->ctrl_watch = g_io_add_watch(idev->ctrl_io,
					G_IO_HUP | G_IO_ERR | G_IO_NVAL,
					ctrl_watch_cb, idev);

	return;

failed:
	btd_service_connecting_complete(idev->service, -EIO);
	g_io_channel_unref(idev->ctrl_io);
	idev->ctrl_io = NULL;
}

static int dev_connect(struct input_device *idev)
{
	GError *err = NULL;
	GIOChannel *io;

	if (idev->disable_sdp)
		bt_clear_cached_session(&idev->src, &idev->dst);

	io = bt_io_connect(control_connect_cb, idev,
			NULL, &err,
			BT_IO_OPT_SOURCE_BDADDR, &idev->src,
			BT_IO_OPT_DEST_BDADDR, &idev->dst,
			BT_IO_OPT_PSM, L2CAP_PSM_HIDP_CTRL,
			BT_IO_OPT_SEC_LEVEL, BT_IO_SEC_LOW,
			BT_IO_OPT_INVALID);
	idev->ctrl_io = io;

	if (err == NULL)
		return 0;

	error("%s", err->message);
	g_error_free(err);

	return -EIO;
}

static gboolean input_device_auto_reconnect(gpointer user_data)
{
	struct input_device *idev = user_data;

	DBG("path=%s, attempt=%d", idev->path, idev->reconnect_attempt);

	/* Stop the recurrent reconnection attempts if the device is reconnected
	 * or is marked for removal. */
	if (device_is_temporary(idev->device) ||
					device_is_connected(idev->device))
		return FALSE;

	/* Only attempt an auto-reconnect for at most 3 minutes (6 * 30s). */
	if (idev->reconnect_attempt >= 6)
		return FALSE;

	/* Check if the profile is already connected. */
	if (idev->ctrl_io)
		return FALSE;

	if (is_connected(idev))
		return FALSE;

	idev->reconnect_attempt++;
	dev_connect(idev);

	return TRUE;
}

static const char * const _reconnect_mode_str[] = {
	"none",
	"device",
	"host",
	"any"
};

static const char *reconnect_mode_to_string(const enum reconnect_mode_t mode)
{
	return _reconnect_mode_str[mode];
}

static void input_device_enter_reconnect_mode(struct input_device *idev)
{
	DBG("path=%s reconnect_mode=%s", idev->path,
				reconnect_mode_to_string(idev->reconnect_mode));

	/* Only attempt an auto-reconnect when the device is required to accept
	 * reconnections from the host. */
	if (idev->reconnect_mode != RECONNECT_ANY &&
				idev->reconnect_mode != RECONNECT_HOST)
		return;

	/* If the device is temporary we are not required to reconnect with the
	 * device. This is likely the case of a removing device. */
	if (device_is_temporary(idev->device) ||
					device_is_connected(idev->device))
		return;

	if (idev->reconnect_timer > 0)
		g_source_remove(idev->reconnect_timer);

	DBG("registering auto-reconnect");
	idev->reconnect_attempt = 0;
	idev->reconnect_timer = g_timeout_add_seconds(30,
					input_device_auto_reconnect, idev);

}

int input_device_connect(struct btd_service *service)
{
	struct input_device *idev;

	DBG("");

	idev = btd_service_get_user_data(service);

	if (idev->ctrl_io)
		return -EBUSY;

	if (is_connected(idev))
		return -EALREADY;

	return dev_connect(idev);
}

int input_device_disconnect(struct btd_service *service)
{
	struct input_device *idev;
	int err;

	DBG("");

	idev = btd_service_get_user_data(service);

	err = connection_disconnect(idev, 0);
	if (err < 0)
		return err;

	return 0;
}

static bool is_device_sdp_disable(const sdp_record_t *rec)
{
	sdp_data_t *data;

	data = sdp_data_get(rec, SDP_ATTR_HID_SDP_DISABLE);

	return data && data->val.uint8;
}

static enum reconnect_mode_t hid_reconnection_mode(bool reconnect_initiate,
						bool normally_connectable)
{
	if (!reconnect_initiate && !normally_connectable)
		return RECONNECT_NONE;
	else if (!reconnect_initiate && normally_connectable)
		return RECONNECT_HOST;
	else if (reconnect_initiate && !normally_connectable)
		return RECONNECT_DEVICE;
	else /* (reconnect_initiate && normally_connectable) */
		return RECONNECT_ANY;
}

static void extract_hid_props(struct input_device *idev,
					const sdp_record_t *rec)
{
	/* Extract HID connectability */
	bool reconnect_initiate, normally_connectable;
	sdp_data_t *pdlist;

	/* HIDNormallyConnectable is optional and assumed FALSE
	* if not present. */
	pdlist = sdp_data_get(rec, SDP_ATTR_HID_RECONNECT_INITIATE);
	reconnect_initiate = pdlist ? pdlist->val.uint8 : TRUE;

	pdlist = sdp_data_get(rec, SDP_ATTR_HID_NORMALLY_CONNECTABLE);
	normally_connectable = pdlist ? pdlist->val.uint8 : FALSE;

	/* Update local values */
	idev->reconnect_mode =
		hid_reconnection_mode(reconnect_initiate, normally_connectable);
}

static struct input_device *input_device_new(struct btd_service *service)
{
	struct btd_device *device = btd_service_get_device(service);
	struct btd_profile *p = btd_service_get_profile(service);
	const char *path = device_get_path(device);
	const sdp_record_t *rec = btd_device_get_record(device, p->remote_uuid);
	struct btd_adapter *adapter = device_get_adapter(device);
	struct input_device *idev;
	char name[HCI_MAX_NAME_LENGTH + 1];

	idev = g_new0(struct input_device, 1);
	bacpy(&idev->src, adapter_get_address(adapter));
	bacpy(&idev->dst, device_get_address(device));
	idev->service = btd_service_ref(service);
	idev->device = btd_device_ref(device);
	idev->path = g_strdup(path);
	idev->handle = rec->handle;
	idev->disable_sdp = is_device_sdp_disable(rec);

	device_get_name(device, name, HCI_MAX_NAME_LENGTH);
	if (strlen(name) > 0)
		idev->name = g_strdup(name);

	/* Initialize device properties */
	extract_hid_props(idev, rec);

	return idev;
}

static gboolean property_get_reconnect_mode(
					const GDBusPropertyTable *property,
					DBusMessageIter *iter, void *data)
{
	struct input_device *idev = data;
	const char *str_mode = reconnect_mode_to_string(idev->reconnect_mode);

	dbus_message_iter_append_basic(iter, DBUS_TYPE_STRING, &str_mode);

	return TRUE;
}

static const GDBusPropertyTable input_properties[] = {
	{ "ReconnectMode", "s", property_get_reconnect_mode },
	{ }
};

int input_device_register(struct btd_service *service)
{
	struct btd_device *device = btd_service_get_device(service);
	const char *path = device_get_path(device);
	struct input_device *idev;

	DBG("%s", path);

	idev = input_device_new(service);
	if (!idev)
		return -EINVAL;

	if (g_dbus_register_interface(btd_get_dbus_connection(),
					idev->path, INPUT_INTERFACE,
					NULL, NULL,
					input_properties, idev,
					NULL) == FALSE) {
		error("Unable to register %s interface", INPUT_INTERFACE);
		input_device_free(idev);
		return -EINVAL;
	}

	btd_service_set_user_data(service, idev);

	return 0;
}

static struct input_device *find_device(const bdaddr_t *src,
					const bdaddr_t *dst)
{
	struct btd_device *device;
	struct btd_service *service;

	device = adapter_find_device(adapter_find(src), dst);
	if (device == NULL)
		return NULL;

	service = btd_device_get_service(device, HID_UUID);
	if (service == NULL)
		return NULL;

	return btd_service_get_user_data(service);
}

void input_device_unregister(struct btd_service *service)
{
	struct btd_device *device = btd_service_get_device(service);
	const char *path = device_get_path(device);
	struct input_device *idev = btd_service_get_user_data(service);

	DBG("%s", path);

	g_dbus_unregister_interface(btd_get_dbus_connection(),
						idev->path, INPUT_INTERFACE);

	input_device_free(idev);
}

static int input_device_connadd(struct input_device *idev)
{
	int err;

	err = input_device_connected(idev);
	if (err < 0)
		goto error;

	return 0;

error:
	if (idev->ctrl_io) {
		g_io_channel_shutdown(idev->ctrl_io, FALSE, NULL);
		g_io_channel_unref(idev->ctrl_io);
		idev->ctrl_io = NULL;
	}
	if (idev->intr_io) {
		g_io_channel_shutdown(idev->intr_io, FALSE, NULL);
		g_io_channel_unref(idev->intr_io);
		idev->intr_io = NULL;
	}

	return err;
}

bool input_device_exists(const bdaddr_t *src, const bdaddr_t *dst)
{
	if (find_device(src, dst))
		return true;

	return false;
}

int input_device_set_channel(const bdaddr_t *src, const bdaddr_t *dst, int psm,
								GIOChannel *io)
{
	struct input_device *idev = find_device(src, dst);

	DBG("idev %p psm %d", idev, psm);

	if (!idev)
		return -ENOENT;

	switch (psm) {
	case L2CAP_PSM_HIDP_CTRL:
		if (idev->ctrl_io)
			return -EALREADY;
		idev->ctrl_io = g_io_channel_ref(io);
		idev->ctrl_watch = g_io_add_watch(idev->ctrl_io,
					G_IO_HUP | G_IO_ERR | G_IO_NVAL,
					ctrl_watch_cb, idev);
		break;
	case L2CAP_PSM_HIDP_INTR:
		if (idev->intr_io)
			return -EALREADY;
		idev->intr_io = g_io_channel_ref(io);
		idev->intr_watch = g_io_add_watch(idev->intr_io,
					G_IO_HUP | G_IO_ERR | G_IO_NVAL,
					intr_watch_cb, idev);
		break;
	}

	if (idev->intr_io && idev->ctrl_io)
		input_device_connadd(idev);

	return 0;
}

int input_device_close_channels(const bdaddr_t *src, const bdaddr_t *dst)
{
	struct input_device *idev = find_device(src, dst);

	if (!idev)
		return -ENOENT;

	if (idev->intr_io)
		g_io_channel_shutdown(idev->intr_io, TRUE, NULL);

	if (idev->ctrl_io)
		g_io_channel_shutdown(idev->ctrl_io, TRUE, NULL);

	return 0;
}
