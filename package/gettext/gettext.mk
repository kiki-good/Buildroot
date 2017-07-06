#############################################################
#
# gettext
#
#############################################################
ifeq ($(BR2_ARCH_IS_64),y)
GETTEXT_VERSION:=0.19
else
GETTEXT_VERSION:=0.16.1
endif
GETTEXT_SOURCE:=gettext-$(GETTEXT_VERSION).tar.gz
GETTEXT_SITE:=$(BR2_GNU_MIRROR)/gettext
GETTEXT_BINARY_SOURCE:=gettext-$(GETTEXT_VERSION)-binary.tar.bz2
GETTEXT_DIR:=$(BUILD_DIR)/gettext-$(GETTEXT_VERSION)
GETTEXT_CAT:=$(ZCAT)
GETTEXT_BINARY:=gettext-runtime/src/gettext
GETTEXT_TARGET_BINARY:=usr/bin/gettext
GETTEXT_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
GETTEXT_BINARY_DIR:=$(GETTEXT_BOARD_PATH)/binaries
GETTEXT_INSTALL_BINARY:=$(GETTEXT_BINARY_DIR)/$(GETTEXT_BINARY_SOURCE)

ifeq ($(BR2_PACKAGE_GETTEXT_STATIC),y)
LIBINTL_TARGET_BINARY:=usr/lib/libintl.a
else
LIBINTL_TARGET_BINARY:=usr/lib/libintl.so
endif

$(DL_DIR)/$(GETTEXT_SOURCE):
	 $(WGET) -P $(DL_DIR) $(GETTEXT_SITE)/$(GETTEXT_SOURCE)

gettext-source: $(DL_DIR)/$(GETTEXT_SOURCE)

