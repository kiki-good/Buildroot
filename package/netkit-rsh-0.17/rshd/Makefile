all: rshd

include ../MCONFIG
include ../MRULES

OBJS = rshd.o

ifeq ($(USE_PAM),1)
# ?
CFLAGS += # -DUSE_PAM
LIBS += -ldl # -lpam -lpam_misc
endif

rshd: $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

install: rshd
	install -s -m$(DAEMONMODE) rshd $(INSTALLROOT)$(SBINDIR)/in.rshd
	install -m$(MANMODE) rshd.8 $(INSTALLROOT)$(MANDIR)/man8/in.rshd.8
	ln -sf in.rshd.8 $(INSTALLROOT)$(MANDIR)/man8/rshd.8

clean:
	rm -f *.o rshd

$(OBJS): ../version.h
