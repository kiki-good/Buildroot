################################################################################
#
# libnl
#
################################################################################

LIBNL_VERSION = 3.2.25
LIBNL_MAIN_VERSION = 3
LIBNL_SITE = http://localhost/
LIBNL_LICENSE = LGPLv2.1+
LIBNL_LICENSE_FILES = COPYING
LIBNL_INSTALL_STAGING = YES
LIBNL_LIBRARY_VERSION = 200.20.0
# LIBNL_DEPENDENCIES = host-bison host-flex

LIBNL_DIR=$(BUILD_DIR)/libnl-$(LIBNL_VERSION)
LIBNL_BINARY_SOURCE:=libnl-$(LIBNL_VERSION)-binary.tar.bz2
LIBNL_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
LIBNL_BINARY_DIR:=$(LIBNL_BOARD_PATH)/binaries
LIBNL_INSTALL_BINARY:=$(LIBNL_BINARY_DIR)/$(LIBNL_BINARY_SOURCE)
LIBNL_TEMP_DIR:=$(LIBNL_BINARY_DIR)/libnl_tmp

define LIBNL_POST_INSTALL_PREBUILT_BINARIES
	mkdir -p $(LIBNL_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(LIBNL_TEMP_DIR) -C $(LIBNL_DIR) install
	(cd $(LIBNL_TEMP_DIR)/usr/lib; ln -snf libnl-$(LIBNL_MAIN_VERSION).so.$(LIBNL_LIBRARY_VERSION) libnl.so)
	(cd $(LIBNL_TEMP_DIR)/usr/lib; ln -snf libnl-$(LIBNL_MAIN_VERSION).so.$(LIBNL_LIBRARY_VERSION) libnl.so.1)
	tar cjvf $(LIBNL_BINARY_DIR)/$(LIBNL_BINARY_SOURCE) -C $(LIBNL_TEMP_DIR) .
	rm -rf $(LIBNL_TEMP_DIR)
	(cd $(TARGET_DIR)/usr/lib; ln -snf libnl-$(LIBNL_MAIN_VERSION).so.$(LIBNL_LIBRARY_VERSION) libnl.so)
	(cd $(TARGET_DIR)/usr/lib; ln -snf libnl-$(LIBNL_MAIN_VERSION).so.$(LIBNL_LIBRARY_VERSION) libnl.so.1)
endef

LIBNL_POST_INSTALL_TARGET_HOOKS += LIBNL_POST_INSTALL_PREBUILT_BINARIES

ifeq ($(BR2_PACKAGE_LIBNL_TOOLS),y)
LIBNL_CONF_OPT += --enable-cli
else
LIBNL_CONF_OPT += --disable-cli
endif


libnl-binary:
	tar -xjvf $(LIBNL_BINARY_DIR)/$(LIBNL_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(LIBNL_BINARY_DIR)/$(LIBNL_BINARY_SOURCE) -C $(TARGET_DIR)/
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/lib/libnl-route-3.la $(STAGING_DIR)/usr/lib/libnl-3.la -lpthread -lm',g" \
	$(STAGING_DIR)/usr/lib/libnl-nf-3.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/lib/libnl-3.la -lpthread -lm',g" $(STAGING_DIR)/usr/lib/libnl-idiag-3.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/lib/libnl-3.la -lpthread -lm',g" $(STAGING_DIR)/usr/lib/libnl-genl-3.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/lib/libnl-3.la -lpthread -lm',g" $(STAGING_DIR)/usr/lib/libnl-route-3.la
	(cd $(TARGET_DIR)/usr/lib; ln -snf libnl-$(LIBNL_MAIN_VERSION).so.$(LIBNL_LIBRARY_VERSION) libnl.so)
	(cd $(TARGET_DIR)/usr/lib; ln -snf libnl-$(LIBNL_MAIN_VERSION).so.$(LIBNL_LIBRARY_VERSION) libnl.so.1)

ifeq ($(wildcard $(LIBNL_INSTALL_BINARY)),)
libnl: $(eval $(call AUTOTARGETS,package,libnl))
else
libnl: libnl-binary
endif

libnl-binary-clean:
	rm $(LIBNL_INSTALL_BINARY)

ifeq ($(BR2_PACKAGE_LIBNL),y)
TARGETS+=libnl
endif


