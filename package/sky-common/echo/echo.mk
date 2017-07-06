#############################################################
#
# echo
#
#############################################################
ECHO_VERSION = 1.0
ECHO_DIR:=$(BUILD_DIR)/echo-$(ECHO_VERSION)
ECHO_SOURCE = echo-$(ECHO_VERSION).tar.bz2
ECHO_CAT:=$(BZCAT)
ECHO_INSTALL_TARGET = YES


$(ECHO_DIR)/.unpacked: $(DL_DIR)/$(ECHO_SOURCE)
	$(ECHO_CAT) $(DL_DIR)/$(ECHO_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	touch $(ECHO_DIR)/.unpacked

$(ECHO_DIR)/.compiled: $(ECHO_DIR)/.unpacked
	$(MAKE) -C $(ECHO_DIR)/src $(TARGET_CONFIGURE_OPTS) $(TARGET_CONFIGURE_ARGS)
	touch $@

$(ECHO_DIR)/.installed: $(ECHO_DIR)/.compiled
	$(MAKE) -C $(ECHO_DIR)/src DESTDIR=$(TARGET_DIR) BUILD_DIR=$(ECHO_DIR) install
	touch $@

echo: $(ECHO_DIR)/.installed

echo-clean:
	cd $(ECHO_DIR)/src;$(MAKE) DESTDIR=$(TARGET_DIR) clean
	rm -rf $(ECHO_DIR)/.installed
	rm -rf $(ECHO_DIR)/.compiled

echo-dirclean:
	rm -rf $(ECHO_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_ECHO),y)
TARGETS+=echo
endif
