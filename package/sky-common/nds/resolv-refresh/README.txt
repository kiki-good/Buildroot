This code was provided by NDS to solve PR#7885: UCLIBC does not
refresh DNS information once /etc/resolv.conf is changed.

The following text was provided by NDS.

By default, DNS server information in resolv.conf is only read on
process start up. The purpose of the ResolveRefresh library is to
reinitialize uclibc resolver on changes of resolv.conf file. The
library is a hack that makes use of LD_PRELOAD environment variable to
overload uclibc functions performing DNS resolutions that are part of
POSIX Subset:

getaddrinfo, gethostbyaddr, gethostbyname, getnameinfo

When calls to these functions are intercepted, library first checks
modification of resolv.conf file. If modification is detected, library
calls __res_init() to re-initialize uclibc resolver state triggering
re-read of resolv.conf file. Calls are the passed on to relevant
functions. Note this will only work for dynamically linked apps.

Big portion of the library deals with the fact, uclibc isn.t compiled
with the support for /etc/ld.so.preload. The library would be much
simpler with this option enabled.

As a side effect, execv function also needs to be pre-loaded and
environment passed to it hijacked.

Library source contains further documentation.

Find attached:

- ResolveRefresh library source( ResolveRefresh.c )

- Test application sources and binaries ( spawn_test,
  test_resolver )

The tests can be run like this:

LD_PRELOAD=/root/libresolv-refresh.so spawn_test /root/test_resolver massive

LD_PRELOAD has to match the path to the library and the tests will
fail if ./etc/hosts. doesn.t exist. Empty hosts file makes the
resolver happy again.

The library has not been tested with GDB.
