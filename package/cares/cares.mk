#############################################################
#
# cares
#
#############################################################
CARES_VERSION:=1.10.0
CARES_SOURCE:=cares-$(CARES_VERSION).tar.gz
CARES_SITE = https://github.com/downloads/cares/cares

CARES_DIR:=$(BUILD_DIR)/cares-$(CARES_VERSION)
CARES_CAT:=$(ZCAT)
CARES_BINARY:=libcares.so
CARES_TARGET_BINARY:=lib/libcares.so
CARES_INSTALL_STAGING = YES

$(DL_DIR)/$(CARES_SOURCE):
	$(WGET) -P $(DL_DIR) $(CARES_SITE)/$(CARES_SOURCE)

cares-source: $(DL_DIR)/$(CARES_SOURCE)

cares-unpacked: $(CARES_DIR)/.unpacked
$(CARES_DIR)/.unpacked: $(DL_DIR)/$(CARES_SOURCE)
	$(CARES_CAT) $(DL_DIR)/$(CARES_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	$(CONFIG_UPDATE) $(CARES_DIR)
	touch $@

$(CARES_DIR)/.configured: $(CARES_DIR)/.unpacked
	(cd $(CARES_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--prefix=/usr \
		--mandir=/usr/share/man \
		--enable-shared \
		--enable-static  \
		--includedir=/usr/include \
		--with-gnu-ld \
	)
	touch $@

$(CARES_DIR)/$(CARES_BINARY): $(CARES_DIR)/.configured
	$(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(CARES_DIR)

$(STAGING_DIR)/$(CARES_TARGET_BINARY): $(CARES_DIR)/$(CARES_BINARY)
	$(MAKE) -C $(CARES_DIR) DESTDIR=$(STAGING_DIR) install

$(TARGET_DIR)/$(CARES_TARGET_BINARY): $(STAGING_DIR)/$(CARES_TARGET_BINARY)
	$(MAKE) -C $(CARES_DIR) DESTDIR=$(TARGET_DIR) install
	rm -f $(addprefix $(TARGET_DIR)/usr/,lib/cares*.la )
ifneq ($(BR2_HAVE_MANPAGES),y)
	rm -fr $(TARGET_DIR)/usr/share/man
endif

cares: $(TARGET_DIR)/$(CARES_TARGET_BINARY)

cares-clean:
	rm -f $(TARGET_DIR)/$(CARES_TARGET_BINARY)*
	-$(MAKE) -C $(CARES_DIR) clean

cares-dirclean:
	rm -rf $(CARES_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_CARES),y)
TARGETS+=cares
endif
