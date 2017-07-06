#############################################################
#
# libglib2
#
#############################################################
ifeq ($(BR2_ARCH_IS_64),y)
LIBGLIB2_VERSION = 2.49.1
#LIBGLIB2_VERSION = 2.32.0
else
LIBGLIB2_VERSION = 2.32.0
endif

LIBGLIB2_SOURCE = glib-$(LIBGLIB2_VERSION).tar.bz2
LIBGLIB2_BINARY_SOURCE:=libglib2-$(LIBGLIB2_VERSION)-binary.tar.bz2
LIBGLIB2_SITE = http://ftp.gtk.org/pub/glib/$(LIBGLIB2_VERSION)

LIBGLIB2_AUTORECONF = NO
LIBGLIB2_INSTALL_STAGING = YES
LIBGLIB2_INSTALL_TARGET = YES
LIBGLIB2_INSTALL_STAGING_OPT = DESTDIR=$(STAGING_DIR) LDFLAGS=-L$(STAGING_DIR)/usr/lib install
LIBGLIB2_DIR:=$(BUILD_DIR)/libglib2-$(LIBGLIB2_VERSION)
LIBGLIB2_BOARD_PATH:=$(strip  $(subst ",, $(BR2_BOARD_PATH)"))
LIBGLIB2_BINARY_DIR:=$(LIBGLIB2_BOARD_PATH)/binaries
LIBGLIB2_INSTALL_BINARY:=$(LIBGLIB2_BINARY_DIR)/$(LIBGLIB2_BINARY_SOURCE)
LIBGLIB2_DEPENDENCIES+=pkgconfig
ifeq ($(BR2_ARCH_IS_64),y)
#TO FIX
LIBGLIB2_LIBTOOL_PATCH = NO
endif



LIBGLIB2_CONF_ENV =	\
		ac_cv_func_posix_getpwuid_r=yes glib_cv_stack_grows=no \
		glib_cv_uscore=no ac_cv_func_strtod=yes \
		ac_fsusage_space=yes fu_cv_sys_stat_statfs2_bsize=yes \
		ac_cv_func_closedir_void=no ac_cv_func_getloadavg=no \
		ac_cv_lib_util_getloadavg=no ac_cv_lib_getloadavg_getloadavg=no \
		ac_cv_func_getgroups=yes ac_cv_func_getgroups_works=yes \
		ac_cv_func_chown_works=yes ac_cv_have_decl_euidaccess=no \
		ac_cv_func_euidaccess=no ac_cv_have_decl_strnlen=yes \
		ac_cv_func_strnlen_working=yes ac_cv_func_lstat_dereferences_slashed_symlink=yes \
		ac_cv_func_lstat_empty_string_bug=no ac_cv_func_stat_empty_string_bug=no \
		vb_cv_func_rename_trailing_slash_bug=no ac_cv_have_decl_nanosleep=yes \
		jm_cv_func_nanosleep_works=yes gl_cv_func_working_utimes=yes \
		ac_cv_func_utime_null=yes ac_cv_have_decl_strerror_r=yes \
		ac_cv_func_strerror_r_char_p=no jm_cv_func_svid_putenv=yes \
		ac_cv_func_getcwd_null=yes ac_cv_func_getdelim=yes \
		ac_cv_func_mkstemp=yes utils_cv_func_mkstemp_limitations=no \
		utils_cv_func_mkdir_trailing_slash_bug=no \
		ac_cv_have_decl_malloc=yes gl_cv_func_malloc_0_nonnull=yes \
		ac_cv_func_malloc_0_nonnull=yes ac_cv_func_calloc_0_nonnull=yes \
		ac_cv_func_realloc_0_nonnull=yes jm_cv_func_gettimeofday_clobber=no \
		gl_cv_func_working_readdir=yes jm_ac_cv_func_link_follows_symlink=no \
		utils_cv_localtime_cache=no ac_cv_struct_st_mtim_nsec=no \
		gl_cv_func_tzset_clobber=no gl_cv_func_getcwd_null=yes \
		gl_cv_func_getcwd_path_max=yes ac_cv_func_fnmatch_gnu=yes \
		am_getline_needs_run_time_check=no am_cv_func_working_getline=yes \
		gl_cv_func_mkdir_trailing_slash_bug=no gl_cv_func_mkstemp_limitations=no \
		ac_cv_func_working_mktime=yes jm_cv_func_working_re_compile_pattern=yes \
		ac_use_included_regex=no gl_cv_c_restrict=no \
		ac_cv_func_posix_getgrgid_r=no \
		gt_cv_c_wchar_t=$(if $(BR2_USE_WCHAR),yes,no)

