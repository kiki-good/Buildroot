#############################################################
#
# openssl
#
#############################################################
ifeq ($(BR2_ARCH_IS_64),y)
OPENSSL_VERSION = 1.1.0d
#OPENSSL_VERSION = 1.0.2k
#OPENSSL_VERSION = 1.0.1t
else
OPENSSL_VERSION = 1.0.1t
endif
OPENSSL_SITE = http://www.openssl.org/source
OPENSSL_INSTALL_STAGING = YES
OPENSSL_DEPENDENCIES = zlib
OPENSSL_TARGET_ARCH = generic32
OPENSSL_BINARY_SOURCE:=openssl-$(OPENSSL_VERSION)-binary.tar.bz2
OPENSSL_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
OPENSSL_BINARY_DIR:=$(OPENSSL_BOARD_PATH)/binaries
OPENSSL_INSTALL_BINARY:=$(OPENSSL_BINARY_DIR)/$(OPENSSL_BINARY_SOURCE)
OPENSSL_TEMP_DIR:=$(OPENSSL_BINARY_DIR)/openssl_tmp

ifeq ($(BR2_ARCH_IS_64),y)
define OPENSSL_POST_APPLY_64BITPATCH
toolchain/patch-kernel.sh $(OPENSSL_DIR) package/openssl/64bitPatch openssl-$(OPENSSL_VERSION)\*.patch*
endef

OPENSSL_POST_PATCH_HOOKS += OPENSSL_POST_APPLY_64BITPATCH
else
define OPENSSL_POST_APPLY_32BITPATCH
#toolchain/patch-kernel.sh $(OPENSSL_DIR) package/openssl/32bitPatch openssl-$(OPENSSL_VERSION)\*.patch*
toolchain/patch-kernel.sh $(OPENSSL_DIR) package/openssl/32bitPatch openssl-\*.patch*
endef
OPENSSL_POST_PATCH_HOOKS += OPENSSL_POST_APPLY_32BITPATCH
endif

# Some architectures are optimized in OpenSSL
ifeq ($(ARCH),arm)
ifneq ($(BR2_generic_arm),y)
ifneq ($(BR2_arm610),y)
ifneq ($(BR2_arm710),y)
	OPENSSL_TARGET_ARCH = armv4
endif
endif
endif
endif
ifeq ($(ARCH),powerpc)
	OPENSSL_TARGET_ARCH = ppc
endif
ifeq ($(ARCH),x86_64)
	OPENSSL_TARGET_ARCH = x86_64
endif

# [Sky] All our architectures are armv7 and can be optimised in OpenSSL
OPENSSL_TARGET_CFLAGS = $(TARGET_CFLAGS)
ifeq ($(BR2_TARGET_SKY),y)
ifeq ($(BR2_ARCH_IS_64),y)
ifeq ($(BR2_aarch64),y) 
 	OPENSSL_TARGET_ARCH = aarch64
#        OPENSSL_TARGET_CFLAGS += -march=armv7-a
endif
else
	OPENSSL_TARGET_ARCH = armv4
	OPENSSL_TARGET_CFLAGS += -march=armv7-a
endif
endif

$(info $$OPENSSL_TARGET_CFLAGS================ is [${OPENSSL_TARGET_CFLAGS}])
$(info $$OPENSSL_TARGET_ARCH================ is [${OPENSSL_TARGET_ARCH}])


ifeq ($(BR2_ARCH_IS_64),y)
define OPENSSL_CONFIGURE_CMDS
        (cd $(@D); \
                $(TARGET_CONFIGURE_ARGS) \
                $(TARGET_CONFIGURE_OPTS) \
                ./Configure \
                        linux-$(OPENSSL_TARGET_ARCH) \
                        --prefix=$(TARGET_DIR)/usr \
                        --openssldir=$(TARGET_DIR)/etc/ssl \
                        threads \
                        shared \
                        no-idea \
                        no-rc5 \
                        no-camellia \
                        no-mdc2 \
                        zlib-dynamic \
                        no-hw \
                        no-md2  \
                        no-md4  \
                        no-rc2  \
                        no-sse2 \
                        no-bf   \
        )

# TODO for OPTIMIZATION       
#        $(SED) "s:-march=[-a-z0-9] ::" -e "s:-mcpu=[-a-z0-9] ::g" $(@D)/Makefile
#        $(SED) "s:-O[0-9]:$(OPENSSL_TARGET_CFLAGS):" $(@D)/Makefile
endef
else
define OPENSSL_CONFIGURE_CMDS
	(cd $(@D); \
		$(TARGET_CONFIGURE_ARGS) \
		$(TARGET_CONFIGURE_OPTS) \
		./Configure \
			linux-$(OPENSSL_TARGET_ARCH) \
			--prefix=/usr \
			--openssldir=/etc/ssl \
			threads \
			shared \
			no-idea \
			no-rc5 \
			no-camellia \
			no-mdc2 \
			enable-tlsext \
			zlib-dynamic \
			no-jpake \
			no-hw \
			no-krb5	\
			no-md2	\
			no-md4	\
			no-rc2	\
			no-ripemed	\
			no-sse2	\
			no-bf	\
	)
	(cd $(@D)/include/openssl/; \
		ln -s ../../crypto/mdc2/mdc2.h mdc2.h; \
		ln -s ../../crypto/md4/md4.h md4.h; \
		ln -s ../../crypto/rc2/rc2.h rc2.h; \
		ln -s ../../crypto/camellia/camellia.h camellia.h; \
		ln -s ../../crypto/idea/idea.h idea.h; \
		ln -s ../../crypto/bf/blowfish.h blowfish.h; \
	)
	$(SED) "s:-march=[-a-z0-9] ::" -e "s:-mcpu=[-a-z0-9] ::g" $(@D)/Makefile
	$(SED) "s:-O[0-9]:$(OPENSSL_TARGET_CFLAGS):" $(@D)/Makefile
