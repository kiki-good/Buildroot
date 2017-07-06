#############################################################
#
# MOUNTMESHDATA
#
#############################################################
MOUNTMESHDATA_VERSION:=0.0.2
MOUNTMESHDATA_SITE:=http://localhost/
MOUNTMESHDATA_SOURCE:=$(SKY_DL_DIR)/mountMeshData-$(MOUNTMESHDATA_VERSION).tar.bz2
MOUNTMESHDATA_DIR:=$(BUILD_DIR)/mountMeshData-$(MOUNTMESHDATA_VERSION)
MOUNTMESHDATA_CAT:=$(BZCAT) 
MOUNTMESHDATA_BINARY:=mountMeshData
MOUNTMESHDATA_TARGET_BINARY:=/usr/bin/mountMeshData

$(DL_DIR)/$(MOUNTMESHDATA_SOURCE): 
	$(WGET) -P $(DL_DIR) $(MOUNTMESHDATA_SITE)/$(MOUNTMESHDATA_SOURCE)

mountMeshData-source: $(DL_DIR)/$(MOUNTMESHDATA_SOURCE)

mountMeshData-unpacked: $(MOUNTMESHDATA_DIR)/.unpacked
$(MOUNTMESHDATA_DIR)/.unpacked: $(DL_DIR)/$(MOUNTMESHDATA_SOURCE)
	$(MOUNTMESHDATA_CAT) $(DL_DIR)/$(MOUNTMESHDATA_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(MOUNTMESHDATA_DIR) package/sky/mountMeshData/ mountMeshData-$(MOUNTMESHDATA_VERSION)\*.patch
	touch $@

$(STAGING_DIR)/$(MOUNTMESHDATA_BINARY): $(MOUNTMESHDATA_DIR)/.unpacked
	$(MAKE) CC=$(TARGET_CC) -C $(MOUNTMESHDATA_DIR)
	#$(MAKE)	-C $(MOUNTMESHDATA_DIR)

$(STAGING_DIR)/$(MOUNTMESHDATA_TARGET_BINARY): $(STAGING_DIR)/$(MOUNTMESHDATA_BINARY)
	$(INSTALL) -D -m 0755 $(MOUNTMESHDATA_DIR)/mountMeshData $(TARGET_DIR)/usr/bin

mountMeshData: $(STAGING_DIR)/$(MOUNTMESHDATA_TARGET_BINARY)

mountMeshData-clean:
	$(MAKE) -C $(MOUNTMESHDATA_DIR) clean
	rm $(TARGET_DIR)/usr/bin/mountMeshData

mountMeshData-dirclean:
	rm -rf $(MOUNTMESHDATA_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_MOUNTMESHDATA),y)
TARGETS+=mountMeshData
endif
