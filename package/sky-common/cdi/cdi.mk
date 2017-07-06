#############################################################
#
# cdi drivers
#
#############################################################

CDI_VARIANT:=$(subst ",,$(BR2_SKY_BUILD_TYPE))
#")
CDI_PROJECT:=$(subst ",,$(BR2_PROJECT))
#")

CDI_SOURCE:=cdi-drivers-$(CDI_PROJECT)-$(CDI_VARIANT).tar.bz2
CDI_CAT:=$(BZCAT)
CDI_DIR:=$(BUILD_DIR)/cdi

# Any file which must be in the binary package
CDI_FILE:=/etc/load-cdi-drivers.sh

# The three possible script files that if present should be executable
CDI_STARTUP_SCRIPTS:=/etc/load-cdi-drivers.sh /etc/jhmknods_nds.sh /etc/bumpup.sh

cdi-source: $(DL_DIR)/$(CDI_SOURCE)

$(CDI_DIR)/.unpacked: $(DL_DIR)/$(CDI_SOURCE) $(TARGET_DIR)/$(CDI_FILE)
	@echo "Unpacking $(DL_DIR)/$(CDI_SOURCE)..."
	$(CDI_CAT) $(DL_DIR)/$(CDI_SOURCE) | tar -C $(TARGET_DIR) $(TAR_OPTIONS) -
	-@mkdir -p $(CDI_DIR)
	touch $@

$(CDI_STARTUP_SCRIPTS):
	$(if $(shell test -e $(TARGET_DIR)/$@ && test ! -x $(TARGET_DIR)/$@ && echo err), \
		$(error The $@ script in the CDI drivers package is not executable! It must be executable if present))

cdi-check: $(CDI_STARTUP_SCRIPTS)

$(TARGET_DIR)/$(CDI_FILE):

cdi: $(CDI_DIR)/.unpacked cdi-check

cdi-clean:
	-rm -fv $(addprefix $(TARGET_DIR)/,$(shell tar jtf $(DL_DIR)/$(CDI_SOURCE)))
	-rmdir -v --ignore-fail-on-non-empty -p $(addprefix $(TARGET_DIR)/,$(shell tar jtf $(DL_DIR)/$(CDI_SOURCE)))

cdi-dirclean:	cdi-clean
	rm -rf $(CDI_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_SKY_CDI_DRIVERS),y)
TARGETS+=cdi
endif
