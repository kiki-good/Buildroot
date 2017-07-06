#############################################################
#
# bluez
#
#############################################################
BLUEZ_VERSION:=5.8
BLUEZ_SOURCE:=bluez-$(BLUEZ_VERSION).tar.bz2
BLUEZ_BINARY_SOURCE:=bluez-$(BLUEZ_VERSION)-binary.tar.bz2
BLUEZ_SITE:=https://www.kernel.org/pub/linux/bluetooth/
BLUEZ_CAT:=$(BZCAT)
BLUEZ_DIR:=$(BUILD_DIR)/bluez-$(BLUEZ_VERSION)
BLUEZ_BINARY:=/NDS/libexec/bluetoothd
BLUEZ_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
BLUEZ_BINARY_DIR:=$(BLUEZ_BOARD_PATH)/binaries
BLUEZ_INSTALL_BINARY:=$(BLUEZ_BINARY_DIR)/$(BLUEZ_BINARY_SOURCE)
BLUEZ_TEMP_DIR:=$(BLUEZ_BINARY_DIR)/bluez_tmp
ifeq ($(BR2_SKY_BUILD_TYPE), "debug")
BLUEZ_CLIENT_OPTS:=--bindir=/usr/bin\
		  --sbindir=/usr/sbin\
		  --enable-client\
		  --enable-tools
else
BLUEZ_CLIENT_OPTS:=--disable-client\
		   --disable-tools
endif 

$(DL_DIR)/$(BLUEZ_SOURCE):
	 $(WGET) -P $(DL_DIR) $(BLUEZ_SITE)/$(BLUEZ_SOURCE)

bluez-source: $(DL_DIR)/$(BLUEZ_SOURCE)

