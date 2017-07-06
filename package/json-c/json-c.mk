#############################################################
#
# JSON_C
#
#############################################################
JSON_C_VERSION:=0.10
JSON_C_SITE:=https://github.com/json-c/json-c/downloads
JSON_C_SOURCE:=json-c-$(JSON_C_VERSION).tar.gz
JSON_C_DIR:=$(BUILD_DIR)/json-c-$(JSON_C_VERSION)
JSON_C_CAT:=$(ZCAT) 
JSON_C_BINARY:=json
JSON_C_TARGET_BINARY:=usr/bin/json

$(DL_DIR)/$(JSON_C_SOURCE): 
	$(WGET) -P $(DL_DIR) $(JSON_C_SITE)/$(JSON_C_SOURCE)

json-c-source: $(DL_DIR)/$(JSON_C_SOURCE)

json-c-unpacked: $(JSON_C_DIR)/.unpacked
$(JSON_C_DIR)/.unpacked: $(DL_DIR)/$(JSON_C_SOURCE)
	$(JSON_C_CAT) $(DL_DIR)/$(JSON_C_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
ifeq ($(BR2_BOARD_NAME),"bskyb-gemini419")
	toolchain/patch-kernel.sh $(JSON_C_DIR) package/json-c/ \*.patch
else
	toolchain/patch-kernel.sh $(JSON_C_DIR) package/json-c/ json-c-$(JSON_C_VERSION)-all\*.patch
endif
	touch $@

$(JSON_C_DIR)/.configured: $(JSON_C_DIR)/.unpacked
	(cd $(JSON_C_DIR); rm -rf config.cache; \
                $(TARGET_CONFIGURE_OPTS) \
                $(TARGET_CONFIGURE_ARGS) \
                ./configure \
                --target=$(GNU_TARGET_NAME) \
                --host=$(GNU_TARGET_NAME) \
                --build=$(GNU_HOST_NAME) \
                --prefix=/usr \
                --sysconfdir=/etc \
        )
	touch $@

$(STAGING_DIR)/$(JSON_C_BINARY): $(JSON_C_DIR)/.configured
	$(MAKE) -C $(JSON_C_DIR)

$(STAGING_DIR)/$(JSON_C_TARGET_BINARY): $(STAGING_DIR)/$(JSON_C_BINARY)
	$(MAKE) DESTDIR=$(TARGET_DIR) -C $(JSON_C_DIR) install
	$(MAKE) DESTDIR=$(STAGING_DIR) -C $(JSON_C_DIR) install

json-c: pkgconfig json-c $(STAGING_DIR)/$(JSON_C_TARGET_BINARY)

json-c-clean:
	-$(MAKE) DESTDIR=$(TARGET_DIR) -C $(JSON_C_DIR) uninstall
	-$(MAKE) DESTDIR=$(STAGING_DIR) -C $(JSON_C_DIR) uninstall
	-$(MAKE) -C $(JSON_C_DIR) clean

json-c-dirclean:
	rm -rf $(JSON_C_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_JSON_C),y)
TARGETS+=json-c
endif
