#############################################################
#
# RSSI
#
#############################################################
RSSI_VERSION:=0.2.4
RSSI_SITE:=http://localhost/
RSSI_SOURCE:=$(SKY_DL_DIR)/skyRssiData-$(RSSI_VERSION).tar.bz2
RSSI_DIR:=$(BUILD_DIR)/skyRssiData-$(RSSI_VERSION)
RSSI_CAT:=$(BZCAT) 
RSSI_BINARY:=skyRssiData
RSSI_TARGET_BINARY:=/usr/bin/skyRssiData

RSSI_PLC_UTILS_VERSION:=0.00
RSSI_PLC_UTILS_SOURCE:=plc-utils-$(RSSI_PLC_UTILS_VERSION).tar.bz2
RSSI_PLC_UTILS_DIR:=$(RSSI_DIR)/plc-utils-$(RSSI_PLC_UTILS_VERSION)
RSSI_PLC_UTILS_CAT:=$(BZCAT)


$(DL_DIR)/$(RSSI_SOURCE): 
	$(WGET) -P $(DL_DIR) $(RSSI_SITE)/$(RSSI_SOURCE)

skyRssiData-source: $(DL_DIR)/$(RSSI_SOURCE)

$(RSSI_DIR)/.unpacked: $(DL_DIR)/$(RSSI_SOURCE)
	$(RSSI_CAT) $(DL_DIR)/$(RSSI_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(RSSI_DIR) package/sky/skyRssiData/ skyRssiData-$(RSSI_VERSION)\*.patch
	touch $@

$(RSSI_PLC_UTILS_DIR)/.unpacked: $(DL_DIR)/$(RSSI_PLC_UTILS_SOURCE)
	$(RSSI_PLC_UTILS_CAT) $(DL_DIR)/$(RSSI_PLC_UTILS_SOURCE) | tar -C $(RSSI_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(RSSI_PLC_UTILS_DIR) package/plc-utils/ plc-utils-$(RSSI_PLC_UTILS_VERSION)\*.patch
	toolchain/patch-kernel.sh $(RSSI_PLC_UTILS_DIR)  $(RSSI_DIR) plc-utils-$(RSSI_PLC_UTILS_VERSION)\*.patch
	touch $@

skyRssiData-unpacked: $(RSSI_DIR)/.unpacked $(RSSI_PLC_UTILS_DIR)/.unpacked
	
$(STAGING_DIR)/$(RSSI_BINARY): skyRssiData-unpacked
	$(MAKE) EXTRA_CFLAGS="-D__UCLIBC__" CC=$(TARGET_CC) -C $(RSSI_PLC_UTILS_DIR)
	$(MAKE) CC=$(TARGET_CC) PLC-UTILS_DIR=$(RSSI_PLC_UTILS_DIR) -C $(RSSI_DIR)

$(STAGING_DIR)/$(RSSI_TARGET_BINARY): $(STAGING_DIR)/$(RSSI_BINARY)
	$(INSTALL) -D -m 0755 $(RSSI_DIR)/skyRssiData $(TARGET_DIR)/usr/bin

skyRssiData: $(STAGING_DIR)/$(RSSI_TARGET_BINARY)

skyRssiData-clean:
	$(MAKE) PLC-UTILS_DIR=$(RSSI_PLC_UTILS_DIR) $(RSSI_DIR) clean
	rm $(TARGET_DIR)/usr/bin/skyRssiData

skyRssiData-dirclean:
	rm -rf $(RSSI_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_SKY_RSSI_DATA),y)
TARGETS+=skyRssiData
endif
