#############################################################
#
# firewall
#
#############################################################

FIREWALL_SCRIPT:=$(TARGET_DIR)/etc/setup-firewall.sh
DOLLAR:="$$"

firewall:
	@rm -f $(FIREWALL_SCRIPT)
	@touch $(FIREWALL_SCRIPT)
	@chmod a+x $(FIREWALL_SCRIPT)

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "#!/bin/sh" >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
	@echo "export NETWORK_INTERFACE="$(DOLLAR)1"" >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
else
	@echo "#!/bin/sh" >> $(FIREWALL_SCRIPT)
	@echo "export NETWORK_INTERFACE="$(DOLLAR)1"" >> $(FIREWALL_SCRIPT)
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_PROC_SYS),y)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "####################################                             " >> $(FIREWALL_SCRIPT)
	@echo "# Use /proc/sys/to restrict  networking                          " >> $(FIREWALL_SCRIPT)
	@echo "# Some of this will duplicate setups in the iptables             " >> $(FIREWALL_SCRIPT)
endif	
ifeq ($(BR2_SKY_BUILD_TYPE),"prod")
	@echo "/bin/writefile \"0\" /proc/sys/net/ipv4/ip_forward                  " >> $(FIREWALL_SCRIPT)
else
	@echo "/bin/echo \"0\" > /proc/sys/net/ipv4/ip_forward                  " >> $(FIREWALL_SCRIPT)
endif
ifeq (,$(filter y,$(BR2_PACKAGE_SKY_FIREWALL_ALLOW_PING) $(BR2_PACKAGE_SKY_FIREWALL_ALLOW_EXTERNAL_PING) $(BR2_PACKAGE_SKY_FIREWALL_ALLOW_DIAG_ICMP)))
ifeq ($(BR2_SKY_BUILD_TYPE),"prod")
	@echo "/bin/writefile \"1\" /proc/sys/net/ipv4/icmp_echo_ignore_all        " >> $(FIREWALL_SCRIPT)
else
	@echo "/bin/echo \"1\" > /proc/sys/net/ipv4/icmp_echo_ignore_all        " >> $(FIREWALL_SCRIPT)
endif
endif
ifeq ($(BR2_SKY_BUILD_TYPE),"prod")
	@echo "/bin/writefile \"1\" /proc/sys/net/ipv4/icmp_echo_ignore_broadcasts " >> $(FIREWALL_SCRIPT)
else
	@echo "/bin/echo \"1\" > /proc/sys/net/ipv4/icmp_echo_ignore_broadcasts " >> $(FIREWALL_SCRIPT)
endif
endif

	# Always enable the looback interface, although disable external packets claiming to be
	# from the loopback interface.
	@echo "/usr/sbin/iptables -F		  				   " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -X		  				   " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -P INPUT DROP  				   " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -P OUTPUT DROP				   " >> $(FIREWALL_SCRIPT)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "#####################################                       " >> $(FIREWALL_SCRIPT)
	@echo "# Loopback interface                                        " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i lo -j ACCEPT                 " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A OUTPUT -o lo -j ACCEPT                " >> $(FIREWALL_SCRIPT)
	@echo "# Refuse packets claiming to be to the loopback interface.  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT  -i "$(DOLLAR)NETWORK_INTERFACE" -d 127.0.0.0/8 -j DROP " >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)

	@echo "####################################                 " >> $(FIREWALL_SCRIPT)
	@echo "# OUTPUT                                             " >> $(FIREWALL_SCRIPT)
	@echo "# Allow all outgoing                                 " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A OUTPUT -j ACCEPT               " >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
else
	@echo "/usr/sbin/iptables -A INPUT -i lo -j ACCEPT                 " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A OUTPUT -o lo -j ACCEPT                " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT  -i "$(DOLLAR)NETWORK_INTERFACE" -d 127.0.0.0/8 -j DROP " >> $(FIREWALL_SCRIPT)

	@echo "/usr/sbin/iptables -A OUTPUT -j ACCEPT               " >> $(FIREWALL_SCRIPT)
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_HTTP),y)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "####################################                                                         " >> $(FIREWALL_SCRIPT)
	@echo "# HTTP / Generic                                                                             " >> $(FIREWALL_SCRIPT)
	@echo "# Rule to allow outgoing connections on any port.                                            " >> $(FIREWALL_SCRIPT)
	@echo "# Intended for HTTP connections however can't guarantee port 80                              " >> $(FIREWALL_SCRIPT)
	@echo "# will be used, therefore the rule is very generic.                                          " >> $(FIREWALL_SCRIPT)
	@echo "# Rule to allow any releated or establised incomming connections                             " >> $(FIREWALL_SCRIPT)
	@echo "# Again intended for HTTP traffic but can't guarantee port 80                                " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp -m state --state ESTABLISHED,RELATED -j ACCEPT    " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp -m state --state ESTABLISHED,RELATED -j ACCEPT    " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p icmp -m state --state ESTABLISHED,RELATED -j ACCEPT    " >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
