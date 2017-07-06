The if_nameindex() function should return one entry per interface in
the system. However, uclibc's implementation uses ioctl(SIOCGCONF) to
build the list, which results in one entry per configured address per
interface.

The fix is to provide an override if_nameindex function in a shared
library, which is then loaded using LD_PRELOAD to override the
standard uClibc version.

To test this, eth0 was configured with more than one IP address and
the uClibc if_nameindex test app was run. To configure multiple IP
addresses, the iproute2 package was built, since ifconfig can
configure only one address.

sh-3.2# ip addr add 10.1.1.1/24 brd + dev eth0
sh-3.2# ip addr                               
1: eth0: <BROADCAST,MULTICAST,UP,10000> mtu 1500 qdisc pfifo_fast qlen 1000
    link/ether 00:10:18:01:e2:8f brd ff:ff:ff:ff:ff:ff
    inet 10.0.0.2/24 brd 10.0.0.255 scope global eth0
    inet 10.1.1.1/24 brd 10.1.1.255 scope global eth0
2: lo: <LOOPBACK,UP,10000> mtu 16436 qdisc noqueue 
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo

# Demonstrate the problem. eth0 is listed twice when it has 2 IP addresses.
sh-3.2# /root/if_nameindex-test 
--- if_nameindex()
1: eth0
1: eth0
2: lo
if_indextoname(1) = eth0
if_nametoindex(eth0) = 1

# Run the same app using the override function
sh-3.2# export LD_PRELOAD=/lib/libifnameindex.so; /root/if_nameindex-test 
--- if_nameindex()
1: eth0
2: lo
if_indextoname(1) = eth0
if_nametoindex(eth0) = 1


