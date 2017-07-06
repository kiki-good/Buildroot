#############################################################
#
# Support Software
#
#############################################################

SUPP_VARIANT:=$(subst ",,$(BR2_SKY_BUILD_TYPE))
#")
SUPP_PROJECT:=$(subst ",,$(BR2_PROJECT))
#")

SUPP_SOURCE:=support-$(SUPP_PROJECT)-$(SUPP_VARIANT).tar.bz2
SUPP_CAT:=$(BZCAT)
SUPP_DIR:=$(BUILD_DIR)/support

# Any file which must be in the binary package
SUPP_FILE:=/etc/start-support.sh

# The possible script files that if present should be executable
SUPP_STARTUP_SCRIPTS:=/etc/start-support.sh

support-source: $(DL_DIR)/$(SUPP_SOURCE)

$(SUPP_DIR)/.unpacked: $(DL_DIR)/$(SUPP_SOURCE) $(TARGET_DIR)/$(SUPP_FILE)
	@echo "Unpacking $(DL_DIR)/$(SUPP_SOURCE)..."
	$(SUPP_CAT) $(DL_DIR)/$(SUPP_SOURCE) | tar -C $(TARGET_DIR) $(TAR_OPTIONS) -
	-@mkdir -p $(SUPP_DIR)
	touch $@

$(SUPP_STARTUP_SCRIPTS):
	$(if $(shell test -e $(TARGET_DIR)/$@ && test ! -x $(TARGET_DIR)/$@ && echo err), \
		$(error The $@ script in the SUPPORT drivers package is not executable! It must be executable if present))

support-check: $(SUPP_STARTUP_SCRIPTS)

$(TARGET_DIR)/$(SUPP_FILE):

support: $(SUPP_DIR)/.unpacked support-check

support-clean:
	-rm -fv $(addprefix $(TARGET_DIR)/,$(shell tar jtf $(DL_DIR)/$(SUPP_SOURCE)))
	-rmdir -v --ignore-fail-on-non-empty -p $(addprefix $(TARGET_DIR)/,$(shell tar jtf $(DL_DIR)/$(SUPP_SOURCE)))

support-dirclean:	support-clean
	rm -rf $(SUPP_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_SKY_SUPPORT),y)
TARGETS+=support
endif
