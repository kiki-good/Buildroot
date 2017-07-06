################################################################################
#
# gst1-plugins-ugly
#
################################################################################

GST1_PLUGINS_UGLY_VERSION = 1.2.3
GST1_PLUGINS_UGLY_SOURCE = gst-plugins-ugly-$(GST1_PLUGINS_UGLY_VERSION).tar.xz
GST1_PLUGINS_UGLY_SITE = http://localhost/
GST1_PLUGINS_UGLY_INSTALL_STAGING = YES
GST1_PLUGINS_UGLY_LICENSE_FILES = COPYING
# GPL licensed plugins will append to GST1_PLUGINS_UGLY_LICENSE if enabled.
GST1_PLUGINS_UGLY_LICENSE = LGPLv2.1+
GST1_PLUGINS_UGLY_AUTORECONF = YES
GST1_PLUGINS_UGLY_AUTORECONF_ENV = AUTOPOINT=true

GST1_PLUGINS_UGLY_DIR=$(BUILD_DIR)/gst1-plugins-ugly-$(GST1_PLUGINS_UGLY_VERSION)
GST1_PLUGINS_UGLY_BINARY_SOURCE:=gst1-plugins-ugly-$(GST1_PLUGINS_UGLY_VERSION)-binary.tar.bz2
GST1_PLUGINS_UGLY_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
GST1_PLUGINS_UGLY_BINARY_DIR:=$(GST1_PLUGINS_UGLY_BOARD_PATH)/binaries
GST1_PLUGINS_UGLY_INSTALL_BINARY:=$(GST1_PLUGINS_UGLY_BINARY_DIR)/$(GST1_PLUGINS_UGLY_BINARY_SOURCE)
GST1_PLUGINS_UGLY_TEMP_DIR:=$(GST1_PLUGINS_UGLY_BINARY_DIR)/gst1-plugins-ugly_tmp

define GST1_PLUGINS_UGLY_PREBUILT_BINARIES
	mkdir -p $(GST1_PLUGINS_UGLY_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(GST1_PLUGINS_UGLY_TEMP_DIR) -C $(GST1_PLUGINS_UGLY_DIR) install
	tar cjvf $(GST1_PLUGINS_UGLY_BINARY_DIR)/$(GST1_PLUGINS_UGLY_BINARY_SOURCE) -C $(GST1_PLUGINS_UGLY_TEMP_DIR) .
	#rm -rf $(GST1_PLUGINS_UGLY_TEMP_DIR)
endef

GST1_PLUGINS_UGLY_POST_INSTALL_STAGING_HOOKS += GST1_PLUGINS_UGLY_PREBUILT_BINARIES

GST1_PLUGINS_UGLY_CONF_ENV = \
	GLIB_GENMARSHAL=$(HOST_GLIB)/bin/glib-genmarshal \
	GLIB_MKENUMS=$(HOST_GLIB)/bin/glib-mkenums \
	ac_cv_header_stdint_t="stdint.h"

GST1_PLUGINS_UGLY_CONF_OPT = \
	--prefix=/usr/local \
	--exec-prefix=/usr/local \
	--disable-examples \
	--disable-debug \
	--disable-valgrind

GST1_PLUGINS_UGLY_DEPENDENCIES = gstreamer1 gst1-plugins-base

ifeq ($(BR2_PACKAGE_ORC),y)
GST1_PLUGINS_UGLY_CONF_OPT += --enable-orc
GST1_PLUGINS_UGLY_DEPENDENCIES += orc
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_UGLY_PLUGIN_ASFDEMUX),y)
GST1_PLUGINS_UGLY_CONF_OPT += --enable-asfdemux
else
GST1_PLUGINS_UGLY_CONF_OPT += --disable-asfdemux
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_UGLY_PLUGIN_DVDLPCMDEC),y)
GST1_PLUGINS_UGLY_CONF_OPT += --enable-dvdlpcmdec
else
GST1_PLUGINS_UGLY_CONF_OPT += --disable-dvdlpcmdec
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_UGLY_PLUGIN_DVDSUB),y)
GST1_PLUGINS_UGLY_CONF_OPT += --enable-dvdsub
else
GST1_PLUGINS_UGLY_CONF_OPT += --disable-dvdsub
endif

ifeq ($(BR2_PACKAGE_GST_PLUGINS_UGL1_PLUGIN_XINGMUX),y)
GST1_PLUGINS_UGLY_CONF_OPT += --enable-xingmux
else
GST1_PLUGINS_UGLY_CONF_OPT += --disable-xingmux
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_UGLY_PLUGIN_REALMEDIA),y)
GST1_PLUGINS_UGLY_CONF_OPT += --enable-realmedia
else
GST1_PLUGINS_UGLY_CONF_OPT += --disable-realmedia
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_UGLY_PLUGIN_DVDREAD),y)
GST1_PLUGINS_UGLY_CONF_OPT += --enable-dvdread
GST1_PLUGINS_UGLY_DEPENDENCIES += libdvdread
GST1_PLUGINS_UGLY_HAS_GPL_LICENSE = y
else
GST1_PLUGINS_UGLY_CONF_OPT += --disable-dvdread
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_UGLY_PLUGIN_LAME),y)
GST1_PLUGINS_UGLY_CONF_OPT += --enable-lame
GST1_PLUGINS_UGLY_DEPENDENCIES += lame
else
GST1_PLUGINS_UGLY_CONF_OPT += --disable-lame
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_UGLY_PLUGIN_MAD),y)
GST1_PLUGINS_UGLY_CONF_OPT += --enable-mad
GST1_PLUGINS_UGLY_DEPENDENCIES += libid3tag libmad
GST1_PLUGINS_UGLY_HAS_GPL_LICENSE = y
else
GST1_PLUGINS_UGLY_CONF_OPT += --disable-mad
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_UGLY_PLUGIN_MPEG2DEC),y)
GST1_PLUGINS_UGLY_CONF_OPT += --enable-mpeg2dec
GST1_PLUGINS_UGLY_DEPENDENCIES += libmpeg2
GST1_PLUGINS_ULGY_HAS_GPL_LICENSE = y
else
GST1_PLUGINS_UGLY_CONF_OPT += --disable-mpeg2dec
endif

# Add GPL license if GPL plugins enabled.
ifeq ($(GST1_PLUGINS_UGLY_HAS_GPL_LICENSE),y)
GST1_PLUGINS_UGLY_LICENSE += GPLv2
endif

# Use the following command to extract license info for plugins.
# # find . -name 'plugin-*.xml' | xargs grep license

gst1-plugins-ugly-binary:
	tar -xjvf $(GST1_PLUGINS_UGLY_BINARY_DIR)/$(GST1_PLUGINS_UGLY_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(GST1_PLUGINS_UGLY_BINARY_DIR)/$(GST1_PLUGINS_UGLY_BINARY_SOURCE) -C $(TARGET_DIR)/

gst1-plugins-ugly-binary-clean:
	rm $(GST1_PLUGINS_UGLY_INSTALL_BINARY)

ifeq ($(wildcard $(GST1_PLUGINS_UGLY_INSTALL_BINARY)),)
gst1-plugins-ugly: $(eval $(autotools-package)) $(eval $(call AUTOTARGETS,package/multimedia/gstreamer1,gst1-plugins-ugly))
else
gst1-plugins-ugly: gst1-plugins-ugly-binary
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_UGLY),y)
TARGETS+=gst1-plugins-ugly
endif

