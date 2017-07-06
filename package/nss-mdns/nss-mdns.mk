#############################################################
#
# NSS_MDNS
#
#############################################################
NSS_MDNS_VERSION:=0.10
NSS_MDNS_SITE:=http://localhost/
NSS_MDNS_SOURCE:=nss-mdns-$(NSS_MDNS_VERSION).tar.gz
NSS_MDNS_DIR:=$(BUILD_DIR)/nss-mdns-$(NSS_MDNS_VERSION)
NSS_MDNS_CAT:=$(ZCAT) 
NSS_MDNS_LIBRARY:=nss_mdns4
NSS_MDNS_TARGET_LIBRARY:=nss_mdns4
NSS_MDNS_BINARY_SOURCE:=nssmdns-$(NSS_MDNS_VERSION)-binary.tar.bz2
NSS_MDNS_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
NSS_MDNS_BINARY_DIR:=$(NSS_MDNS_BOARD_PATH)/binaries
NSS_MDNS_INSTALL_BINARY:=$(NSS_MDNS_BINARY_DIR)/$(NSS_MDNS_BINARY_SOURCE)
NSS_MDNS_TEMP_DIR:=$(NSS_MDNS_BINARY_DIR)/nss-mdns_tmp


$(NSS_MDNS_DIR)/.unpacked:
	$(NSS_MDNS_CAT) $(DL_DIR)/$(NSS_MDNS_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(NSS_MDNS_DIR) package/nss-mdns/ nss-mdns-$(NSS_MDNS_VERSION)-\*.patch
	touch $@

$(NSS_MDNS_DIR)/.configured: $(NSS_MDNS_DIR)/.unpacked
	(cd $(NSS_MDNS_DIR); rm -rf config.cache; \
                $(TARGET_CONFIGURE_OPTS) \
                $(TARGET_CONFIGURE_ARGS) \
                ./configure \
                --target=$(GNU_TARGET_NAME) \
                --host=$(GNU_TARGET_NAME) \
                --build=$(GNU_HOST_NAME) \
                --with-gnu-ld \
		--enable-legacy \
        )
	touch $@

$(NSS_MDNS_DIR)/$(NSS_MDNS_LIBRARY): $(NSS_MDNS_DIR)/.configured
	$(MAKE)	-C $(NSS_MDNS_DIR)

$(STAGING_DIR)/$(NSS_MDNS_TARGET_LIBRARY): $(NSS_MDNS_DIR)/$(NSS_MDNS_LIBRARY)
	$(MAKE) DESTDIR=$(TARGET_DIR) -C $(NSS_MDNS_DIR) install
	rm -rf $(TARGET_DIR)/lib/libnss_mdns6_minimal.so.2
	rm -rf $(TARGET_DIR)/lib/libnss_mdns6.so.2
	rm -rf $(TARGET_DIR)/lib/libnss_mdns_minimal.so.2
	rm -rf $(TARGET_DIR)/lib/libnss_mdns.so.2
	$(MAKE) DESTDIR=$(STAGING_DIR) -C $(NSS_MDNS_DIR) install
	mkdir -p $(NSS_MDNS_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(NSS_MDNS_TEMP_DIR) -C $(NSS_MDNS_DIR) install
	rm -rf $(NSS_MDNS_TEMP_DIR)/lib/libnss_mdns6_minimal.so.2
	rm -rf $(NSS_MDNS_TEMP_DIR)/lib/libnss_mdns6.so.2
	rm -rf $(NSS_MDNS_TEMP_DIR)/lib/libnss_mdns_minimal.so.2
	rm -rf $(NSS_MDNS_TEMP_DIR)/lib/libnss_mdns.so.2
	tar cjvf $(NSS_MDNS_BINARY_DIR)/$(NSS_MDNS_BINARY_SOURCE) -C $(NSS_MDNS_TEMP_DIR) .
	rm -rf $(NSS_MDNS_TEMP_DIR)
	
nss-mdns-binary:
	tar -xjvf $(NSS_MDNS_BINARY_DIR)/$(NSS_MDNS_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(NSS_MDNS_BINARY_DIR)/$(NSS_MDNS_BINARY_SOURCE) -C $(TARGET_DIR)/
	
ifeq ($(wildcard $(NSS_MDNS_INSTALL_BINARY)),)
nss-mdns: $(STAGING_DIR)/$(NSS_MDNS_TARGET_LIBRARY)
else
nss-mdns: nss-mdns-binary
endif



nss-mdns-clean:
	-$(MAKE) DESTDIR=$(STAGING_DIR) -C $(NSS_MDNS_DIR) uninstall
	-$(MAKE) DESTDIR=$(TARGET_DIR) -C $(NSS_MDNS_DIR) uninstall
	-$(MAKE) -C $(NSS_MDNS_DIR) clean

nss-mdns-dirclean:
	rm -rf $(NSS_MDNS_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_NSS_MDNS),y)
TARGETS+=nss-mdns
endif
