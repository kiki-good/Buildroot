all: rlogin

include ../MCONFIG
include ../MRULES

PROG=rlogin
OBJS=rlogin.o

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

install: $(PROG)
	install -s -o root -m$(SUIDMODE) $(PROG) $(INSTALLROOT)$(BINDIR)
	install -m $(MANMODE) $(PROG).1 $(INSTALLROOT)$(MANDIR)/man1

clean:
	rm -f *.o $(PROG)

$(OBJS): ../version.h
