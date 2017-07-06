################################################################################
#
# gst1-plugins-base
#
################################################################################

GST1_PLUGINS_BASE_VERSION = 1.2.3
GST1_PLUGINS_BASE_SOURCE = gst-plugins-base-$(GST1_PLUGINS_BASE_VERSION).tar.xz
GST1_PLUGINS_BASE_SITE = http://localhost/
GST1_PLUGINS_BASE_INSTALL_STAGING = YES
GST1_PLUGINS_BASE_LICENSE_FILES = COPYING.LIB
GST1_PLUGINS_BASE_LICENSE = LGPLv2+ LGPLv2.1+
GST1_PLUGINS_BASE_AUTORECONF = YES
GST1_PLUGINS_BASE_AUTORECONF_ENV = AUTOPOINT=true

GST1_PLUGINS_BASE_DIR=$(BUILD_DIR)/gst1-plugins-base-$(GST1_PLUGINS_BASE_VERSION)
GST1_PLUGINS_BASE_BINARY_SOURCE:=gst1-plugins-base-$(GST1_PLUGINS_BASE_VERSION)-binary.tar.bz2
GST1_PLUGINS_BASE_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
GST1_PLUGINS_BASE_BINARY_DIR:=$(GST1_PLUGINS_BASE_BOARD_PATH)/binaries
GST1_PLUGINS_BASE_INSTALL_BINARY:=$(GST1_PLUGINS_BASE_BINARY_DIR)/$(GST1_PLUGINS_BASE_BINARY_SOURCE)
GST1_PLUGINS_BASE_TEMP_DIR:=$(GST1_PLUGINS_BASE_BINARY_DIR)/gst1-plugins-base_tmp

define GST1_PLUGINS_BASE_PREBUILT_BINARIES
	mkdir -p $(GST1_PLUGINS_BASE_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(GST1_PLUGINS_BASE_TEMP_DIR) -C $(GST1_PLUGINS_BASE_DIR) install
	tar cjvf $(GST1_PLUGINS_BASE_BINARY_DIR)/$(GST1_PLUGINS_BASE_BINARY_SOURCE) -C $(GST1_PLUGINS_BASE_TEMP_DIR) .
	rm -rf $(GST1_PLUGINS_BASE_TEMP_DIR)
endef

GST1_PLUGINS_BASE_POST_INSTALL_STAGING_HOOKS += GST1_PLUGINS_BASE_PREBUILT_BINARIES

# freetype is only used by examples, but if it is not found
# and the host has a freetype-config script, then the host
# include dirs are added to the search path causing trouble
GST1_PLUGINS_BASE_CONF_ENV = \
	FT2_CONFIG=/bin/false \
	GLIB_GENMARSHAL=$(HOST_GLIB)/bin/glib-genmarshal \
	GLIB_MKENUMS=$(HOST_GLIB)/bin/glib-mkenums \
	ac_cv_header_stdint_t="stdint.h"

GST1_PLUGINS_BASE_CONF_OPT = \
	--prefix=/usr/local \
	--exec-prefix=/usr/local \
	--disable-examples \
	--disable-oggtest \
	--disable-vorbistest \
	--disable-freetypetest \
	--disable-valgrind \
	--disable-debug

# Options which require currently unpackaged libraries
GST1_PLUGINS_BASE_CONF_OPT += \
	--disable-cdparanoia \
	--disable-libvisual \
	--disable-iso-codes

GST1_PLUGINS_BASE_DEPENDENCIES = gstreamer1

define GST1_PLUGINS_BASE_POST_INSTALL
        rm -rf $(TARGET_DIR)/usr/local/share/gst-plugins-base
        touch $@
endef

GST1_PLUGINS_BASE_POST_INSTALL_HOOKS += GST1_PLUGINS_BASE_POST_INSTALL
GST1_PLUGINS_BASE_POST_INSTALL_TARGET_HOOKS += GST1_PLUGINS_BASE_POST_INSTALL


# These plugins are liste in the order from ./configure --help

ifeq ($(BR2_PACKAGE_ORC),y)
GST1_PLUGINS_BASE_DEPENDENCIES += orc
GST1_PLUGINS_BASE_CONF_OPT += --enable-orc
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_ADDER),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-adder
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-adder
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_APP),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-app
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-app
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_AUDIOCONVERT),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-audioconvert
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-audioconvert
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_AUDIORATE),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-audiorate
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-audiorate
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_AUDIOTESTSRC),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-audiotestsrc
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-audiotestsrc
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_ENCODING),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-encoding
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-encoding
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_VIDEOCONVERT),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-videoconvert
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-videoconvert
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_GIO),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-gio
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-gio
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_PLAYBACK),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-playback
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-playback
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_AUDIORESAMPLE),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-audioresample
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-audioresample
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_SUBPARSE),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-subparse
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-subparse
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_TCP),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-tcp
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-tcp
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_TYPEFIND),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-typefind
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-typefind
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_VIDEOTESTSRC),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-videotestsrc
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-videotestsrc
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_VIDEORATE),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-videorate
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-videorate
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_VIDEOSCALE),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-videoscale
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-videoscale
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_VOLUME),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-volume
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-volume
endif

