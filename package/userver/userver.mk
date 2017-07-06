#############################################################
#
# userver
#
#############################################################
USERVER_VERSION = 0.01.64.0052
USERVER_DIR:=$(BUILD_DIR)/userver-$(USERVER_VERSION)
USERVER_SOURCE = userver-$(USERVER_VERSION).tar.bz2
USERVER_CAT:=$(BZCAT)

$(DL_DIR)/$(USERVER_SOURCE):
	 $(WGET) -P $(DL_DIR) $(USERVER_SITE)/$(USERVER_SOURCE)

userver-source: $(DL_DIR)/$(USERVER_SOURCE)

$(USERVER_DIR)/.unpacked: $(DL_DIR)/$(USERVER_SOURCE)
	-mkdir $(USERVER_DIR)
	$(USERVER_CAT) $(DL_DIR)/$(USERVER_SOURCE) | tar -C $(USERVER_DIR) $(TAR_OPTIONS) -
	touch $(USERVER_DIR)/.unpacked

$(USERVER_DIR)/.configured: $(USERVER_DIR)/.unpacked $(USERVER_EXTRA_DEPS)
		touch $@

$(USERVER_DIR)/.compiled: $(USERVER_DIR)/.configured
	touch $@

$(USERVER_DIR)/.installed: $(USERVER_DIR)/.compiled
	$(INSTALL) $(USERVER_DIR)/$(BR2_BOARD_NAME)/userver $(TARGET_DIR)/usr/bin/
	$(INSTALL) $(USERVER_DIR)/userver.conf $(TARGET_DIR)/DBUS/etc/dbus-1/system.d/
	touch $@

userver: $(USERVER_DIR)/.installed
userver-clean:
	rm -rf $(TARGET_DIR)/usr/bin/userver
	rm -rf $(TARGET_DIR)/DBUS/etc/dbus-1/system.d/userver.conf
	rm -rf $(USERVER_DIR)/.installed
	rm -rf $(USERVER_DIR)/.compiled

userver-dirclean:
	rm -rf $(USERVER_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_USERVER),y)
TARGETS+=userver
endif
