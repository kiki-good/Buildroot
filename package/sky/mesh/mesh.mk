#############################################################
#
# AirTies drivers
#
#############################################################

MESH_VARIANT:=$(subst ",,$(BR2_SKY_BUILD_TYPE))
#")
MESH_PROJECT:=$(subst ",,$(BR2_PROJECT))
#")

MESH_SOURCE:=mesh-drivers-$(MESH_PROJECT)-$(MESH_VARIANT).tar.bz2
MESH_CAT:=$(BZCAT)
MESH_DIR:=$(BUILD_DIR)/mesh

# Any file which must be in the binary package
MESH_FILE:=/etc/rc.d/rc.platform

# The three possible script files that if present should be executable
MESH_STARTUP_SCRIPTS:=/etc/rc.d/rc.platform

mesh-source: $(DL_DIR)/$(mesh_SOURCE)

$(MESH_DIR)/.unpacked: $(DL_DIR)/$(MESH_SOURCE) $(TARGET_DIR)/$(MESH_FILE)
	@echo "Unpacking $(DL_DIR)/$(MESH_SOURCE)..."
	$(MESH_CAT) $(DL_DIR)/$(MESH_SOURCE) | tar -C $(TARGET_DIR) $(TAR_OPTIONS) -
	-@mkdir -p $(MESH_DIR)
	cp $(TARGET_DIR)/lib/libaci.so $(STAGING_DIR)/lib/
	touch $@

$(MESH_STARTUP_SCRIPTS):
	$(if $(shell test -e $(TARGET_DIR)/$@ && test ! -x $(TARGET_DIR)/$@ && echo err), \
		$(error The $@ script in the MESH drivers package is not executable! It must be executable if present))

mesh-check: $(MESH_STARTUP_SCRIPTS)

$(TARGET_DIR)/$(MESH_FILE):

mesh: $(MESH_DIR)/.unpacked mesh-check

mesh-clean:
	-rm -fv $(addprefix $(TARGET_DIR)/,$(shell tar jtf $(DL_DIR)/$(MESH_SOURCE)))
	-rmdir -v --ignore-fail-on-non-empty -p $(addprefix $(TARGET_DIR)/,$(shell tar jtf $(DL_DIR)/$(MESH_SOURCE)))

mesh-dirclean:	mesh-clean
	rm -rf $(MESH_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_MESH_DRIVERS),y)
TARGETS+=mesh
endif
