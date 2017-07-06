#############################################################
#
# craftworks
#
#############################################################

CRAFTWORKS_VERSION:=$(subst ",,$(BR2_PACKAGE_SKY_CRAFTWORKS_VERSION))
#")
CRAFTWORKS_VARIANT:=$(subst ",,$(BR2_SKY_BUILD_TYPE))
#")

CRAFTWORKS_SOURCE:=$(SKY_DL_DIR)/craftworks-$(ARCH)-$(CRAFTWORKS_VERSION)-$(CRAFTWORKS_VARIANT).tar.bz2
CRAFTWORKS_CAT:=$(BZCAT)
CRAFTWORKS_DIR:=$(BUILD_DIR)/craftworks
CRAFTWORKS_FILES:=/usr/bin/CRAFTWORKS

craftworks-source: $(DL_DIR)/$(CRAFTWORKS_SOURCE)

$(CRAFTWORKS_DIR)/.unpacked: $(DL_DIR)/$(CRAFTWORKS_SOURCE)
	$(CRAFTWORKS_CAT) $(DL_DIR)/$(CRAFTWORKS_SOURCE) | tar -C $(TARGET_DIR) $(TAR_OPTIONS) -
	-@mkdir $(CRAFTWORKS_DIR)
	touch $@

craftworks: uclibc $(CRAFTWORKS_DIR)/.unpacked

craftworks-clean:
	rm -f $(addprefix $(TARGET_DIR),$(CRAFTWORKS_FILES))

craftworks-dirclean:
	rm -rf $(CRAFTWORKS_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_SKY_CRAFTWORKS),y)
TARGETS+=craftworks
endif
