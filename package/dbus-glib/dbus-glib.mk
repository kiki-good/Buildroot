#############################################################
#
# dbus-glib
#
#############################################################
DBUS_GLIB_VERSION:=0.100.2
DBUS_GLIB_SOURCE:=dbus-glib-$(DBUS_GLIB_VERSION).tar.gz
DBUS_GLIB_SITE:=http://dbus.freedesktop.org/releases/dbus-glib/
DBUS_GLIB_DIR:=$(BUILD_DIR)/dbus-glib-$(DBUS_GLIB_VERSION)
DBUS_GLIB_CAT:=$(ZCAT)
DBUS_GLIB_BINARY:=dbus/.libs/dbus-binding-tool
DBUS_GLIB_TARGET_BINARY:=usr/bin/dbus-binding-tool
DBUS_GLIB_BINARY_SOURCE:=dbus-glib-$(DBUS_GLIB_VERSION)-binary.tar.bz2
DBUS_GLIB_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
DBUS_GLIB_BINARY_DIR:=$(DBUS_GLIB_BOARD_PATH)/binaries
DBUS_GLIB_BINARY_TEMP_DIR:=$(DBUS_GLIB_BINARY_DIR)/dbus-glib_temp
DBUS_GLIB_INSTALL_BINARY:=$(DBUS_GLIB_BINARY_DIR)/$(DBUS_GLIB_BINARY_SOURCE)

$(DL_DIR)/$(DBUS_GLIB_SOURCE):
	$(WGET) -P $(DL_DIR) $(DBUS_GLIB_SITE)/$(DBUS_GLIB_SOURCE)

dbus-glib-source: $(DL_DIR)/$(DBUS_GLIB_SOURCE)

$(DBUS_GLIB_DIR)/.unpacked: $(DL_DIR)/$(DBUS_GLIB_SOURCE)
	$(DBUS_GLIB_CAT) $(DL_DIR)/$(DBUS_GLIB_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(DBUS_GLIB_DIR) package/dbus-glib/ dbus-glib-$(DBUS_GLIB_VERSION)\*.patch
	touch $(DBUS_GLIB_DIR)/.unpacked

$(DBUS_GLIB_DIR)/.configured: $(DBUS_GLIB_DIR)/.unpacked
	(cd $(DBUS_GLIB_DIR); rm -rf config.cache; autoconf; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		ac_cv_have_abstract_sockets=yes \
		ac_cv_func_posix_getpwnam_r=yes \
		LDFLAGS=-L$(STAGING_DIR)/usr/lib/ \
		DBUS_CFLAGS="-I$(STAGING_DIR)/usr/include/dbus-1.0 -I$(STAGING_DIR)/usr/lib/dbus-1.0/include" \
		DBUS_LIBS="$(STAGING_DIR)/usr/lib/libdbus-1.so" \
		DBUS_GLIB_CFLAGS="-I$(STAGING_DIR)/usr/include/glib-2.0 -I$(STAGING_DIR)/usr/lib/glib-2.0/include" \
		DBUS_GLIB_LIBS="$(STAGING_DIR)/usr/lib/libglib-2.0.so $(STAGING_DIR)/usr/lib/libgobject-2.0.so $(STAGING_DIR)/usr/lib/libgmodule-2.0.so $(STAGING_DIR)/usr/lib/libgthread-2.0.so $(STAGING_DIR)/usr/lib/libgio-2.0.so" \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--prefix=/usr \
		--localstatedir=/var \
		--program-prefix="" \
		--disable-tests \
		--disable-xml-docs \
		--disable-doxygen-docs \
		--enable-asserts=yes \
		--without-examples \
		PKG_CONFIG= $(STAGING_DIR)/usr/bin/pkg-config \
		PKG_CONFIG_PATH= $(STAGING_DIR)/usr/lib/pkgconfig/ \
	)
	touch $(DBUS_GLIB_DIR)/.configured

$(DBUS_GLIB_DIR)/$(DBUS_GLIB_BINARY): $(DBUS_GLIB_DIR)/.configured
	$(MAKE) DBUS_BUS_LIBS="$(STAGING_DIR)/lib/libexpat.so" -C $(DBUS_GLIB_DIR) all
	$(MAKE) DESTDIR=$(STAGING_DIR) -C $(DBUS_GLIB_DIR) install
	cp $(DBUS_GLIB_DIR)/dbus-glib-1.pc $(STAGING_DIR)/usr/lib/pkgconfig
	$(MAKE) DESTDIR=$(PWD)/$(DBUS_GLIB_BINARY_TEMP_DIR) -C $(DBUS_GLIB_DIR) install
	tar cjvf $(DBUS_GLIB_BINARY_DIR)/$(DBUS_GLIB_BINARY_SOURCE) -C $(DBUS_GLIB_BINARY_TEMP_DIR) .
	rm -rf $(DBUS_GLIB_BINARY_TEMP_DIR)

$(TARGET_DIR)/$(DBUS_GLIB_TARGET_BINARY): $(DBUS_GLIB_DIR)/$(DBUS_GLIB_BINARY)
	cp -a $(STAGING_DIR)/usr/lib/libdbus-glib-1.so.2* $(TARGET_DIR)/usr/lib
ifeq ($(BR2_SKY_BUILD_TYPE),"debug")
	cp -a $(STAGING_DIR)/usr/bin/dbus-binding-tool $(TARGET_DIR)/usr/bin
endif
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libdbus-glib-1.so.2*
	touch $@

dbus-glib-binary:
	tar -xjvf $(DBUS_GLIB_BINARY_DIR)/$(DBUS_GLIB_BINARY_SOURCE) -C $(STAGING_DIR)/
	cp -a $(STAGING_DIR)/usr/lib/libdbus-glib-1.so.2* $(TARGET_DIR)/usr/lib
ifeq ($(BR2_SKY_BUILD_TYPE),"debug")
	cp -a $(STAGING_DIR)/usr/bin/dbus-binding-tool $(TARGET_DIR)/usr/bin
endif
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libdbus-glib-1.so.2*


ifeq ($(wildcard $(DBUS_GLIB_INSTALL_BINARY)),)
dbus-glib: uclibc pkgconfig dbus libglib2 $(TARGET_DIR)/$(DBUS_GLIB_TARGET_BINARY)
else
dbus-glib: dbus-glib-binary
endif

dbus-glib-clean:
	rm -f $(TARGET_DIR)/usr/lib/libdbus-glib-1.so.2*
	rm -f $(TARGET_DIR)/usr/bin/dbus-binding-tool
	rm -f $(STAGING_DIR)/usr/lib/libdbus-glib-1.so*
	-$(MAKE) -C $(DBUS_GLIB_DIR) clean

dbus-glib-dirclean:
	rm -rf $(DBUS_GLIB_DIR)

dbus-glib-binary-clean:
	rm $(DBUS_GLIB_INSTALL_BINARY)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_DBUS_GLIB),y)
TARGETS+=dbus-glib
endif
