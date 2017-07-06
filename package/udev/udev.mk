#############################################################
#
# udev
#
#############################################################
ifeq ($(BR2_ARCH_IS_64),y)
UDEV_VERSION:=164
else
UDEV_VERSION:=164
endif
UDEV_VOLUME_ID_CURRENT:=0
UDEV_VOLUME_ID_AGE:=79
UDEV_VOLUME_ID_REVISION:=0
UDEV_VOLUME_ID_VERSION:=$(UDEV_VOLUME_ID_CURRENT).$(UDEV_VOLUME_ID_AGE).$(UDEV_VOLUME_ID_REVISION)
UDEV_SOURCE:=udev-$(UDEV_VERSION).tar.bz2
UDEV_BINARY_SOURCE:=udev-$(UDEV_VERSION)-binary.tar.bz2
UDEV_SITE:=$(BR2_KERNEL_MIRROR)/linux/utils/kernel/hotplug/
UDEV_CAT:=$(BZCAT)
UDEV_DIR:=$(BUILD_DIR)/udev-$(UDEV_VERSION)
UDEV_TARGET_BINARY:=sbin/udevd
UDEV_BINARY:=udevd
UDEV_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
UDEV_BINARY_DIR:=$(UDEV_BOARD_PATH)/binaries
UDEV_INSTALL_BINARY:=$(UDEV_BINARY_DIR)/$(UDEV_BINARY_SOURCE)
UDEV_TEMP_DIR:=$(UDEV_BINARY_DIR)/udev_tmp

# 094 had _GNU_SOURCE set
BR2_UDEV_CFLAGS:= -D_GNU_SOURCE $(TARGET_CFLAGS)
ifeq ($(BR2_LARGEFILE),)
BR2_UDEV_CFLAGS+=-U_FILE_OFFSET_BITS
endif

UDEV_EXTRAS=no
ifeq ($(BR2_PACKAGE_UDEV_VOLUME_ID),y)
UDEV_EXTRAS=yes
endif
ifeq ($(BR2_PACKAGE_UDEV_SCSI_ID),y)
UDEV_EXTRAS=yes
endif

# UDEV_ROOT is /dev so we can replace devfs, not /udev for experiments
UDEV_ROOT:=/dev

$(DL_DIR)/$(UDEV_SOURCE):
	 $(WGET) -P $(DL_DIR) $(UDEV_SITE)/$(UDEV_SOURCE)