else
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp -m state --state ESTABLISHED,RELATED -j ACCEPT    " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp -m state --state ESTABLISHED,RELATED -j ACCEPT    " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p icmp -m state --state ESTABLISHED,RELATED -j ACCEPT    " >> $(FIREWALL_SCRIPT)
endif
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_OQTP),y)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "####################################                                                                          " >> $(FIREWALL_SCRIPT)
	@echo "# OQTP                                                                                                        " >> $(FIREWALL_SCRIPT)
	@echo "# Allow OQTP requests from the STB and responses from the server.                                             " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp -m state --state ESTABLISHED -j ACCEPT                             " >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
else
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp -m state --state ESTABLISHED -j ACCEPT                             " >> $(FIREWALL_SCRIPT)
endif
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_DHCP),y)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "####################################                                                                          " >> $(FIREWALL_SCRIPT)
	@echo "# DHCP                                                                                                        " >> $(FIREWALL_SCRIPT)
	@echo "# Allow DHCP requests from the STB and responses from the NTE.                                                " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 67:68 --sport 67:68 -j ACCEPT                              " >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
else
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 67:68 --sport 67:68 -j ACCEPT                              " >> $(FIREWALL_SCRIPT)
endif
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_DNS),y)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "#####################################                                                                          " >> $(FIREWALL_SCRIPT)
	@echo "# DNS                                                                                                          " >> $(FIREWALL_SCRIPT)
	@echo "# Allow DNS requests and responses.                                                                            " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --sport 53 --dport 1024:65535 -m state --state ESTABLISHED -j ACCEPT" >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
else
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --sport 53 --dport 1024:65535 -m state --state ESTABLISHED -j ACCEPT" >> $(FIREWALL_SCRIPT)
endif
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "#####################################                                                                          " >> $(FIREWALL_SCRIPT)
	@echo "# ICMP / PING                                                                                                  " >> $(FIREWALL_SCRIPT)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_EXTERNAL_PING),y)
	@echo "# Allow external ping requests and responses                                                                   " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p icmp --icmp-type 8 -s 0/0 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT    " >> $(FIREWALL_SCRIPT)
endif
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_DIAG_ICMP),y)
	@echo "# Allow ICMP packets used for remote debugging diagnostic interface                                            " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p icmp --icmp-type 1 -s 0/0 -j ACCEPT                                             " >> $(FIREWALL_SCRIPT)
endif
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_PING),y)
	@echo "# Allow ICMP echo requests to be sent from the STB and valid                                                   " >> $(FIREWALL_SCRIPT)
	@echo "# replies received.                                                                                            " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p icmp --icmp-type 0 -s 0/0 -m state --state ESTABLISHED,RELATED -j ACCEPT" >> $(FIREWALL_SCRIPT)
endif
	@echo "" >> $(FIREWALL_SCRIPT)
else
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_EXTERNAL_PING),y)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p icmp --icmp-type 8 -s 0/0 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT    " >> $(FIREWALL_SCRIPT)
endif
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_DIAG_ICMP),y)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p icmp --icmp-type 1 -s 0/0 -j ACCEPT                                             " >> $(FIREWALL_SCRIPT)
endif
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_PING),y)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p icmp --icmp-type 0 -s 0/0 -m state --state ESTABLISHED,RELATED -j ACCEPT" >> $(FIREWALL_SCRIPT)
endif
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_CA_CALLBACK),y)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "####################################                                                            " >> $(FIREWALL_SCRIPT)
	@echo "# CA Callback / PPP                                                                             " >> $(FIREWALL_SCRIPT)
	@echo "# Allows TCP connections to/from port 129000.                                                   " >> $(FIREWALL_SCRIPT)
	@echo "# Assumes the link will be given the identifier tun0.                                           " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i tun0 -p tcp --sport 12900 -m state --state ESTABLISHED -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
