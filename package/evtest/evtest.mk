#############################################################
#
# evtest
# 	
# #############################################################
EVTEST_VERSION:=1.30
EVTEST_SOURCE:=evtest-$(EVTEST_VERSION).tar.bz2
EVTEST_DIR:=$(BUILD_DIR)/evtest-$(EVTEST_VERSION)
EVTEST_SITE:=http://localhost/
EVTEST_AUTORECONF:=NO
EVTEST_INSTALL_STAGING:=NO
EVTEST_INSTALL_TARGET:=YES
EVTEST_CONF_ENV:=ac_cv_func_malloc_0_nonnull=yes
EVTEST_CONF_OPT:=--disable-dependency-tracking --disable-web100 $(DISABLE_IPV6)

define EVTEST_POST_CONFIG
	 $(SED) "s,^XML_LIBS =.*,XML_LIBS = -lz -liconv -lxml2 ,g" $(EVTEST_DIR)/Makefile
endef

EVTEST_POST_CONFIGURE_HOOKS += EVTEST_POST_CONFIG
EVTEST_DEPENDENCIES:=uclibc libiconv libxml2
$(eval $(call AUTOTARGETS,package,evtest))
