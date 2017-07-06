#############################################################
#
# CMDLINEMESH
#
#############################################################
CMDLINEMESH_VERSION:=0.0.1
CMDLINEMESH_SITE:=http://localhost/
CMDLINEMESH_SOURCE:=$(SKY_DL_DIR)/cmdLineMesh-$(CMDLINEMESH_VERSION).tar.bz2
CMDLINEMESH_DIR:=$(BUILD_DIR)/cmdLineMesh-$(CMDLINEMESH_VERSION)
CMDLINEMESH_CAT:=$(BZCAT) 
CMDLINEMESH_BINARY:=cmdLineMesh
CMDLINEMESH_TARGET_BINARY:=/usr/bin/cmdLineMesh

$(DL_DIR)/$(CMDLINEMESH_SOURCE): 
	$(WGET) -P $(DL_DIR) $(CMDLINEMESH_SITE)/$(CMDLINEMESH_SOURCE)

cmdLineMesh-source: $(DL_DIR)/$(CMDLINEMESH_SOURCE)

cmdLineMesh-unpacked: $(CMDLINEMESH_DIR)/.unpacked
$(CMDLINEMESH_DIR)/.unpacked: $(DL_DIR)/$(CMDLINEMESH_SOURCE)
	$(CMDLINEMESH_CAT) $(DL_DIR)/$(CMDLINEMESH_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(CMDLINEMESH_DIR) package/sky/cmdLineMesh/ cmdLineMesh-$(CMDLINEMESH_VERSION)\*.patch
	touch $@

$(STAGING_DIR)/$(CMDLINEMESH_BINARY): $(CMDLINEMESH_DIR)/.unpacked
	$(MAKE) CC=$(TARGET_CC) -C $(CMDLINEMESH_DIR)
	#$(MAKE)	-C $(CMDLINEMESH_DIR)

$(STAGING_DIR)/$(CMDLINEMESH_TARGET_BINARY): $(STAGING_DIR)/$(CMDLINEMESH_BINARY)
	$(INSTALL) -D -m 0755 $(CMDLINEMESH_DIR)/cmdLineMesh $(TARGET_DIR)/usr/bin

cmdLineMesh: $(STAGING_DIR)/$(CMDLINEMESH_TARGET_BINARY)

cmdLineMesh-clean:
	$(MAKE) -C $(CMDLINEMESH_DIR) clean
	rm $(TARGET_DIR)/usr/bin/cmdLineMesh

cmdLineMesh-dirclean:
	rm -rf $(CMDLINEMESH_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_CMDLINEMESH),y)
TARGETS+=cmdLineMesh
endif
