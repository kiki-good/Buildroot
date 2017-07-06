#############################################################
#
# LIBS3
#
#############################################################
LIBS3_VERSION:=002
LIBS3_SITE:=http://localhost/
LIBS3_SOURCE:=libs3-$(LIBS3_VERSION).tar.bz2
LIBS3_DIR:=$(BUILD_DIR)/libs3-$(LIBS3_VERSION)
LIBS3_CAT:=$(BZCAT)
LIBS3_BINARY_SOURCE:= libs3-$(LIBS3_VERSION)-binary.tar.bz2
LIBS3_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
LIBS3_BINARY_DIR:=$(LIBS3_BOARD_PATH)/binaries
LIBS3_INSTALL_BINARY:=$(LIBS3_BINARY_DIR)/$(LIBS3_BINARY_SOURCE) 
LIBS3_TEMP_DIR:=$(LIBS3_BINARY_DIR)/libs3_tmp
LIBS3_BINARY:=s3
LIBS3_TARGET_BINARY:=/usr/bin/s3

ifeq ($(BR2_ARCH_IS_64),y)
OPENSSL_VERSION:=1.1.0d
else
OPENSSL_VERSION:=1.0.1t
endif

$(DL_DIR)/$(LIBS3_SOURCE): 
	$(WGET) -P $(DL_DIR) $(LIBS3_SITE)/$(LIBS3_SOURCE)

libs3-source: $(DL_DIR)/$(LIBS3_SOURCE)

libs3-unpacked: $(LIBS3_DIR)/.unpacked
$(LIBS3_DIR)/.unpacked: $(DL_DIR)/$(LIBS3_SOURCE)
	$(LIBS3_CAT) $(DL_DIR)/$(LIBS3_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
#	toolchain/patch-kernel.sh $(LIBS3_DIR) package/libs3/ libs3-$(LIBS3_VERSION)\*.patch
ifneq ($(BR2_ARCH_IS_64),y)
	toolchain/patch-kernel.sh $(LIBS3_DIR) package/libs3/ libs3-$(LIBS3_VERSION)\*.patch*
else
	toolchain/patch-kernel.sh $(LIBS3_DIR) package/libs3/64bitPatch libs3-$(LIBS3_VERSION)\*.patch*
endif
	touch $@

$(STAGING_DIR)/$(LIBS3_BINARY): $(LIBS3_DIR)/.unpacked
	mkdir -p $(LIBS3_TEMP_DIR)/usr/bin
	mkdir -p $(LIBS3_TEMP_DIR)/usr/lib
	$(MAKE) \
	CC="$(TARGET_CC)" CURL_CFLAGS="-I$(STAGING_DIR)/usr/include/ -I$(BUILD_DIR)/openssl-$(OPENSSL_VERSION)/include/" LIBXML2_CFLAGS=-I$(STAGING_DIR)/usr/include/libxml2 \
	LIBXML2_LIBS="-L$(STAGING_DIR)/usr/lib/ -lxml2 -lz -lm -liconv" \
	CURL_LIBS="-L$(STAGING_DIR)/usr/lib/ -lcurl" -C $(LIBS3_DIR)
	touch $@

$(STAGING_DIR)/$(LIBS3_TARGET_BINARY): $(STAGING_DIR)/$(LIBS3_BINARY)
	$(INSTALL) -D -m 0755 $(LIBS3_DIR)/build/bin/s3 $(TARGET_DIR)/usr/bin
	cp $(LIBS3_DIR)/build/lib/libs3.so.4 $(TARGET_DIR)/usr/lib
	$(INSTALL) -D -m 0755 $(LIBS3_DIR)/build/bin/s3 $(LIBS3_TEMP_DIR)/usr/bin
	cp $(LIBS3_DIR)/build/lib/libs3.so.4 $(LIBS3_TEMP_DIR)/usr/lib
	tar cjvf $(LIBS3_BINARY_DIR)/$(LIBS3_BINARY_SOURCE) -C $(LIBS3_TEMP_DIR) .
	rm -rf $(LIBS3_TEMP_DIR)
	touch $@

libs3-binary:
	tar xjvf $(LIBS3_BINARY_DIR)/$(LIBS3_BINARY_SOURCE) -C $(TARGET_DIR)/

ifeq ($(wildcard $(LIBS3_INSTALL_BINARY)),)
libs3: libxml2 libcurl zlib libiconv openssl $(STAGING_DIR)/$(LIBS3_TARGET_BINARY)
else
libs3: libxml2 libcurl zlib libiconv libs3-binary
endif

libs3-clean:
	$(MAKE) -C $(LIBS3_DIR) clean
	rm $(TARGET_DIR)/usr/bin/s3
	rm $(TARGET_DIR)/usr/lib/libs3.so.4

libs3-dirclean:
	rm -rf $(LIBS3_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_LIBS3),y)
TARGETS+=libs3
endif