$(GETTEXT_DIR)/.unpacked: $(DL_DIR)/$(GETTEXT_SOURCE)
	$(GETTEXT_CAT) $(DL_DIR)/$(GETTEXT_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -

ifneq ($(BR2_ARCH_IS_64),y)
	toolchain/patch-kernel.sh $(GETTEXT_DIR) package/gettext/ gettext\*.patch
	$(CONFIG_UPDATE) $(@D)
	$(CONFIG_UPDATE) $(GETTEXT_DIR)/build-aux
else
	toolchain/patch-kernel.sh $(GETTEXT_DIR) package/gettext/64bitPatch gettext\*.patch
endif
	touch $@

ifeq ($(BR2_TOOLCHAIN_EXTERNAL),y)
IGNORE_EXTERNAL_GETTEXT:=--with-included-gettext
endif

$(GETTEXT_DIR)/.configured: $(GETTEXT_DIR)/.unpacked
	(cd $(GETTEXT_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		ac_cv_func_strtod=yes \
		ac_fsusage_space=yes \
		fu_cv_sys_stat_statfs2_bsize=yes \
		ac_cv_func_closedir_void=no \
		ac_cv_func_getloadavg=no \
		ac_cv_lib_util_getloadavg=no \
		ac_cv_lib_getloadavg_getloadavg=no \
		ac_cv_func_getgroups=yes \
		ac_cv_func_getgroups_works=yes \
		ac_cv_func_chown_works=yes \
		ac_cv_have_decl_euidaccess=no \
		ac_cv_func_euidaccess=no \
		ac_cv_have_decl_strnlen=yes \
		ac_cv_func_strnlen_working=yes \
		ac_cv_func_lstat_dereferences_slashed_symlink=yes \
		ac_cv_func_lstat_empty_string_bug=no \
		ac_cv_func_stat_empty_string_bug=no \
		vb_cv_func_rename_trailing_slash_bug=no \
		ac_cv_have_decl_nanosleep=yes \
		jm_cv_func_nanosleep_works=yes \
		gl_cv_func_working_utimes=yes \
		ac_cv_func_utime_null=yes \
		ac_cv_have_decl_strerror_r=yes \
		ac_cv_func_strerror_r_char_p=no \
		jm_cv_func_svid_putenv=yes \
		ac_cv_func_getcwd_null=yes \
		ac_cv_func_getdelim=yes \
		ac_cv_func_mkstemp=yes \
		utils_cv_func_mkstemp_limitations=no \
		utils_cv_func_mkdir_trailing_slash_bug=no \
		ac_cv_func_memcmp_working=yes \
		ac_cv_have_decl_malloc=yes \
		gl_cv_func_malloc_0_nonnull=yes \
		ac_cv_func_malloc_0_nonnull=yes \
		ac_cv_func_calloc_0_nonnull=yes \
		ac_cv_func_realloc_0_nonnull=yes \
		jm_cv_func_gettimeofday_clobber=no \
		gl_cv_func_working_readdir=yes \
		jm_ac_cv_func_link_follows_symlink=no \
		utils_cv_localtime_cache=no \
		ac_cv_struct_st_mtim_nsec=no \
		gl_cv_func_tzset_clobber=no \
		gl_cv_func_getcwd_null=yes \
		gl_cv_func_getcwd_path_max=yes \
		ac_cv_func_fnmatch_gnu=yes \
		am_getline_needs_run_time_check=no \
		am_cv_func_working_getline=yes \
		gl_cv_func_mkdir_trailing_slash_bug=no \
		gl_cv_func_mkstemp_limitations=no \
		ac_cv_func_working_mktime=yes \
		jm_cv_func_working_re_compile_pattern=yes \
		ac_use_included_regex=no \
		gl_cv_c_restrict=no \
		./configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--prefix=/usr \
		--exec-prefix=/usr \
		--disable-libasprintf \
		--enable-shared \
		$(IGNORE_EXTERNAL_GETTEXT) \
		$(OPENMP) \
	)
	touch $@

define GETTEXT_POST_INSTALL
        rm -rf $(TARGET_DIR)/usr/share/info/
        touch $@
endef
GETTEXT_POST_INSTALL_HOOKS += AUGEAS_POST_INSTALL
$(GETTEXT_DIR)/$(GETTEXT_BINARY): $(GETTEXT_DIR)/.configured
	$(MAKE) -C $(GETTEXT_DIR)
	touch -c $(GETTEXT_DIR)/$(GETTEXT_BINARY)

$(STAGING_DIR)/$(GETTEXT_TARGET_BINARY): $(GETTEXT_DIR)/$(GETTEXT_BINARY)
	-mkdir $(TARGET_DIR)/usr/lib
	$(MAKE) DESTDIR=$(STAGING_DIR) -C $(GETTEXT_DIR) install
	mkdir -p $(GETTEXT_BINARY_DIR)/gettext_tmp
	$(MAKE) DESTDIR=$(PWD)/$(GETTEXT_BINARY_DIR)/gettext_tmp -C $(GETTEXT_DIR) install
	$(SED) 's,/lib/,$(STAGING_DIR)/usr/lib/,g' $(STAGING_DIR)/usr/lib/libgettextlib.la
	$(SED) 's,/lib/,$(STAGING_DIR)/usr/lib/,g' $(STAGING_DIR)/usr/lib/libgettextpo.la
	$(SED) 's,/lib/,$(STAGING_DIR)/usr/lib/,g' $(STAGING_DIR)/usr/lib/libgettextsrc.la
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/lib\',g" $(STAGING_DIR)/usr/lib/libgettextlib.la
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/lib\',g" $(STAGING_DIR)/usr/lib/libgettextpo.la
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/lib\',g" $(STAGING_DIR)/usr/lib/libgettextsrc.la
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/lib\',g" $(STAGING_DIR)/usr/lib/libintl.la
	rm -f $(addprefix $(STAGING_DIR)/usr/bin/, \
		autopoint envsubst gettext.sh gettextize msg* ?gettext)
	tar cjvf $(GETTEXT_BINARY_DIR)/$(GETTEXT_BINARY_SOURCE) -C $(GETTEXT_BINARY_DIR)/gettext_tmp .
	rm -rf $(GETTEXT_BINARY_DIR)/gettext_tmp
	touch -c $@

gettext-binary: 
	tar -xjvf $(GETTEXT_BINARY_DIR)/$(GETTEXT_BINARY_SOURCE) -C $(STAGING_DIR)/
	rm -rf $(TARGET_DIR)/usr/share/info/
	$(SED) 's,/lib/,$(STAGING_DIR)/usr/lib/,g' $(STAGING_DIR)/usr/lib/libgettextlib.la
	$(SED) 's,/lib/,$(STAGING_DIR)/usr/lib/,g' $(STAGING_DIR)/usr/lib/libgettextpo.la
	$(SED) 's,/lib/,$(STAGING_DIR)/usr/lib/,g' $(STAGING_DIR)/usr/lib/libgettextsrc.la
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/lib\',g" $(STAGING_DIR)/usr/lib/libgettextlib.la
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/lib\',g" $(STAGING_DIR)/usr/lib/libgettextpo.la
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/lib\',g" $(STAGING_DIR)/usr/lib/libgettextsrc.la
	$(SED) "s,^libdir=.*,libdir=\'$(STAGING_DIR)/usr/lib\',g" $(STAGING_DIR)/usr/lib/libintl.la
	rm -f $(addprefix $(STAGING_DIR)/usr/bin/, \
		autopoint envsubst gettext.sh gettextize msg* ?gettext)

ifeq ($(wildcard $(GETTEXT_INSTALL_BINARY)),)
gettext: uclibc pkgconfig $(STAGING_DIR)/$(GETTEXT_TARGET_BINARY)
else
gettext: uclibc pkgconfig gettext-binary
endif


gettext-unpacked: $(GETTEXT_DIR)/.unpacked

gettext-clean:
	-$(MAKE) DESTDIR=$(STAGING_DIR) CC=$(TARGET_CC) -C $(GETTEXT_DIR) uninstall
	-$(MAKE) DESTDIR=$(TARGET_DIR) CC=$(TARGET_CC) -C $(GETTEXT_DIR) uninstall
	-$(MAKE) -C $(GETTEXT_DIR) clean

gettext-dirclean:
	rm -rf $(GETTEXT_DIR)

gettext-binary-clean:
	rm -rf $(GETTEXT_INSTALL_BINARY)

#############################################################
#
# gettext on the target
#
#############################################################

gettext-target: $(GETTEXT_DIR)/$(GETTEXT_BINARY)
ifeq ($(wildcard $(GETTEXT_INSTALL_BINARY)),)
	$(MAKE) DESTDIR=$(TARGET_DIR) -C $(GETTEXT_DIR) install
else
	cp -dpf $(STAGING_DIR)/usr/lib/libgettext*.so* $(TARGET_DIR)/usr/lib/ 
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libgettext*.so*
endif
	chmod +x $(TARGET_DIR)/usr/lib/libintl.so* # identify as needing to be stripped
ifneq ($(BR2_HAVE_INFOPAGES),y)
	rm -rf $(TARGET_DIR)/usr/info
endif
ifneq ($(BR2_HAVE_MANPAGES),y)
	rm -rf $(TARGET_DIR)/usr/man
endif
	rm -rf $(addprefix $(TARGET_DIR),/usr/share/doc \
		/usr/doc /usr/share/aclocal /usr/include/libintl.h)
	rmdir --ignore-fail-on-non-empty $(TARGET_DIR)/usr/include

$(TARGET_DIR)/usr/lib/libintl.so: $(STAGING_DIR)/$(GETTEXT_TARGET_BINARY)
	mkdir -p $(TARGET_DIR)/usr/lib/
	cp -dpf $(STAGING_DIR)/usr/lib/libintl*.so* $(TARGET_DIR)/usr/lib/
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libintl*.so*
	rm -f $(addprefix $(TARGET_DIR)/usr/lib/, \
		libgettext*.so*.la libintl*.so*.la)
	touch -c $@

$(TARGET_DIR)/usr/lib/libintl.a: $(STAGING_DIR)/$(GETTEXT_TARGET_BINARY)
	mkdir -p $(TARGET_DIR)/usr/lib/
	cp -dpf $(STAGING_DIR)/usr/lib/libintl*.a $(TARGET_DIR)/usr/lib/
	touch -c $@

libintl-binary.a:
	mkdir -p $(TARGET_DIR)/usr/lib/
	cp -dpf $(STAGING_DIR)/usr/lib/libintl*.a $(TARGET_DIR)/usr/lib/
libintl-binary.so:
	mkdir -p $(TARGET_DIR)/usr/lib/
	cp -dpf $(STAGING_DIR)/usr/lib/libintl*.so* $(TARGET_DIR)/usr/lib/
	$(STRIPCMD) $(STRIP_STRIP_UNNEEDED) $(TARGET_DIR)/usr/lib/libintl*.so*
	rm -f $(addprefix $(TARGET_DIR)/usr/lib/, \
		libgettext*.so*.la libintl*.so*.la)


ifeq ($(BR2_PACKAGE_GETTEXT_STATIC),y)
libintl-binary:libintl-binary.a
else
libintl-binary:libintl-binary.so
endif

ifeq ($(wildcard $(GETTEXT_INSTALL_BINARY)),)
libintl: $(TARGET_DIR)/$(LIBINTL_TARGET_BINARY)
else
libintl: gettext libintl-binary
endif


#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_LIBINTL),y)
TARGETS+=libintl
endif
ifeq ($(BR2_PACKAGE_GETTEXT),y)
TARGETS+=gettext
endif
