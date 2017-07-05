all: rexecd

include ../MCONFIG
include ../MRULES

#ifdef HAVE_TCP_WRAPPER_LIBRARY
#CFLAGS += -DTCP_WRAPPER
#endif

ifeq ($(USE_PAM),1)
CFLAGS += -DUSE_PAM
LIBS += -ldl -lpam
endif

ifeq ($(USE_SHADOW),1)
CFLAGS += -DUSE_SHADOW
LIBS += $(LIBSHADOW)
endif

# -DRESTRICT_FTP if you want to deny all users in /etc/ftpusers to use rexecd
#ifeq ($(RESTRICT_FTP),1)
#CFLAGS += -DRESTRICT_FTP
#endif 
CFLAGS += -DRESTRICT_FTP=1

rexecd: rexecd.o
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

install: rexecd
	install -s -m$(DAEMONMODE) rexecd $(INSTALLROOT)$(SBINDIR)/in.rexecd
	install -m$(MANMODE) rexecd.8 $(INSTALLROOT)$(MANDIR)/man8/in.rexecd.8
	ln -sf in.rexecd.8 $(INSTALLROOT)$(MANDIR)/man8/rexecd.8
ifeq ($(USE_PAM),1)
	@echo
	@echo You have chosen to use PAM as the authentication method
	@echo You should copy the rexec.pam file provided to /etc/pam.d
	@echo or if you know what you are doing, tailor it to your needs
	@echo
endif	

clean:
	rm -f *.o rexecd

rexecd.o: ../version.h
