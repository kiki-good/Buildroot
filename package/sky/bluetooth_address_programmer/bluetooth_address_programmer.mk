#############################################################
#
# bluetooth_address_programmer
#
#############################################################
BT_ADDR_PGM_VERSION = 0.0.3
BT_ADDR_PGM_DIR:=$(BUILD_DIR)/bluetooth_address_programmer-$(BT_ADDR_PGM_VERSION)
BT_ADDR_PGM_SOURCE = $(SKY_DL_DIR)/bluetooth_address_programmer-$(BT_ADDR_PGM_VERSION).tar.bz2
BT_ADDR_PGM_CAT:=$(BZCAT)
BT_ADDR_PGM_INSTALL_TARGET = YES
BOARD_NAME= $(strip $(subst ",,$(BR2_BOARD_NAME)))

ifeq ($(BOARD_NAME),bskyb-falcon-d1)
BT_ADDR_PGM_CFLAGS := -DBSKYB_FALCON_PLATFORM
else ifeq ($(BOARD_NAME),bskyb-falcon-d1-uhd)
BT_ADDR_PGM_CFLAGS := -DBSKYB_FALCON_PLATFORM
else ifeq ($(BR2_TOOLCHAIN_EXTERNAL_PREFIX),"armv7-linux")
BT_ADDR_PGM_CFLAGS := -DBSKYB_ST_PLATFORM
else
#error "Platform not supported"
endif

bluetooth_address_programmer-source: $(DL_DIR)/$(BT_ADDR_PGM_SOURCE)

$(BT_ADDR_PGM_DIR)/.unpacked: $(DL_DIR)/$(BT_ADDR_PGM_SOURCE)
	mkdir -p $(BT_ADDR_PGM_DIR)
	$(BT_ADDR_PGM_CAT) $(DL_DIR)/$(BT_ADDR_PGM_SOURCE) | tar -C $(BT_ADDR_PGM_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(BT_ADDR_PGM_DIR) package/sky/bluetooth_address_programmer/ bluetooth_address_programmer-$(BT_ADDR_PGM_VERSION)\*.patch
	touch $(BT_ADDR_PGM_DIR)/.unpacked

$(BT_ADDR_PGM_DIR)/.configured: $(BT_ADDR_PGM_DIR)/.unpacked $(BT_ADDR_PGM_EXTRA_DEPS)
		touch $@

$(BT_ADDR_PGM_DIR)/.compiled: $(BT_ADDR_PGM_DIR)/.configured
	$(MAKE) -C $(BT_ADDR_PGM_DIR) $(TARGET_CONFIGURE_OPTS) $(TARGET_CONFIGURE_ARGS) CFLAGS="$(BT_ADDR_PGM_CFLAGS)"
	touch $@

$(BT_ADDR_PGM_DIR)/.installed: $(BT_ADDR_PGM_DIR)/.compiled
	$(MAKE) -C $(BT_ADDR_PGM_DIR) DESTDIR=$(TARGET_DIR)  install 
	touch $@

bluetooth_address_programmer: $(BT_ADDR_PGM_DIR)/.installed

bluetooth_address_programmer-clean:
	$(MAKE) -C $(BT_ADDR_PGM_DIR) DESTDIR=$(TARGET_DIR) clean
	rm -rf $(BT_ADDR_PGM_DIR)/.installed
	rm -rf $(BT_ADDR_PGM_DIR)/.compiled

bluetooth_address_programmer-dirclean:
	rm -rf $(BT_ADDR_PGM_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_BT_ADDR_PGM),y)
TARGETS+=bluetooth_address_programmer
endif
