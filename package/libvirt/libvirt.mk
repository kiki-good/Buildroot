#############################################################
#
# libvirt
#
#############################################################
LIBVIRT_VERSION = 1.2.18.2
LIBVIRT_SOURCE = libvirt-$(LIBVIRT_VERSION).tar.gz
LIBVIRT_SITE = ftp://localhost/
LIBVIRT_LIBTOOL_PATCH = NO
LIBVIRT_INSTALL_STAGING = YES
LIBVIRT_INSTALL_TARGET = YES
LIBVIRT_BINARY_SOURCE:=libvirt-$(LIBVIRT_VERSION)-binary.tar.bz2
LIBVIRT_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
LIBVIRT_BINARY_DIR:=$(LIBVIRT_BOARD_PATH)/binaries
LIBVIRT_INSTALL_BINARY:=$(LIBVIRT_BINARY_DIR)/$(LIBVIRT_BINARY_SOURCE)
LIBVIRT_TEMP_DIR:=$(LIBVIRT_BINARY_DIR)/libvirt_tmp


ifneq ($(BR2_LARGEFILE),y)
LIBVIRT_CONF_ENV = CC="$(TARGET_CC) $(TARGET_CFLAGS) -DNO_LARGEFILE_SOURCE"
endif

ifneq ($(BR2_SKY_BUILD_TYPE),"debug")
LIBVIRT_PROD_BUILD="yes"
else
LIBVIRT_PROD_BUILD="no"
endif

LIBVIRT_CONF_ENV += IP_PATH="/sbin/ip"
LIBVIRT_CONF_ENV += IP6TABLES_PATH="/usr/sbin/ip6tables"
LIBVIRT_CONF_ENV += IPTABLES_PATH="/usr/sbin/iptables"
LIBVIRT_CONF_ENV += EBTABLES_PATH="/usr/sbin/ebtables"

LIBVIRT_CONF_OPT = \
		--with-netcf		     \
		--with-lxc 		     \
		--without-test		     \
		--with-init-script=none	     \
		--with-sysctl=no	     \
		--with-network		     \
		--with-libvirtd  	     \
		--with-capng                 \
		--with-interface	     \
		--without-macvtap	     \
		--without-virtualport	     \
		--without-apparmor	     \
		--without-attr		     \
		--without-audit		     \
		--without-avahi		     \
		--without-blkid		     \
		--without-curl		     \
		--without-dbus		     \
		--without-fuse		     \
		--without-hal		     \
		--without-numactl	     \
		--without-openwsman	     \
		--without-pciaccess	     \
		--without-sanlock	     \
		--without-sasl		     \
		--without-selinux	     \
		--without-ssh2		     \
		--without-udev		     \
		--without-yajl		     \
		--without-xen		     \
		--without-qemu		     \
		--without-uml		     \
		--without-openvz	     \
		--without-vmware	     \
		--without-phyp		     \
		--without-xenapi	     \
		--without-libxl		     \
		--without-vbox		     \
		--without-esx		     \
		--without-hyperv	     \
		--without-gnutls	     \
		--without-polkit	     \
		--without-firewalld	     \
		--without-secdriver-selinux  \
		--without-secdriver-apparmor \
		--without-dtrace	     \
		--without-numad		     \
		--without-secrets	     \
		--without-storage-lvm	     \
		--without-storage-iscsi	     \
		--without-storage-scsi	     \
		--without-storage-mpath	     \
		--without-storage-disk	     \
		--without-storage-rbd	     \
		--without-storage-sheepdog   \
		--without-libpcap            \
		--without-pm-utils           \
		--without-systemd-daemon


define LIBVIRT_POST_INSTALL_PREBUILT_BINARIES
	mkdir -p $(LIBVIRT_TEMP_DIR)
	$(MAKE) DESTDIR=$(PWD)/$(LIBVIRT_TEMP_DIR) -C $(LIBVIRT_DIR) install
	tar cjvf $(LIBVIRT_BINARY_DIR)/$(LIBVIRT_BINARY_SOURCE) -C $(LIBVIRT_TEMP_DIR) .
	rm -rf $(LIBVIRT_TEMP_DIR)
endef

LIBVIRT_POST_INSTALL_STAGING_HOOKS += LIBVIRT_POST_INSTALL_PREBUILT_BINARIES



