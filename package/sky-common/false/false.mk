#############################################################
#
## false
#
##############################################################
FALSE_VERSION:=1.0
FALSE_SOURCE:=false-$(FALSE_VERSION).tar.gz
FALSE_SITE:=http://localhost
FALSE_DIR:=$(BUILD_DIR)/false-$(FALSE_VERSION)
FALSE_CAT:=$(ZCAT)
FALSE_BINARY:=src/false
FALSE_TARGET_BINARY:=bin/false

bumper-source: $(DL_DIR)/$(FALSE_SOURCE)

$(FALSE_DIR)/.unpacked: $(DL_DIR)/$(FALSE_SOURCE)
	$(FALSE_CAT) $(DL_DIR)/$(FALSE_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	touch $(FALSE_DIR)/.unpacked

$(FALSE_DIR)/.configured: $(FALSE_DIR)/.unpacked
	(cd $(FALSE_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
	)
	touch $(FALSE_DIR)/.configured

$(FALSE_DIR)/$(FALSE_BINARY): $(FALSE_DIR)/.configured
	$(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(FALSE_DIR)

$(TARGET_DIR)/$(FALSE_TARGET_BINARY): $(FALSE_DIR)/$(FALSE_BINARY)
	install -D $(FALSE_DIR)/$(FALSE_BINARY) $(TARGET_DIR)/$(FALSE_TARGET_BINARY)

FALSE: uclibc $(TARGET_DIR)/$(FALSE_TARGET_BINARY)

FALSE-clean:
	rm -f $(TARGET_DIR)/$(FALSE_TARGET_BINARY)
	-$(MAKE) -C $(FALSE_DIR) clean

FALSE-dirclean:
	rm -rf $(FALSE_DIR)
#############################################################
#
## Toplevel Makefile options
#
##############################################################
ifeq ($(BR2_PACKAGE_FALSE),y)
TARGETS+=FALSE
endif

