#############################################################
#
# iksemel
#
#############################################################
IKSEMEL_VERSION=1.4
IKSEMEL_SOURCE=iksemel-$(IKSEMEL_VERSION).tar.gz
IKSEMEL_SITE=http://localhost/
IKSEMEL_DIR=$(BUILD_DIR)/iksemel-$(IKSEMEL_VERSION)
IKSEMEL_CAT:=$(ZCAT)
IKSEMEL_LIBTOOL_PATCH=NO
IKSEMEL_INSTALL_STAGING=YES
IKSEMEL_INSTALL_TARGET=YES
IKSEMEL_AUTORECONF=NO

IKSEMEL_CONF_OPT = --includedir=/usr/include --enable-shared 


$(eval $(call AUTOTARGETS,package,iksemel))
