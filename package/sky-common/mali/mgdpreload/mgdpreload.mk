#############################################################
#
# Mali Graphics Debugger Preload Library
#
# This preload library intercepts the socket calls for both
# the daemon and interceptor library to get it to use
# unix domain sockets with real pathnames, not abstract ones
#
#############################################################
MGD_PRELOAD_VERSION:=3.1
MGD_PRELOAD_SOURCE:=mgd-preload-$(MGD_PRELOAD_VERSION).tar.gz
MGD_PRELOAD_CAT:=$(ZCAT)
MGD_PRELOAD_DIR:=$(BUILD_DIR)/mgd-preload-$(MGD_PRELOAD_VERSION)
MGD_PRELOAD_LIBRARY:=libmgdpreload.so
MGD_PRELOAD_TARGET_LIBRARY:=opt/lib/$(MGD_PRELOAD_LIBRARY)

$(MGD_PRELOAD_DIR)/.unpacked: $(DL_DIR)/$(MGD_PRELOAD_SOURCE)
	$(MGD_PRELOAD_CAT) $(DL_DIR)/$(MGD_PRELOAD_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	touch $(MGD_PRELOAD_DIR)/.unpacked

$(MGD_PRELOAD_DIR)/$(MGD_PRELOAD_LIBRARY): $(MGD_PRELOAD_DIR)/.unpacked
	-$(MAKE) CC=$(TARGET_CC) LD=$(TARGET_LD) -C $(MGD_PRELOAD_DIR)

$(TARGET_DIR)/$(MGD_PRELOAD_TARGET_LIBRARY): $(MGD_PRELOAD_DIR)/$(MGD_PRELOAD_LIBRARY)
	install -D $(MGD_PRELOAD_DIR)/$(MGD_PRELOAD_LIBRARY) $(TARGET_DIR)/$(MGD_PRELOAD_TARGET_LIBRARY)

mgdpreload: $(TARGET_DIR)/$(MGD_PRELOAD_TARGET_LIBRARY)

mgdpreload-clean:
	-$(MAKE) -C $(MGD_PRELOAD_DIR) clean
	rm -f $(TARGET_DIR)/$(MGD_PRELOAD_TARGET_LIBRARY)


#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_MGD_PRELOAD),y)
TARGETS+=mgdpreload
endif

