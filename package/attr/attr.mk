#############################################################
#
# attr
#
#############################################################
ifeq ($(BR2_ARCH_IS_64),y)
ATTR_VERSION:=2.4.47
else
ATTR_VERSION:=2.4.44
endif
ATTR_SOURCE:=attr-$(ATTR_VERSION).src.tar.gz
ATTR_BINARY_SOURCE:=attr-$(ATTR_VERSION)-binary.tar.bz2
ATTR_SITE:=http://download.savannah.gnu.org/releases/attr/$(ATTR_SOURCE)
ATTR_DIR:=$(BUILD_DIR)/attr-$(ATTR_VERSION)
ATTR_CAT:=$(ZCAT)
ATTR_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
ATTR_BINARY_DIR:=$(ATTR_BOARD_PATH)/binaries
ATTR_INSTALL_BINARY:=$(ATTR_BINARY_DIR)/$(ATTR_BINARY_SOURCE)

$(DL_DIR)/$(ATTR_SOURCE): $(ATTR_PATCH)
	$(WGET) -P $(DL_DIR) $(ATTR_SITE)/$(ATTR_SOURCE)
	touch -c $@

attr-source: $(DL_DIR)/$(ATTR_SOURCE) $(ATTR_PATCH)

attr-unpacked: $(ATTR_DIR)/.unpacked
$(ATTR_DIR)/.unpacked: $(AUTOCONF) $(AUTOMAKE) $(LIBTOOL) $(DL_DIR)/$(ATTR_SOURCE)
	$(ATTR_CAT) $(DL_DIR)/$(ATTR_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(ATTR_DIR) package/attr/ attr-$(ATTR_VERSION)\*.patch*
ifneq ($(BR2_ARCH_IS_64),y)
	$(CONFIG_UPDATE) $(ATTR_DIR)
endif
	touch $@

$(ATTR_DIR)/.configured: $(ATTR_DIR)/.unpacked
	(cd $(ATTR_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		ac_cv_header_regex_h=no \
		enable_gettext=no \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--prefix=$(STAGING_DIR)/usr \
		--disable-debug \
		--disable-build-docs \
		LIBS=-L"$(STAGING_DIR)/usr/lib/libintl.so" \
	)
	touch $@
	$(MAKE) -C $(ATTR_DIR)
	$(MAKE) -C $(ATTR_DIR) install
	$(MAKE) -C $(ATTR_DIR) install-dev
	$(MAKE) -C $(ATTR_DIR) install-lib
	PREVIOUS_DIR=$(PWD)
	rm -rf $(STAGING_DIR)/usr/lib/libattr.a
	rm -rf $(STAGING_DIR)/usr/lib/libattr.la
	rm -rf $(STAGING_DIR)/usr/libexec/libattr.so
	(cd $(STAGING_DIR)/usr/lib/; \
	ln -sf ../libexec/libattr.a libattr.a; \
	ln -sf ../libexec/libattr.la libattr.la; \
	)
	(cd $(STAGING_DIR)/usr/libexec/; \
	ln -sf ../lib/libattr.so libattr.so; \
	)

	cd $(PREVIOUS_DIR)
	cp -vdrf $(STAGING_DIR)/usr/lib/libattr*.so* $(TARGET_DIR)/usr/lib/
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libattr*.so*

$(ATTR_DIR)/binary: $(ATTR_DIR)/.unpacked
	(cd $(ATTR_DIR); rm -rf config.cache; \
	 $(TARGET_CONFIGURE_OPTS) \
	 $(TARGET_CONFIGURE_ARGS) \
	 ac_cv_header_regex_h=no \
	 enable_gettext=no \
	 ./configure \
	 --target=$(GNU_TARGET_NAME) \
	 --host=$(GNU_TARGET_NAME) \
	 --build=$(GNU_HOST_NAME) \
	 --prefix=$(PWD)/$(BR2_BOARD_PATH)/binaries/attr_tmp/usr \
	 --disable-debug \
	 --disable-build-docs \
	 LIBS=-L"$(STAGING_DIR)/usr/lib/libintl.so" \
	)
	touch $@
	mkdir -p $(ATTR_BINARY_DIR)/attr_tmp
	$(MAKE) -C $(ATTR_DIR) install
	$(MAKE) -C $(ATTR_DIR) install-dev
	$(MAKE) -C $(ATTR_DIR) install-lib
	PREVIOUS_DIR=$(PWD)
	rm -rf $(ATTR_BINARY_DIR)/attr_tmp/usr/lib/libattr.a
	rm -rf $(ATTR_BINARY_DIR)/attr_tmp/usr/lib/libattr.la
	rm -rf $(ATTR_BINARY_DIR)/attr_tmp/usr/libexec/libattr.so
	(cd $(ATTR_BINARY_DIR)/attr_tmp/usr/lib/; \
	ln -sf ../libexec/libattr.a libattr.a; \
	ln -sf ../libexec/libattr.la libattr.la; \
	)
	(cd $(ATTR_BINARY_DIR)/attr_tmp/usr/libexec/; \
	ln -sf ../lib/libattr.so libattr.so; \
	)
	cd $(PREVIOUS_DIR)
	tar cjvf $(ATTR_BINARY_DIR)/$(ATTR_BINARY_SOURCE) -C $(ATTR_BINARY_DIR)/attr_tmp .
	rm -rf $(ATTR_BINARY_DIR)/attr_tmp

attr-binary:
	tar -xjvf $(ATTR_BINARY_DIR)/$(ATTR_BINARY_SOURCE) -C $(STAGING_DIR)/
	cp -vdrf $(STAGING_DIR)/usr/lib/libattr*.so* $(TARGET_DIR)/usr/lib/
ifeq ($(BR2_SKY_BUILD_TYPE), "debug")
	cp -vdrf $(STAGING_DIR)/usr/bin/getfattr $(TARGET_DIR)/usr/bin/
	cp -vdrf $(STAGING_DIR)/usr/bin/setfattr $(TARGET_DIR)/usr/bin/
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/bin/getfattr
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/bin/setfattr
endif
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libattr*.so*
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/lib\',g" $(STAGING_DIR)/usr/lib/libattr.la
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/libexec\',g" $(STAGING_DIR)/usr/libexec/libattr.la

ifeq ($(wildcard $(ATTR_INSTALL_BINARY)),)
attr: libintl $(ATTR_DIR)/.configured $(ATTR_DIR)/binary

else
attr: libintl attr-binary
endif

attr-clean:
	-$(MAKE) -C $(ATTR_DIR) clean
	rm -rf $(STAGING_DIR)/usr/include/attr
	rm -rf $(STAGING_DIR)/usr/lib/libattr.so*

attr-dirclean:
	rm -rf $(ATTR_DIR)

attr-binary-clean:
	rm -rf $(ATTR_INSTALL_BINARY)



#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_ATTR),y)
TARGETS+=attr
endif
