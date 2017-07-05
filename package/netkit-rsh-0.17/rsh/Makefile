all: rsh

include ../MCONFIG
include ../MRULES

OBJS = rsh.o

rsh: $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

install: rsh
	install -s -o root -m$(SUIDMODE) rsh $(INSTALLROOT)$(BINDIR)
	install -m$(MANMODE) rsh.1 $(INSTALLROOT)$(MANDIR)/man1

clean:
	rm -f *.o rsh

$(OBJS): ../version.h
