all: rlogind

include ../MCONFIG
include ../MRULES

OBJS = rlogind.o network.o auth.o
# logwtmp.o

ifeq ($(USE_PAM),1)
OBJS += sockconv.o
CFLAGS += -DUSE_PAM
LIBS += -ldl -lpam -lpam_misc
endif

rlogind: $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

rlogind.o: pathnames.h logwtmp.h rlogind.h ../version.h
logwtmp.o: logwtmp.h
auth.o network.o: rlogind.h

install: rlogind
	install -s -m$(DAEMONMODE) rlogind $(INSTALLROOT)$(SBINDIR)/in.rlogind
	install -m$(MANMODE) rlogind.8 $(INSTALLROOT)$(MANDIR)/man8/in.rlogind.8
	ln -sf in.rlogind.8 $(INSTALLROOT)$(MANDIR)/man8/rlogind.8

clean:
	rm -f *.o rlogind

