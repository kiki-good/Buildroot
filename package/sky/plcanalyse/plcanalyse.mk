#############################################################
#
# PLCANALYSE
#
#############################################################
PLCANALYSE_VERSION:=0.0.1
PLCANALYSE_SITE:=http://localhost/
PLCANALYSE_SOURCE:=$(SKY_DL_DIR)/plcanalyse-$(PLCANALYSE_VERSION).tar.bz2
PLCANALYSE_DIR:=$(BUILD_DIR)/plcanalyse-$(PLCANALYSE_VERSION)
PLCANALYSE_CAT:=$(BZCAT) 
PLCANALYSE_BINARY:=plcanalyse
PLCANALYSE_TARGET_BINARY:=/usr/bin/plcanalyse


$(DL_DIR)/$(PLCANALYSE_SOURCE): 
	$(WGET) -P $(DL_DIR) $(PLCANALYSE_SITE)/$(PLCANALYSE_SOURCE)

plcanalyse-source: $(DL_DIR)/$(PLCANALYSE_SOURCE)

$(PLCANALYSE_DIR)/.unpacked: $(DL_DIR)/$(PLCANALYSE_SOURCE)
	$(PLCANALYSE_CAT) $(DL_DIR)/$(PLCANALYSE_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(PLCANALYSE_DIR) package/sky/plcanalyse/ plcanalyse-$(PLCANALYSE_VERSION)\*.patch
	touch $@


plcanalyse-unpacked: $(PLCANALYSE_DIR)/.unpacked 
	
$(STAGING_DIR)/$(PLCANALYSE_BINARY): plcanalyse-unpacked
	$(MAKE) CC=$(TARGET_CC) -C $(PLCANALYSE_DIR)

$(STAGING_DIR)/$(PLCANALYSE_TARGET_BINARY): $(STAGING_DIR)/$(PLCANALYSE_BINARY)
	$(INSTALL) -D -m 0755 $(PLCANALYSE_DIR)/plc/plcanalyse $(TARGET_DIR)/usr/local/bin/plcanalyse

plcanalyse: $(STAGING_DIR)/$(PLCANALYSE_TARGET_BINARY)

plcanalyse-clean:
	$(MAKE) PLC-UTILS_DIR=$(PLCANALYSE_PLC_UTILS_DIR) $(PLCANALYSE_DIR) clean
	rm $(TARGET_DIR)/usr/local/bin/plcanalyse

plcanalyse-dirclean:
	rm -rf $(PLCANALYSE_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_PLCANALYSE_DATA),y)
TARGETS+=plcanalyse
endif
