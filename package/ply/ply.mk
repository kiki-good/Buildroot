#############################################################
#
# ply
#
#############################################################
PLY_VERSION=3.3
PLY_SOURCE=ply-$(PLY_VERSION).tar.gz
PLY_SITE=http://localhost/
PLY_DIR=$(BUILD_DIR)/ply-$(PLY_VERSION)
PLY_CAT:=$(ZCAT)
PLY_BINARY:=ply
PLY_TARGET_LIB:=$(PLY_DIR)/$(PLY_BINARY)

$(PLY_DIR)/.unpacked: $(DL_DIR)/$(PLY_SOURCE)
	$(PLY_CAT) $(DL_DIR)/$(PLY_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	touch $@

$(PLY_DIR)/.configured: $(PLY_DIR)/.unpacked
	(cd $(PLY_DIR);  \
		python setup.py build; \
	)
	touch $@

$(PLY_DIR)/$(PLY_BINARY): $(PLY_DIR)/.configured

$(TARGET_DIR)/$(PLY_TARGET_LIB): $(PLY_DIR)/$(PLY_BINARY)

ply:	$(TARGET_DIR)/$(PLY_TARGET_LIB)

ply-source: $(DL_DIR)/$(PLY_SOURCE)

ply-clean:
	-$(MAKE) -C $(PLY_DIR) clean

ply-dirclean:
	rm -rf $(PLY_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_PLY),y)
TARGETS+=ply
endif
