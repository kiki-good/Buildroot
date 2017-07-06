#############################################################
#
# SKY BINARY Package/
#
#############################################################
BINARY_ARCH= $(strip $(subst ",,$(BR2_ARCH)))
BINARY_PROJECT= $(strip $(subst ",,$(BR2_PROJECT)))
BINARY_VARIANT= $(strip $(subst ",,$(BR2_SKY_BUILD_TYPE)))
SKYBINARY_PACKAGE:=binary/sky_binary_$(BINARY_ARCH)_$(BINARY_PROJECT)_$(BINARY_VARIANT)_root_package.tar.bz2
SKYBINARY_CAT:=$(BZCAT)
SKYBINARY_DIR:=$(BUILD_DIR)/skybinary

# Any file which must be in the binary package

# The three possible script files that if present should be executable

skybinary-source: $(DL_DIR)/$(SKYBINARY_PACKAGE)

$(SKYBINARY_DIR)/.unpacked: $(DL_DIR)/$(SKYBINARY_PACKAGE) 
	@echo "Unpacking $(DL_DIR)/$(SKYBINARY_PACKAGE)..."
	$(SKYBINARY_CAT) $(DL_DIR)/$(SKYBINARY_PACKAGE) | tar -C $(TARGET_DIR) $(TAR_OPTIONS) -
	-@mkdir -p $(SKYBINARY_DIR)
	touch $@

skybinary-check: 


skybinary: $(SKYBINARY_DIR)/.unpacked skybinary-check

skybinary-clean:
	-rm -fv $(addprefix $(TARGET_DIR)/,$(shell tar jtf $(DL_DIR)/$(SKYBINARY_PACKAGE)))
	-rmdir -v --ignore-fail-on-non-empty -p $(addprefix $(TARGET_DIR)/,$(shell tar jtf $(DL_DIR)/$(SKYBINARY_PACKAGE)))

skybinary-dirclean:skybinary-clean
	rm -rf $(SKYBINARY_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_TARGET_SKY_BINARY_PACKAGE),y)
TARGETS+=skybinary
endif