$(UDEV_DIR)/.unpacked: $(DL_DIR)/$(UDEV_SOURCE)
	$(UDEV_CAT) $(DL_DIR)/$(UDEV_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -

ifneq ($(BR2_ARCH_IS_64),y)
	toolchain/patch-kernel.sh $(UDEV_DIR) package/udev udev-$(UDEV_VERSION)-\*.patch
ifneq ($(BR2_SKY_BUILD_TYPE),"debug")
	toolchain/patch-kernel.sh $(UDEV_DIR) package/udev udev-Hardening-$(UDEV_VERSION)-\*.patch
endif

else
	toolchain/patch-kernel.sh $(UDEV_DIR) package/udev/64bitPatch udev-$(UDEV_VERSION)-\*.patch
ifneq ($(BR2_SKY_BUILD_TYPE),"debug")
	toolchain/patch-kernel.sh $(UDEV_DIR) package/udev/64bitPatch udev-Hardening-$(UDEV_VERSION)-\*.patch
endif
endif
	cd $(UDEV_DIR) && $(AUTOCONF) 
	touch $@

$(UDEV_DIR)/.configured: $(UDEV_DIR)/.unpacked
ifeq ($(BR2_SKY_BUILD_TYPE),"debug")
	(cd $(UDEV_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		GLIB_LIBS="$(STAGING_DIR)/usr/lib/libglib-2.0.so $(STAGING_DIR)/usr/lib/libgobject-2.0.so $(STAGING_DIR)/usr/lib/libgmodule-2.0.so $(STAGING_DIR)/usr/lib/libgthread-2.0.so $(STAGING_DIR)/usr/lib/libgio-2.0.so" \
		LIBUSB_LIBS="$(STAGING_DIR)/usr/lib/libusb.so" \
		LDFLAGS=-L"$(STAGING_DIR)/usr/lib/" \
		ac_cv_header_regex_h=no \
		ac_cv_lib_acl_acl_init=yes \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--with-pci-ids-path=$(TARGET_DIR)/usr/share/ \
		--prefix=/usr \
		--disable-debug \
		--disable-build-docs \
		--enable-extras=$(UDEV_EXTRAS) \
		--disable-introspection \
		--disable-gtk-doc-html \
	)
endif
ifneq ($(BR2_SKY_BUILD_TYPE),"debug")
	(cd $(UDEV_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		GLIB_LIBS="$(STAGING_DIR)/usr/lib/libglib-2.0.so $(STAGING_DIR)/usr/lib/libgobject-2.0.so $(STAGING_DIR)/usr/lib/libgmodule-2.0.so $(STAGING_DIR)/usr/lib/libgthread-2.0.so $(STAGING_DIR)/usr/lib/libgio-2.0.so" \
		LIBUSB_LIBS="$(STAGING_DIR)/usr/lib/libusb.so" \
		LDFLAGS=-L"$(STAGING_DIR)/usr/lib/" \
		ac_cv_header_regex_h=no \
		ac_cv_lib_acl_acl_init=yes \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--with-pci-ids-path=$(TARGET_DIR)/usr/share/ \
		--prefix=/usr \
		--disable-debug \
		--disable-build-docs \
		--enable-extras \
		--disable-logging \
		--disable-introspection \
		--disable-gtk-doc-html \
	)
endif
	touch $@

$(UDEV_DIR)/$(UDEV_BINARY): $(UDEV_DIR)/.configured
	$(MAKE) CROSS_COMPILE=$(TARGET_CROSS) CC=$(TARGET_CC) LD=$(TARGET_CC)\
		CFLAGS="$(BR2_UDEV_CFLAGS)" \
		USE_LOG=false USE_SELINUX=false \
		udevdir=$(UDEV_ROOT) -C $(UDEV_DIR)
	touch -c $@

$(TARGET_DIR)/$(UDEV_TARGET_BINARY): $(UDEV_DIR)/$(UDEV_BINARY)
	mkdir -p $(TARGET_DIR)/sys
	$(MAKE) $(TARGET_CONFIGURE_OPTS) \
		DESTDIR=$(STAGING_DIR)\
		CFLAGS="$(BR2_UDEV_CFLAGS)" \
		LDFLAGS="-warn-common" \
		USE_LOG=false USE_SELINUX=false \
		udevdir=$(UDEV_ROOT) -C $(UDEV_DIR) install
	cp -drf $(UDEV_DIR)/udev/udev.pc $(STAGING_DIR)/usr/lib/pkgconfig
	cp -drf $(UDEV_DIR)/libudev/libudev.pc $(STAGING_DIR)/usr/lib/pkgconfig
ifeq ($(wildcard $(UDEV_INSTALL_BINARY)),)
	mkdir -p $(UDEV_TEMP_DIR)/usr/lib/
	mkdir -p $(UDEV_TEMP_DIR)/usr/include/
	cp -drf $(UDEV_DIR)/libudev/.libs/libudev.so* $(STAGING_DIR)/usr/lib/
	cp -drf $(UDEV_DIR)/libudev/.libs/libudev.so* $(TARGET_DIR)/usr/lib/
	cp -drf $(UDEV_DIR)/libudev/.libs/libudev.so* $(UDEV_TEMP_DIR)/usr/lib/
	cp -rf $(STAGING_DIR)/usr/include/libudev.h $(UDEV_TEMP_DIR)/usr/include/
	tar cjvf $(UDEV_BINARY_DIR)/$(UDEV_BINARY_SOURCE) -C $(UDEV_TEMP_DIR) .
	rm -rf $(UDEV_TEMP_DIR)
else
	tar xjvf $(UDEV_BINARY_DIR)/$(UDEV_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar xjvf $(UDEV_BINARY_DIR)/$(UDEV_BINARY_SOURCE) -C $(TARGET_DIR)/
	rm -rf $(TARGET_DIR)/usr/include/
endif
ifeq ($(UDEV_EXTRAS),yes)
	cp -drf $(UDEV_DIR)/extras/gudev/gudev-1.0.pc $(STAGING_DIR)/usr/lib/pkgconfig
	cp -drf $(UDEV_DIR)/extras/gudev/.libs/libgudev-1.0.so* $(STAGING_DIR)/usr/lib/
	cp -drf $(UDEV_DIR)/extras/gudev/.libs/libgudev-1.0.so* $(TARGET_DIR)/usr/lib/
	cp -drf	$(STAGING_DIR)/usr/lib/ConsoleKit/ $(TARGET_DIR)/usr/lib
endif
	cp -drf $(STAGING_DIR)/usr/etc/udev $(TARGET_DIR)/etc/
	cp -drf $(STAGING_DIR)/usr/sbin/udev* $(TARGET_DIR)/sbin/
	cp -drf $(STAGING_DIR)/usr/libexec/  $(TARGET_DIR)/usr/
		
	( grep udev_root $(TARGET_DIR)/etc/udev/udev.conf > /dev/null 2>&1 || echo 'udev_root=/dev' >> $(TARGET_DIR)/etc/udev/udev.conf )
	rm -rf $(TARGET_DIR)/usr/share/man
	rm -rf $(TARGET_DIR)/usr/share/gtk-doc
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/60-persistent-storage.rules
ifneq ($(BR2_SKY_BUILD_TYPE),"debug")
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/60-cdrom_id.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/60-persistent-serial.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/78-sound-card.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/61-persistent-storage-edd.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/61-mobile-action.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/60-persistent-alsa.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/60-persistent-storage-tape.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/95-keyboard-force-release.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/60-floppy.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/60-persistent-input.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/95-keymap.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/60-persistent-v4l.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/75-cd-aliases-generator.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/80-drivers.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/70-acl.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/75-tty-description.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/79-fstab_import.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/75-probe_mtd.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/75-net-description.rules
	rm -f $(TARGET_DIR)/usr/libexec/rules.d/75-persistent-net-generator.rules
	rm -rf $(TARGET_DIR)/usr/libexec/keymaps/*
	rm -rf $(TARGET_DIR)/usr/libexec/write_cd_rules
	rm -rf $(TARGET_DIR)/usr/libexec/write_net_rules
	rm -rf $(TARGET_DIR)/usr/libexec/rule_generator.functions
	rm -rf $(TARGET_DIR)/etc/udev/rules.d
	sed -i "/^#/d" $(TARGET_DIR)/etc/udev/udev.conf
	sed -i "/^$$/d" $(TARGET_DIR)/etc/udev/udev.conf
	rm -rf $(TARGET_DIR)/usr/libexec/fstab_import
	rm -rf $(TARGET_DIR)/usr/libexec/cdrom_id
	rm -rf $(TARGET_DIR)/usr/libexec/create_floppy_devices
	rm -rf $(TARGET_DIR)/usr/libexec/edd_id
	rm -rf $(TARGET_DIR)/usr/libexec/v4l_id
	rm -rf $(TARGET_DIR)/usr/libexec/scsi_id
	rm -rf $(TARGET_DIR)/usr/libexec/path_id
	rm -rf $(TARGET_DIR)/usr/libexec/input_id
	rm -rf $(TARGET_DIR)/usr/libexec/keymap
	rm -rf $(TARGET_DIR)/usr/libexec/keymaps
	rm -rf $(TARGET_DIR)/usr/libexec/findkeyboards
	rm -rf $(TARGET_DIR)/usr/libexec/pci-db
	rm -rf $(TARGET_DIR)/usr/libexec/usb-db
	rm -rf $(TARGET_DIR)/usr/libexec/mtd_probe
	rm -rf $(TARGET_DIR)/usr/libexec/mobile-action-modeswitch
endif
ifneq ($(BR2_PACKAGE_UDEV_UTILS),y)
	rm -f $(TARGET_DIR)/usr/sbin/udevmonitor
	rm -f $(TARGET_DIR)/usr/bin/udevinfo
	rm -f $(TARGET_DIR)/usr/bin/udevtest
endif

#####################################################################
.PHONY: udev-source udev udev-clean udev-dirclean

udev: libacl usbutils pciutils libffi libglib2 $(TARGET_DIR)/$(UDEV_TARGET_BINARY)

udev-source: $(DL_DIR)/$(UDEV_SOURCE)

udev-clean: $(UDEV_CLEAN_DEPS)
	rm -f $(TARGET_DIR)/usr/sbin/udevmonitor $(TARGET_DIR)/usr/bin/udev*
	rm -fr $(TARGET_DIR)/sys
	-$(MAKE) -C $(UDEV_DIR) clean


udev-dirclean: $(UDEV_DIRCLEAN_DEPS)
	rm -rf $(UDEV_DIR)

#####################################################################
ifeq ($(BR2_PACKAGE_UDEV_VOLUME_ID),y)
.PHONY: udev-volume_id udev-volume_id-clean udev-volume_id-dirclean

$(STAGING_DIR)/usr/lib/libvolume_id.so.$(UDEV_VOLUME_ID_VERSION):
	$(MAKE) CROSS_COMPILE=$(TARGET_CROSS) \
		CFLAGS="$(BR2_UDEV_CFLAGS)" \
		USE_LOG=false USE_SELINUX=false \
		udevdir=$(UDEV_ROOT) EXTRAS="extras/volume_id" -C $(UDEV_DIR)
	$(INSTALL) -m 0644 -D $(UDEV_DIR)/extras/volume_id/lib/libvolume_id.h $(STAGING_DIR)/usr/include/libvolume_id.h
	$(INSTALL) -m 0755 -D $(UDEV_DIR)/extras/volume_id/lib/libvolume_id.so.$(UDEV_VOLUME_ID_VERSION) $@
	-ln -sf libvolume_id.so.$(UDEV_VOLUME_ID_VERSION) $(STAGING_DIR)/usr/lib/libvolume_id.so.0
	-ln -sf libvolume_id.so.$(UDEV_VOLUME_ID_VERSION) $(STAGING_DIR)/usr/lib/libvolume_id.so

$(STAGING_DIR)/usr/lib/libvolume_id.la: $(STAGING_DIR)/usr/lib/libvolume_id.so.$(UDEV_VOLUME_ID_VERSION)
	$(INSTALL) -m 0755 -D package/udev/libvolume_id.la.tmpl $@
	$(SED) 's/REPLACE_CURRENT/$(UDEV_VOLUME_ID_CURRENT)/g' $@
	$(SED) 's/REPLACE_AGE/$(UDEV_VOLUME_ID_AGE)/g' $@
	$(SED) 's/REPLACE_REVISION/$(UDEV_VOLUME_ID_REVISION)/g' $@
	$(SED) 's,REPLACE_LIB_DIR,$(STAGING_DIR)/usr/lib,g' $@

$(TARGET_DIR)/lib/udev/vol_id: $(STAGING_DIR)/usr/lib/libvolume_id.la
	$(INSTALL) -m 0755 -D $(UDEV_DIR)/extras/volume_id/lib/libvolume_id.so.$(UDEV_VOLUME_ID_VERSION) $(TARGET_DIR)/usr/lib/libvolume_id.so.$(UDEV_VOLUME_ID_VERSION)
	-ln -sf libvolume_id.so.$(UDEV_VOLUME_ID_VERSION) $(TARGET_DIR)/usr/lib/libvolume_id.so.0
	-ln -sf libvolume_id.so.$(UDEV_VOLUME_ID_VERSION) $(TARGET_DIR)/usr/lib/libvolume_id.so
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libvolume_id.so.$(UDEV_VOLUME_ID_VERSION)
	$(INSTALL) -m 0755 -D $(UDEV_DIR)/extras/volume_id/vol_id $@

udev-volume_id: udev $(TARGET_DIR)/lib/udev/vol_id

udev-volume_id-clean:
	rm -f $(STAGING_DIR)/usr/include/libvolume_id.h
	rm -f $(STAGING_DIR)/usr/lib/libvolume_id.so*
	rm -f $(STAGING_DIR)/usr/lib/libvolume_id.la
	rm -f $(TARGET_DIR)/usr/lib/libvolume_id.so.0*
	rm -f $(TARGET_DIR)/lib/udev/vol_id
	rmdir --ignore-fail-on-non-empty $(TARGET_DIR)/lib/udev

udev-volume_id-dirclean:
	-$(MAKE) EXTRAS="extras/volume_id" -C $(UDEV_DIR) clean

UDEV_CLEAN_DEPS+=udev-volume_id-clean
UDEV_DIRCLEAN_DEPS+=udev-volume_id-dirclean
endif

#####################################################################
ifeq ($(BR2_PACKAGE_UDEV_SCSI_ID),y)
.PHONY: udev-scsi_id udev-scsi_id-clean udev-scsi_id-dirclean

$(TARGET_DIR)/lib/udev/scsi_id: $(STAGING_DIR)/usr/lib/libvolume_id.so.$(UDEV_VOLUME_ID_VERSION)
	$(MAKE) CROSS_COMPILE=$(TARGET_CROSS) \
		CFLAGS="$(BR2_UDEV_CFLAGS)" \
		USE_LOG=false USE_SELINUX=false \
		udevdir=$(UDEV_ROOT) EXTRAS="extras/scsi_id" -C $(UDEV_DIR)
	$(INSTALL) -m 0755 -D $(UDEV_DIR)/extras/scsi_id/scsi_id $@
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $@

$(TARGET_DIR)/lib/udev/usb_id: $(STAGING_DIR)/usr/lib/libvolume_id.so.$(UDEV_VOLUME_ID_VERSION)
	$(MAKE) CROSS_COMPILE=$(TARGET_CROSS) \
		CFLAGS="$(BR2_UDEV_CFLAGS)" \
		USE_LOG=false USE_SELINUX=false \
		udevdir=$(UDEV_ROOT) EXTRAS="extras/usb_id" -C $(UDEV_DIR)
	$(INSTALL) -m 0755 -D $(UDEV_DIR)/extras/usb_id/usb_id $@
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $@

udev-scsi_id: udev $(TARGET_DIR)/lib/udev/scsi_id $(TARGET_DIR)/lib/udev/usb_id

udev-scsi_id-clean:
	rm -f $(TARGET_DIR)/lib/udev/scsi_id
	rm -f $(TARGET_DIR)/lib/udev/usb_id
	rmdir --ignore-fail-on-non-empty $(TARGET_DIR)/lib/udev

udev-scsi_id-dirclean:
	-$(MAKE) EXTRAS="extras/scsi_id" -C $(UDEV_DIR) clean

UDEV_CLEAN_DEPS+=udev-scsi_id-clean
UDEV_DIRCLEAN_DEPS+=udev-scsi_id-dirclean
endif

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_UDEV),y)
TARGETS+=udev
endif

ifeq ($(BR2_PACKAGE_UDEV_VOLUME_ID),y)
TARGETS+=udev-volume_id
endif

ifeq ($(BR2_PACKAGE_UDEV_SCSI_ID),y)
TARGETS+=udev-scsi_id
endif