ifeq ($(BR2_ARCH_IS_64),y)
LIBGLIB2_CONF_OPT = \
                    --target=$(GNU_TARGET_NAME) \
                    --host=$(GNU_TARGET_NAME) \
                    --build=$(GNU_HOST_NAME)\
                    --enable-shared \
                    --enable-static \
                    --disable-gtk-doc-html \
                    --with-libiconv=gnu \
                    --with-pcre=internal \
                    PKG_CONFIG_PATH= $(STAGING_DIR)/usr/lib/pkgconfig/ \
                    LIBFFI_CFLAGS=-I$(STAGING_DIR)/usr/lib/libffi-3.2.1/include/
                    #LIBFFI_LIBS=$(STAGING_DIR)/usr/lib64/libffi.la
else
LIBGLIB2_CONF_OPT = \
		    --target=$(GNU_TARGET_NAME) \
		    --host=$(GNU_TARGET_NAME) \
		    --build=$(GNU_HOST_NAME)\
		    --enable-shared \
		    --enable-static \
		    --disable-gtk-doc-html \
		    --with-libiconv=gnu \
		    PKG_CONFIG_PATH= $(STAGING_DIR)/usr/lib/pkgconfig/ \
		    LIBFFI_CFLAGS=-I$(STAGING_DIR)/usr/lib/libffi-3.0.13/include/
endif

ifeq ($(BR2_ARCH_IS_64),y)
define LIBGLIB2_POST_APPLY_64BITPATCH
toolchain/patch-kernel.sh $(LIBGLIB2_DIR) package/libglib2/64bitPatch libglib2-$(LIBGLIB2_VERSION)\*.patch*
endef

LIBGLIB2_POST_PATCH_HOOKS += LIBGLIB2_POST_APPLY_64BITPATCH
else
define LIBGLIB2_POST_APPLY_32BITPATCH
toolchain/patch-kernel.sh $(LIBGLIB2_DIR) package/libglib2/32bitPatch libglib2-$(LIBGLIB2_VERSION)\*.patch*
endef
LIBGLIB2_POST_PATCH_HOOKS += LIBGLIB2_POST_APPLY_32BITPATCH
endif


