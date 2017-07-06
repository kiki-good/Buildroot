################################################################################
#
# libnss
#
################################################################################

LIBNSS_VERSION = 3.14.5
LIBNSS_SOURCE = nss-$(LIBNSS_VERSION).tar.gz
LIBNSS_SITE = http://localhost/
LIBNSS_SUBDIR = mozilla/security
LIBNSS_DISTDIR = mozilla/dist
LIBNSS_INSTALL_STAGING = YES
LIBNSS_DEPENDENCIES = libnspr sqlite zlib
LIBNSS_LICENSE = MPLv2.0
LIBNSS_LICENSE_FILES = mozilla/security/nss/COPYING
LIBNSS_DIR = $(BUILD_DIR)/nss-$(LIBNSS_VERSION)
LIBNSS_CAT = $(ZCAT)
LIBNSS_BINARY = usr/lib/libnss.so
LIBNSS_BINARY_SOURCE:=nss-$(LIBNSS_VERSION)-binary.tar.bz2
LIBNSS_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
LIBNSS_BINARY_DIR:=$(LIBNSS_BOARD_PATH)/binaries
LIBNSS_INSTALL_BINARY:=$(LIBNSS_BINARY_DIR)/$(LIBNSS_BINARY_SOURCE)
LIBNSS_TEMP_DIR:=$(LIBNSS_BINARY_DIR)/nss_tmp

LIBNSS_BUILD_VARS = MOZILLA_CLIENT=1 \
		NSPR_INCLUDE_DIR=$(STAGING_DIR)/usr/include/nspr \
		NSPR_LIB_DIR=$(STAGING_DIR)/usr/lib \
		BUILD_OPT=1 \
		NS_USE_GCC=1 \
		NSS_USE_SYSTEM_SQLITE=1 \
		NSS_USE_SYSTEM_ZLIB=1 \
		USE_SYSTEM_ZLIB=1 \
		NSS_ENABLE_ECC=1 \
		NATIVE_CC="$(HOSTCC)" \
		TARGETCC="$(TARGET_CC)" \
		TARGETCCC="$(TARGET_CXX)" \
		TARGETRANLIB="$(TARGET_RANLIB)" \
		OS_ARCH="Linux" \
		OS_RELEASE="2.6" \
		OS_TEST="$(ARCH)"

ifeq ($(BR2_ARCH_IS_64),y)
LIBNSS_BUILD_VARS += USE_64=1
endif

define LIBNSS_BUILD_CMDS
	mkdir -p $(@D)/$(LIBNSS_SUBDIR)/nss
	$(MAKE1) -C $(@D)/$(LIBNSS_SUBDIR)/nss build_coreconf \
			SOURCE_MD_DIR=$(@D)/$(LIBNSS_DISTDIR) \
			DIST=$(@D)/$(LIBNSS_DISTDIR) \
			CHECKLOC= \
			$(LIBNSS_BUILD_VARS)
	$(MAKE1) -C $(@D)/$(LIBNSS_SUBDIR)/nss build_dbm all \
			SOURCE_MD_DIR=$(@D)/$(LIBNSS_DISTDIR) \
			DIST=$(@D)/$(LIBNSS_DISTDIR) \
			CHECKLOC= \
			$(LIBNSS_BUILD_VARS) OPTIMIZER="$(TARGET_CFLAGS)"
endef

