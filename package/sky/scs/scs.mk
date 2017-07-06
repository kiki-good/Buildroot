#############################################################
#
# Service Centre Software (SCS)
#
#############################################################

SCS_VARIANT:=$(subst ",,$(BR2_SKY_BUILD_TYPE))
#")
SCS_PROJECT:=$(subst ",,$(BR2_PROJECT))
#")

SCS_SOURCE:=service-centre-$(SCS_PROJECT)-$(SCS_VARIANT).tar.bz2
SCS_CAT:=$(BZCAT)
SCS_DIR:=$(BUILD_DIR)/scs

# Any file which must be in the binary package
SCS_FILE:=/etc/start-scs.sh

# The possible script files that if present should be executable
SCS_STARTUP_SCRIPTS:=/etc/start-scs.sh

scs-source: $(DL_DIR)/$(SCS_SOURCE)

$(SCS_DIR)/.unpacked: $(DL_DIR)/$(SCS_SOURCE) $(TARGET_DIR)/$(SCS_FILE)
	@echo "Unpacking $(DL_DIR)/$(SCS_SOURCE)..."
	$(SCS_CAT) $(DL_DIR)/$(SCS_SOURCE) | tar -C $(TARGET_DIR) $(TAR_OPTIONS) -
	-@mkdir -p $(SCS_DIR)
	touch $@

$(SCS_STARTUP_SCRIPTS):
	$(if $(shell test -e $(TARGET_DIR)/$@ && test ! -x $(TARGET_DIR)/$@ && echo err), \
		$(error The $@ script in the SCS drivers package is not executable! It must be executable if present))

scs-check: $(SCS_STARTUP_SCRIPTS)

$(TARGET_DIR)/$(SCS_FILE):

scs: $(SCS_DIR)/.unpacked scs-check

scs-clean:
	-rm -fv $(addprefix $(TARGET_DIR)/,$(shell tar jtf $(DL_DIR)/$(SCS_SOURCE)))
	-rmdir -v --ignore-fail-on-non-empty -p $(addprefix $(TARGET_DIR)/,$(shell tar jtf $(DL_DIR)/$(SCS_SOURCE)))

scs-dirclean:	scs-clean
	rm -rf $(SCS_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_SKY_SCS),y)
TARGETS+=scs
endif
