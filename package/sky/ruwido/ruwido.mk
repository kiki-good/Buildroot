#############################################################
#
# ruwido
#
#############################################################
ifeq ($(BR2_BOARD_NAME), "bskyb-97445")
RUWIDO_VERSION = 0.4.8
else
RUWIDO_VERSION = 0.7.11
endif
RUWIDO_DIR:=$(BUILD_DIR)/ruwido-$(RUWIDO_VERSION)
RUWIDO_SOURCE = $(SKY_DL_DIR)/ruwido_daemon-$(RUWIDO_VERSION).tar.bz2
RUWIDO_BINARY_SOURCE:= ruwido_daemon-$(RUWIDO_VERSION)-binary.tar.bz2
RUWIDO_CAT:=$(BZCAT)
RUWIDO_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
RUWIDO_BINARY_DIR:=$(RUWIDO_BOARD_PATH)/binaries
RUWIDO_INSTALL_BINARY:=$(RUWIDO_BINARY_DIR)/$(RUWIDO_BINARY_SOURCE)
RUWIDO_TEMP_DIR:=$(RUWIDO_BINARY_DIR)/ruwido_tmp

RUWIDO_AUTORECONF = YES
RUWIDO_INSTALL_STAGING = YES
RUWIDO_INSTALL_TARGET = YES
RUWIDO_INSTALL_STAGING_OPT = DESTDIR=$(STAGING_DIR) LDFLAGS=-L$(STAGING_DIR)/usr/lib install

RUWIDO_DEPENDENCIES = uclibc libglib2
$(DL_DIR)/$(RUWIDO_SOURCE):
	 $(WGET) -P $(DL_DIR) $(RUWIDO_SITE)/$(RUWIDO_SOURCE)

ruwido-source: $(DL_DIR)/$(RUWIDO_SOURCE)

