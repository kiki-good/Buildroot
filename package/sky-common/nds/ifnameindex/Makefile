
all:	libifnameindex.so if_nameindex-test

libifnameindex.so:	if_nameindex.o
	$(CC) $(LDFLAGS) -shared -ldl -lpthread -o $@ $^

if_nameindex-test:	if_nameindex-test.o
	$(CC) $(LDFLAGS) -lpthread -ldl -o $@ $^

%.o:	%.c
	$(CC) $(CFLAGS) -c -fPIC -pthread -o $@ $^

clean:
	rm -f libifnameindex.so if_nameindex.o if_nameindex-test.o if_nameindex-test

