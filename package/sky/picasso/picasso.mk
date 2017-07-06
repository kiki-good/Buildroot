#############################################################
#
# picasso
#
#############################################################

PICASSO_VERSION:=$(subst ",,$(BR2_PACKAGE_SKY_PICASSO_VERSION))
#")
PICASSO_VARIANT:=$(subst ",,$(BR2_SKY_BUILD_TYPE))
#")

PICASSO_SOURCE:=$(SKY_DL_DIR)/picasso-$(ARCH)-$(PICASSO_VERSION)-$(PICASSO_VARIANT).tar.bz2
PICASSO_CAT:=$(BZCAT)
PICASSO_DIR:=$(BUILD_DIR)/picasso
PICASSO_FILES:=/usr/bin/PICASSO

picasso-source: $(DL_DIR)/$(PICASSO_SOURCE)

$(PICASSO_DIR)/.unpacked: $(DL_DIR)/$(PICASSO_SOURCE)
	$(PICASSO_CAT) $(DL_DIR)/$(PICASSO_SOURCE) | tar -C $(TARGET_DIR) $(TAR_OPTIONS) -
	-@mkdir $(PICASSO_DIR)
	touch $@

picasso: uclibc $(PICASSO_DIR)/.unpacked

picasso-clean:
	rm -f $(addprefix $(TARGET_DIR),$(PICASSO_FILES))

picasso-dirclean:
	rm -rf $(PICASSO_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_SKY_PICASSO),y)
TARGETS+=picasso
endif
