# ###################################################################
#	@file Makefile
#	@author Tijo Thomas John <tijo.thomas@bsykb.com>
#
#	Copyright (c) bSkyb Limited 2015
#
#	P R O P R I E T A R Y  &  C O N F I D E N T I A L
#	
# ###################################################################

TOOLCHAIN=/opt/toolchains/stbgcc-4.5.3-2.5
CROSS_COMPILE=$(TOOLCHAIN)/bin/arm-linux-

CC    = $(CROSS_COMPILE)gcc 
AR    = $(CROSS_COMPILE)ar 
STRIP = $(CROSS_COMPILE)strip
INSTALL= $(DESTDIR)
OBJS := $(patsubst %.c,%.o,$(wildcard *.c))


all:pgm_bt_addr

pgm_bt_addr: $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

install: pgm_bt_addr
	mkdir -p $(INSTALL)/usr/bin
	cp pgm_bt_addr $(INSTALL)/usr/bin

.PHONY: all 

clean:
	rm -f $(OBJS) pgm_bt_addr $(INSTALL)/usr/bin/pgm_bt_addr 
