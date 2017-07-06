#############################################################
# diagnostics
#############################################################
DIAGNOSTICS_VERSION=1.3
DIAGNOSTICS_SOURCE=$(SKY_DL_DIR)/pace-$(DIAGNOSTICS_VERSION).tar.gz
DIAGNOSTICS_SITE=http://localhost/
DIAGNOSTICS_DIR=$(BUILD_DIR)/diagnostics-$(DIAGNOSTICS_VERSION)
DIAGNOSTICS_CAT:=$(ZCAT)
DIAGNOSTICS_BINARY_SOURCE:=diagnostics-$(DIAGNOSTICS_VERSION)-binary.tar.bz2
DIAGNOSTICS_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
DIAGNOSTICS_BINARY_DIR:=$(PWD)/$(DIAGNOSTICS_BOARD_PATH)/binaries
DIAGNOSTICS_TEMP_DIR:=$(DIAGNOSTICS_BINARY_DIR)/diagnostics_tmp
DIAGNOSTICS_INSTALL_BINARY:=$(DIAGNOSTICS_BINARY_DIR)/$(DIAGNOSTICS_BINARY_SOURCE)

DIAGNOSTICS_AUTORECONF = YES
DIAGNOSTICS_INSTALL_STAGING = YES
DIAGNOSTICS_LIBTOOL_PATCH:=NO

DIAGNOSTICS_DEPENDENCIES:= libxml2 libevent libcom_err openssl arpcgen ply iksemel 
DIAGNOSTICS_LIBS=lib2sp.so* libarpc.so* libboard.so* libcm*so* libcrc.so* libcwm*so* libfsutil.so* libhttp*so* libkeycode.so* liblm.so* libmap.so* libmif*so* libnetutil.so* libpki.so* librgw_compat.so* libsoap.so* libstring.so* libtimeutil.so* libxdrutil.so*
DIAGNOSTICS_APPS:=cmc cmd mifc mifd cwmc cwmd iptest cmfilechk fixmount

ifeq ($(BR2_PACKAGE_DIAGNOSTICS_ENABLE_UPLOADD),y)
DIAGNOSTICS_ENABLE_UPLOADD="yes"
DIAGNOSTICS_APPS += uploadd
else
DIAGNOSTICS_ENABLE_UPLOADD="no"
endif

ifeq ($(BR2_PACKAGE_DIAGNOSTICS_ENABLE_XMPPD),y)
DIAGNOSTICS_ENABLE_XMPPD="yes"
DIAGNOSTICS_APPS += xmppd
else
DIAGNOSTICS_ENABLE_XMPPD="no"
endif

DIAGNOSTICS_CONF_OPT:= --disable-voiced
DIAGNOSTICS_CONF_ENV:= LDFLAGS="$(TARGET_LDFLAGS) -L$(TARGET_DIR)/lib" CFLAGS="-I$(STAGING_DIR)/usr/include/libxml2 -I$(TARGET_DIR)/inc"

DIAGNOSTICS_INSTALL_STAGING_OPT = $(DIAGNOSTICS_MAKE_OPT) DESTDIR=$(STAGING_DIR) install

