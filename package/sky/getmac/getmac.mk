#############################################################
#
# GETMAC
#
#############################################################
GETMAC_VERSION:=0.00
GETMAC_SITE:=http://localhost/
GETMAC_SOURCE:=$(SKY_DL_DIR)/GetMac-$(GETMAC_VERSION).tar.bz2
GETMAC_DIR:=$(BUILD_DIR)/GetMac-$(GETMAC_VERSION)
GETMAC_CAT:=$(BZCAT) 
GETMAC_BINARY:=GetMac
GETMAC_TARGET_BINARY:=/usr/bin/GetMac

$(DL_DIR)/$(GETMAC_SOURCE): 
	$(WGET) -P $(DL_DIR) $(GETMAC_SITE)/$(GETMAC_SOURCE)

getmac-source: $(DL_DIR)/$(GETMAC_SOURCE)

getmac-unpacked: $(GETMAC_DIR)/.unpacked
$(GETMAC_DIR)/.unpacked: $(DL_DIR)/$(GETMAC_SOURCE)
	$(GETMAC_CAT) $(DL_DIR)/$(GETMAC_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(GETMAC_DIR) package/sky/getmac/ GetMac-$(GETMAC_VERSION)\*.patch
	touch $@

$(STAGING_DIR)/$(GETMAC_BINARY): $(GETMAC_DIR)/.unpacked
	$(MAKE) CC=$(TARGET_CC) -C $(GETMAC_DIR)
	#$(MAKE)	-C $(GETMAC_DIR)

$(STAGING_DIR)/$(GETMAC_TARGET_BINARY): $(STAGING_DIR)/$(GETMAC_BINARY)
	$(INSTALL) -D -m 0755 $(GETMAC_DIR)/GetMac $(TARGET_DIR)/usr/bin

getmac: $(STAGING_DIR)/$(GETMAC_TARGET_BINARY)

getmac-clean:
	$(MAKE) -C $(GETMAC_DIR) clean
	rm $(TARGET_DIR)/usr/bin/GetMac

getmac-dirclean:
	rm -rf $(GETMAC_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_GETMAC),y)
TARGETS+=getmac
endif
