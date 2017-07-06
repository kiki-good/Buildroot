#############################################################
#
# WPA_SUPPLICANT
#
#############################################################
WPA_SUPPLICANT_VERSION:=2.6
WPA_SUPPLICANT_SITE:=http://localhost/
WPA_SUPPLICANT_SOURCE:=wpa_supplicant-$(WPA_SUPPLICANT_VERSION).tar.bz2
WPA_SUPPLICANT_DIR:=$(BUILD_DIR)/wpa_supplicant-$(WPA_SUPPLICANT_VERSION)/wpa_supplicant
WPA_SUPPLICANT_CAT:=$(BZCAT) 
WPA_SUPPLICANT_BINARY:=wpa_supplicant
WPA_SUPPLICANT_TARGET_BINARY:=/usr/bin/wpa_supplicant
LIBNL_PKG_PATH:=$(BUILD_DIR)/staging_dir/usr/lib/pkgconfig

$(DL_DIR)/$(WPA_SUPPLICANT_SOURCE): 
	$(WGET) -P $(DL_DIR) $(WPA_SUPPLICANT_SITE)/$(WPA_SUPPLICANT_SOURCE)

wpa_supplicant-source: $(DL_DIR)/$(WPA_SUPPLICANT_SOURCE)

$(WPA_SUPPLICANT_DIR)/.unpacked: $(DL_DIR)/$(WPA_SUPPLICANT_SOURCE)
	$(WPA_SUPPLICANT_CAT) $(DL_DIR)/$(WPA_SUPPLICANT_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	touch $@

wpa_supplicant-unpacked: $(WPA_SUPPLICANT_DIR)/.unpacked 
	
$(STAGING_DIR)/$(WPA_SUPPLICANT_BINARY): wpa_supplicant-unpacked
	export PKG_CONFIG_PATH=$(LIBNL_PKG_PATH)
	$(MAKE) CC=$(TARGET_CC) -C $(WPA_SUPPLICANT_DIR) PKG_CONFIG="$(STAGING_DIR)/usr/bin/pkg-config"

$(STAGING_DIR)/$(WPA_SUPPLICANT_TARGET_BINARY): $(STAGING_DIR)/$(WPA_SUPPLICANT_BINARY)
	$(INSTALL) -D -m 0755 $(WPA_SUPPLICANT_DIR)/wpa_supplicant $(TARGET_DIR)/usr/bin
	$(INSTALL) -D -m 0755 $(WPA_SUPPLICANT_DIR)/wpa_cli $(TARGET_DIR)/usr/bin
	$(INSTALL) -D -m 0755 $(WPA_SUPPLICANT_DIR)/wpa_passphrase $(TARGET_DIR)/usr/bin

wpa_supplicant: $(STAGING_DIR)/$(WPA_SUPPLICANT_TARGET_BINARY)

wpa_supplicant-clean:
	$(MAKE) CC=$(TARGET_CC) -C $(WPA_SUPPLICANT_DIR) clean
	rm $(TARGET_DIR)/usr/bin/wpa_supplicant
	rm $(TARGET_DIR)/usr/bin/wpa_cli
	rm $(TARGET_DIR)/usr/bin/wpa_passphrase

wpa_supplicant-dirclean:
	rm -rf $(WPA_SUPPLICANT_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_SKY_WPA_SUPPLICANT),y)
TARGETS+=wpa_supplicant
endif
