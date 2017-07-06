#############################################################
#
# ctemplate
#
#############################################################
CTEMPLATE_VERSION = 2.3
CTEMPLATE_SOURCE = ctemplate-$(CTEMPLATE_VERSION).tar.gz
CTEMPLATE_SITE = https://code.google.com/p/ctemplate/
CTEMPLATE_INSTALL_STAGING = YES
CTEMPLATE_INSTALL_TARGET = YES
CTEMPLATE_DIR=$(BUILD_DIR)/ctemplate-$(CTEMPLATE_VERSION)
CTEMPLATE_BINARY_SOURCE:=ctemplate-$(CTEMPLATE_VERSION)-binary.tar.bz2
CTEMPLATE_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
CTEMPLATE_BINARY_DIR:=$(CTEMPLATE_BOARD_PATH)/binaries
CTEMPLATE_INSTALL_BINARY:=$(CTEMPLATE_BINARY_DIR)/$(CTEMPLATE_BINARY_SOURCE)
CTEMPLATE_TEMP_DIR:=$(CTEMPLATE_BINARY_DIR)/ctemplate_tmp

define CTEMPLATE_POST_INSTALL_PREBUILT_BINARIES
	mkdir -p $(CTEMPLATE_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(CTEMPLATE_TEMP_DIR) -C $(CTEMPLATE_DIR) install
	tar cjvf $(CTEMPLATE_BINARY_DIR)/$(CTEMPLATE_BINARY_SOURCE) -C $(CTEMPLATE_TEMP_DIR) .
	rm -rf $(CTEMPLATE_TEMP_DIR)
endef

define CTEMPLATE_POST_INSTALL
	rm -rf $(TARGET_DIR)/usr/bin/make_tpl_varnames_h
	rm -rf $(TARGET_DIR)/usr/bin/diff_tpl_auto_escape
	rm -rf $(TARGET_DIR)/usr/bin/template-converter
	rm -rf $(TARGET_DIR)/usr/lib/libctemplate_nothreads*
	touch $@
endef
CTEMPLATE_POST_INSTALL_STAGING_HOOKS += CTEMPLATE_POST_INSTALL_PREBUILT_BINARIES
CTEMPLATE_POST_INSTALL_TARGET_HOOKS += CTEMPLATE_POST_INSTALL
ifneq ($(BR2_LARGEFILE),y)
CTEMPLATE_CONF_ENV = CC="$(TARGET_CC) $(TARGET_CFLAGS) -DNO_LARGEFILE_SOURCE"
endif

CTEMPLATE_CONF_OPT = \
		--without-threads \

#CTEMPLATE_DEPENDENCIES = netcf libcap-ng libcap-ng 

ctemplate-binary:
	tar -xjvf $(CTEMPLATE_BINARY_DIR)/$(CTEMPLATE_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(CTEMPLATE_BINARY_DIR)/$(CTEMPLATE_BINARY_SOURCE) -C $(TARGET_DIR)/
	rm -rf $(TARGET_DIR)/usr/bin/make_tpl_varnames_h
	rm -rf $(TARGET_DIR)/usr/bin/diff_tpl_auto_escape
	rm -rf $(TARGET_DIR)/usr/bin/template-converter
	rm -rf $(TARGET_DIR)/usr/lib/libctemplate_nothreads*

ifeq ($(wildcard $(CTEMPLATE_INSTALL_BINARY)),)
ctemplate: $(eval $(call AUTOTARGETS,package,ctemplate))
else
ctemplate: ctemplate-binary
endif

ctemplate-binary-clean: 
	rm $(CTEMPLATE_INSTALL_BINARY)

ifeq ($(BR2_PACKAGE_CTEMPLATE),y)
TARGETS+=ctemplate
endif
