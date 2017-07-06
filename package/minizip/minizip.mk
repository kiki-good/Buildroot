################################################################################
#
# minizip
#
################################################################################

MINIZIP_VERSION = 1.2.8
MINIZIP_SOURCE = minizip-$(MINIZIP_VERSION).tar.bz2
MINIZIP_SITE = https://localhost/
MINIZIP_DEPENDENCIES = zlib
MINIZIP_AUTORECONF = YES
MINIZIP_INSTALL_STAGING = YES
MINIZIP_DIR=$(BUILD_DIR)/minizip-$(MINIZIP_VERSION)
MINIZIP_BINARY_SOURCE:=minizip-$(MINIZIP_VERSION)-binary.tar.bz2
MINIZIP_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
MINIZIP_BINARY_DIR:=$(MINIZIP_BOARD_PATH)/binaries
MINIZIP_INSTALL_BINARY:=$(MINIZIP_BINARY_DIR)/$(MINIZIP_BINARY_SOURCE)
MINIZIP_TEMP_DIR:=$(MINIZIP_BINARY_DIR)/minizip_tmp


define MINIZIP_POST_INSTALL_PREBUILT_BINARIES
        mkdir -p $(MINIZIP_TEMP_DIR)
        $(MAKE) DESTDIR=$(PWD)/$(MINIZIP_TEMP_DIR) -C $(MINIZIP_DIR) install
	rm -rf $(MINIZIP_TEMP_DIR)/usr/lib/libminizip.la 
	rm -rf $(MINIZIP_TEMP_DIR)/usr/lib/libminizip.a 
        tar cjvf $(MINIZIP_BINARY_DIR)/$(MINIZIP_BINARY_SOURCE) -C $(MINIZIP_TEMP_DIR) .
        rm -rf $(MINIZIP_TEMP_DIR)
endef

MINIZIP_POST_INSTALL_STAGING_HOOKS += MINIZIP_POST_INSTALL_PREBUILT_BINARIES

minizip-binary:
	tar -xjvf $(MINIZIP_BINARY_DIR)/$(MINIZIP_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(MINIZIP_BINARY_DIR)/$(MINIZIP_BINARY_SOURCE) -C $(TARGET_DIR)/


ifeq ($(wildcard $(MINIZIP_INSTALL_BINARY)),)
$(eval $(call AUTOTARGETS,package,minizip))
else
minizip: minizip-binary
endif

minizip-binary-clean:
	rm $(MINIZIP_INSTALL_BINARY)

ifeq ($(BR2_PACKAGE_MINIZIP),y)
TARGETS+=minizip
endif

