################################################################################
#
# libsbc
#
################################################################################

LIBSBC_VERSION = 1.3
LIBSBC_SITE = http://localhost/
LIBSBC_LICENSE = LGPLv2.1+
LIBSBC_LICENSE_FILES = COPYING
LIBSBC_SOURCE:=sbc-$(LIBSBC_VERSION).tar.xz
LIBSBC_INSTALL_STAGING = YES
LIBSBC_INSTALL_TARGET = YES
# LIBSBC_DEPENDENCIES = host-bison host-flex

LIBSBC_DIR=$(BUILD_DIR)/libsbc-$(LIBSBC_VERSION)
LIBSBC_BINARY_SOURCE:=libsbc-$(LIBSBC_VERSION)-binary.tar.bz2
LIBSBC_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
LIBSBC_BINARY_DIR:=$(LIBSBC_BOARD_PATH)/binaries
LIBSBC_INSTALL_BINARY:=$(LIBSBC_BINARY_DIR)/$(LIBSBC_BINARY_SOURCE)
LIBSBC_TEMP_DIR:=$(LIBSBC_BINARY_DIR)/libsbc_tmp

define LIBSBC_POST_INSTALL_PREBUILT_BINARIES
	mkdir -p $(LIBSBC_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(LIBSBC_TEMP_DIR) -C $(LIBSBC_DIR) install
	tar cjvf $(LIBSBC_BINARY_DIR)/$(LIBSBC_BINARY_SOURCE) -C $(LIBSBC_TEMP_DIR) .
	rm -rf $(LIBSBC_TEMP_DIR)
endef

define LIBSBC_TARGET_CLEAN_UP
	rm -rf $(TARGET_DIR)/usr/local/sbc/
	if [ $(BR2_SKY_BUILD_TYPE) != "debug" ]; then \
		rm -rf $(TARGET_DIR)/usr/bin/sbcinfo; \
		rm -rf $(TARGET_DIR)/usr/bin/sbcenc; \
		rm -rf $(TARGET_DIR)/usr/bin/sbcdec; \
	fi
endef

LIBSBC_POST_INSTALL_STAGING_HOOKS += LIBSBC_POST_INSTALL_PREBUILT_BINARIES

LIBSBC_POST_INSTALL_TARGET_HOOKS += LIBSBC_TARGET_CLEAN_UP

LIBSBC_CONF_OPT += --prefix=/usr/local/sbc --disable-silent-rules --disable-tester


libsbc-binary:
	tar -xjvf $(LIBSBC_BINARY_DIR)/$(LIBSBC_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(LIBSBC_BINARY_DIR)/$(LIBSBC_BINARY_SOURCE) -C $(TARGET_DIR)/
	$(SED) "s,^libdir=.*,libdir\='$(STAGING_DIR)/usr/lib',g" $(STAGING_DIR)/usr/lib/libsbc.la
	rm -rf $(TARGET_DIR)/usr/local/sbc/
ifneq ($(BR2_SKY_BUILD_TYPE),"debug")
	rm -rf $(TARGET_DIR)/usr/bin/sbcinfo
	rm -rf $(TARGET_DIR)/usr/bin/sbcenc
	rm -rf $(TARGET_DIR)/usr/bin/sbcdec
endif


ifeq ($(wildcard $(LIBSBC_INSTALL_BINARY)),)
libsbc: $(eval $(call AUTOTARGETS,package,libsbc))
else
libsbc: libsbc-binary
endif

libsbc-binary-clean:
	rm $(LIBSBC_INSTALL_BINARY)

ifeq ($(BR2_PACKAGE_LIBSBC),y)
TARGETS+=libsbc
endif


