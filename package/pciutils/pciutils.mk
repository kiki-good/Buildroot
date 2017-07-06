#############################################################
#
# pciutils
#
#############################################################
PCIUTILS_VERSION:=2.2.10
PCIUTILS_SOURCE:=pciutils-$(PCIUTILS_VERSION).tar.gz
PCIUTILS_CAT:=$(ZCAT)
PCIUTILS_SITE:=ftp://atrey.karlin.mff.cuni.cz/pub/linux/pci
PCIUTILS_DIR:=$(BUILD_DIR)/pciutils-$(PCIUTILS_VERSION)

# Yet more targets...
PCIIDS_SITE:=http://pciids.sourceforge.net/
PCIIDS_SOURCE:=pci.ids.bz2
PCIIDS_CAT:=$(BZCAT)

ifeq ($(BR2_PACKAGE_ZLIB),y)
PCIUTILS_HAVE_ZLIB=yes
PCIIDS_FILE=pci.ids.gz
else
PCIUTILS_HAVE_ZLIB=no
PCIIDS_FILE=pci.ids
endif

$(DL_DIR)/$(PCIUTILS_SOURCE):
	 $(WGET) -P $(DL_DIR) $(PCIUTILS_SITE)/$(PCIUTILS_SOURCE)

$(DL_DIR)/$(PCIIDS_SOURCE):
	$(WGET) -P $(DL_DIR) $(PCIIDS_SITE)/$(PCIIDS_SOURCE)

$(PCIUTILS_DIR)/.unpacked: $(DL_DIR)/$(PCIUTILS_SOURCE) $(DL_DIR)/$(PCIIDS_SOURCE)
	$(PCIUTILS_CAT) $(DL_DIR)/$(PCIUTILS_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	$(PCIIDS_CAT) $(DL_DIR)/$(PCIIDS_SOURCE) > $(PCIUTILS_DIR)/$(PCIIDS_FILE)
	toolchain/patch-kernel.sh $(PCIUTILS_DIR) package/pciutils pciutils-$(PCIUTILS_VERSION)\*.patch
	$(SED) 's/uname -s/echo Linux/' \
		-e 's/uname -r/echo $(LINUX_HEADERS_VERSION)/' \
		$(PCIUTILS_DIR)/lib/configure
	-mkdir $(TARGET_DIR)/sbin
	touch $@

$(PCIUTILS_DIR)/.compiled: $(PCIUTILS_DIR)/.unpacked
	$(MAKE1) CC="$(TARGET_CC)" OPT="$(TARGET_CFLAGS)" -C $(PCIUTILS_DIR) \
		HOST="$(GNU_TARGET_NAME)" \
		SHAREDIR="/usr/share/" \
		ZLIB=$(PCIUTILS_HAVE_ZLIB) \
		PREFIX=/usr \
		LDFLAGS=-L"$(STAGING_DIR)/usr/lib"
	touch $@

$(TARGET_DIR)/sbin/lspci: $(PCIUTILS_DIR)/.compiled
ifneq ($(BR2_SKY_BUILD_TYPE),"prod")
	cp $(PCIUTILS_DIR)/lspci $(TARGET_DIR)/sbin/lspci
endif

$(TARGET_DIR)/sbin/setpci: $(PCIUTILS_DIR)/.compiled
ifeq ($(BR2_SKY_BUILD_TYPE),"debug")
	cp $(PCIUTILS_DIR)/setpci $(TARGET_DIR)/sbin/setpci
endif

$(TARGET_DIR)/usr/share/$(PCIIDS_FILE): $(PCIUTILS_DIR)/.unpacked
ifeq ($(BR2_SKY_BUILD_TYPE),"debug")
	cp -drf $(PCIUTILS_DIR)/$(PCIIDS_FILE) $(@D)
endif

pciutils: zlib $(if $(BR2_PACKAGE_ZLIB),zlib) $(TARGET_DIR)/sbin/setpci $(TARGET_DIR)/sbin/lspci $(TARGET_DIR)/usr/share/$(PCIIDS_FILE)

pciutils-source: $(DL_DIR)/$(PCIUTILS_SOURCE) $(DL_DIR)/$(PCIIDS_SOURCE)

pciutils-clean:
	-$(MAKE) -C $(PCIUTILS_DIR) clean
	rm -f $(TARGET_DIR)/sbin/lspci $(TARGET_DIR)/sbin/setpci $(TARGET_DIR)/usr/share/pci.ids*

pciutils-dirclean:
	rm -rf $(PCIUTILS_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_PCIUTILS),y)
TARGETS+=pciutils
endif
