#############################################################
#
# libxslt
#
#############################################################
ifeq ($(BR2_ARCH_IS_64),y)
LIBXSLT_VERSION = 1.1.29
else
LIBXSLT_VERSION = 1.1.28
endif
LIBXSLT_SOURCE = libxslt-$(LIBXSLT_VERSION).tar.gz
LIBXSLT_SITE = ftp://xmlsoft.org/libxslt
LIBXSLT_INSTALL_STAGING = YES
LIBXSLT_INSTALL_TARGET = YES
LIBXSLT_DIR=$(BUILD_DIR)/libxslt-$(LIBXSLT_VERSION)
LIBXSLT_BINARY_SOURCE:=libxslt-$(LIBXSLT_VERSION)-binary.tar.bz2
LIBXSLT_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
LIBXSLT_BINARY_DIR:=$(LIBXSLT_BOARD_PATH)/binaries
LIBXSLT_INSTALL_BINARY:=$(LIBXSLT_BINARY_DIR)/$(LIBXSLT_BINARY_SOURCE)
LIBXSLT_TEMP_DIR:=$(LIBXSLT_BINARY_DIR)/libxslt_tmp
#TO FIX
LIBXSLT_LIBTOOL_PATCH = NO

# If we have enabled libgcrypt then use it, else disable crypto support.
ifeq ($(BR2_PACKAGE_LIBGCRYPT),y)
LIBXSLT_DEPENDENCIES_EXTRA=libgcrypt
else
LIBXSLT_XTRA_CONF_OPT = --without-crypto
endif

LIBXSLT_CONF_OPT = --with-gnu-ld --enable-shared \
		--enable-static $(LIBXSLT_XTRA_CONF_OPT) \
		$(DISABLE_NLS) $(DISABLE_IPV6) \
		--without-debugging --without-python \
		--without-threads \
		--with-libxml-prefix=$(STAGING_DIR)/usr \
		--with-libxml-include-prefix=$(STAGING_DIR)/usr/include/libxml2

LIBXSLT_DEPENDENCIES = uclibc libxml2 $(LIBXSLT_DEPENDENCIES_EXTRA)


ifeq ($(BR2_ARCH_IS_64),y)
define LIBXSLT_POST_APPLY_64BITPATCH
toolchain/patch-kernel.sh $(LIBXSLT_DIR) package/libxslt/64bitPatch libxslt-$(LIBXSLT_VERSION)\*.patch*
(cd $(LIBXSLT_SRCDIR) && \
        pwd && \
        ./autogen.sh;)
endef

LIBXSLT_POST_PATCH_HOOKS += LIBXSLT_POST_APPLY_64BITPATCH
else
define LIBXSLT_POST_APPLY_32BITPATCH
#toolchain/patch-kernel.sh $(LIBXSLT_DIR) package/libxslt/32bitPatch libxslt-$(LIBXSLT_VERSION)\*.patch*
toolchain/patch-kernel.sh $(LIBXSLT_DIR) package/libxslt/32bitPatch libxslt-\*.patch*
endef
LIBXSLT_POST_PATCH_HOOKS += LIBXSLT_POST_APPLY_32BITPATCH
endif


define LIBXSLT_POST_INSTALL
	$(SED) "s,^prefix=.*,prefix=\'$(STAGING_DIR)/usr\',g" $(STAGING_DIR)/usr/bin/xslt-config
	$(SED) "s,^exec_prefix=.*,exec_prefix=\'$(STAGING_DIR)/usr\',g" $(STAGING_DIR)/usr/bin/xslt-config
	$(SED) "s,^includedir=.*,includedir=\'$(STAGING_DIR)/usr/include\',g" $(STAGING_DIR)/usr/bin/xslt-config
	rm -rf $(TARGET_DIR)/usr/share/aclocal \
	       $(TARGET_DIR)/usr/share/doc/libxslt-$(LIBXSLT_VERSION) \
	       $(TARGET_DIR)/usr/share/gtk-doc \
	       $(TARGET_DIR)/usr/bin/xsltproc \
	       $(TARGET_DIR)/usr/bin/xslt-config 
	touch $@
