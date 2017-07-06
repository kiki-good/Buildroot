#############################################################
#
# freetype
#
#############################################################
FREETYPE_VERSION = $(strip $(subst ",, $(BR2_FREETYPE_VERSION)))
FREETYPE_SITE = http://localhost/
FREETYPE_SOURCE = freetype-$(FREETYPE_VERSION).tar.bz2
FREETYPE_LIBTOOL_PATCH = NO
FREETYPE_INSTALL_STAGING = YES
FREETYPE_INSTALL_TARGET = YES

FREETYPE_DIR=$(BUILD_DIR)/freetype-$(FREETYPE_VERSION)
FREETYPE_BINARY_SOURCE:=freetype-$(FREETYPE_VERSION)-binary.tar.bz2
FREETYPE_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
FREETYPE_BINARY_DIR:=$(FREETYPE_BOARD_PATH)/binaries
FREETYPE_INSTALL_BINARY:=$(FREETYPE_BINARY_DIR)/$(FREETYPE_BINARY_SOURCE)
FREETYPE_TEMP_DIR:=$(FREETYPE_BINARY_DIR)/freetype_tmp

FREETYPE_MAKE_OPT = CCexe="$(HOSTCC)"
FREETYPE_DEPENDENCIES = pkgconfig zlib
FREETYPE_CONF_OPT = --with-png=no

define FREETYPE_POST_INSTALL_PREBUILT_BINARIES
	ln -s $(STAGING_DIR)/usr/include/freetype2 $(STAGING_DIR)/usr/include/freetype
	mkdir -p $(FREETYPE_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(FREETYPE_TEMP_DIR) -C $(FREETYPE_DIR) install
	tar cjvf $(FREETYPE_BINARY_DIR)/$(FREETYPE_BINARY_SOURCE) -C $(FREETYPE_TEMP_DIR) .
	rm -rf $(FREETYPE_TEMP_DIR)
endef

FREETYPE_POST_INSTALL_STAGING_HOOKS +=FREETYPE_POST_INSTALL_PREBUILT_BINARIES


$(FREETYPE_TARGET_INSTALL_TARGET):
	-cp -a $(FREETYPE_DIR)/objs/.libs/libfreetype.so* $(TARGET_DIR)/usr/lib/
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libfreetype.so
	$(SED) "s,^prefix=.*,prefix=\'$(STAGING_DIR)/usr\',g" $(STAGING_DIR)/usr/bin/freetype-config
	$(SED) "s,^exec_prefix=.*,exec_prefix=\'$(STAGING_DIR)/usr\',g" $(STAGING_DIR)/usr/bin/freetype-config
ifneq ($(BR2_PACKAGE_FREETYPE_FONTS_TARBALL),"")
	# Install platform-specific fonts into the default place
	mkdir -p $(TARGET_DIR)/usr/share/fonts
	$(TAR) -C $(TARGET_DIR)/usr/share/fonts -xf package/freetype/$(BR2_PACKAGE_FREETYPE_FONTS_TARBALL)
endif
	touch $@

freetype-binary:
	tar -xjvf $(FREETYPE_BINARY_DIR)/$(FREETYPE_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(FREETYPE_BINARY_DIR)/$(FREETYPE_BINARY_SOURCE) -C $(TARGET_DIR)/
	rm -f $(TARGET_DIR)/usr/bin/freetype-config
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libfreetype.so
	$(SED) "s,^prefix=.*,prefix=\'$(STAGING_DIR)/usr\',g" $(STAGING_DIR)/usr/bin/freetype-config
	$(SED) "s,^exec_prefix=.*,exec_prefix=\'$(STAGING_DIR)/usr\',g" $(STAGING_DIR)/usr/bin/freetype-config
ifneq ($(BR2_PACKAGE_FREETYPE_FONTS_TARBALL),"")
	# Install platform-specific fonts into the default place
	mkdir -p $(TARGET_DIR)/usr/share/fonts
	$(TAR) -C $(TARGET_DIR)/usr/share/fonts -xf package/freetype/$(BR2_PACKAGE_FREETYPE_FONTS_TARBALL)
endif
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib \
	-L$(STAGING_DIR)/usr/lib -lz',g" $(STAGING_DIR)/usr/lib/libfreetype.la
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/lib\',g" $(STAGING_DIR)/usr/lib/libfreetype.la

ifeq ($(wildcard $(FREETYPE_INSTALL_BINARY)),)
freetype: $(eval $(call AUTOTARGETS,package,freetype))
else
freetype: freetype-binary
endif

freetype-binary-clean:
	rm $(FREETYPE_INSTALL_BINARY)

ifeq ($(BR2_PACKAGE_FREETYPE),y)
TARGETS+=freetype
endif
