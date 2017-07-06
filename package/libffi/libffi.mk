#############################################################
#
# libffi
#
#############################################################
ifeq ($(BR2_ARCH_IS_64),y)
LIBFFI_VERSION:=3.2.1
else
LIBFFI_VERSION:=3.0.13
endif
LIBFFI_SOURCE:=libffi-$(LIBFFI_VERSION).tar.gz
LIBFFI_BINARY_SOURCE:=libffi-$(LIBFFI_VERSION)-binary.tar.bz2
LIBFFI_SITE:=ftp://sourceware.org/pub/libffi/$(LIBFFI_VERSION)
LIBFFI_DIR:=$(BUILD_DIR)/libffi-$(LIBFFI_VERSION)
LIBFFI_CAT:=$(ZCAT)
LIBFFI_BINARY:=usr/lib/libffi.so
LIBFFI_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
LIBFFI_BINARY_DIR:=$(LIBFFI_BOARD_PATH)/binaries
LIBFFI_INSTALL_BINARY:=$(LIBFFI_BINARY_DIR)/$(LIBFFI_BINARY_SOURCE)


$(DL_DIR)/$(LIBFFI_SOURCE): $(LIBFFI_PATCH)
	$(WGET) -P $(DL_DIR) $(LIBFFI_SITE)/$(LIBFFI_SOURCE)
	touch -c $@

libffi-source: $(DL_DIR)/$(LIBFFI_SOURCE) $(LIBFFI_PATCH)

libffi-unpacked: $(LIBFFI_DIR)/.unpacked
$(LIBFFI_DIR)/.unpacked: $(DL_DIR)/$(LIBFFI_SOURCE)
	$(LIBFFI_CAT) $(DL_DIR)/$(LIBFFI_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(LIBFFI_DIR) package/libffi/ libffi-$(LIBFFI_VERSION)\*.patch*
ifneq ($(BR2_ARCH_IS_64),y)
	$(CONFIG_UPDATE) $(LIBFFI_DIR)
endif
	cd $(LIBFFI_DIR) && $(AUTOCONF)
	touch $@

$(LIBFFI_DIR)/.configured: $(LIBFFI_DIR)/.unpacked
	(cd $(LIBFFI_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		ac_cv_header_regex_h=no \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--prefix=$(STAGING_DIR)/usr \
		--with-gcc-arch=mips \
		--disable-debug \
		--disable-build-docs \
	)
	touch $@
$(LIBFFI_DIR)/binary: $(LIBFFI_DIR)/.unpacked
	(cd $(LIBFFI_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		ac_cv_header_regex_h=no \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--prefix=$(PWD)/$(LIBFFI_BINARY_DIR)/libffi_tmp/usr \
		--with-gcc-arch=mips \
		--disable-debug \
		--disable-build-docs \
	)
	touch $@
	mkdir -p $(LIBFFI_BINARY_DIR)/libffi_tmp
	$(MAKE) -C $(LIBFFI_DIR) install
	tar -cjvf $(LIBFFI_BINARY_DIR)/$(LIBFFI_BINARY_SOURCE) -C $(LIBFFI_BINARY_DIR)/libffi_tmp .
	rm -rf $(LIBFFI_BINARY_DIR)/libffi_tmp


$(STAGING_DIR)/usr/lib/libffi.so: $(LIBFFI_DIR)/.configured
	$(MAKE) -C $(LIBFFI_DIR)
	$(MAKE) -C $(LIBFFI_DIR) install
	#mkdir -p $(LIBFFI_BINARY_DIR)/libffi_tmp
	#$(MAKE) DESTDIR=$(PWD)/$(LIBFFI_BINARY_DIR)/libffi_tmp -C $(LIBFFI_DIR) install
	#cd $(PWD)/$(LIBFFI_BINARY_DIR)
	#tar -cjvf $(LIBFFI_BINARY_DIR)/$(LIBFFI_BINARY_SOURCE) -C $(LIBFFI_BINARY_DIR)/libffi_tmp .
	#rm -rf $(LIBFFI_BINARY_DIR)/libffi_tmp

$(TARGET_DIR)/$(LIBFFI_BINARY): $(STAGING_DIR)/usr/lib/libffi.so $(LIBFFI_DIR)/binary
	mkdir -p $(TARGET_DIR)/usr/lib/
ifeq ($(BR2_ARCH_IS_64),y)
	#Work Around:TO FIX
	mkdir -p $(STAGING_DIR)/usr/lib/
	cp -dpf $(STAGING_DIR)/usr/lib64/libffi*.so* $(TARGET_DIR)/usr/lib/
	cp -dpf $(STAGING_DIR)/usr/lib64/libffi*.so* $(STAGING_DIR)/usr/lib/
	cp -dpf $(STAGING_DIR)/usr/lib64/libffi*.la $(STAGING_DIR)/usr/lib
	#$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib64/libffi*.so*
else
	cp -dpf $(STAGING_DIR)/usr/lib/libffi*.so* $(TARGET_DIR)/usr/lib/
endif
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libffi*.so*

libffi-binary:
	tar -xjvf $(LIBFFI_BINARY_DIR)/$(LIBFFI_BINARY_SOURCE) -C $(STAGING_DIR)/
ifeq ($(BR2_ARCH_IS_64),y)
	#Work Around:TO FIX
	mkdir -p $(STAGING_DIR)/usr/lib/
	cp -dpf $(STAGING_DIR)/usr/lib64/libffi*.so* $(TARGET_DIR)/usr/lib/
	cp -dpf $(STAGING_DIR)/usr/lib64/libffi*.so* $(STAGING_DIR)/usr/lib/
	cp -dpf $(STAGING_DIR)/usr/lib64/libffi*.la $(STAGING_DIR)/usr/lib/
	#$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib64/libffi*.so*
else
	cp -dpf $(STAGING_DIR)/usr/lib/libffi*.so* $(TARGET_DIR)/usr/lib/
endif
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libffi*.so*

ifeq ($(BR2_ARCH_IS_64),y)
	#$(SED) "s,^libdir=.*,libdir\='$(STAGING_DIR)/usr/lib64',g" $(STAGING_DIR)/usr/lib64/libffi.la
	$(SED) "s,^libdir=.*,libdir\='$(STAGING_DIR)/usr/lib',g" $(STAGING_DIR)/usr/lib/libffi.la
else
	$(SED) "s,^libdir=.*,libdir\='$(STAGING_DIR)/usr/lib',g" $(STAGING_DIR)/usr/lib/libffi.la
endif


ifeq ($(wildcard $(LIBFFI_INSTALL_BINARY)),)
libffi: autoconf $(TARGET_DIR)/$(LIBFFI_BINARY)
else
libffi: autoconf libffi-binary
endif

libffi-clean:
	rm -f $(STAGING_DIR)/bin/libffi-config
	rm -f $(STAGING_DIR)/lib/libffi*
	rm -rf $(STAGING_DIR)/lib/pkgconfig
	rm -f $(TARGET_DIR)/usr/lib/libffi*
	-$(MAKE) -C $(LIBFFI_DIR) clean

libffi-dirclean:
	rm -rf $(LIBFFI_DIR)
libffi-binary-clean:
	rm -rf $(LIBFFI_INSTALL_BINARY)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_LIBFFI),y)
TARGETS+=libffi
endif
