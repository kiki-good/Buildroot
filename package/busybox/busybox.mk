#############################################################
#
# busybox
#
#############################################################


ifeq ($(BR2_PACKAGE_BUSYBOX_SNAPSHOT),y)
# Be aware that this changes daily....
BUSYBOX_DIR:=$(PROJECT_BUILD_DIR)/busybox
BUSYBOX_SOURCE:=busybox-snapshot.tar.bz2
BUSYBOX_SITE:=http://www.busybox.net/downloads/snapshots
else
BUSYBOX_VERSION=$(strip $(subst ",, $(BR2_BUSYBOX_VERSION)))
#"))
BUSYBOX_DIR:=$(PROJECT_BUILD_DIR)/busybox-$(BUSYBOX_VERSION)
BUSYBOX_SOURCE:=busybox-$(BUSYBOX_VERSION).tar.bz2
BUSYBOX_SITE:=http://www.busybox.net/downloads
BUSYBOX_VARINAT=$(strip $(subst ",, $(BR2_SKY_BUILD_TYPE)))
#"))
BUSYBOX_BINARY_SOURCE:=busybox-$(BUSYBOX_VERSION)-$(BUSYBOX_VARINAT)-binary.tar.bz2
BUSYBOX_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
BUSYBOX_BINARY_DIR:=$(BUSYBOX_BOARD_PATH)/binaries
BUSYBOX_INSTALL_BINARY:=$(BUSYBOX_BINARY_DIR)/$(BUSYBOX_BINARY_SOURCE)
endif

BUSYBOX_UNZIP=$(BZCAT)

ifndef BUSYBOX_CONFIG_FILE
BUSYBOX_CONFIG_FILE=$(subst ",, $(strip $(BR2_PACKAGE_BUSYBOX_CONFIG)))
#")
endif

$(DL_DIR)/$(BUSYBOX_SOURCE):
	 $(WGET) -P $(DL_DIR) $(BUSYBOX_SITE)/$(BUSYBOX_SOURCE)

$(BUSYBOX_DIR)/.unpacked: $(DL_DIR)/$(BUSYBOX_SOURCE)
	$(BUSYBOX_UNZIP) $(DL_DIR)/$(BUSYBOX_SOURCE) | tar -C $(PROJECT_BUILD_DIR) $(TAR_OPTIONS) -
ifeq ($(BR2_PACKAGE_SYSKLOGD),y)
	# if we have external syslogd, force busybox to use it
	$(SED) "/#include.*busybox\.h/a#define CONFIG_SYSLOGD" $(BUSYBOX_DIR)/init/init.c
endif
	# Allow busybox patches.
ifeq ($(BR2_PACKAGE_BUSYBOX_SNAPSHOT),y)
	toolchain/patch-kernel.sh $(BUSYBOX_DIR) package/busybox busybox.\*.patch
else
	toolchain/patch-kernel.sh $(BUSYBOX_DIR) package/busybox busybox-$(BUSYBOX_VERSION)-\*.patch
ifeq ($(BR2_SKY_BUILD_TYPE),"prod")
	toolchain/patch-kernel.sh $(BUSYBOX_DIR) package/busybox busybox-turn-off-syslog-prod.patch
endif
endif
	touch $@

$(BUSYBOX_DIR)/.configured: $(BUSYBOX_DIR)/.unpacked $(BUSYBOX_CONFIG_FILE)
	cp -f $(BUSYBOX_CONFIG_FILE) $(BUSYBOX_DIR)/.config
	$(SED) s,^CONFIG_PREFIX=.*,CONFIG_PREFIX=\"$(TARGET_DIR)\", \
		$(BUSYBOX_DIR)/.config
ifeq ($(BR2_BUSYBOX_VERSION_1_0_1),y)
	$(SED) "s,^CROSS.*,CROSS=$(TARGET_CROSS)\n\PREFIX=$(TARGET_DIR),;" \
		$(BUSYBOX_DIR)/Rules.mak
endif
ifeq ($(BR2_BUSYBOX_VERSION_1_1_3),y)
	$(SED) s,^PREFIX=.*,CONFIG_PREFIX=\"$(TARGET_DIR)\", \
		$(BUSYBOX_DIR)/.config
endif
ifeq ($(BR2_BUSYBOX_VERSION_1_2_2_1),y)
	$(SED) s,^CROSS_COMPILER_PREFIX=.*,CROSS_COMPILER_PREFIX=\"$(TARGET_CROSS)\", \
		$(BUSYBOX_DIR)/.config
	$(SED) s,^PREFIX=.*,CROSS_COMPILER_PREFIX=\"$(TARGET_CROSS)\", \
		$(BUSYBOX_DIR)/.config
endif
# id applet breaks on 1.13.0 with old uclibc unless the bb pwd routines are used
ifeq ($(BR2_BUSYBOX_VERSION_1_13_X)$(BR2_UCLIBC_VERSION_0_9_28_3)$(BR2_UCLIBC_VERSION_0_9_29),yy)
	if grep -q 'CONFIG_ID=y' $(BUSYBOX_DIR)/.config; \
	then \
		echo 'warning: CONFIG_ID needs BB_PWD_GRP with old uclibc, enabling' >&2;\
		$(SED) "s/^.*CONFIG_USE_BB_PWD_GRP.*/CONFIG_USE_BB_PWD_GRP=y/;" $(BUSYBOX_DIR)/.config; \
	fi
endif
ifeq ($(BR2_PACKAGE_BUSYBOX_SNAPSHOT),y)
	$(SED) s,^CROSS_COMPILER_PREFIX=.*,CROSS_COMPILER_PREFIX=\"$(TARGET_CROSS)\", \
		$(BUSYBOX_DIR)/.config
	$(SED) s,^PREFIX=.*,CROSS_COMPILER_PREFIX=\"$(TARGET_CROSS)\", \
		$(BUSYBOX_DIR)/.config
endif
ifeq ($(BR2_LARGEFILE),y)
	$(SED) "s/^.*CONFIG_LFS.*/CONFIG_LFS=y/;" $(BUSYBOX_DIR)/.config
	$(SED) "s/^.*CONFIG_FDISK_SUPPORT_LARGE_DISKS.*/CONFIG_FDISK_SUPPORT_LARGE_DISKS=y/;" $(BUSYBOX_DIR)/.config
else
	$(SED) "s/^.*CONFIG_LFS.*/CONFIG_LFS=n/;" $(BUSYBOX_DIR)/.config
	$(SED) "s/^.*FDISK_SUPPORT_LARGE_DISKS.*/CONFIG_FDISK_SUPPORT_LARGE_DISKS=n/;" $(BUSYBOX_DIR)/.config
endif
ifeq ($(BR2_INET_IPV6),y)
	$(SED) "s/^.*CONFIG_FEATURE_IPV6.*/CONFIG_FEATURE_IPV6=y/;" $(BUSYBOX_DIR)/.config
else
	$(SED) "s/^.*CONFIG_FEATURE_IPV6.*/CONFIG_FEATURE_IPV6=n/;" $(BUSYBOX_DIR)/.config
endif
ifeq ($(BR2_PACKAGE_BUSYBOX_SKELETON),y)
	# force mdev on
	$(SED) "s/^.*CONFIG_MDEV.*/CONFIG_MDEV=y/" $(BUSYBOX_DIR)/.config
endif
ifeq ($(BR2_PACKAGE_NETKITBASE),y)
	# disable usage of inetd if netkit-base package is selected
	$(SED) "s/^.*CONFIG_INETD.*/CONFIG_INETD=n/;" $(BUSYBOX_DIR)/.config
	@echo "WARNING!! CONFIG_INETD option disabled!"
endif
ifeq ($(BR2_PACKAGE_NETKITTELNET),y)
	# disable usage of telnetd if netkit-telnetd package is selected
	$(SED) "s/^.*CONFIG_TELNETD.*/CONFIG_TELNETD=n/;" $(BUSYBOX_DIR)/.config
	@echo "WARNING!! CONFIG_TELNETD option disabled!"
endif
	yes "" | $(MAKE) CC=$(TARGET_CC) CROSS_COMPILE="$(TARGET_CROSS)" \
		CROSS="$(TARGET_CROSS)" -C $(BUSYBOX_DIR) oldconfig
	touch $@


$(BUSYBOX_DIR)/busybox: $(BUSYBOX_DIR)/.configured
	$(MAKE) CC=$(TARGET_CC) CROSS_COMPILE="$(TARGET_CROSS)" \
		CROSS="$(TARGET_CROSS)" PREFIX="$(TARGET_DIR)" \
		ARCH=$(KERNEL_ARCH) \
		EXTRA_CFLAGS="$(TARGET_CFLAGS)" -C $(BUSYBOX_DIR)
ifeq ($(BR2_PREFER_IMA)$(BR2_PACKAGE_BUSYBOX_SNAPSHOT),yy)
	rm -f $@
	$(MAKE) CC=$(TARGET_CC) CROSS_COMPILE="$(TARGET_CROSS)" \
		CROSS="$(TARGET_CROSS)" PREFIX="$(TARGET_DIR)" \
		ARCH=$(KERNEL_ARCH) STRIP="$(STRIPCMD)" \
		EXTRA_CFLAGS="$(TARGET_CFLAGS)" -C $(BUSYBOX_DIR) \
		-f scripts/Makefile.IMA
endif

$(TARGET_DIR)/bin/busybox: $(BUSYBOX_DIR)/busybox
ifeq ($(BR2_PACKAGE_BUSYBOX_FULLINSTALL),y)
	$(MAKE) CC=$(TARGET_CC) CROSS_COMPILE="$(TARGET_CROSS)" \
		CROSS="$(TARGET_CROSS)" PREFIX="$(TARGET_DIR)" \
		ARCH=$(KERNEL_ARCH) \
		EXTRA_CFLAGS="$(TARGET_CFLAGS)" -C $(BUSYBOX_DIR) install
		mkdir -p $(BUSYBOX_BINARY_DIR)/busybox_tmp
	$(MAKE) CC=$(TARGET_CC) CROSS_COMPILE="$(TARGET_CROSS)" \
		CROSS="$(TARGET_CROSS)" PREFIX="$(PWD)/$(BUSYBOX_BINARY_DIR)/busybox_tmp" \
		ARCH=$(KERNEL_ARCH) \
		EXTRA_CFLAGS="$(TARGET_CFLAGS)" -C $(BUSYBOX_DIR) install
else
	install -D -m 0755 $(BUSYBOX_DIR)/busybox $(TARGET_DIR)/bin/busybox
endif
	# Just in case - the DHCP script is not present on production builds,
	# so the following is just done on other builds.
ifneq ($(BR2_SKY_BUILD_TYPE),"prod")
	-chmod a+x $(TARGET_DIR)/usr/share/udhcpc/default.script
endif


busybox-temp:
	mkdir -p $(BUSYBOX_BINARY_DIR)/busybox_tmp
	$(SED) s,^CONFIG_PREFIX=.*,CONFIG_PREFIX=\"$(PWD)/$(BUSYBOX_BINARY_DIR)/busybox_tmp\", \
	$(BUSYBOX_DIR)/.config
	$(MAKE) CC=$(TARGET_CC) CROSS_COMPILE="$(TARGET_CROSS)" \
		CROSS="$(TARGET_CROSS)" PREFIX="$(PWD)/$(BUSYBOX_BINARY_DIR)/busybox_tmp" \
		ARCH=$(KERNEL_ARCH) \
		EXTRA_CFLAGS="$(TARGET_CFLAGS)" -C $(BUSYBOX_DIR) oldconfig
	$(MAKE) CC=$(TARGET_CC) CROSS_COMPILE="$(TARGET_CROSS)" \
		CROSS="$(TARGET_CROSS)" PREFIX="$(PWD)/$(BUSYBOX_BINARY_DIR)/busybox_tmp" \
		ARCH=$(KERNEL_ARCH) \
		EXTRA_CFLAGS="$(TARGET_CFLAGS)" -C $(BUSYBOX_DIR) install
		tar cjvf $(BUSYBOX_BINARY_DIR)/$(BUSYBOX_BINARY_SOURCE) -C $(BUSYBOX_BINARY_DIR)/busybox_tmp .
		rm -rf $(BUSYBOX_BINARY_DIR)/busybox_tmp

busybox-binary:
ifeq ($(BR2_PACKAGE_BUSYBOX_FULLINSTALL),y)
	tar -xjvf $(BUSYBOX_BINARY_DIR)/$(BUSYBOX_BINARY_SOURCE) -C $(TARGET_DIR)/
ifneq ($(BR2_SKY_BUILD_TYPE),"prod")
	-chmod a+x $(TARGET_DIR)/usr/share/udhcpc/default.script
endif
else
	mkdir -p $(BUSYBOX_BINARY_DIR)/busybox_tmp
	tar -xjvf $(BUSYBOX_BINARY_DIR)/$(BUSYBOX_BINARY_SOURCE) -C $(BUSYBOX_BINARY_DIR)/busybox_tmp
	install -D -m 0755 $(BUSYBOX_BINARY_DIR)/busybox_tmp/bin/busybox $(TARGET_DIR)/bin/busybox
	rm -rf $(BUSYBOX_BINARY_DIR)/busybox_tmp
endif

ifeq ($(wildcard $(BUSYBOX_INSTALL_BINARY)),)
busybox: uclibc $(TARGET_DIR)/bin/busybox busybox-temp
else
busybox: uclibc busybox-binary
endif

busybox-source: $(DL_DIR)/$(BUSYBOX_SOURCE)

busybox-unpacked: host-sed $(PROJECT_BUILD_DIR) $(BUSYBOX_DIR)/.unpacked

busybox-config: host-sed $(PROJECT_BUILD_DIR) $(BUSYBOX_DIR)/.configured

busybox-menuconfig: host-sed $(PROJECT_BUILD_DIR) busybox-source $(BUSYBOX_DIR)/.configured
	$(MAKE) __TARGET_ARCH=$(ARCH) -C $(BUSYBOX_DIR) menuconfig

busybox-update:
	cp -f $(BUSYBOX_DIR)/.config $(BUSYBOX_CONFIG_FILE)

busybox-clean:
	rm -f $(TARGET_DIR)/bin/busybox
	-$(MAKE) -C $(BUSYBOX_DIR) clean

busybox-dirclean:
	rm -rf $(BUSYBOX_DIR)
#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_BUSYBOX),y)
TARGETS+=busybox
endif
