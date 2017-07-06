################################################################################
#
# iftop
#
################################################################################

IFTOP_VERSION = 0.17
IFTOP_SITE = http://local-host
IFTOP_INSTALL_STAGING = YES
IFTOP_SOURCE:=iftop-$(IFTOP_VERSION).tar.gz
# IFTOP_DEPENDENCIES = host-bison host-flex

IFTOP_DIR=$(BUILD_DIR)/iftop-$(IFTOP_VERSION)
IFTOP_BINARY_SOURCE:=iftop-$(IFTOP_VERSION)-binary.tar.bz2
IFTOP_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
IFTOP_BINARY_DIR:=$(IFTOP_BOARD_PATH)/binaries
IFTOP_INSTALL_BINARY:=$(IFTOP_BINARY_DIR)/$(IFTOP_BINARY_SOURCE)
IFTOP_TEMP_DIR:=$(IFTOP_BINARY_DIR)/iftop_tmp

IFTOP_DEPENDENCIES = libpcap ncurses

define IFTOP_POST_INSTALL_PREBUILT_BINARIES
	mkdir -p $(IFTOP_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(IFTOP_TEMP_DIR) -C $(IFTOP_DIR) install
	tar cjvf $(IFTOP_BINARY_DIR)/$(IFTOP_BINARY_SOURCE) -C $(IFTOP_TEMP_DIR) .
	rm -rf $(IFTOP_TEMP_DIR)
endef

IFTOP_POST_INSTALL_STAGING_HOOKS += IFTOP_POST_INSTALL_PREBUILT_BINARIES

iftop-binary:
	tar -xjvf $(IFTOP_BINARY_DIR)/$(IFTOP_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(IFTOP_BINARY_DIR)/$(IFTOP_BINARY_SOURCE) -C $(TARGET_DIR)/


ifeq ($(wildcard $(IFTOP_INSTALL_BINARY)),)
iftop: $(eval $(call AUTOTARGETS,package,iftop))
else
iftop: libpcap ncurses iftop-binary
endif

iftop-binary-clean:
	rm $(IFTOP_INSTALL_BINARY)

ifeq ($(BR2_PACKAGE_IFTOP),y)
TARGETS+=iftop
endif


