#############################################################
#
# systat
#
#############################################################
SYSSTAT_VERSION:=11.0.1
SYSSTAT_SOURCE:=sysstat-$(SYSSTAT_VERSION).tar.gz
SYSSTAT_SITE:=http://localhost
SYSSTAT_DIR:=$(BUILD_DIR)/sysstat-$(SYSSTAT_VERSION)
SYSSTAT_CAT:=$(ZCAT)
SYSSTAT_IOSTAT_BINARY:=iostat
SYSSTAT_IOSTAT_TARGET_BINARY:=bin/iostat
SYSSTAT_SAR_BINARY:=sar
SYSSTAT_SAR_TARGET_BINARY:=bin/sar

sysstat-source: $(DL_DIR)/$(SYSSTAR_SOURCE)

$(SYSSTAT_DIR)/.unpacked: $(DL_DIR)/$(SYSSTAT_SOURCE)
	$(SYSSTAT_CAT) $(DL_DIR)/$(SYSSTAT_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(SYSSTAT_DIR) package/sysstat/ sysstat-$(SYSSTAT_VERSION)\*.patch*
ifeq ($(BR2_TOOLCHAIN_EXTERNAL_PREFIX),"armv7-linux")
	$(CONFIG_UPDATE) $(SYSSTAT_DIR)
endif
	touch $(SYSSTAT_DIR)/.unpacked

$(SYSSTAT_DIR)/.configured: $(SYSSTAT_DIR)/.unpacked
	(cd $(SYSSTAT_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		./configure LDFLAGS=-L$(STAGING_DIR)/usr/lib \
		--disable-nls \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--disable-sensors \
	)
	touch $(SYSSTAT_DIR)/.configured

$(SYSSTAT_DIR)/$(SYSSTAT_BINARY): $(SYSSTAT_DIR)/.configured
	$(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(SYSSTAT_DIR)

$(TARGET_DIR)/$(SYSSTAT_TARGET_BINARY): $(SYSSTAT_DIR)/$(SYSSTAT_BINARY)
ifeq ($(BR2_PACKAGE_SYSSTAT),y)
	install -D $(SYSSTAT_DIR)/$(SYSSTAT_IOSTAT_BINARY) $(TARGET_DIR)/$(SYSSTAT_IOSTAT_TARGET_BINARY)
	install -D $(SYSSTAT_DIR)/$(SYSSTAT_SAR_BINARY) $(TARGET_DIR)/$(SYSSTAT_SAR_TARGET_BINARY)
endif

sysstat: $(TARGET_DIR)/$(SYSSTAT_TARGET_BINARY)

sysstat-clean:
	rm -f $(TARGET_DIR)/$(SYSSTAT_TARGET_BINARY)
	-$(MAKE) -C $(SYSSTAT_DIR) clean

sysstat-dirclean:
	rm -rf $(SYSSTAT_DIR)
#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_SYSSTAT),y)
TARGETS+=sysstat
endif

