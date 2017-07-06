#############################################################
#
# IPERF3
#
#############################################################
IPERF3_VERSION:=0.00
IPERF3_SITE:=https://localhost/
IPERF3_SOURCE:=iperf3-$(IPERF3_VERSION).tar.bz2
IPERF3_BINARY_SOURCE:=iperf3-$(IPERF3_VERSION).tar.bz2
IPERF3_DIR:=$(BUILD_DIR)/iperf3-$(IPERF3_VERSION)
IPERF3_CAT:=$(BZCAT) 
IPERF3_BINARY:=iperf3
IPERF3_TARGET_BINARY:=usr/bin/iperf3
IPERF3_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
IPERF3_BINARY_DIR:=$(PWD)/$(IPERF3_BOARD_PATH)/binaries
IPERF3_INSTALL_BINARY:=$(IPERF3_BINARY_DIR)/$(IPERF3_BINARY_SOURCE)
IPERF3_TEMP_DIR:=$(IPERF3_BINARY_DIR)/iperf3_tmp


$(DL_DIR)/$(IPERF3_SOURCE): 
	$(WGET) -P $(DL_DIR) $(IPERF3_SITE)/$(IPERF3_SOURCE)

iperf3-source: $(DL_DIR)/$(IPERF3_SOURCE)

iperf3-unpacked: $(IPERF3_DIR)/.unpacked
$(IPERF3_DIR)/.unpacked: $(DL_DIR)/$(IPERF3_SOURCE)
	$(IPERF3_CAT) $(DL_DIR)/$(IPERF3_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(IPERF3_DIR) package/iperf3/ \*.patch
	touch $@

$(IPERF3_DIR)/.configured: $(IPERF3_DIR)/.unpacked
	(cd $(IPERF3_DIR); rm -rf config.cache; \
                $(TARGET_CONFIGURE_OPTS) \
                $(TARGET_CONFIGURE_ARGS) \
                ./configure \
                --target=$(GNU_TARGET_NAME) \
                --host=$(GNU_TARGET_NAME) \
                --build=$(GNU_HOST_NAME) \
                --prefix=/usr \
                --sysconfdir=/etc \
        )
	touch $@

$(STAGING_DIR)/$(IPERF3_BINARY): $(IPERF3_DIR)/.configured
	$(MAKE) -C $(IPERF3_DIR)

$(STAGING_DIR)/$(IPERF3_TARGET_BINARY): $(STAGING_DIR)/$(IPERF3_BINARY)
	mkdir -p $(IPERF3_TEMP_DIR)
	$(MAKE) DESTDIR=$(TARGET_DIR) -C $(IPERF3_DIR) install
	$(MAKE) DESTDIR=$(STAGING_DIR) -C $(IPERF3_DIR) install
	$(MAKE) DESTDIR=$(IPERF3_TEMP_DIR) -C $(IPERF3_DIR) install
	rm -rf $(IPERF3_TEMP_DIR)/usr/share/
	tar -cjvf $(IPERF3_BINARY_DIR)/$(IPERF3_BINARY_SOURCE) -C $(IPERF3_TEMP_DIR) .
	rm -rf $(IPERF3_TEMP_DIR)
	

iperf3-binary:
	tar -xjvf $(IPERF3_BINARY_DIR)/$(IPERF3_BINARY_SOURCE) -C $(TARGET_DIR)/

ifeq ($(wildcard $(IPERF3_INSTALL_BINARY)),)
iperf3: $(STAGING_DIR)/$(IPERF3_TARGET_BINARY)
else
iperf3:iperf3-binary
endif

iperf3-clean:
	-$(MAKE) DESTDIR=$(TARGET_DIR) -C $(IPERF3_DIR) uninstall
	-$(MAKE) DESTDIR=$(TARGET_DIR) -C $(IPERF3_DIR) clean

iperf3-dirclean:
	rm -rf $(IPERF3_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_IPERF3),y)
TARGETS+=iperf3
endif
