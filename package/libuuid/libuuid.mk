#############################################################
#
# LIBUUID
#
#############################################################
LIBUUID_VERSION:=1.0.3
LIBUUID_SOURCE:=libuuid-$(LIBUUID_VERSION).tar.gz
LIBUUID_DIR:=$(BUILD_DIR)/libuuid-$(LIBUUID_VERSION)
LIBUUID_CAT:=$(ZCAT) 
LIBUUID_BINARY:=libuuid.so
LIBUUID_TARGET_BINARY:=lib/libuuid.so
LIBUUID_DIR=$(BUILD_DIR)/libuuid-$(LIBUUID_VERSION)
LIBUUID_BINARY_SOURCE:=libuuid-$(LIBUUID_VERSION)-binary.tar.bz2
LIBUUID_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
LIBUUID_BINARY_DIR:=$(LIBUUID_BOARD_PATH)/binaries
LIBUUID_INSTALL_BINARY:=$(LIBUUID_BINARY_DIR)/$(LIBUUID_BINARY_SOURCE)
LIBUUID_TEMP_DIR:=$(LIBUUID_BINARY_DIR)/libuuid_tmp

$(LIBUUID_DIR)/.unpacked: 
	$(LIBUUID_CAT) $(DL_DIR)/$(LIBUUID_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(LIBUUID_DIR) package/libuuid/ libuuid-$(LIBUUID_VERSION)-\*.patch
	touch $@

$(LIBUUID_DIR)/.configured: $(LIBUUID_DIR)/.unpacked
	(cd $(LIBUUID_DIR); rm -rf config.cache; \
                $(TARGET_CONFIGURE_OPTS) \
                $(TARGET_CONFIGURE_ARGS) \
                ./configure \
                --target=$(GNU_TARGET_NAME) \
                --host=$(GNU_TARGET_NAME) \
                --build=$(GNU_HOST_NAME) \
                --with-gnu-ld \
                prefix=/ \
                --exec-prefix=/ \
                CFLAG="-I$(STAGING_DIR)/usr/include" \
		LDFLAGS="$(TARGET_LDFLAGS) -L$(TARGET_DIR)/lib" \
        )
	touch $@

$(STAGING_DIR)/$(LIBUUID_BINARY): $(LIBUUID_DIR)/.configured
	$(MAKE)	-C $(LIBUUID_DIR)

$(STAGING_DIR)/$(LIBUUID_TARGET_BINARY): $(STAGING_DIR)/$(LIBUUID_BINARY)
	mkdir -p $(PWD)/$(LIBUUID_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(LIBUUID_TEMP_DIR) -C $(LIBUUID_DIR) install
	tar cjvf $(LIBUUID_BINARY_DIR)/$(LIBUUID_BINARY_SOURCE) -C $(LIBUUID_TEMP_DIR) .
	rm -rf $(PWD)/$(LIBUUID_TEMP_DIR)
	$(MAKE) DESTDIR=$(TARGET_DIR) -C $(LIBUUID_DIR) install
	$(MAKE) DESTDIR=$(STAGING_DIR) -C $(LIBUUID_DIR) install

libuuid-binary:
	tar -xjvf $(LIBUUID_BINARY_DIR)/$(LIBUUID_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(LIBUUID_BINARY_DIR)/$(LIBUUID_BINARY_SOURCE) -C $(TARGET_DIR)/

ifeq ($(wildcard $(LIBUUID_INSTALL_BINARY)),)
libuuid: pkgconfig $(STAGING_DIR)/$(LIBUUID_TARGET_BINARY)
else
libuuid: libuuid-binary
endif


libuuid-clean:
	-$(MAKE) DESTDIR=$(STAGING_DIR) -C $(LIBUUID_DIR) uninstall
	-$(MAKE) DESTDIR=$(TARGET_DIR) -C $(LIBUUID_DIR) uninstall
	-$(MAKE) -C $(LIBUUID_DIR) clean

libuuid-dirclean:
	rm -rf $(LIBUUID_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_LIBUUID),y)
TARGETS+=libuuid
endif
