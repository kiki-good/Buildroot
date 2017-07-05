## Makefile.in for ICU - extra/scrptrun
## Copyright (c) 2001-2011, International Business Machines Corporation and
## others. All Rights Reserved.

## Source directory information
srcdir = .
top_srcdir = ../..

top_builddir = ../..

include $(top_builddir)/icudefs.mk

## Platform-specific setup
include $(top_srcdir)/config/mh-linux

## Build directory information
subdir = extra/scrptrun

## Extra files to remove for 'make clean'
CLEANFILES = *~ $(DEPS)

## Target information
TARGET = srtest

DEFS = -DPACKAGE_NAME=\"ICU\" -DPACKAGE_TARNAME=\"International\ Components\ for\ Unicode\" -DPACKAGE_VERSION=\"56.1\" -DPACKAGE_STRING=\"ICU\ 56.1\" -DPACKAGE_BUGREPORT=\"http://icu-project.org/bugs\" -DPACKAGE_URL=\"http://icu-project.org\" -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DSIZEOF_VOID_P=8 -DHAVE_LIBM=1 -DHAVE_ELF_H=1 -DHAVE_DLFCN_H=1 -DHAVE_DLOPEN=1 -DHAVE_GETTIMEOFDAY=1 -DHAVE_LIBPTHREAD=1 -DHAVE_INTTYPES_H=1 -DHAVE_DIRENT_H=1 -DHAVE_WCHAR_H=1 -DSIZEOF_WCHAR_T=4
CPPFLAGS =  $(THREADSCPPFLAGS)  -DU_HAVE_ELF_H=1 -DU_HAVE_ATOMIC=1  -I$(top_srcdir)/common -I$(top_srcdir) 
CFLAGS = -Os  -I/home/jqiao/spk_64bit/spk/objOutput/bskyb-brcm64bit/build_aarch64/staging_dir/include -I/home/jqiao/spk_64bit/spk/objOutput/bskyb-brcm64bit/build_aarch64/staging_dir/usr/include -I/home/hperev/Documents/CDI/1-From-NAS/eric-same-dir/97271IP-Toolchain/stbgcc-4.8-1.5//aarch64-linux/include -std=c99 -pedantic -Wshadow -Wpointer-arith -Wmissing-prototypes -Wwrite-strings $(THREADSCFLAGS) 
CXXFLAGS = -Os  -I/home/jqiao/spk_64bit/spk/objOutput/bskyb-brcm64bit/build_aarch64/staging_dir/include -I/home/jqiao/spk_64bit/spk/objOutput/bskyb-brcm64bit/build_aarch64/staging_dir/usr/include -I/home/hperev/Documents/CDI/1-From-NAS/eric-same-dir/97271IP-Toolchain/stbgcc-4.8-1.5//aarch64-linux/include -pedantic -Wpointer-arith -Wwrite-strings -Wno-long-long --std=c++0x $(THREADSCXXFLAGS) 
ENABLE_RPATH = NO
ifeq ($(ENABLE_RPATH),YES)
RPATHLDFLAGS = $(LD_RPATH)$(LD_RPATH_PRE)$(libdir)
endif
LDFLAGS = -L/home/jqiao/spk_64bit/spk/objOutput/bskyb-brcm64bit/build_aarch64/staging_dir/lib -L/home/jqiao/spk_64bit/spk/objOutput/bskyb-brcm64bit/build_aarch64/staging_dir/usr/lib $(RPATHLDFLAGS)
LIBS = $(LIBICUUC) -lpthread -ldl -lm  

OBJECTS = scrptrun.o srtest.o

DEPS = $(OBJECTS:.o=.d)

## List of phony targets
.PHONY : all all-local install install-local clean clean-local	\
distclean distclean-local dist dist-local check check-local

## Clear suffix list
.SUFFIXES :

## List of standard targets
all: all-local
install: install-local
clean: clean-local
distclean : distclean-local
dist: dist-local
check: all check-local

all-local: $(TARGET)

install-local:

dist-local:

clean-local:
	test -z "$(CLEANFILES)" || $(RMV) $(CLEANFILES)
	$(RMV) $(OBJECTS) $(TARGET)

distclean-local: clean-local
	$(RMV) Makefile

check-local: all-local

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) \
	 && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status

$(TARGET) : $(OBJECTS)
	$(LINK.cc) -o $@ $^ $(LIBS)
	$(POST_BUILD_STEP)

invoke:
	ICU_DATA=$${ICU_DATA:-$(top_builddir)/data/} TZ=PST8PDT $(INVOKE) $(INVOCATION)

ifeq (,$(MAKECMDGOALS))
-include $(DEPS)
else
ifneq ($(patsubst %clean,,$(MAKECMDGOALS)),)
-include $(DEPS)
endif
endif