define LIBNSS_INSTALL_STAGING_CMDS
	$(INSTALL) -m 755 -t $(STAGING_DIR)/usr/lib/ \
		$(@D)/$(LIBNSS_DISTDIR)/lib/*.so
	$(INSTALL) -m 755 -d $(STAGING_DIR)/usr/include/nss
	$(INSTALL) -m 644 -t $(STAGING_DIR)/usr/include/nss \
		$(@D)/$(LIBNSS_DISTDIR)/public/nss/*
	$(INSTALL) -m 755 -t $(STAGING_DIR)/usr/lib/ \
		$(@D)/$(LIBNSS_DISTDIR)/lib/*.a
	$(INSTALL) -D -m 0644 $(TOPDIR)/package/libnss/nss.pc.in \
		$(STAGING_DIR)/usr/lib/pkgconfig/nss.pc
	$(SED) 's/@VERSION@/$(LIBNSS_VERSION)/g;' \
		$(STAGING_DIR)/usr/lib/pkgconfig/nss.pc
endef

define LIBNSS_INSTALL_TARGET_CMDS
	$(INSTALL) -m 755 -t $(TARGET_DIR)/usr/lib/ \
		$(@D)/$(LIBNSS_DISTDIR)/lib/*.so
	$(INSTALL) -m 755 -d $(TARGET_DIR)/usr/include/nss
	$(INSTALL) -m 644 -t $(TARGET_DIR)/usr/include/nss \
		$(@D)/$(LIBNSS_DISTDIR)/public/nss/*
	$(INSTALL) -m 755 -t $(TARGET_DIR)/usr/lib/ \
		$(@D)/$(LIBNSS_DISTDIR)/lib/*.a
	$(INSTALL) -D -m 0644 $(TOPDIR)/package/libnss/nss.pc.in \
		$(TARGET_DIR)/usr/lib/pkgconfig/nss.pc
	$(SED) 's/@VERSION@/$(LIBNSS_VERSION)/g;' \
		$(TARGET_DIR)/usr/lib/pkgconfig/nss.pc
endef

define LIBNSS_INSTALL_TEMP_DIR
	$(INSTALL) -m 755 -d $(LIBNSS_TEMP_DIR)/usr/lib
	$(INSTALL) -m 755 -t $(LIBNSS_TEMP_DIR)/usr/lib/ \
		$(LIBNSS_DIR)/$(LIBNSS_DISTDIR)/lib/*.so
	$(INSTALL) -m 755 -d $(LIBNSS_TEMP_DIR)/usr/include/nss
	$(INSTALL) -m 644 -t $(LIBNSS_TEMP_DIR)/usr/include/nss \
		$(LIBNSS_DIR)/$(LIBNSS_DISTDIR)/public/nss/*
	$(INSTALL) -m 755 -t $(LIBNSS_TEMP_DIR)/usr/lib/ \
		$(LIBNSS_DIR)/$(LIBNSS_DISTDIR)/lib/*.a
	$(INSTALL) -D -m 0644 $(TOPDIR)/package/libnss/nss.pc.in \
		$(LIBNSS_TEMP_DIR)/usr/lib/pkgconfig/nss.pc
endef

$(DL_DIR)/$(LIBNSS_SOURCE): $(LIBNSS_PATCH)
	$(WGET) -P $(DL_DIR) $(LIBNSS_SITE)/$(LIBNSS_SOURCE)
	touch -c $@

libnss-source: $(DL_DIR)/$(LIBNSS_SOURCE) $(LIBNSS_PATCH)

libnss-unpacked: $(LIBNSS_DIR)/.unpacked
$(LIBNSS_DIR)/.unpacked: $(AUTOCONF) $(AUTOMAKE) $(LIBTOOL) $(DL_DIR)/$(LIBNSS_SOURCE)
	$(LIBNSS_CAT) $(DL_DIR)/$(LIBNSS_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(LIBNSS_DIR) package/libnss/ libnss-\*.patch
	touch $@

$(LIBNSS_DIR)/.configured: $(LIBNSS_DIR)/.unpacked
	touch $@

$(LIBNSS_DIR)/.built: $(LIBNSS_DIR)/.configured
	$(LIBNSS_BUILD_CMDS)
	touch $@

libnss-temp-install: 
	mkdir -p $(LIBNSS_TEMP_DIR)
	$(LIBNSS_INSTALL_TEMP_DIR)
	tar cjvf $(LIBNSS_BINARY_DIR)/$(LIBNSS_BINARY_SOURCE) -C $(LIBNSS_TEMP_DIR) .
	rm -rf $(LIBNSS_TEMP_DIR)

$(LIBNSS_DIR)/.installed-staging: $(LIBNSS_DIR)/.built libnss-temp-install
	$(LIBNSS_INSTALL_STAGING_CMDS)
	touch $@

$(LIBNSS_DIR)/.installed-target: $(LIBNSS_DIR)/.installed-staging
	$(LIBNSS_INSTALL_TARGET_CMDS)
	touch $@

libnss-binary: 
	tar -xjvf $(LIBNSS_BINARY_DIR)/$(LIBNSS_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(LIBNSS_BINARY_DIR)/$(LIBNSS_BINARY_SOURCE) -C $(TARGET_DIR)/
	$(SED) 's/@VERSION@/$(LIBNSS_VERSION)/g;' \
		$(STAGING_DIR)/usr/lib/pkgconfig/nss.pc
	$(SED) 's/@VERSION@/$(LIBNSS_VERSION)/g;' \
		$(TARGET_DIR)/usr/lib/pkgconfig/nss.pc

ifeq ($(wildcard $(LIBNSS_INSTALL_BINARY)),)
libnss: libnspr sqlite zlib $(LIBNSS_DIR)/.installed-target
else
libnss: libnss-binary
endif


libnss-clean:
	rm -f $(STAGING_DIR)/bin/libnss-config
	rm -f $(STAGING_DIR)/lib/libnss*
	rm -rf $(STAGING_DIR)/lib/pkgconfig
	rm -f $(TARGET_DIR)/usr/lib/libnss*
	-$(MAKE) -C $(LIBNSS_DIR) clean

libnss-dirclean:
	rm -rf $(LIBNSS_DIR)

libnss-binary-clean:
	rm $(LIBNSS_INSTALL_BINARY)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_LIBNSS),y)
TARGETS+=libnss
endif

