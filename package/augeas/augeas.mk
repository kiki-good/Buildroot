#############################################################
#
# augeas
#
#############################################################
AUGEAS_VERSION = 1.2.0
AUGEAS_SOURCE = augeas-$(AUGEAS_VERSION).tar.gz
AUGEAS_SITE = http://download.augeas.net/
AUGEAS_INSTALL_STAGING = YES
AUGEAS_INSTALL_TARGET = YES
AUGEAS_DIR=$(BUILD_DIR)/augeas-$(AUGEAS_VERSION)
AUGEAS_BINARY_SOURCE:=augeas-$(AUGEAS_VERSION)-binary.tar.bz2
AUGEAS_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
AUGEAS_BINARY_DIR:=$(AUGEAS_BOARD_PATH)/binaries
AUGEAS_INSTALL_BINARY:=$(AUGEAS_BINARY_DIR)/$(AUGEAS_BINARY_SOURCE)
AUGEAS_TEMP_DIR:=$(AUGEAS_BINARY_DIR)/augeas_tmp


ifneq ($(BR2_LARGEFILE),y)
AUGEAS_CONF_ENV = CC="$(TARGET_CC) $(TARGET_CFLAGS) -DNO_LARGEFILE_SOURCE"
endif

AUGEAS_CONF_ENV += LIBXML_CFLAGS="-I$(STAGING_DIR)/usr/include/libxml2"
AUGEAS_CONF_ENV += LIBXML_LIBS="-L$(STAGING_DIR)/usr/lib -lxml2"

AUGEAS_CONF_OPT = --disable-static

AUGEAS_DEPENDENCIES = libiconv zlib libxml2 readline



define AUGEAS_POST_INSTALL
        rm -rf $(TARGET_DIR)/usr/share/augeas/
	rm -rf $(TARGET_DIR)/usr/share/vim/
        touch $@
endef

define AUGEAS_POST_INSTALL_PREBUILT_BINARIES
	mkdir -p $(AUGEAS_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(AUGEAS_TEMP_DIR) -C $(AUGEAS_DIR) install
	tar cjvf $(AUGEAS_BINARY_DIR)/$(AUGEAS_BINARY_SOURCE) -C $(AUGEAS_TEMP_DIR) .
	rm -rf $(AUGEAS_TEMP_DIR)
endef

AUGEAS_POST_INSTALL_HOOKS += AUGEAS_POST_INSTALL
AUGEAS_POST_INSTALL_TARGET_HOOKS += AUGEAS_POST_INSTALL
AUGEAS_POST_INSTALL_STAGING_HOOKS += AUGEAS_POST_INSTALL_PREBUILT_BINARIES

augeas-binary:
	tar -xjvf $(AUGEAS_BINARY_DIR)/$(AUGEAS_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(AUGEAS_BINARY_DIR)/$(AUGEAS_BINARY_SOURCE) -C $(TARGET_DIR)/
	rm -rf $(TARGET_DIR)/usr/share/augeas/
	rm -rf $(TARGET_DIR)/usr/share/vim
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L/$(STAGING_DIR)/usr/lib \
        $(STAGING_DIR)/usr/lib/libfa.la $(STAGING_DIR)/usr/lib/libxml2.la -ldl -lz \
	$(STAGING_DIR)/usr/lib/libiconv.la -L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib -lm',g" \
	$(STAGING_DIR)/usr/lib/libaugeas.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L/$(STAGING_DIR)/usr/lib',g" $(STAGING_DIR)/usr/lib/libfa.la
	$(SED) "s,^libdir=.*,libdir\='$(STAGING_DIR)/usr/lib',g" $(STAGING_DIR)/usr/lib/libaugeas.la
	$(SED) "s,^libdir=.*,libdir\='$(STAGING_DIR)/usr/lib',g" $(STAGING_DIR)/usr/lib/libfa.la

augeas-binary-clean: 
	rm $(AUGEAS_INSTALL_BINARY)

ifeq ($(wildcard $(AUGEAS_INSTALL_BINARY)),)
augeas: $(eval $(call AUTOTARGETS,package,augeas))
else
augeas: augeas-binary
endif

ifeq ($(BR2_PACKAGE_AUGEAS),y)
TARGETS+=augeas
endif

