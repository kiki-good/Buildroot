#############################################################
#
# curl
#
#############################################################
CURL_VERSION:=7.53.1
LIBCURL_VERSION:=4.4.0
CURL_SOURCE:=curl-$(CURL_VERSION).tar.bz2
CURL_BINARY_SOURCE:=curl-$(CURL_VERSION)-binary.tar.bz2
CURL_SITE:=http://curl.haxx.se/download/
CURL_CAT:=$(BZCAT)
CURL_DIR:=$(BUILD_DIR)/curl-$(CURL_VERSION)
CURL_BINARY:=curl
CURL_DESTDIR:=$(STAGING_DIR)/usr
CURL_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
CURL_BINARY_DIR:=$(CURL_BOARD_PATH)/binaries
CURL_INSTALL_BINARY:=$(CURL_BINARY_DIR)/$(CURL_BINARY_SOURCE)

$(DL_DIR)/$(CURL_SOURCE):
	 $(WGET) -P $(DL_DIR) $(CURL_SITE)/$(CURL_SOURCE)

curl-source: $(DL_DIR)/$(CURL_SOURCE)

$(CURL_DIR)/.unpacked: $(DL_DIR)/$(CURL_SOURCE)
	$(CURL_CAT) $(DL_DIR)/$(CURL_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(CURL_DIR) package/curl/ curl-$(CURL_VERSION)-\*.patch*
ifneq ($(BR2_ARCH_IS_64),y)
	toolchain/patch-kernel.sh $(CURL_DIR) package/curl/ curl-$(CURL_VERSION)\*.patch*
else
	toolchain/patch-kernel.sh $(CURL_DIR) package/curl/64bitPatch curl-$(CURL_VERSION)\*.patch*
endif

	touch $(CURL_DIR)/.unpacked

$(CURL_DIR)/.configured: $(CURL_DIR)/.unpacked
	(cd $(CURL_DIR); rm -rf config.cache; )
ifneq ($(BR2_ARCH_IS_64),y)
	$(CONFIG_UPDATE) $(CURL_DIR)
endif
	(cd $(CURL_DIR); \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--prefix=/usr \
		--exec-prefix=/usr \
		--bindir=/usr/bin \
		--sbindir=/usr/sbin \
		--libdir=/usr/lib \
		--libexecdir=/usr/lib \
		--sysconfdir=/etc \
		--datadir=/usr/share \
		--localstatedir=/var \
		--includedir=/usr/include \
		--mandir=/usr/share/man \
		--infodir=/usr/share/info \
		--with-random=/dev/urandom \
		--without-ssl \
		--without-zlib \
	)
	touch $(CURL_DIR)/.configured

$(CURL_DIR)/src/.libs/$(CURL_BINARY): $(CURL_DIR)/.configured
	$(MAKE) -C $(CURL_DIR)

$(CURL_DESTDIR)/bin/$(CURL_BINARY): $(CURL_DIR)/src/.libs/$(CURL_BINARY)
	-mkdir $(CURL_DESTDIR)/bin
	$(MAKE) DESTDIR=$(STAGING_DIR) -C $(CURL_DIR) install
	mkdir -p $(CURL_BINARY_DIR)/curl_tmp
	$(MAKE) DESTDIR=$(PWD)/$(CURL_BINARY_DIR)/curl_tmp -C $(CURL_DIR) install
	$(SED) "s,^libdir=.*,libdir=\'$(CURL_DESTDIR)/lib\',g" $(CURL_DESTDIR)/lib/libcurl.la
	touch $(CURL_DESTDIR)/bin/$(CURL_BINARY)
	tar cjvf $(CURL_BINARY_DIR)/$(CURL_BINARY_SOURCE) -C $(CURL_BINARY_DIR)/curl_tmp .
	rm -rf $(CURL_BINARY_DIR)/curl_tmp


$(TARGET_DIR)/usr/lib/libcurl.so.$(LIBCURL_VERSION): $(CURL_DESTDIR)/bin/$(CURL_BINARY)
	-mkdir $(TARGET_DIR)/usr/lib
	-mkdir $(TARGET_DIR)/usr/bin
	cp -a $(CURL_DESTDIR)/lib/libcurl.so* $(TARGET_DIR)/usr/lib
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libcurl.so.$(LIBCURL_VERSION)

$(TARGET_DIR)/usr/bin/$(CURL_BINARY): $(TARGET_DIR)/usr/lib/libcurl.so.$(LIBCURL_VERSION)
	cp -a $(CURL_DESTDIR)/bin/$(CURL_BINARY) $(TARGET_DIR)/usr/bin
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/bin/$(CURL_BINARY)

libcurl-binary: 
	tar -xjvf $(CURL_BINARY_DIR)/$(CURL_BINARY_SOURCE) -C $(STAGING_DIR)/
	cp -a $(STAGING_DIR)/usr/lib/libcurl.so* $(TARGET_DIR)/usr/lib
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/lib\',g" $(STAGING_DIR)/usr/lib/libcurl.la
curl-binary: libcurl-binary
	cp -a $(STAGING_DIR)/usr/bin/$(CURL_BINARY) $(TARGET_DIR)/usr/bin


ifeq ($(wildcard $(CURL_INSTALL_BINARY)),)
curl: uclibc $(TARGET_DIR)/usr/bin/$(CURL_BINARY)
else
curl: uclibc curl-binary
endif

ifeq ($(wildcard $(CURL_INSTALL_BINARY)),)
libcurl: $(CURL_DESTDIR)/bin/$(CURL_BINARY)
else
libcurl: libcurl-binary
endif

curl-clean:
	rm -f $(TARGET_DIR)/usr/lib/libcurl.so*
	rm -f $(TARGET_DIR)/usr/bin/curl
	rm -f $(CURL_DESTDIR)/bin/curl*
	rm -f $(CURL_DESTDIR)/lib/libcurl.so*
	rm -rf $(CURL_DESTDIR)/include/curl
	-$(MAKE) -C $(CURL_DIR) clean

curl-dirclean:
	rm -rf $(CURL_DIR)

curl-binary-clean:
	rm -rf $(CURL_INSTALL_BINARY)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_CURL),y)
TARGETS+=curl
endif
ifeq ($(BR2_PACKAGE_LIBCURL),y)
TARGETS+=libcurl
endif
