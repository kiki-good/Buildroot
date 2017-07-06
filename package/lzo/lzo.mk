#############################################################
#
# lzo
#
#############################################################
LZO_VERSION:=2.03
LZO_SOURCE:=lzo-$(LZO_VERSION).tar.gz
LZO_BINARY_SOURCE:=lzo-$(LZO_VERSION)-binary.tar.bz2
LZO_SITE:=http://www.oberhumer.com/opensource/lzo/download
LZO_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
LZO_BINARY_DIR:=$(LZO_BOARD_PATH)/binaries
LZO_INSTALL_BINARY:=$(LZO_BINARY_DIR)/$(LZO_BINARY_SOURCE)
LZO_AUTORECONF = NO
LZO_INSTALL_STAGING = YES
LZO_INSTALL_TARGET = YES
LZO_INSTALL_STAGING_OPT = CC="$(TARGET_CC)" DESTDIR=$(STAGING_DIR) install
LZO_CONF_ENV =
LZO_CONF_OPT = $(DISABLE_LARGEFILE)
LZO_DEPENDENCIES = uclibc

define LZO_POST_INSTALL_CUSTOMISATION
	mkdir -p $(LZO_BINARY_DIR)/lzo_tmp
	$(MAKE) DESTDIR=$(PWD)/$(LZO_BINARY_DIR)/lzo_tmp -C $(LZO_DIR) install
	tar cjvf $(LZO_BINARY_DIR)/$(LZO_BINARY_SOURCE) -C $(LZO_BINARY_DIR)/lzo_tmp .
	rm -rf $(LZO_BINARY_DIR)/lzo_tmp
endef

lzo-binary:
	tar -xjvf $(LZO_BINARY_DIR)/$(LZO_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(LZO_BINARY_DIR)/$(LZO_BINARY_SOURCE) -C $(TARGET_DIR)/

ifeq ($(wildcard $(LZO_INSTALL_BINARY)),)
$(eval $(call AUTOTARGETS,package,lzo))
else
lzo: lzo-binary
endif

lzo-binary-clean:
	rm -rf $(LZO_INSTALL_BINARY)


LZO_POST_INSTALL_STAGING_HOOKS += LZO_POST_INSTALL_CUSTOMISATION
