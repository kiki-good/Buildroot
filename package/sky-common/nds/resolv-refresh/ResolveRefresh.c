/*
 * ResolveRefresh library
 *
 * Author:  Mat Fundarek[NDS] (based on similiar implementation by Jim Hawkins[NDS])
 * Build:   gcc -shared -fPIC -ldl -o libResolveRefresh.so ResolveRefresh.c -O3
 * Install: cp libResolveRefresh.so rootfs/usr/lib/
 * Usage:   LD_PRELOAD=/usr/lib/libResolveRefresh.so SCD_Process
 * PROBLEM: uclibc doesn't monitor resolv.conf changes. This file is only read at the initialization time
 *          as a result modification will only be taken into account on process restart
 *          this isn't an option for Fusion
 *
 * SOLUTION: Pre-load library to force resolv.conf re-read on update
 *           library hooks into functions that perform name resolution(listed further down)
 *           when user calls any of these functions, library performs a time stamp comparison on a resolv.conf file
 *           in either of these 2 locations: 
 *                /etc/resolv.conf
 *           or 
 *                /etc/config/resolv.conf
 *
 *           when modification is detected, library calls __res_init()
 *           to refresh the nameserver configuration
 *
 * FUNCTIONS THAT NEED HANDLING :
 *  int getaddrinfo(const char *restrict nodename,
 *         const char *restrict servname,
 *         const struct addrinfo *restrict hints,
 *         struct addrinfo **restrict res);
 *         
 *  struct hostent *gethostbyaddr(const void *addr, socklen_t len,
 *         int type);
 *         
 *  struct hostent *gethostbyname(const char *name);
 *
 * OPTIONAL HANDLING REQUIRED:
 *   but uclibc implementation calls gethostbyaddr
 *   so handling that one should be sufficient, see CONFIG_GETNAMEINFO_PRELOADED_BY_GETHOSTBYADDR
 *  int getnameinfo(const struct sockaddr *restrict sa, socklen_t salen,
 *         char *restrict node, socklen_t nodelen, char *restrict service,
 *         socklen_t servicelen, int flags);
 *  
 *
 * FUNCTIONS THAT DO NOT NEED HANDLING :
 *  void endservent(void);
 *  struct servent *getservbyname(const char *name, const char *proto);
 *  struct servent *getservbyport(int port, const char *proto);
 *  struct servent *getservent(void);
 *  void setservent(int stayopen);
 *  
 *  void endnetent(void);
 *  struct netent *getnetbyaddr(uint32_t net, int type);
 *  struct netent *getnetbyname(const char *name);
 *  struct netent *getnetent(void);
 *  void setnetent(int stayopen);
 *  
 *  void endprotoent(void);
 *  struct protoent *getprotobyname(const char *name);
 *  struct protoent *getprotobynumber(int proto);
 *  struct protoent *getprotoent(void);
 *  void setprotoent(int stayopen);
 *  
 *  
 *  CUSTOMIZATION:
 *  CONFIG_DEBUG: enable debugging printounts
 *      
 *  CONFIG_PROPAGATE_LD_PRELOAD_VIA_EXECV: make sure LD_PRELOAD is passed on to execv - needed for current posix_spawn implementation
 *      
 *  CONFIG_HARDCODE_LD_PRELOAD_CONTENTS_FOR_EXECV: use hardcoded LD_PRELOAD value rather then one from environment var
 *      
 *  CONFIG_SEPARATE_SYMBOL_INIT_NEEDED: enable if symbol preloading cannot be done from constructor, might be usefull for debugging with gdb
 *      
 *  CONFIG_GETNAMEINFO_PRELOADED_BY_GETHOSTBYADDR: enable if getnameinfo implementation ends up calling gethostbyaddr
 */

/** LIBRARY BUILD CONFIGURATION FLAGS***********************************/
/* enable debugging */
#undef CONFIG_DEBUG

/* define if processes spawned by execv() from NDS posix_spawn() implementation */
#define CONFIG_PROPAGATE_LD_PRELOAD_VIA_EXECV

/* applicable when CONFIG_PROPAGATE_LD_PRELOAD_VIA_EXECV 
* use hardcoded LD_PRELOAD value rather then one from environment var
*/
#undef CONFIG_HARDCODE_LD_PRELOAD_CONTENTS_FOR_EXECV

/* getnameinfo in some uclibc implementations use gethotbyaddr, no need to prelaod getnameinfo*/
#undef CONFIG_GETNAMEINFO_PRELOADED_BY_GETHOSTBYADDR

#ifdef CONFIG_PROPAGATE_LD_PRELOAD_VIA_EXECV
    /* this will de-active initialized? checking in pre-loaded functions 
     * as execv has to be called first 
     * --> currently not used in the source
     */
    #define CONFIG_START_ALL_PROCESSES_VIA_EXECV
#endif

/* enable if symbol preloading cannot be done from constructor, might be usefull for debugging with gdb */
#undef CONFIG_SEPARATE_SYMBOL_INIT_NEEDED