else
	@echo "/usr/sbin/iptables -A INPUT -i tun0 -p tcp --sport 12900 -m state --state ESTABLISHED -j ACCEPT " >> $(FIREWALL_SCRIPT)
endif
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_PPP_HTTP),y)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "####################################                                                          " >> $(FIREWALL_SCRIPT)
	@echo "# LAE / PPP                                                                                   " >> $(FIREWALL_SCRIPT)
	@echo "# Allows established UDP/TCP connections over the PPP interface                               " >> $(FIREWALL_SCRIPT)
	@echo "# Assumes the link will be given the identifier tun0.                                         " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i tun0 -p tcp -m state --state ESTABLISHED,RELATED -j ACCEPT     " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i tun0 -p udp -m state --state ESTABLISHED,RELATED -j ACCEPT     " >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
else
	@echo "/usr/sbin/iptables -A INPUT -i tun0 -p tcp -m state --state ESTABLISHED,RELATED -j ACCEPT     " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i tun0 -p udp -m state --state ESTABLISHED,RELATED -j ACCEPT     " >> $(FIREWALL_SCRIPT)
endif
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_MW_DEBUG),y)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "#####################################                      " >> $(FIREWALL_SCRIPT)
	@echo "# MW Debugging                                             " >> $(FIREWALL_SCRIPT)
	@echo "# Allow incoming UDP packets sent to port 5555             " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 5555 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
else
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 5555 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
endif
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_GDBSERVER),y)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "#####################################                       " >> $(FIREWALL_SCRIPT)
	@echo "# GDB Server                                                " >> $(FIREWALL_SCRIPT)
	@echo "# Allow incoming TCP packets sent to port 12345             " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 12345 -j ACCEPT  " >> $(FIREWALL_SCRIPT)	
	@echo "" >> $(FIREWALL_SCRIPT)
else
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 12345 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
endif
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_TELNET),y)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "#####################################                               " >> $(FIREWALL_SCRIPT)
	@echo "# Telnet                                                            " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport telnet -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
else
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport telnet -j ACCEPT " >> $(FIREWALL_SCRIPT)
endif
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_FTP),y)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "#####################################                                                          " >> $(FIREWALL_SCRIPT)
	@echo "# FTP                                                                                          " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --sport ftp -j ACCEPT                               " >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
else
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --sport ftp -j ACCEPT                               " >> $(FIREWALL_SCRIPT)
endif
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_HFL_DEBUG),y)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "#####################################                       " >> $(FIREWALL_SCRIPT)
	@echo "# HFL Debugging                                             " >> $(FIREWALL_SCRIPT)
	@echo "# Allow incoming TCP packets sent to port 20077 HFL Studio  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 20077 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
else
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 20077 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
endif
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_UPNP),y)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "#####################################                       " >> $(FIREWALL_SCRIPT)
	@echo "# UPNP                                             	   " >> $(FIREWALL_SCRIPT)
	@echo "# Allow incoming UDP 1900 49154 TCP 5900 49153  		   " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 49153 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 5900 -j ACCEPT   " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 1900 -j ACCEPT   " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 49154   -j ACCEPT" >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
else
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 49153 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 5900 -j ACCEPT   " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p  udp --dport 1900 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 49154   -j ACCEPT" >> $(FIREWALL_SCRIPT)
endif
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_MR_GW_COMM),y)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "#####################################                       " >> $(FIREWALL_SCRIPT)
	@echo "# MR <-> GW generic communication                           " >> $(FIREWALL_SCRIPT)
	@echo "# Allow incoming  TCP 49155 			           " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 49155 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
else
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 49155 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
endif
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_SSH),y)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "#####################################                       " >> $(FIREWALL_SCRIPT)
	@echo "# Allow SSH Traffic                                         " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 22 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
else
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 22 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
endif
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_FUSION_SLAVE_SOAP_PORT),y)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "#####################################                       " >> $(FIREWALL_SCRIPT)
	@echo "# Allow incoming TCP 9997 to 9999 Traffic                                         " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 9997:9999 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
