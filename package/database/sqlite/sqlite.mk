#############################################################
#
# sqlite
#
#############################################################

SQLITE_VERSION:=3.6.4
SQLITE_SOURCE:=sqlite-$(SQLITE_VERSION).tar.gz
SQLITE_SITE:=http://www.sqlite.org
SQLITE_DIR:=$(BUILD_DIR)/sqlite-$(SQLITE_VERSION)
SQLITE_CAT:=$(ZCAT)
SQLITE_BINARY_SOURCE:=sqlite-$(SQLITE_VERSION)-binary.tar.bz2
SQLITE_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
SQLITE_BINARY_DIR:=$(SQLITE_BOARD_PATH)/binaries
SQLITE_BINARY_TEMP_DIR:=$(SQLITE_BINARY_DIR)/sqlite_temp
SQLITE_INSTALL_BINARY:=$(SQLITE_BINARY_DIR)/$(SQLITE_BINARY_SOURCE)


$(DL_DIR)/$(SQLITE_SOURCE):
	$(WGET) -P $(DL_DIR) $(SQLITE_SITE)/$(SQLITE_SOURCE)

$(SQLITE_DIR)/.unpacked: $(DL_DIR)/$(SQLITE_SOURCE)
	$(SQLITE_CAT) $(DL_DIR)/$(SQLITE_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(SQLITE_DIR) package/database/sqlite/ sqlite-$(SQLITE_VERSION)\*.patch*
	touch $(SQLITE_DIR)/.unpacked

$(SQLITE_DIR)/.configured: $(SQLITE_DIR)/.unpacked
	(cd $(SQLITE_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		config_BUILD_CC="$(HOSTCC)" \
		config_TARGET_CFLAGS="$(TARGET_CFLAGS)" \
		config_TARGET_CC="$(TARGET_CC)" \
		config_TARGET_READLINE_LIBS="-L$(TARGET_DIR)/usr/lib -L$(TARGET_DIR)/lib -lncurses -lreadline" \
		config_TARGET_READLINE_INC="-I$(STAGING_DIR)/usr/include" \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--prefix=/usr \
		--sysconfdir=/etc \
		--localstatedir=/var \
		--enable-shared \
		--enable-static \
		--disable-tcl \
		--enable-tempstore \
		--enable-threadsafe \
		--enable-releasemode \
	)
	touch $(SQLITE_DIR)/.configured

$(SQLITE_DIR)/sqlite3: $(SQLITE_DIR)/.configured
	$(MAKE) -C $(SQLITE_DIR)

$(STAGING_DIR)/usr/bin/sqlite3: $(SQLITE_DIR)/sqlite3
	$(MAKE) DESTDIR=$(STAGING_DIR) -C $(SQLITE_DIR) install
	$(MAKE) DESTDIR=$(PWD)/$(SQLITE_BINARY_TEMP_DIR) -C $(SQLITE_DIR) install
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/lib\',g" $(STAGING_DIR)/usr/lib/libsqlite3.la
	tar cjvf $(SQLITE_BINARY_DIR)/$(SQLITE_BINARY_SOURCE) -C $(SQLITE_BINARY_TEMP_DIR) .
	rm -rf $(SQLITE_BINARY_TEMP_DIR)

$(TARGET_DIR)/usr/bin/sqlite3: $(STAGING_DIR)/usr/bin/sqlite3
	$(INSTALL) -m 0755 -D $^ $@
	$(STRIPCMD) $(STRIP_STRIP_ALL) $@
	cp -dpf $(STAGING_DIR)/usr/lib/libsqlite3*.so* $(TARGET_DIR)/usr/lib/
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libsqlite3.so

sqlite-binary: 
	tar -xjvf $(SQLITE_BINARY_DIR)/$(SQLITE_BINARY_SOURCE) -C $(STAGING_DIR)/
	$(INSTALL) -m 0755 -D $(STAGING_DIR)/usr/bin/sqlite3 $(TARGET_DIR)/usr/bin/sqlite3
	$(STRIPCMD) $(STRIP_STRIP_ALL) $(TARGET_DIR)/usr/bin/sqlite3
	cp -dpf $(STAGING_DIR)/usr/lib/libsqlite3*.so* $(TARGET_DIR)/usr/lib/
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libsqlite3.so

ifeq ($(wildcard $(SQLITE_INSTALL_BINARY)),)
sqlite: uclibc readline-target ncurses $(TARGET_DIR)/usr/bin/sqlite3
else
sqlite: sqlite-binary
endif

sqlite-source: $(DL_DIR)/$(SQLITE_SOURCE)

sqlite-clean:
	-$(MAKE) -C $(SQLITE_DIR) clean
	-rm -rf $(STAGING_DIR)/usr/lib/libsqlite*
	-rm -rf $(STAGING_DIR)/usr/bin/sqlite3
	-rm -rf $(STAGING_DIR)/usr/include/sqlite*
	-rm -rf $(STAGING_DIR)/usr/lib/pkgconfig/sqlite*
	-rm -rf $(TARGET_DIR)/usr/lib/libsqlite*
	-rm -rf $(TARGET_DIR)/usr/bin/sqlite3

sqlite-dirclean:
	rm -rf $(SQLITE_DIR)

sqlite-binary-clean:
	rm $(SQLITE_INSTALL_BINARY)
	
#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_SQLITE),y)
TARGETS+=sqlite
endif
