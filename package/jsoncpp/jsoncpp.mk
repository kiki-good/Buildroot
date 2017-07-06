################################################################################
#
# jsoncpp
#
################################################################################

JSONCPP_VERSION = 1.7.2-amalagated
JSONCPP_FILE = jsoncpp-$(JSONCPP_VERSION).tar.gz
JSONCPP_SITE = https://localhost/
JSONCPP_LICENSE = Public Domain or MIT
JSONCPP_LICENSE_FILES = LICENSE
JSONCPP_INSTALL_STAGING = YES
JSONCPP_INSTALL_TARGET = YES
JSONCPP_DIR=$(BUILD_DIR)/jsoncpp-$(JSONCPP_VERSION)
JSONCPP_BINARY_SOURCE:=jsoncpp-$(JSONCPP_VERSION)-binary.tar.bz2
JSONCPP_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
JSONCPP_BINARY_DIR:=$(JSONCPP_BOARD_PATH)/binaries
JSONCPP_INSTALL_BINARY:=$(JSONCPP_BINARY_DIR)/$(JSONCPP_BINARY_SOURCE)
JSONCPP_TEMP_DIR:=$(JSONCPP_BINARY_DIR)/jsoncpp_tmp


define JSONCPP_BUILD_CMDS
	$(MAKE) CXX=$(TARGET_CXX) LD=$(TARGET_LD) -C $(@D) all
endef

define JSONCPP_CLEAN_CMDS
	$(MAKE) CXX=$(TARGET_CXX) LD=$(TARGET_LD) -C $(@D) clean
endef

define JSONCPP_INSTALL_STAGING_CMDS
	$(INSTALL) -D -m 0755 $(@D)/libjsoncpp.so* $(STAGING_DIR)/usr/lib
	$(INSTALL) -D -m 0755 -d $(STAGING_DIR)/usr/include/jsoncpp
	$(INSTALL) -D -m 0644 $(@D)/json/* $(STAGING_DIR)/usr/include/jsoncpp
	mkdir -p $(JSONCPP_TEMP_DIR)
	mkdir -p $(JSONCPP_TEMP_DIR)/usr/lib
	$(INSTALL) -D -m 0755 $(@D)/libjsoncpp.so* $(JSONCPP_TEMP_DIR)/usr/lib
	$(INSTALL) -D -m 0755 -d $(JSONCPP_TEMP_DIR)/usr/include/jsoncpp
	$(INSTALL) -D -m 0644 $(@D)/json/* $(JSONCPP_TEMP_DIR)/usr/include/jsoncpp
	tar cjvf $(JSONCPP_BINARY_DIR)/$(JSONCPP_BINARY_SOURCE) -C $(JSONCPP_TEMP_DIR) .
	rm -rf $(JSONCPP_TEMP_DIR)
endef

define JSONCPP_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/libjsoncpp.so* $(TARGET_DIR)/usr/lib
endef

jsoncpp-binary:
	tar -xjvf $(JSONCPP_BINARY_DIR)/$(JSONCPP_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(JSONCPP_BINARY_DIR)/$(JSONCPP_BINARY_SOURCE) -C $(TARGET_DIR)/


ifeq ($(wildcard $(JSONCPP_INSTALL_BINARY)),)
$(eval $(call GENTARGETS,package,jsoncpp))
else
jsoncpp: jsoncpp-binary
endif

jsoncpp-binary-clean:
	rm $(JSONCPP_INSTALL_BINARY)

ifeq ($(BR2_PACKAGE_JSONCPP),y)
TARGETS+=jsoncpp
endif

