/*
 * libudev - interface to udev device information
 *
 * Copyright (C) 2008-2010 Kay Sievers <kay.sievers@vrfy.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#include "libudev.h"
#include "libudev-private.h"

static void udev_device_tag(struct udev_device *dev, const char *tag, bool add)
{
	struct udev *udev = udev_device_get_udev(dev);
	char filename[UTIL_PATH_SIZE];

	util_strscpyl(filename, sizeof(filename), udev_get_dev_path(udev), "/.udev/tags/", tag, "/",
		      udev_device_get_subsystem(dev), ":", udev_device_get_sysname(dev), NULL);

	if (add) {
		util_create_path(udev, filename);
		symlink(udev_device_get_devpath(dev), filename);
		/* possibly cleanup old entries after a device renaming */
		if (udev_device_get_sysname_old(dev) != NULL) {
			char filename_old[UTIL_PATH_SIZE];

			util_strscpyl(filename_old, sizeof(filename_old), udev_get_dev_path(udev), "/.udev/tags/", tag, "/",
				      udev_device_get_subsystem(dev), ":", udev_device_get_sysname_old(dev), NULL);
			unlink(filename_old);
		}
	} else {
		unlink(filename);
	}
}

int udev_device_tag_index(struct udev_device *dev, struct udev_device *dev_old, bool add)
{
	struct udev_list_entry *list_entry;
	bool found;

	if (add && dev_old != NULL) {
		/* delete possible left-over tags */
		udev_list_entry_foreach(list_entry, udev_device_get_tags_list_entry(dev_old)) {
			const char *tag_old = udev_list_entry_get_name(list_entry);
			struct udev_list_entry *list_entry_current;

			found = false;
			udev_list_entry_foreach(list_entry_current, udev_device_get_tags_list_entry(dev)) {
				const char *tag = udev_list_entry_get_name(list_entry_current);

				if (strcmp(tag, tag_old) == 0) {
					found = true;
					break;
				}
			}
			if (!found)
				udev_device_tag(dev_old, tag_old, false);
		}
	}

	udev_list_entry_foreach(list_entry, udev_device_get_tags_list_entry(dev))
		udev_device_tag(dev, udev_list_entry_get_name(list_entry), add);

	return 0;
}

int udev_device_update_db(struct udev_device *udev_device)
{
	struct udev *udev = udev_device_get_udev(udev_device);
	char filename[UTIL_PATH_SIZE];
	char filename_tmp[UTIL_PATH_SIZE];
	FILE *f;
	char target[232]; /* on 64bit, tmpfs inlines up to 239 bytes */
	size_t devlen = strlen(udev_get_dev_path(udev))+1;
	char *s;
	size_t l;
	struct udev_list_entry *list_entry;
	int ret;

	util_strscpyl(filename, sizeof(filename), udev_get_dev_path(udev), "/.udev/db/",
		      udev_device_get_subsystem(udev_device), ":", udev_device_get_sysname(udev_device), NULL);
	util_strscpyl(filename_tmp, sizeof(filename_tmp), filename, ".tmp", NULL);

	udev_list_entry_foreach(list_entry, udev_device_get_properties_list_entry(udev_device))
		if (udev_list_entry_get_flags(list_entry))
			goto file;
	if (udev_device_get_tags_list_entry(udev_device) != NULL)
		goto file;
	if (udev_device_get_devlink_priority(udev_device) != 0)
		goto file;
	if (udev_device_get_event_timeout(udev_device) >= 0)
		goto file;
	if (udev_device_get_watch_handle(udev_device) >= 0)
		goto file;
	if (udev_device_get_devnode(udev_device) == NULL)
		goto out;

	/*
	 * if we have only the node and symlinks to store, try not to waste
	 * tmpfs memory -- store values, if they fit, in a symlink target
	 */
	s = target;
	l = util_strpcpy(&s, sizeof(target), &udev_device_get_devnode(udev_device)[devlen]);
	udev_list_entry_foreach(list_entry, udev_device_get_devlinks_list_entry(udev_device)) {
		l = util_strpcpyl(&s, l, " ", &udev_list_entry_get_name(list_entry)[devlen], NULL);
		if (l == 0) {
			info(udev, "size of links too large, create file\n");
			goto file;
		}
	}
	udev_selinux_setfscreatecon(udev, filename_tmp, S_IFLNK);
	util_create_path(udev, filename_tmp);
	ret = symlink(target, filename_tmp);
	udev_selinux_resetfscreatecon(udev);
	if (ret != 0)
		goto file;
	ret = rename(filename_tmp, filename);
	if (ret != 0)
		goto file;
	info(udev, "created db link (%s)\n", target);
	goto out;
file:
	util_create_path(udev, filename_tmp);
	f = fopen(filename_tmp, "w");
	if (f == NULL) {
		err(udev, "unable to create temporary db file '%s': %m\n", filename_tmp);
		return -1;
	}

	if (udev_device_get_devnode(udev_device) != NULL) {
		fprintf(f, "N:%s\n", &udev_device_get_devnode(udev_device)[devlen]);
		udev_list_entry_foreach(list_entry, udev_device_get_devlinks_list_entry(udev_device))
			fprintf(f, "S:%s\n", &udev_list_entry_get_name(list_entry)[devlen]);
	}
	if (udev_device_get_devlink_priority(udev_device) != 0)
		fprintf(f, "L:%i\n", udev_device_get_devlink_priority(udev_device));
	if (udev_device_get_event_timeout(udev_device) >= 0)
		fprintf(f, "T:%i\n", udev_device_get_event_timeout(udev_device));
	if (udev_device_get_watch_handle(udev_device) >= 0)
		fprintf(f, "W:%i\n", udev_device_get_watch_handle(udev_device));
	udev_list_entry_foreach(list_entry, udev_device_get_properties_list_entry(udev_device)) {
		if (!udev_list_entry_get_flags(list_entry))
			continue;
		fprintf(f, "E:%s=%s\n",
			udev_list_entry_get_name(list_entry),
			udev_list_entry_get_value(list_entry));
	}
	udev_list_entry_foreach(list_entry, udev_device_get_tags_list_entry(udev_device))
		fprintf(f, "G:%s\n", udev_list_entry_get_name(list_entry));
	fclose(f);
	rename(filename_tmp, filename);
	info(udev, "created db file for '%s' in '%s'\n", udev_device_get_devpath(udev_device), filename);
out:
	return 0;
}

int udev_device_delete_db(struct udev_device *udev_device)
{
	struct udev *udev = udev_device_get_udev(udev_device);
	char filename[UTIL_PATH_SIZE];

	util_strscpyl(filename, sizeof(filename), udev_get_dev_path(udev), "/.udev/db/",
		      udev_device_get_subsystem(udev_device), ":", udev_device_get_sysname(udev_device), NULL);
	unlink(filename);
	return 0;
}
