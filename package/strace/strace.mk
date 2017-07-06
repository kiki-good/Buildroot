#############################################################
#
# strace
#
#############################################################
STRACE_VERSION:=4.5.18
STRACE_SOURCE:=strace-$(STRACE_VERSION).tar.bz2
STRACE_SITE:=http://$(BR2_SOURCEFORGE_MIRROR).dl.sourceforge.net/sourceforge/strace
STRACE_DIR:=$(BUILD_DIR)/strace-$(STRACE_VERSION)
STRACE_BINARY:=strace
STRACE_TARGET_BINARY:=usr/bin/strace

$(DL_DIR)/$(STRACE_SOURCE):
	$(WGET) -P $(DL_DIR) $(STRACE_SITE)/$(STRACE_SOURCE)

$(STRACE_DIR)/.source: $(DL_DIR)/$(STRACE_SOURCE)
	$(BZCAT) $(DL_DIR)/$(STRACE_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(STRACE_DIR) package/strace/ strace\*.patch
ifeq ($(BR2_TOOLCHAIN_EXTERNAL_PREFIX),"armv7-linux")
	$(CONFIG_UPDATE) $(STRACE_DIR)
endif
	touch $@

$(STRACE_DIR)/.configured: $(STRACE_DIR)/.source
	(cd $(STRACE_DIR); rm -f config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		CFLAGS="$(TARGET_CFLAGS)" \
		./configure \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--with-cc=$(TARGET_CC) \
		--with-linker=$(TARGET_CROSS)ld \
		--prefix=/usr \
	)
	touch $@


$(STRACE_DIR)/$(STRACE_BINARY): $(STRACE_DIR)/.configured
	    $(TARGET_CONFIGURE_OPTS) $(MAKE) -C $(STRACE_DIR)

$(TARGET_DIR)/$(STRACE_TARGET_BINARY): $(STRACE_DIR)/$(STRACE_BINARY)
	$(MAKE) $(TARGET_CONFIGURE_OPTS) DESTDIR=$(TARGET_DIR) \
		install='install -D' -C $(STRACE_DIR) lib64=/lib \
		ldconfig='/bin/true' install
	rm -Rf $(TARGET_DIR)/usr/share/man
	$(STRIPCMD) $(STRIP_STRIP_ALL) $(TARGET_DIR)/usr/bin/strace

strace: uclibc $(TARGET_DIR)/$(STRACE_TARGET_BINARY)

strace-source: $(DL_DIR)/$(STRACE_SOURCE)
	rm -f $(TARGET_DIR)/usr/bin/strace

strace-dirclean:
	rm -rf $(STRACE_DIR)

ifeq ($(BR2_PACKAGE_STRACE),y)
TARGETS+=strace
endif

