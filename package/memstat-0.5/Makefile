#
# Makefile for memstat for Debian GNU/Linux
# Copyright 1998, by Bernd Eckenfels <ecki@debian.org>
# This file is under the GPL.
#
CFLAGS = -O2 -Wall
prefix = $(DESTDIR)/
exec_prefix = $(prefix)/usr

INSTALL = install
INSTALL_PROGRAM = $(INSTALL) -p    -o root -g root  -m  755
INSTALL_FILE    = $(INSTALL) -p    -o root -g root  -m  644
INSTALL_DIR     = $(INSTALL) -p -d -o root -g root  -m  755

ifneq (,$(findstring debug,$(DEB_BUILD_OPTIONS)))
CFLAGS += -g
endif
ifeq (,$(findstring nostrip,$(DEB_BUILD_OPTIONS)))
INSTALL_PROGRAM += -s
endif

memstat: memstat.c

clean:
	rm -f memstat.o memstat DEADJOE *~ */*~

install: memstat
	$(INSTALL_PROGRAM) memstat $(exec_prefix)/bin/memstat
	$(INSTALL_FILE) memstat.conf $(prefix)/etc

