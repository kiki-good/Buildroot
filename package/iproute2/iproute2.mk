#############################################################
#
# iproute2
#
#############################################################
IPROUTE2_VERSION:=3.18.0
IPROUTE2_SOURCE:=iproute2-$(IPROUTE2_VERSION).tar.gz
IPROUTE2_SITE:=http://localhost
IPROUTE2_DIR:=$(BUILD_DIR)/iproute2-$(IPROUTE2_VERSION)
IPROUTE2_CAT:=$(ZCAT)
IPROUTE2_BINARY:=tc/tc
IPROUTE2_TARGET_BINARY:=sbin/tc

$(DL_DIR)/$(IPROUTE2_SOURCE):
	$(WGET) -P $(DL_DIR) $(IPROUTE2_SITE)$(IPROUTE2_SOURCE)

iproute2-source: $(DL_DIR)/$(IPROUTE2_SOURCE)

$(IPROUTE2_DIR)/.unpacked: $(DL_DIR)/$(IPROUTE2_SOURCE)
	$(IPROUTE2_CAT) $(DL_DIR)/$(IPROUTE2_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(IPROUTE2_DIR) package/iproute2/ iproute2-$(IPROUTE2_VERSION)\*.patch
	touch $(IPROUTE2_DIR)/.unpacked

$(IPROUTE2_DIR)/.configured: $(IPROUTE2_DIR)/.unpacked
	(cd $(IPROUTE2_DIR); \
		$(SED) 's/gcc/$$CC $$CFLAGS/g' ./configure; \
		$(TARGET_CONFIGURE_OPTS) ./configure; \
		$(SED) 's/-Werror//' Makefile; \
		echo "IPT_LIB_DIR:=/usr/lib/xtables" >> Config; \
		$(SED) "/^TARGETS=/s: arpd : :" misc/Makefile; \
		echo "TC_CONFIG_IPSET:=n" >> Config)
	touch $(IPROUTE2_DIR)/.configured

$(IPROUTE2_DIR)/$(IPROUTE2_BINARY): $(IPROUTE2_DIR)/.configured
	$(SED) 's/$$(CCOPTS)//' $(IPROUTE2_DIR)/netem/Makefile
	$(MAKE) \
		-C $(IPROUTE2_DIR) \
		KERNEL_INCLUDE=$(LINUX_SOURCE_DIR)/include \
		DBM_INCLUDE="$(STAGING_DIR)/usr/include" \
		CC=$(TARGET_CC) \
		AR=$(TARGET_CROSS)ar \
		NETEM_DIST="" \
		SUBDIRS="lib tc ip"

$(TARGET_DIR)/$(IPROUTE2_TARGET_BINARY): $(IPROUTE2_DIR)/$(IPROUTE2_BINARY)
	install -Dc $(IPROUTE2_DIR)/ip/ip $(TARGET_DIR)/sbin/ip
	install -Dc $(IPROUTE2_DIR)/$(IPROUTE2_BINARY) $(TARGET_DIR)/$(IPROUTE2_TARGET_BINARY)

iproute2: $(TARGET_DIR)/$(IPROUTE2_TARGET_BINARY)

iproute2-clean:
	rm -f $(TARGET_DIR)/$(IPROUTE2_TARGET_BINARY)
	-$(MAKE) -C $(IPROUTE2_DIR) clean

iproute2-dirclean:
	rm -rf $(IPROUTE2_DIR)
#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_IPROUTE2),y)
TARGETS+=iproute2
endif
