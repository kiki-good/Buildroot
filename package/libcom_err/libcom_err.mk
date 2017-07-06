#############################################################
#
# libcom_err
#
#############################################################
LIBCOM_ERR_VERSION=5.0
LIBCOM_ERR_SOURCE=libcom_err-$(LIBCOM_ERR_VERSION).tar.gz
LIBCOM_ERR_SITE=http://localhost/
LIBCOM_ERR_DIR=$(BUILD_DIR)/libcom_err-$(LIBCOM_ERR_VERSION)
LIBCOM_ERR_CAT:=$(ZCAT)
LIBCOM_ERR_LIBTOOL_PATCH=NO
LIBCOM_ERR_INSTALL_STAGING=YES
LIBCOM_ERR_INSTALL_TARGET=YES
LIBCOM_ERR_AUTORECONF=NO
LIBCOM_ERR_DEPENDENCIES+= pkgconfig
LIBCOM_ERR_CONF_OPT = --includedir=/usr/include --enable-shared 

ifeq ($(BR2_ARCH_IS_64),y)
define LIBCOM_ERR_POST_APPLY_64BITPATCH
	toolchain/patch-kernel.sh $(LIBCOM_ERR_DIR) package/libcom_err/64bitPatch libcom_err-$(LIBCOM_ERR_VERSION)\*.patch
endef

LIBCOM_ERR_POST_PATCH_HOOKS += LIBCOM_ERR_POST_APPLY_64BITPATCH
else
define LIBCOM_ERR_POST_APPLY_32BITPATCH
        toolchain/patch-kernel.sh $(LIBCOM_ERR_DIR) package/libcom_err/32bitPatch libcom_err-$(LIBCOM_ERR_VERSION)\*.patch
endef
LIBCOM_ERR_POST_PATCH_HOOKS += LIBCOM_ERR_POST_APPLY_32BITPATCH	
endif


$(eval $(call AUTOTARGETS,package,libcom_err))
