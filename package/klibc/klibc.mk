#############################################################
#
# klibc
#
#############################################################
KLIBC_VERSION=2.0.3
KLIBC_SOURCE=klibc-$(KLIBC_VERSION).tar.bz2 
KLIBC_SITE=https://www.kernel.org/pub/linux/libs/klibc/2.0
KLIBC_DIR=$(BUILD_DIR)/klibc-$(KLIBC_VERSION)


$(DL_DIR)/$(KLIBC_SOURCE):
	$(WGET) -P $(DL_DIR) $(KLIBC_SITE)/$(KLIBC_SOURCE)

$(KLIBC_DIR)/.unpacked: $(DL_DIR)/$(KLIBC_SOURCE)
	$(BZCAT) $(DL_DIR)/$(KLIBC_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(KLIBC_DIR) package/klibc klibc\*.patch
	touch $@


$(KLIBC_DIR)/.configured: $(KLIBC_DIR)/.unpacked
	$(SED) "s,# CONFIG_AEABI is not set,CONFIG_AEABI=y," $(KLIBC_DIR)/defconfig
	touch $@


## [bSkyb]
## There is a problem with klibc on arm (and only arm) where the kernel
## header files aren't in the klibc assumed places.  The solution is to
## get the kernel to install it's user header and then tell klibc to use
## those as oppose to straight from the kernel tree
$(KLIBC_DIR)/.kernel_usr_headers: $(KLIBC_DIR)/.configured
	$(MAKE1) -C $(LINUX26_DIR) \
	        ARCH=$(KERNEL_ARCH) \
	        INSTALL_HDR_PATH=$(KLIBC_DIR)/kernel_usr_headers \
	        headers_install
	$(SED) "s,(KLIBCKERNELSRC)/include,(srctree)/kernel_usr_headers/include," $(KLIBC_DIR)/scripts/Kbuild.klibc
	touch $@


$(KLIBC_DIR)/usr/kinit/run-init/static/run-init: $(KLIBC_DIR)/.kernel_usr_headers
	$(MAKE1) CROSS_COMPILE=$(KERNEL_CROSS) \
	        ARCH=$(KERNEL_ARCH) \
	        KLIBCKERNELSRC=$(LINUX26_DIR) \
	        -C $(KLIBC_DIR)



klibc: $(KLIBC_DIR)/usr/kinit/run-init/static/run-init

klibc-source: $(DL_DIR)/$(KLIBC_SOURCE)

klibc-clean:
	-$(MAKE1) -C $(KLIBC_DIR) clean

klibc-dirclean:
	rm -rf $(KLIBC_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_KLIBC),y)
TARGETS+=klibc
endif
