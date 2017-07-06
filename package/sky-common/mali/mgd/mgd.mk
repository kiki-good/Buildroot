#############################################################
#
# Mali Graphics Debugger
#
#############################################################
MGD_VERSION:=3.1
MGD_SOURCE:=mgd-$(MGD_VERSION).tar.gz
MGD_CAT:=$(ZCAT)
MGD_DIR:=$(BUILD_DIR)/mgd-$(MGD_VERSION)
MGD_DAEMON:=mgddaemon
MGD_LIBRARY:=libinterceptor.so
MGD_TARGET_DAEMON:=opt/bin/$(MGD_DAEMON)
MGD_TARGET_LIBRARY:=opt/lib/$(MGD_LIBRARY)
MGD_TARGET_UPSTART_CONF:=etc/init/mgddaemon.conf

$(MGD_DIR)/.unpacked: $(DL_DIR)/$(MGD_SOURCE)
	$(MGD_CAT) $(DL_DIR)/$(MGD_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	touch $(MGD_DIR)/.unpacked

$(TARGET_DIR)/$(MGD_TARGET_UPSTART_CONF): package/sky-common/mali/mgd/mgddaemon.conf
	install -D package/sky-common/mali/mgd/mgddaemon.conf $(TARGET_DIR)/$(MGD_TARGET_UPSTART_CONF)

$(TARGET_DIR)/$(MGD_TARGET_DAEMON): $(MGD_DIR)/.unpacked
	install -D $(MGD_DIR)/$(MGD_DAEMON) $(TARGET_DIR)/$(MGD_TARGET_DAEMON)

$(TARGET_DIR)/$(MGD_TARGET_LIBRARY): $(MGD_DIR)/.unpacked
	install -D $(MGD_DIR)/$(MGD_LIBRARY) $(TARGET_DIR)/$(MGD_TARGET_LIBRARY)


mgd: $(TARGET_DIR)/$(MGD_TARGET_DAEMON) $(TARGET_DIR)/$(MGD_TARGET_LIBRARY) $(TARGET_DIR)/$(MGD_TARGET_UPSTART_CONF)

mgd-clean:
	rm -f $(TARGET_DIR)/$(MGD_TARGET_UPSTART_CONF)
	rm -f $(TARGET_DIR)/$(MGD_TARGET_DAEMON)
	rm -f $(TARGET_DIR)/$(MGD_TARGET_LIBRARY)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_MGD),y)
TARGETS+=mgd
endif