ifeq ($(BR2_PACKAGE_ZLIB),y)
GST1_PLUGINS_BASE_DEPENDENCIES += zlib
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-zlib
endif

ifeq ($(BR2_PACKAGE_XORG7),y)
GST1_PLUGINS_BASE_DEPENDENCIES += xlib_libX11 xlib_libXext xlib_libXv
GST1_PLUGINS_BASE_CONF_OPT += \
	--enable-x \
	--enable-xshm \
	--enable-xvideo
else
GST1_PLUGINS_BASE_CONF_OPT += \
	--disable-x \
	--disable-xshm \
	--disable-xvideo
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_ALSA),y)
GST1_PLUGINS_BASE_DEPENDENCIES += alsa-lib
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-alsa
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_TREMOR),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-ivorbis
GST1_PLUGINS_BASE_DEPENDENCIES += tremor
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-ivorbis
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_OGG),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-ogg
GST1_PLUGINS_BASE_DEPENDENCIES += libogg
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-ogg
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_PANGO),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-pango
GST1_PLUGINS_BASE_DEPENDENCIES += pango
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-pango
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_THEORA),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-theora
GST1_PLUGINS_BASE_DEPENDENCIES += libtheora
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-theora
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE_PLUGIN_VORBIS),y)
GST1_PLUGINS_BASE_CONF_OPT += --enable-vorbis
GST1_PLUGINS_BASE_DEPENDENCIES += libvorbis
else
GST1_PLUGINS_BASE_CONF_OPT += --disable-vorbis
endif

