################################################################################
#
# icu
#
################################################################################

ICU_VERSION = 56.1
ICU_SOURCE = icu4c-$(subst .,_,$(ICU_VERSION))-src.tgz
ICU_SITE = http://localhost/
ICU_LICENSE = ICU License
ICU_LICENSE_FILES = license.html

ICU_DEPENDENCIES = host-icu
ICU_INSTALL_STAGING = YES
ICU_CONFIG_SCRIPTS = icu-config
ICU_CONF_OPT = \
	--with-cross-build=$(HOST_ICU_DIR)/source \
	--disable-samples \
	--disable-tests \
	--disable-tools
HOST_ICU_CONF_OPTS = \
	--disable-samples \
	--disable-tests \
	--disable-extras \
	--disable-icuio \
	--disable-layout \
	--disable-renaming
ICU_MAKE = $(MAKE1)
ICU_SUBDIR = source
HOST_ICU_SUBDIR = source
HOST_ICU_INSTALL_HOST = NO

ICU_DIR=$(BUILD_DIR)/icu-$(ICU_VERSION)
ICU_BINARY_SOURCE:=icu-$(ICU_VERSION)-binary.tar.bz2
ICU_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
ICU_BINARY_DIR:=$(ICU_BOARD_PATH)/binaries
ICU_INSTALL_BINARY:=$(ICU_BINARY_DIR)/$(ICU_BINARY_SOURCE)
ICU_TEMP_DIR:=$(ICU_BINARY_DIR)/icu_tmp

define ICU_POST_INSTALL_PREBUILT_BINARIES
        mkdir -p $(ICU_TEMP_DIR)
        $(MAKE) DESTDIR=$(PWD)/$(ICU_TEMP_DIR) -C $(ICU_DIR)/$(ICU_SUBDIR) install
	rm -rf $(ICU_TEMP_DIR)/usr/share
	rm -rf $(ICU_TEMP_DIR)/usr/sbin
	rm -rf $(ICU_TEMP_DIR)/usr/bin
        tar cjvf $(ICU_BINARY_DIR)/$(ICU_BINARY_SOURCE) -C $(ICU_TEMP_DIR) .
	rm -rf $(ICU_TEMP_DIR)
endef

ICU_CUSTOM_DATA_PATH = $(strip $(subst ",,$(BR2_PACKAGE_ICU_CUSTOM_DATA_PATH)))
ICU_DATA_FILE_NAME = "icudt$(firstword $(subst ., ,$(ICU_VERSION)))l.dat"

ifneq ($(ICU_CUSTOM_DATA_PATH),)
define ICU_COPY_CUSTOM_DATA
	cp $(ICU_CUSTOM_DATA_PATH) $(@D)/source/data/in/$(ICU_DATA_FILE_NAME)
endef
ICU_POST_PATCH_HOOKS += ICU_COPY_CUSTOM_DATA
endif

ICU_POST_INSTALL_STAGING_HOOKS += ICU_POST_INSTALL_PREBUILT_BINARIES

icu-binary:
	tar -xjvf $(ICU_BINARY_DIR)/$(ICU_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(ICU_BINARY_DIR)/$(ICU_BINARY_SOURCE) -C $(TARGET_DIR)/
	rm -rf $(TARGET_DIR)/usr/lib/icu

icu-host: $(eval $(call AUTOTARGETS,package,icu,host))

ifeq ($(wildcard $(ICU_INSTALL_BINARY)),)
icu: icu-host $(eval $(call AUTOTARGETS,package,icu))
else
icu: icu-binary
endif


#############################################################
#
## Toplevel Makefile options
#
##############################################################
ifeq ($(BR2_PACKAGE_ICU),y)
TARGETS+=icu
endif

