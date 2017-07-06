#############################################################
#
# procproxy
#
#############################################################
PROCPROXY_VERSION:=1.4
PROCPROXY_SOURCE:=$(SKY_DL_DIR)/procproxy-$(PROCPROXY_VERSION).tar.gz
PROCPROXY_SITE:=http://localhost
PROCPROXY_DIR:=$(BUILD_DIR)/procproxy-$(PROCPROXY_VERSION)
PROCPROXY_BINARY_SOURCE:=procproxy-$(PROCPROXY_VERSION).tar.bz2
PROCPROXY_CAT:=$(ZCAT)
PROCPROXY_BINARY:=src/procproxy
PROCPROXY_TARGET_BINARY:=usr/bin/procproxy
PROCPROXY_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
PROCPROXY_BINARY_DIR:=$(PROCPROXY_BOARD_PATH)/binaries
PROCPROXY_INSTALL_BINARY:=$(PROCPROXY_BINARY_DIR)/$(PROCPROXY_BINARY_SOURCE)
PROCPROXY_TEMP_DIR:=$(PROCPROXY_BINARY_DIR)/procproxy_tmp


procproxy-source: $(DL_DIR)/$(PROCPROXY_SOURCE)

$(PROCPROXY_DIR)/.unpacked: $(DL_DIR)/$(PROCPROXY_SOURCE)
	$(PROCPROXY_CAT) $(DL_DIR)/$(PROCPROXY_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(PROCPROXY_DIR) package/sky/procproxy/ \*.patch
	$(CONFIG_UPDATE) $(PROCPROXY_DIR)
	touch $(PROCPROXY_DIR)/.unpacked

$(PROCPROXY_DIR)/.configured: $(PROCPROXY_DIR)/.unpacked
	(cd $(PROCPROXY_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
	)
	touch $(PROCPROXY_DIR)/.configured

$(PROCPROXY_DIR)/$(PROCPROXY_BINARY): $(PROCPROXY_DIR)/.configured
	$(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(PROCPROXY_DIR) LDFLAGS="$(TARGET_LDFLAGS) -latasmart -ludev -L$(TARGET_DIR)/usr/lib" CFLAGS="-I$(STAGING_DIR)/usr/include/"

$(TARGET_DIR)/$(PROCPROXY_TARGET_BINARY): $(PROCPROXY_DIR)/$(PROCPROXY_BINARY)
	mkdir -p $(PROCPROXY_TEMP_DIR)/bin
	$(INSTALL) -D $(PROCPROXY_DIR)/$(PROCPROXY_BINARY) $(TARGET_DIR)/$(PROCPROXY_TARGET_BINARY)
	$(INSTALL) -D $(PROCPROXY_DIR)/$(PROCPROXY_BINARY) $(PROCPROXY_TEMP_DIR)/$(PROCPROXY_TARGET_BINARY)
	$(INSTALL) -D -m 440 package/sky/procproxy/*.conf  ${TARGET_DIR}/etc/init/
	tar cjvf $(PROCPROXY_BINARY_DIR)/$(PROCPROXY_BINARY_SOURCE) -C $(PROCPROXY_TEMP_DIR) .
	rm -rf $(PROCPROXY_TEMP_DIR)
	touch $@

procproxy-binary:
	tar xjvf $(PROCPROXY_BINARY_DIR)/$(PROCPROXY_BINARY_SOURCE) -C $(TARGET_DIR)/
	$(INSTALL) -D -m 440 package/sky/procproxy/*.conf  ${TARGET_DIR}/etc/init/

ifeq ($(wildcard $(PROCPROXY_INSTALL_BINARY)),)
PROCPROXY: libatasmart $(TARGET_DIR)/$(PROCPROXY_TARGET_BINARY)
else
PROCPROXY: libatasmart procproxy-binary
endif

PROCPROXY-clean:
	rm -f $(TARGET_DIR)/$(PROCPROXY_TARGET_BINARY)
	-$(MAKE) -C $(PROCPROXY_DIR) clean

PROCPROXY-dirclean:
	rm -rf $(PROCPROXY_DIR)
#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_SKY_PROCPROXY),y)
TARGETS+=PROCPROXY
endif
