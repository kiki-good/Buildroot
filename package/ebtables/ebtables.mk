#############################################################
#
# ebtables
#
#############################################################

EBTABLES_VERSION = 2.0.10-4
EBTABLES_SOURCE = ebtables-v$(EBTABLES_VERSION).tar.gz
EBTABLES_SITE = http://localhost
EBTABLES_CAT = $(ZCAT)
EBTABLES_DIR = $(BUILD_DIR)/ebtables-v$(EBTABLES_VERSION)
EBTABLES_STATIC = static
EBTABLES_BINARY = ebtables
EBTABLES_TARGET_BINARY = usr/sbin/ebtables




$(DL_DIR)/$(EBTABLES_SOURCE):
	$(WGET) -P $(DL_DIR) $(EBTABLES_SITE)/$(EBTABLES_SOURCE)

ebtables-source: $(DL_DIR)/$(EBTABLES_SOURCE)

$(EBTABLES_DIR)/.unpacked: $(DL_DIR)/$(EBTABLES_SOURCE)
	$(EBTABLES_CAT) $(DL_DIR)/$(EBTABLES_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(EBTABLES_DIR) package/ebtables/ ebtables-$(EBTABLES_VERSION)\*.patch
	touch $(EBTABLES_DIR)/.unpacked

$(EBTABLES_DIR)/.configured: $(EBTABLES_DIR)/.unpacked
	touch $@

$(EBTABLES_DIR)/$(EBTABLES_STATIC): $(EBTABLES_DIR)/.configured
	$(MAKE) $(TARGET_CONFIGURE_OPTS) LIBDIR=/lib/ebtables $(EBTABLES_STATIC) \
		CFLAGS="$(TARGET_CFLAGS)" -C $(EBTABLES_DIR)

$(TARGET_DIR)/$(EBTABLES_TARGET_BINARY): $(EBTABLES_DIR)/$(EBTABLES_STATIC)
	$(INSTALL) -m 0755 -D $(EBTABLES_DIR)/$(EBTABLES_STATIC) $(TARGET_DIR)/$(EBTABLES_TARGET_BINARY)
	$(INSTALL) -m 0644 -D $(EBTABLES_DIR)/ethertypes $(TARGET_DIR)/etc/ethertypes


ebtables: uclibc $(TARGET_DIR)/$(EBTABLES_TARGET_BINARY)

ebtables-clean:
	-$(MAKE) -C $(EBTABLES_DIR) clean

ebtables-dirclean:
	rm -rf $(EBTABLES_DIR)


#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_EBTABLES),y)
TARGETS+=ebtables
endif





