#############################################################
#
# maid
#
#############################################################
MAID_AMIDALA_VERSION = 0.0.2
MAID_AMIDALA_DIR:=$(BUILD_DIR)/maid-amidala-$(MAID_AMIDALA_VERSION)
MAID_AMIDALA_SOURCE = maid-amidala-$(MAID_AMIDALA_VERSION).tar.bz2
MAID_AMIDALA_BINARY_SOURCE:=maid-$(MAID_AMIDALA_VERSION)-binary.tar.bz2
MAID_AMIDALA_CAT:=$(BZCAT)
MAID_AMIDALA_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
MAID_AMIDALA_BINARY_DIR=$(PWD)/$(MAID_AMIDALA_BOARD_PATH)/binaries
MAID_AMIDALA_INSTALL_BINARY=$(MAID_AMIDALA_BINARY_DIR)/$(MAID_AMIDALA_BINARY_SOURCE)
MAID_AMIDALA_INSTALL_STAGING = YES
MAID_AMIDALA_INSTALL_TARGET = YES
GLIB_INC=$(STAGING_DIR)/usr/include/glib-2.0/
WPA_SUPP_HARDENING=0

maid-source: $(DL_DIR)/$(MAID_AMIDALA_SOURCE)

$(MAID_AMIDALA_DIR)/.unpacked: $(DL_DIR)/$(MAID_AMIDALA_SOURCE)
	-mkdir $(MAID_AMIDALA_DIR)
	$(MAID_AMIDALA_CAT) $(DL_DIR)/$(MAID_AMIDALA_SOURCE) | tar -C $(MAID_AMIDALA_DIR) $(TAR_OPTIONS) -
	touch $(MAID_AMIDALA_DIR)/.unpacked

$(MAID_AMIDALA_DIR)/.configured: $(MAID_AMIDALA_DIR)/.unpacked $(MAID_AMIDALA_EXTRA_DEPS)
		touch $@

