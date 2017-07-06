#############################################################
#
# XZ Utils
#
#############################################################
XZ_UTILS_VERSION:=4.999.9beta
XZ_UTILS_SOURCE:=xz-$(XZ_UTILS_VERSION).tar.gz
XZ_UTILS_CAT:=$(ZCAT)
XZ_UTILS_SITE:=http://tukaani.org/xz
XZ_UTILS_HOST_DIR:=$(TOOL_BUILD_DIR)/xz-$(XZ_UTILS_VERSION)
XZ_UTILS_TARGET_DIR:=$(BUILD_DIR)/xz-$(XZ_UTILS_VERSION)
XZ_UTILS_TARGET_BINARY:=bin/xz

# xz utils binary for use on the host
XZ_UTILS=$(TOOL_BUILD_DIR)/bin/xz
HOST_XZ_UTILS_IF_ANY=$(shell $(CONFIG_SHELL) toolchain/dependencies/check-host-lzma.sh)


$(DL_DIR)/$(XZ_UTILS_SOURCE):
	$(WGET) -P $(DL_DIR) $(XZ_UTILS_SITE)/$(XZ_UTILS_SOURCE)

######################################################################
#
# xz host
#
######################################################################

$(XZ_UTILS_HOST_DIR)/.unpacked: $(DL_DIR)/$(XZ_UTILS_SOURCE)
	$(XZ_UTILS_CAT) $(DL_DIR)/$(XZ_UTILS_SOURCE) | tar -C $(TOOL_BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(XZ_UTILS_HOST_DIR) package/xz-utils/ xz-utils\*.patch
	touch $@

$(XZ_UTILS_HOST_DIR)/.configured: $(XZ_UTILS_HOST_DIR)/.unpacked
	(cd $(XZ_UTILS_HOST_DIR); rm -f config.cache;\
		CC="$(HOSTCC)" \
		CXX="$(HOSTCXX)" \
		./configure \
		--prefix=/ \
	)
	touch $@

$(XZ_UTILS_HOST_DIR)/src/xz/xz: $(XZ_UTILS_HOST_DIR)/.configured
	$(MAKE) -C $(XZ_UTILS_HOST_DIR) all
	touch -c $@

$(STAGING_DIR)/bin/xz: $(XZ_UTILS_HOST_DIR)/src/xz/xz
	$(MAKE) DESTDIR=$(STAGING_DIR) -C $(XZ_UTILS_HOST_DIR) install
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/lib\',g" \
		$(STAGING_DIR)/lib/liblzma.la

.PHONY: xz-utils-host use-xz-utils-host-binary
use-xz-utils-host-binary:
	if [ ! -f "$(TOOL_BUILD_DIR)/bin/xz" ]; then \
		[ -d $(TOOL_BUILD_DIR)/bin ] || mkdir -p $(TOOL_BUILD_DIR)/bin; \
		ln -sf "$(HOST_XZ_UTILS_IF_ANY)" "$(TOOL_BUILD_DIR)/bin/xz"; \
	fi

build-xz-utils-host-binary: $(XZ_UTILS_HOST_DIR)/src/xz/xz
	-rm -f $(TOOL_BUILD_DIR)/bin/xz
	-rm -f $(TOOL_BUILD_DIR)/bin/lzma
	[ -d $(TOOL_BUILD_DIR)/bin ] || mkdir $(TOOL_BUILD_DIR)/bin
	cp -pf $(XZ_UTILS_HOST_DIR)/src/xz/xz $(TOOL_BUILD_DIR)/bin/xz
	ln -s $(TOOL_BUILD_DIR)/bin/xz $(TOOL_BUILD_DIR)/bin/lzma

host-xz-utils: build-xz-utils-host-binary

xz-utils-host: $(STAGING_DIR)/bin/xz

xz-utils-host-clean:
	rm -f $(STAGING_DIR)/bin/xz
	rm -f $(STAGING_DIR)/bin/lzma
	-$(MAKE) -C $(XZ_UTILS_HOST_DIR) clean

xz-utils-host-dirclean:
	rm -rf $(XZ_UTILS_HOST_DIR)

xz-utils-host-install: /usr/local/bin/xzcat


#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_XZ_UTILS_HOST),y)
TARGETS+=xz-utils-host
HOST_SOURCE+=xz-utils-source
endif

