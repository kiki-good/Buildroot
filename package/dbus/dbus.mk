#############################################################
#
# dbus
#
#############################################################
DBUS_VERSION:=1.8.20
DBUS_SOURCE:=dbus-$(DBUS_VERSION).tar.gz
DBUS_BINARY_SOURCE:=dbus-$(DBUS_VERSION)-binary.tar.bz2
DBUS_SITE:=http://dbus.freedesktop.org/releases/dbus/dbus-$(DBUS_VERSION).tar.gz
DBUS_DIR:=$(BUILD_DIR)/dbus-$(DBUS_VERSION)
DBUS_HOST_DIR:=$(TOOL_BUILD_DIR)/dbus-$(DBUS_VERSION)-host
DBUS_CAT:=$(ZCAT)
DBUS_BINARY:=bus/dbus-daemon
DBUS_TARGET_BINARY:=usr/bin/dbus-daemon
DBUS_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
DBUS_BINARY_DIR:=$(DBUS_BOARD_PATH)/binaries
DBUS_INSTALL_BINARY:=$(DBUS_BINARY_DIR)/$(DBUS_BINARY_SOURCE)
DBUS:=$(TARGET_DIR)/usr/bin/dbus-daemon
DBUS_SRC_DIR:=$(TOOL_BUILD_DIR)/dbus-$(DBUS_VERSION)

ifeq ($(BR2_DBUS_EXPAT),y)
DBUS_XML:=expat
# depend on the exact library file instead of expat so dbus isn't always
# considered out-of-date
DBUS_XML_DEP:=$(STAGING_DIR)/usr/lib/libexpat.so.1
else
DBUS_XML:=libxml2
# Makefile.autotools.in unfortunately has broken dependency handling,
# so we cannot do the same for libxml2
DBUS_XML_DEP:=libxml2-install-staging
endif

$(DL_DIR)/$(DBUS_SOURCE):
	$(WGET) -P $(DL_DIR) $(DBUS_SITE)/$(DBUS_SOURCE)

dbus-source: $(DL_DIR)/$(DBUS_SOURCE)

