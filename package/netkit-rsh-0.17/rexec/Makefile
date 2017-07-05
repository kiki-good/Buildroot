all: rexec

include ../MCONFIG
include ../MRULES

PROG=rexec
OBJS=rexec.o

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

install: $(PROG)
	install -s -m $(BINMODE) $(PROG) $(INSTALLROOT)$(BINDIR)
	install -m $(MANMODE) $(PROG).1 $(INSTALLROOT)$(MANDIR)/man1

clean:
	rm -f *.o $(PROG)

$(OBJS): ../version.h
