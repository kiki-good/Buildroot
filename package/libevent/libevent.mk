#############################################################
#
# libevent
#
#############################################################
LIBEVENT_VERSION:=2.0.14
LIBEVENT_SOURCE:=libevent-$(LIBEVENT_VERSION)-stable.tar.gz
LIBEVENT_SITE:=http://localhost/
LIBEVENT_DIR:=$(BUILD_DIR)/libevent-$(LIBEVENT_VERSION)-stable
LIBEVENT_CAT:=$(ZCAT)
LIBEVENT_BINARY:=libevent.la
LIBEVENT_TARGET_BINARY:=usr/lib/libevent.so
LIBEVENT_INSTALL_STAGING = YES
LIBEVENT_AUTORECONF = YES
LIBEVENT_BINARY_SOURCE:=libevent-$(LIBEVENT_VERSION)-binary.tar.bz2
LIBEVENT_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
LIBEVENT_BINARY_DIR:=$(LIBEVENT_BOARD_PATH)/binaries
LIBEVENT_BINARY_TEMP_DIR:=$(LIBEVENT_BINARY_DIR)/libevent_temp
LIBEVENT_INSTALL_BINARY:=$(LIBEVENT_BINARY_DIR)/$(LIBEVENT_BINARY_SOURCE)


$(DL_DIR)/$(LIBEVENT_SOURCE):
	$(WGET) -P $(DL_DIR) $(LIBEVENT_SITE)/$(LIBEVENT_SOURCE)

libevent-source: $(DL_DIR)/$(LIBEVENT_SOURCE)

libevent-unpacked: $(LIBEVENT_DIR)/.unpacked
$(LIBEVENT_DIR)/.unpacked: $(DL_DIR)/$(LIBEVENT_SOURCE)
	$(LIBEVENT_CAT) $(DL_DIR)/$(LIBEVENT_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(LIBEVENT_DIR) package/libevent/ \*.patch
	$(CONFIG_UPDATE) $(LIBEVENT_DIR)
	touch $@

$(LIBEVENT_DIR)/.configured: $(LIBEVENT_DIR)/.unpacked
	(cd $(LIBEVENT_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--prefix=/usr \
		--mandir=/usr/share/man \
		--disable-static \
		--with-gnu-ld \
	)
	touch $@

$(LIBEVENT_DIR)/$(LIBEVENT_BINARY): $(LIBEVENT_DIR)/.configured
	$(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(LIBEVENT_DIR)

$(STAGING_DIR)/$(LIBEVENT_TARGET_BINARY): $(LIBEVENT_DIR)/$(LIBEVENT_BINARY)
	$(MAKE) -C $(LIBEVENT_DIR) DESTDIR=$(STAGING_DIR) install
	$(MAKE) -C $(LIBEVENT_DIR) DESTDIR=$(PWD)/$(LIBEVENT_BINARY_TEMP_DIR) install
	tar cjvf $(LIBEVENT_BINARY_DIR)/$(LIBEVENT_BINARY_SOURCE) -C $(LIBEVENT_BINARY_TEMP_DIR) .
	rm -rf $(LIBEVENT_BINARY_TEMP_DIR)

$(TARGET_DIR)/$(LIBEVENT_TARGET_BINARY): $(STAGING_DIR)/$(LIBEVENT_TARGET_BINARY)
	$(MAKE) -C $(LIBEVENT_DIR) DESTDIR=$(TARGET_DIR) install
	rm -f $(addprefix $(TARGET_DIR)/usr/,lib/libevent*.la)
ifneq ($(BR2_HAVE_MANPAGES),y)
	rm -fr $(TARGET_DIR)/usr/share/man
endif

libevent-binary:
	tar -xjvf $(LIBEVENT_BINARY_DIR)/$(LIBEVENT_BINARY_SOURCE) -C $(STAGING_DIR)/
	cp -dpf $(STAGING_DIR)/usr/lib/libevent-2.0.so* $(TARGET_DIR)/usr/lib/
	cp -dpf $(STAGING_DIR)/usr/lib/libevent.so $(TARGET_DIR)/usr/lib/
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libevent-2.0.so*

	rm -f $(addprefix $(TARGET_DIR)/usr/,lib/libevent*.la)
ifneq ($(BR2_HAVE_MANPAGES),y)
	rm -fr $(TARGET_DIR)/usr/share/man
endif

ifeq ($(wildcard $(LIBEVENT_INSTALL_BINARY)),)
libevent: $(TARGET_DIR)/$(LIBEVENT_TARGET_BINARY)
else
libevent: libevent-binary
endif

libevent-clean:
	rm -f $(TARGET_DIR)/$(LIBEVENT_TARGET_BINARY)*
	-$(MAKE) -C $(LIBEVENT_DIR) clean

libevent-dirclean:
	rm -rf $(LIBEVENT_DIR)

libevent-binary-clean:
	rm $(LIBEVENT_INSTALL_BINARY)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_LIBEVENT),y)
TARGETS+=libevent
endif
