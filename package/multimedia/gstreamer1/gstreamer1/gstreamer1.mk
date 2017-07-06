################################################################################
#
# gstreamer1
#
################################################################################

GSTREAMER1_VERSION = 1.2.3
GSTREAMER1_SOURCE = gstreamer-$(GSTREAMER1_VERSION).tar.xz
GSTREAMER1_SITE = http://localhost/
GSTREAMER1_INSTALL_STAGING = YES
GSTREAMER1_LICENSE_FILES = COPYING
GSTREAMER1_LICENSE = LGPLv2+ LGPLv2.1+
GSTREAMER1_AUTORECONF = YES
GSTREAMER1_AUTORECONF_ENV = AUTOPOINT=true

GSTREAMER1_DIR=$(BUILD_DIR)/gstreamer1-$(GSTREAMER1_VERSION)
GSTREAMER1_BINARY_SOURCE:=gstreamer1-$(GSTREAMER1_VERSION)-binary.tar.bz2
GSTREAMER1_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
GSTREAMER1_BINARY_DIR:=$(GSTREAMER1_BOARD_PATH)/binaries
GSTREAMER1_INSTALL_BINARY:=$(GSTREAMER1_BINARY_DIR)/$(GSTREAMER1_BINARY_SOURCE)
GSTREAMER1_TEMP_DIR:=$(GSTREAMER1_BINARY_DIR)/gstreamer1_tmp

