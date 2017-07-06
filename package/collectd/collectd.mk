################################################################################
#
# collectd
#
################################################################################

COLLECTD_VERSION = 5.4.1
COLLECTD_SITE = http://local-host
COLLECTD_INSTALL_STAGING = YES
COLLECTD_SOURCE:=collectd-$(COLLECTD_VERSION).tar.bz2

COLLECTD_DIR=$(BUILD_DIR)/collectd-$(COLLECTD_VERSION)
COLLECTD_BINARY_SOURCE:=collectd-$(COLLECTD_VERSION)-binary.tar.bz2
COLLECTD_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
COLLECTD_BINARY_DIR:=$(COLLECTD_BOARD_PATH)/binaries
COLLECTD_INSTALL_BINARY:=$(COLLECTD_BINARY_DIR)/$(COLLECTD_BINARY_SOURCE)
COLLECTD_TEMP_DIR:=$(COLLECTD_BINARY_DIR)/collectd_tmp

COLLECTD_CONF_OPT += --with-fp-layout=nothing --with-perl-bindings=no

define COLLECTD_POST_INSTALL_PREBUILT_BINARIES
	mkdir -p $(COLLECTD_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(COLLECTD_TEMP_DIR) -C $(COLLECTD_DIR) install
	tar cjvf $(COLLECTD_BINARY_DIR)/$(COLLECTD_BINARY_SOURCE) -C $(COLLECTD_TEMP_DIR) .
	rm -rf $(COLLECTD_TEMP_DIR)
	mkdir -p $(TARGET_DIR)/etc/
	cp package/collectd/collectd.conf $(TARGET_DIR)/etc/
endef

COLLECTD_POST_INSTALL_TARGET_HOOKS += COLLECTD_POST_INSTALL_PREBUILT_BINARIES

collectd-binary:
	tar -xjvf $(COLLECTD_BINARY_DIR)/$(COLLECTD_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(COLLECTD_BINARY_DIR)/$(COLLECTD_BINARY_SOURCE) -C $(TARGET_DIR)/
	mkdir -p $(TARGET_DIR)/etc/
	cp package/collectd/collectd.conf $(TARGET_DIR)/etc/

ifeq ($(wildcard $(COLLECTD_INSTALL_BINARY)),)
collectd: $(eval $(call AUTOTARGETS,package,collectd))
else
collectd: collectd-binary
endif

collectd-binary-clean:
	rm $(COLLECTD_INSTALL_BINARY)

ifeq ($(BR2_PACKAGE_COLLECTD),y)
TARGETS+=collectd
endif