$(BLUEZ_DIR)/.unpacked: $(DL_DIR)/$(BLUEZ_SOURCE)
	$(BLUEZ_CAT) $(DL_DIR)/$(BLUEZ_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(BLUEZ_DIR) $(BR2_BOARD_PATH)/kernel-patches bluez-$(BLUEZ_VERSION)\*.patch*
	toolchain/patch-kernel.sh $(BLUEZ_DIR) package/bluez/ bluez-$(BLUEZ_VERSION)\*.patch*
	touch $(BLUEZ_DIR)/.unpacked

$(BLUEZ_DIR)/.configured: $(BLUEZ_DIR)/.unpacked

	(cd $(BLUEZ_DIR); rm -rf config.cache; \
	cd $(BLUEZ_DIR); \
	$(TARGET_CONFIGURE_OPTS) \
	$(TARGET_CONFIGURE_ARGS) \
	./configure \
		--build=$(GNU_HOST_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--target=$(GNU_TARGET_NAME) \
		--prefix=/NDS \
		--datadir=/NDS/share \
		--with-dbusconfdir=/DBUS/etc/dbus-1/ \
		--with-dbussystembusdir=/DBUS/share/dbus-1/system-services/ \
		--with-dbussessionbusdir=/DBUS/share/dbus-1/system-services/ \
		--localstatedir=/NDS/var \
		--sysconfdir=/NDS/etc \
		--with-gnu-ld \
		--enable-library \
		--disable-monitor \
		--disable-udev \
		--disable-cups \
		--disable-obex \
		--enable-systemd \
		--disable-datafiles \
		--disable-android \
		$(BLUEZ_CLIENT_OPTS) \
		--with-systemdsystemunitdir=/DBUS/share/dbus-1/system-services/ \
		--with-systemduserunitdir=/DBUS/share/dbus-1/services/ \
		CFLAG="-I$(BLUEZ_DIR)/lib/bluetooth" \
		LDFLAGS="-L$(STAGING_DIR)/usr/lib/ -L$(STAGING_DIR)/lib -L$(STAGING_DIR)/NDS/lib" \
		LIBS="-lncurses")
	touch $(BLUEZ_DIR)/.configured

$(STAGING_DIR)/NDS/libexec/bluetooth/bluetoothd: $(BLUEZ_DIR)/.configured
	$(MAKE) -C $(BLUEZ_DIR)	$(TARGET_CONFIGURE_OPTS) $(TARGET_CONFIGURE_ARGS)
	$(MAKE) DESTDIR=$(STAGING_DIR) -C $(BLUEZ_DIR) install
	mkdir -p $(BLUEZ_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(BLUEZ_TEMP_DIR) -C $(BLUEZ_DIR) install

$(TARGET_DIR)/$(BLUEZ_BINARY): $(STAGING_DIR)/NDS/libexec/bluetooth/bluetoothd
	$(MAKE) DESTDIR=$(TARGET_DIR) -C $(BLUEZ_DIR) install	
ifeq ($(BR2_SKY_BUILD_TYPE), "debug")
	$(INSTALL) -m 0755 package/bluez/program_bt_chip_settings.sh $(TARGET_DIR)/sbin/
	$(INSTALL) -m 0666 package/bluez/pskey_reduce_inquiry_priority_and_disable_deep_sleep.psr $(TARGET_DIR)/etc/
	$(INSTALL) -m 0666 package/bluez/pskey_coex_transaction_priority_table.psr $(TARGET_DIR)/etc/
endif
	cp -rf $(STAGING_DIR)/NDS/lib/libbluetooth.* $(TARGET_DIR)/usr/lib
#	cp -rf $(STAGING_DIR)/usr/lib/bluetooth/* $(TARGET_DIR)/usr/bin
	cp -rf $(STAGING_DIR)/NDS/libexec/bluetooth/* $(TARGET_DIR)/NDS/libexec/bluetooth/ 
	-mkdir -p $(TARGET_DIR)/NDS/etc/bluetooth
	-mkdir -p $(TARGET_DIR)/NDS/var/lib/bluetooth
	chmod 0755 $(TARGET_DIR)/NDS/etc/bluetooth
	chmod 0755 $(TARGET_DIR)/NDS/var/lib
	chmod 0700 $(TARGET_DIR)/NDS/var/lib/bluetooth
	sed -i 's/Sky/$(BR2_BOARD_NAME)/g' $(BLUEZ_DIR)/src/main.conf	
	-cp -rf $(STAGING_DIR)/DBUS/etc/dbus-1/system.d/* $(TARGET_DIR)/DBUS/etc/dbus-1/system.d/
	cp -rf $(BLUEZ_DIR)/src/bluetooth.conf $(TARGET_DIR)/DBUS/etc/dbus-1/system.d/
	cp -rf $(BLUEZ_DIR)/src/main.conf $(TARGET_DIR)/NDS/etc/bluetooth/
ifeq ($(BLUEZ_VERSION), "5.5")
	cp -rf $(BLUEZ_DIR)/profiles/audio/audio.conf $(TARGET_DIR)/NDS/etc/bluetooth/
endif
	cp -rf $(BLUEZ_DIR)/profiles/network/network.conf $(TARGET_DIR)/NDS/etc/bluetooth/
	cp -rf $(BLUEZ_DIR)/profiles/proximity/proximity.conf $(TARGET_DIR)/NDS/etc/bluetooth/
	cp -rf $(BLUEZ_DIR)/profiles/input/input.conf $(TARGET_DIR)/NDS/etc/bluetooth/
	rm -rf $(TARGET_DIR)/usr/share/gtk-doc
	rm -rf $(TARGET_DIR)/usr/share/glib-2.0
	rm -rf $(TARGET_DIR)/usr/share/gdb
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libbluetooth*.so*
	mkdir -p $(BLUEZ_TEMP_DIR)/temp_dir_to_target
	cp -rf $(BLUEZ_DIR)/src/bluetooth.conf $(BLUEZ_TEMP_DIR)/temp_dir_to_target
	cp -rf $(BLUEZ_DIR)/src/main.conf $(BLUEZ_TEMP_DIR)/temp_dir_to_target
ifeq ($(BLUEZ_VERSION), "5.5")
	cp -rf $(BLUEZ_DIR)/profiles/audio/audio.conf $(BLUEZ_TEMP_DIR)/temp_dir_to_target
endif
	cp -rf $(BLUEZ_DIR)/profiles/network/network.conf $(TARGET_DIR)/NDS/etc/bluetooth/
	cp -rf $(BLUEZ_DIR)/profiles/network/network.conf $(BLUEZ_TEMP_DIR)/temp_dir_to_target
	cp -rf $(BLUEZ_DIR)/profiles/proximity/proximity.conf $(BLUEZ_TEMP_DIR)/temp_dir_to_target
	cp -rf $(BLUEZ_DIR)/profiles/input/input.conf $(BLUEZ_TEMP_DIR)/temp_dir_to_target
	tar cjvf $(BLUEZ_BINARY_DIR)/$(BLUEZ_BINARY_SOURCE) -C $(BLUEZ_TEMP_DIR) .
	rm -rf $(BLUEZ_TEMP_DIR)
ifneq ($(BR2_SKY_BUILD_TYPE), "debug")
	rm -rf $(TARGET_DIR)/NDS/libexec/bluetooth/obexd
	sed -i "/^#/d" $(TARGET_DIR)/NDS/etc/bluetooth/proximity.conf 
	sed -i "/^#/d" $(TARGET_DIR)/NDS/etc/bluetooth/input.conf 
	sed -i "/^#/d" $(TARGET_DIR)/NDS/etc/bluetooth/network.conf
	sed -i "/^#/d" $(TARGET_DIR)/NDS/etc/bluetooth/main.conf 
	sed -i "/^$$/d" $(TARGET_DIR)/NDS/etc/bluetooth/proximity.conf 
	sed -i "/^$$/d" $(TARGET_DIR)/NDS/etc/bluetooth/input.conf 
	sed -i "/^$$/d" $(TARGET_DIR)/NDS/etc/bluetooth/network.conf
	sed -i "/^$$/d" $(TARGET_DIR)/NDS/etc/bluetooth/main.conf 
endif

bluez-binary:
ifeq ($(BR2_SKY_BUILD_TYPE), "debug")
	$(INSTALL) -m 0755 package/bluez/program_bt_chip_settings.sh $(TARGET_DIR)/sbin/
	$(INSTALL) -m 0666 package/bluez/pskey_reduce_inquiry_priority_and_disable_deep_sleep.psr $(TARGET_DIR)/etc/
	$(INSTALL) -m 0666 package/bluez/pskey_coex_transaction_priority_table.psr $(TARGET_DIR)/etc/
endif
	tar xjvf $(BLUEZ_BINARY_DIR)/$(BLUEZ_BINARY_SOURCE) -C $(STAGING_DIR)/
	cp -rf $(STAGING_DIR)/NDS/lib/libbluetooth.* $(TARGET_DIR)/usr/lib
#	cp -rf $(STAGING_DIR)/usr/lib/bluetooth/* $(TARGET_DIR)/usr/bin
	-mkdir -p $(TARGET_DIR)/NDS/libexec/bluetooth/
	cp -rf $(STAGING_DIR)/NDS/libexec/bluetooth/* $(TARGET_DIR)/NDS/libexec/bluetooth/ 
	cp -rf $(STAGING_DIR)/DBUS/share/dbus-1/* $(TARGET_DIR)/DBUS/share/dbus-1/ 
	-mkdir -p $(TARGET_DIR)/NDS/etc/bluetooth
	-mkdir -p $(TARGET_DIR)/NDS/var/lib/bluetooth
	chmod 0755 $(TARGET_DIR)/NDS/etc/bluetooth
	chmod 0755 $(TARGET_DIR)/NDS/var/lib
	chmod 0700 $(TARGET_DIR)/NDS/var/lib/bluetooth
	cp -rf $(STAGING_DIR)/temp_dir_to_target/bluetooth.conf $(TARGET_DIR)/DBUS/etc/dbus-1/system.d/
	cp -rf $(STAGING_DIR)/temp_dir_to_target/main.conf $(TARGET_DIR)/NDS/etc/bluetooth/
ifeq ($(BLUEZ_VERSION), "5.5")
	cp -rf $(STAGING_DIR)/temp_dir_to_target/audio.conf $(TARGET_DIR)/NDS/etc/bluetooth/
endif
	cp -rf $(STAGING_DIR)/temp_dir_to_target/network.conf $(TARGET_DIR)/NDS/etc/bluetooth/
	cp -rf $(STAGING_DIR)/temp_dir_to_target/proximity.conf $(TARGET_DIR)/NDS/etc/bluetooth/
	cp -rf $(STAGING_DIR)/temp_dir_to_target/input.conf $(TARGET_DIR)/NDS/etc/bluetooth/
	rm -rf $(STAGING_DIR)/usr/share/gtk-doc
	rm -rf $(STAGING_DIR)/usr/share/glib-2.0
	rm -rf $(STAGING_DIR)/usr/share/gdb
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libbluetooth*.so*
	cp -rf $(STAGING_DIR)/usr/bin/hciconfig $(TARGET_DIR)/usr/bin
	cp -rf $(STAGING_DIR)/usr/bin/bccmd $(TARGET_DIR)/usr/bin
ifeq ($(BR2_SKY_BUILD_TYPE), "debug")
	cp -rf $(STAGING_DIR)/usr/bin/hciattach $(TARGET_DIR)/usr/bin
	cp -rf $(STAGING_DIR)/usr/bin/hcitool $(TARGET_DIR)/usr/bin
	cp -rf $(STAGING_DIR)/usr/bin/hcidump $(TARGET_DIR)/usr/bin
	cp -rf $(STAGING_DIR)/usr/bin/rfcomm $(TARGET_DIR)/usr/bin
	cp -rf $(STAGING_DIR)/usr/bin/sdptool $(TARGET_DIR)/usr/bin
	cp -rf $(STAGING_DIR)/usr/bin/ciptool $(TARGET_DIR)/usr/bin
	cp -rf $(STAGING_DIR)/usr/bin/bluetoothctl $(TARGET_DIR)/usr/bin
	cp -rf $(STAGING_DIR)/usr/bin/bdaddr $(TARGET_DIR)/usr/bin
endif
ifneq ($(BR2_SKY_BUILD_TYPE), "debug")
	rm -rf $(TARGET_DIR)/NDS/libexec/bluetooth/obexd
	sed -i "/^#/d" $(TARGET_DIR)/NDS/etc/bluetooth/proximity.conf 
	sed -i "/^#/d" $(TARGET_DIR)/NDS/etc/bluetooth/input.conf 
	sed -i "/^#/d" $(TARGET_DIR)/NDS/etc/bluetooth/network.conf
	sed -i "/^#/d" $(TARGET_DIR)/NDS/etc/bluetooth/main.conf 
	sed -i "/^$$/d" $(TARGET_DIR)/NDS/etc/bluetooth/proximity.conf 
	sed -i "/^$$/d" $(TARGET_DIR)/NDS/etc/bluetooth/input.conf 
	sed -i "/^$$/d" $(TARGET_DIR)/NDS/etc/bluetooth/network.conf
	sed -i "/^$$/d" $(TARGET_DIR)/NDS/etc/bluetooth/main.conf 
endif


ifeq ($(wildcard $(BLUEZ_INSTALL_BINARY)),)
bluez:	uclibc pkgconfig dbus zlib libusb libffi readline gettext libglib2 udev $(TARGET_DIR)/$(BLUEZ_BINARY)
else
bluez:	uclibc pkgconfig dbus zlib libusb libffi readline gettext libglib2 udev bluez-binary
endif

bluez-clean:
	-$(MAKE) -C $(BLUEZ_DIR) clean
	rm -rf $(STAGING_DIR)/NDS/libexec/bluetooth/*
	rm -rf $(TARGET_DIR)/NDS/libexec/bluetooth/*
#	rm -rf $(STAGING_DIR)/usr/lib/libbluetooth.*
#	rm -rf $(STAGING_DIR)/usr/lib/bluetooth/*
	rm -rf $(STAGING_DIR)/usr/bin/hciconfig
	rm -rf $(STAGING_DIR)/usr/bin/bccmd
	rm -rf $(TARGET_DIR)/usr/bin/hciconfig
	rm -rf $(TARGET_DIR)/usr/bin/bccmd
ifeq ($(BR2_SKY_BUILD_TYPE), "debug")
	rm -rf $(STAGING_DIR)/usr/bin/hciattach
	rm -rf $(STAGING_DIR)/usr/bin/hcitool
	rm -rf $(STAGING_DIR)/usr/bin/hcidump
	rm -rf $(STAGING_DIR)/usr/bin/rfcomm
	rm -rf $(STAGING_DIR)/usr/bin/rctest
	rm -rf $(STAGING_DIR)/usr/bin/l2test
	rm -rf $(STAGING_DIR)/usr/bin/l2ping
	rm -rf $(STAGING_DIR)/usr/bin/sdptool
	rm -rf $(STAGING_DIR)/usr/bin/ciptool
	rm -rf $(STAGING_DIR)/usr/bin/bluetoothctl
	rm -rf $(STAGING_DIR)/usr/bin/bdaddr
	rm -rf $(TARGET_DIR)/usr/bin/hciattach
	rm -rf $(TARGET_DIR)/usr/bin/hcitool
	rm -rf $(TARGET_DIR)/usr/bin/hcidump
	rm -rf $(TARGET_DIR)/usr/bin/rfcomm
	rm -rf $(TARGET_DIR)/usr/bin/rctest
	rm -rf $(TARGET_DIR)/usr/bin/l2test
	rm -rf $(TARGET_DIR)/usr/bin/l2ping
	rm -rf $(TARGET_DIR)/usr/bin/sdptool
	rm -rf $(TARGET_DIR)/usr/bin/ciptool
	rm -rf $(TARGET_DIR)/usr/bin/bluetoothctl
	rm -rf $(TARGET_DIR)/usr/bin/bdaddr
endif
bluez-dirclean:
	rm -rf $(BLUEZ_DIR)

bluez-binary-clean:
	rm -rf $(BLUEZ_INSTALL_BINARY)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_BLUEZ),y)
TARGETS+=bluez
BLUEZ_DEPENDS+=dbus
BLUEZ_DEPENDS+=libglib2 
BLUEZ_DEPENDS+=libusb
BLUEZ_DEPENDS+=libffi
BLUEZ_DEPENDS+=readline
BLUEZ_DEPENDS+=udev
endif
