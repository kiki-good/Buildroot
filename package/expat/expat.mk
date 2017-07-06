#############################################################
#
# expat
#
#############################################################
ifeq ($(BR2_ARCH_IS_64),y)
EXPAT_VERSION=2.2.0
else
EXPAT_VERSION=2.1.0
endif
EXPAT_SOURCE=expat-$(EXPAT_VERSION).tar.gz
EXPAT_BINARY_SOURCE:=expat-$(EXPAT_VERSION)-binary.tar.bz2
EXPAT_CAT:=$(ZCAT)
EXPAT_SITE=http://$(BR2_SOURCEFORGE_MIRROR).dl.sourceforge.net/sourceforge/expat
EXPAT_DIR:=$(BUILD_DIR)/expat-$(EXPAT_VERSION)
EXPAT_HOST_DIR:=$(TOOL_BUILD_DIR)/expat-$(EXPAT_VERSION)-host
EXPAT_BINARY:=.libs/libexpat.a
EXPAT_TARGET_BINARY:=usr/lib/libexpat.so.1
EXPAT_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
EXPAT_BINARY_DIR:=$(EXPAT_BOARD_PATH)/binaries
EXPAT_INSTALL_BINARY:=$(EXPAT_BINARY_DIR)/$(EXPAT_BINARY_SOURCE)
EXPAT:=$(STAGING_DIR)/usr/lib/libexpat.so.1
EXPAT_STAGING_HOST:=$(STAGING_DIR)/host/expat-$(EXPAT_VERSION)
EXPAT_SRC_DIR:=$(TOOL_BUILD_DIR)/expat-$(EXPAT_VERSION)

$(DL_DIR)/$(EXPAT_SOURCE):
	$(WGET) -P $(DL_DIR) $(EXPAT_SITE)/$(EXPAT_SOURCE)

expat-source: $(DL_DIR)/$(EXPAT_SOURCE)

$(EXPAT_SRC_DIR)/.unpacked: $(DL_DIR)/$(EXPAT_SOURCE)
	$(EXPAT_CAT) $(DL_DIR)/$(EXPAT_SOURCE) | \
		tar -C $(TOOL_BUILD_DIR) $(TAR_OPTIONS) -
ifneq ($(BR2_ARCH_IS_64),y)
	toolchain/patch-kernel.sh $(EXPAT_SRC_DIR) package/expat/ \*.patch
else
	toolchain/patch-kernel.sh $(EXPAT_SRC_DIR) package/expat/64bitPatch expat-$(EXPAT_VERSION)\*.patch*
endif

ifneq ($(BR2_ARCH_IS_64),y)
	$(CONFIG_UPDATE) $(EXPAT_SRC_DIR)/
	$(CONFIG_UPDATE) $(EXPAT_SRC_DIR)/conftools
endif
	touch $@

#############################################################
#
## expat for the target
#
##############################################################

$(EXPAT_DIR)/.configured: $(EXPAT_SRC_DIR)/.unpacked
	mkdir -p $(EXPAT_DIR)
	(cd $(EXPAT_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		$(EXPAT_SRC_DIR)/configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--prefix=/usr \
		--exec-prefix=/usr \
		--sysconfdir=/etc \
		--localstatedir=/var \
		--enable-shared \
	)
	touch $@

$(EXPAT_DIR)/$(EXPAT_BINARY): $(EXPAT_DIR)/.configured
	$(MAKE) -C $(EXPAT_DIR) all
	touch -c $@

$(STAGING_DIR)/$(EXPAT_TARGET_BINARY): $(EXPAT_DIR)/$(EXPAT_BINARY)
	$(MAKE) DESTDIR=$(STAGING_DIR) -C $(EXPAT_DIR) install
	mkdir -p $(EXPAT_BINARY_DIR)/expat_tmp
	$(MAKE) DESTDIR=$(PWD)/$(EXPAT_BINARY_DIR)/expat_tmp -C $(EXPAT_DIR) install
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/lib\',g" \
		$(STAGING_DIR)/usr/lib/libexpat.la
	touch -c $@

$(TARGET_DIR)/$(EXPAT_TARGET_BINARY): $(STAGING_DIR)/$(EXPAT_TARGET_BINARY)
	mkdir -p $(TARGET_DIR)/usr/lib
	cp -dpf $(STAGING_DIR)/usr/lib/libexpat.so* $(TARGET_DIR)/usr/lib/
	#cp -dpf $(STAGING_DIR)/usr/bin/xmlwf $(TARGET_DIR)/usr/bin/xmlwf	
	-$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libexpat.so*
	tar cjvf $(EXPAT_BINARY_DIR)/$(EXPAT_BINARY_SOURCE) -C $(EXPAT_BINARY_DIR)/expat_tmp .
	rm -rf $(EXPAT_BINARY_DIR)/expat_tmp
	touch -c $@

ifeq ($(wildcard $(EXPAT_INSTALL_BINARY)),)
expat: uclibc pkgconfig $(TARGET_DIR)/$(EXPAT_TARGET_BINARY)
else
expat: uclibc pkgconfig expat-binary
endif

expat-binary:
	tar -xjvf $(EXPAT_BINARY_DIR)/$(EXPAT_BINARY_SOURCE) -C $(STAGING_DIR)/
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/lib\',g" \
		$(STAGING_DIR)/usr/lib/libexpat.la
	mkdir -p $(TARGET_DIR)/usr/lib
	cp -dpf $(STAGING_DIR)/usr/lib/libexpat.so* $(TARGET_DIR)/usr/lib/

expat-clean:
	rm -f $(EXPAT_DIR)/.configured
	rm -f $(STAGING_DIR)/usr/lib/libexpat.* \
		$(TARGET_DIR)/usr/lib/libexpat.*
	#rm -f $(STAGING_DIR)/usr/bin/xmlwf $(TARGET_DIR)/usr/bin/xmlwf
	-$(MAKE) -C $(EXPAT_DIR) clean

expat-dirclean:
	rm -rf $(EXPAT_DIR)

expat-binary-clean:
	rm -rf $(EXPAT_INSTALL_BINARY)

#############################################################
#
## expat for the host
#
##############################################################

$(EXPAT_HOST_DIR)/.configured: $(EXPAT_SRC_DIR)/.unpacked
	mkdir -p $(EXPAT_HOST_DIR)
	mkdir -p $(EXPAT_STAGING_HOST)
	(cd $(EXPAT_HOST_DIR); rm -rf config.cache; \
                $(HOST_CONFIGURE_OPTS) \
                $(EXPAT_SRC_DIR)/configure \
	)
	touch $@

$(EXPAT_HOST_DIR)/$(EXPAT_BINARY): $(EXPAT_HOST_DIR)/.configured
	$(MAKE) -C $(EXPAT_HOST_DIR)
	$(MAKE) -C $(EXPAT_HOST_DIR) DESTDIR=$(EXPAT_STAGING_HOST) install
	touch -c $@


host-expat: $(EXPAT_HOST_DIR)/$(EXPAT_BINARY)

host-expat-clean:
	-$(MAKE) -C $(EXPAT_HOST_DIR) clean

host-expat-dirclean:
	rm -rf $(EXPAT_HOST_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_EXPAT),y)
TARGETS+=expat
endif
