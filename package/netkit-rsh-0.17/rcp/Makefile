all: rcp

include ../MCONFIG
include ../MRULES

rcp: rcp.o
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

install: rcp
	install -s -o root -m$(SUIDMODE) rcp $(INSTALLROOT)$(BINDIR)
	install -m$(MANMODE) rcp.1 $(INSTALLROOT)$(MANDIR)/man1

clean:
	rm -f *.o rcp

rcp.o: ../version.h
