#############################################################
#
# ifnameindex
#
#############################################################
IFNAMEINDEX_DIR:=$(BUILD_DIR)/nds/ifnameindex
IFNAMEINDEX_BINARY:=libifnameindex.so
IFNAMEINDEX_TARGET_BINARY:=lib/libifnameindex.so

ifnameindex-source:

$(IFNAMEINDEX_DIR)/.unpacked: $(DL_DIR)/$(IFNAMEINDEX_SOURCE)
	-mkdir -p $(IFNAMEINDEX_DIR)
	cp -rv $(TOPDIR)/package/sky-common/nds/ifnameindex/* $(IFNAMEINDEX_DIR)
	touch $@

$(IFNAMEINDEX_DIR)/$(IFNAMEINDEX_BINARY): $(IFNAMEINDEX_DIR)/.unpacked
	make $(TARGET_CONFIGURE_OPTS) -C $(IFNAMEINDEX_DIR) \
		CFLAGS="$(TARGET_CFLAGS)" \
		LDFLAGS="$(TARGET_LDFLAGS)"

$(TARGET_DIR)/$(IFNAMEINDEX_TARGET_BINARY): $(IFNAMEINDEX_DIR)/$(IFNAMEINDEX_BINARY)
	rm -f $(TARGET_DIR)/$(IFNAMEINDEX_TARGET_BINARY)
	$(INSTALL) -D -m 0755 $(IFNAMEINDEX_DIR)/$(IFNAMEINDEX_BINARY) $(TARGET_DIR)/$(IFNAMEINDEX_TARGET_BINARY)
	$(STRIPCMD) $(STRIP_STRIP_ALL) $@

ifnameindex: uclibc $(TARGET_DIR)/$(IFNAMEINDEX_TARGET_BINARY)

ifnameindex-clean:
	-$(MAKE) -C $(IFNAMEINDEX_DIR) clean
	rm -f $(TARGET_DIR)/$(IFNAMEINDEX_TARGET_BINARY)

ifnameindex-dirclean:
	rm -rf $(IFNAMEINDEX_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
TARGETS+=ifnameindex
