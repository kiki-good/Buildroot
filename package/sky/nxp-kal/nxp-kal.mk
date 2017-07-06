#############################################################
#
# NXP KAL Kernel Device Driver
#
#############################################################
NXP_KAL_VERSION:=7.1.0
NXP_KAL_SOURCE:=$(SKY_DL_DIR)/nxp-kal-$(NXP_KAL_VERSION).tar.bz2
NXP_KAL_DIR:=$(BUILD_DIR)/nxp-kal-$(NXP_KAL_VERSION)
NXP_KAL_BINARY:=cnxt_kernel_kal.ko

$(DL_DIR)/$(NXP_KAL_SOURCE):
	$(error Missing source package for NXP KAL device driver '$@')

$(NXP_KAL_DIR)/.unpacked: $(DL_DIR)/$(NXP_KAL_SOURCE)
	$(BZCAT) $(DL_DIR)/$(NXP_KAL_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(NXP_KAL_DIR) package/sky/nxp-kal nxp-kal\*.patch
	touch $@

$(NXP_KAL_DIR)/$(NXP_KAL_BINARY): $(NXP_KAL_DIR)/.unpacked
	$(MAKE) CC=$(TARGET_CC) AR=$(TARGET_AR) LD=$(TARGET_LD) KDIR=$(LINUX26_DIR) -C $(NXP_KAL_DIR)

nxp-kal-install: $(NXP_KAL_DIR)/$(NXP_KAL_BINARY)
	install -c $(NXP_KAL_DIR)/$(NXP_KAL_BINARY) $(TARGET_DIR)/lib/modules/$(LINUX26_VERSION)/$(NXP_KAL_BINARY)

nxp-kal: linux26 $(NXP_KAL_DIR)/$(NXP_KAL_BINARY) nxp-kal-install

nxp-kal-source: $(DL_DIR)/$(NXP_KAL_SOURCE)

nxp-kal-unpacked: $(NXP_KAL_DIR)/.unpacked

nxp-kal-clean:
	rm -f $(TARGET_DIR)/lib/modules/$(LINUX26_VERSION)/$(NXP_KAL_BINARY)
	-$(MAKE) -C $(NXP_KAL_DIR) clean

nxp-kal-dirclean:
	rm -rf $(NXP_KAL_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_NXP_KAL),y)
TARGETS+=nxp-kal
endif
