#############################################################
#
# OTPMESHDATA
#
#############################################################
OTPMESHDATA_VERSION:=0.1.2
OTPMESHDATA_SITE:=http://localhost/
OTPMESHDATA_SOURCE:=$(SKY_DL_DIR)/otpMeshData-$(OTPMESHDATA_VERSION).tar.bz2
OTPMESHDATA_DIR:=$(BUILD_DIR)/otpMeshData-$(OTPMESHDATA_VERSION)
OTPMESHDATA_CAT:=$(BZCAT) 
OTPMESHDATA_BINARY:=otpMeshData
OTPMESHDATA_TARGET_BINARY:=/usr/bin/otpMeshData

ifneq (,$(filter $(BR2_BOARD_NAME),"bskyb-mr412" "bskyb-gemini419"))
COEX_SUPPORT_ENABLE=n
else
COEX_SUPPORT_ENABLE=y
endif

$(DL_DIR)/$(OTPMESHDATA_SOURCE): 
	$(WGET) -P $(DL_DIR) $(OTPMESHDATA_SITE)/$(OTPMESHDATA_SOURCE)

otpMeshData-source: $(DL_DIR)/$(OTPMESHDATA_SOURCE)

otpMeshData-unpacked: $(OTPMESHDATA_DIR)/.unpacked
$(OTPMESHDATA_DIR)/.unpacked: $(DL_DIR)/$(OTPMESHDATA_SOURCE)
	$(OTPMESHDATA_CAT) $(DL_DIR)/$(OTPMESHDATA_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(OTPMESHDATA_DIR) package/sky/otpMeshData/ otpMeshData-$(OTPMESHDATA_VERSION)\*.patch
	touch $@

$(STAGING_DIR)/$(OTPMESHDATA_BINARY): $(OTPMESHDATA_DIR)/.unpacked
	$(MAKE) CC=$(TARGET_CC) -C $(OTPMESHDATA_DIR) COEX_SUPPORT_ENABLE=$(COEX_SUPPORT_ENABLE)
	#$(MAKE)	-C $(OTPMESHDATA_DIR)

$(STAGING_DIR)/$(OTPMESHDATA_TARGET_BINARY): $(STAGING_DIR)/$(OTPMESHDATA_BINARY)
	$(INSTALL) -D -m 0755 $(OTPMESHDATA_DIR)/otpMeshData $(TARGET_DIR)/usr/bin

otpMeshData: $(STAGING_DIR)/$(OTPMESHDATA_TARGET_BINARY)

otpMeshData-clean:
	$(MAKE) -C $(OTPMESHDATA_DIR) clean
	rm $(TARGET_DIR)/usr/bin/otpMeshData

otpMeshData-dirclean:
	rm -rf $(OTPMESHDATA_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_OTPMESHDATA),y)
TARGETS+=otpMeshData
endif