$(MAID_AMIDALA_DIR)/.compiled: $(MAID_AMIDALA_DIR)/.configured

	$(MAKE) -C $(MAID_AMIDALA_DIR)/wifi_helper/src $(TARGET_CONFIGURE_OPTS) $(TARGET_CONFIGURE_ARGS) \
		LDFLAGS=-L"$(MAID_AMIDALA_DIR)/lib/build/"\
		LDFLAGS+=-L"$(STAGING_DIR)/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/usr/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/NDS/lib/"\
		BUILD_DIR=$(MAID_AMIDALA_DIR)/wifi_helper/src \
		WIFI_HELPER_INC_DIR=$(MAID_AMIDALA_DIR)/wifi_helper/inc \
		WIFI_HELPER_INC_DIR+=$(MAID_AMIDALA_DIR)/wifi_helper/inc/nds \
		WPA_SUPP_HARDENING="$(WPA_SUPP_HARDENING)"

	$(MAKE) -C $(MAID_AMIDALA_DIR)/wifi_helper/test/ $(TARGET_CONFIGURE_OPTS) $(TARGET_CONFIGURE_ARGS) \
		LDFLAGS=-L"$(MAID_AMIDALA_DIR)/lib/build/"\
		LDFLAGS+=-L"$(STAGING_DIR)/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/usr/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/NDS/lib/"\
		LDFLAGS+=-L"$(MAID_AMIDALA_DIR)/wifi_helper/src/"\
		BUILD_DIR=$(MAID_AMIDALA_DIR)/wifi_helper/test \
		WIFI_HELPER_INC_DIR=$(MAID_AMIDALA_DIR)/wifi_helper/inc 

	$(MAKE) -C $(MAID_AMIDALA_DIR)/src $(TARGET_CONFIGURE_OPTS) $(TARGET_CONFIGURE_ARGS) \
		DBUS_INSTALL_DIR="$(DBUS_DIR)" SYS_INCLUDE_DIR="$(STAGING_DIR)" $(MAID_AMIDALA_CFLAGS) \
		GLIB_INC_FLAGS=-I"$(STAGING_DIR)/usr/include/glib-2.0/" \
		GLIB_INC_FLAGS+=-I"$(STAGING_DIR)/usr/lib/glib-2.0/include"\
		DBUS_INC_FLAGS=-I"$(STAGING_DIR)/DBUS/include/dbus-1.0/"\
		LDFLAGS=-L"$(STAGING_DIR)/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/usr/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/NDS/lib/"\
		LDFLAGS+=-L"$(MAID_AMIDALA_DIR)/wifi_helper/src/"\
		BUILD_DIR=$(MAID_AMIDALA_DIR)\
		PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"\
		PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)"
		

	$(MAKE) -C $(MAID_AMIDALA_DIR)/lib $(TARGET_CONFIGURE_OPTS) $(TARGET_CONFIGURE_ARGS) \
		DBUS_INSTALL_DIR="$(DBUS_DIR)" SYS_INCLUDE_DIR="$(STAGING_DIR)" $(MAID_AMIDALA_CFLAGS) \
		GLIB_INC_FLAGS=-I"$(STAGING_DIR)/usr/include/glib-2.0/" \
		GLIB_INC_FLAGS+=-I"$(STAGING_DIR)/usr/lib/glib-2.0/include"\
		DBUS_INC_FLAGS=-I"$(STAGING_DIR)/DBUS/include/dbus-1.0/"\
		LDFLAGS=-L"$(STAGING_DIR)/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/usr/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/NDS/lib/"\
		BUILD_DIR=$(MAID_AMIDALA_DIR) \
		PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"\
		PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)"
	
	$(MAKE) -C $(MAID_AMIDALA_DIR)/ngi_helper/src $(TARGET_CONFIGURE_OPTS) $(TARGET_CONFIGURE_ARGS) \
		LDFLAGS=-L"$(MAID_AMIDALA_DIR)/lib/build/"\
		LDFLAGS+=-L"$(STAGING_DIR)/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/usr/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/NDS/lib/"\
		BUILD_DIR=$(MAID_AMIDALA_DIR)/ngi_helper/src \
		MAID_INC_DIR=$(MAID_AMIDALA_DIR)/inc \
		PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"\
		PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)"

	$(MAKE) -C $(MAID_AMIDALA_DIR)/ngi_helper/test/ $(TARGET_CONFIGURE_OPTS) $(TARGET_CONFIGURE_ARGS) \
		LDFLAGS=-L"$(MAID_AMIDALA_DIR)/lib/build/"\
		LDFLAGS+=-L"$(STAGING_DIR)/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/usr/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/NDS/lib/"\
		LDFLAGS+=-L"$(MAID_AMIDALA_DIR)/ngi_helper/src/ngi/build/"\
		BUILD_DIR=$(MAID_AMIDALA_DIR)/ngi_helper/test \
		MAID_INC_DIR=$(MAID_AMIDALA_DIR)/inc \
		PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"\
		PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)"

	$(MAKE) -C $(MAID_AMIDALA_DIR)/lib/test/ $(TARGET_CONFIGURE_OPTS) $(TARGET_CONFIGURE_ARGS) \
		LDFLAGS=-L"$(MAID_AMIDALA_DIR)/lib/build/"\
		LDFLAGS+=-L"$(STAGING_DIR)/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/usr/lib/"\
		LDFLAGS+=-L"$(STAGING_DIR)/NDS/lib/"\
		LDFLAGS+=-L"$(MAID_AMIDALA_DIR)/ngi_helper/src/ngi/build/"\
		BUILD_DIR=$(MAID_AMIDALA_DIR)/lib/test \
		MAID_INC_DIR=$(MAID_AMIDALA_DIR)/inc \
		PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"\
		PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)"

	touch $@

