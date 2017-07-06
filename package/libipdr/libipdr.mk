#############################################################
#
# libipdr
#
#############################################################

# Current version, use the latest unless there are any known issues.
LIBIPDR_VERSION=1.2.3
# The filename of the package to download.
LIBIPDR_SOURCE=libipdr-$(LIBIPDR_VERSION).tar.bz2
# The site and path to where the source packages are.
LIBIPDR_SITE=http://www.example.net/libipdr/source
# The directory which the source package is extracted to.
# LIBIPDR_DIR=$(BUILD_DIR)/libipdr-$(LIBIPDR_VERSION)
LIBIPDR_DIR=$(BUILD_DIR)/libipdr
# Which decompression to use, BZCAT or ZCAT.
LIBIPDR_CAT:=$(BZCAT)
# Target binary for the package.
#LIBIPDR_BINARY:=libipdr
# Not really needed, but often handy define.
#LIBIPDR_TARGET_BINARY:=usr/bin/$(LIBIPDR_BINARY)
LIBIPDR_INCLUDE:=$(STAGING_DIR)/usr/include/libxml2

# The download rule. Main purpose is to download the source package.
$(DL_DIR)/$(LIBIPDR_SOURCE):
	$(WGET) -P $(DL_DIR) $(LIBIPDR_SITE)/$(LIBIPDR_SOURCE)

# The unpacking rule. Main purpose is to extract the source package, apply any
# patches and update config.guess and config.sub.
$(LIBIPDR_DIR)/.unpacked: $(DL_DIR)/$(LIBIPDR_SOURCE)
	$(LIBIPDR_CAT) $(DL_DIR)/$(LIBIPDR_SOURCE) | tar -C $(BUILD_DIR) $(TAR_OPTIONS) -
	toolchain/patch-kernel.sh $(LIBIPDR_DIR) package/libipdr/ libipdr-$(LIBIPDR_VERSION)-\*.patch\*
	$(CONFIG_UPDATE) $(LIBIPDR_DIR)
	touch $@

# The configure rule. Main purpose is to get the package ready for compilation,
# usually by running the configure script with different kinds of options
# specified.
$(LIBIPDR_DIR)/.configured: $(LIBIPDR_DIR)/.unpacked
	(cd $(LIBIPDR_DIR); rm -rf config.cache; \
		$(TARGET_CONFIGURE_OPTS) \
		$(TARGET_CONFIGURE_ARGS) \
		$(LIBIPDR_DIR)/configure \
		--target=$(GNU_TARGET_NAME) \
		--host=$(GNU_TARGET_NAME) \
		--build=$(GNU_HOST_NAME) \
		--prefix=/usr \
		--sysconfdir=/etc \
		CFLAGS="-I$(LIBIPDR_INCLUDE)" \
		LDFLAGS="-L$(STAGING_DIR)/usr/lib" \
		$(DISABLE_NLS) \
		$(DISABLE_LARGEFILE) \
	)
	touch $@

#$(LIBIPDR_DIR)/$(LIBIPDR_BINARY): $(LIBIPDR_DIR)/.configured
#	$(MAKE) -C $(LIBIPDR_DIR)

# The installing rule. Main purpose is to install the binary into the target
# root directory and make sure it is stripped from debug symbols to reduce the
# space requirements to a minimum.
#
# Only the files needed to run the application should be installed to the
# target root directory, to not waste valuable flash space.
#$(TARGET_DIR)/$(LIBIPDR_TARGET_BINARY): $(LIBIPDR_DIR)/$(LIBIPDR_BINARY)
#	cp -dpf $(LIBIPDR_DIR)/libipdr $@
#	$(STRIPCMD) --strip-unneeded $@

# Main rule which shows which other packages must be installed before the libipdr
# package is installed. This to ensure that all depending libraries are
# installed.
libipdr: libxml2  $(TARGET_DIR)/$(LIBIPDR_TARGET_BINARY)

# Source download rule. Main purpose to download the source package. Since some
# people would like to work offline, it is mandotory to implement a rule which
# downloads everything this package needs.
libipdr-source: $(DL_DIR)/$(LIBIPDR_SOURCE)

# Clean rule. Main purpose is to clean the build directory, thus forcing a new
# rebuild the next time Buildroot is made.
libipdr-clean:
	-$(MAKE) -C $(LIBIPDR_DIR) clean

# Directory clean rule. Main purpose is to remove the build directory, forcing
# a new extraction, patching and rebuild the next time Buildroot is made.
libipdr-dirclean:
	rm -rf $(LIBIPDR_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
# This is how the libipdr package is added to the list of rules to build.
ifeq ($(BR2_PACKAGE_LIBIPDR),y)
TARGETS+=libipdr
endif
