#############################################################
#
# netcf
#
#############################################################
NETCF_VERSION = 0.2.3
NETCF_SOURCE = netcf-$(NETCF_VERSION).tar.gz
NETCF_SITE = https://fedorahosted.org/released/netcf/
NETCF_INSTALL_STAGING = YES
NETCF_INSTALL_TARGET = YES
NETCF_DIR=$(BUILD_DIR)/netcf-$(NETCF_VERSION)
NETCF_BINARY_SOURCE:=netcf-$(NETCF_VERSION)-binary.tar.bz2
NETCF_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
NETCF_BINARY_DIR:=$(NETCF_BOARD_PATH)/binaries
NETCF_INSTALL_BINARY:=$(NETCF_BINARY_DIR)/$(NETCF_BINARY_SOURCE)
NETCF_TEMP_DIR:=$(NETCF_BINARY_DIR)/netcf_tmp


ifneq ($(BR2_LARGEFILE),y)
NETCF_CONF_ENV = CC="$(TARGET_CC) $(TARGET_CFLAGS) -DNO_LARGEFILE_SOURCE"
endif

NETCF_CONF_ENV += LIBNL_CFLAGS="-I$(STAGING_DIR)/usr/include/libnl3"
NETCF_CONF_ENV += LIBNL_LIBS="-L$(STAGING_DIR)/usr/lib -lnl-3"

# NETCF_CONF_ENV += LIBXSLT_CFLAGS="-I$(STAGING_DIR)/usr/include/libxslt"
# NETCF_CONF_ENV += LIBXSLT_LIBS="-L$(STAGING_DIR)/usr/lib -lxslt"

# NETCF_CONF_ENV += LIBEXSLT_CFLAGS="-I$(STAGING_DIR)/usr/include/libexslt"
# NETCF_CONF_ENV += LIBEXSLT_LIBS="-L$(STAGING_DIR)/usr/lib -lexslt"

NETCF_CONF_OPT = --disable-static

NETCF_DEPENDENCIES = uclibc augeas libxslt libnl

define NETCF_POST_INSTALL
        rm -rf $(TARGET_DIR)/usr/share/netcf/
        touch $@
endef
define NETCF_POST_INSTALL_PREBUILT_BINARIES
	mkdir -p $(NETCF_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(NETCF_TEMP_DIR) -C $(NETCF_DIR) install
	tar cjvf $(NETCF_BINARY_DIR)/$(NETCF_BINARY_SOURCE) -C $(NETCF_TEMP_DIR) .
	rm -rf $(NETCF_TEMP_DIR)
endef


NETCF_POST_INSTALL += NETCF_POST_INSTALL
NETCF_POST_INSTALL_STAGING_HOOKS += NETCF_POST_INSTALL_PREBUILT_BINARIES

netcf-binary:
	tar -xjvf $(NETCF_BINARY_DIR)/$(NETCF_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(NETCF_BINARY_DIR)/$(NETCF_BINARY_SOURCE) -C $(TARGET_DIR)/
	rm -rf $(TARGET_DIR)/usr/share/netcf/
ifeq ($(BR2_SKY_BUILD_TYPE),"prod")
	mkdir -p $(TARGET_DIR)/etc/rc.d/init.d
	cp -av package/netcf/netcf-transaction $(TARGET_DIR)/etc/rc.d/init.d/
endif
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/lib/libaugeas.la -L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/lib/libfa.la -L$(STAGING_DIR)/usr/lib $(STAGING_DIR)/usr/lib/libexslt.la \
	$(STAGING_DIR)/usr/lib/libxslt.la $(STAGING_DIR)/usr/lib/libgcrypt.la \
	$(STAGING_DIR)/usr/lib/libgpg-error.la $(STAGING_DIR)/usr/lib/libxslt.la \
	$(STAGING_DIR)/usr/lib/libxml2.la -ldl -lz $(STAGING_DIR)/usr/lib/libiconv.la -lm -lnl-3 -lpthread',g" \
	$(STAGING_DIR)/usr/lib/libnetcf.la 
	$(SED) "s,^libdir=.*,libdir\='$(STAGING_DIR)/usr/lib',g" $(STAGING_DIR)/usr/lib/libnetcf.la


ifeq ($(wildcard $(NETCF_INSTALL_BINARY)),)
netcf: $(eval $(call AUTOTARGETS,package,netcf))
else
netcf: netcf-binary
endif

netcf-binary-clean: 
	rm $(NETCF_INSTALL_BINARY)

ifeq ($(BR2_PACKAGE_NETCF),y)
TARGETS+=netcf
endif