$(MAID_AMIDALA_DIR)/.installed: $(MAID_AMIDALA_DIR)/.compiled
	mkdir -p $(MAID_AMIDALA_BINARY_DIR)/maid_tmp
	$(MAKE) -C $(MAID_AMIDALA_DIR)/src DESTDIR=$(TARGET_DIR) BUILD_DIR=$(MAID_AMIDALA_DIR) DBUS_SYS_DIR=$(TARGET_DIR)/DBUS/etc/dbus-1/system.d install PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)" PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"
	$(MAKE) -C $(MAID_AMIDALA_DIR)/lib DESTDIR=$(TARGET_DIR) BUILD_DIR=$(MAID_AMIDALA_DIR) DBUS_SYS_DIR=$(TARGET_DIR)/DBUS/etc/dbus-1/system.d install PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)" PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"
	$(MAKE) -C $(MAID_AMIDALA_DIR)/ngi_helper/src DESTDIR=$(TARGET_DIR) BUILD_DIR=$(MAID_AMIDALA_DIR)/ngi_helper/src/ MAID_AMIDALA_INC_DIR=$(MAID_AMIDALA_DIR)/inc install PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)" PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"
	$(MAKE) -C $(MAID_AMIDALA_DIR)/ngi_helper/test DESTDIR=$(TARGET_DIR) BUILD_DIR=$(MAID_AMIDALA_DIR)/ngi_helper/test/ MAID_AMIDALA_INC_DIR=$(MAID_AMIDALA_DIR)/inc install PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)" PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"
	$(MAKE) -C $(MAID_AMIDALA_DIR)/wifi_helper/src DESTDIR=$(TARGET_DIR) BUILD_DIR=$(MAID_AMIDALA_DIR)/wifi_helper/src/ WIFI_HELPER_INC_DIR=$(MAID_AMIDALA_DIR)/wifi_helper/inc WIFI_HELPER_INC_DIR+=$(MAID_AMIDALA_DIR)/wifi_helper/inc/nds install
	$(MAKE) -C $(MAID_AMIDALA_DIR)/wifi_helper/test DESTDIR=$(TARGET_DIR) BUILD_DIR=$(MAID_AMIDALA_DIR)/wifi_helper/test WIFI_HELPER_INC_DIR=$(MAID_AMIDALA_DIR)/wifi_helper/inc install
	$(INSTALL) $(MAID_AMIDALA_DIR)/src/maid $(TARGET_DIR)/usr/bin
ifeq ($(BR2_TARGET_HUMAX_AMIDALA_418),n)
	$(INSTALL) $(STAGING_DIR)/lib/libaci.so $(TARGET_DIR)/lib
endif
	-mkdir -p $(STAGING_DIR)/usr/include
	$(INSTALL) $(MAID_AMIDALA_DIR)/inc/lanss.h $(STAGING_DIR)/usr/include
	-mkdir -p $(MAID_AMIDALA_BINARY_DIR)/maid_tmp/lib
	-mkdir -p $(MAID_AMIDALA_BINARY_DIR)/maid_tmp/usr/bin
	-mkdir -p $(MAID_AMIDALA_BINARY_DIR)/maid_tmp/DBUS/etc/dbus-1/system.d/
	$(MAKE) -C $(MAID_AMIDALA_DIR)/src DESTDIR=$(MAID_AMIDALA_BINARY_DIR)/maid_tmp BUILD_DIR=$(MAID_AMIDALA_DIR) DBUS_SYS_DIR=$(MAID_AMIDALA_BINARY_DIR)/maid_tmp/DBUS/etc/dbus-1/system.d/ install PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)" PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"
	$(MAKE) -C $(MAID_AMIDALA_DIR)/lib DESTDIR=$(MAID_AMIDALA_BINARY_DIR)/maid_tmp BUILD_DIR=$(MAID_AMIDALA_DIR) DBUS_SYS_DIR=$(MAID_AMIDALA_BINARY_DIR)/maid_tmp/DBUS/etc/dbus-1/system.d/ install PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)" PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"
	$(MAKE) -C $(MAID_AMIDALA_DIR)/ngi_helper/src DESTDIR=$(MAID_AMIDALA_BINARY_DIR)/maid_tmp BUILD_DIR=$(MAID_AMIDALA_DIR)/ngi_helper/src/ MAID_AMIDALA_INC_DIR=$(MAID_AMIDALA_DIR)/inc install PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)" PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"
	$(MAKE) -C $(MAID_AMIDALA_DIR)/ngi_helper/test DESTDIR=$(MAID_AMIDALA_BINARY_DIR)/maid_tmp BUILD_DIR=$(MAID_AMIDALA_DIR)/ngi_helper/test MAID_AMIDALA_INC_DIR=$(MAID_AMIDALA_DIR)/inc install PLATFORM_CFLAGS="$(BSKYB_FALCON_PLATFORM)" PLC_ON_GW_ONLY="$(PLC_ON_GW_ONLY)"
	$(MAKE) -C $(MAID_AMIDALA_DIR)/wifi_helper/src DESTDIR=$(MAID_AMIDALA_BINARY_DIR)/maid_tmp BUILD_DIR=$(MAID_AMIDALA_DIR)/wifi_helper/src/ WIFI_HELPER_INC_DIR=$(MAID_AMIDALA_DIR)/wifi_helper/inc WIFI_HELPER_INC_DIR+=$(MAID_AMIDALA_DIR)/wifi_helper/inc/nds install
	$(MAKE) -C $(MAID_AMIDALA_DIR)/wifi_helper/test DESTDIR=$(MAID_AMIDALA_BINARY_DIR)/maid_tmp BUILD_DIR=$(MAID_AMIDALA_DIR)/wifi_helper/test WIFI_HELPER_INC_DIR=$(MAID_AMIDALA_DIR)/wifi_helper/inc install
	$(INSTALL) $(MAID_AMIDALA_DIR)/src/maid $(MAID_AMIDALA_BINARY_DIR)/maid_tmp/usr/bin
	-mkdir -p $(MAID_AMIDALA_BINARY_DIR)/maid_tmp/usr/include
	-mkdir -p $(MAID_AMIDALA_BINARY_DIR)/maid_tmp/lib
	$(INSTALL) $(MAID_AMIDALA_DIR)/inc/lanss.h $(MAID_AMIDALA_BINARY_DIR)/maid_tmp/usr/include
