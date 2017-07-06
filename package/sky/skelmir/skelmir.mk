#############################################################
#
# skelmir
#
#############################################################

SKELMIR_VERSION:=$(subst ",,$(BR2_PACKAGE_SKY_SKELMIR_VERSION))
#")
SKELMIR_VARIANT:=$(subst ",,$(BR2_SKY_BUILD_TYPE))
#")

SKELMIR_SOURCE:=$(SKY_DL_DIR)/skelmir-$(ARCH)-$(SKELMIR_VERSION)-$(SKELMIR_VARIANT).tar.bz2
SKELMIR_CAT:=$(BZCAT)
SKELMIR_DIR:=$(BUILD_DIR)/skelmir
SKELMIR_FILES:=/usr/bin/SKELMIR

skelmir-source: $(DL_DIR)/$(SKELMIR_SOURCE)

$(SKELMIR_DIR)/.unpacked: $(DL_DIR)/$(SKELMIR_SOURCE)
	$(SKELMIR_CAT) $(DL_DIR)/$(SKELMIR_SOURCE) | tar -C $(TARGET_DIR) $(TAR_OPTIONS) -
	-@mkdir $(SKELMIR_DIR)
	touch $@

skelmir: uclibc $(SKELMIR_DIR)/.unpacked

skelmir-clean:
	rm -f $(addprefix $(TARGET_DIR),$(SKELMIR_FILES))

skelmir-dirclean:
	rm -rf $(SKELMIR_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_SKY_SKELMIR),y)
TARGETS+=skelmir
endif
