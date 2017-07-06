#############################################################
#
# maid
#
#############################################################
MAID_VERSION = 0.3.23
MESH_VERSION = 2017w21
MAID_DIR:=$(BUILD_DIR)/maid-$(MAID_VERSION)
MAID_SOURCE = $(SKY_DL_DIR)/maid-$(MAID_VERSION).tar.bz2
MAID_SUPPORT_TARBALL = $(SKY_DL_DIR)/maid-support-$(BOARD_NAME)-$(BR2_SKY_BUILD_TYPE)-$(MESH_VERSION).tar.bz2
MAID_BINARY_SOURCE:=maid-$(MAID_VERSION)-binary.tar.bz2
MAID_CAT:=$(BZCAT)
MAID_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
MAID_BINARY_DIR=$(PWD)/$(MAID_BOARD_PATH)/binaries
MAID_INSTALL_BINARY=$(MAID_BINARY_DIR)/$(MAID_BINARY_SOURCE)
MAID_INSTALL_STAGING = YES
MAID_INSTALL_TARGET = YES
GLIB_INC=$(STAGING_DIR)/usr/include/glib-2.0/
GLIB_INC+= 
$(DL_DIR)/$(MAID_SOURCE):
	 $(WGET) -P $(DL_DIR) $(MAID_SITE)/$(MAID_SOURCE)

PLC_ON_GW_ONLY=n
ifeq ($(BOARD_NAME),bskyb-falcon-d1)
BSKYB_FALCON_PLATFORM=y
PLC_ON_GW_ONLY=y
else ifeq ($(BOARD_NAME),bskyb-falcon-d1-uhd)
BSKYB_FALCON_PLATFORM=y
PLC_ON_GW_ONLY=y
else ifeq ($(BR2_TOOLCHAIN_EXTERNAL_PREFIX),"armv7-linux")
BSKYB_FALCON_PLATFORM=n
else
#error "Platform not supported"
endif

ifeq ($(BR2_TARGET_SKY_BSKYB_XWING_412),y)
PLC_ON_GW_ONLY=y
endif

ifeq ($(BR2_TARGET_SKY_BSKYB_XWING_HIP),y)
PLC_ON_GW_ONLY=y
endif

ifeq ($(BR2_TARGET_SKY_BSKYB_GEMINI_419),y)
PLC_ON_GW_ONLY=y
endif

maid-source: $(DL_DIR)/$(MAID_SOURCE)

$(MAID_DIR)/.unpacked: $(DL_DIR)/$(MAID_SOURCE)
	-mkdir $(MAID_DIR)
	$(MAID_CAT) $(DL_DIR)/$(MAID_SOURCE) | tar -C $(MAID_DIR) $(TAR_OPTIONS) -
	$(MAID_CAT) $(DL_DIR)/$(MAID_SUPPORT_TARBALL) | tar -C $(MAID_DIR) $(TAR_OPTIONS) -
	mv $(MAID_DIR)/lib/libaci.so $(STAGING_DIR)/lib/
	toolchain/patch-kernel.sh $(MAID_DIR) package/sky/maid/ maid-$(MAID_VERSION)\*.patch*
	toolchain/patch-kernel.sh $(MAID_DIR) package/sky/maid/ maid-hardening-dbus-conf.patch
	touch $(MAID_DIR)/.unpacked

$(MAID_DIR)/.configured: $(MAID_DIR)/.unpacked $(MAID_EXTRA_DEPS)
		touch $@

$(MAID_DIR)/.compiled: $(MAID_DIR)/.configured
	$(MAKE) -C $(MAID_DIR)/src $(TARGET_CONFIGURE_OPTS) $(TARGET_CONFIGURE_ARGS) \
		DBUS_INSTALL_DIR="$(DBUS_DIR)" SYS_INCLUDE_DIR="$(STAGING_DIR)" $(MAID_CFLAGS) \
		GLIB_INC_FLAGS=-I"$(STAGING_DIR)/usr/include/glib-2.0/" \
		GLIB_INC_FLAGS+=-I"$(STAGING_DIR)/usr/lib/glib-2.0/include"\
		DBUS_INC_FLAGS=-I"$(STAGING_DIR)/DBUS/include/dbus-1.0/"\
		LDFLAGS=-L"$(STAGING_DIR)/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/usr/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/NDS/lib/"\
		BUILD_DIR=$(MAID_DIR)\
		PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"\
		PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)"
		

	$(MAKE) -C $(MAID_DIR)/lib $(TARGET_CONFIGURE_OPTS) $(TARGET_CONFIGURE_ARGS) \
		DBUS_INSTALL_DIR="$(DBUS_DIR)" SYS_INCLUDE_DIR="$(STAGING_DIR)" $(MAID_CFLAGS) \
		GLIB_INC_FLAGS=-I"$(STAGING_DIR)/usr/include/glib-2.0/" \
		GLIB_INC_FLAGS+=-I"$(STAGING_DIR)/usr/lib/glib-2.0/include"\
		DBUS_INC_FLAGS=-I"$(STAGING_DIR)/DBUS/include/dbus-1.0/"\
		LDFLAGS=-L"$(STAGING_DIR)/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/usr/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/NDS/lib/"\
		BUILD_DIR=$(MAID_DIR) \
		PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"\
		PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)"
	
	$(MAKE) -C $(MAID_DIR)/ngi_helper/src $(TARGET_CONFIGURE_OPTS) $(TARGET_CONFIGURE_ARGS) \
		LDFLAGS=-L"$(MAID_DIR)/lib/build/"\
		LDFLAGS+=-L"$(STAGING_DIR)/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/usr/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/NDS/lib/"\
		BUILD_DIR=$(MAID_DIR)/ngi_helper/src \
		MAID_INC_DIR=$(MAID_DIR)/inc \
		PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"\
		PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)"
	touch $@