ifeq ($(BR2_TARGET_HUMAX_AMIDALA_418),n)
	$(INSTALL) $(STAGING_DIR)/lib/libaci.so $(MAID_AMIDALA_BINARY_DIR)/maid_tmp/lib
endif
	$(INSTALL) -m 0755 package/sky-common/maid-amidala/S50Maid $(TARGET_DIR)/etc/init.d/
	-mkdir -p $(MAID_AMIDALA_BINARY_DIR)/maid_tmp/etc/init.d/
	$(INSTALL) -m 0755 package/sky-common/maid-amidala/S50Maid $(MAID_AMIDALA_BINARY_DIR)/maid_tmp/etc/init.d/
	tar -cjvf $(MAID_AMIDALA_BINARY_DIR)/$(MAID_AMIDALA_BINARY_SOURCE) -C $(MAID_AMIDALA_BINARY_DIR)/maid_tmp .
	rm -rf $(MAID_AMIDALA_BINARY_DIR)/maid_tmp
	touch $@

maid-amidala-binary:
	tar -xjvf $(MAID_AMIDALA_BINARY_DIR)/$(MAID_AMIDALA_BINARY_SOURCE) -C $(TARGET_DIR)/
	-mkdir -p $(STAGING_DIR)/usr/include
	cp $(TARGET_DIR)/usr/include/lanss.h $(STAGING_DIR)/usr/include/

ifeq ("$(wildcard $(MAID_AMIDALA_INSTALL_BINARY))","")
maid-amidala: pkgconfig libglib2 dbus libintl $(MAID_AMIDALA_DIR)/.installed
else
maid-amidala: maid-amidala-binary
endif
	
maid-amidala-clean:
	cd $(MAID_AMIDALA_DIR)/src;$(MAKE) DESTDIR=$(TARGET_DIR) clean
	cd $(MAID_AMIDALA_DIR)/lib;$(MAKE) DESTDIR=$(TARGET_DIR) clean
	cd $(MAID_AMIDALA_DIR)/ngi_helper/src;$(MAKE) DESTDIR=$(TARGET_DIR) BUILD_DIR=$(MAID_AMIDALA_DIR)/ngi_helper/src MAID_AMIDALA_INC_DIR=$(MAID_AMIDALA_DIR)/inc clean
	cd $(MAID_AMIDALA_DIR)/wifi_helper/src; $(MAKE) DESTDIR=$(TARGET_DIR) BUILD_DIR=$(MAID_AMIDALA_DIR)/wifi_helper/src WIFI_HELPER_INC_DIR=$(MAID_AMIDALA_DIR)/wifi_helper/inc WIFI_HELPER_INC_DIR+=$(MAID_AMIDALA_DIR)/wifi_helper/inc/nds clean
	cd $(MAID_AMIDALA_DIR)/wifi_helper/test; $(MAKE) DESTDIR=$(TARGET_DIR) BUILD_DIR=$(MAID_AMIDALA_DIR)/wifi_helper/test WIFI_HELPER_INC_DIR=$(MAID_AMIDALA_DIR)/wifi_helper/inc clean
	rm -rf $(MAID_AMIDALA_DIR)/.installed
	rm -rf $(MAID_AMIDALA_DIR)/.compiled

maid-amidala-dirclean:
	rm -rf $(MAID_AMIDALA_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_MAID_AMIDALA),y)
TARGETS+=maid-amidala
endif
