include package/sky-common/nds/*/*.mk

#############################################################
#
# ndsmw
#
#############################################################

NDS_VARIANT:=$(subst ",,$(BR2_SKY_BUILD_TYPE))
#")
NDS_PROJECT:=$(subst ",,$(BR2_PROJECT))
#")

NDS_MW_SOURCE:=mw-epg-$(NDS_PROJECT)-$(NDS_VARIANT).tar.bz2
NDS_MW_CAT:=$(BZCAT)
NDS_MW_DIR:=$(BUILD_DIR)/nds-mw
# Any file which must be in the binary package
NDS_MW_FILE:=/etc/start-mw.sh
# The MW startup script
NDS_MW_STARTUP_SCRIPT:=/etc/start-mw.sh

nds-mw-source: $(DL_DIR)/$(NDS_MW_SOURCE)

$(NDS_MW_DIR)/.unpacked: $(DL_DIR)/$(NDS_MW_SOURCE) $(TARGET_DIR)/$(NDS_MW_FILE)
	@echo "Unpacking $(DL_DIR)/$(NDS_MW_SOURCE)..."
	$(NDS_MW_CAT) $(DL_DIR)/$(NDS_MW_SOURCE) | tar -C $(TARGET_DIR) $(TAR_OPTIONS) -
	#sed -i '/#ABORT BUSY ABORT/d' $(TARGET_DIR)/NDS/config/chat_script.conf
	-@mkdir -p $(NDS_MW_DIR)
	touch $@

$(NDS_MW_STARTUP_SCRIPT):
	$(if $(shell test -e $(TARGET_DIR)/$@ && test ! -x $(TARGET_DIR)/$@ && echo err), \
		$(error The $@ script in the NDS MW package is not executable! It must be executable if present))

nds-mw-check: $(NDS_MW_STARTUP_SCRIPT)

$(TARGET_DIR)/$(NDS_MW_FILE):

nds-mw: uclibc $(NDS_MW_DIR)/.unpacked nds-mw-check

nds-mw-clean:
	$(RM) $(NDS_MW_DIR)/.unpacked

nds-mw-dirclean:
	rm -rf $(NDS_MW_DIR)

#############################################################

NDS_DRV_SOURCE:=nds-drv-$(NDS_PROJECT)-$(NDS_VARIANT).tar.bz2
NDS_DRV_CAT:=$(BZCAT)
NDS_DRV_DIR:=$(BUILD_DIR)/nds-drv

# Any file which must be in the binary package
NDS_DRV_FILE:=/etc/load-nds-drivers.sh
# The MW driver startup script
NDS_DRV_STARTUP_SCRIPT:=/etc/load-nds-drivers.sh

nds-drv-source: $(DL_DIR)/$(NDS_DRV_SOURCE)

$(NDS_DRV_DIR)/.unpacked: $(DL_DIR)/$(NDS_DRV_SOURCE) $(TARGET_DIR)/$(NDS_DRV_FILE)
	@echo "Unpacking $(DL_DIR)/$(NDS_DRV_SOURCE)..."
	$(NDS_DRV_CAT) $(DL_DIR)/$(NDS_DRV_SOURCE) | tar -C $(TARGET_DIR) $(TAR_OPTIONS) -
	-@mkdir -p $(NDS_DRV_DIR)
	touch $@

$(NDS_DRV_STARTUP_SCRIPT):
	$(if $(shell test -e $(TARGET_DIR)/$@ && test ! -x $(TARGET_DIR)/$@ && echo err), \
		$(error The $@ script in the NDS MW package is not executable! It must be executable if present))

nds-drv-check: $(NDS_DRV_STARTUP_SCRIPT)

$(TARGET_DIR)/$(NDS_DRV_FILE):

nds-drv: uclibc $(NDS_DRV_DIR)/.unpacked nds-drv-check

nds-drv-clean:
	$(RM) $(NDS_DRV_DIR)/.unpacked

nds-drv-dirclean:
	rm -rf $(NDS_DRV_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_SKY_NDS_DRIVERS),y)
TARGETS+=nds-drv
endif
ifeq ($(BR2_PACKAGE_SKY_NDS_MW),y)
TARGETS+=nds-mw
endif
