#############################################################
#
# pigz
#
#############################################################
PIGZ_VERSION:=2.3.3
PIGZ_SOURCE:=pigz-$(PIGZ_VERSION).tar.bz2
PIGZ_SITE:=http://localhost/
PIGZ_CAT:=$(BZCAT)
PIGZ_DIR:=$(BUILD_DIR)/pigz-$(PIGZ_VERSION)
PIGZ_BINARY:=pigz
PIGZ_TARGET_BINARY:=usr/bin/pigz
PIGZ_DEPENDENCIES:=zlib

$(DL_DIR)/$(PIGZ_SOURCE):
	 $(call DOWNLOAD,$(PIGZ_SITE),$(PIGZ_SOURCE))

pigz-source: $(DL_DIR)/$(PIGZ_SOURCE)

$(PIGZ_DIR)/.unpacked: $(DL_DIR)/$(PIGZ_SOURCE)
	$(PIGZ_CAT) $(DL_DIR)/$(PIGZ_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(PIGZ_DIR) package/pigz/ pigz-$(PIGZ_VERSION)-\*.patch
	touch $@

$(PIGZ_DIR)/$(PIGZ_BINARY): $(PIGZ_DIR)/.unpacked
	$(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(PIGZ_DIR) \
		CFLAGS+=-I$(STAGING_DIR)/usr/include/ \
		CFLAGS+=-I$(STAGING_DIR)/include/ \
		LDFLAGS=-L$(TARGET_DIR)/usr/lib/

$(TARGET_DIR)/$(PIGZ_TARGET_BINARY): $(PIGZ_DIR)/$(PIGZ_BINARY)
	rm -f $(TARGET_DIR)/$(PIGZ_TARGET_BINARY)
	$(INSTALL) -D -m 0755 $(PIGZ_DIR)/$(PIGZ_BINARY) $(TARGET_DIR)/$(PIGZ_TARGET_BINARY)
	$(STRIPCMD) $(STRIP_STRIP_ALL) $@

pigz: zlib $(TARGET_DIR)/$(PIGZ_TARGET_BINARY)

pigz-clean:
	-$(MAKE) -C $(PIGZ_DIR) clean
	rm -f $(TARGET_DIR)/$(PIGZ_TARGET_BINARY)

pigz-dirclean:
	rm -rf $(PIGZ_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_PIGZ),y)
TARGETS+=pigz
endif
