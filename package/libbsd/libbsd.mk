#############################################################
#
# libbsd
#
#############################################################
LIBBSD_VERSION=0.4.2
LIBBSD_SOURCE=libbsd-$(LIBBSD_VERSION).tar.gz
LIBBSD_SITE=http://localhost/
LIBBSD_DIR=$(BUILD_DIR)/libbsd-$(LIBBSD_VERSION)
LIBBSD_CAT:=$(ZCAT)
LIBBSD_LIBTOOL_PATCH=NO
LIBBSD_INSTALL_STAGING=YES
LIBBSD_INSTALL_TARGET=YES
LIBBSD_AUTORECONF=YES

LIBBSD_CONF_OPT = --includedir=/usr/include --enable-shared 


$(eval $(call AUTOTARGETS,package,libbsd))
