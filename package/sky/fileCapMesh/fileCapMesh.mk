#############################################################
#
# FILECAPMESH
#
#############################################################
FILECAPMESH_VERSION:=0.0.4
FILECAPMESH_SITE:=http://localhost/
FILECAPMESH_SOURCE:=$(SKY_DL_DIR)/fileCapMesh-$(FILECAPMESH_VERSION).tar.bz2
FILECAPMESH_DIR:=$(BUILD_DIR)/fileCapMesh-$(FILECAPMESH_VERSION)
FILECAPMESH_CAT:=$(BZCAT) 
FILECAPMESH_BINARY:=fileCapMesh
FILECAPMESH_TARGET_BINARY:=/usr/bin/fileCapMesh
FILECAPMESH_CFLAGS+= -I$(STAGING_DIR)/usr/include
FILECAPMESH_LDFLAGS+= -lcap-ng -L$(STAGING_DIR)/usr/lib

$(DL_DIR)/$(FILECAPMESH_SOURCE): 
	$(WGET) -P $(DL_DIR) $(FILECAPMESH_SITE)/$(FILECAPMESH_SOURCE)

fileCapMesh-source: $(DL_DIR)/$(FILECAPMESH_SOURCE)

fileCapMesh-unpacked: $(FILECAPMESH_DIR)/.unpacked
$(FILECAPMESH_DIR)/.unpacked: $(DL_DIR)/$(FILECAPMESH_SOURCE)
	$(FILECAPMESH_CAT) $(DL_DIR)/$(FILECAPMESH_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(FILECAPMESH_DIR) package/sky/fileCapMesh/ fileCapMesh-$(FILECAPMESH_VERSION)\*.patch
	touch $@

$(STAGING_DIR)/$(FILECAPMESH_BINARY): $(FILECAPMESH_DIR)/.unpacked
	$(MAKE) CC=$(TARGET_CC) -C $(FILECAPMESH_DIR) FILECAPMESH_CFLAGS="-I$(STAGING_DIR)/usr/include" FILECAPMESH_LDFLAGS="-lcap-ng -L$(STAGING_DIR)/usr/lib"
	#$(MAKE)	-C $(FILECAPMESH_DIR)

$(STAGING_DIR)/$(FILECAPMESH_TARGET_BINARY): $(STAGING_DIR)/$(FILECAPMESH_BINARY)
	$(INSTALL) -D -m 0755 $(FILECAPMESH_DIR)/fileCapMesh $(TARGET_DIR)/usr/bin

fileCapMesh: libcap-ng $(STAGING_DIR)/$(FILECAPMESH_TARGET_BINARY)

fileCapMesh-clean:
	$(MAKE) -C $(FILECAPMESH_DIR) clean
	rm $(TARGET_DIR)/usr/bin/fileCapMesh

fileCapMesh-dirclean:
	rm -rf $(FILECAPMESH_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_FILECAPMESH),y)
TARGETS+=fileCapMesh
endif
