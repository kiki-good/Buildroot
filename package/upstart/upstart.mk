#############################################################
#
# UPSTART
#
#############################################################
UPSTART_VERSION:=1.13.2
UPSTART_SITE:=http://upstart.ubuntu.com/download/$(UPSTART_VERSION)
UPSTART_SOURCE:=upstart-$(UPSTART_VERSION).tar.gz
UPSTART_DIR:=$(BUILD_DIR)/upstart-$(UPSTART_VERSION)
UPSTART_CAT:=$(ZCAT) 
UPSTART_BINARY:=init
UPSTART_TARGET_BINARY:=sbin/init
ifeq ($(BR2_TOOLCHAIN_EXTERNAL_PREFIX),"armv7-linux")
DEV_TTY=ttyAS0
else
DEV_TTY=ttyS0
endif

$(DL_DIR)/$(UPSTART_SOURCE): 
	$(WGET) -P $(DL_DIR) $(UPSTART_SITE)/$(UPSTART_SOURCE)

upstart-source: $(DL_DIR)/$(UPSTART_SOURCE)

upstart-unpacked: $(UPSTART_DIR)/.unpacked
$(UPSTART_DIR)/.unpacked: $(DL_DIR)/$(UPSTART_SOURCE)
	$(UPSTART_CAT) $(DL_DIR)/$(UPSTART_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(UPSTART_DIR) package/upstart/ upstart-$(UPSTART_VERSION)-\*.patch
ifneq ($(BR2_CONSOLE_SUPPORT),y)
	toolchain/patch-kernel.sh $(UPSTART_DIR) package/upstart/ upstart-$(UPSTART_VERSION)Console-disable.patch
	toolchain/patch-kernel.sh $(UPSTART_DIR) package/upstart/ upstart-$(UPSTART_VERSION)Remove-blanks-remarks.patch
	toolchain/patch-kernel.sh $(UPSTART_DIR) package/upstart/ upstart-$(UPSTART_VERSION)RemovingCode_rc-sysinit.patch
endif
ifeq ($(BR2_SKY_BUILD_TYPE),"prod")
ifneq ($(BR2_CONSOLE_SUPPORT),y)
	toolchain/patch-kernel.sh $(UPSTART_DIR) package/upstart/ upstart-$(UPSTART_VERSION)DevPTS.patch
endif
endif
	touch $@

$(UPSTART_DIR)/.configured: $(UPSTART_DIR)/.unpacked
	(cd $(UPSTART_DIR); rm -rf config.cache; \
                $(TARGET_CONFIGURE_OPTS) \
                $(TARGET_CONFIGURE_ARGS) \
                ./configure \
                --target=$(GNU_TARGET_NAME) \
                --host=$(GNU_TARGET_NAME) \
                --build=$(GNU_HOST_NAME) \
                --with-gnu-ld \
		--with-libiconv-prefix=$(STAGING_DIR)/usr \
		--with-libintl-prefix=$(STAGING_DIR)/usr \
                prefix=/ \
                --exec-prefix=/ \
                NIH_CFLAGS="-I$(STAGING_DIR)/usr/include/" \
                NIH_LIBS="$(TARGET_DIR)/usr/lib/libnih.so.1.0.0" \
                NIH_DBUS_CFLAGS="-I$(STAGING_DIR)/usr/include/" \
                NIH_DBUS_LIBS="$(TARGET_DIR)/usr/lib/libnih-dbus.so.1.0.0" \
		NIH_DBUS_TOOL="$(LIBNIH_HOST_DIR)/nih-dbus-tool/nih-dbus-tool" \
		DBUS_CFLAGS="-I$(STAGING_DIR)/usr/include/dbus-1.0 -I$(STAGING_DIR)/usr/lib/dbus-1.0/include" \
		DBUS_LIBS="$(STAGING_DIR)/usr/lib/libdbus-1.so" \
                JSON_CFLAGS="-I$(JSON_C_DIR)/ -I$(STAGING_DIR)/usr/include/ -I$(STAGING_DIR)/usr/include/json/" \
                JSON_LIBS="-L$(STAGING_DIR)/usr/lib -ljson" \
                CFLAG="-I$(STAGING_DIR)/usr/include" \
		LDFLAGS="$(TARGET_LDFLAGS) -L$(TARGET_DIR)/lib" \
        )
	touch $@

$(STAGING_DIR)/$(UPSTART_BINARY): $(UPSTART_DIR)/.configured
	$(MAKE)	-C $(UPSTART_DIR)

$(STAGING_DIR)/$(UPSTART_TARGET_BINARY): $(STAGING_DIR)/$(UPSTART_BINARY)
	$(MAKE) DESTDIR=$(TARGET_DIR) -C $(UPSTART_DIR) install
	$(MAKE) DESTDIR=$(STAGING_DIR) -C $(UPSTART_DIR) install
	#cp $(UPSTART_DIR)/dbus/Upstart.conf $(TARGET_DIR)/DBUS/etc/dbus-1/system.d/
	mv $(TARGET_DIR)/etc/dbus-1/system.d/Upstart.conf $(TARGET_DIR)/DBUS/etc/dbus-1/system.d/
	chmod 0444 $(TARGET_DIR)/share/applications/upstart-monitor.desktop
	chmod 0444 $(TARGET_DIR)/share/upstart/sessions/re-exec.conf
	chmod 0444 $(TARGET_DIR)/share/upstart/sessions/upstart-file-bridge.conf
	chmod 0444 $(TARGET_DIR)/share/upstart/sessions/upstart-dbus-system-bridge.conf
	chmod 0444 $(TARGET_DIR)/share/upstart/sessions/upstart-dbus-session-bridge.conf
	chmod 0444 $(TARGET_DIR)/share/upstart/sessions/upstart-dconf-bridge.conf
	chmod 0444 $(TARGET_DIR)/share/upstart/sessions/upstart-event-bridge.conf
	chmod 0444 $(TARGET_DIR)/share/upstart/icons/upstart-monitor.svg
	chmod 0444 $(TARGET_DIR)/lib/pkgconfig/libupstart.pc
	chmod 0444 $(TARGET_DIR)/share/icons/hicolor/scalable/apps/upstart-monitor.svg
	mv $(TARGET_DIR)/sbin/reboot $(TARGET_DIR)/sbin/reboot_upstart
	$(INSTALL) -m 0755 package/upstart/reboot $(TARGET_DIR)/sbin/
	rm -rf $(TARGET_DIR)/bin/init-checkconf
	rm -rf $(TARGET_DIR)/etc/init/upstart-event-bridge.conf
	rm -rf $(TARGET_DIR)/share/locale $(TARGET_DIR)/share/man
	rm -rf $(TARGET_DIR)/include/upstart*
	rm -rf $(TARGET_DIR)/etc/init/control-alt-delete.conf
	rm -rf $(TARGET_DIR)/share/upstart/sessions/upstart-dconf-bridge.conf
	rm -rf $(TARGET_DIR)/bin/upstart-monitor
	rm -rf $(TARGET_DIR)/share/icons	
	rm -rf $(TARGET_DIR)/share/upstart/icons
	rm -rf $(TARGET_DIR)/share/applications
ifneq ($(BR2_SKY_BUILD_TYPE),"debug")
	rm -rf $(TARGET_DIR)/sbin/telinit
endif
ifeq ($(BR2_CONSOLE_SUPPORT),y)
	-sed -i 's/console none/console owner/' $(TARGET_DIR)/etc/init/load.conf
	-sed -i 's/console none/console output/' $(TARGET_DIR)/etc/init/rhad-start.conf
	-sed -i 's/console none/console output/' $(TARGET_DIR)/etc/init/rapid-start.conf
	-sed -i 's/console none/console output/' $(TARGET_DIR)/etc/init/maid-start.conf
	-sed -i 's/console none/console owner/' $(TARGET_DIR)/etc/init/maid-stop.conf
	-sed -i 's/console none/console output/' $(TARGET_DIR)/etc/init/bluez.conf
	-sed -i 's/console none/console output/' $(TARGET_DIR)/etc/init/userver-start.conf
	-sed -i 's/console none/console output/' $(TARGET_DIR)/etc/init/Italian-check.conf
ifeq ($(BR2_SKY_BUILD_TYPE),"debug")
	-sed -i 's/console none/console owner/' $(TARGET_DIR)/etc/init/${DEV_TTY}.conf
endif
else
	-sed -i 's/console owner/console none/' $(TARGET_DIR)/etc/init/load.conf
	-sed -i 's/console output/console none/' $(TARGET_DIR)/etc/init/rhad-start.conf
	-sed -i 's/console output/console none/' $(TARGET_DIR)/etc/init/rapid-start.conf
	-sed -i 's/console output/console none/' $(TARGET_DIR)/etc/init/maid-start.conf
	-sed -i 's/console owner/console none/' $(TARGET_DIR)/etc/init/maid-stop.conf
	-sed -i 's/console output/console none/' $(TARGET_DIR)/etc/init/bluez.conf
	-sed -i 's/console output/console none/' $(TARGET_DIR)/etc/init/userver-start.conf
	-sed -i 's/console output/console none/' $(TARGET_DIR)/etc/init/Italian-check.conf
ifeq ($(BR2_SKY_BUILD_TYPE),"debug")
	sed -i 's/console owner/console none/' $(TARGET_DIR)/etc/init/${DEV_TTY}.conf
endif
endif

upstart: pkgconfig libnih host-libnih json-c udev $(STAGING_DIR)/$(UPSTART_TARGET_BINARY)

upstart-clean:
	-$(MAKE) DESTDIR=$(STAGING_DIR) -C $(UPSTART_DIR) uninstall
	-$(MAKE) DESTDIR=$(TARGET_DIR) -C $(UPSTART_DIR) uninstall
	-$(MAKE) -C $(UPSTART_DIR) clean

upstart-dirclean:
	rm -rf $(UPSTART_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_UPSTART),y)
TARGETS+=upstart
endif
