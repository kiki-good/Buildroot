#############################################################
#
# iptables
#
#############################################################
IPTABLES_VERSION = 1.4.21
IPTABLES_SOURCE = iptables-$(IPTABLES_VERSION).tar.bz2
IPTABLES_SITE = http://localhost

IPTABLES_CONF_OPT = --libexecdir=/usr/lib --enable-static=yes
IPTABLES_INSTALL_TARGET = YES

IPTABLES_AUTORECONF = NO
IPTABLES_DEPENDENCIES =
IPTABLES_CONFIGURE_OPT = --with-kernel=$(LINUX_HEADERS_DIR)
IPTABLES_MAKE_OPT = GLIB_GENMARSHAL=/usr/bin/glib-genmarshal GLIB_MKENUMS=/usr/bin

# Override the '--disable-ipv6' configuration option if option was
# specified in config
ifeq ($(BR2_PACKAGE_IPTABLES_IPV6),y)
DISABLE_IPV6 := 
endif

$(eval $(call AUTOTARGETS,package,iptables))

define IPTABLES_POST_INSTALL
# Remove the features we don't want. This is a bit of a hack
# but quickest/easiest way to do it for now.

ifneq ($(BR2_PACKAGE_IPTABLES_IPV6),y)
	rm -rf ${TARGET_DIR}/usr/sbin/ip6tables*
	rm -rf ${TARGET_DIR}/usr/lib/xtables/libip6t*
endif
ifneq ($(BR2_PACKAGE_IPTABLES_XML),y)
	rm -rf ${TARGET_DIR}/usr/bin/iptables-xml
endif

endef

IPTABLES_POST_INSTALL_HOOKS += IPTABLES_POST_INSTALL


