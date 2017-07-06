#############################################################
#
# UAPI Daemon
#
#############################################################
UAPI_VERSION:=1.0
UAPI_SOURCE:=UAPIDaemon-$(UAPI_VERSION).tar.bz2
UAPI_SITE:=sftp://bskyb@ueiftp.ueic.com/users/BSKYB/UAPIDaemon_To_Sky
UAPI_CAT:=$(BZCAT)
UAPI_DIR:=$(BUILD_DIR)/UAPIDaemon-$(UAPI_VERSION)
UAPI_BINARY:=/usr/bin/uapid

$(DL_DIR)/$(UAPI_SOURCE):
	 $(WGET) -P $(DL_DIR) $(UAPI_SITE)/$(UAPI_SOURCE)

uapi-source: $(DL_DIR)/$(UAPI_SOURCE)

$(UAPI_DIR)/.unpacked: $(DL_DIR)/$(UAPI_SOURCE)
	$(UAPI_CAT) $(DL_DIR)/$(UAPI_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(UAPI_DIR) package/UAPIDaemon/ uapidaemon-$(UAPI_VERSION)\*.patch*
	touch $(UAPI_DIR)/.unpacked

$(UAPI_DIR)/.configured: $(UAPI_DIR)/.unpacked
	(cd $(UAPI_DIR); rm -rf config.cache; \
	cp $(UAPI_DIR)/client/libqs.so $(STAGING_DIR)/usr/lib/ )
	touch $(UAPI_DIR)/.configured

$(STAGING_DIR)/usr/bin/uapid: $(UAPI_DIR)/.configured
	$(MAKE) -C $(UAPI_DIR)/daemon $(TARGET_CONFIGURE_OPTS) 	$(TARGET_CONFIGURE_ARGS) DBUS_INSTALL_DIR="$(DBUS_DIR)" SYS_INCLUDE_DIR="$(STAGING_DIR)" 
	$(MAKE) -C $(UAPI_DIR)/client $(TARGET_CONFIGURE_OPTS) 	$(TARGET_CONFIGURE_ARGS) DBUS_INSTALL_DIR="$(DBUS_DIR)" SYS_INCLUDE_DIR="$(STAGING_DIR)" 

$(TARGET_DIR)/$(UAPI_BINARY): $(STAGING_DIR)/usr/bin/uapid
	cp $(UAPI_DIR)/daemon/uapid $(TARGET_DIR)/usr/bin/
	cp $(UAPI_DIR)/client/uapi_client $(TARGET_DIR)/usr/bin/
	cp $(UAPI_DIR)/client/uapi.conf $(TARGET_DIR)/etc/dbus-1/system.d/
	cp $(STAGING_DIR)/usr/lib/libqs.so $(TARGET_DIR)/usr/lib/libqs.so
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libqs.so
	$(INSTALL) -m 0755 package/UAPIDaemon/S50UAPI $(TARGET_DIR)/etc/init.d/

uapi:	uclibc pkgconfig bluez $(TARGET_DIR)/$(UAPI_BINARY)

uapi-clean:
	$(MAKE) -C $(UAPI_DIR)/daemon clean
	$(MAKE) -C $(UAPI_DIR)/client clean
	rm -rf $(TARGET_DIR)/usr/bin/uapid
	rm -rf $(TARGET_DIR)/usr/bin/uapi_client
	rm -rf $(TARGET_DIR)/usr/lib/libqs.so
	rm -rf $(TARGET_DIR)/usr/dbus-1/system.d/uapi.conf

uapi-dirclean:
	rm -rf $(UAPI_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_UAPI),y)
TARGETS+=uapi
UAPI_DEPENDS+=bluez
endif
