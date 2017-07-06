#############################################################
#
# writefile
#
#############################################################
WRITEFILE_VERSION:=1.1
WRITEFILE_SOURCE:=writefile-$(WRITEFILE_VERSION).tar.gz
WRITEFILE_SITE:=http://localhost
WRITEFILE_DIR:=$(BUILD_DIR)/writefile-$(WRITEFILE_VERSION)
WRITEFILE_BINARY_SOURCE:=writefile-$(WRITEFILE_VERSION).tar.bz2
WRITEFILE_CAT:=$(ZCAT)
WRITEFILE_BINARY:=src/writefile
WRITEFILE_TARGET_BINARY:=bin/writefile
WRITEFILE_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
WRITEFILE_BINARY_DIR:=$(WRITEFILE_BOARD_PATH)/binaries
WRITEFILE_INSTALL_BINARY:=$(WRITEFILE_BINARY_DIR)/$(WRITEFILE_BINARY_SOURCE)
WRITEFILE_TEMP_DIR:=$(WRITEFILE_BINARY_DIR)/writefile_tmp


writefile-source: $(DL_DIR)/$(WRITEFILE_SOURCE)

$(WRITEFILE_DIR)/.unpacked: $(DL_DIR)/$(WRITEFILE_SOURCE)
	$(WRITEFILE_CAT) $(DL_DIR)/$(WRITEFILE_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(WRITEFILE_DIR) package/sky-common/writefile/ \*.patch
	$(CONFIG_UPDATE) $(WRITEFILE_DIR)
	touch $(WRITEFILE_DIR)/.unpacked

$(WRITEFILE_DIR)/.configured: $(WRITEFILE_DIR)/.unpacked
	(cd $(WRITEFILE_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
	)
	touch $(WRITEFILE_DIR)/.configured

$(WRITEFILE_DIR)/$(WRITEFILE_BINARY): $(WRITEFILE_DIR)/.configured
	$(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(WRITEFILE_DIR)

$(TARGET_DIR)/$(WRITEFILE_TARGET_BINARY): $(WRITEFILE_DIR)/$(WRITEFILE_BINARY)
	mkdir -p $(WRITEFILE_TEMP_DIR)/bin
	install -D $(WRITEFILE_DIR)/$(WRITEFILE_BINARY) $(TARGET_DIR)/$(WRITEFILE_TARGET_BINARY)
	install -D $(WRITEFILE_DIR)/$(WRITEFILE_BINARY) $(WRITEFILE_TEMP_DIR)/$(WRITEFILE_TARGET_BINARY)
	tar cjvf $(WRITEFILE_BINARY_DIR)/$(WRITEFILE_BINARY_SOURCE) -C $(WRITEFILE_TEMP_DIR) .
	rm -rf $(WRITEFILE_TEMP_DIR)
	touch $@

writefile-binary:
	tar xjvf $(WRITEFILE_BINARY_DIR)/$(WRITEFILE_BINARY_SOURCE) -C $(TARGET_DIR)/

ifeq ($(wildcard $(WRITEFILE_INSTALL_BINARY)),)
WRITEFILE: $(TARGET_DIR)/$(WRITEFILE_TARGET_BINARY)
else
WRITEFILE: writefile-binary
endif

WRITEFILE-clean:
	rm -f $(TARGET_DIR)/$(WRITEFILE_TARGET_BINARY)
	-$(MAKE) -C $(WRITEFILE_DIR) clean

WRITEFILE-dirclean:
	rm -rf $(WRITEFILE_DIR)
#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_SKY_WRITEFILE),y)
TARGETS+=WRITEFILE
endif
