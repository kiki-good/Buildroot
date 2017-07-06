#############################################################
#
# libical
#
#############################################################
LIBICAL_VERSION:=0.48
LIBICAL_SOURCE:=libical-$(LIBICAL_VERSION).tar.gz
LIBICAL_SITE:=http://downloads.sourceforge.net/freeassociation/$(LIBICAL_VERSION)
LIBICAL_DIR:=$(BUILD_DIR)/libical-$(LIBICAL_VERSION)
LIBICAL_CAT:=$(ZCAT)
LIBICAL_BINARY:=usr/lib/libical.so

$(DL_DIR)/$(LIBICAL_SOURCE): 
	$(WGET) -P $(DL_DIR) $(LIBICAL_SITE)/$(LIBICAL_SOURCE)
	touch -c $@

libical-source: $(DL_DIR)/$(LIBICAL_SOURCE)

libical-unpacked: $(LIBICAL_DIR)/.unpacked
$(LIBICAL_DIR)/.unpacked: $(AUTOCONF) $(AUTOMAKE) $(LIBTOOL) $(DL_DIR)/$(LIBICAL_SOURCE)
	$(LIBICAL_CAT) $(DL_DIR)/$(LIBICAL_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(LIBICAL_DIR) package/libical/ libusb-$(LIBICAL_VERSION)\*.patch*
	$(CONFIG_UPDATE) $(LIBICAL_DIR)
	cd $(LIBICAL_DIR) && $(AUTOCONF)
	touch $@

$(LIBICAL_DIR)/.configured: $(LIBICAL_DIR)/.unpacked
	(cd $(LIBICAL_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		ac_cv_header_regex_h=no \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--prefix=$(STAGING_DIR)/usr \
		--disable-debug \
		--disable-build-docs \
	)
	touch $@

$(STAGING_DIR)/usr/lib/libical.so: $(LIBICAL_DIR)/.configured
	$(MAKE) -C $(LIBICAL_DIR)
	$(MAKE) -C $(LIBICAL_DIR) install

$(TARGET_DIR)/$(LIBICAL_BINARY): $(STAGING_DIR)/usr/lib/libical.so
	mkdir -p $(TARGET_DIR)/usr/lib/
	cp -dpf $(STAGING_DIR)/usr/lib/libical*.so* $(TARGET_DIR)/usr/lib/
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libical*.so*

libical: uclibc pkgconfig autoconf $(TARGET_DIR)/$(LIBICAL_BINARY)

libical-clean:
	rm -f $(STAGING_DIR)/bin/libical-config
	rm -f $(STAGING_DIR)/lib/libical*
	rm -rf $(STAGING_DIR)/lib/pkgconfig
	rm -f $(TARGET_DIR)/usr/lib/libical*
	-$(MAKE) -C $(LIBICAL_DIR) clean

libical-dirclean:
	rm -rf $(LIBICAL_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_LIBICAL),y)
TARGETS+=libical
endif