/*************************************/

/* Default library name*/
#define LIB_NAME "libResolveRefresh.so"

/* Default path to library */
#define DEFAULT_LIB_PATH "/usr/lib/" LIB_NAME

/* for RTLD_NEXT */
#define _GNU_SOURCE 1

#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> /* for mutex*/
#include <sys/stat.h>
#include <sys/time.h>
#include <netdb.h>

#ifndef CONFIG_HARDCODE_LD_PRELOAD_CONTENTS_FOR_EXECV
#include <string.h>
#endif

/** Debugging macros****************************************************/
#ifdef CONFIG_DEBUG
    #define DPRINTF(X,args...) fprintf(stderr, X, ##args)
#else
    #define DPRINTF(X,args...)
#endif /* DEBUG */

/** ****************************************************/
#ifdef CONFIG_PROPAGATE_LD_PRELOAD_VIA_EXECV

#ifdef CONFIG_HARDCODE_LD_PRELOAD_CONTENTS_FOR_EXECV
    /* LD_PRELOAD value */
    static const char * ld_preload_value_for_execv = DEFAULT_LIB_PATH;
#else
    static const char * ld_preload_value_for_execv;
#endif /*CONFIG_HARDCODE_LD_PRELOAD_CONTENTS_FOR_EXECV*/

/** Function pointers to hacked system library functions ****************************************************/

    int (*real_execv)(const char *path, char *const argv[]) = NULL;
#endif /*CONFIG_PROPAGATE_LD_PRELOAD_VIA_EXECV*/

struct hostent *(*real_gethostbyaddr)(const void *addr, socklen_t len,
       int type);

struct hostent *(*real_gethostbyname)(const char *name);

#ifndef CONFIG_GETNAMEINFO_PRELOADED_BY_GETHOSTBYADDR
int (*real_getnameinfo)(const struct sockaddr * sa, socklen_t salen,
       char * node, socklen_t nodelen, char * service,
       socklen_t servicelen,unsigned int flags);
#endif

int (*real_getaddrinfo)(const char * nodename,
       const char * servname,
       const struct addrinfo * hints,
       struct addrinfo ** res);

/** define as macro so it can either be part of constructor or separate function*/
#define SYMINIT \
  DPRINTF("dliniting: %s\n", LIB_NAME);\
  for (i = 0; i < sizeof(real_symbols)/sizeof(*real_symbols); i++)\
  {\
    *(real_symbols[i].func) = dlsym(RTLD_NEXT, real_symbols[i].name);\
    if (*(real_symbols[i].func) == NULL)\
    {\
      DPRINTF( "%s: Couldn't load symbol %s\n", LIB_NAME, real_symbols[i].name);\
      exit(1);\
    }\
  }\
  
/** GLOBAL vars*******************************************************************************/
/** stamp for resolv.conf modification time.*/
time_t  _resolvconf_stamp = 0; 

/* time stamp lock*/
static pthread_mutex_t   time_stamp_mutex = PTHREAD_MUTEX_INITIALIZER;

/* List of symbols to be filled in */
struct
{
  const char * const    name;
  void **               func;
}
static real_symbols[] =
{
#ifdef CONFIG_PROPAGATE_LD_PRELOAD_VIA_EXECV
  { "execv",          (void **)&real_execv },
#endif
  { "gethostbyaddr",  (void **)&real_gethostbyaddr },
  { "gethostbyname" , (void **)&real_gethostbyname},
  
#ifndef CONFIG_GETNAMEINFO_PRELOADED_BY_GETHOSTBYADDR
  { "getnameinfo",    (void **)&real_getnameinfo },
#endif
  { "getaddrinfo",    (void **)&real_getaddrinfo },
};

#ifdef CONFIG_SEPARATE_SYMBOL_INIT_NEEDED
/** Init real symbols ***********************************************************
** Do not call from the constructor, because uClibc breaks if we do 
 **/
static void dlinit(void)
{
    int i;

    SYMINIT;
}
#endif

#ifndef CONFIG_HARDCODE_LD_PRELOAD_CONTENTS_FOR_EXECV
/** GET LD_PRELOAD_CONTENTS To pass to EXECV from environment********************
 ** Constructor called before main() 
 **/
static void __attribute__((constructor)) init(void)
{
  char *envvar;

/* SYMINIT dependency*/
#ifndef CONFIG_SEPARATE_SYMBOL_INIT_NEEDED 
  int i;
#endif

    DPRINTF("initing: %s\n", LIB_NAME);
    
    /* Get LD_PRELOAD value */
    envvar = getenv("LD_PRELOAD");
    if (envvar != NULL)
    {
        DPRINTF("%s: supplied LD_PRELOAD:%s\n", LIB_NAME, envvar);
        
        ld_preload_value_for_execv = strdup(envvar);
        
        if (ld_preload_value_for_execv == NULL)
        {
            DPRINTF( "%s: failed strdup, something went terribly wrong\n", LIB_NAME);
        }
    }
    else
    {
        DPRINTF( "%s: failed to getenv LD_PRELOAD, something went terribly wrong\n", LIB_NAME);
    }
    
#ifndef CONFIG_SEPARATE_SYMBOL_INIT_NEEDED
    SYMINIT;
#endif
}
#endif