define GSTREAMER1_PREBUILT_BINARIES
	mkdir -p $(GSTREAMER1_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(GSTREAMER1_TEMP_DIR) -C $(GSTREAMER1_DIR) install
	tar cjvf $(GSTREAMER1_BINARY_DIR)/$(GSTREAMER1_BINARY_SOURCE) -C $(GSTREAMER1_TEMP_DIR) .
	rm -rf $(GSTREAMER1_TEMP_DIR)
endef

GSTREAMER1_POST_INSTALL_STAGING_HOOKS += GSTREAMER1_PREBUILT_BINARIES

GSTREAMER1_CONF_ENV = \
	GLIB_GENMARSHAL=$(HOST_GLIB)/bin/glib-genmarshal \
	GLIB_MKENUMS=$(HOST_GLIB)/bin/glib-mkenums
# Checking if unaligned memory access works correctly cannot be done when cross
# compiling. For the following architectures there is no information available
# in the configure script.
ifeq ($(BR2_avr32)$(BR2_xtensa)$(BR2_microblaze),y)
GSTREAMER1_CONF_ENV += as_cv_unaligned_access=no
endif
ifeq ($(BR2_aarch64),y)
GSTREAMER1_CONF_ENV += as_cv_unaligned_access=yes
endif

GSTREAMER1_CONF_OPT = \
	--prefix=/usr/local \
	--exec-prefix=/usr/local \
	--disable-examples \
	--disable-tests \
	--disable-failing-tests \
	--disable-debug \
	--disable-valgrind \
	--disable-benchmarks \
	--disable-check \
	$(if $(BR2_PACKAGE_GSTREAMER1_TRACE),,--disable-trace) \
	$(if $(BR2_PACKAGE_GSTREAMER1_PARSE),,--disable-parse) \
	$(if $(BR2_PACKAGE_GSTREAMER1_GST_DEBUG),,--disable-gst-debug) \
	$(if $(BR2_PACKAGE_GSTREAMER1_PLUGIN_REGISTRY),,--disable-registry) \
	$(if $(BR2_PACKAGE_GSTREAMER1_INSTALL_TOOLS),--enable-tools,--disable-tools)

# GSTREAMER1_DEPENDENCIES = libglib2 host-pkgconfig host-bison host-flex
GSTREAMER1_DEPENDENCIES = libglib2 pkgconfig gettext

gstreamer1-binary:
	tar -xjvf $(GSTREAMER1_BINARY_DIR)/$(GSTREAMER1_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(GSTREAMER1_BINARY_DIR)/$(GSTREAMER1_BINARY_SOURCE) -C $(TARGET_DIR)/
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib \
	-L$(STAGING_DIR)/usr/lib $(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la -lm \
	$(STAGING_DIR)/usr/lib/libgobject-2.0.la $(STAGING_DIR)/usr/lib/libgthread-2.0.la \
	$(STAGING_DIR)/usr/lib/libffi.la $(STAGING_DIR)/usr/lib/libgmodule-2.0.la \
	$(STAGING_DIR)/usr/lib/libglib-2.0.la $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc -ldl',g" $(STAGING_DIR)/usr/local/lib/libgstbase-1.0.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/lib/libgobject-2.0.la $(STAGING_DIR)/usr/lib/libgthread-2.0.la \
	$(STAGING_DIR)/usr/lib/libffi.la $(STAGING_DIR)/usr/lib/libgmodule-2.0.la \
	$(STAGING_DIR)/usr/lib/libglib-2.0.la $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc -lm -ldl',g" $(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/local/lib/libgstbase-1.0.la $(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la -lm \
	$(STAGING_DIR)/usr/lib/libgobject-2.0.la $(STAGING_DIR)/usr/lib/libgthread-2.0.la \
	$(STAGING_DIR)/usr/lib/libffi.la $(STAGING_DIR)/usr/lib/libgmodule-2.0.la \
	$(STAGING_DIR)/usr/lib/libglib-2.0.la $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc -ldl',g" $(STAGING_DIR)/usr/local/lib/gstreamer-1.0/libgstcoreelements.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la -lm $(STAGING_DIR)/usr/lib/libgio-2.0.la \
	$(STAGING_DIR)/usr/lib/libgthread-2.0.la $(STAGING_DIR)/usr/lib/libgmodule-2.0.la \
	$(STAGING_DIR)/usr/lib/libglib-2.0.la -lz $(STAGING_DIR)/usr/lib/libgobject-2.0.la \
	$(STAGING_DIR)/usr/lib/libgthread-2.0.la $(STAGING_DIR)/usr/lib/libffi.la \
	$(STAGING_DIR)/usr/lib/libglib-2.0.la $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc -ldl',g" $(STAGING_DIR)/usr/local/lib/libgstnet-1.0.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la $(STAGING_DIR)/usr/lib/libgobject-2.0.la \
	$(STAGING_DIR)/usr/lib/libgthread-2.0.la $(STAGING_DIR)/usr/lib/libffi.la \
	$(STAGING_DIR)/usr/lib/libgmodule-2.0.la $(STAGING_DIR)/usr/lib/libglib-2.0.la \
	$(STAGING_DIR)/usr/lib/libiconv.la -lpthread $(STAGING_DIR)/usr/lib/libintl.la -lc -lm -ldl',g" \
	$(STAGING_DIR)/usr/local/lib/libgstcontroller-1.0.la

	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/local/lib\',g" $(STAGING_DIR)/usr/local/lib/libgstbase-1.0.la
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/local/lib\',g" $(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/local/lib/gstreamer-1.0/libgstcoreelements.la\',g" \
	$(STAGING_DIR)/usr/local/lib/gstreamer-1.0/libgstcoreelements.la
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/local/lib/libgstnet-1.0.la\',g" $(STAGING_DIR)/usr/local/lib/libgstnet-1.0.la
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/local/lib/libgstcontroller-1.0.la\',g" $(STAGING_DIR)/usr/local/lib/libgstcontroller-1.0.la

gstreamer1-binary-clean:
	rm $(GSTREAMER1_INSTALL_BINARY)

ifeq ($(wildcard $(GSTREAMER1_INSTALL_BINARY)),)
gstreamer1: $(eval $(autotools-package)) $(eval $(call AUTOTARGETS,package/multimedia/gstreamer1,gstreamer1))
else
gstreamer1: gstreamer1-binary
endif

ifeq ($(BR2_PACKAGE_GSTREAMER1),y)
TARGETS+=gstreamer1
endif

