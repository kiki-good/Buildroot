
all:	libresolv-refresh.so spawn_test resolver_test

libresolv-refresh.so:	ResolveRefresh.o
	$(CC) $(LDFLAGS) -shared -ldl -lpthread -o $@ $^

spawn_test:	spawn_test.o
	$(CC) $(LDFLAGS) -lpthread -ldl -o $@ $^

resolver_test:	resolver_test.o
	$(CC) $(LDFLAGS) -lpthread -ldl -o $@ $^

%.o:	%.c
	$(CC) $(CFLAGS) -c -fPIC -pthread -o $@ $^

clean:
	rm -f libresolv-refresh.so ResolveRefresh.o \
		spawn_test spawn_test.o \
		resolver_test resolver_test.o

