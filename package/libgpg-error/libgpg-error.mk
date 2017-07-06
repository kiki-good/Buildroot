#############################################################
#
# libgpg-error
#
#############################################################
ifeq ($(BR2_ARCH_IS_64),y)
LIBGPG_ERROR_VERSION:=1.26
else
LIBGPG_ERROR_VERSION:=1.8
endif
LIBGPG_ERROR_SOURCE:=libgpg-error-$(LIBGPG_ERROR_VERSION).tar.bz2
LIBGPG_ERROR_SITE:=ftp://gd.tuwien.ac.at/privacy/gnupg/libgpg-error

LIBGPG_ERROR_LIBTOOL_PATCH = NO
LIBGPG_ERROR_INSTALL_STAGING = YES

ifeq ($(BR2_PACKAGE_DIAG),y)
LIBGPG_ERROR_INSTALL_TARGET = NO
endif

$(eval $(call AUTOTARGETS,package,libgpg-error))

define LIBGPG_POST_INSTALL
	cp -dpf $(STAGING_DIR)/usr/lib/libgpg-error.so* $(TARGET_DIR)/usr/lib
endef

LIBGPG_POST_INSTALL_HOOKS += LIBGPG_POST_INSTALL
