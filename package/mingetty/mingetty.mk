#############################################################
#
# MINGETTY
#
#############################################################
MINGETTY_VERSION:=1.08
MINGETTY_SITE:=http://mingetty.ubuntu.com/download/$(MINGETTY_VERSION)
MINGETTY_SOURCE:=mingetty-$(MINGETTY_VERSION).tar.gz
MINGETTY_DIR:=$(BUILD_DIR)/mingetty-$(MINGETTY_VERSION)
MINGETTY_CAT:=$(ZCAT) 
MINGETTY_BINARY:=mingetty
MINGETTY_TARGET_BINARY:=sbin/mingetty

$(DL_DIR)/$(MINGETTY_SOURCE): 
	$(WGET) -P $(DL_DIR) $(MINGETTY_SITE)/$(MINGETTY_SOURCE)

mingetty-source: $(DL_DIR)/$(MINGETTY_SOURCE)

mingetty-unpacked: $(MINGETTY_DIR)/.unpacked
$(MINGETTY_DIR)/.unpacked: $(DL_DIR)/$(MINGETTY_SOURCE)
	$(MINGETTY_CAT) $(DL_DIR)/$(MINGETTY_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(MINGETTY_DIR) package/mingetty/ mingetty-$(MINGETTY_VERSION)\*.patch
	touch $@

$(STAGING_DIR)/$(MINGETTY_BINARY): $(MINGETTY_DIR)/.unpacked
	$(MAKE) CC=$(TARGET_CC) -C $(MINGETTY_DIR)
	#$(MAKE)	-C $(MINGETTY_DIR)

$(STAGING_DIR)/$(MINGETTY_TARGET_BINARY): $(STAGING_DIR)/$(MINGETTY_BINARY)
	$(INSTALL) -D -m 0755 $(MINGETTY_DIR)/mingetty $(TARGET_DIR)/sbin

mingetty: $(STAGING_DIR)/$(MINGETTY_TARGET_BINARY)

mingetty-clean:
	$(MAKE) -C $(MINGETTY_DIR) clean
	rm $(TARGET_DIR)/sbin/mingetty

mingetty-dirclean:
	rm -rf $(MINGETTY_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_MINGETTY),y)
TARGETS+=mingetty
endif
