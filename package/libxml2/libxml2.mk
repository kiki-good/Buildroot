#############################################################
#
# libxml2
#
#############################################################
LIBXML2_VERSION = 2.9.2
LIBXML2_SOURCE = libxml2-$(LIBXML2_VERSION).tar.gz
LIBXML2_BINARY_SOURCE:=libxml2-$(LIBXML2_VERSION)-binary.tar.bz2
LIBXML2_SITE = ftp://xmlsoft.org/libxml2
LIBXML2_INSTALL_STAGING = YES
LIBXML2_INSTALL_TARGET = YES
LIBXML2_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
LIBXML2_BINARY_DIR:=$(LIBXML2_BOARD_PATH)/binaries
LIBXML2_INSTALL_BINARY:=$(LIBXML2_BINARY_DIR)/$(LIBXML2_BINARY_SOURCE)

ifneq ($(BR2_LARGEFILE),y)
LIBXML2_CONF_ENV = CC="$(TARGET_CC) $(TARGET_CFLAGS) -DNO_LARGEFILE_SOURCE"
endif

LIBXML2_CONF_OPT = --with-gnu-ld --enable-shared \
		--enable-static $(DISABLE_IPV6) \
		--without-debugging --without-python \
		--without-threads $(DISABLE_NLS) \
		--with-sax1 \
		--without-lzma \
		--with-c14n \
		--with-output --with-tree \
		--with-push --with-reader \
		--with-writer --with-schemas \
		--with-xpath --with-html \
		LIBS="-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib"

LIBXML2_DEPENDENCIES = uclibc zlib

define LIBXML2_POST_INSTALL_CUSTOMISATION
	mkdir -p $(LIBXML2_BINARY_DIR)/libxml2_tmp
	$(MAKE) DESTDIR=$(PWD)/$(LIBXML2_BINARY_DIR)/libxml2_tmp -C $(LIBXML2_DIR) install
	tar cjvf $(LIBXML2_BINARY_DIR)/$(LIBXML2_BINARY_SOURCE) -C $(LIBXML2_BINARY_DIR)/libxml2_tmp .
	rm -rf $(LIBXML2_BINARY_DIR)/libxml2_tmp
endef

libxml2-binary:
	tar -xjvf $(LIBXML2_BINARY_DIR)/$(LIBXML2_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(LIBXML2_BINARY_DIR)/$(LIBXML2_BINARY_SOURCE) -C $(TARGET_DIR)/
	$(SED) "s,^prefix=.*,prefix=\'$(STAGING_DIR)/usr\',g" $(STAGING_DIR)/usr/bin/xml2-config
	$(SED) "s,^exec_prefix=.*,exec_prefix=\'$(STAGING_DIR)/usr\',g" $(STAGING_DIR)/usr/bin/xml2-config
	$(SED) "s,^dependency_libs=.*,dependency_libs=\' -ldl  -L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	-lz $(STAGING_DIR)/usr/lib/libiconv.la  -L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib -lm ',g" \
	$(STAGING_DIR)/usr/lib/libxml2.la
	$(SED) "s,^libdir=.*,libdir\='$(STAGING_DIR)/usr/lib',g" $(STAGING_DIR)/usr/lib/libxml2.la

	rm -rf $(TARGET_DIR)/usr/include/
	rm -rf $(TARGET_DIR)/usr/share/aclocal \
		$(TARGET_DIR)/usr/share/doc/libxml2-$(LIBXML2_VERSION) \
		$(TARGET_DIR)/usr/share/gtk-doc \
		$(TARGET_DIR)/usr/man/ \
		$(TARGET_DIR)/usr/bin/xmllint \
		$(TARGET_DIR)/usr/bin/xmlcatalog \
		$(TARGET_DIR)/usr/bin/xml2-config 

libxml2-binary-install-staging:
	tar -xjvf $(LIBXML2_BINARY_DIR)/$(LIBXML2_BINARY_SOURCE) -C $(STAGING_DIR)/
	$(SED) "s,^prefix=.*,prefix=\'$(STAGING_DIR)/usr\',g" $(STAGING_DIR)/usr/bin/xml2-config
	$(SED) "s,^exec_prefix=.*,exec_prefix=\'$(STAGING_DIR)/usr\',g" $(STAGING_DIR)/usr/bin/xml2-config
	$(SED) "s,^dependency_libs=.*,dependency_libs=\' -ldl  -L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	-lz $(STAGING_DIR)/usr/lib/libiconv.la  -L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib -lm ',g" $(STAGING_DIR)/usr/lib/libxml2.la

ifeq ($(wildcard $(LIBXML2_INSTALL_BINARY)),)
libxml2: $(eval $(call AUTOTARGETS,package,libxml2))
else
libxml2: libxml2-binary
libxml2-install-staging: libxml2-binary-install-staging
endif

libxml2-binary-clean:
	rm -rf $(LIBXML2_INSTALL_BINARY)

define LIBXML2_POST_EXTRACT
	rm -f $(LIBXML2_DIR)/win32/Makefile.msvc.rej
	rm -f $(LIBXML2_DIR)/macos/src/XMLTestPrefix.h.rej
endef

LIBXML2_POST_EXTRACT_HOOKS += LIBXML2_POST_EXTRACT
LIBXML2_POST_INSTALL_STAGING_HOOKS += LIBXML2_POST_INSTALL_CUSTOMISATION

define LIBXML2_POST_INSTALL
	$(SED) "s,^prefix=.*,prefix=\'$(STAGING_DIR)/usr\',g" $(STAGING_DIR)/usr/bin/xml2-config
	$(SED) "s,^exec_prefix=.*,exec_prefix=\'$(STAGING_DIR)/usr\',g" $(STAGING_DIR)/usr/bin/xml2-config
	rm -rf $(TARGET_DIR)/usr/share/aclocal \
	       $(TARGET_DIR)/usr/share/doc/libxml2-$(LIBXML2_VERSION) \
	       $(TARGET_DIR)/usr/share/gtk-doc \
	       $(TARGET_DIR)/usr/man/ \
	       $(TARGET_DIR)/usr/bin/xmllint \
	       $(TARGET_DIR)/usr/bin/xmlcatalog \
	       $(TARGET_DIR)/usr/bin/xml2-config 
	touch $@
endef

LIBXML2_POST_INSTALL_HOOKS += LIBXML2_POST_INSTALL

