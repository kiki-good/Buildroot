#############################################################
#
# mtd provides jffs2 utilities
#
#############################################################
MTD_VERSION:=1.5.0
MTD_SOURCE:=mtd-utils-$(MTD_VERSION).tar.bz2
MTD_SITE:=ftp://ftp.infradead.org/pub/mtd-utils
MTD_HOST_DIR:= $(TOOL_BUILD_DIR)/mtd_orig
MTD_DIR:=$(BUILD_DIR)/mtd_orig
MTD_CAT:=$(BZCAT)
MTD_NAME:=mtd-utils-$(MTD_VERSION)
#############################################################
#
# Build mkfs.jffs2 and sumtool for use on the local host system if
# needed by target/jffs2root.
#
#############################################################
MKFS_JFFS2 := $(MTD_HOST_DIR)/mkfs.jffs2
SUMTOOL := $(MTD_HOST_DIR)/sumtool
MKFS_UBIFS := $(MTD_HOST_DIR)/mkfs.ubifs/mkfs.ubifs

$(DL_DIR)/$(MTD_SOURCE):
	$(WGET) -P $(DL_DIR) $(MTD_SITE)/$(MTD_SOURCE)

$(MTD_HOST_DIR)/.unpacked: $(DL_DIR)/$(MTD_SOURCE)
	$(MTD_CAT) $(DL_DIR)/$(MTD_SOURCE) | tar -C $(TOOL_BUILD_DIR) $(TAR_OPTIONS) -
	rm -rf $(MTD_HOST_DIR)
	mv $(TOOL_BUILD_DIR)/$(MTD_NAME) $(MTD_HOST_DIR)
	toolchain/patch-kernel.sh $(MTD_HOST_DIR) \
		package/mtd/mtd-utils mtd-utils-$(MTD_VERSION)\*.patch
	toolchain/patch-kernel.sh $(MTD_HOST_DIR) \
		package/mtd/mtd-utils mtd-utils-$(MTD_VERSION)-host\*.patch
	touch $@


$(MKFS_JFFS2) $(SUMTOOL): $(MTD_HOST_DIR)/.unpacked
	CC="$(HOSTCC)" CROSS= CFLAGS=-I$(LINUX_HEADERS_DIR)/include \
		$(MAKE) LINUXDIR=$(LINUX_DIR) \
		BUILDDIR=$(MTD_HOST_DIR) \
		-C $(MTD_HOST_DIR) $(MKFS_JFFS2) $(SUMTOOL)

$(MKFS_UBIFS): $(MTD_HOST_DIR)/.unpacked
	CC="$(HOSTCC)" CROSS= CFLAGS=I$(LINUX_HEADERS_DIR)/include \
		$(MAKE) LINUXDIR=$(LINUX_DIR) \
		BUILDDIR=$(MTD_HOST_DIR)/mkfs.ubifs \
		-C $(MTD_HOST_DIR)/mkfs.ubifs \
		$(MKFS_UBIFS) 

mtd-host: $(MKFS_JFFS2) $(SUMTOOL) $(MKFS_UBIFS) 

mtd-host-source: $(DL_DIR)/$(MTD_SOURCE)

mtd-host-clean:
	-$(MAKE) -C $(MTD_HOST_DIR) clean

mtd-host-dirclean:
	rm -rf $(MTD_HOST_DIR)

