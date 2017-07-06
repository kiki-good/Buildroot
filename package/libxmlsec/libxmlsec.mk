#############################################################
#
# libxml2
#
#############################################################
ifeq ($(BR2_ARCH_IS_64),y)
#LIBXMLSEC_VERSION = 1.2.23
#LIBXMLSEC_SOURCE = libxmlsec-$(LIBXMLSEC_VERSION).tar.gz

#LIBXMLSEC_VERSION = 1.2.20
#LIBXMLSEC_SOURCE = xmlsec1-$(LIBXMLSEC_VERSION).tar.gz

LIBXMLSEC_VERSION = 1.2.24
LIBXMLSEC_SOURCE = xmlsec1-$(LIBXMLSEC_VERSION).tar.gz
else
LIBXMLSEC_VERSION = 1.2.20
LIBXMLSEC_SOURCE = xmlsec1-$(LIBXMLSEC_VERSION).tar.gz
endif

#LIBXMLSEC_SOURCE = xmlsec1-$(LIBXMLSEC_VERSION).tar.gz
LIBXMLSEC_BINARY_SOURCE:=libxmlsec-$(LIBXMLSEC_VERSION)-binary.tar.bz2
LIBXMLSEC_SITE = http://localhost/
LIBXMLSEC_INSTALL_STAGING = YES
LIBXMLSEC_INSTALL_TARGET = YES
LIBXMLSEC_DIR=$(BUILD_DIR)/libxmlsec-$(LIBXMLSEC_VERSION)
LIBXMLSEC_BINARY_SOURCE:=libxmlsec-$(LIBXMLSEC_VERSION)-binary.tar.bz2
LIBXMLSEC_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
LIBXMLSEC_BINARY_DIR:=$(LIBXMLSEC_BOARD_PATH)/binaries
LIBXMLSEC_INSTALL_BINARY:=$(LIBXMLSEC_BINARY_DIR)/$(LIBXMLSEC_BINARY_SOURCE)
LIBXMLSEC_TEMP_DIR:=$(LIBXMLSEC_BINARY_DIR)/libxmlsec_tmp

#TO FIX
LIBXMLSEC_LIBTOOL_PATCH = NO

ifeq ($(BR2_ARCH_IS_64),y)
define LIBXMLSEC_POST_APPLY_64BITPATCH
toolchain/patch-kernel.sh $(LIBXMLSEC_DIR) package/libxmlsec/64bitPatch libxmlsec-$(LIBXMLSEC_VERSION)\*.patch*
endef

LIBXMLSEC_POST_PATCH_HOOKS += LIBXMLSEC_POST_APPLY_64BITPATCH
else
define OPENSSL_POST_APPLY_32BITPATCH
#toolchain/patch-kernel.sh $(LIBXMLSEC_DIR) package/libxmlsec/32bitPatch libxmlsec-$(LIBXMLSEC_VERSION)\*.patch*
toolchain/patch-kernel.sh $(LIBXMLSEC_DIR) package/libxmlsec/32bitPatch libxmlsec-\*.patch*
endef
LIBXMLSEC_POST_PATCH_HOOKS += LIBXMLSEC_POST_APPLY_32BITPATCH
endif


define LIBXMLSEC_POST_INSTALL_PREBUILT_BINARIES
	mkdir -p $(LIBXMLSEC_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(LIBXMLSEC_TEMP_DIR) -C $(LIBXMLSEC_DIR) install
	tar cjvf $(LIBXMLSEC_BINARY_DIR)/$(LIBXMLSEC_BINARY_SOURCE) -C $(LIBXMLSEC_TEMP_DIR) .
	rm -rf $(LIBXMLSEC_TEMP_DIR)
endef

define LIBXMLSEC_POST_INSTALL
	rm -rf $(TARGET_DIR)/usr/bin/xmlsec1-config
	rm -rf $(TARGET_DIR)/usr/bin/xmlsec1
	rm -rf $(TARGET_DIR)/usr/lib/xmlsec1Conf.sh
	touch $@
endef
LIBXMLSEC_POST_INSTALL_STAGING_HOOKS += LIBXMLSEC_POST_INSTALL_PREBUILT_BINARIES
LIBXMLSEC_POST_INSTALL_TARGET_HOOKS += LIBXMLSEC_POST_INSTALL


ifneq ($(BR2_LARGEFILE),y)
LIBXMLSEC_CONF_ENV = CC="$(TARGET_CC) $(TARGET_CFLAGS) -DNO_LARGEFILE_SOURCE"
endif

#LIBXMLSEC_CONF_ENV = CC="$(TARGET_CC) $(TARGET_CFLAGS) -I/home/jqiao/spk64bit_formal_check_in/spk/objOutput/bskyb-brcm64bit/build_aarch64/openssl-1.1.0d/include -L/home/jqiao/spk64bit_formal_check_in/spk/./objOutput/bskyb-brcm64bit/project_build_aarch64/bskyb-brcm64bit/root/usr/lib"

LIBXMLSEC_CONF_ENV = CC="$(TARGET_CC) $(TARGET_CFLAGS) -I/home/jqiao/spk64bit_formal_check_in/spk/objOutput/bskyb-brcm64bit/build_aarch64/openssl-1.1.0d/include"

#LIBXMLSEC_CONF_ENV += OPENSSL_LIBS="/home/jqiao/spk64bit_formal_check_in/spk/objOutput/bskyb-brcm64bit/project_build_aarch64/bskyb-brcm64bit/root/usr/lib"

LIBXMLSEC_CONF_OPT = --disable-crypto-dl \
			--without-nss \
			--without-gcrypt \
			--without-gnutls \
			--with-openssl=$(TARGET_DIR)/usr


LIBXMLSEC_DEPENDENCIES = libxml2 libiconv libxslt openssl

libxmlsec-binary:
	tar -xjvf $(LIBXMLSEC_BINARY_DIR)/$(LIBXMLSEC_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(LIBXMLSEC_BINARY_DIR)/$(LIBXMLSEC_BINARY_SOURCE) -C $(TARGET_DIR)/
	rm -rf $(TARGET_DIR)/usr/bin/xmlsec1-config
	rm -rf $(TARGET_DIR)/usr/bin/xmlsec1
	rm -rf $(TARGET_DIR)/usr/lib/xmlsec1Conf.sh

ifeq ($(wildcard $(LIBXMLSEC_INSTALL_BINARY)),)
libxmlsec: $(eval $(call AUTOTARGETS,package,libxmlsec))
else
libxmlsec: libxmlsec-binary
endif

libxmlsec-binary-clean:
	rm $(LIBXMLSEC_INSTALL_BINARY)

ifeq ($(BR2_PACKAGE_LIBXMLSEC),y)
TARGETS+=libxmlsec
endif


