#############################################################
#
# libgcrypt
#
#############################################################
ifeq ($(BR2_ARCH_IS_64),y)
LIBGCRYPT_VERSION = 1.7.6
else
LIBGCRYPT_VERSION = 1.5.0
endif
LIBGCRYPT_SOURCE = libgcrypt-$(LIBGCRYPT_VERSION).tar.bz2
LIBGCRYPT_SITE = ftp://ftp.gnupg.org/gcrypt/libgcrypt
LIBGCRYPT_DIR = 
LIBGCRYPT_INSTALL_STAGING = YES
LIBGCRYPT_INSTALL_TARGET = NO
LIBGCRYPT_LIBTOOL_PATCH = NO
LIBGCRYPT_DEPENDENCIES := libgpg-error
LIBGCRYPT_MAKE := $(MAKE1)
LIBGCRYPT_DIR:=$(BUILD_DIR)/libgcrypt-$(LIBGCRYPT_VERSION)

LIBGCRYPT_CONF_ENV = \
	ac_cv_sys_symbol_underscore=no
LIBGCRYPT_CONF_OPT = \
	--disable-optimization \
	--with-gpg-error-prefix=$(STAGING_DIR)/usr \
	--libdir=/usr/lib


ifeq ($(BR2_ARCH_IS_64),y)
define LIBGCRYPT_POST_APPLY_64BITPATCH
toolchain/patch-kernel.sh $(LIBGCRYPT_DIR) package/libgcrypt/64bitPatch libgcrypt-$(LIBGCRYPT_VERSION)\*.patch*
endef

LIBGCRYPT_POST_PATCH_HOOKS += LIBGCRYPT_POST_APPLY_64BITPATCH
else
define LIBGCRYPT_POST_APPLY_32BITPATCH
#toolchain/patch-kernel.sh $(LIBGCRYPT_DIR) package/libgcrypt/32bitPatch libgcrypt-$(LIBGCRYPT_VERSION)\*.patch*
toolchain/patch-kernel.sh $(LIBGCRYPT_DIR) package/libgcrypt/32bitPatch libgcrypt-\*.patch*
endef
LIBGCRYPT_POST_PATCH_HOOKS += LIBGCRYPT_POST_APPLY_32BITPATCH
endif


$(eval $(call AUTOTARGETS,package,libgcrypt))
