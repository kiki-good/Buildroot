#############################################################
#
# bumper
#
#############################################################
BUMPER_VERSION:=0.0
BUMPER_SOURCE:=bumper-$(BUMPER_VERSION).tar.gz
BUMPER_SITE:=http://localhost
BUMPER_DIR:=$(BUILD_DIR)/bumper-$(BUMPER_VERSION)
BUMPER_CAT:=$(ZCAT)
BUMPER_BINARY:=src/bumper
BUMPER_TARGET_BINARY:=sbin/bumper

bumper-source: $(DL_DIR)/$(BUMPER_SOURCE)

$(BUMPER_DIR)/.unpacked: $(DL_DIR)/$(BUMPER_SOURCE)
	$(BUMPER_CAT) $(DL_DIR)/$(BUMPER_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(BUMPER_DIR) package/sky-common/bumper/ bumper-$(BUMPER_VERSION)\*.patch*
ifeq ($(BR2_TOOLCHAIN_EXTERNAL_PREFIX),"armv7-linux")
	$(CONFIG_UPDATE) $(BUMPER_DIR)
endif
	touch $(BUMPER_DIR)/.unpacked

$(BUMPER_DIR)/.configured: $(BUMPER_DIR)/.unpacked
	(cd $(BUMPER_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
	)
	touch $(BUMPER_DIR)/.configured

$(BUMPER_DIR)/$(BUMPER_BINARY): $(BUMPER_DIR)/.configured
	$(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(BUMPER_DIR)

$(TARGET_DIR)/$(BUMPER_TARGET_BINARY): $(BUMPER_DIR)/$(BUMPER_BINARY)
	install -D $(BUMPER_DIR)/$(BUMPER_BINARY) $(TARGET_DIR)/$(BUMPER_TARGET_BINARY)

BUMPER: uclibc $(TARGET_DIR)/$(BUMPER_TARGET_BINARY)

BUMPER-clean:
	rm -f $(TARGET_DIR)/$(BUMPER_TARGET_BINARY)
	-$(MAKE) -C $(BUMPER_DIR) clean

BUMPER-dirclean:
	rm -rf $(BUMPER_DIR)
#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_BUMPER),y)
TARGETS+=BUMPER
endif
