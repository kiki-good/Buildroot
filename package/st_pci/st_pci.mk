ST_PCI_MODULES_VERSION:=
ST_PCI_MODULES_SITE:= 
ST_PCI_MODULES_PATH:=$(LINUX_DIR)/drivers/pci/host
ST_PCI_MODULES_BINARY:=$(LINUX_DIR)/drivers/pci/host/pci-st.ko
ST_PCI_MODULES_DEPENDENCIES:=
ifeq ($(BR2_PROJECT),"bskyb-xwing412")
ST_PCI_INSTALL_PATH:=lib/modules/3.10.27-xwing-h412/
endif
ifeq ($(BR2_PROJECT),"bskyb-xwing-hip")
ST_PCI_INSTALL_PATH:=lib/modules/3.10.27-xwing-hip/
endif
ifeq ($(BR2_PROJECT),"bskyb-mr412")
ST_PCI_INSTALL_PATH:=lib/modules/3.10.27-mrbox-h412/
endif

ST_PCI:
	$(MAKE) -C $(LINUX_DIR) $(LINUX_MAKE_FLAGS) M=$(LINUX_DIR)/drivers/pci/host/ ARCH=$(ARCH) CROSS_COMPILE=$(TARGET_CROSS) modules
	mkdir -p $(TARGET_DIR)/$(ST_PCI_INSTALL_PATH)
ifeq ($(BR2_PROJECT),"bskyb-xwing412")
	install -D $(LINUX_DIR)/$(ST_PCI_MODULES_BINARY) $(TARGET_DIR)/lib/modules/3.10.27-xwing-h412/
endif
ifeq ($(BR2_PROJECT),"bskyb-xwing-hip")
	install -D $(LINUX_DIR)/$(ST_PCI_MODULES_BINARY) $(TARGET_DIR)/lib/modules/3.10.27-xwing-hip/
endif
ifeq ($(BR2_PROJECT),"bskyb-mr412")
	install -D $(LINUX_DIR)/$(ST_PCI_MODULES_BINARY) $(TARGET_DIR)/lib/modules/3.10.27-mrbox-h412/
endif

ST_PCI-clean:
	$(MAKE) -C $(LINUX_DIR) $(LINUX_MAKE_FLAGS) M=$(LINUX_DIR)/drivers/pci/host/ ARCH=$(ARCH) CROSS_COMPILE=$(TARGET_CROSS) clean
ifeq ($(BR2_PROJECT),"bskyb-xwing412")
	rm $(TARGET_DIR)/lib/modules/3.10.27-xwing-h412/pci-st.ko
endif
ifeq ($(BR2_PROJECT),"bskyb-xwing-hip")
	rm $(TARGET_DIR)/lib/modules/3.10.27-xwing-hip/pci-st.ko
endif
ifeq ($(BR2_PROJECT),"bskyb-mr412")
	rm $(TARGET_DIR)/lib/modules/3.10.27-mrbox-h412/pci-st.ko
endif

#############################################################
#
### Toplevel Makefile options
#
###############################################################
ifeq ($(BR2_PACKAGE_ST_PCI),y)
TARGETS+=ST_PCI
endif