#############################################################
#
# build mtd for use on the target system
#
#############################################################
$(MTD_DIR)/.unpacked: $(DL_DIR)/$(MTD_SOURCE)
	$(MTD_CAT) $(DL_DIR)/$(MTD_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	mv $(BUILD_DIR)/$(MTD_NAME) $(MTD_DIR)
	toolchain/patch-kernel.sh $(MTD_DIR) package/mtd/mtd-utils mtd-utils-$(MTD_VERSION)\*.patch
	toolchain/patch-kernel.sh $(MTD_DIR) package/mtd/mtd-utils mtd-utils-$(MTD_VERSION)-target\*.patch
	touch $@

MTD_TARGETS_n :=
MTD_TARGETS_y :=

MTD_TARGETS_$(BR2_PACKAGE_MTD_FLASH_ERASE) += flash_erase
MTD_TARGETS_$(BR2_PACKAGE_MTD_FLASH_ERASEALL) += flash_eraseall
MTD_TARGETS_$(BR2_PACKAGE_MTD_FLASH_LOCK) += flash_lock
MTD_TARGETS_$(BR2_PACKAGE_MTD_FLASH_OTP_DUMP) += flash_otp_dump
MTD_TARGETS_$(BR2_PACKAGE_MTD_FLASH_OTP_INFO) += flash_otp_info
MTD_TARGETS_$(BR2_PACKAGE_MTD_FLASH_OTP_LOCK) += flash_otp_lock
MTD_TARGETS_$(BR2_PACKAGE_MTD_FLASH_OTP_WRITE) += flash_otp_write
MTD_TARGETS_$(BR2_PACKAGE_MTD_FLASH_UNLOCK) += flash_unlock
MTD_TARGETS_$(BR2_PACKAGE_MTD_FLASHCP) += flashcp
MTD_TARGETS_$(BR2_PACKAGE_MTD_MKFSJFFS2) += mkfs.jffs2
MTD_TARGETS_$(BR2_PACKAGE_MTD_MKFSJFFS) += mkfs.jffs
MTD_TARGETS_MKFS_$(BR2_PACKAGE_MTD_MKFSUBIFS) += mkfs.ubifs
MTD_TARGETS_$(BR2_PACKAGE_MTD_JFFS2DUMP) += jffs2dump
MTD_TARGETS_$(BR2_PACKAGE_MTD_SUMTOOL) += sumtool
MTD_TARGETS_$(BR2_PACKAGE_MTD_FTL_CHECK) += ftl_check
MTD_TARGETS_$(BR2_PACKAGE_MTD_FTL_FORMAT) += ftl_format
MTD_TARGETS_$(BR2_PACKAGE_MTD_NFTLDUMP) += nftldump
MTD_TARGETS_$(BR2_PACKAGE_MTD_NFTL_FORMAT) += nftl_format
MTD_TARGETS_$(BR2_PACKAGE_MTD_NANDDUMP) += nanddump
MTD_TARGETS_$(BR2_PACKAGE_MTD_NANDTEST)	+= nandtest
MTD_TARGETS_$(BR2_PACKAGE_MTD_NANDWRITE) += nandwrite
MTD_TARGETS_$(BR2_PACKAGE_MTD_MTD_DEBUG) += mtd_debug
MTD_TARGETS_$(BR2_PACKAGE_MTD_DOCFDISK) += docfdisk
MTD_TARGETS_$(BR2_PACKAGE_MTD_DOC_LOADBIOS) += doc_loadbios

MTD_TARGETS_UBI_n :=
MTD_TARGETS_UBI_y :=

MTD_TARGETS_UBI_$(BR2_PACKAGE_MTD_MTDINFO) += mtdinfo
MTD_TARGETS_UBI_$(BR2_PACKAGE_MTD_UBIATTACH) += ubiattach
MTD_TARGETS_UBI_$(BR2_PACKAGE_MTD_UBICRC32) += ubicrc32
MTD_TARGETS_UBI_$(BR2_PACKAGE_MTD_UBIDETACH) += ubidetach
MTD_TARGETS_UBI_$(BR2_PACKAGE_MTD_UBIFORMAT) += ubiformat
MTD_TARGETS_UBI_$(BR2_PACKAGE_MTD_UBIMKVOL) += ubimkvol
MTD_TARGETS_UBI_$(BR2_PACKAGE_MTD_UBINFO) += ubinfo
MTD_TARGETS_UBI_$(BR2_PACKAGE_MTD_UBINIZE) += ubinize
MTD_TARGETS_UBI_$(BR2_PACKAGE_MTD_UBIRENAME) += ubirename
MTD_TARGETS_UBI_$(BR2_PACKAGE_MTD_UBIRMVOL) += ubirmvol
MTD_TARGETS_UBI_$(BR2_PACKAGE_MTD_UBIRSVOL) += ubirsvol
MTD_TARGETS_UBI_$(BR2_PACKAGE_MTD_UBIUPDATEVOL)	+= ubiupdatevol

MTD_TARGETS_MKFSUBIFS_n :=
MTD_TARGETS_MKFSUBIFS_y :=

MTD_TARGETS_MKFSUBIFS_$(BR2_PACKAGE_MTD_MKFSUBIFS) += mkfs.ubifs

MTD_BUILD_UBI_TARGETS := $(addprefix $(MTD_DIR)/ubi-utils/,$(MTD_TARGETS_UBI_y))
MTD_BUILD_MKFSUBIFS_TARGETS := $(addprefix $(MTD_DIR)/mkfs.ubifs/,$(MTD_TARGETS_MKFSUBIFS_y))
MTD_BUILD_TARGETS := $(addprefix $(MTD_DIR)/, $(MTD_TARGETS_y))

ifeq ($(BR2_SKY_TOOLCHAIN_WITHOUT_SYSROOT),)
SYSROOT_FLAGS+=--sysroot $(STAGING_DIR)
endif

$(MTD_BUILD_TARGETS): $(MTD_DIR)/.unpacked
	mkdir -p $(TARGET_DIR)/usr/sbin
	$(MAKE) CFLAGS_EXTRA="-I. -I./include -I$(LINUX_HEADERS_DIR)/include -I$(STAGING_DIR)/usr/include $(TARGET_CFLAGS) $(ZLIBCPPFLAGS) $(SYSROOT_FLAGS)" \
		LDFLAGS="$(SYSROOT_FLAGS) $(TARGET_LDFLAGS) -L$(STAGING_DIR)/../e2fsprogs-1.42.6/lib" \
		BUILDDIR=$(MTD_DIR) \
		ZLIBCPPFLAGS=-I$(STAGING_DIR)/usr/include \
		LZOCPPFLAGS=-I$(STAGING_DIR)/usr/include \
		UUIDCPPFLAGS=-I$(STAGING_DIR)/../e2fsprogs-1.42.6/lib/ \
		CROSS=$(TARGET_CROSS) CC=$(TARGET_CC) LINUXDIR=$(LINUX26_DIR) WITHOUT_XATTR=1 -C $(MTD_DIR) 

MTD_TARGETS := $(addprefix $(TARGET_DIR)/usr/sbin/, $(MTD_TARGETS_y))
MTD_UBI_TARGETS := $(addprefix $(TARGET_DIR)/usr/sbin/, $(MTD_TARGETS_UBI_y))
MTD_MKFSUBIFS_TARGETS := $(addprefix $(TARGET_DIR)/usr/sbin/, $(MTD_TARGETS_MKFSUBIFS_y))

$(MTD_TARGETS): $(TARGET_DIR)/usr/sbin/% : $(MTD_DIR)/%
	cp -f $< $@
	-$(STRIPCMD) $@

$(MTD_UBI_TARGETS): $(TARGET_DIR)/usr/sbin/% : $(MTD_DIR)/ubi-utils/%
	cp -f $< $@
	-$(STRIPCMD) $@

$(MTD_MKFSUBIFS_TARGETS): $(TARGET_DIR)/usr/sbin/% : $(MTD_DIR)/mkfs.ubifs/%
	cp -f $< $@
	-$(STRIPCMD) $@

mtd: zlib lzo e2fsprogs $(MTD_TARGETS) $(MTD_UBI_TARGETS) $(MTD_MKFSUBIFS_TARGETS) 

mtd-source: $(DL_DIR)/$(MTD_SOURCE)

mtd-clean:
	-$(MAKE) -C $(MTD_DIR) clean

mtd-dirclean:
	rm -rf $(MTD_DIR)

mtd-tests:
	-$(MAKE) -C $(MTD_DIR)/tests

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_MTD),y)
TARGETS+=mtd
endif
