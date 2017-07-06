#############################################################
#
# arpcgen
#
#############################################################
ARPCGEN_VERSION:=0.0.1
ARPCGEN_SOURCE:=arpcgen-$(ARPCGEN_VERSION).tar.gz
ARPCGEN_SITE:=http://localhost/
ARPCGEN_CAT:=$(ZCAT)
ARPCGEN_DIR:=$(TOOL_BUILD_DIR)/arpcgen-$(ARPCGEN_VERSION)
ARPCGEN_BINARY:=arpcgen/arpcgen

$(DL_DIR)/$(ARPCGEN_SOURCE):
	mkdir -p $(DL_DIR)

arpcgen-source: $(DL_DIR)/$(ARPCGEN_SOURCE)


#############################################################
#
# build arpcgen for use on the host system
#
#############################################################
$(ARPCGEN_DIR)/.unpacked: $(DL_DIR)/$(ARPCGEN_SOURCE)
	$(ARPCGEN_CAT) $(DL_DIR)/$(ARPCGEN_SOURCE) | tar -C $(TOOL_BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(ARPCGEN_DIR) package/arpcgen/ arpcgen-$(ARPCGEN_VERSION)-\*.patch*
	touch $@

$(ARPCGEN_DIR)/.configured: $(ARPCGEN_DIR)/.unpacked
	(cd $(ARPCGEN_DIR); rm -rf config.cache; \
                $(HOST_CONFIGURE_OPTS) \
		$(HOST_CONFIGURE_ARGS) \
		./configure \
                --target=$(GNU_HOST_NAME) \
                --host=$(GNU_HOST_NAME) \
                --build=$(GNU_HOST_NAME) \
                CFLAGS="$(HOST_CFLAGS)" \
                LDFLAGS="$(HOST_LDFLAGS)" \
	)
	touch $@

$(ARPCGEN_DIR)/$(ARPCGEN_BINARY): $(ARPCGEN_DIR)/.configured
	$(MAKE) -C $(ARPCGEN_DIR)

arpcgen: $(ARPCGEN_DIR)/$(ARPCGEN_BINARY)

arpcgen-clean:
	$(MAKE) -C $(ARPCGEN_DIR) clean

arpcgen-dirclean:
	rm -rf $(ARPCGEN_DIR)


#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_ARPCGEN),y)
TARGETS+=arpcgen
endif
