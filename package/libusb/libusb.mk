#############################################################
#
# libusb
#
#############################################################
ifeq ($(BR2_ARCH_IS_64),y)
#LIBUSB_VERSION:=1.0.20
LIBUSB_VERSION:=0.1.12
else
LIBUSB_VERSION:=0.1.12
endif
LIBUSB_SOURCE:=libusb-$(LIBUSB_VERSION).tar.gz
LIBUSB_SITE:=http://snapshot.debian.net/archive/2008/04/27/debian/pool/main/libu/libusb
LIBUSB_DIR:=$(BUILD_DIR)/libusb-$(LIBUSB_VERSION)
LIBUSB_CAT:=$(ZCAT)
ifeq ($(LIBUSB_VERSION),1.0.20)
LIBUSB_BINARY:=usr/lib/libusb-1.0.so
else
LIBUSB_BINARY:=usr/lib/libusb.so
endif

$(DL_DIR)/$(LIBUSB_SOURCE): $(LIBUSB_PATCH)
	$(WGET) -P $(DL_DIR) $(LIBUSB_SITE)/$(LIBUSB_SOURCE)
	touch -c $@

libusb-source: $(DL_DIR)/$(LIBUSB_SOURCE) $(LIBUSB_PATCH)

libusb-unpacked: $(LIBUSB_DIR)/.unpacked
$(LIBUSB_DIR)/.unpacked: $(AUTOCONF) $(AUTOMAKE) $(LIBTOOL) $(DL_DIR)/$(LIBUSB_SOURCE)
	$(LIBUSB_CAT) $(DL_DIR)/$(LIBUSB_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -

ifneq ($(BR2_ARCH_IS_64),y)
	toolchain/patch-kernel.sh $(LIBUSB_DIR) package/libusb/ libusb-$(LIBUSB_VERSION)\*.patch*
	$(CONFIG_UPDATE) $(LIBUSB_DIR)
else
	toolchain/patch-kernel.sh $(LIBUSB_DIR) package/libusb/64bitPatch libusb-$(LIBUSB_VERSION)\*.patch*
endif

ifeq ($(LIBUSB_VERSION),1.0.21)
        cd $(LIBUSB_DIR) && ./autogen.sh
else
	cd $(LIBUSB_DIR) && $(AUTOCONF)
endif
	touch $@

ifneq ($(LIBUSB_VERSION),1.0.20)
$(LIBUSB_DIR)/.configured: $(LIBUSB_DIR)/.unpacked
	(cd $(LIBUSB_DIR); rm -rf config.cache; \
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
else
$(LIBUSB_DIR)/.configured: $(LIBUSB_DIR)/.unpacked
	(cd $(LIBUSB_DIR); rm -rf config.cache; \
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
		--enable-udev=no \
	)
	touch $@
endif

$(STAGING_DIR)/usr/lib/libusb.so: $(LIBUSB_DIR)/.configured
ifeq ($(LIBUSB_VERSION),1.0.20)
#common issue is reported at https://sourceforge.net/p/libusb/mailman/message/34454335/ 
	make -C $(LIBUSB_DIR)
	make -C $(LIBUSB_DIR) install
else
	$(MAKE) -C $(LIBUSB_DIR)
	$(MAKE) -C $(LIBUSB_DIR) install
endif

ifeq ($(LIBUSB_VERSION),1.0.20)
$(TARGET_DIR)/$(LIBUSB_BINARY): $(STAGING_DIR)/usr/lib/libusb-1.0.so
	cp -dpf $(STAGING_DIR)/usr/lib/libusb[^p]*.so* $(TARGET_DIR)/usr/lib/
	cp -dpf $(STAGING_DIR)/usr/lib/libusb-1.0.so $(TARGET_DIR)/usr/lib/
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libusb*.so*
else
$(TARGET_DIR)/$(LIBUSB_BINARY): $(STAGING_DIR)/usr/lib/libusb.so
	cp -dpf $(STAGING_DIR)/usr/lib/libusb[^p]*.so* $(TARGET_DIR)/usr/lib/
	cp -dpf $(STAGING_DIR)/usr/lib/libusb.so $(TARGET_DIR)/usr/lib/
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libusb*.so*
endif

libusb: autoconf $(TARGET_DIR)/$(LIBUSB_BINARY)

libusb-clean:
	rm -f $(STAGING_DIR)/bin/libusb-config
	rm -f $(STAGING_DIR)/usr/includes/usb*.h
	rm -f $(STAGING_DIR)/lib/libusb*
	rm -rf $(STAGING_DIR)/lib/pkgconfig
	rm -f $(TARGET_DIR)/usr/lib/libusb*
	-$(MAKE) -C $(LIBUSB_DIR) clean

libusb-dirclean:
	rm -rf $(LIBUSB_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_LIBUSB),y)
TARGETS+=libusb
endif