#ifdef CONFIG_PROPAGATE_LD_PRELOAD_VIA_EXECV
/** execv handler *******************************************************************************************
 ** SYSINIT clears the environment, so we have to restore LD_PRELOAD to ensure we preload spawned processes
 ** Assumes processes spawned by execv() from NDS posix_spawn() implementation 
 */   
int execv(const char *path, char *const argv[])
{
    
#ifndef CONFIG_SEPARATE_SYMBOL_INIT_NEEDED    
  /* init symbol table */
  if (real_execv == NULL) dlinit();
#endif

  DPRINTF( "%s: execv\n", LIB_NAME);

  if (ld_preload_value_for_execv == NULL)
  {
      DPRINTF( "%s: LD_PRELOAD not set\n", LIB_NAME);
      /* carry on
      exit(1);
      */
  }
  else
  { //ld_preload_value_for_execv
      DPRINTF("%s: setting execv LD_PRELOAD set to:%s\n", LIB_NAME, ld_preload_value_for_execv);
      /* Restore LD_PRELOAD */
      if(setenv("LD_PRELOAD", ld_preload_value_for_execv, 0) != 0)
      {
          DPRINTF( "%s: failed to set LD_PRELOAD in the environment\n", LIB_NAME);
          /* carry on
          exit(1);
          */
      }
  }
  
  DPRINTF("%s: calling execv with \"%s\" arg: \"%s\", \"%s\" \n", LIB_NAME, path, argv[1], argv[2]);
  /* Call real execv */
  return real_execv(path, argv);
}
#endif

/** HANDLES resolv.conf modification, called before any resolving function ***********/
void handle_resolv_updates(void)
{
    FILE *fp;
    struct stat statbuf;

    pthread_mutex_lock(&time_stamp_mutex);
    
    if (stat("/etc/resolv.conf", &statbuf) < 0) 
    {
        if (stat("/etc/config/resolv.conf", &statbuf) < 0)
        {
            DPRINTF("failed to stat resolv.conf, something terrible has happened\n");

            /* WHAT do we do now ???, just leave*/            
            pthread_mutex_unlock(&time_stamp_mutex);
            return;
        }
    }
    
    if ((_resolvconf_stamp != statbuf.st_mtime ))
    {
      DPRINTF("%s: detected resolv.conf update\n",LIB_NAME);
      __res_init();
      _resolvconf_stamp = statbuf.st_mtime;
    }
    
    pthread_mutex_unlock(&time_stamp_mutex);
    
    return;
}

/*************************************************/
struct hostent * gethostbyaddr(const void *addr, socklen_t len, int type)
{
  DPRINTF( "%s: gethostbyaddr\n", LIB_NAME);
  
#ifndef CONFIG_SEPARATE_SYMBOL_INIT_NEEDED    
  /* init symbol table */
  if (real_gethostbyaddr == NULL) dlinit();
#endif

  handle_resolv_updates();
  return real_gethostbyaddr(addr, len, type);
}

/*************************************************/
struct hostent * gethostbyname(const char *name)
{
  DPRINTF( "%s: gethostbyname\n", LIB_NAME);
  
#ifndef CONFIG_SEPARATE_SYMBOL_INIT_NEEDED    
  /* init symbol table */
  if (real_gethostbyname == NULL) dlinit();
#endif

  handle_resolv_updates();
  return real_gethostbyname(name);
}

#ifdef CONFIG_GETNAMEINFO_PRELOADED_BY_GETHOSTBYADDR
/*************************************************/
int getnameinfo(const struct sockaddr * sa, socklen_t salen,
       char * node, socklen_t nodelen, char * service,
       socklen_t servicelen, unsigned int flags)
{
  DPRINTF( "%s: getnameinfo\n", LIB_NAME);
  
#ifndef CONFIG_SEPARATE_SYMBOL_INIT_NEEDED    
  /* init symbol table */
  if (real_getnameinfo == NULL) dlinit();
#endif
  
  handle_resolv_updates();
  return real_getnameinfo(sa, salen, node, nodelen, service, servicelen, flags);
}
#endif

/*************************************************/
int getaddrinfo(const char * nodename,
       const char * servname,
       const struct addrinfo * hints,
       struct addrinfo ** res)
{
  DPRINTF( "%s: getaddrinfo\n", LIB_NAME);
  
#ifndef CONFIG_SEPARATE_SYMBOL_INIT_NEEDED    
  /* init symbol table */
  if (real_getaddrinfo == NULL) dlinit();
#endif
  
  handle_resolv_updates();
  return real_getaddrinfo(nodename,servname,hints,res);
}