$(MAID_DIR)/.installed: $(MAID_DIR)/.compiled
	mkdir -p $(MAID_BINARY_DIR)/maid_tmp
	$(MAKE) -C $(MAID_DIR)/src DESTDIR=$(TARGET_DIR) BUILD_DIR=$(MAID_DIR) DBUS_SYS_DIR=$(TARGET_DIR)/DBUS/etc/dbus-1/system.d install PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)" PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"
	$(MAKE) -C $(MAID_DIR)/lib DESTDIR=$(TARGET_DIR) BUILD_DIR=$(MAID_DIR) DBUS_SYS_DIR=$(TARGET_DIR)/DBUS/etc/dbus-1/system.d install PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)" PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"
	$(MAKE) -C $(MAID_DIR)/ngi_helper/src DESTDIR=$(TARGET_DIR) BUILD_DIR=$(MAID_DIR)/ngi_helper/src/ MAID_INC_DIR=$(MAID_DIR)/inc install PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)" PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"
	$(INSTALL) $(MAID_DIR)/src/maid $(TARGET_DIR)/usr/bin
	$(INSTALL) $(STAGING_DIR)/lib/libaci.so $(TARGET_DIR)/lib
	-mkdir -p $(STAGING_DIR)/usr/include
	$(INSTALL) $(MAID_DIR)/inc/lanss.h $(STAGING_DIR)/usr/include
	-mkdir -p $(MAID_BINARY_DIR)/maid_tmp/lib
	-mkdir -p $(MAID_BINARY_DIR)/maid_tmp/usr/bin
	-mkdir -p $(MAID_BINARY_DIR)/maid_tmp/DBUS/etc/dbus-1/system.d/
	$(MAKE) -C $(MAID_DIR)/src DESTDIR=$(MAID_BINARY_DIR)/maid_tmp BUILD_DIR=$(MAID_DIR) DBUS_SYS_DIR=$(MAID_BINARY_DIR)/maid_tmp/DBUS/etc/dbus-1/system.d/ install PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)" PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"
	$(MAKE) -C $(MAID_DIR)/lib DESTDIR=$(MAID_BINARY_DIR)/maid_tmp BUILD_DIR=$(MAID_DIR) DBUS_SYS_DIR=$(MAID_BINARY_DIR)/maid_tmp/DBUS/etc/dbus-1/system.d/ install PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)" PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"
	$(MAKE) -C $(MAID_DIR)/ngi_helper/src DESTDIR=$(MAID_BINARY_DIR)/maid_tmp BUILD_DIR=$(MAID_DIR)/ngi_helper/src/ MAID_INC_DIR=$(MAID_DIR)/inc install PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)" PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"
	$(INSTALL) $(MAID_DIR)/src/maid $(MAID_BINARY_DIR)/maid_tmp/usr/bin
	-mkdir -p $(MAID_BINARY_DIR)/maid_tmp/usr/include
	-mkdir -p $(MAID_BINARY_DIR)/maid_tmp/lib
	$(INSTALL) $(MAID_DIR)/inc/lanss.h $(MAID_BINARY_DIR)/maid_tmp/usr/include
	$(INSTALL) $(STAGING_DIR)/lib/libaci.so $(MAID_BINARY_DIR)/maid_tmp/lib
ifneq ($(BR2_BOARD_NAME), "bskyb-97445")
	$(INSTALL) -m 0755 package/sky/maid/S50Maid $(TARGET_DIR)/etc/init.d/
	-mkdir -p $(MAID_BINARY_DIR)/maid_tmp/etc/init.d/
	$(INSTALL) -m 0755 package/sky/maid/S50Maid $(MAID_BINARY_DIR)/maid_tmp/etc/init.d/
endif
	tar -cjvf $(MAID_BINARY_DIR)/$(MAID_BINARY_SOURCE) -C $(MAID_BINARY_DIR)/maid_tmp .
	rm -rf $(MAID_BINARY_DIR)/maid_tmp
	touch $@

maid-binary:
	tar -xjvf $(MAID_BINARY_DIR)/$(MAID_BINARY_SOURCE) -C $(TARGET_DIR)/
	-mkdir -p $(STAGING_DIR)/usr/include
	cp $(TARGET_DIR)/usr/include/lanss.h $(STAGING_DIR)/usr/include/

ifeq ("$(wildcard $(MAID_INSTALL_BINARY))","")
maid: pkgconfig libglib2 dbus $(MAID_DIR)/.installed
else
maid: maid-binary
endif
	
maid-clean:
	cd $(MAID_DIR)/src;$(MAKE) DESTDIR=$(TARGET_DIR) clean
	cd $(MAID_DIR)/lib;$(MAKE) DESTDIR=$(TARGET_DIR) clean
	cd $(MAID_DIR)/ngi_helper/src;$(MAKE) DESTDIR=$(TARGET_DIR) BUILD_DIR=$(MAID_DIR)/ngi_helper/src MAID_INC_DIR=$(MAID_DIR)/inc clean
	rm -rf $(MAID_DIR)/.installed
	rm -rf $(MAID_DIR)/.compiled

maid-dirclean:
	rm -rf $(MAID_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_MAID),y)
TARGETS+=maid
endif