define LIBGLIB2_TARGET_CLEAN_UP
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
        $(STAGING_DIR)/usr/lib/libgthread-2.0.la $(STAGING_DIR)/usr/lib/libglib-2.0.la \
        $(STAGING_DIR)/usr/lib/libiconv.la -lpthread -L$(STAGING_DIR)/usr/lib $(STAGING_DIR)/usr/lib/libffi.la \
        $(STAGING_DIR)/usr/lib/libintl.la -lc',g" $(STAGING_DIR)/usr/lib/libgobject-2.0.la
        $(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
        $(STAGING_DIR)/usr/lib/libglib-2.0.la $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
        $(STAGING_DIR)/usr/lib/libintl.la -lc',g" $(STAGING_DIR)/usr/lib/libgthread-2.0.la
        $(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
        $(STAGING_DIR)/usr/lib/libgobject-2.0.la $(STAGING_DIR)/usr/lib//libgthread-2.0.la \
        $(STAGING_DIR)/usr/lib/libffi.la $(STAGING_DIR)/usr/lib/libgmodule-2.0.la -ldl $(STAGING_DIR)/usr/lib//libglib-2.0.la \
        $(STAGING_DIR)/usr/lib/libiconv.la -lpthread -lz $(STAGING_DIR)/usr/lib/libintl.la -lc',g" $(STAGING_DIR)/usr/lib/libgio-2.0.la
        $(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
        $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
        $(STAGING_DIR)/usr/lib/libintl.la -lc' ,g" $(STAGING_DIR)/usr/lib/libglib-2.0.la
        $(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
        -ldl $(STAGING_DIR)/usr/lib/libglib-2.0.la $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc',g" $(STAGING_DIR)/usr/lib/libgmodule-2.0.la
	#LHR: remove gtester,gtester-report,glib-gettextize,glib-compile-resources,glib-compile-schemas,glib-genmarshal,glib-mkenums,gsettings,gobject-query,gresource,gdbus-codegen
	rm -rf $(TARGET_DIR)/usr/bin/gtester
	rm -rf $(TARGET_DIR)/usr/bin/gtester-report
	rm -rf $(TARGET_DIR)/usr/bin/glib-gettextize
	rm -rf $(TARGET_DIR)/usr/bin/glib-compile-resources
        rm -rf $(TARGET_DIR)/usr/bin/glib-compile-schemas
        rm -rf $(TARGET_DIR)/usr/bin/gio-querymodules
        rm -rf $(TARGET_DIR)/usr/bin/glib-genmarshal
        rm -rf $(TARGET_DIR)/usr/bin/glib-mkenums
        rm -rf $(TARGET_DIR)/usr/bin/gsettings
        rm -rf $(TARGET_DIR)/usr/bin/gresource
        rm -rf $(TARGET_DIR)/usr/bin/gobject-query
        rm -rf $(TARGET_DIR)/usr/include/
        rm -rf $(TARGET_DIR)/usr/lib/pkgconfig/
	rm -rf $(TARGET_DIR)/usr/lib/gdbus-2.0/codegen/
	rm -rf $(TARGET_DIR)/usr/lib/glib-2.0/include/
        rm -rf $(TARGET_DIR)/usr/share/glib-2.0/
	rm -rf $(TARGET_DIR)/usr/bin/gdbus-codegen
	if [ $(BR2_SKY_BUILD_TYPE) != "debug" ]; then \
		rm -rf $(TARGET_DIR)/etc/bash_completion.d; \
		rm -rf $(TARGET_DIR)/usr/share/locale; \
		rm -rf $(TARGET_DIR)/usr/bin/gdbus; \
		rm -rf $(TARGET_DIR)/usr/share/gdb; \
		rm -rf $(TARGET_DIR)/usr/share/aclocal; \
	fi
endef

define LIBGLIB2_POST_INSTALL_CUSTOMISATION
	mkdir -p $(LIBGLIB2_BINARY_DIR)/libglib2_tmp
	$(MAKE) DESTDIR=$(PWD)/$(LIBGLIB2_BINARY_DIR)/libglib2_tmp -C $(LIBGLIB2_DIR) install
	#Adding the Staging directory path to the package config file and the gdbus-codegen python script
	$(SED) "s,^gdbus_codegen=.*,gdbus_codegen=$(STAGING_DIR)/usr/bin/gdbus-codegen,g" $(STAGING_DIR)/usr/lib/pkgconfig/gio-2.0.pc
	$(SED) "s,/usr/lib,$(STAGING_DIR)/usr/lib,g" $(STAGING_DIR)/usr/bin/gdbus-codegen
	tar cjvf $(LIBGLIB2_BINARY_DIR)/$(LIBGLIB2_BINARY_SOURCE) -C $(LIBGLIB2_BINARY_DIR)/libglib2_tmp .
	rm -rf $(LIBGLIB2_BINARY_DIR)/libglib2_tmp

endef

ifeq ($(BR2_ARCH_IS_64),y)
libglib2-binary: libiconv
	tar -xjvf $(LIBGLIB2_BINARY_DIR)/$(LIBGLIB2_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(LIBGLIB2_BINARY_DIR)/$(LIBGLIB2_BINARY_SOURCE) -C $(TARGET_DIR)/
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/lib/libgthread-2.0.la $(STAGING_DIR)/usr/lib/libglib-2.0.la \
	$(STAGING_DIR)/usr/lib/libiconv.la -lpthread -L$(STAGING_DIR)/usr/lib $(STAGING_DIR)/usr/lib64/libffi.la \
	$(STAGING_DIR)/usr/lib/libintl.la -lc',g" $(STAGING_DIR)/usr/lib/libgobject-2.0.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/lib/libglib-2.0.la $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc',g" $(STAGING_DIR)/usr/lib/libgthread-2.0.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/lib/libgobject-2.0.la $(STAGING_DIR)/usr/lib//libgthread-2.0.la \
	$(STAGING_DIR)/usr/lib64/libffi.la $(STAGING_DIR)/usr/lib/libgmodule-2.0.la -ldl $(STAGING_DIR)/usr/lib//libglib-2.0.la \
	$(STAGING_DIR)/usr/lib/libiconv.la -lpthread -lz $(STAGING_DIR)/usr/lib/libintl.la -lc',g" $(STAGING_DIR)/usr/lib/libgio-2.0.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc' ,g" $(STAGING_DIR)/usr/lib/libglib-2.0.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
-ldl $(STAGING_DIR)/usr/lib/libglib-2.0.la $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc',g" $(STAGING_DIR)/usr/lib/libgmodule-2.0.la
	#LHR: remove gtester,gtester-report,glib-gettextize,glib-compile-resources,glib-compile-schemas,glib-genmarshal,glib-mkenums,gsettings,gobject-query,gresource,gdbus-codegen
	rm -rf $(TARGET_DIR)/usr/bin/gtester
	rm -rf $(TARGET_DIR)/usr/bin/gtester-report
	rm -rf $(TARGET_DIR)/usr/bin/glib-gettextize
	rm -rf $(TARGET_DIR)/usr/bin/glib-compile-resources
	rm -rf $(TARGET_DIR)/usr/bin/glib-compile-schemas
	rm -rf $(TARGET_DIR)/usr/bin/gio-querymodules
	rm -rf $(TARGET_DIR)/usr/bin/glib-genmarshal
	rm -rf $(TARGET_DIR)/usr/bin/glib-mkenums
	rm -rf $(TARGET_DIR)/usr/bin/gsettings
	rm -rf $(TARGET_DIR)/usr/bin/gresource
	rm -rf $(TARGET_DIR)/usr/bin/gobject-query
	rm -rf $(TARGET_DIR)/usr/include/
	rm -rf $(TARGET_DIR)/usr/lib/pkgconfig/
	rm -rf $(TARGET_DIR)/usr/lib/gdbus-2.0/codegen/
	rm -rf $(TARGET_DIR)/usr/lib/glib-2.0/include/
	rm -rf $(TARGET_DIR)/usr/share/glib-2.0/
	rm -rf $(TARGET_DIR)/usr/bin/gdbus-codegen
ifneq ($(BR2_SKY_BUILD_TYPE),"debug")
	rm -rf $(TARGET_DIR)/etc/bash_completion.d
	rm -rf $(TARGET_DIR)/usr/share/locale
	rm -rf $(TARGET_DIR)/usr/bin/gdbus
	rm -rf $(TARGET_DIR)/usr/share/gdb
	rm -rf $(TARGET_DIR)/usr/share/aclocal
endif

else


libglib2-binary: libiconv
	tar -xjvf $(LIBGLIB2_BINARY_DIR)/$(LIBGLIB2_BINARY_SOURCE) -C $(STAGING_DIR)/
	tar -xjvf $(LIBGLIB2_BINARY_DIR)/$(LIBGLIB2_BINARY_SOURCE) -C $(TARGET_DIR)/
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/lib/libgthread-2.0.la $(STAGING_DIR)/usr/lib/libglib-2.0.la \
	$(STAGING_DIR)/usr/lib/libiconv.la -lpthread -L$(STAGING_DIR)/usr/lib $(STAGING_DIR)/usr/lib/libffi.la \
	$(STAGING_DIR)/usr/lib/libintl.la -lc',g" $(STAGING_DIR)/usr/lib/libgobject-2.0.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/lib/libglib-2.0.la $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc',g" $(STAGING_DIR)/usr/lib/libgthread-2.0.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/lib/libgobject-2.0.la $(STAGING_DIR)/usr/lib//libgthread-2.0.la \
	$(STAGING_DIR)/usr/lib/libffi.la $(STAGING_DIR)/usr/lib/libgmodule-2.0.la -ldl $(STAGING_DIR)/usr/lib//libglib-2.0.la \
	$(STAGING_DIR)/usr/lib/libiconv.la -lpthread -lz $(STAGING_DIR)/usr/lib/libintl.la -lc',g" $(STAGING_DIR)/usr/lib/libgio-2.0.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	$(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc' ,g" $(STAGING_DIR)/usr/lib/libglib-2.0.la
	$(SED) "s,^dependency_libs=.*,dependency_libs=\'-L$(STAGING_DIR)/lib -L$(STAGING_DIR)/usr/lib \
	-ldl $(STAGING_DIR)/usr/lib/libglib-2.0.la $(STAGING_DIR)/usr/lib/libiconv.la -lpthread \
	$(STAGING_DIR)/usr/lib/libintl.la -lc',g" $(STAGING_DIR)/usr/lib/libgmodule-2.0.la
	#Adding the Staging directory path to the package config file and the gdbus-codegen python script
	$(SED) "s,^gdbus_codegen=.*,gdbus_codegen=$(STAGING_DIR)/usr/bin/gdbus-codegen,g" $(STAGING_DIR)/usr/lib/pkgconfig/gio-2.0.pc
	$(SED) "s,/usr/lib,$(STAGING_DIR)/usr/lib,g" $(STAGING_DIR)/usr/bin/gdbus-codegen
	#LHR: remove gtester,gtester-report,glib-gettextize,glib-compile-resources,glib-compile-schemas,glib-genmarshal,glib-mkenums,gsettings,gobject-query,gresource,gdbus-codegen
	rm -rf $(TARGET_DIR)/usr/bin/gtester
	rm -rf $(TARGET_DIR)/usr/bin/gtester-report
	rm -rf $(TARGET_DIR)/usr/bin/glib-gettextize
	rm -rf $(TARGET_DIR)/usr/bin/glib-compile-resources
	rm -rf $(TARGET_DIR)/usr/bin/glib-compile-schemas
	rm -rf $(TARGET_DIR)/usr/bin/gio-querymodules
	rm -rf $(TARGET_DIR)/usr/bin/glib-genmarshal
	rm -rf $(TARGET_DIR)/usr/bin/glib-mkenums
	rm -rf $(TARGET_DIR)/usr/bin/gsettings
	rm -rf $(TARGET_DIR)/usr/bin/gresource
	rm -rf $(TARGET_DIR)/usr/bin/gobject-query
	rm -rf $(TARGET_DIR)/usr/include/
	rm -rf $(TARGET_DIR)/usr/lib/pkgconfig/
	rm -rf $(TARGET_DIR)/usr/lib/gdbus-2.0/codegen/
	rm -rf $(TARGET_DIR)/usr/lib/glib-2.0/include/
	rm -rf $(TARGET_DIR)/usr/share/glib-2.0/
	rm -rf $(TARGET_DIR)/usr/bin/gdbus-codegen
ifneq ($(BR2_SKY_BUILD_TYPE),"debug")
	rm -rf $(TARGET_DIR)/etc/bash_completion.d
	rm -rf $(TARGET_DIR)/usr/share/locale
	rm -rf $(TARGET_DIR)/usr/bin/gdbus
	rm -rf $(TARGET_DIR)/usr/share/gdb
	rm -rf $(TARGET_DIR)/usr/share/aclocal
endif

endif
libglib2-binary-clean:
	 rm -rf $(LIBGLIB2_INSTALL_BINARY)

LIBGLIB2_POST_INSTALL_STAGING_HOOKS += LIBGLIB2_POST_INSTALL_CUSTOMISATION
LIBGLIB2_POST_INSTALL_TARGET_HOOKS += LIBGLIB2_TARGET_CLEAN_UP

ifneq ($(BR2_ENABLE_LOCALE),y)
LIBGLIB2_DEPENDENCIES+=libiconv
endif

ifeq ($(BR2_PACKAGE_LIBGLIB2),y)
TARGETS+=libglib2
LIBGLIB2_DEPENDS+=uclibc
LIBGLIB2_DEPENDS+=pkgconfig 
LIBGLIB2_DEPENDS+=gettext 
LIBGLIB2_DEPENDS+=libiconv
LIBGLIB2_DEPENDS+=libffi
LIBGLIB2_DEPENDS+=zlib
endif

ifeq ($(wildcard $(LIBGLIB2_INSTALL_BINARY)),)
$(eval $(call AUTOTARGETS,package,libglib2))
else
libglib2: libglib2-binary 
endif
