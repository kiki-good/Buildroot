#############################################################
#
# wayland
#
#############################################################

WAYLAND_VERSION = 1.7.0
WAYLAND_SITE = http://localhost/
WAYLAND_SOURCE = wayland-$(WAYLAND_VERSION).tar.xz
WAYLAND_LICENSE = MIT
WAYLAND_LICENSE_FILES = COPYING

WAYLAND_INSTALL_STAGING = YES
WAYLAND_INSTALL_TARGET = NO
WAYLAND_DEPENDENCIES = libffi expat host-expat

WAYLAND_DIR=$(BUILD_DIR)/wayland-$(WAYLAND_VERSION)
WAYLAND_BINARY_SOURCE:=wayland-$(WAYLAND_VERSION)-binary.tar.bz2
WAYLAND_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
WAYLAND_BINARY_DIR:=$(WAYLAND_BOARD_PATH)/binaries
WAYLAND_INSTALL_BINARY:=$(WAYLAND_BINARY_DIR)/$(WAYLAND_BINARY_SOURCE)
WAYLAND_TEMP_DIR:=$(WAYLAND_BINARY_DIR)/wayland_tmp

define WAYLAND_POST_INSTALL_PREBUILT_BINARIES
        mkdir -p $(WAYLAND_TEMP_DIR)
        $(MAKE) DESTDIR=$(PWD)/$(WAYLAND_TEMP_DIR) -C $(WAYLAND_DIR) install
        tar cjvf $(WAYLAND_BINARY_DIR)/$(WAYLAND_BINARY_SOURCE) -C $(WAYLAND_TEMP_DIR) .
        rm -rf $(WAYLAND_TEMP_DIR)
	cp -dpf $(STAGING_DIR)/usr/lib/libwayland-server*.so* $(TARGET_DIR)/usr/lib/
	cp -dpf $(STAGING_DIR)/usr/lib/libwayland-client*.so* $(TARGET_DIR)/usr/lib/
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libwayland*.so*
endef

#wayland-scanner has a dependancy on host-expat.
#The installation path for host-expat is need for building wayland-scanner
ifeq ($(BR2_ARCH_IS_64),y)
WAYLAND_EXPAT_VERSION:= 2.2.0
else
WAYLAND_EXPAT_VERSION:= 2.1.0
endif
WAYLAND_EXPAT_STAGING_HOST:=$(STAGING_DIR)/host/expat-$(WAYLAND_EXPAT_VERSION)
WAYLAND_EXPAT_HOST_INCLUDE:=$(WAYLAND_EXPAT_STAGING_HOST)/usr/local/include/
WAYLAND_EXPAT_HOST_LIBS:=$(WAYLAND_EXPAT_STAGING_HOST)/usr/local/lib/

# wayland needs a wayland-scanner program to generate some of its
# source code. By default, it builds it with CC, so it doesn't work with
# cross-compilation. Therefore, we build it manually, and tell wayland
# that the tool is already available.
WAYLAND_CONF_OPT = --disable-scanner

define WAYLAND_BUILD_SCANNER
	(cd $(@D)/src/; \
		$(HOSTCC) $(HOST_CFLAGS) $(HOST_LDFLAGS) -I$(WAYLAND_EXPAT_HOST_INCLUDE)\
			-o wayland-scanner scanner.c wayland-util.c -lexpat -L$(WAYLAND_EXPAT_HOST_LIBS))
endef

# also disable documentation, we don't need it and means the host has
# to have the latex generation tools
WAYLAND_CONF_OPT += --disable-documentation

# the libffi headers aren't put in the correct place for our build, so
# manually set the path
WAYLAND_CONF_ENV = FFI_CFLAGS="-I$(STAGING_DIR)/usr/lib/libffi-$(LIBFFI_VERSION)/include" \
                   FFI_LIBS="-L$(STAGING_DIR)/usr/lib -lffi"

WAYLAND_POST_CONFIGURE_HOOKS += WAYLAND_BUILD_SCANNER
WAYLAND_POST_INSTALL_STAGING_HOOKS += WAYLAND_POST_INSTALL_PREBUILT_BINARIES

wayland-binary:
	tar -xjvf $(WAYLAND_BINARY_DIR)/$(WAYLAND_BINARY_SOURCE) -C $(STAGING_DIR)/
	cp -dpf $(STAGING_DIR)/usr/lib/libwayland-server*.so* $(TARGET_DIR)/usr/lib/
	cp -dpf $(STAGING_DIR)/usr/lib/libwayland-client*.so* $(TARGET_DIR)/usr/lib/
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libwayland*.so*
	$(SED) "s,^libdir=.*,libdir\='$(STAGING_DIR)/usr/lib',g" $(STAGING_DIR)/usr/lib/libwayland-client.la
	$(SED) "s,^libdir=.*,libdir\='$(STAGING_DIR)/usr/lib',g" $(STAGING_DIR)/usr/lib/libwayland-server.la
	$(SED) "s,^libdir=.*,libdir\='$(STAGING_DIR)/usr/lib',g" $(STAGING_DIR)/usr/lib/libwayland-cursor.la

ifeq ($(wildcard $(WAYLAND_INSTALL_BINARY)),)
wayland: $(eval $(call AUTOTARGETS,package,wayland))
else
wayland: wayland-binary
endif

#############################################################
#
## Toplevel Makefile options
#
##############################################################
ifeq ($(BR2_PACKAGE_WAYLAND),y)
TARGETS+=wayland
endif
