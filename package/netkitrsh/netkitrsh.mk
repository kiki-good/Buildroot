#############################################################
#
# netkitrsh
#
#############################################################
NETKITRSH_VERSION:=0.17
NETKITRSH_SOURCE:=netkit-rsh-$(NETKITRSH_VERSION).tar.gz
NETKITRSH_SITE:=ftp://ftp.uk.linux.org/pub/linux/Networking/netkit/
NETKITRSH_DIR:=$(BUILD_DIR)/netkit-rsh-$(NETKITRSH_VERSION)
NETKITRSH_CAT:=$(ZCAT)
NETKITRSH_BINARY:=rshd/rshd
NETKITRSH_TARGET_BINARY:=usr/sbin/rshd

$(DL_DIR)/$(NETKITRSH_SOURCE):
	 $(WGET) -P $(DL_DIR) $(NETKITRSH_SITE)/$(NETKITRSH_SOURCE)

netkitrsh-source: $(DL_DIR)/$(NETKITRSH_SOURCE)

$(NETKITRSH_DIR)/.unpacked: $(DL_DIR)/$(NETKITRSH_SOURCE)
	$(NETKITRSH_CAT) $(DL_DIR)/$(NETKITRSH_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	# use ANSI syntax
	$(SED) "s/main()/main(void)/;" $(NETKITRSH_DIR)/configure
	# Disable termcap support
	$(SED) "s~\(.*termcap\.h.*\)~/* \1 */~;" $(NETKITRSH_DIR)/rshd/rshd.c
	# don't try to run cross compiled binaries while configuring things
	toolchain/patch-kernel.sh $(NETKITRSH_DIR) package/netkitrsh/ netkitrsh\*.patch
	touch $(NETKITRSH_DIR)/.unpacked

$(NETKITRSH_DIR)/.configured: $(NETKITRSH_DIR)/.unpacked
	(cd $(NETKITRSH_DIR); rm -f config.cache; \
	 PATH=$(TARGET_PATH) CC=$(TARGET_CC) \
	./configure --installroot=$(TARGET_DIR) --with-c-compiler=$(TARGET_CC) \
		--without-pam --without-shadow \
	)
	touch $(NETKITRSH_DIR)/.configured

$(NETKITRSH_DIR)/$(NETKITRSH_BINARY): $(NETKITRSH_DIR)/.configured
	$(MAKE) SUB="rsh rshd rcp" CC="$(TARGET_CC) $(TARGET_SYSROOT)" -C $(NETKITRSH_DIR)
	$(STRIPCMD) $(NETKITRSH_DIR)/$(NETKITRSH_BINARY)

$(TARGET_DIR)/$(NETKITRSH_TARGET_BINARY): $(NETKITRSH_DIR)/$(NETKITRSH_BINARY)
	# Only install a few selected items...
	mkdir -p $(TARGET_DIR)/usr/sbin
	rm -f $(TARGET_DIR)/$(NETKITRSH_TARGET_BINARY)
	cp $(NETKITRSH_DIR)/$(NETKITRSH_BINARY) $(TARGET_DIR)/$(NETKITRSH_TARGET_BINARY)
	cp $(NETKITRSH_DIR)/rcp/rcp $(TARGET_DIR)/usr/bin/rcp
	# Enable rsh in inetd
	$(SED) "s~^#rsh.*~rsh\tstream\ttcp\tnowait\troot\t/usr/sbin/rshd\t/usr/sbin/rshd~;" $(TARGET_DIR)/etc/inetd.conf
	#$(MAKE) DESTDIR=$(TARGET_DIR) CC=$(TARGET_CC) -C $(NETKITRSH_DIR) install
	#rm -rf $(TARGET_DIR)/share/locale $(TARGET_DIR)/usr/info \
	# $(TARGET_DIR)/usr/man $(TARGET_DIR)/usr/share/doc

netkitrsh: uclibc netkitbase $(TARGET_DIR)/$(NETKITRSH_TARGET_BINARY)

netkitrsh-clean:
	#$(MAKE) DESTDIR=$(TARGET_DIR) CC=$(TARGET_CC) -C $(NETKITRSH_DIR) uninstall
	-rm -f $(TARGET_DIR)/usr/sbin/rshd
	-$(MAKE) -C $(NETKITRSH_DIR) clean

netkitrsh-dirclean:
	rm -rf $(NETKITRSH_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_NETKITRSH),y)
TARGETS+=netkitrsh
endif
