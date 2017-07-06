#############################################################
#
# fontconfig
#
#############################################################
FONTCONFIG_VERSION = 2.6.0
FONTCONFIG_SOURCE = fontconfig-$(FONTCONFIG_VERSION).tar.gz
FONTCONFIG_SITE = http://local-host/
FONTCONFIG_AUTORECONF = YES
FONTCONFIG_USE_CONFIG_CACHE = NO
FONTCONFIG_INSTALL_STAGING = YES
FONTCONFIG_INSTALL_TARGET = YES

FONTCONFIG_DIR=$(BUILD_DIR)/fontconfig-$(FONTCONFIG_VERSION)
FONTCONFIG_BINARY_SOURCE:=fontconfig-$(FONTCONFIG_VERSION)-binary.tar.bz2
FONTCONFIG_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
FONTCONFIG_BINARY_DIR:=$(FONTCONFIG_BOARD_PATH)/binaries
FONTCONFIG_INSTALL_BINARY:=$(FONTCONFIG_BINARY_DIR)/$(FONTCONFIG_BINARY_SOURCE)
FONTCONFIG_TEMP_DIR:=$(FONTCONFIG_BINARY_DIR)/fontconfig_tmp

define FONTCONFIG_POST_INSTALL_PREBUILT_BINARIES
	mkdir -p $(FONTCONFIG_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(FONTCONFIG_TEMP_DIR) -C $(FONTCONFIG_DIR) install
	tar cjvf $(FONTCONFIG_BINARY_DIR)/$(FONTCONFIG_BINARY_SOURCE) -C $(FONTCONFIG_TEMP_DIR) .
	rm -rf $(FONTCONFIG_TEMP_DIR)
endef

FONTCONFIG_POST_INSTALL_STAGING_HOOKS += FONTCONFIG_POST_INSTALL_PREBUILT_BINARIES

# This package does not like using the target cflags for some reason.
FONTCONFIG_CONF_ENV = CFLAGS="-I$(STAGING_DIR)/usr/include/freetype" LDFLAGS="-L$(STAGING_DIR)/usr/lib/ -lz"

FONTCONFIG_CONF_OPT = --with-arch=$(GNU_TARGET_NAME) \
		--with-sysroot="$(STAGING_DIR)" \
		--with-freetype-config="$(STAGING_DIR)/usr/bin/freetype-config" \
		--localstatedir=/var \
		--sysconfdir=/etc \
		--disable-docs

FONTCONFIG_DEPENDENCIES = freetype zlib expat libiconv

define FONTCONFIG_POST_INSTALL_HOOK
	rm -rf $(TARGET_DIR)/etc/fonts/conf.d/README
	touch $@
endef

FONTCONFIG_POST_INSTALL_TARGET_HOOKS += FONTCONFIG_POST_INSTALL_HOOK

fontconfig-binary:
	tar -xjvf $(FONTCONFIG_BINARY_DIR)/$(FONTCONFIG_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(FONTCONFIG_BINARY_DIR)/$(FONTCONFIG_BINARY_SOURCE) -C $(TARGET_DIR)/
	rm -f $(TARGET_DIR)/usr/bin/fc-list
	rm -f $(TARGET_DIR)/usr/bin/fc-match
	rm -f $(TARGET_DIR)/usr/bin/fc-cat
	rm -rf $(TARGET_DIR)/etc/fonts/conf.d/README
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/lib\',g" $(STAGING_DIR)/usr/lib/libfontconfig.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib \
	-L$(STAGING_DIR)/usr/lib $(STAGING_DIR)/usr/lib/libfreetype.la -lz \
	$(STAGING_DIR)/usr/lib/libexpat.la',g" $(STAGING_DIR)/usr/lib/libfontconfig.la

ifeq ($(wildcard $(FONTCONFIG_INSTALL_BINARY)),)
fontconfig: $(eval $(call AUTOTARGETS,package,fontconfig))
else
fontconfig: fontconfig-binary
endif

fontconfig-binary-clean:
	rm $(FONTCONFIG_INSTALL_BINARY)

ifeq ($(BR2_PACKAGE_FONTCONFIG),y)
TARGETS+=fontconfig
endif

