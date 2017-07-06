#############################################################
#
# resolvrefresh
#
#############################################################
RESOLVREFRESH_DIR:=$(BUILD_DIR)/nds/resolv-refresh
RESOLVREFRESH_BINARY:=libresolv-refresh.so
RESOLVREFRESH_TARGET_BINARY:=lib/libresolv-refresh.so

resolvrefresh-source:

$(RESOLVREFRESH_DIR)/.unpacked: $(DL_DIR)/$(RESOLVREFRESH_SOURCE)
	-mkdir -p $(RESOLVREFRESH_DIR)
	cp -rv $(TOPDIR)/package/sky-common/nds/resolv-refresh/* $(RESOLVREFRESH_DIR)
	touch $@

$(RESOLVREFRESH_DIR)/$(RESOLVREFRESH_BINARY): $(RESOLVREFRESH_DIR)/.unpacked
	make $(TARGET_CONFIGURE_OPTS) -C $(RESOLVREFRESH_DIR) \
		CFLAGS="$(TARGET_CFLAGS)" \
		LDFLAGS="$(TARGET_LDFLAGS)"

$(TARGET_DIR)/$(RESOLVREFRESH_TARGET_BINARY): $(RESOLVREFRESH_DIR)/$(RESOLVREFRESH_BINARY)
	rm -f $(TARGET_DIR)/$(RESOLVREFRESH_TARGET_BINARY)
	$(INSTALL) -D -m 0755 $(RESOLVREFRESH_DIR)/$(RESOLVREFRESH_BINARY) $(TARGET_DIR)/$(RESOLVREFRESH_TARGET_BINARY)
	$(STRIPCMD) $(STRIP_STRIP_ALL) $@

resolvrefresh: uclibc $(TARGET_DIR)/$(RESOLVREFRESH_TARGET_BINARY)

resolvrefresh-clean:
	-$(MAKE) -C $(RESOLVREFRESH_DIR) clean
	rm -f $(TARGET_DIR)/$(RESOLVREFRESH_TARGET_BINARY)

resolvrefresh-dirclean:
	rm -rf $(RESOLVREFRESH_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
TARGETS+=resolvrefresh