$(RUWIDO_DIR)/.unpacked: $(DL_DIR)/$(RUWIDO_SOURCE)
	-mkdir $(RUWIDO_DIR)
	$(RUWIDO_CAT) $(DL_DIR)/$(RUWIDO_SOURCE) | tar -C $(RUWIDO_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(RUWIDO_DIR) package/sky/ruwido/ ruwido-$(RUWIDO_VERSION)\*.patch*
	toolchain/patch-kernel.sh $(RUWIDO_DIR) package/sky/ruwido/ ruwido-hardening-dbus-conf.patch
	toolchain/patch-kernel.sh $(RUWIDO_DIR) package/sky/ruwido/ ruwido-change_pkgconfig.patch
	touch $(RUWIDO_DIR)/.unpacked

$(RUWIDO_DIR)/.configured: $(RUWIDO_DIR)/.unpacked $(RUWIDO_EXTRA_DEPS)
		(cd $(RUWIDO_DIR); PATH=$(TARGET_PATH) libtoolize --force)
		$(CONFIG_UPDATE) $(@D)
		(cd $(RUWIDO_DIR); PATH=$(TARGET_PATH) ./bootstrap)
		(cd $(RUWIDO_DIR) && \
		$(TARGET_CONFIGURE_OPTS)\
		$(TARGET_CONFIGURE_ARGS)\
		./configure \
		    --target=$(GNU_TARGET_NAME) \
		    --host=$(GNU_TARGET_NAME) \
		    --build=$(GNU_HOST_NAME)\
		    --libexec=/usr/bin \
		    --enable-devel \
		    --enable-tests \
		    --enable-db-offline \
		    LIBS= $(STAGING_DIR)/usr/lib/\
		    LDFLAGS=-L$(STAGING_DIR)/usr/lib/)
		touch $@

$(RUWIDO_DIR)/.compiled: $(RUWIDO_DIR)/.configured
ifeq ($(BR2_BOARD_NAME), "bskyb-97445")
	$(MAKE1) -C $(RUWIDO_DIR) 
else
	$(MAKE1) -C $(RUWIDO_DIR) \
		 RCU_KEY="{0xde, 0xad, 0xbe, 0xef, 0xde, 0xad, 0xbe, 0xef, 0xde, 0xad, 0xbe, 0xef, 0xde, 0xad, 0xbe, 0xef}"
endif
	touch $@

$(RUWIDO_DIR)/.installed: $(RUWIDO_DIR)/.compiled
	$(MAKE) DESTDIR=$(STAGING_DIR) -C $(RUWIDO_DIR) install
	$(MAKE) DESTDIR=$(TARGET_DIR) -C $(RUWIDO_DIR) install
	-mkdir -p $(TARGET_DIR)/RCU/etc/ruwido
	-mkdir -p $(TARGET_DIR)/DBUS/etc/dbus-1/system.d/
	cp $(RUWIDO_DIR)/db/db.sqlite $(TARGET_DIR)/RCU/etc/ruwido
	chmod 440 $(TARGET_DIR)/RCU/etc/ruwido/db.sqlite
	cp $(RUWIDO_DIR)/rapid.conf $(TARGET_DIR)/DBUS/etc/dbus-1/system.d/
	mkdir -p $(RUWIDO_TEMP_DIR)/usr/bin
ifeq ($(BR2_BOARD_NAME), "bskyb-97445")
	$(INSTALL) -m 755 $(STAGING_DIR)/usr/bin/ruwido_daemon $(RUWIDO_TEMP_DIR)/usr/bin/
else
	$(INSTALL) -m 755 $(STAGING_DIR)/usr/bin/rapid $(RUWIDO_TEMP_DIR)/usr/bin/
endif
	mkdir -p $(RUWIDO_TEMP_DIR)/RCU/etc/ruwido
	cp $(RUWIDO_DIR)/db/db.sqlite $(RUWIDO_TEMP_DIR)/RCU/etc/ruwido
	chmod 440 $(RUWIDO_TEMP_DIR)/RCU/etc/ruwido/db.sqlite
	mkdir -p $(RUWIDO_TEMP_DIR)/DBUS/etc/dbus-1/system.d/
	cp $(RUWIDO_DIR)/rapid.conf $(RUWIDO_TEMP_DIR)/DBUS/etc/dbus-1/system.d/
	tar cjvf $(RUWIDO_BINARY_DIR)/$(RUWIDO_BINARY_SOURCE) -C $(RUWIDO_TEMP_DIR) .
	rm -rf $(RUWIDO_TEMP_DIR)
	touch $@

ruwido-binary:
	tar xjvf $(RUWIDO_BINARY_DIR)/$(RUWIDO_BINARY_SOURCE) -C $(STAGING_DIR)/
ifeq ($(BR2_BOARD_NAME), "bskyb-97445")
	$(INSTALL) -m 755 $(STAGING_DIR)/usr/bin/ruwido_daemon $(TARGET_DIR)/usr/bin/
else
	$(INSTALL) -m 755 $(STAGING_DIR)/usr/bin/rapid $(TARGET_DIR)/usr/bin/
endif
	-mkdir -p $(TARGET_DIR)/RCU/etc/ruwido
	-mkdir -p $(TARGET_DIR)/DBUS/etc/dbus-1/system.d/
	cp -rf $(STAGING_DIR)/RCU/etc/ruwido/db.sqlite $(TARGET_DIR)/RCU/etc/ruwido/
	chmod 440 $(TARGET_DIR)/RCU/etc/ruwido/db.sqlite
	cp -rf $(STAGING_DIR)/DBUS/etc/dbus-1/system.d/rapid.conf $(TARGET_DIR)/DBUS/etc/dbus-1/system.d/

ifeq ($(wildcard $(RUWIDO_INSTALL_BINARY)),)
ruwido: host-autoconf udev dbus-glib bluez $(RUWIDO_DIR)/.installed
else
ruwido: host-autoconf udev dbus-glib bluez ruwido-binary
endif

ruwido-clean:
	-$(MAKE) -C $(RUWIDO_DIR) distclean
ifeq ($(BR2_BOARD_NAME), "bskyb-97445")
	rm -rf $(STAGING_DIR)/usr/bin/ruwido_daemon
	rm -rf $(TARGET_DIR)/usr/bin/ruwido_daemon
else
	rm -rf $(STAGING_DIR)/usr/bin/rapid
	rm -rf $(TARGET_DIR)/usr/bin/rapid
endif
	rm -rf $(STAGING_DIR)/RCU/etc/ruwido
	rm -rf $(TARGET_DIR)/RCU/etc/ruwido
	rm -rf $(STAGING_DIR)/DBUS/etc/dbus-1/system.d/rapid.conf
	rm -rf $(TARGET_DIR)/DBUS/etc/dbus-1/system.d/rapid.conf
	rm -rf $(RUWIDO_DIR)/.installed
	rm -rf $(RUWIDO_DIR)/.compiled

ruwido-dirclean:
	rm -rf $(RUWIDO_DIR)

ruwido-binary-clean:
	rm -rf $(RUWIDO_INSTALL_BINARY)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_RUWIDO),y)
TARGETS+=ruwido
endif
