#############################################################
#
# libacl
#
#############################################################
LIBACL_VERSION:=2.2.52
LIBACL_SOURCE:=acl-$(LIBACL_VERSION).src.tar.gz
LIBACL_SITE:=http://download.savannah.gnu.org/releases/acl/$(LIBACL_SOURCE)
LIBACL_DIR:=$(BUILD_DIR)/acl-$(LIBACL_VERSION)
LIBACL_CAT:=$(ZCAT)
LIBACL_BINARY:=usr/lib/libacl.so

$(DL_DIR)/$(LIBACL_SOURCE): $(LIBACL_PATCH)
	$(WGET) -P $(DL_DIR) $(LIBACL_SITE)/$(LIBACL_SOURCE)
	touch -c $@

libacl-source: $(DL_DIR)/$(LIBACL_SOURCE) $(LIBACL_PATCH)

libacl-unpacked: $(LIBACL_DIR)/.unpacked
$(LIBACL_DIR)/.unpacked: $(AUTOCONF) $(AUTOMAKE) $(LIBTOOL) $(DL_DIR)/$(LIBACL_SOURCE)
	$(LIBACL_CAT) $(DL_DIR)/$(LIBACL_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
ifneq ($(BR2_ARCH_IS_64),y)
	toolchain/patch-kernel.sh $(LIBACL_DIR) package/libacl/ libacl-$(LIBACL_VERSION)\*.patch*
	$(CONFIG_UPDATE) $(LIBACL_DIR)
else
	toolchain/patch-kernel.sh $(LIBACL_DIR) package/libacl/64bitPatch libacl-$(LIBACL_VERSION)\*.patch*
endif
	touch $@

$(LIBACL_DIR)/.configured: $(LIBACL_DIR)/.unpacked
	(cd $(LIBACL_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		ac_cv_header_regex_h=no \
		CFLAGS=-I"$(STAGING_DIR)/usr/include" \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--prefix=$(STAGING_DIR)/usr \
		--disable-debug \
		--disable-build-docs \
		--enable-gettext=no \
		LDFLAGS=-L"$(STAGING_DIR)/usr/lib/" \
	)
	touch $@

$(STAGING_DIR)/usr/lib/libacl.so: $(LIBACL_DIR)/.configured
	$(MAKE) -C $(LIBACL_DIR)
	$(MAKE) -C $(LIBACL_DIR) install
	$(MAKE) -C $(LIBACL_DIR) install-dev
	$(MAKE) -C $(LIBACL_DIR) install-lib

$(TARGET_DIR)/$(LIBACL_BINARY): $(STAGING_DIR)/usr/lib/libacl.so
	PREVIOUS_DIR=$(PWD)
	rm -rf $(STAGING_DIR)/usr/lib/libacl.a
	rm -rf $(STAGING_DIR)/usr/lib/libacl.la
	rm -rf $(STAGING_DIR)/usr/libexec/libacl.so
	(cd $(STAGING_DIR)/usr/lib/; \
        ln -sf ../libexec/libacl.a libacl.a; \
        ln -sf ../libexec/libacl.la libacl.la; \
        )
	(cd $(STAGING_DIR)/usr/libexec/; \
        ln -sf ../lib/libacl.so libacl.so; \
        )
	cd $(PREVIOUS_DIR)
	cp -vdpf $(STAGING_DIR)/usr/lib/libacl*.so* $(TARGET_DIR)/usr/lib/
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libacl*.so*

libacl: attr libintl $(TARGET_DIR)/$(LIBACL_BINARY)

libacl-clean:
	rm -f $(STAGING_DIR)/bin/libacl-config
	rm -f $(STAGING_DIR)/usr/includes/usb*.h
	rm -f $(STAGING_DIR)/lib/libacl*
	rm -rf $(STAGING_DIR)/lib/pkgconfig
	rm -f $(TARGET_DIR)/usr/lib/libacl*
	-$(MAKE) -C $(LIBACL_DIR) clean

libacl-dirclean:
	rm -rf $(LIBACL_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_LIBACL),y)
TARGETS+=libacl
endif