endef
endif

ifeq ($(BR2_ARCH_IS_64),y)
define OPENSSL_BUILD_CMDS
        $(MAKE1) -C $(@D) all
endef
else
define OPENSSL_BUILD_CMDS
	$(MAKE1) -C $(@D) all build-shared
	$(MAKE1) -C $(@D) do_linux-shared
endef
endif

define OPENSSL_INSTALL_STAGING_CMDS
	$(MAKE1) -C $(@D) INSTALL_PREFIX=$(STAGING_DIR) install
endef

define OPENSSL_INSTALL_TARGET_CMDS
	$(MAKE1) -C $(@D) INSTALL_PREFIX=$(TARGET_DIR) install
endef

define OPENSSL_REMOVE_DEV_FILES
	rm -rf $(TARGET_DIR)/usr/lib/ssl
endef

ifneq ($(BR2_HAVE_DEVFILES),y)
OPENSSL_POST_INSTALL_TARGET_HOOKS += OPENSSL_REMOVE_DEV_FILES
endif

define OPENSSL_REMOVE_OPENSSL_BIN
	rm -f $(TARGET_DIR)/usr/bin/openssl
endef

ifneq ($(BR2_PACKAGE_OPENSSL_BIN),y)
OPENSSL_POST_INSTALL_TARGET_HOOKS += OPENSSL_REMOVE_OPENSSL_BIN
endif

define OPENSSL_INSTALL_FIXUPS
	rm -f $(TARGET_DIR)/usr/bin/c_rehash
	# libraries gets installed read only, so strip fails
	chmod +w $(TARGET_DIR)/usr/lib/engines/lib*.so || true
	for i in $(addprefix $(TARGET_DIR)/usr/lib/,libcrypto.so.* libssl.so.*); \
	do chmod +w $$i; done
endef

define OPENSSL_POST_INSTALL_CUSTOMISATION
	mkdir -p $(OPENSSL_BINARY_DIR)/openssl_tmp
	$(MAKE1) -C $(@D) INSTALL_PREFIX=$(PWD)/$(OPENSSL_BINARY_DIR)/openssl_tmp install
	tar cjvf $(OPENSSL_BINARY_DIR)/$(OPENSSL_BINARY_SOURCE) -C $(OPENSSL_BINARY_DIR)/openssl_tmp .
	rm -rf $(OPENSSL_BINARY_DIR)/openssl_tmp
endef

openssl-binary:
	tar -xjvf $(OPENSSL_BINARY_DIR)/$(OPENSSL_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(OPENSSL_BINARY_DIR)/$(OPENSSL_BINARY_SOURCE) -C $(TARGET_DIR)/
	rm -rf $(TARGET_DIR)/usr/include/
	rm -f $(TARGET_DIR)/usr/bin/c_rehash
	# libraries gets installed read only, so strip fails
	chmod +w $(TARGET_DIR)/usr/lib/engines/lib*.so || true
	for i in $(addprefix $(TARGET_DIR)/usr/lib/,libcrypto.so.* libssl.so.*); \
	do chmod +w $$i; done
ifneq ($(BR2_PACKAGE_OPENSSL_BIN),y)
	rm -f $(TARGET_DIR)/usr/bin/openssl
endif
ifneq ($(BR2_HAVE_DEVFILES),y)
	rm -rf $(TARGET_DIR)/usr/lib/ssl
endif
ifneq ($(BR2_PACKAGE_OPENSSL_ENGINES),y)
	rm -rf $(TARGET_DIR)/usr/lib/engines
endif

OPENSSL_POST_INSTALL_TARGET_HOOKS += OPENSSL_INSTALL_FIXUPS
OPENSSL_POST_INSTALL_STAGING_HOOKS += OPENSSL_POST_INSTALL_CUSTOMISATION

define OPENSSL_REMOVE_OPENSSL_ENGINES
	rm -rf $(TARGET_DIR)/usr/lib/engines
endef

ifneq ($(BR2_PACKAGE_OPENSSL_ENGINES),y)
OPENSSL_POST_INSTALL_TARGET_HOOKS += OPENSSL_REMOVE_OPENSSL_ENGINES
endif

openssl-binary-clean:
	rm -rf $(OPENSSL_INSTALL_BINARY)

define OPENSSL_UNINSTALL_CMDS
	rm -rf $(addprefix $(TARGET_DIR)/,etc/ssl usr/bin/openssl usr/include/openssl)
	rm -rf $(addprefix $(TARGET_DIR)/usr/lib/,ssl engines libcrypto* libssl* pkgconfig/libcrypto.pc)
	rm -rf $(addprefix $(STAGING_DIR)/,etc/ssl usr/bin/openssl usr/include/openssl)
	rm -rf $(addprefix $(STAGING_DIR)/usr/lib/,ssl engines libcrypto* libssl* pkgconfig/libcrypto.pc)
endef


ifeq ($(wildcard $(OPENSSL_INSTALL_BINARY)),)
openssl: $(eval $(call GENTARGETS,package,openssl))
else
openssl: openssl-binary
endif

ifeq ($(BR2_PACKAGE_OPENSSL),y)
TARGETS+=openssl
endif