diagnostics-binary:
	tar -xjvf $(DIAGNOSTICS_BINARY_DIR)/$(DIAGNOSTICS_BINARY_SOURCE) -C $(STAGING_DIR)/
	$(call MESSAGE,"==========================")
	$(call MESSAGE,"Installing TR069 to target")
	$(call MESSAGE,"==========================")
	mkdir -p $(TARGET_DIR)/tr069/bin
	mkdir -p $(TARGET_DIR)/tr069/etc
	mkdir -p $(TARGET_DIR)/tr069/cm
	mkdir -p $(TARGET_DIR)/lib/cm
	for lib in $(DIAGNOSTICS_LIBS); do \
		cp -dpf  $(STAGING_DIR)/usr/lib/$$lib $(TARGET_DIR)/usr/lib; \
	done
	for app in $(DIAGNOSTICS_APPS); do \
		$(INSTALL) -D -m 755 ${STAGING_DIR}/usr/bin/$$app ${TARGET_DIR}/tr069/bin/$$app; \
	done
	$(call MESSAGE,"Install diagnostics tr069.sh startup script...")
	$(INSTALL) -D -m 550 ${STAGING_DIR}/etc/tr069.sh ${TARGET_DIR}/tr069/etc/tr069.sh
	$(call MESSAGE,"Install diagnostics upstart config files...")
	$(INSTALL) -D -m 440 package/sky/diagnostics/*.conf  ${TARGET_DIR}/etc/init/
	$(call MESSAGE,"Install diagnostics bumper config file bumper_tr69.cfg...")
	$(INSTALL) -D -m 440 ${STAGING_DIR}/tr069/etc/bumper_tr69.cfg ${TARGET_DIR}/tr069/etc/bumper_tr69.cfg || true


ifeq ($(wildcard $(DIAGNOSTICS_INSTALL_BINARY)),)
diagnostics: $(eval $(call AUTOTARGETS,package,diagnostics))
else
diagnostics: libxml2 libevent libcom_err openssl arpcgen ply iksemel diagnostics-binary
endif

# ply python lib is for dmsutils (gendm)
# it is placed into dl directory

# Python PATH only for Pace
P_PATH=${DIAGNOSTICS_DIR}/python

define DIAGNOSTICS_POST_EXTRACT
	@$(call MESSAGE,"DIAGNOSTICS_POST_EXTRACT")
	sed -i "s%arpcgen%${ARPCGEN_DIR}/arpcgen%g" ${DIAGNOSTICS_DIR}/proj_defs.mk
	sed -i "s%gendm%${P_PATH}/gendm%g" ${DIAGNOSTICS_DIR}/proj_defs.mk
	(cd ${DIAGNOSTICS_DIR}/apps/datamodel; \
	python setup.py build; \
	sed -e "s,@EXENAME@,/usr/bin/python," -e "s,TOOLDIR=None,TOOLDIR=\"/usr\"," < gendm.py > gendm; \
	mkdir -p ${P_PATH}; \
	python setup.py install --prefix=${P_PATH}; \
	install -m 0755 gendm ${P_PATH}/gendm; \
	)
	(cd ${P_PATH}; \
		echo `find . -name dmutils `>  .dmutils_path; \
		ln -s `cat .dmutils_path` dmutils; \
	)
	{ cd ${P_PATH}; \
		echo `find . -name "dmutils" | grep site` > .sky_path;\
		sed -i 's%^.%%g' .sky_path;\
	}
	cp -af  ${PLY_TARGET_LIB} ${P_PATH}/`cat ${P_PATH}}/.sky_path`/
	touch $@
	toolchain/patch-kernel.sh $(DIAGNOSTICS_DIR) $(BR2_BOARD_PATH)/kernel-patches diagnostics-$(DIAGNOSTICS_VERSION)-\*.patch
	toolchain/patch-kernel.sh $(DIAGNOSTICS_DIR) package/sky/diagnostics diagnostics-\*.patch
	if [ $(DIAGNOSTICS_ENABLE_UPLOADD) = "no" ]; then \
		toolchain/patch-kernel.sh $(DIAGNOSTICS_DIR) package/sky/diagnostics uploadd-tr69-$(DIAGNOSTICS_VERSION)-\*.patch ; \
	fi 
	if [ $(DIAGNOSTICS_ENABLE_XMPPD) = "no" ]; then \
		toolchain/patch-kernel.sh $(DIAGNOSTICS_DIR) package/sky/diagnostics xmppd-tr69-$(DIAGNOSTICS_VERSION)-\*.patch ; \
	fi 
endef

DIAGNOSTICS_POST_EXTRACT_HOOKS += DIAGNOSTICS_POST_EXTRACT 


define DIAGNOSTICS_POST_INSTALL_PREBUILT_BINARIES
	mkdir -p $(DIAGNOSTICS_TEMP_DIR)
	$(MAKE) DESTDIR=$(DIAGNOSTICS_TEMP_DIR) -C $(DIAGNOSTICS_DIR) install
	(cd ${DIAGNOSTICS_DIR}; \
		 cp -f --parents include/*/*.h ${DIAGNOSTICS_TEMP_DIR}/usr/;\
	)
	$(call MESSAGE,"Install diagnostics tr069.sh startup script...")
	$(INSTALL) -D -m 550 ${DIAGNOSTICS_DIR}/apps/cmd/tr069.sh ${DIAGNOSTICS_TEMP_DIR}/etc/tr069.sh
	$(call MESSAGE,"Install diagnostics upstart config files...")
	$(INSTALL) -D -m 440 package/sky/diagnostics/*.conf  ${TARGET_DIR}/etc/init/
	$(call MESSAGE,"Install diagnostics bumper config file bumper_tr69.cfg...")
	$(INSTALL) -D -m 440 ${DIAGNOSTICS_DIR}/etc/bumper_tr69.cfg ${DIAGNOSTICS_TEMP_DIR}/tr069/etc/bumper_tr69.cfg || true
	tar cjvf $(DIAGNOSTICS_BINARY_DIR)/$(DIAGNOSTICS_BINARY_SOURCE) -C $(DIAGNOSTICS_TEMP_DIR) .; \
	rm -rf $(DIAGNOSTICS_TEMP_DIR)
endef

DIAGNOSTICS_POST_INSTALL_STAGING_HOOKS += DIAGNOSTICS_POST_INSTALL_PREBUILT_BINARIES


$(DIAGNOSTICS_TARGET_INSTALL_TARGET): $(DIAGNOSTICS_TARGET_INSTALL_STAGING_DIR)
	$(call MESSAGE,"==========================")
	$(call MESSAGE,"Installing TR069 to target")
	$(call MESSAGE,"==========================")
	$(MAKE) DESTDIR=$(STAGING_DIR) -C $(DIAGNOSTICS_DIR) install
	mkdir -p $(TARGET_DIR)/tr069/bin
	mkdir -p $(TARGET_DIR)/tr069/etc
	mkdir -p $(TARGET_DIR)/tr069/cm
	mkdir -p $(TARGET_DIR)/lib/cm
	for lib in $(DIAGNOSTICS_LIBS); do \
		cp -dpf  $(STAGING_DIR)/usr/lib/$$lib $(TARGET_DIR)/usr/lib; \
	done
	for app in $(DIAGNOSTICS_APPS); do \
		$(INSTALL) -D -m 750 ${STAGING_DIR}/usr/bin/$$app ${TARGET_DIR}/tr069/bin/$$app; \
	done
	$(call MESSAGE,"Install diagnostics tr069.sh startup script...")
	$(INSTALL) -D -m 550 ${DIAGNOSTICS_DIR}/apps/cmd/tr069.sh ${TARGET_DIR}/tr069/etc/tr069.sh
ifneq ($(BR2_SKY_BUILD_TYPE), "debug")
	sed -i "/LD_LIBRARY_PATH/d" ${TARGET_DIR}/tr069/etc/tr069.sh
endif 
	$(call MESSAGE,"Install diagnostics upstart config files...")
	$(INSTALL) -D -m 440 package/sky/diagnostics/*.conf  ${TARGET_DIR}/etc/init/
	$(call MESSAGE,"Install diagnostics bumper config file bumper_tr69.cfg...")
	$(INSTALL) -D -m 440 ${DIAGNOSTICS_DIR}/etc/bumper_tr69.cfg ${TARGET_DIR}/tr069/etc/bumper_tr69.cfg || true
	# Create a file that will be used as standard input for CM daemon
	touch ${TARGET_DIR}/usr/input.txt
	touch $@

DIAGNOSTICS_CLEAN_FILES=$(DIAG_DIR)/libs/libcwmrpc/cwmd.h

diagnostics-clean:
	 echo "Cleaning diag..."
	-$(MAKE) -C $(DIAGNOSTICS_DIR) clean
	-test -z $(DIAGNOSTICS_CLEAN_FILES) || rm -f $(DIAGNOSTICS_CLEAN_FILES)
	for lib in $(DIAG_LIBS); do \
		test -z "$(STAGING_DIR)/usr/lib/$$lib" || rm -f $(STAGING_DIR)/usr/lib/$$lib; \
		test -z "$(TARGET_DIR)/usr/lib/$$lib" || rm -f $(TARGET_DIR)/usr/lib/$$lib; \
	done
	rm -f $(TARGET_DIR)/tr069/etc/tr069.sh
	rm -f $(TARGET_DIR)/usr/input.txt

diagnostics-binary-clean:
	rm $(DIAGNOSTICS_INSTALL_BINARY)
ifeq ($(BR2_PACKAGE_DIAGNOSTICS),y)
TARGETS+=diagnostics
endif