$(DBUS_SRC_DIR)/.unpacked: $(DL_DIR)/$(DBUS_SOURCE)
	$(DBUS_CAT) $(DL_DIR)/$(DBUS_SOURCE) | tar -C $(TOOL_BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(DBUS_SRC_DIR) package/dbus/ dbus-$(DBUS_VERSION)\*.patch*
	touch $@

#############################################################
#
### dbus for the target
#
###############################################################

$(DBUS_DIR)/.configured: $(DBUS_SRC_DIR)/.unpacked $(DBUS_XML_DEP)
	mkdir -p $(DBUS_DIR)
	(cd $(DBUS_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		ac_cv_have_abstract_sockets=yes \
		$(DBUS_SRC_DIR)/configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--prefix=/usr \
		--exec-prefix=/usr \
		--localstatedir=/var \
		--program-prefix="" \
		--sysconfdir=/DBUS/etc \
		--datadir=/DBUS/share \
		--with-dbus-user=messagebus \
		--disable-tests \
		--disable-asserts \
		--enable-abstract-sockets \
		--enable-usb \
		--disable-selinux \
		--disable-xml-docs \
		--disable-doxygen-docs \
		--disable-static \
		--enable-dnotify \
		--without-x \
		--with-xml=$(DBUS_XML)\
		--with-system-socket=/DBUS/var/run/dbus/system_bus_socket \
		--with-system-pid-file=/DBUS/var/run/messagebus.pid \
	        --with-systemdsystemunitdir=/DBUS/share/dbus-1/system-services \
		LDFLAGS=-L$(STAGING_DIR)/usr/lib/ \
                CFLAGS="-I$(STAGING_DIR)/usr/include/ -I$(STAGING_DIR)/usr/lib/glib-2.0/include/ -I$(STAGING_DIR)/usr/include/dbus-1.0/" \
	)
	touch $@

$(DBUS_DIR)/$(DBUS_BINARY): $(DBUS_DIR)/.configured
	$(MAKE) -C $(DBUS_DIR) all

$(STAGING_DIR)/$(DBUS_TARGET_BINARY): $(DBUS_DIR)/$(DBUS_BINARY)
	$(MAKE) DESTDIR=$(STAGING_DIR) -C $(DBUS_DIR) install
	mkdir -p $(DBUS_BINARY_DIR)/dbus_tmp
	$(MAKE) DESTDIR=$(PWD)/$(DBUS_BINARY_DIR)/dbus_tmp -C $(DBUS_DIR) install

$(TARGET_DIR)/$(DBUS_TARGET_BINARY): $(STAGING_DIR)/$(DBUS_TARGET_BINARY)
	mkdir -p $(TARGET_DIR)/DBUS/var/run/dbus $(TARGET_DIR)/DBUS/var/lib/dbus $(TARGET_DIR)/etc/init.d
ifeq ($(BR2_STRIP_none),y)
	$(MAKE) DESTDIR=$(TARGET_DIR) \
		initdir=/etc/init.d -C $(DBUS_DIR) install
	$(MAKE) DESTDIR=$(PWD)/$(DBUS_BINARY_DIR)/dbus_tmp \
		initdir=/etc/init.d -C $(DBUS_DIR) install
else
	$(MAKE) DESTDIR=$(TARGET_DIR) STRIPPROG='$(STRIPCMD)' \
		initdir=/etc/init.d -C $(DBUS_DIR) install-strip
	$(MAKE) DESTDIR=$(PWD)/$(DBUS_BINARY_DIR)/dbus_tmp STRIPPROG='$(STRIPCMD)' \
		initdir=/etc/init.d -C $(DBUS_DIR) install-strip
endif
	rm -rf $(TARGET_DIR)/usr/lib/dbus-1.0 \
		$(TARGET_DIR)/usr/lib/libdbus-1.la \
		$(TARGET_DIR)/usr/include/dbus-1.0 \
		$(TARGET_DIR)/usr/lib/pkgconfig
	chmod 4755 $(STAGING_DIR)/usr/libexec/dbus-daemon-launch-helper 
	chmod 4755 $(TARGET_DIR)/usr/libexec/dbus-daemon-launch-helper
	chmod 4755 $(DBUS_BINARY_DIR)/dbus_tmp/usr/libexec/dbus-daemon-launch-helper
	rm -f $(TARGET_DIR)/etc/init.d/messagebus
ifneq ($(BR2_SKY_BUILD_TYPE),"debug")
	rm -f $(TARGET_DIR)/usr/bin/dbus-send
	rm -f $(TARGET_DIR)/usr/bin/dbus-monitor
	$(INSTALL) -m 0440 package/dbus/dbus-$(DBUS_VERSION)-session.conf $(TARGET_DIR)/DBUS/etc/dbus-1/session.conf
endif

ifneq ($(BR2_HAVE_MANPAGES),y)
	rm -rf $(TARGET_DIR)/usr/share/man
endif
	$(INSTALL) -m 0755 package/dbus/mw-as.conf $(TARGET_DIR)/DBUS/etc/dbus-1/system.d/
	$(INSTALL) -m 0440 package/dbus/mw-ai.conf $(TARGET_DIR)/DBUS/etc/dbus-1/system.d/
	tar cjvf $(DBUS_BINARY_DIR)/$(DBUS_BINARY_SOURCE) -C $(DBUS_BINARY_DIR)/dbus_tmp .
	rm -rf $(DBUS_BINARY_DIR)/dbus_tmp


dbus-binary:
	tar -xjvf $(DBUS_BINARY_DIR)/$(DBUS_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(DBUS_BINARY_DIR)/$(DBUS_BINARY_SOURCE) -C $(TARGET_DIR)/
	$(INSTALL) -m 0755 package/dbus/mw-as.conf $(TARGET_DIR)/DBUS/etc/dbus-1/system.d/
	$(INSTALL) -m 0440 package/dbus/mw-ai.conf $(TARGET_DIR)/DBUS/etc/dbus-1/system.d/
	rm -rf $(TARGET_DIR)/usr/lib/dbus-1.0 \
		$(TARGET_DIR)/usr/lib/libdbus-1.la \
		$(TARGET_DIR)/usr/include/dbus-1.0 \
		$(TARGET_DIR)/usr/lib/pkgconfig
	rm -f $(TARGET_DIR)/etc/init.d/messagebus
ifneq ($(BR2_SKY_BUILD_TYPE),"debug")
	rm -f $(TARGET_DIR)/usr/bin/dbus-send
	rm -f $(TARGET_DIR)/usr/bin/dbus-monitor
	$(INSTALL) -m 0440 package/dbus/dbus-$(DBUS_VERSION)-session.conf $(TARGET_DIR)/DBUS/etc/dbus-1/session.conf
endif
	
ifneq ($(BR2_HAVE_MANPAGES),y)
	rm -rf $(TARGET_DIR)/usr/share/man
endif

ifeq ($(wildcard $(DBUS_INSTALL_BINARY)),) 
dbus: uclibc pkgconfig expat $(TARGET_DIR)/$(DBUS_TARGET_BINARY)
else
dbus: uclibc pkgconfig expat dbus-binary
endif

dbus-clean:
	rm -f $(TARGET_DIR)/DBUS/etc/dbus-1/session.conf
	rm -f $(TARGET_DIR)/DBUS/etc/dbus-1/system.conf
	rmdir -p --ignore-fail-on-non-empty $(TARGET_DIR)/etc/dbus-1/system.d
	rm -f $(TARGET_DIR)/usr/lib/libdbus-1.so*
	rm -f $(TARGET_DIR)/usr/bin/dbus-daemon
	rm -rf $(TARGET_DIR)/tmp/dbus
	rm -f $(STAGING_DIR)/usr/lib/libdbus-1.*
	rm -rf $(STAGING_DIR)/usr/lib/dbus-1.0
	rm -rf $(STAGING_DIR)/usr/include/dbus-1.0
	rmdir --ignore-fail-on-non-empty $(STAGING_DIR)/usr/include
	-$(MAKE) -C $(DBUS_DIR) clean

dbus-dirclean:
	rm -rf $(DBUS_DIR)
dbus-binary-clean:
	rm -rf $(DBUS_INSTALL_BINARY)


#############################################################
#
### dbus for the host
#
###############################################################

$(DBUS_HOST_DIR)/.configured: $(DBUS_SRC_DIR)/.unpacked  $(DBUS_XML_DEP)
	mkdir -p $(DBUS_HOST_DIR)
	(cd $(DBUS_HOST_DIR); rm -rf config.cache; \
                $(HOST_CONFIGURE_OPTS) \
                CFLAGS="-I$(STAGING_DIR)/usr/include/ -I$(STAGING_DIR)/usr/lib/glib-2.0/include/ -I$(STAGING_DIR)/usr/include/dbus-1.0/" \
                LDFLAGS="-L$(EXPAT_HOST_DIR)/.libs/ -lexpat" \
                $(DBUS_SRC_DIR)/configure \
                --prefix=$(STAGING_DIR)/usr \
		--with-xml=$(DBUS_XML)\
                --disable-tests \
                --disable-asserts \
                --enable-abstract-sockets \
                --enable-usb \
                --disable-selinux \
                --disable-xml-docs \
                --disable-doxygen-docs \
                --disable-static \
		--with-dbus-glib=no \
	)
	touch $@

$(DBUS_HOST_DIR)/$(DBUS_BINARY): host-expat $(DBUS_HOST_DIR)/.configured
	$(MAKE) -C $(DBUS_HOST_DIR)
	touch -c $@

host-dbus: $(DBUS_HOST_DIR)/$(DBUS_BINARY)

host-dbus-clean:
	-$(MAKE) -C $(DBUS_HOST_DIR) uninstall
	-$(MAKE) -C $(DBUS_HOST_DIR) clean

host-dbus-dirclean:
	rm -rf $(DBUS_HOST_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_DBUS),y)
TARGETS+=dbus
DBUS_DEPENDS+=expat
endif
