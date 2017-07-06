#############################################################
#
# libatasmart
#
#############################################################
ifeq ($(BR2_ARCH_IS_64),y)
LIBATASMART_VERSION:=0.19
else
LIBATASMART_VERSION:=0.19
endif

LIBATASMART_SOURCE:=libatasmart-$(LIBATASMART_VERSION).tar.gz
LIBATASMART_DIR:=$(BUILD_DIR)/libatasmart-$(LIBATASMART_VERSION)
LIBATASMART_CAT:=$(ZCAT)
LIBATASMART_LIBS_DIR=.libs
LIBATASMART_BINARY:=libatasmart.so
LIBATASMART_TARGET:=usr/lib/libatasmart.so
LIBATASMART_DEPENDENCIES:= libudev
libatasmart-source: $(DL_DIR)/$(LIBATASMART_SOURCE)

$(LIBATASMART_DIR)/.unpacked: $(DL_DIR)/$(LIBATASMART_SOURCE)
	$(ZCAT) $(DL_DIR)/$(LIBATASMART_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
ifeq ($(BR2_ARCH_IS_64),y)
	toolchain/patch-kernel.sh $(LIBATASMART_DIR) package/libatasmart/64bitPatch libatasmart-$(LIBATASMART_VERSION)-\*.patch
else
	toolchain/patch-kernel.sh $(LIBATASMART_DIR) package/libatasmart libatasmart-$(LIBATASMART_VERSION)-\*.patch
endif
	touch $@

$(LIBATASMART_DIR)/.configured: $(LIBATASMART_DIR)/.unpacked
	(cd $(LIBATASMART_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		LDFLAGS=-L"$(STAGING_DIR)/usr/lib/" \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--prefix=/usr \
		--disable-static \
	)
	touch $(LIBATASMART_DIR)/.configured
	touch $@

$(LIBATASMART_DIR)/$(LIBATASMART_BINARY): $(LIBATASMART_DIR)/.configured
	$(MAKE) -C $(LIBATASMART_DIR)
	touch -c $@

$(TARGET_DIR)/$(LIBATASMART_TARGET): $(LIBATASMART_DIR)/$(LIBATASMART_BINARY)
	cp $(LIBATASMART_DIR)/$(LIBATASMART_LIBS_DIR)/$(LIBATASMART_BINARY) $(TARGET_DIR)/usr/lib/
	cp $(LIBATASMART_DIR)/$(LIBATASMART_LIBS_DIR)/$(LIBATASMART_BINARY) $(STAGING_DIR)/usr/lib/
	cp $(LIBATASMART_DIR)/$(LIBATASMART_LIBS_DIR)/$(LIBATASMART_BINARY).4 $(TARGET_DIR)/usr/lib/
	cp $(LIBATASMART_DIR)/$(LIBATASMART_LIBS_DIR)/$(LIBATASMART_BINARY).4 $(STAGING_DIR)/usr/lib/
	$(INSTALL) -D $(LIBATASMART_DIR)/atasmart.h $(STAGING_DIR)/usr/include/atasmart.h

libatasmart: udev $(TARGET_DIR)/$(LIBATASMART_TARGET)

libatasmart-clean:
	$(MAKE) DESTDIR=$(TARGET_DIR) -C $(LIBATASMART_DIR) uninstall
	-$(MAKE) -C $(LIBATASMART_DIR) clean

libatasmart-dirclean:
	rm -rf $(LIBATASMART_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_LIBATASMART),y)
TARGETS+=libatasmart
endif
