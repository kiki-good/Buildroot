#############################################################
#
# LIBNIH
#
#############################################################
LIBNIH_VERSION:=1.0.3
LIBNIH_SOURCE:=libnih-$(LIBNIH_VERSION).tar.gz
LIBNIH_SITE:=https://launchpad.net/libnih/1.0/$(LIBNIH_VERSION)/+download
LIBNIH_CAT:=$(ZCAT) 
LIBNIH_SRC_DIR:=$(TOOL_BUILD_DIR)/libnih-$(LIBNIH_VERSION)
LIBNIH_DIR:=$(BUILD_DIR)/libnih-$(LIBNIH_VERSION)
LIBNIH_HOST_DIR:=$(TOOL_BUILD_DIR)/libnih-$(LIBNIH_VERSION)-host
LIBNIH_BINARY:=nih-dbus-tool
LIBNIH_TARGET_BINARY:=usr/bin/nih-dbus-tool
LIBNIH:=$(STAGING_DIR)/usr/bin/nih-dbus-tool

LIBNIH_CONF_OPT += NIH_DBUS_TOOL=$(LIBNIH_HOST_DIR)/nih-dbus-tool/nih-dbus-tool \

$(DL_DIR)/$(LIBNIH_SOURCE): 
	$(WGET) -P $(DL_DIR) $(LIBNIH_SITE)/$(LIBNIH_SOURCE)

libnih-source: $(DL_DIR)/$(LIBNIH_SOURCE)

libnih-unpacked: $(LIBNIH_DIR)/.unpacked
$(LIBNIH_SRC_DIR)/.unpacked: $(DL_DIR)/$(LIBNIH_SOURCE)
	$(LIBNIH_CAT) $(DL_DIR)/$(LIBNIH_SOURCE) | tar -C $(TOOL_BUILD_DIR) $(TAR_OPTIONS) -
ifneq ($(BR2_ARCH_IS_64),y)
	toolchain/patch-kernel.sh $(LIBNIH_SRC_DIR) package/libnih/ \*.patch
else
	toolchain/patch-kernel.sh $(LIBNIH_SRC_DIR) package/libnih/64bitPatch libnih-$(LIBNIH_VERSION)\*.patch*
endif
	touch $@
#############################################################
#
# libnih for the target
#
#############################################################
$(LIBNIH_DIR)/.configured: $(LIBNIH_SRC_DIR)/.unpacked
	mkdir -p $(LIBNIH_DIR)
	(cd $(LIBNIH_DIR); rm -rf config.cache; \
                $(TARGET_CONFIGURE_OPTS) \
                $(TARGET_CONFIGURE_ARGS) \
		$(LIBNIH_SRC_DIR)/configure \
		--target=$(GNU_TARGET_NAME) \
                --host=$(GNU_TARGET_NAME) \
                --build=$(GNU_HOST_NAME) \
		DBUS_CFLAGS="-I$(STAGING_DIR)/usr/include/dbus-1.0 -I$(STAGING_DIR)/usr/lib/dbus-1.0/include" \
                DBUS_LIBS="$(STAGING_DIR)/usr/lib/libdbus-1.so" \
		NIH_DBUS_TOOL="$(LIBNIH_HOST_DIR)/nih-dbus-tool/nih-dbus-tool" \
		LDFLAGS="-L$(TARGET_DIR)/usr/lib/" \
		--prefix=/usr \
                --exec-prefix=/usr \
                --sbindir=/usr/sbin \
                --libdir=/lib \
                --libexecdir=/usr/lib \
                --sysconfdir=/etc \
                --datadir=/usr/share \
                --localstatedir=/var \
                --mandir=/usr/share/man \
                --infodir=/usr/share/info \
                --includedir=/usr/include \
        )
	touch $@

$(STAGING_DIR)/$(LIBNIH_BINARY): $(LIBNIH_DIR)/.configured
	$(MAKE) -C $(LIBNIH_DIR)
	touch -c $@

$(TARGET_DIR)/$(LIBNIH_TARGET_BINARY): $(STAGING_DIR)/$(LIBNIH_BINARY)
	$(MAKE) \
            prefix=$(TARGET_DIR)/usr \
            exec_prefix=$(TARGET_DIR)/usr \
            bindir=$(TARGET_DIR)/usr/bin \
            sbindir=$(TARGET_DIR)/usr/sbin \
            libexecdir=$(TARGET_DIR)/usr/lib \
            datadir=$(TARGET_DIR)/usr/share \
            sysconfdir=$(TARGET_DIR)/etc \
            localstatedir=$(TARGET_DIR)/var \
            libdir=$(TARGET_DIR)/usr/lib \
            infodir=$(TARGET_DIR)/usr/share/info \
            mandir=$(TARGET_DIR)/usr/share/man \
            includedir=$(TARGET_DIR)/usr/include \
	    -C $(LIBNIH_DIR) install
	touch -c $@

libnih: expat dbus host-libnih $(TARGET_DIR)/$(LIBNIH_TARGET_BINARY)

libnih-clean:
	-$(MAKE) DESTDIR=$(TARGET_DIR) -C $(LIBNIH_DIR) uninstall
	-$(MAKE) -C $(LIBNIH_DIR) clean

libnih-dirclean:
	rm -rf $(LIBNIH_DIR)


#############################################################
#
# libnih for the host
#
#############################################################

$(LIBNIH_HOST_DIR)/.configured: $(LIBNIH_SRC_DIR)/.unpacked
	mkdir -p $(LIBNIH_HOST_DIR)
	(cd $(LIBNIH_HOST_DIR); rm -rf config.cache; \
                $(HOST_CONFIGURE_OPTS) \
		DBUS_CFLAGS="-I$(STAGING_DIR)/usr/include/dbus-1.0 -I$(STAGING_DIR)/usr/lib/dbus-1.0/include" \
                DBUS_LIBS="$(DBUS_HOST_DIR)/dbus/.libs/libdbus-1.so" \
                CFLAGS="$(HOST_CFLAGS) -I$(STAGING_DIR)/usr/include/ -I$(STAGING_DIR)/usr/include/dbus-1.0/ -I$(STAGING_DIR)/usr/lib/dbus-1.0/include" \
                LDFLAGS="-L$(LIBNIH_HOST_DIR)/nih/.libs/  -L$(DBUS_HOST_DIR)/dbus/.libs/ -ldbus-1 -L$(EXPAT_HOST_DIR)/.libs/ -lexpat" \
                $(LIBNIH_SRC_DIR)/configure \
                --prefix=$(STAGING_DIR)/usr \
        )
	touch $@

$(LIBNIH_HOST_DIR)/$(LIBNIH_BINARY): $(LIBNIH_HOST_DIR)/.configured
	$(MAKE) -C $(LIBNIH_HOST_DIR)
	touch -c $@

$(LIBNIH): $(LIBNIH_HOST_DIR)/$(LIBNIH_BINARY)
	$(MAKE) -C $(LIBNIH_HOST_DIR) install
	touch -c $@

host-libnih: host-expat host-dbus $(LIBNIH) 

host-libnih-clean:
	-$(MAKE) -C $(LIBNIH_HOST_DIR) uninstall
	-$(MAKE) -C $(LIBNIH_HOST_DIR) clean

host-libnih-dirclean:
	rm -rf $(LIBNIH_HOST_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_LIBNIH),y)
TARGETS+=libnih
endif
