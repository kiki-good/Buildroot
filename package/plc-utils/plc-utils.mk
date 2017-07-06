#############################################################
#
# plc-utils
#
#############################################################
PLC-UTILS_VERSION:=0.00
PLC-UTILS_SOURCE:=plc-utils-$(PLC-UTILS_VERSION).tar.bz2
PLC-UTILS_DIR:=$(BUILD_DIR)/plc-utils-$(PLC-UTILS_VERSION)
PLC-UTILS_CAT:=$(BZCAT) 
PLC-UTILS_BINARY:=plc-utils
PLC-UTILS_TARGET_BINARY:=sbin/plc-utils

plc-utils-unpacked: $(PLC-UTILS_DIR)/.unpacked
$(PLC-UTILS_DIR)/.unpacked: $(DL_DIR)/$(PLC-UTILS_SOURCE)
	$(PLC-UTILS_CAT) $(DL_DIR)/$(PLC-UTILS_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(PLC-UTILS_DIR) package/plc-utils/ plc-utils-$(PLC-UTILS_VERSION)\*.patch
	touch $@

$(STAGING_DIR)/$(PLC-UTILS_BINARY): $(PLC-UTILS_DIR)/.unpacked
	$(MAKE) EXTRA_CFLAGS="-D__UCLIBC__" CC=$(TARGET_CC) -C $(PLC-UTILS_DIR)

$(STAGING_DIR)/$(PLC-UTILS_TARGET_BINARY): $(STAGING_DIR)/$(PLC-UTILS_BINARY)
ifneq ($(BR2_SKY_BUILD_TYPE),"debug")
	$(MAKE) ROOTFS=$(STAGING_DIR) CC=$(TARGET_CC) -C $(PLC-UTILS_DIR) install
	mkdir -p $(TARGET_DIR)/usr/local/bin/
	cp -rf $(STAGING_DIR)/usr/local/bin/efsu $(TARGET_DIR)/usr/local/bin/
	cp -rf $(STAGING_DIR)/usr/local/bin/modpib $(TARGET_DIR)/usr/local/bin/
	cp -rf $(STAGING_DIR)/usr/local/bin/plcstat $(TARGET_DIR)/usr/local/bin/
	cp -rf $(STAGING_DIR)/usr/local/bin/plctool $(TARGET_DIR)/usr/local/bin/
	cp -rf $(STAGING_DIR)/usr/local/bin/plclist $(TARGET_DIR)/usr/local/bin/
	cp -rf $(STAGING_DIR)/usr/local/bin/plchost $(TARGET_DIR)/usr/local/bin/
	cp -rf $(STAGING_DIR)/usr/local/bin/plcrate $(TARGET_DIR)/usr/local/bin/
	cp -rf $(STAGING_DIR)/usr/local/bin/setpib $(TARGET_DIR)/usr/local/bin/
	cp -rf $(STAGING_DIR)/usr/local/bin/plcrule $(TARGET_DIR)/usr/local/bin/
	cp -rf $(STAGING_DIR)/usr/local/bin/plctone $(TARGET_DIR)/usr/local/bin/
	cp -rf $(STAGING_DIR)/usr/local/bin/getpib $(TARGET_DIR)/usr/local/bin/
endif
ifeq ($(BR2_SKY_BUILD_TYPE),"debug")
	$(MAKE) ROOTFS=$(TARGET_DIR) CC=$(TARGET_CC) -C $(PLC-UTILS_DIR) install
endif

plc-utils: $(STAGING_DIR)/$(PLC-UTILS_TARGET_BINARY)

plc-utils-clean:
ifeq ($(BR2_SKY_BUILD_TYPE),"debug")
	$(MAKE) ROOTFS=$(TARGET_DIR) CC=$(TARGET_CC) -C $(PLC-UTILS_DIR) uninstall
endif
ifneq ($(BR2_SKY_BUILD_TYPE),"debug")
	$(MAKE) ROOTFS=$(STAGING_DIR) CC=$(TARGET_CC) -C $(PLC-UTILS_DIR) uninstall
endif
plc-utils-dirclean:
	rm -rf $(PLC-UTILS_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_PLC_UTILS),y)
TARGETS+=plc-utils
endif
