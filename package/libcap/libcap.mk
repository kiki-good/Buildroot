LIBCAP_VERSION=2.24
LIBCAP_SOURCE=libcap-$(LIBCAP_VERSION).tar.gz
LIBCAP_SITE=http://localhost/
LIBCAP_DEPENDENCIES = host-libcap
LIBCAP_INSTALL_STAGING=YES
LIBCAP_HOST_DIR=$(BUILD_DIR)/libcap-host/


LIBCAP_DIR=$(BUILD_DIR)/libcap-$(LIBCAP_VERSION)
LIBCAP_BINARY_SOURCE:=libcap-$(LIBCAP_VERSION)-binary.tar.bz2
LIBCAP_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
LIBCAP_BINARY_DIR:=$(LIBCAP_BOARD_PATH)/binaries
LIBCAP_INSTALL_BINARY:=$(LIBCAP_BINARY_DIR)/$(LIBCAP_BINARY_SOURCE)
LIBCAP_TEMP_DIR:=$(LIBCAP_BINARY_DIR)/libcap_tmp


define LIBCAP_POST_INSTALL_PREBUILT_BINARIES
	mkdir -p $(LIBCAP_TEMP_DIR)
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) LIBATTR=no DESTDIR=$(PWD)/$(LIBCAP_TEMP_DIR) \
		prefix=/usr lib=lib install
	rm -rf $(LIBCAP_TEMP_DIR)/usr/share
	rm -f $(addprefix $(LIBCAP_TEMP_DIR)/usr/sbin/,capsh getpcaps)
	tar cjvf $(LIBCAP_BINARY_DIR)/$(LIBCAP_BINARY_SOURCE) -C $(LIBCAP_TEMP_DIR) .
	rm -rf $(LIBCAP_TEMP_DIR)
endef


define LIBCAP_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(TARGET_CONFIGURE_OPTS) $(MAKE) -C $(@D) \
		LIBATTR=no BUILD_CC="$(HOSTCC)"
endef

define LIBCAP_INSTALL_STAGING_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) LIBATTR=no DESTDIR=$(STAGING_DIR) \
		prefix=/usr lib=lib install
endef

define LIBCAP_INSTALL_TARGET_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) LIBATTR=no DESTDIR=$(TARGET_DIR) \
		prefix=/usr lib=lib install
	rm -f $(addprefix $(TARGET_DIR)/usr/sbin/,capsh getpcaps)
endef

define HOST_LIBCAP_BUILD_CMDS
	$(HOST_MAKE_ENV) $(HOST_CONFIGURE_OPTS) $(MAKE) -C $(@D) LIBATTR=no \
		BUILD_CC="$(HOSTCC)"
endef

define HOST_LIBCAP_INSTALL_CMDS
	$(HOST_MAKE_ENV) $(MAKE) -C $(@D) LIBATTR=no DESTDIR=$(LIBCAP_HOST_DIR) \
		prefix=/usr lib=lib install
endef

LIBCAP_POST_INSTALL_STAGING_HOOKS += LIBCAP_POST_INSTALL_PREBUILT_BINARIES

libcap-host: $(eval $(call GENTARGETS,package,libcap,host))

libcap-binary:
	tar -xjvf $(LIBCAP_BINARY_DIR)/$(LIBCAP_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(LIBCAP_BINARY_DIR)/$(LIBCAP_BINARY_SOURCE) -C $(TARGET_DIR)/
	rm -f $(addprefix $(TARGET_DIR)/usr/sbin/,capsh getpcaps)


ifeq ($(wildcard $(LIBCAP_INSTALL_BINARY)),)
libcap: libcap-host $(eval $(call GENTARGETS,package,libcap))
else
libcap: libcap-binary
endif

#############################################################
#
### Toplevel Makefile options
#
###############################################################
ifeq ($(BR2_PACKAGE_LIBCAP),y)
TARGETS+=libcap
endif

