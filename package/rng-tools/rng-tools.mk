#############################################################
#
# RNG_TOOLS
#
#############################################################
RNG_TOOLS_VERSION:=5
RNG_TOOLS_SITE:=http://localhost/
RNG_TOOLS_SOURCE:=rng-tools-$(RNG_TOOLS_VERSION).tar.gz
RNG_TOOLS_DIR:=$(BUILD_DIR)/rng-tools-$(RNG_TOOLS_VERSION)
RNG_TOOLS_CAT:=$(ZCAT) 
RNG_TOOLS_BINARY:=rngd
RNG_TOOLS_TARGET_BINARY:=sbin/rngd
RNG_TOOLS_BINARY_SOURCE:=rng-tools-$(RNG_TOOLS_VERSION)-binary.tar.bz2
RNG_TOOLS_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
RNG_TOOLS_BINARY_DIR:=$(RNG_TOOLS_BOARD_PATH)/binaries
RNG_TOOLS_INSTALL_BINARY:=$(RNG_TOOLS_BINARY_DIR)/$(RNG_TOOLS_BINARY_SOURCE)
RNG_TOOLS_TEMP_DIR:=$(PWD)/$(RNG_TOOLS_BINARY_DIR)/rng-tools_tmp


$(DL_DIR)/$(RNG_TOOLS_SOURCE): 
	$(WGET) -P $(DL_DIR) $(RNG_TOOLS_SITE)/$(RNG_TOOLS_SOURCE)

rng-tools-source: $(DL_DIR)/$(RNG_TOOLS_SOURCE)

rng-tools-unpacked: $(RNG_TOOLS_DIR)/.unpacked
$(RNG_TOOLS_DIR)/.unpacked: $(DL_DIR)/$(RNG_TOOLS_SOURCE)
	$(RNG_TOOLS_CAT) $(DL_DIR)/$(RNG_TOOLS_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(RNG_TOOLS_DIR) package/rng-tools/ rng-tools-$(RNG_TOOLS_VERSION)-\*.patch
	touch $@

$(RNG_TOOLS_DIR)/.configured: $(RNG_TOOLS_DIR)/.unpacked
	(cd $(RNG_TOOLS_DIR); rm -rf config.cache; \
                $(TARGET_CONFIGURE_OPTS) \
                $(TARGET_CONFIGURE_ARGS) \
                ./configure \
                --target=$(GNU_TARGET_NAME) \
                --host=$(GNU_TARGET_NAME) \
                --build=$(GNU_HOST_NAME) \
                --with-gnu-ld \
                prefix=/ \
                --exec-prefix=/ \
                CFLAG="-I$(STAGING_DIR)/usr/include" \
		LDFLAGS="$(TARGET_LDFLAGS) -L$(TARGET_DIR)/lib" \
        )
	touch $@

$(STAGING_DIR)/$(RNG_TOOLS_BINARY): $(RNG_TOOLS_DIR)/.configured
	$(MAKE)	-C $(RNG_TOOLS_DIR)

$(STAGING_DIR)/$(RNG_TOOLS_TARGET_BINARY): $(STAGING_DIR)/$(RNG_TOOLS_BINARY)
	$(MAKE) DESTDIR=$(TARGET_DIR) -C $(RNG_TOOLS_DIR) install
	$(MAKE) DESTDIR=$(STAGING_DIR) -C $(RNG_TOOLS_DIR) install
	mkdir -p $(PWD)/$(RNG_TOOLS_TEMP_DIR)/sbin
	mkdir -p $(PWD)/$(RNG_TOOLS_TEMP_DIR)/bin
	$(MAKE) DESTDIR=$(RNG_TOOLS_TEMP_DIR) -C $(RNG_TOOLS_DIR) install
	rm -rf $(RNG_TOOLS_TEMP_DIR)/share
	tar cjvf $(RNG_TOOLS_BINARY_DIR)/$(RNG_TOOLS_BINARY_SOURCE) -C $(RNG_TOOLS_TEMP_DIR) .
	rm -rf $(RNG_TOOLS_TEMP_DIR)
	touch -c $@

rng-tools-binary:
	tar -xjvf $(RNG_TOOLS_BINARY_DIR)/$(RNG_TOOLS_BINARY_SOURCE) -C $(TARGET_DIR)/

rng-tools-clean:
	-$(MAKE) DESTDIR=$(STAGING_DIR) -C $(RNG_TOOLS_DIR) uninstall
	-$(MAKE) DESTDIR=$(TARGET_DIR) -C $(RNG_TOOLS_DIR) uninstall
	-$(MAKE) -C $(RNG_TOOLS_DIR) clean

rng-tools-dirclean:
	rm -rf $(RNG_TOOLS_DIR)

ifeq ("$(wildcard $(RNG_TOOLS_INSTALL_BINARY))","")
rng-tools: pkgconfig $(STAGING_DIR)/$(RNG_TOOLS_TARGET_BINARY)
else
rng-tools: rng-tools-binary
endif
	
	
rng-tools-binary-clean:
	rm -rf $(RNG_TOOLS_INSTALL_BINARY)
#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_RNG_TOOLS),y)
TARGETS+=rng-tools
endif