define LIBVIRT_POST_INSTALL
	@$(call MESSAGE,"LIBVIRT_POST_INSTALL")
	if [ $(LIBVIRT_PROD_BUILD) = "yes" ]; then \
		$(INSTALL) -D -m 755 package/libvirt/S51libvirt.prod $(TARGET_DIR)/etc/init.d/S51libvirt ; \
	else \
		$(INSTALL) -D -m 755 package/libvirt/S51libvirt $(TARGET_DIR)/etc/init.d/S51libvirt ; \
	fi 
	$(SED) "s|^#listen_tls = 0|listen_tls = 0|g" $(TARGET_DIR)/etc/libvirt/libvirtd.conf
	$(SED) "s|^#unix_sock_group = \"libvirt\"|unix_sock_group = \"NDS_MW\"|g" $(TARGET_DIR)/etc/libvirt/libvirtd.conf
	$(SED) "s|^#unix_sock_ro_perms = \"0777\"|unix_sock_ro_perms = \"0770\"|g" $(TARGET_DIR)/etc/libvirt/libvirtd.conf
	$(SED) "s|^#unix_sock_rw_perms = \"0770\"|unix_sock_rw_perms = \"0770\"|g" $(TARGET_DIR)/etc/libvirt/libvirtd.conf
	sed -i "/^#/d" $(TARGET_DIR)/etc/libvirt/libvirt.conf
	sed -i "/^#/d" $(TARGET_DIR)/etc/libvirt/libvirtd.conf
	sed -i "/^#/d" $(TARGET_DIR)/etc/libvirt/virt-login-shell.conf
	sed -i "/^#/d" $(TARGET_DIR)/etc/libvirt/virtlockd.conf
	sed -i "/^#/d" $(TARGET_DIR)/etc/libvirt/lxc.conf
	sed -i "/^$$/d" $(TARGET_DIR)/etc/libvirt/libvirt.conf
	sed -i "/^$$/d" $(TARGET_DIR)/etc/libvirt/libvirtd.conf
	sed -i "/^$$/d" $(TARGET_DIR)/etc/libvirt/virt-login-shell.conf
	sed -i "/^$$/d" $(TARGET_DIR)/etc/libvirt/virtlockd.conf
	sed -i "/^$$/d" $(TARGET_DIR)/etc/libvirt/lxc.conf
	rm -rf $(TARGET_DIR)/usr/share/doc/libvirt-$(LIBVIRT_VERSION) \
	       $(TARGET_DIR)/usr/share/gtk-doc \
	       $(TARGET_DIR)/etc/logrotate.d \
	       $(TARGET_DIR)/etc/libvirt/qemu \
	       $(TARGET_DIR)/usr/share/libvirt \
	       $(TARGET_DIR)/usr/include/libvirt 
endef

define LIBVIRT_POST_INSTALL_PROD
	@$(call MESSAGE,"LIBVIRT_POST_INSTALL_PROD")
	$(SED) "s|^#log_outputs=\"3:syslog:libvirtd\"|#log_outputs=\"3:syslog:libvirtd\"\n#\nlog_outputs=\"1:file:/dev/null\"\n|g" $(TARGET_DIR)/etc/libvirt/libvirtd.conf
	rm -rf $(TARGET_DIR)/usr/bin/virsh \
	       $(TARGET_DIR)/usr/bin/virt-host-validate \
	       $(TARGET_DIR)/usr/bin/virt-login-shell \
	       $(TARGET_DIR)/usr/bin/virt-pki-validate \
	       $(TARGET_DIR)/usr/bin/virt-xml-validate
endef


LIBVIRT_DEPENDENCIES = netcf libcap-ng libcap-ng libgcrypt libxslt


ifeq ($(wildcard $(LIBVIRT_INSTALL_BINARY)),)
libvirt: $(eval $(call AUTOTARGETS,package,libvirt))
else
libvirt: libvirt-binary
endif

ifneq ($(BR2_SKY_BUILD_TYPE), "debug")
LIBVIRT_POST_INSTALL_HOOKS += LIBVIRT_POST_INSTALL_PROD
LIBVIRT_POST_INSTALL_TARGET_HOOKS += LIBVIRT_POST_INSTALL_PROD
endif

LIBVIRT_POST_INSTALL_HOOKS += LIBVIRT_POST_INSTALL
LIBVIRT_POST_INSTALL_TARGET_HOOKS += LIBVIRT_POST_INSTALL


libvirt-binary:
	tar -xjvf $(LIBVIRT_BINARY_DIR)/$(LIBVIRT_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(LIBVIRT_BINARY_DIR)/$(LIBVIRT_BINARY_SOURCE) -C $(TARGET_DIR)/
	$(foreach POST_INSTALL, $(LIBVIRT_POST_INSTALL_TARGET_HOOKS), $(call $(POST_INSTALL)))
	sed -i "/^#/d" $(TARGET_DIR)/etc/libvirt/libvirt.conf
	sed -i "/^#/d" $(TARGET_DIR)/etc/libvirt/libvirtd.conf
	sed -i "/^#/d" $(TARGET_DIR)/etc/libvirt/virt-login-shell.conf
	sed -i "/^#/d" $(TARGET_DIR)/etc/libvirt/virtlockd.conf
	sed -i "/^#/d" $(TARGET_DIR)/etc/libvirt/lxc.conf
	sed -i "/^$$/d" $(TARGET_DIR)/etc/libvirt/libvirt.conf
	sed -i "/^$$/d" $(TARGET_DIR)/etc/libvirt/libvirtd.conf
	sed -i "/^$$/d" $(TARGET_DIR)/etc/libvirt/virt-login-shell.conf
	sed -i "/^$$/d" $(TARGET_DIR)/etc/libvirt/virtlockd.conf
	sed -i "/^$$/d" $(TARGET_DIR)/etc/libvirt/lxc.conf

libvirt-binary-clean:
	rm $(LIBVIRT_INSTALL_BINARY)


ifeq ($(BR2_PACKAGE_LIBVIRT),y)
TARGETS+=libvirt
endif

