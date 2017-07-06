#############################################################
#
# rhad
#
#############################################################
RHAD_VERSION = 0.8.0
RHAD_DIR:=$(BUILD_DIR)/rhad-$(RHAD_VERSION)
RHAD_SOURCE = rhad-$(RHAD_VERSION).tar.bz2
RHAD_CAT:=$(BZCAT)
RHAD_INSTALL_STAGING = YES
RHAD_INSTALL_TARGET = YES
GLIB_INC=$(STAGING_DIR)/usr/include/glib-2.0/
GLIB_INC+=
ifeq ($(BR2_SKY_BUILD_TYPE), "prod")
BUILD_FLAG="-DPROD_BUILD"
else
BUILD_FLAG=-DDEBUG_BUILD
ENABLE_SYSLOG=-DENABLE_SYSLOG
endif 
$(DL_DIR)/$(RHAD_SOURCE):
	 $(WGET) -P $(DL_DIR) $(RHAD_SITE)/$(RHAD_SOURCE)

rhad-source: $(DL_DIR)/$(RHAD_SOURCE)

$(RHAD_DIR)/.unpacked: $(DL_DIR)/$(RHAD_SOURCE)
	-mkdir $(RHAD_DIR)
	$(RHAD_CAT) $(DL_DIR)/$(RHAD_SOURCE) | tar -C $(RHAD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(RHAD_DIR) package/sky-common/rhad/ rhad-$(RHAD_VERSION)\*.patch*
	toolchain/patch-kernel.sh $(RHAD_DIR) package/sky-common/rhad/ rhad-hardening-dbus-conf.patch
	touch $(RHAD_DIR)/.unpacked

$(RHAD_DIR)/.configured: $(RHAD_DIR)/.unpacked $(RHAD_EXTRA_DEPS)
		touch $@

$(RHAD_DIR)/.compiled: $(RHAD_DIR)/.configured
	$(MAKE) -C $(RHAD_DIR)/src $(TARGET_CONFIGURE_OPTS) $(TARGET_CONFIGURE_ARGS) \
		DBUS_INSTALL_DIR="$(DBUS_DIR)" SYS_INCLUDE_DIR="$(STAGING_DIR)" $(RHAD_CFLAGS) \
		GLIB_INC_FLAGS=-I"$(STAGING_DIR)/usr/include/glib-2.0/" \
		GLIB_INC_FLAGS+=-I"$(STAGING_DIR)/usr/lib/glib-2.0/include"\
		DBUS_INC_FLAGS=-I"$(STAGING_DIR)/DBUS/include/dbus-1.0/"\
		LDFLAGS=-L"$(STAGING_DIR)/usr/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/NDS/lib/"\
		BUILD_DIR=$(RHAD_DIR)\
		BUILD_TYPE=$(BUILD_FLAG)
	
	$(MAKE) -C $(RHAD_DIR)/src/tools $(TARGET_CONFIGURE_OPTS) $(TARGET_CONFIGURE_ARGS) \
		DBUS_INSTALL_DIR="$(DBUS_DIR)" SYS_INCLUDE_DIR="$(STAGING_DIR)" $(RHAD_CFLAGS) \
		GLIB_INC_FLAGS=-I"$(STAGING_DIR)/usr/include/glib-2.0/" \
		GLIB_INC_FLAGS+=-I"$(STAGING_DIR)/usr/lib/glib-2.0/include"\
		DBUS_INC_FLAGS=-I"$(STAGING_DIR)/DBUS/include/dbus-1.0/"\
		LDFLAGS=-L"$(STAGING_DIR)/usr/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/NDS/lib/"\
		LDFLAGS+=-I"$(STAGING_DIR)/NDS/include"\
		BUILD_DIR=$(RHAD_DIR)\
		BUILD_TYPE=$(BUILD_FLAG)\
		ENABLE_SYSLOG=$(ENABLE_SYSLOG)
	touch $@

$(RHAD_DIR)/.installed: $(RHAD_DIR)/.compiled
	$(MAKE) -C $(RHAD_DIR)/src DESTDIR=$(TARGET_DIR) BUILD_DIR=$(RHAD_DIR) DBUS_SYS_DIR=$(TARGET_DIR)/DBUS/etc/dbus-1/system.d install
	$(INSTALL) $(RHAD_DIR)/src/rhad $(TARGET_DIR)/usr/bin
ifneq ($(BR2_BOARD_NAME), "humax-amidala418")
	$(MAKE) -C $(RHAD_DIR)/src/tools/ DESTDIR=$(TARGET_DIR) BUILD_DIR=$(RHAD_DIR) install
	$(INSTALL) $(RHAD_DIR)/src/tools/enable_3_button_wakeup $(TARGET_DIR)/usr/bin
	$(INSTALL) -m 440 package/sky-common/rhad/pskey_qualcomm_patch.psr $(TARGET_DIR)/etc
endif
#ifneq ($(BR2_BOARD_NAME), "bskyb-97445")
#	$(INSTALL) -m 0755 package/sky/rhad/S40RCU $(TARGET_DIR)/etc/init.d/
#endif
	touch $@

rhad: pkgconfig $(RHAD_DIR)/.installed
rhad-clean:
	$(MAKE) -C $(RHAD_DIR)/src DESTDIR=$(TARGET_DIR) BUILD_DIR=$(RHAD_DIR) DBUS_SYS_DIR=$(TARGET_DIR)/DBUS/etc/dbus-1/system.d clean
	$(MAKE) -C $(RHAD_DIR)/src/tools DESTDIR=$(TARGET_DIR) BUILD_DIR=$(RHAD_DIR) clean
	rm -rf $(RHAD_DIR)/.installed
	rm -rf $(RHAD_DIR)/.compiled

rhad-dirclean:
	rm -rf $(RHAD_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_RHAD),y)
TARGETS+=rhad
endif
