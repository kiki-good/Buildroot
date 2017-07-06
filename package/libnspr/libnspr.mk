################################################################################
#
# libnspr
#
################################################################################

LIBNSPR_VERSION = 4.9.6
LIBNSPR_SOURCE = nspr-$(LIBNSPR_VERSION).tar.gz
LIBNSPR_SITE = http://localhost/
LIBNSPR_SUBDIR = mozilla/nsprpub
LIBNSPR_INSTALL_STAGING = YES
LIBNSPR_CONFIG_SCRIPTS = nspr-config
LIBNSPR_LICENSE = MPLv2.0
LIBNSPR_LICENSE_FILES = mozilla/nsprpub/LICENSE
LIBNSPR_DIR=$(BUILD_DIR)/libnspr-$(LIBNSPR_VERSION)
LIBNSPR_BINARY_SOURCE:=libnspr-$(LIBNSPR_VERSION)-binary.tar.bz2
LIBNSPR_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
LIBNSPR_BINARY_DIR:=$(LIBNSPR_BOARD_PATH)/binaries
LIBNSPR_INSTALL_BINARY:=$(LIBNSPR_BINARY_DIR)/$(LIBNSPR_BINARY_SOURCE)
LIBNSPR_TEMP_DIR:=$(LIBNSPR_BINARY_DIR)/libnspr_tmp

define LIBNSPR_POST_INSTALL_PREBUILT_BINARIES
	mkdir -p $(LIBNSPR_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(LIBNSPR_TEMP_DIR) -C $(LIBNSPR_DIR)/$(LIBNSPR_SUBDIR) install
	tar cjvf $(LIBNSPR_BINARY_DIR)/$(LIBNSPR_BINARY_SOURCE) -C $(LIBNSPR_TEMP_DIR) .
	rm -rf $(LIBNSPR_TEMP_DIR)
endef

LIBNSPR_POST_INSTALL_STAGING_HOOKS += LIBNSPR_POST_INSTALL_PREBUILT_BINARIES


# Set the host CFLAGS and LDFLAGS so NSPR does not guess wrongly
LIBNSPR_CONF_ENV = HOST_CFLAGS="-g -O2" \
		   HOST_LDFLAGS="-lc"
# NSPR mixes up --build and --host
LIBNSPR_CONF_OPT  = --host=$(GNU_HOST_NAME)
LIBNSPR_CONF_OPT += --$(if $(BR2_ARCH_IS_64),en,dis)able-64bit
LIBNSPR_CONF_OPT += --$(if $(BR2_INET_IPV6),en,dis)able-ipv6

ifeq ($(BR2_arm),y)
ifeq ($(BR2_cortex_a8)$(BR2_cortex_a9),y)
LIBNSPR_CONF_OPT += --enable-thumb2
else
LIBNSPR_CONF_OPT += --disable-thumb2
endif
endif


libnspr-binary:
	tar -xjvf $(LIBNSPR_BINARY_DIR)/$(LIBNSPR_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(LIBNSPR_BINARY_DIR)/$(LIBNSPR_BINARY_SOURCE) -C $(TARGET_DIR)/
	rm -f $(TARGET_DIR)/usr/bin/compile-et.pl
	rm -f $(TARGET_DIR)/usr/bin/prerr.properties
	rm -f $(TARGET_DIR)/usr/bin/nspr-config


ifeq ($(wildcard $(LIBNSPR_INSTALL_BINARY)),)
libnspr: $(eval $(call AUTOTARGETS,package,libnspr))
else
libnspr: libnspr-binary
endif

libnspr-binary-clean:
	rm $(LIBNSPR_INSTALL_BINARY)

ifeq ($(BR2_PACKAGE_LIBNSPR),y)
TARGETS+=libnspr
endif