endef

define LIBXSLT_POST_INSTALL_PREBUILT_BINARIES
	mkdir -p $(LIBXSLT_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(LIBXSLT_TEMP_DIR) -C $(LIBXSLT_DIR) install
	tar cjvf $(LIBXSLT_BINARY_DIR)/$(LIBXSLT_BINARY_SOURCE) -C $(LIBXSLT_TEMP_DIR) .
	rm -rf $(LIBXSLT_TEMP_DIR)
endef


LIBXSLT_POST_INSTALL_HOOKS += LIBXSLT_POST_INSTALL
LIBXSLT_POST_INSTALL_TARGET_HOOKS += LIBXSLT_POST_INSTALL

LIBXSLT_POST_INSTALL_STAGING_HOOKS += LIBXSLT_POST_INSTALL_PREBUILT_BINARIES

libxslt-binary:
	tar -xjvf $(LIBXSLT_BINARY_DIR)/$(LIBXSLT_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(LIBXSLT_BINARY_DIR)/$(LIBXSLT_BINARY_SOURCE) -C $(TARGET_DIR)/
	$(SED) "s,^prefix=.*,prefix=\'$(STAGING_DIR)/usr\',g" $(STAGING_DIR)/usr/bin/xslt-config
	$(SED) "s,^exec_prefix=.*,exec_prefix=\'$(STAGING_DIR)/usr\',g" $(STAGING_DIR)/usr/bin/xslt-config
	$(SED) "s,^includedir=.*,includedir=\'$(STAGING_DIR)/usr/include\',g" $(STAGING_DIR)/usr/bin/xslt-config
	$(SED) "s,^dependency_libs=.*,dependency_libs=\' -L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/lib/libxml2.la -lz $(STAGING_DIR)/usr/lib/libiconv.la -L$(STAGING_DIR)/lib \
	-L$(STAGING_DIR)/usr/lib -lm -ldl',g" $(STAGING_DIR)/usr/lib/libxslt.la
	$(SED) "s,^libdir=.*,libdir\='$(STAGING_DIR)/usr/lib',g" $(STAGING_DIR)/usr/lib/libxslt.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\' -L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	-L$(STAGING_DIR)/usr/lib/libxslt.la -L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/lib/libxml2.la -lz $(STAGING_DIR)/usr/lib/libiconv.la -lm -ldl \
	$(STAGING_DIR)/usr/lib/libgcrypt.la $(STAGING_DIR)/usr/lib/libgpg-error.la',g" $(STAGING_DIR)/usr/lib/libexslt.la
	$(SED) "s,^libdir=.*,libdir\='$(STAGING_DIR)/usr/lib',g" $(STAGING_DIR)/usr/lib/libexslt.la
	rm -rf  $(TARGET_DIR)/usr/share/aclocal \
		$(TARGET_DIR)/usr/share/doc/libxslt-$(LIBXSLT_VERSION) \
		$(TARGET_DIR)/usr/share/gtk-doc \
		$(TARGET_DIR)/usr/include/libxslt \
		$(TARGET_DIR)/usr/include/libexslt \
		$(TARGET_DIR)/usr/bin/xsltproc \
		$(TARGET_DIR)/usr/bin/xslt-config 

ifeq ($(wildcard $(LIBXSLT_INSTALL_BINARY)),)
libxslt: $(eval $(call AUTOTARGETS,package,libxslt))
else
libxslt: libxslt-binary
endif

libxslt-binary-clean: 
	rm $(LIBXSLT_INSTALL_BINARY)

ifeq ($(BR2_PACKAGE_LIBXSLT),y)
TARGETS+=libxslt
endif

