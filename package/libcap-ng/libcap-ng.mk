################################################################################
#
# libcap-ng
#
################################################################################

LIBCAP_NG_VERSION = 0.7.7
LIBCAP_NG_SITE = http://people.redhat.com/sgrubb/libcap-ng
LIBCAP_NG_LICENSE = GPLv2+ LGPLv2.1+
LIBCAP_NG_LICENSE_FILES = COPYING COPYING.LIB
LIBCAP_NG_INSTALL_STAGING = YES
LIBCAP_NG_DIR=$(BUILD_DIR)/libcap-ng-$(LIBCAP_NG_VERSION)
LIBCAP_NG_BINARY_SOURCE:=libcapng-$(LIBCAP_NG_VERSION)-binary.tar.bz2
LIBCAP_NG_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
LIBCAP_NG_BINARY_DIR:=$(LIBCAP_NG_BOARD_PATH)/binaries
LIBCAP_NG_INSTALL_BINARY:=$(LIBCAP_NG_BINARY_DIR)/$(LIBCAP_NG_BINARY_SOURCE)
LIBCAP_NG_TEMP_DIR:=$(LIBCAP_NG_BINARY_DIR)/libcap-ng_tmp

define LIBCAP_NG_POST_INSTALL_PREBUILT_BINARIES
	mkdir -p $(LIBCAP_NG_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(LIBCAP_NG_TEMP_DIR) -C $(LIBCAP_NG_DIR) install
	tar cjvf $(LIBCAP_NG_BINARY_DIR)/$(LIBCAP_NG_BINARY_SOURCE) -C $(LIBCAP_NG_TEMP_DIR) .
	rm -rf $(LIBCAP_NG_TEMP_DIR)
endef

define LIBCAP_NG_POST_INSTALL
	rm -rf $(TARGET_DIR)/usr/share/aclocal/cap-ng.m4
	mv $(TARGET_DIR)/usr/bin/$(BR2_TOOLCHAIN_EXTERNAL_PREFIX)-captest $(TARGET_DIR)/usr/bin/captest
	mv $(TARGET_DIR)/usr/bin/$(BR2_TOOLCHAIN_EXTERNAL_PREFIX)-pscap $(TARGET_DIR)/usr/bin/pscap
	mv $(TARGET_DIR)/usr/bin/$(BR2_TOOLCHAIN_EXTERNAL_PREFIX)-filecap $(TARGET_DIR)/usr/bin/filecap
	mv $(TARGET_DIR)/usr/bin/$(BR2_TOOLCHAIN_EXTERNAL_PREFIX)-netcap $(TARGET_DIR)/usr/bin/netcap
endef
LIBCAP_NG_POST_INSTALL_STAGING_HOOKS += LIBCAP_NG_POST_INSTALL_PREBUILT_BINARIES
LIBCAP_NG_POST_INSTALL_TARGET_HOOKS += LIBCAP_NG_POST_INSTALL


LIBCAP_NG_CONF_ENV = ac_cv_prog_swig_found=no
LIBCAP_NG_CONF_OPT = --without-python


libcap-ng-binary:
	tar -xjvf $(LIBCAP_NG_BINARY_DIR)/$(LIBCAP_NG_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(LIBCAP_NG_BINARY_DIR)/$(LIBCAP_NG_BINARY_SOURCE) -C $(TARGET_DIR)/
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L/$(STAGING_DIR)/usr/lib',g" $(STAGING_DIR)/usr/lib/libcap-ng.la
	$(SED) "s,^libdir=.*,libdir\='$(STAGING_DIR)/usr/lib',g" $(STAGING_DIR)/usr/lib/libcap-ng.la
	rm -rf $(TARGET_DIR)/usr/share/aclocal/cap-ng.m4
	mv $(TARGET_DIR)/usr/bin/$(BR2_TOOLCHAIN_EXTERNAL_PREFIX)-captest $(TARGET_DIR)/usr/bin/captest
	mv $(TARGET_DIR)/usr/bin/$(BR2_TOOLCHAIN_EXTERNAL_PREFIX)-pscap $(TARGET_DIR)/usr/bin/pscap
	mv $(TARGET_DIR)/usr/bin/$(BR2_TOOLCHAIN_EXTERNAL_PREFIX)-filecap $(TARGET_DIR)/usr/bin/filecap
	mv $(TARGET_DIR)/usr/bin/$(BR2_TOOLCHAIN_EXTERNAL_PREFIX)-netcap $(TARGET_DIR)/usr/bin/netcap

ifeq ($(wildcard $(LIBCAP_NG_INSTALL_BINARY)),)
libcap-ng: $(eval $(call AUTOTARGETS,package,libcap-ng))
else
libcap-ng: libcap-ng-binary
endif

libcap-ng-binary-clean:
	rm $(LIBCAP_NG_INSTALL_BINARY)

ifeq ($(BR2_PACKAGE_LIBCAP_NG),y)
TARGETS+=libcap-ng
endif