gst1-plugins-base-binary:
	tar -xjvf $(GST1_PLUGINS_BASE_BINARY_DIR)/$(GST1_PLUGINS_BASE_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(GST1_PLUGINS_BASE_BINARY_DIR)/$(GST1_PLUGINS_BASE_BINARY_SOURCE) -C $(TARGET_DIR)/
	rm -rf $(TARGET_DIR)/usr/local/share/gst-plugins-base/
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	-L$(STAGING_DIR)/usr/local/lib $(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la \
	$(STAGING_DIR)/usr/lib/libgmodule-2.0.la -ldl $(STAGING_DIR)/usr/lib/libgobject-2.0.la \
	$(STAGING_DIR)/usr/lib/libgthread-2.0.la $(STAGING_DIR)/usr/lib/libffi.la \
	$(STAGING_DIR)/usr/lib/libglib-2.0.la $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc -lm',g" $(STAGING_DIR)/usr/local/lib/libgstallocators-1.0.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/local/lib/libgstvideo-1.0.la -L$(STAGING_DIR)/usr/local/lib \
	$(STAGING_DIR)/usr/local/lib/libgstaudio-1.0.la $(STAGING_DIR)/usr/local/lib/libgsttag-1.0.la -lz \
	$(STAGING_DIR)/usr/local/lib/libgstbase-1.0.la $(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la \
	$(STAGING_DIR)/usr/lib/libgmodule-2.0.la -lm -ldl $(STAGING_DIR)/usr/lib/libgobject-2.0.la \
	$(STAGING_DIR)/usr/lib/libgthread-2.0.la $(STAGING_DIR)/usr/lib/libffi.la \
	$(STAGING_DIR)/usr/lib/libglib-2.0.la $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc',g" $(STAGING_DIR)/usr/local/lib/libgstpbutils-1.0.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	-L$(STAGING_DIR)/usr/local/lib $(STAGING_DIR)/usr/local/lib/libgstbase-1.0.la \
	$(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la $(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la \
	$(STAGING_DIR)/usr/lib/libgmodule-2.0.la -lm -ldl $(STAGING_DIR)/usr/lib/libgobject-2.0.la \
	$(STAGING_DIR)/usr/lib/libgthread-2.0.la $(STAGING_DIR)/usr/lib/libffi.la \
	$(STAGING_DIR)/usr/lib/libglib-2.0.la $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc',g" $(STAGING_DIR)/usr/local/lib/libgstvideo-1.0.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	-L$(STAGING_DIR)/usr/local/lib $(STAGING_DIR)/usr/local/lib/libgstbase-1.0.la \
	$(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la $(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la \
	$(STAGING_DIR)/usr/lib/libgmodule-2.0.la -ldl $(STAGING_DIR)/usr/lib/libgobject-2.0.la \
	$(STAGING_DIR)/usr/lib/libgthread-2.0.la $(STAGING_DIR)/usr/lib/libffi.la \
	$(STAGING_DIR)/usr/lib/libglib-2.0.la $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc -lm -lz',g" $(STAGING_DIR)/usr/local/lib/libgsttag-1.0.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	-L$(STAGING_DIR)/usr/local/lib $(STAGING_DIR)/usr/local/lib/libgstbase-1.0.la \
	$(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la $(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la \
	$(STAGING_DIR)/usr/lib/libgmodule-2.0.la -lm -ldl $(STAGING_DIR)/usr/lib/libgobject-2.0.la \
	$(STAGING_DIR)/usr/lib/libgthread-2.0.la $(STAGING_DIR)/usr/lib/libffi.la \
	$(STAGING_DIR)/usr/lib/libglib-2.0.la $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc',g" $(STAGING_DIR)/usr/local/lib/libgstapp-1.0.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/local/lib/libgsttag-1.0.la -L$(STAGING_DIR)/usr/local/lib -lz \
	$(STAGING_DIR)/usr/local/lib/libgstbase-1.0.la $(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la \
	$(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la $(STAGING_DIR)/usr/lib/libgmodule-2.0.la -ldl \
	$(STAGING_DIR)/usr/lib/libgobject-2.0.la $(STAGING_DIR)/usr/lib/libgthread-2.0.la \
	$(STAGING_DIR)/usr/lib/libffi.la $(STAGING_DIR)/usr/lib/libglib-2.0.la $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc -lm',g" $(STAGING_DIR)/usr/local/lib/libgstaudio-1.0.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/local/lib/libgstaudio-1.0.la -L$(STAGING_DIR)/usr/local/lib \
	$(STAGING_DIR)/usr/local/lib/libgsttag-1.0.la -lz $(STAGING_DIR)/usr/local/lib/libgstbase-1.0.la \
	$(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la $(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la \
	$(STAGING_DIR)/usr/lib/libgmodule-2.0.la -lm -ldl $(STAGING_DIR)/usr/lib/libgobject-2.0.la \
	$(STAGING_DIR)/usr/lib/libgthread-2.0.la $(STAGING_DIR)/usr/lib/libffi.la \
	$(STAGING_DIR)/usr/lib/libglib-2.0.la $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc',g" $(STAGING_DIR)/usr/local/lib/libgstriff-1.0.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	-L$(STAGING_DIR)/usr/local/lib $(STAGING_DIR)/usr/local/lib/libgstbase-1.0.la \
	$(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la $(STAGING_DIR)/usr/local/lib/libgstreamer-1.0.la \
	$(STAGING_DIR)/usr/lib/libgmodule-2.0.la -lm -ldl $(STAGING_DIR)/usr/lib/libgobject-2.0.la \
	$(STAGING_DIR)/usr/lib/libgthread-2.0.la $(STAGING_DIR)/usr/lib/libffi.la \
	$(STAGING_DIR)/usr/lib/libglib-2.0.la $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc',g" $(STAGING_DIR)/usr/local/lib/libgstrtp-1.0.la

gst1-plugins-base-binary-clean:
	rm $(GST1_PLUGINS_BASE_INSTALL_BINARY)

ifeq ($(wildcard $(GST1_PLUGINS_BASE_INSTALL_BINARY)),)
gst1-plugins-base: $(eval $(autotools-package)) $(eval $(call AUTOTARGETS,package/multimedia/gstreamer1,gst1-plugins-base))
else
gst1-plugins-base: gst1-plugins-base-binary
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE),y)
TARGETS+=gst1-plugins-base
endif