else
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 9997:9999 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
endif
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ALLOW_CISCO_FIREWALL),y)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "# Transcode Port - Port use for transcoding and sideloading requests from CE devices  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 4545  -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 4730  -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 4730  -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 4733  -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 4733  -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	# For fixing oversized mesh packet issue NGDEV 70670
	@echo "/usr/sbin/iptables -t mangle -A OUTPUT -p tcp --tcp-flags SYN,RST SYN -j TCPMSS --clamp-mss-to-pmtu " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -t mangle -A FORWARD -p tcp --tcp-flags SYN,RST SYN -j TCPMSS --clamp-mss-to-pmtu " >> $(FIREWALL_SCRIPT)

	@echo "" >> $(FIREWALL_SCRIPT)

	@echo "# AS" >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 9005:9008  -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)

	@echo "# Multicast packets " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -d 224.0.0.0/4 -j ACCEPT  " >> $(FIREWALL_SCRIPT)

	@echo "#Required for AS " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 1234 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 3210 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 8123 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 123 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 80 -j ACCEPT  " >> $(FIREWALL_SCRIPT)

	@echo "#AIRPLAY " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 13579 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 5000:5001 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 5010 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 6000 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 6000:6002 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 6010:6011 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 6020:6021 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 6030 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 6040 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 6041 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 6042 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 6042 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 6043 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 6100 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 6100 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 6200 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 6200 -j ACCEPT " >> $(FIREWALL_SCRIPT)

	@echo "#mDNS " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 5353 -j ACCEPT " >> $(FIREWALL_SCRIPT)

	@echo "#DIAL " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 8008 -j ACCEPT " >> $(FIREWALL_SCRIPT)

	@echo "#WEBSOCKET-SERVER " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 9091 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)

	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 8080:8081 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 49162 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 49163 -j ACCEPT" >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
else
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 4545  -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 4730  -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 4730  -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 4733  -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 4733  -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -t mangle -A OUTPUT -p tcp --tcp-flags SYN,RST SYN -j TCPMSS --clamp-mss-to-pmtu " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -t mangle -A FORWARD -p tcp --tcp-flags SYN,RST SYN -j TCPMSS --clamp-mss-to-pmtu " >> $(FIREWALL_SCRIPT)


	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 9005:9008  -j ACCEPT  " >> $(FIREWALL_SCRIPT)

	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -d 224.0.0.0/4 -j ACCEPT  " >> $(FIREWALL_SCRIPT)

	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 1234 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 8123 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 123 -j ACCEPT  " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 80 -j ACCEPT  " >> $(FIREWALL_SCRIPT)

	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 13579 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 5000:5001 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 5010 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 6000 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 6000:6002 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 6010:6011 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 6020:6021 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 6030 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 6040 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 6041 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 6042 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 6042 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 6043 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 6100 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 6100 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 6200 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 6200 -j ACCEPT " >> $(FIREWALL_SCRIPT)

	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p udp --dport 5353 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 8008 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 9091 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 8080:8081 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 49162 -j ACCEPT " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 49163 -j ACCEPT" >> $(FIREWALL_SCRIPT)
endif

ifeq ($(BR2_PACKAGE_MALI_GRAPHICS_DEBUGGER),y)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "# Mali Graphics Debugger" >> $(FIREWALL_SCRIPT)
endif
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -p tcp --dport 5002 -j ACCEPT " >> $(FIREWALL_SCRIPT)
ifeq ($(BR2_PACKAGE_SKY_FIREWALL_TURN_ON_TEXT),y)
	@echo "" >> $(FIREWALL_SCRIPT)
endif
endif

ifeq ($(BR2_PACKAGE_SKY_FIREWALL_ENABLE_LOGS),y)
ifneq ($(BR2_SKY_BUILD_TYPE),"prod")
#Log dropped packets
	@echo "/usr/sbin/iptables -N LOGGING " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A INPUT -j LOGGING " >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A LOGGING -j LOG  -m limit --limit 100/min --log-prefix \"IPTables Packet Dropped: \" --log-level 7" >> $(FIREWALL_SCRIPT)
	@echo "/usr/sbin/iptables -A LOGGING -j DROP " >> $(FIREWALL_SCRIPT)
	@echo "" >> $(FIREWALL_SCRIPT)
endif
endif
endif


	# Drop everything else
	@echo "/usr/sbin/iptables -A INPUT -i "$(DOLLAR)NETWORK_INTERFACE" -j DROP  " >> $(FIREWALL_SCRIPT)

firewall-source:

firewall-clean:
	# Remove the script and create a new one
	rm -f $(FIREWALL_SCRIPT)

firewall-dirclean: firewall-clean


#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_SKY_FIREWALL),y)
TARGETS+=firewall
endif
