#############################################################
#
# httpsend
#
#############################################################
HTTPSEND_VERSION:=0.0
HTTPSEND_SOURCE:=httpsend-$(HTTPSEND_VERSION).tar.gz
HTTPSEND_SITE:=http://localhost
HTTPSEND_DIR:=$(BUILD_DIR)/httpsend-$(HTTPSEND_VERSION)
HTTPSEND_CAT:=$(ZCAT)
HTTPSEND_BINARY:=src/httpsend
HTTPSEND_TARGET_BINARY:=sbin/httpsend

httpsend-source: $(DL_DIR)/$(HTTPSEND_SOURCE)

$(HTTPSEND_DIR)/.unpacked: $(DL_DIR)/$(HTTPSEND_SOURCE)
	$(HTTPSEND_CAT) $(DL_DIR)/$(HTTPSEND_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(HTTPSEND_DIR) package/sky-common/httpsend/ \*.patch
	$(CONFIG_UPDATE) $(HTTPSEND_DIR)
	touch $(HTTPSEND_DIR)/.unpacked

$(HTTPSEND_DIR)/.configured: $(HTTPSEND_DIR)/.unpacked
	(cd $(HTTPSEND_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
	)
	touch $(HTTPSEND_DIR)/.configured

$(HTTPSEND_DIR)/$(HTTPSEND_BINARY): $(HTTPSEND_DIR)/.configured
	$(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(HTTPSEND_DIR)

$(TARGET_DIR)/$(HTTPSEND_TARGET_BINARY): $(HTTPSEND_DIR)/$(HTTPSEND_BINARY)
	install -D $(HTTPSEND_DIR)/$(HTTPSEND_BINARY) $(TARGET_DIR)/$(HTTPSEND_TARGET_BINARY)

HTTPSEND: uclibc $(TARGET_DIR)/$(HTTPSEND_TARGET_BINARY)

HTTPSEND-clean:
	rm -f $(TARGET_DIR)/$(HTTPSEND_TARGET_BINARY)
	-$(MAKE) -C $(HTTPSEND_DIR) clean

HTTPSEND-dirclean:
	rm -rf $(HTTPSEND_DIR)
#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_SKY_HTTPSEND),y)
TARGETS+=HTTPSEND
endif
