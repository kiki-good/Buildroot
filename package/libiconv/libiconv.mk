#############################################################
#
# libiconv
#
#############################################################
ifeq ($(BR2_ARCH_IS_64),y)
LIBICONV_VERSION = 1.15
else
LIBICONV_VERSION = 1.12
endif
LIBICONV_SOURCE = libiconv-$(LIBICONV_VERSION).tar.gz
LIBICONV_SITE = $(BR2_GNU_MIRROR)/libiconv
LIBICONV_BINARY_SOURCE:=libiconv-$(LIBICONV_VERSION)-binary.tar.bz2
LIBICONV_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
LIBICONV_DIR=$(BUILD_DIR)/libiconv-$(LIBICONV_VERSION)
LIBICONV_BINARY_DIR:=$(LIBICONV_BOARD_PATH)/binaries
LIBICONV_INSTALL_BINARY:=$(LIBICONV_BINARY_DIR)/$(LIBICONV_BINARY_SOURCE)
LIBICONV_AUTORECONF = NO
LIBICONV_INSTALL_STAGING = YES
LIBICONV_INSTALL_TARGET = YES
ifeq ($(BR2_ARCH_IS_64),y)
#TO FIX
LIBICONV_LIBTOOL_PATCH = NO
endif

LIBICONV_INSTALL_TARGET_OPT = DESTDIR=$(TARGET_DIR) install

LIBICONV_DEPENDENCIES = uclibc

ifeq ($(BR2_ARCH_IS_64),y)
define LIBICONV_POST_APPLY_64BITPATCH
toolchain/patch-kernel.sh $(LIBICONV_DIR) package/libiconv/64bitPatch libiconv-$(LIBICONV_VERSION)\*.patch*
endef

LIBICONV_POST_PATCH_HOOKS += LIBICONV_POST_APPLY_64BITPATCH
else
define LIBICONV_POST_APPLY_32BITPATCH
toolchain/patch-kernel.sh $(LIBICONV_DIR) package/libiconv/32bitPatch libiconv-$(LIBICONV_VERSION)\*.patch*
endef
LIBICONV_POST_PATCH_HOOKS += LIBICONV_POST_APPLY_32BITPATCH
endif

libiconv-binary:
	tar -xjvf $(LIBICONV_BINARY_DIR)/$(LIBICONV_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(LIBICONV_BINARY_DIR)/$(LIBICONV_BINARY_SOURCE) -C $(TARGET_DIR)/
	rm -f $(TARGET_DIR)/usr/lib/preloadable_libiconv.so
	rm -f $(TARGET_DIR)/usr/lib/libcharset.so


ifeq ($(wildcard $(LIBICONV_INSTALL_BINARY)),)
$(eval $(call AUTOTARGETS,package,libiconv))
else
libiconv: libiconv-binary
endif

libiconv-binary-clean:
	rm -rf $(LIBICONV_INSTALL_BINARY)

define LIBICONV_POST_INSTALL
	@$(call MESSAGE,"LIBICONV_POST_INSTALL")
	# Remove not used preloadable libiconv.so
	rm -f $(STAGING_DIR)/usr/lib/preloadable_libiconv.so
	rm -f $(TARGET_DIR)/usr/lib/preloadable_libiconv.so
	rm -f $(TARGET_DIR)/usr/lib/libcharset.so
ifneq ($(BR2_ENABLE_DEBUG),y)
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libiconv.so.*
endif
	touch $@
endef

define LIBICONV_POST_INSTALL_CUSTOMISATION
	mkdir -p $(LIBICONV_BINARY_DIR)/libiconv_tmp
	$(MAKE) DESTDIR=$(PWD)/$(LIBICONV_BINARY_DIR)/libiconv_tmp -C $(LIBICONV_DIR) install
	tar cjvf $(LIBICONV_BINARY_DIR)/$(LIBICONV_BINARY_SOURCE) -C $(LIBICONV_BINARY_DIR)/libiconv_tmp .
	rm -rf $(LIBICONV_BINARY_DIR)/libiconv_tmp
endef

LIBICONV_POST_INSTALL_HOOKS += LIBICONV_POST_INSTALL
LIBICONV_POST_INSTALL_STAGING_HOOKS += LIBICONV_POST_INSTALL_CUSTOMISATION
