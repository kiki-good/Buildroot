typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long int int64_t;
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long int uint64_t;
typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;
typedef long int int_least64_t;
typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long int uint_least64_t;
typedef signed char int_fast8_t;
typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
typedef unsigned char uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
typedef long int intptr_t;
typedef unsigned long int uintptr_t;
typedef long int intmax_t;
typedef unsigned long int uintmax_t;
typedef unsigned int __gwchar_t;

typedef struct
  {
    long int quot;
    long int rem;
  } imaxdiv_t;
extern intmax_t imaxabs (intmax_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern imaxdiv_t imaxdiv (intmax_t __numer, intmax_t __denom)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern intmax_t strtoimax (const char *__restrict __nptr,
      char **__restrict __endptr, int __base) __attribute__ ((__nothrow__ , __leaf__));
extern uintmax_t strtoumax (const char *__restrict __nptr,
       char ** __restrict __endptr, int __base) __attribute__ ((__nothrow__ , __leaf__));
extern intmax_t wcstoimax (const __gwchar_t *__restrict __nptr,
      __gwchar_t **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__));
extern uintmax_t wcstoumax (const __gwchar_t *__restrict __nptr,
       __gwchar_t ** __restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__));


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;
typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef int __daddr_t;
typedef int __key_t;
typedef int __clockid_t;
typedef void * __timer_t;
typedef int __blksize_t;
typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;
typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;
typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;
typedef long int __fsword_t;
typedef long int __ssize_t;
typedef long int __syscall_slong_t;
typedef unsigned long int __syscall_ulong_t;
typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;
typedef long int __intptr_t;
typedef unsigned int __socklen_t;
typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;
typedef __loff_t loff_t;
typedef __ino_t ino_t;
typedef __ino64_t ino64_t;
typedef __dev_t dev_t;
typedef __gid_t gid_t;
typedef __mode_t mode_t;
typedef __nlink_t nlink_t;
typedef __uid_t uid_t;
typedef __off_t off_t;
typedef __off64_t off64_t;
typedef __pid_t pid_t;
typedef __id_t id_t;
typedef __ssize_t ssize_t;
typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;
typedef __key_t key_t;

typedef __clock_t clock_t;



typedef __time_t time_t;


typedef __clockid_t clockid_t;
typedef __timer_t timer_t;
typedef __useconds_t useconds_t;
typedef __suseconds_t suseconds_t;
typedef long unsigned int size_t;
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
typedef unsigned int u_int8_t __attribute__ ((__mode__ (__QI__)));
typedef unsigned int u_int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int u_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int u_int64_t __attribute__ ((__mode__ (__DI__)));
typedef int register_t __attribute__ ((__mode__ (__word__)));
static __inline unsigned int
__bswap_32 (unsigned int __bsx)
{
  return __builtin_bswap32 (__bsx);
}
static __inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{
  return __builtin_bswap64 (__bsx);
}
typedef int __sig_atomic_t;
typedef struct
  {
    unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
  } __sigset_t;
typedef __sigset_t sigset_t;
struct timespec
  {
    __time_t tv_sec;
    __syscall_slong_t tv_nsec;
  };
struct timeval
  {
    __time_t tv_sec;
    __suseconds_t tv_usec;
  };
typedef long int __fd_mask;
typedef struct
  {
    __fd_mask fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];
  } fd_set;
typedef __fd_mask fd_mask;

extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);


__extension__
extern unsigned int gnu_dev_major (unsigned long long int __dev)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__
extern unsigned int gnu_dev_minor (unsigned long long int __dev)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__
extern unsigned long long int gnu_dev_makedev (unsigned int __major,
            unsigned int __minor)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));

typedef __blksize_t blksize_t;
typedef __blkcnt_t blkcnt_t;
typedef __fsblkcnt_t fsblkcnt_t;
typedef __fsfilcnt_t fsfilcnt_t;
typedef __blkcnt64_t blkcnt64_t;
typedef __fsblkcnt64_t fsblkcnt64_t;
typedef __fsfilcnt64_t fsfilcnt64_t;
typedef unsigned long int pthread_t;
union pthread_attr_t
{
  char __size[64];
  long int __align;
};
typedef union pthread_attr_t pthread_attr_t;
typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;
    unsigned int __nusers;
    int __kind;
    int __spins;
    __pthread_list_t __list;
  } __data;
  char __size[48];
  long int __align;
} pthread_mutex_t;
typedef union
{
  char __size[8];
  long int __align;
} pthread_mutexattr_t;
typedef union
{
  struct
  {
    int __lock;
    unsigned int __futex;
    __extension__ unsigned long long int __total_seq;
    __extension__ unsigned long long int __wakeup_seq;
    __extension__ unsigned long long int __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[48];
  long int __align;
} pthread_cond_t;
typedef union
{
  char __size[8];
  int __align;
} pthread_condattr_t;
typedef unsigned int pthread_key_t;
typedef int pthread_once_t;
typedef union
{
  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    int __writer;
    int __shared;
    unsigned long int __pad1;
    unsigned long int __pad2;
    unsigned int __flags;
  } __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;
typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;
typedef volatile int pthread_spinlock_t;
typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;
typedef union
{
  char __size[8];
  int __align;
} pthread_barrierattr_t;

typedef long int ptrdiff_t;
typedef unsigned int wchar_t;

typedef __socklen_t socklen_t;
extern int access (const char *__name, int __type) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int euidaccess (const char *__name, int __type)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int eaccess (const char *__name, int __type)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int faccessat (int __fd, const char *__file, int __type, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) ;
extern __off_t lseek (int __fd, __off_t __offset, int __whence) __attribute__ ((__nothrow__ , __leaf__));
extern __off64_t lseek64 (int __fd, __off64_t __offset, int __whence)
     __attribute__ ((__nothrow__ , __leaf__));
extern int close (int __fd);
extern ssize_t read (int __fd, void *__buf, size_t __nbytes) ;
extern ssize_t write (int __fd, const void *__buf, size_t __n) ;
extern ssize_t pread (int __fd, void *__buf, size_t __nbytes,
        __off_t __offset) ;
extern ssize_t pwrite (int __fd, const void *__buf, size_t __n,
         __off_t __offset) ;
extern ssize_t pread64 (int __fd, void *__buf, size_t __nbytes,
   __off64_t __offset) ;
extern ssize_t pwrite64 (int __fd, const void *__buf, size_t __n,
    __off64_t __offset) ;
extern int pipe (int __pipedes[2]) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int pipe2 (int __pipedes[2], int __flags) __attribute__ ((__nothrow__ , __leaf__)) ;
extern unsigned int alarm (unsigned int __seconds) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned int sleep (unsigned int __seconds);
extern __useconds_t ualarm (__useconds_t __value, __useconds_t __interval)
     __attribute__ ((__nothrow__ , __leaf__));
extern int usleep (__useconds_t __useconds);
extern int pause (void);
extern int chown (const char *__file, __uid_t __owner, __gid_t __group)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int fchown (int __fd, __uid_t __owner, __gid_t __group) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int lchown (const char *__file, __uid_t __owner, __gid_t __group)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int fchownat (int __fd, const char *__file, __uid_t __owner,
       __gid_t __group, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) ;
extern int chdir (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int fchdir (int __fd) __attribute__ ((__nothrow__ , __leaf__)) ;
extern char *getcwd (char *__buf, size_t __size) __attribute__ ((__nothrow__ , __leaf__)) ;
extern char *get_current_dir_name (void) __attribute__ ((__nothrow__ , __leaf__));
extern char *getwd (char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__)) ;
extern int dup (int __fd) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int dup2 (int __fd, int __fd2) __attribute__ ((__nothrow__ , __leaf__));
extern int dup3 (int __fd, int __fd2, int __flags) __attribute__ ((__nothrow__ , __leaf__));
extern char **__environ;
extern char **environ;
extern int execve (const char *__path, char *const __argv[],
     char *const __envp[]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int fexecve (int __fd, char *const __argv[], char *const __envp[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int execv (const char *__path, char *const __argv[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execle (const char *__path, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execl (const char *__path, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execvp (const char *__file, char *const __argv[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execlp (const char *__file, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execvpe (const char *__file, char *const __argv[],
      char *const __envp[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nice (int __inc) __attribute__ ((__nothrow__ , __leaf__)) ;
extern void _exit (int __status) __attribute__ ((__noreturn__));
enum
  {
    _PC_LINK_MAX,
    _PC_MAX_CANON,
    _PC_MAX_INPUT,
    _PC_NAME_MAX,
    _PC_PATH_MAX,
    _PC_PIPE_BUF,
    _PC_CHOWN_RESTRICTED,
    _PC_NO_TRUNC,
    _PC_VDISABLE,
    _PC_SYNC_IO,
    _PC_ASYNC_IO,
    _PC_PRIO_IO,
    _PC_SOCK_MAXBUF,
    _PC_FILESIZEBITS,
    _PC_REC_INCR_XFER_SIZE,
    _PC_REC_MAX_XFER_SIZE,
    _PC_REC_MIN_XFER_SIZE,
    _PC_REC_XFER_ALIGN,
    _PC_ALLOC_SIZE_MIN,
    _PC_SYMLINK_MAX,
    _PC_2_SYMLINKS
  };
enum
  {
    _SC_ARG_MAX,
    _SC_CHILD_MAX,
    _SC_CLK_TCK,
    _SC_NGROUPS_MAX,
    _SC_OPEN_MAX,
    _SC_STREAM_MAX,
    _SC_TZNAME_MAX,
    _SC_JOB_CONTROL,
    _SC_SAVED_IDS,
    _SC_REALTIME_SIGNALS,
    _SC_PRIORITY_SCHEDULING,
    _SC_TIMERS,
    _SC_ASYNCHRONOUS_IO,
    _SC_PRIORITIZED_IO,
    _SC_SYNCHRONIZED_IO,
    _SC_FSYNC,
    _SC_MAPPED_FILES,
    _SC_MEMLOCK,
    _SC_MEMLOCK_RANGE,
    _SC_MEMORY_PROTECTION,
    _SC_MESSAGE_PASSING,
    _SC_SEMAPHORES,
    _SC_SHARED_MEMORY_OBJECTS,
    _SC_AIO_LISTIO_MAX,
    _SC_AIO_MAX,
    _SC_AIO_PRIO_DELTA_MAX,
    _SC_DELAYTIMER_MAX,
    _SC_MQ_OPEN_MAX,
    _SC_MQ_PRIO_MAX,
    _SC_VERSION,
    _SC_PAGESIZE,
    _SC_RTSIG_MAX,
    _SC_SEM_NSEMS_MAX,
    _SC_SEM_VALUE_MAX,
    _SC_SIGQUEUE_MAX,
    _SC_TIMER_MAX,
    _SC_BC_BASE_MAX,
    _SC_BC_DIM_MAX,
    _SC_BC_SCALE_MAX,
    _SC_BC_STRING_MAX,
    _SC_COLL_WEIGHTS_MAX,
    _SC_EQUIV_CLASS_MAX,
    _SC_EXPR_NEST_MAX,
    _SC_LINE_MAX,
    _SC_RE_DUP_MAX,
    _SC_CHARCLASS_NAME_MAX,
    _SC_2_VERSION,
    _SC_2_C_BIND,
    _SC_2_C_DEV,
    _SC_2_FORT_DEV,
    _SC_2_FORT_RUN,
    _SC_2_SW_DEV,
    _SC_2_LOCALEDEF,
    _SC_PII,
    _SC_PII_XTI,
    _SC_PII_SOCKET,
    _SC_PII_INTERNET,
    _SC_PII_OSI,
    _SC_POLL,
    _SC_SELECT,
    _SC_UIO_MAXIOV,
    _SC_IOV_MAX = _SC_UIO_MAXIOV,
    _SC_PII_INTERNET_STREAM,
    _SC_PII_INTERNET_DGRAM,
    _SC_PII_OSI_COTS,
    _SC_PII_OSI_CLTS,
    _SC_PII_OSI_M,
    _SC_T_IOV_MAX,
    _SC_THREADS,
    _SC_THREAD_SAFE_FUNCTIONS,
    _SC_GETGR_R_SIZE_MAX,
    _SC_GETPW_R_SIZE_MAX,
    _SC_LOGIN_NAME_MAX,
    _SC_TTY_NAME_MAX,
    _SC_THREAD_DESTRUCTOR_ITERATIONS,
    _SC_THREAD_KEYS_MAX,
    _SC_THREAD_STACK_MIN,
    _SC_THREAD_THREADS_MAX,
    _SC_THREAD_ATTR_STACKADDR,
    _SC_THREAD_ATTR_STACKSIZE,
    _SC_THREAD_PRIORITY_SCHEDULING,
    _SC_THREAD_PRIO_INHERIT,
    _SC_THREAD_PRIO_PROTECT,
    _SC_THREAD_PROCESS_SHARED,
    _SC_NPROCESSORS_CONF,
    _SC_NPROCESSORS_ONLN,
    _SC_PHYS_PAGES,
    _SC_AVPHYS_PAGES,
    _SC_ATEXIT_MAX,
    _SC_PASS_MAX,
    _SC_XOPEN_VERSION,
    _SC_XOPEN_XCU_VERSION,
    _SC_XOPEN_UNIX,
    _SC_XOPEN_CRYPT,
    _SC_XOPEN_ENH_I18N,
    _SC_XOPEN_SHM,
    _SC_2_CHAR_TERM,
    _SC_2_C_VERSION,
    _SC_2_UPE,
    _SC_XOPEN_XPG2,
    _SC_XOPEN_XPG3,
    _SC_XOPEN_XPG4,
    _SC_CHAR_BIT,
    _SC_CHAR_MAX,
    _SC_CHAR_MIN,
    _SC_INT_MAX,
    _SC_INT_MIN,
    _SC_LONG_BIT,
    _SC_WORD_BIT,
    _SC_MB_LEN_MAX,
    _SC_NZERO,
    _SC_SSIZE_MAX,
    _SC_SCHAR_MAX,
    _SC_SCHAR_MIN,
    _SC_SHRT_MAX,
    _SC_SHRT_MIN,
    _SC_UCHAR_MAX,
    _SC_UINT_MAX,
    _SC_ULONG_MAX,
    _SC_USHRT_MAX,
    _SC_NL_ARGMAX,
    _SC_NL_LANGMAX,
    _SC_NL_MSGMAX,
    _SC_NL_NMAX,
    _SC_NL_SETMAX,
    _SC_NL_TEXTMAX,
    _SC_XBS5_ILP32_OFF32,
    _SC_XBS5_ILP32_OFFBIG,
    _SC_XBS5_LP64_OFF64,
    _SC_XBS5_LPBIG_OFFBIG,
    _SC_XOPEN_LEGACY,
    _SC_XOPEN_REALTIME,
    _SC_XOPEN_REALTIME_THREADS,
    _SC_ADVISORY_INFO,
    _SC_BARRIERS,
    _SC_BASE,
    _SC_C_LANG_SUPPORT,
    _SC_C_LANG_SUPPORT_R,
    _SC_CLOCK_SELECTION,
    _SC_CPUTIME,
    _SC_THREAD_CPUTIME,
    _SC_DEVICE_IO,
    _SC_DEVICE_SPECIFIC,
    _SC_DEVICE_SPECIFIC_R,
    _SC_FD_MGMT,
    _SC_FIFO,
    _SC_PIPE,
    _SC_FILE_ATTRIBUTES,
    _SC_FILE_LOCKING,
    _SC_FILE_SYSTEM,
    _SC_MONOTONIC_CLOCK,
    _SC_MULTI_PROCESS,
    _SC_SINGLE_PROCESS,
    _SC_NETWORKING,
    _SC_READER_WRITER_LOCKS,
    _SC_SPIN_LOCKS,
    _SC_REGEXP,
    _SC_REGEX_VERSION,
    _SC_SHELL,
    _SC_SIGNALS,
    _SC_SPAWN,
    _SC_SPORADIC_SERVER,
    _SC_THREAD_SPORADIC_SERVER,
    _SC_SYSTEM_DATABASE,
    _SC_SYSTEM_DATABASE_R,
    _SC_TIMEOUTS,
    _SC_TYPED_MEMORY_OBJECTS,
    _SC_USER_GROUPS,
    _SC_USER_GROUPS_R,
    _SC_2_PBS,
    _SC_2_PBS_ACCOUNTING,
    _SC_2_PBS_LOCATE,
    _SC_2_PBS_MESSAGE,
    _SC_2_PBS_TRACK,
    _SC_SYMLOOP_MAX,
    _SC_STREAMS,
    _SC_2_PBS_CHECKPOINT,
    _SC_V6_ILP32_OFF32,
    _SC_V6_ILP32_OFFBIG,
    _SC_V6_LP64_OFF64,
    _SC_V6_LPBIG_OFFBIG,
    _SC_HOST_NAME_MAX,
    _SC_TRACE,
    _SC_TRACE_EVENT_FILTER,
    _SC_TRACE_INHERIT,
    _SC_TRACE_LOG,
    _SC_LEVEL1_ICACHE_SIZE,
    _SC_LEVEL1_ICACHE_ASSOC,
    _SC_LEVEL1_ICACHE_LINESIZE,
    _SC_LEVEL1_DCACHE_SIZE,
    _SC_LEVEL1_DCACHE_ASSOC,
    _SC_LEVEL1_DCACHE_LINESIZE,
    _SC_LEVEL2_CACHE_SIZE,
    _SC_LEVEL2_CACHE_ASSOC,
    _SC_LEVEL2_CACHE_LINESIZE,
    _SC_LEVEL3_CACHE_SIZE,
    _SC_LEVEL3_CACHE_ASSOC,
    _SC_LEVEL3_CACHE_LINESIZE,
    _SC_LEVEL4_CACHE_SIZE,
    _SC_LEVEL4_CACHE_ASSOC,
    _SC_LEVEL4_CACHE_LINESIZE,
    _SC_IPV6 = _SC_LEVEL1_ICACHE_SIZE + 50,
    _SC_RAW_SOCKETS,
    _SC_V7_ILP32_OFF32,
    _SC_V7_ILP32_OFFBIG,
    _SC_V7_LP64_OFF64,
    _SC_V7_LPBIG_OFFBIG,
    _SC_SS_REPL_MAX,
    _SC_TRACE_EVENT_NAME_MAX,
    _SC_TRACE_NAME_MAX,
    _SC_TRACE_SYS_MAX,
    _SC_TRACE_USER_EVENT_MAX,
    _SC_XOPEN_STREAMS,
    _SC_THREAD_ROBUST_PRIO_INHERIT,
    _SC_THREAD_ROBUST_PRIO_PROTECT
  };
enum
  {
    _CS_PATH,
    _CS_V6_WIDTH_RESTRICTED_ENVS,
    _CS_GNU_LIBC_VERSION,
    _CS_GNU_LIBPTHREAD_VERSION,
    _CS_V5_WIDTH_RESTRICTED_ENVS,
    _CS_V7_WIDTH_RESTRICTED_ENVS,
    _CS_LFS_CFLAGS = 1000,
    _CS_LFS_LDFLAGS,
    _CS_LFS_LIBS,
    _CS_LFS_LINTFLAGS,
    _CS_LFS64_CFLAGS,
    _CS_LFS64_LDFLAGS,
    _CS_LFS64_LIBS,
    _CS_LFS64_LINTFLAGS,
    _CS_XBS5_ILP32_OFF32_CFLAGS = 1100,
    _CS_XBS5_ILP32_OFF32_LDFLAGS,
    _CS_XBS5_ILP32_OFF32_LIBS,
    _CS_XBS5_ILP32_OFF32_LINTFLAGS,
    _CS_XBS5_ILP32_OFFBIG_CFLAGS,
    _CS_XBS5_ILP32_OFFBIG_LDFLAGS,
    _CS_XBS5_ILP32_OFFBIG_LIBS,
    _CS_XBS5_ILP32_OFFBIG_LINTFLAGS,
    _CS_XBS5_LP64_OFF64_CFLAGS,
    _CS_XBS5_LP64_OFF64_LDFLAGS,
    _CS_XBS5_LP64_OFF64_LIBS,
    _CS_XBS5_LP64_OFF64_LINTFLAGS,
    _CS_XBS5_LPBIG_OFFBIG_CFLAGS,
    _CS_XBS5_LPBIG_OFFBIG_LDFLAGS,
    _CS_XBS5_LPBIG_OFFBIG_LIBS,
    _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,
    _CS_POSIX_V6_ILP32_OFF32_CFLAGS,
    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS,
    _CS_POSIX_V6_ILP32_OFF32_LIBS,
    _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_LIBS,
    _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS,
    _CS_POSIX_V6_LP64_OFF64_CFLAGS,
    _CS_POSIX_V6_LP64_OFF64_LDFLAGS,
    _CS_POSIX_V6_LP64_OFF64_LIBS,
    _CS_POSIX_V6_LP64_OFF64_LINTFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LIBS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS,
    _CS_POSIX_V7_ILP32_OFF32_CFLAGS,
    _CS_POSIX_V7_ILP32_OFF32_LDFLAGS,
    _CS_POSIX_V7_ILP32_OFF32_LIBS,
    _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS,
    _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS,
    _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS,
    _CS_POSIX_V7_ILP32_OFFBIG_LIBS,
    _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS,
    _CS_POSIX_V7_LP64_OFF64_CFLAGS,
    _CS_POSIX_V7_LP64_OFF64_LDFLAGS,
    _CS_POSIX_V7_LP64_OFF64_LIBS,
    _CS_POSIX_V7_LP64_OFF64_LINTFLAGS,
    _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS,
    _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS,
    _CS_POSIX_V7_LPBIG_OFFBIG_LIBS,
    _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS,
    _CS_V6_ENV,
    _CS_V7_ENV
  };
extern long int pathconf (const char *__path, int __name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long int fpathconf (int __fd, int __name) __attribute__ ((__nothrow__ , __leaf__));
extern long int sysconf (int __name) __attribute__ ((__nothrow__ , __leaf__));
extern size_t confstr (int __name, char *__buf, size_t __len) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getpid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getppid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getpgrp (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t __getpgid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getpgid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));
extern int setpgid (__pid_t __pid, __pid_t __pgid) __attribute__ ((__nothrow__ , __leaf__));
extern int setpgrp (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t setsid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getsid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));
extern __uid_t getuid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __uid_t geteuid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __gid_t getgid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __gid_t getegid (void) __attribute__ ((__nothrow__ , __leaf__));
extern int getgroups (int __size, __gid_t __list[]) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int group_member (__gid_t __gid) __attribute__ ((__nothrow__ , __leaf__));
extern int setuid (__uid_t __uid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setreuid (__uid_t __ruid, __uid_t __euid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int seteuid (__uid_t __uid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setgid (__gid_t __gid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setregid (__gid_t __rgid, __gid_t __egid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setegid (__gid_t __gid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int getresuid (__uid_t *__ruid, __uid_t *__euid, __uid_t *__suid)
     __attribute__ ((__nothrow__ , __leaf__));
extern int getresgid (__gid_t *__rgid, __gid_t *__egid, __gid_t *__sgid)
     __attribute__ ((__nothrow__ , __leaf__));
extern int setresuid (__uid_t __ruid, __uid_t __euid, __uid_t __suid)
     __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setresgid (__gid_t __rgid, __gid_t __egid, __gid_t __sgid)
     __attribute__ ((__nothrow__ , __leaf__)) ;
extern __pid_t fork (void) __attribute__ ((__nothrow__));
extern __pid_t vfork (void) __attribute__ ((__nothrow__ , __leaf__));
extern char *ttyname (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern int ttyname_r (int __fd, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) ;
extern int isatty (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern int ttyslot (void) __attribute__ ((__nothrow__ , __leaf__));
extern int link (const char *__from, const char *__to)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) ;
extern int linkat (int __fromfd, const char *__from, int __tofd,
     const char *__to, int __flags)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4))) ;
extern int symlink (const char *__from, const char *__to)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) ;
extern ssize_t readlink (const char *__restrict __path,
    char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) ;
extern int symlinkat (const char *__from, int __tofd,
        const char *__to) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3))) ;
extern ssize_t readlinkat (int __fd, const char *__restrict __path,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3))) ;
extern int unlink (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int unlinkat (int __fd, const char *__name, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int rmdir (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern __pid_t tcgetpgrp (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern int tcsetpgrp (int __fd, __pid_t __pgrp_id) __attribute__ ((__nothrow__ , __leaf__));
extern char *getlogin (void);
extern int getlogin_r (char *__name, size_t __name_len) __attribute__ ((__nonnull__ (1)));
extern int setlogin (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern char *optarg;
extern int optind;
extern int opterr;
extern int optopt;
extern int getopt (int ___argc, char *const *___argv, const char *__shortopts)
       __attribute__ ((__nothrow__ , __leaf__));
extern int gethostname (char *__name, size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int sethostname (const char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int sethostid (long int __id) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int getdomainname (char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int setdomainname (const char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int vhangup (void) __attribute__ ((__nothrow__ , __leaf__));
extern int revoke (const char *__file) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int profil (unsigned short int *__sample_buffer, size_t __size,
     size_t __offset, unsigned int __scale)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int acct (const char *__name) __attribute__ ((__nothrow__ , __leaf__));
extern char *getusershell (void) __attribute__ ((__nothrow__ , __leaf__));
extern void endusershell (void) __attribute__ ((__nothrow__ , __leaf__));
extern void setusershell (void) __attribute__ ((__nothrow__ , __leaf__));
extern int daemon (int __nochdir, int __noclose) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int chroot (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern char *getpass (const char *__prompt) __attribute__ ((__nonnull__ (1)));
extern int fsync (int __fd);
extern int syncfs (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern long int gethostid (void);
extern void sync (void) __attribute__ ((__nothrow__ , __leaf__));
extern int getpagesize (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int getdtablesize (void) __attribute__ ((__nothrow__ , __leaf__));
extern int truncate (const char *__file, __off_t __length)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int truncate64 (const char *__file, __off64_t __length)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int ftruncate (int __fd, __off_t __length) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ftruncate64 (int __fd, __off64_t __length) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int brk (void *__addr) __attribute__ ((__nothrow__ , __leaf__)) ;
extern void *sbrk (intptr_t __delta) __attribute__ ((__nothrow__ , __leaf__));
extern long int syscall (long int __sysno, ...) __attribute__ ((__nothrow__ , __leaf__));
extern int lockf (int __fd, int __cmd, __off_t __len) ;
extern int lockf64 (int __fd, int __cmd, __off64_t __len) ;
extern int fdatasync (int __fildes);
extern char *crypt (const char *__key, const char *__salt)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void encrypt (char *__libc_block, int __edflag) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void swab (const void *__restrict __from, void *__restrict __to,
    ssize_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


union wait
  {
    int w_status;
    struct
      {
 unsigned int __w_termsig:7;
 unsigned int __w_coredump:1;
 unsigned int __w_retcode:8;
 unsigned int:16;
      } __wait_terminated;
    struct
      {
 unsigned int __w_stopval:8;
 unsigned int __w_stopsig:8;
 unsigned int:16;
      } __wait_stopped;
  };
typedef union
  {
    union wait *__uptr;
    int *__iptr;
  } __WAIT_STATUS __attribute__ ((__transparent_union__));

typedef struct
  {
    int quot;
    int rem;
  } div_t;
typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;


__extension__ typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;

extern size_t __ctype_get_mb_cur_max (void) __attribute__ ((__nothrow__ , __leaf__)) ;

extern double atof (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
extern int atoi (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
extern long int atol (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;


__extension__ extern long long int atoll (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;


extern double strtod (const char *__restrict __nptr,
        char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern float strtof (const char *__restrict __nptr,
       char **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long double strtold (const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int strtol (const char *__restrict __nptr,
   char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern unsigned long int strtoul (const char *__restrict __nptr,
      char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern long long int strtoq (const char *__restrict __nptr,
        char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
__extension__
extern unsigned long long int strtouq (const char *__restrict __nptr,
           char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern long long int strtoll (const char *__restrict __nptr,
         char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
__extension__
extern unsigned long long int strtoull (const char *__restrict __nptr,
     char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

typedef struct __locale_struct
{
  struct __locale_data *__locales[13];
  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;
  const char *__names[13];
} *__locale_t;
typedef __locale_t locale_t;
extern long int strtol_l (const char *__restrict __nptr,
     char **__restrict __endptr, int __base,
     __locale_t __loc) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 4)));
extern unsigned long int strtoul_l (const char *__restrict __nptr,
        char **__restrict __endptr,
        int __base, __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 4)));
__extension__
extern long long int strtoll_l (const char *__restrict __nptr,
    char **__restrict __endptr, int __base,
    __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 4)));
__extension__
extern unsigned long long int strtoull_l (const char *__restrict __nptr,
       char **__restrict __endptr,
       int __base, __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 4)));
extern double strtod_l (const char *__restrict __nptr,
   char **__restrict __endptr, __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));
extern float strtof_l (const char *__restrict __nptr,
         char **__restrict __endptr, __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));
extern long double strtold_l (const char *__restrict __nptr,
         char **__restrict __endptr,
         __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));
extern char *l64a (long int __n) __attribute__ ((__nothrow__ , __leaf__)) ;
extern long int a64l (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
extern long int random (void) __attribute__ ((__nothrow__ , __leaf__));
extern void srandom (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));
extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern char *setstate (char *__statebuf) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };
extern int random_r (struct random_data *__restrict __buf,
       int32_t *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
   size_t __statelen,
   struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));
extern int setstate_r (char *__restrict __statebuf,
         struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int rand (void) __attribute__ ((__nothrow__ , __leaf__));
extern void srand (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));

extern int rand_r (unsigned int *__seed) __attribute__ ((__nothrow__ , __leaf__));
extern double drand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern double erand48 (unsigned short int __xsubi[3]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long int lrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int nrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long int mrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int jrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void srand48 (long int __seedval) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    __extension__ unsigned long long int __a;
  };
extern int drand48_r (struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int lrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int mrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;
extern void *calloc (size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;


extern void *realloc (void *__ptr, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));
extern void free (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));

extern void cfree (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));

extern void *alloca (size_t __size) __attribute__ ((__nothrow__ , __leaf__));

extern void *valloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;
extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern void *aligned_alloc (size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_size__ (2))) ;

extern void abort (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
extern int atexit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int at_quick_exit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern void exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
extern void quick_exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));


extern void _Exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));


extern char *getenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;

extern char *secure_getenv (const char *__name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int putenv (char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int setenv (const char *__name, const char *__value, int __replace)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int unsetenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int clearenv (void) __attribute__ ((__nothrow__ , __leaf__));
extern char *mktemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int mkstemp (char *__template) __attribute__ ((__nonnull__ (1))) ;
extern int mkstemp64 (char *__template) __attribute__ ((__nonnull__ (1))) ;
extern int mkstemps (char *__template, int __suffixlen) __attribute__ ((__nonnull__ (1))) ;
extern int mkstemps64 (char *__template, int __suffixlen)
     __attribute__ ((__nonnull__ (1))) ;
extern char *mkdtemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int mkostemp (char *__template, int __flags) __attribute__ ((__nonnull__ (1))) ;
extern int mkostemp64 (char *__template, int __flags) __attribute__ ((__nonnull__ (1))) ;
extern int mkostemps (char *__template, int __suffixlen, int __flags)
     __attribute__ ((__nonnull__ (1))) ;
extern int mkostemps64 (char *__template, int __suffixlen, int __flags)
     __attribute__ ((__nonnull__ (1))) ;

extern int system (const char *__command) ;

extern char *canonicalize_file_name (const char *__name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern char *realpath (const char *__restrict __name,
         char *__restrict __resolved) __attribute__ ((__nothrow__ , __leaf__)) ;
typedef int (*__compar_fn_t) (const void *, const void *);
typedef __compar_fn_t comparison_fn_t;
typedef int (*__compar_d_fn_t) (const void *, const void *, void *);

extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) ;
extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));
extern void qsort_r (void *__base, size_t __nmemb, size_t __size,
       __compar_d_fn_t __compar, void *__arg)
  __attribute__ ((__nonnull__ (1, 4)));
extern int abs (int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern long int labs (long int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;

__extension__ extern long long int llabs (long long int __x)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;

extern div_t div (int __numer, int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;


__extension__ extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;

extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *gcvt (double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;
extern char *qecvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qfcvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;
extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qecvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qfcvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));

extern int mblen (const char *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));
extern int mbtowc (wchar_t *__restrict __pwc,
     const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));
extern int wctomb (char *__s, wchar_t __wchar) __attribute__ ((__nothrow__ , __leaf__));
extern size_t mbstowcs (wchar_t *__restrict __pwcs,
   const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));
extern size_t wcstombs (char *__restrict __s,
   const wchar_t *__restrict __pwcs, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__));

extern int rpmatch (const char *__response) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int getsubopt (char **__restrict __optionp,
        char *const *__restrict __tokens,
        char **__restrict __valuep)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3))) ;
extern void setkey (const char *__key) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int posix_openpt (int __oflag) ;
extern int grantpt (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern int unlockpt (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern char *ptsname (int __fd) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ptsname_r (int __fd, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int getpt (void);
extern int getloadavg (double __loadavg[], int __nelem)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


struct _IO_FILE;

typedef struct _IO_FILE FILE;


typedef struct _IO_FILE __FILE;
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;
typedef struct
{
  __off_t __pos;
  __mbstate_t __state;
} _G_fpos_t;
typedef struct
{
  __off64_t __pos;
  __mbstate_t __state;
} _G_fpos64_t;
typedef __builtin_va_list __gnuc_va_list;
struct _IO_jump_t; struct _IO_FILE;
typedef void _IO_lock_t;
struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;
  int _pos;
};
enum __codecvt_result
{
  __codecvt_ok,
  __codecvt_partial,
  __codecvt_error,
  __codecvt_noconv
};
struct _IO_FILE {
  int _flags;
  char* _IO_read_ptr;
  char* _IO_read_end;
  char* _IO_read_base;
  char* _IO_write_base;
  char* _IO_write_ptr;
  char* _IO_write_end;
  char* _IO_buf_base;
  char* _IO_buf_end;
  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;
  struct _IO_marker *_markers;
  struct _IO_FILE *_chain;
  int _fileno;
  int _flags2;
  __off_t _old_offset;
  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];
  _IO_lock_t *_lock;
  __off64_t _offset;
  void *__pad1;
  void *__pad2;
  void *__pad3;
  void *__pad4;
  size_t __pad5;
  int _mode;
  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];
};
typedef struct _IO_FILE _IO_FILE;
struct _IO_FILE_plus;
extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
typedef __ssize_t __io_read_fn (void *__cookie, char *__buf, size_t __nbytes);
typedef __ssize_t __io_write_fn (void *__cookie, const char *__buf,
     size_t __n);
typedef int __io_seek_fn (void *__cookie, __off64_t *__pos, int __w);
typedef int __io_close_fn (void *__cookie);
typedef __io_read_fn cookie_read_function_t;
typedef __io_write_fn cookie_write_function_t;
typedef __io_seek_fn cookie_seek_function_t;
typedef __io_close_fn cookie_close_function_t;
typedef struct
{
  __io_read_fn *read;
  __io_write_fn *write;
  __io_seek_fn *seek;
  __io_close_fn *close;
} _IO_cookie_io_functions_t;
typedef _IO_cookie_io_functions_t cookie_io_functions_t;
struct _IO_cookie_file;
extern void _IO_cookie_init (struct _IO_cookie_file *__cfile, int __read_write,
        void *__cookie, _IO_cookie_io_functions_t __fns);
extern int __underflow (_IO_FILE *);
extern int __uflow (_IO_FILE *);
extern int __overflow (_IO_FILE *, int);
extern int _IO_getc (_IO_FILE *__fp);
extern int _IO_putc (int __c, _IO_FILE *__fp);
extern int _IO_feof (_IO_FILE *__fp) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_ferror (_IO_FILE *__fp) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_peekc_locked (_IO_FILE *__fp);
extern void _IO_flockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern void _IO_funlockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_ftrylockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_vfscanf (_IO_FILE * __restrict, const char * __restrict,
   __gnuc_va_list, int *__restrict);
extern int _IO_vfprintf (_IO_FILE *__restrict, const char *__restrict,
    __gnuc_va_list);
extern __ssize_t _IO_padn (_IO_FILE *, int, __ssize_t);
extern size_t _IO_sgetn (_IO_FILE *, void *, size_t);
extern __off64_t _IO_seekoff (_IO_FILE *, __off64_t, int, int);
extern __off64_t _IO_seekpos (_IO_FILE *, __off64_t, int);
extern void _IO_free_backup_area (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
typedef __gnuc_va_list va_list;

typedef _G_fpos_t fpos_t;

typedef _G_fpos64_t fpos64_t;
extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;

extern int remove (const char *__filename) __attribute__ ((__nothrow__ , __leaf__));
extern int rename (const char *__old, const char *__new) __attribute__ ((__nothrow__ , __leaf__));

extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) __attribute__ ((__nothrow__ , __leaf__));

extern FILE *tmpfile (void) ;
extern FILE *tmpfile64 (void) ;
extern char *tmpnam (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;

extern char *tmpnam_r (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;
extern char *tempnam (const char *__dir, const char *__pfx)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;

extern int fclose (FILE *__stream);
extern int fflush (FILE *__stream);

extern int fflush_unlocked (FILE *__stream);
extern int fcloseall (void);

extern FILE *fopen (const char *__restrict __filename,
      const char *__restrict __modes) ;
extern FILE *freopen (const char *__restrict __filename,
        const char *__restrict __modes,
        FILE *__restrict __stream) ;

extern FILE *fopen64 (const char *__restrict __filename,
        const char *__restrict __modes) ;
extern FILE *freopen64 (const char *__restrict __filename,
   const char *__restrict __modes,
   FILE *__restrict __stream) ;
extern FILE *fdopen (int __fd, const char *__modes) __attribute__ ((__nothrow__ , __leaf__)) ;
extern FILE *fopencookie (void *__restrict __magic_cookie,
     const char *__restrict __modes,
     _IO_cookie_io_functions_t __io_funcs) __attribute__ ((__nothrow__ , __leaf__)) ;
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __attribute__ ((__nothrow__ , __leaf__)) ;
extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__)) ;

extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));
extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ , __leaf__));

extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__ , __leaf__));
extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));

extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...);
extern int printf (const char *__restrict __format, ...);
extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__));
extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg);
extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);
extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));


extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));
extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));

extern int vasprintf (char **__restrict __ptr, const char *__restrict __f,
        __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 0))) ;
extern int __asprintf (char **__restrict __ptr,
         const char *__restrict __fmt, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3))) ;
extern int asprintf (char **__restrict __ptr,
       const char *__restrict __fmt, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3))) ;
extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));

extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) ;
extern int scanf (const char *__restrict __format, ...) ;
extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));


extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) ;
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 0)));


extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);
extern int getchar (void);

extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
extern int fgetc_unlocked (FILE *__stream);

extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);
extern int putchar (int __c);

extern int fputc_unlocked (int __c, FILE *__stream);
extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);
extern int getw (FILE *__stream);
extern int putw (int __w, FILE *__stream);

extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     ;

extern char *fgets_unlocked (char *__restrict __s, int __n,
        FILE *__restrict __stream) ;
extern __ssize_t __getdelim (char **__restrict __lineptr,
          size_t *__restrict __n, int __delimiter,
          FILE *__restrict __stream) ;
extern __ssize_t getdelim (char **__restrict __lineptr,
        size_t *__restrict __n, int __delimiter,
        FILE *__restrict __stream) ;
extern __ssize_t getline (char **__restrict __lineptr,
       size_t *__restrict __n,
       FILE *__restrict __stream) ;

extern int fputs (const char *__restrict __s, FILE *__restrict __stream);
extern int puts (const char *__s);
extern int ungetc (int __c, FILE *__stream);
extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s);

extern int fputs_unlocked (const char *__restrict __s,
      FILE *__restrict __stream);
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream);

extern int fseek (FILE *__stream, long int __off, int __whence);
extern long int ftell (FILE *__stream) ;
extern void rewind (FILE *__stream);

extern int fseeko (FILE *__stream, __off_t __off, int __whence);
extern __off_t ftello (FILE *__stream) ;

extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);
extern int fsetpos (FILE *__stream, const fpos_t *__pos);

extern int fseeko64 (FILE *__stream, __off64_t __off, int __whence);
extern __off64_t ftello64 (FILE *__stream) ;
extern int fgetpos64 (FILE *__restrict __stream, fpos64_t *__restrict __pos);
extern int fsetpos64 (FILE *__stream, const fpos64_t *__pos);

extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;

extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;

extern void perror (const char *__s);

extern int sys_nerr;
extern const char *const sys_errlist[];
extern int _sys_nerr;
extern const char *const _sys_errlist[];
extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern FILE *popen (const char *__command, const char *__modes) ;
extern int pclose (FILE *__stream);
extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__));
extern char *cuserid (char *__s);
struct obstack;
extern int obstack_printf (struct obstack *__restrict __obstack,
      const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3)));
extern int obstack_vprintf (struct obstack *__restrict __obstack,
       const char *__restrict __format,
       __gnuc_va_list __args)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 0)));
extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));



extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
       size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memmove (void *__dest, const void *__src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
        int __c, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern void *memset (void *__s, int __c, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern void *rawmemchr (const void *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern void *memrchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strcat (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strncat (char *__restrict __dest, const char *__restrict __src,
        size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strcmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strcoll (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern size_t strxfrm (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int strcoll_l (const char *__s1, const char *__s2, __locale_t __l)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));
extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    __locale_t __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));
extern char *strdup (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
extern char *strndup (const char *__string, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));

extern char *strchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern char *strrchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern char *strchrnul (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern size_t strcspn (const char *__s, const char *__reject)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern size_t strspn (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strpbrk (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strstr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strtok (char *__restrict __s, const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern char *__strtok_r (char *__restrict __s,
    const char *__restrict __delim,
    char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
extern char *strtok_r (char *__restrict __s, const char *__restrict __delim,
         char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
extern char *strcasestr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memmem (const void *__haystack, size_t __haystacklen,
       const void *__needle, size_t __needlelen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 3)));
extern void *__mempcpy (void *__restrict __dest,
   const void *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *mempcpy (void *__restrict __dest,
        const void *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern size_t strlen (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern size_t strnlen (const char *__string, size_t __maxlen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern char *strerror (int __errnum) __attribute__ ((__nothrow__ , __leaf__));

extern char *strerror_r (int __errnum, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) ;
extern char *strerror_l (int __errnum, __locale_t __l) __attribute__ ((__nothrow__ , __leaf__));
extern void __bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void bcopy (const void *__src, void *__dest, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *index (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern char *rindex (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern int ffs (int __i) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int ffsl (long int __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__ extern int ffsll (long long int __ll)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int strcasecmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strcasecmp_l (const char *__s1, const char *__s2,
    __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));
extern int strncasecmp_l (const char *__s1, const char *__s2,
     size_t __n, __locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 4)));
extern char *strsep (char **__restrict __stringp,
       const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strsignal (int __sig) __attribute__ ((__nothrow__ , __leaf__));
extern char *__stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *__stpncpy (char *__restrict __dest,
   const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strverscmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strfry (char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void *memfrob (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern char *basename (const char *__filename) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int *__errno_location (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern char *program_invocation_name, *program_invocation_short_name;

typedef int error_t;

struct timex
{
  unsigned int modes;
  __syscall_slong_t offset;
  __syscall_slong_t freq;
  __syscall_slong_t maxerror;
  __syscall_slong_t esterror;
  int status;
  __syscall_slong_t constant;
  __syscall_slong_t precision;
  __syscall_slong_t tolerance;
  struct timeval time;
  __syscall_slong_t tick;
  __syscall_slong_t ppsfreq;
  __syscall_slong_t jitter;
  int shift;
  __syscall_slong_t stabil;
  __syscall_slong_t jitcnt;
  __syscall_slong_t calcnt;
  __syscall_slong_t errcnt;
  __syscall_slong_t stbcnt;
  int tai;
  int :32; int :32; int :32; int :32;
  int :32; int :32; int :32; int :32;
  int :32; int :32; int :32;
};

extern int clock_adjtime (__clockid_t __clock_id, struct timex *__utx) __attribute__ ((__nothrow__ , __leaf__));


struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
  long int tm_gmtoff;
  const char *tm_zone;
};


struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  };
struct sigevent;

extern clock_t clock (void) __attribute__ ((__nothrow__ , __leaf__));
extern time_t time (time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));
extern double difftime (time_t __time1, time_t __time0)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern time_t mktime (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));
extern size_t strftime (char *__restrict __s, size_t __maxsize,
   const char *__restrict __format,
   const struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));

extern char *strptime (const char *__restrict __s,
         const char *__restrict __fmt, struct tm *__tp)
     __attribute__ ((__nothrow__ , __leaf__));
extern size_t strftime_l (char *__restrict __s, size_t __maxsize,
     const char *__restrict __format,
     const struct tm *__restrict __tp,
     __locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));
extern char *strptime_l (const char *__restrict __s,
    const char *__restrict __fmt, struct tm *__tp,
    __locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));

extern struct tm *gmtime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));
extern struct tm *localtime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));

extern struct tm *gmtime_r (const time_t *__restrict __timer,
       struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));
extern struct tm *localtime_r (const time_t *__restrict __timer,
          struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));

extern char *asctime (const struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));
extern char *ctime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));

extern char *asctime_r (const struct tm *__restrict __tp,
   char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));
extern char *ctime_r (const time_t *__restrict __timer,
        char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));
extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;
extern char *tzname[2];
extern void tzset (void) __attribute__ ((__nothrow__ , __leaf__));
extern int daylight;
extern long int timezone;
extern int stime (const time_t *__when) __attribute__ ((__nothrow__ , __leaf__));
extern time_t timegm (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));
extern time_t timelocal (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));
extern int dysize (int __year) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int nanosleep (const struct timespec *__requested_time,
        struct timespec *__remaining);
extern int clock_getres (clockid_t __clock_id, struct timespec *__res) __attribute__ ((__nothrow__ , __leaf__));
extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) __attribute__ ((__nothrow__ , __leaf__));
extern int clock_settime (clockid_t __clock_id, const struct timespec *__tp)
     __attribute__ ((__nothrow__ , __leaf__));
extern int clock_nanosleep (clockid_t __clock_id, int __flags,
       const struct timespec *__req,
       struct timespec *__rem);
extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) __attribute__ ((__nothrow__ , __leaf__));
extern int timer_create (clockid_t __clock_id,
    struct sigevent *__restrict __evp,
    timer_t *__restrict __timerid) __attribute__ ((__nothrow__ , __leaf__));
extern int timer_delete (timer_t __timerid) __attribute__ ((__nothrow__ , __leaf__));
extern int timer_settime (timer_t __timerid, int __flags,
     const struct itimerspec *__restrict __value,
     struct itimerspec *__restrict __ovalue) __attribute__ ((__nothrow__ , __leaf__));
extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     __attribute__ ((__nothrow__ , __leaf__));
extern int timer_getoverrun (timer_t __timerid) __attribute__ ((__nothrow__ , __leaf__));
extern int timespec_get (struct timespec *__ts, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int getdate_err;
extern struct tm *getdate (const char *__string);
extern int getdate_r (const char *__restrict __string,
        struct tm *__restrict __resbufp);


struct timezone
  {
    int tz_minuteswest;
    int tz_dsttime;
  };
typedef struct timezone *__restrict __timezone_ptr_t;
extern int gettimeofday (struct timeval *__restrict __tv,
    __timezone_ptr_t __tz) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int settimeofday (const struct timeval *__tv,
    const struct timezone *__tz)
     __attribute__ ((__nothrow__ , __leaf__));
extern int adjtime (const struct timeval *__delta,
      struct timeval *__olddelta) __attribute__ ((__nothrow__ , __leaf__));
enum __itimer_which
  {
    ITIMER_REAL = 0,
    ITIMER_VIRTUAL = 1,
    ITIMER_PROF = 2
  };
struct itimerval
  {
    struct timeval it_interval;
    struct timeval it_value;
  };
typedef enum __itimer_which __itimer_which_t;
extern int getitimer (__itimer_which_t __which,
        struct itimerval *__value) __attribute__ ((__nothrow__ , __leaf__));
extern int setitimer (__itimer_which_t __which,
        const struct itimerval *__restrict __new,
        struct itimerval *__restrict __old) __attribute__ ((__nothrow__ , __leaf__));
extern int utimes (const char *__file, const struct timeval __tvp[2])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int lutimes (const char *__file, const struct timeval __tvp[2])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int futimes (int __fd, const struct timeval __tvp[2]) __attribute__ ((__nothrow__ , __leaf__));
extern int futimesat (int __fd, const char *__file,
        const struct timeval __tvp[2]) __attribute__ ((__nothrow__ , __leaf__));



































































































































































































































































typedef struct sysent {
 unsigned nargs;
 int sys_flags;
 int sen;
 int (*sys_func)();
 const char *sys_name;
} struct_sysent;
typedef struct ioctlent {
 const char *symbol;
 unsigned int code;
} struct_ioctlent;
struct fault_opts {
 uint16_t first;
 uint16_t step;
 uint16_t err;
};
struct tcb {
 int flags;
 int pid;
 int qual_flg;
 unsigned long u_error;
 long scno;
 long u_arg[6];
 long u_rval;
 unsigned int currpers;
 int sys_func_rval;
 int curcol;
 FILE *outf;
 const char *auxstr;
 void *_priv_data;
 void (*_free_priv_data)(void *);
 const struct_sysent *s_ent;
 const struct_sysent *s_prev_ent;
 struct fault_opts *fault_vec[2];
 struct timeval stime;
 struct timeval dtime;
 struct timeval etime;
};
struct xlat {
 uint64_t val;
 const char *str;
};
extern const struct xlat addrfams[];
extern const struct xlat at_flags[];
extern const struct xlat dirent_types[];
extern const struct xlat evdev_abs[];
extern const struct xlat msg_flags[];
extern const struct xlat open_access_modes[];
extern const struct xlat open_mode_flags[];
extern const struct xlat resource_flags[];
extern const struct xlat socketlayers[];
extern const struct xlat whence_codes[];
enum sock_proto {
 SOCK_PROTO_UNKNOWN,
 SOCK_PROTO_UNIX,
 SOCK_PROTO_TCP,
 SOCK_PROTO_UDP,
 SOCK_PROTO_TCPv6,
 SOCK_PROTO_UDPv6,
 SOCK_PROTO_NETLINK
};
extern enum sock_proto get_proto_by_name(const char *);
enum iov_decode {
 IOV_DECODE_ADDR,
 IOV_DECODE_STR,
 IOV_DECODE_NETLINK
};
typedef enum {
 CFLAG_NONE = 0,
 CFLAG_ONLY_STATS,
 CFLAG_BOTH
} cflag_t;
extern cflag_t cflag;
extern _Bool debug_flag;
extern _Bool Tflag;
extern _Bool iflag;
extern _Bool count_wallclock;
extern unsigned int qflag;
extern _Bool not_failing_only;
extern unsigned int show_fd_path;
extern const char **paths_selected;
extern unsigned xflag;
extern unsigned followfork;
extern unsigned ptrace_setoptions;
extern unsigned max_strlen;
extern unsigned os_release;
void error_msg(const char *fmt, ...) __attribute__((__format__ (printf, 1, 2)));
void perror_msg(const char *fmt, ...) __attribute__((__format__ (printf, 1, 2)));
void error_msg_and_die(const char *fmt, ...)
 __attribute__((__format__ (printf, 1, 2))) __attribute__((__noreturn__));
void error_msg_and_help(const char *fmt, ...)
 __attribute__((__format__ (printf, 1, 2))) __attribute__((__noreturn__));
void perror_msg_and_die(const char *fmt, ...)
 __attribute__((__format__ (printf, 1, 2))) __attribute__((__noreturn__));
void die_out_of_memory(void) __attribute__((__noreturn__));
void *xmalloc(size_t size) __attribute__((__malloc__)) __attribute__((__alloc_size__ (1)));
void *xcalloc(size_t nmemb, size_t size)
 __attribute__((__malloc__)) __attribute__((__alloc_size__ (1, 2)));
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
 __attribute__((__alloc_size__ (2, 3)));
char *xstrdup(const char *str) __attribute__((__malloc__));
extern int read_int_from_file(const char *, int *);
extern void set_sortby(const char *);
extern void set_overhead(int);
extern void print_pc(struct tcb *);
extern int trace_syscall(struct tcb *);
extern void count_syscall(struct tcb *, const struct timeval *);
extern void call_summary(FILE *);
extern void clear_regs(void);
extern void get_regs(pid_t pid);
extern int get_scno(struct tcb *tcp);
extern const char *syscall_name(long scno);
extern const char *err_name(unsigned long err);
extern _Bool is_erestart(struct tcb *);
extern void temporarily_clear_syserror(struct tcb *);
extern void restore_cleared_syserror(struct tcb *);
extern void *get_tcb_priv_data(const struct tcb *);
extern int set_tcb_priv_data(struct tcb *, void *priv_data,
        void (*free_priv_data)(void *));
extern void free_tcb_priv_data(struct tcb *);
static inline unsigned long get_tcb_priv_ulong(const struct tcb *tcp)
{
 return (unsigned long) get_tcb_priv_data(tcp);
}
static inline int set_tcb_priv_ulong(struct tcb *tcp, unsigned long val)
{
 return set_tcb_priv_data(tcp, (void *) val, 0);
}
extern int umoven(struct tcb *, long, unsigned int, void *);
extern int umoven_or_printaddr(struct tcb *, long, unsigned int, void *);
extern int
umoven_or_printaddr_ignore_syserror(struct tcb *tcp, const long addr,
        const unsigned int len, void *our_addr);
extern int umovestr(struct tcb *, long, unsigned int, char *);
extern int upeek(int pid, long, long *);
extern int upoke(int pid, long, long);
extern _Bool
print_array(struct tcb *tcp,
     const unsigned long start_addr,
     const size_t nmemb,
     void *const elem_buf,
     const size_t elem_size,
     int (*const umoven_func)(struct tcb *,
         long,
         unsigned int,
         void *),
     _Bool (*const print_func)(struct tcb *,
         void *elem_buf,
         size_t elem_size,
         void *opaque_data),
     void *const opaque_data);
extern const char *signame(const int);
extern void pathtrace_select(const char *);
extern int pathtrace_match(struct tcb *);
extern int getfdpath(struct tcb *, int, char *, unsigned);
extern enum sock_proto getfdproto(struct tcb *, int);
extern const char *xlookup(const struct xlat *, const uint64_t);
extern const char *xlat_search(const struct xlat *, const size_t, const uint64_t);
extern unsigned long get_pagesize(void);
extern int
string_to_uint_ex(const char *str, char **endptr,
    unsigned int max_val, const char *accepted_ending);
extern int string_to_uint(const char *str);
static inline int
string_to_uint_upto(const char *const str, unsigned int max_val)
{
 return string_to_uint_ex(str, ((void *)0), max_val, ((void *)0));
}
extern int next_set_bit(const void *bit_array, unsigned cur_bit, unsigned size_bits);
extern int string_quote(const char *, char *, unsigned int, unsigned int);
extern int print_quoted_string(const char *, unsigned int, unsigned int);
extern int getllval(struct tcb *, unsigned long long *, int);
extern int printllval(struct tcb *, const char *, int)
 __attribute__((__format__ (printf, 2, 0)));
extern void printaddr_ull(unsigned long long);
extern int printxvals(const uint64_t, const char *, const struct xlat *, ...)
 __attribute__((__sentinel__));
extern int printxval_searchn(const struct xlat *xlat, size_t xlat_size,
 uint64_t val, const char *dflt);
extern long long getarg_ll(struct tcb *tcp, int argn);
extern unsigned long long getarg_ull(struct tcb *tcp, int argn);
extern int printargs(struct tcb *);
extern int printargs_u(struct tcb *);
extern int printargs_d(struct tcb *);
extern void addflags(const struct xlat *, uint64_t);
extern int printflags64(const struct xlat *, uint64_t, const char *);
extern const char *sprintflags(const char *, const struct xlat *, uint64_t);
extern const char *sprinttime(time_t);
extern void print_symbolic_mode_t(unsigned int);
extern void print_numeric_umode_t(unsigned short);
extern void print_numeric_long_umask(unsigned long);
extern void dumpiov_in_msghdr(struct tcb *, long, unsigned long);
extern void dumpiov_in_mmsghdr(struct tcb *, long);
extern void dumpiov_upto(struct tcb *, int, long, unsigned long);
extern void dumpstr(struct tcb *, long, int);
extern void printstr_ex(struct tcb *, long addr, long len,
 unsigned int user_style);
extern _Bool printnum_short(struct tcb *, long, const char *)
 __attribute__((__format__ (printf, 3, 0)));
extern _Bool printnum_int(struct tcb *, long, const char *)
 __attribute__((__format__ (printf, 3, 0)));
extern _Bool printnum_int64(struct tcb *, long, const char *)
 __attribute__((__format__ (printf, 3, 0)));
extern _Bool printnum_long_int(struct tcb *, long, const char *, const char *)
 __attribute__((__format__ (printf, 3, 0)))
 __attribute__((__format__ (printf, 4, 0)));
extern _Bool printpair_int(struct tcb *, long, const char *)
 __attribute__((__format__ (printf, 3, 0)));
extern _Bool printpair_int64(struct tcb *, long, const char *)
 __attribute__((__format__ (printf, 3, 0)));
extern void printpath(struct tcb *, long);
extern void printpathn(struct tcb *, long, unsigned int);
extern void printfd(struct tcb *, int);
extern void print_sockaddr(struct tcb *tcp, const void *, int);
extern _Bool print_sockaddr_by_inode(const unsigned long, const enum sock_proto);
extern _Bool print_sockaddr_by_inode_cached(const unsigned long);
extern void print_dirfd(struct tcb *, int);
extern int decode_sockaddr(struct tcb *, long, int);
extern void printuid(const char *, const unsigned int);
extern void print_sigset_addr_len(struct tcb *, long, long);
extern const char *sprintsigmask_n(const char *, const void *, unsigned int);
extern void printsignal(int);
extern void tprint_iov(struct tcb *, unsigned long, unsigned long, enum iov_decode);
extern void tprint_iov_upto(struct tcb *, unsigned long, unsigned long,
       enum iov_decode, unsigned long);
extern void decode_netlink(struct tcb *, unsigned long, unsigned long);
extern void tprint_open_modes(unsigned int);
extern const char *sprint_open_modes(unsigned int);
extern void print_seccomp_filter(struct tcb *, unsigned long);
extern void print_seccomp_fprog(struct tcb *, unsigned long, unsigned short);
struct strace_stat;
extern void print_struct_stat(struct tcb *tcp, const struct strace_stat *const st);
struct strace_statfs;
extern void print_struct_statfs(struct tcb *tcp, long);
extern void print_struct_statfs64(struct tcb *tcp, long, unsigned long);
extern void print_ifindex(unsigned int);
struct number_set;
extern struct number_set read_set;
extern struct number_set write_set;
extern struct number_set signal_set;
extern _Bool is_number_in_set(unsigned int number, const struct number_set *);
extern void qualify(const char *);
extern unsigned int qual_flags(const unsigned int);
extern int dm_ioctl(struct tcb *, const unsigned int, long);
extern int file_ioctl(struct tcb *, const unsigned int, long);
extern int fs_x_ioctl(struct tcb *, const unsigned int, long);
extern int loop_ioctl(struct tcb *, const unsigned int, long);
extern int ptp_ioctl(struct tcb *, const unsigned int, long);
extern int scsi_ioctl(struct tcb *, const unsigned int, long);
extern int sock_ioctl(struct tcb *, const unsigned int, long);
extern int term_ioctl(struct tcb *, const unsigned int, long);
extern int ubi_ioctl(struct tcb *, const unsigned int, long);
extern int uffdio_ioctl(struct tcb *, const unsigned int, long);
extern int tv_nz(const struct timeval *);
extern int tv_cmp(const struct timeval *, const struct timeval *);
extern double tv_float(const struct timeval *);
extern void tv_add(struct timeval *, const struct timeval *, const struct timeval *);
extern void tv_sub(struct timeval *, const struct timeval *, const struct timeval *);
extern void tv_mul(struct timeval *, const struct timeval *, int);
extern void tv_div(struct timeval *, const struct timeval *, int);
static inline void
printaddr(unsigned long addr)
{
 printaddr_ull(addr);
}
static inline void
printstr(struct tcb *tcp, long addr, long len)
{
 printstr_ex(tcp, addr, len, 0);
}
static inline int
printflags(const struct xlat *x, unsigned int flags, const char *dflt)
{
 return printflags64(x, flags, dflt);
}
static inline int
printflags_long(const struct xlat *x, unsigned long flags, const char *dflt)
{
 return printflags64(x, flags, dflt);
}
static inline int
printxval64(const struct xlat *x, const uint64_t val, const char *dflt)
{
 return printxvals(val, dflt, x, ((void *)0));
}
static inline int
printxval(const struct xlat *x, const unsigned int val, const char *dflt)
{
 return printxvals(val, dflt, x, ((void *)0));
}
static inline int
printxval_long(const struct xlat *x, const unsigned long val, const char *dflt)
{
 return printxvals(val, dflt, x, ((void *)0));
}
extern struct tcb *printing_tcp;
extern void printleader(struct tcb *);
extern void line_ended(void);
extern void tabto(void);
extern void tprintf(const char *fmt, ...) __attribute__((__format__ (printf, 1, 2)));
extern void tprints(const char *str);
extern void set_personality(int personality);
extern unsigned current_personality;
extern unsigned current_wordsize;
extern const struct_sysent sysent0[];
extern const char *const errnoent0[];
extern const char *const signalent0[];
extern const struct_ioctlent ioctlent0[];
extern const struct_sysent *sysent;
extern const char *const *errnoent;
extern const char *const *signalent;
extern const struct_ioctlent *ioctlent;
extern unsigned nsyscalls;
extern unsigned nerrnos;
extern unsigned nsignals;
extern unsigned nioctlents;
extern const unsigned int nsyscall_vec[2];
extern const struct_sysent *const sysent_vec[2];
extern struct fault_opts *fault_vec[2];
typedef __signed__ char __s8;
typedef unsigned char __u8;
typedef __signed__ short __s16;
typedef unsigned short __u16;
typedef __signed__ int __s32;
typedef unsigned int __u32;
__extension__ typedef __signed__ long long __s64;
__extension__ typedef unsigned long long __u64;
typedef struct {
 unsigned long fds_bits[1024 / (8 * sizeof(long))];
} __kernel_fd_set;
typedef void (*__kernel_sighandler_t)(int);
typedef int __kernel_key_t;
typedef int __kernel_mqd_t;
typedef long __kernel_long_t;
typedef unsigned long __kernel_ulong_t;
typedef __kernel_ulong_t __kernel_ino_t;
typedef unsigned int __kernel_mode_t;
typedef int __kernel_pid_t;
typedef int __kernel_ipc_pid_t;
typedef unsigned int __kernel_uid_t;
typedef unsigned int __kernel_gid_t;
typedef __kernel_long_t __kernel_suseconds_t;
typedef int __kernel_daddr_t;
typedef unsigned int __kernel_uid32_t;
typedef unsigned int __kernel_gid32_t;
typedef __kernel_uid_t __kernel_old_uid_t;
typedef __kernel_gid_t __kernel_old_gid_t;
typedef unsigned int __kernel_old_dev_t;
typedef __kernel_ulong_t __kernel_size_t;
typedef __kernel_long_t __kernel_ssize_t;
typedef __kernel_long_t __kernel_ptrdiff_t;
typedef struct {
 int val[2];
} __kernel_fsid_t;
typedef __kernel_long_t __kernel_off_t;
typedef long long __kernel_loff_t;
typedef __kernel_long_t __kernel_time_t;
typedef __kernel_long_t __kernel_clock_t;
typedef int __kernel_timer_t;
typedef int __kernel_clockid_t;
typedef char * __kernel_caddr_t;
typedef unsigned short __kernel_uid16_t;
typedef unsigned short __kernel_gid16_t;
typedef __u16 __le16;
typedef __u16 __be16;
typedef __u32 __le32;
typedef __u32 __be32;
typedef __u64 __le64;
typedef __u64 __be64;
typedef __u16 __sum16;
typedef __u32 __wsum;
enum v4l2_power_line_frequency {
 V4L2_CID_POWER_LINE_FREQUENCY_DISABLED = 0,
 V4L2_CID_POWER_LINE_FREQUENCY_50HZ = 1,
 V4L2_CID_POWER_LINE_FREQUENCY_60HZ = 2,
 V4L2_CID_POWER_LINE_FREQUENCY_AUTO = 3,
};
enum v4l2_colorfx {
 V4L2_COLORFX_NONE = 0,
 V4L2_COLORFX_BW = 1,
 V4L2_COLORFX_SEPIA = 2,
 V4L2_COLORFX_NEGATIVE = 3,
 V4L2_COLORFX_EMBOSS = 4,
 V4L2_COLORFX_SKETCH = 5,
 V4L2_COLORFX_SKY_BLUE = 6,
 V4L2_COLORFX_GRASS_GREEN = 7,
 V4L2_COLORFX_SKIN_WHITEN = 8,
 V4L2_COLORFX_VIVID = 9,
 V4L2_COLORFX_AQUA = 10,
 V4L2_COLORFX_ART_FREEZE = 11,
 V4L2_COLORFX_SILHOUETTE = 12,
 V4L2_COLORFX_SOLARIZATION = 13,
 V4L2_COLORFX_ANTIQUE = 14,
 V4L2_COLORFX_SET_CBCR = 15,
};
enum v4l2_mpeg_stream_type {
 V4L2_MPEG_STREAM_TYPE_MPEG2_PS = 0,
 V4L2_MPEG_STREAM_TYPE_MPEG2_TS = 1,
 V4L2_MPEG_STREAM_TYPE_MPEG1_SS = 2,
 V4L2_MPEG_STREAM_TYPE_MPEG2_DVD = 3,
 V4L2_MPEG_STREAM_TYPE_MPEG1_VCD = 4,
 V4L2_MPEG_STREAM_TYPE_MPEG2_SVCD = 5,
};
enum v4l2_mpeg_stream_vbi_fmt {
 V4L2_MPEG_STREAM_VBI_FMT_NONE = 0,
 V4L2_MPEG_STREAM_VBI_FMT_IVTV = 1,
};
enum v4l2_mpeg_audio_sampling_freq {
 V4L2_MPEG_AUDIO_SAMPLING_FREQ_44100 = 0,
 V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000 = 1,
 V4L2_MPEG_AUDIO_SAMPLING_FREQ_32000 = 2,
};
enum v4l2_mpeg_audio_encoding {
 V4L2_MPEG_AUDIO_ENCODING_LAYER_1 = 0,
 V4L2_MPEG_AUDIO_ENCODING_LAYER_2 = 1,
 V4L2_MPEG_AUDIO_ENCODING_LAYER_3 = 2,
 V4L2_MPEG_AUDIO_ENCODING_AAC = 3,
 V4L2_MPEG_AUDIO_ENCODING_AC3 = 4,
};
enum v4l2_mpeg_audio_l1_bitrate {
 V4L2_MPEG_AUDIO_L1_BITRATE_32K = 0,
 V4L2_MPEG_AUDIO_L1_BITRATE_64K = 1,
 V4L2_MPEG_AUDIO_L1_BITRATE_96K = 2,
 V4L2_MPEG_AUDIO_L1_BITRATE_128K = 3,
 V4L2_MPEG_AUDIO_L1_BITRATE_160K = 4,
 V4L2_MPEG_AUDIO_L1_BITRATE_192K = 5,
 V4L2_MPEG_AUDIO_L1_BITRATE_224K = 6,
 V4L2_MPEG_AUDIO_L1_BITRATE_256K = 7,
 V4L2_MPEG_AUDIO_L1_BITRATE_288K = 8,
 V4L2_MPEG_AUDIO_L1_BITRATE_320K = 9,
 V4L2_MPEG_AUDIO_L1_BITRATE_352K = 10,
 V4L2_MPEG_AUDIO_L1_BITRATE_384K = 11,
 V4L2_MPEG_AUDIO_L1_BITRATE_416K = 12,
 V4L2_MPEG_AUDIO_L1_BITRATE_448K = 13,
};
enum v4l2_mpeg_audio_l2_bitrate {
 V4L2_MPEG_AUDIO_L2_BITRATE_32K = 0,
 V4L2_MPEG_AUDIO_L2_BITRATE_48K = 1,
 V4L2_MPEG_AUDIO_L2_BITRATE_56K = 2,
 V4L2_MPEG_AUDIO_L2_BITRATE_64K = 3,
 V4L2_MPEG_AUDIO_L2_BITRATE_80K = 4,
 V4L2_MPEG_AUDIO_L2_BITRATE_96K = 5,
 V4L2_MPEG_AUDIO_L2_BITRATE_112K = 6,
 V4L2_MPEG_AUDIO_L2_BITRATE_128K = 7,
 V4L2_MPEG_AUDIO_L2_BITRATE_160K = 8,
 V4L2_MPEG_AUDIO_L2_BITRATE_192K = 9,
 V4L2_MPEG_AUDIO_L2_BITRATE_224K = 10,
 V4L2_MPEG_AUDIO_L2_BITRATE_256K = 11,
 V4L2_MPEG_AUDIO_L2_BITRATE_320K = 12,
 V4L2_MPEG_AUDIO_L2_BITRATE_384K = 13,
};
enum v4l2_mpeg_audio_l3_bitrate {
 V4L2_MPEG_AUDIO_L3_BITRATE_32K = 0,
 V4L2_MPEG_AUDIO_L3_BITRATE_40K = 1,
 V4L2_MPEG_AUDIO_L3_BITRATE_48K = 2,
 V4L2_MPEG_AUDIO_L3_BITRATE_56K = 3,
 V4L2_MPEG_AUDIO_L3_BITRATE_64K = 4,
 V4L2_MPEG_AUDIO_L3_BITRATE_80K = 5,
 V4L2_MPEG_AUDIO_L3_BITRATE_96K = 6,
 V4L2_MPEG_AUDIO_L3_BITRATE_112K = 7,
 V4L2_MPEG_AUDIO_L3_BITRATE_128K = 8,
 V4L2_MPEG_AUDIO_L3_BITRATE_160K = 9,
 V4L2_MPEG_AUDIO_L3_BITRATE_192K = 10,
 V4L2_MPEG_AUDIO_L3_BITRATE_224K = 11,
 V4L2_MPEG_AUDIO_L3_BITRATE_256K = 12,
 V4L2_MPEG_AUDIO_L3_BITRATE_320K = 13,
};
enum v4l2_mpeg_audio_mode {
 V4L2_MPEG_AUDIO_MODE_STEREO = 0,
 V4L2_MPEG_AUDIO_MODE_JOINT_STEREO = 1,
 V4L2_MPEG_AUDIO_MODE_DUAL = 2,
 V4L2_MPEG_AUDIO_MODE_MONO = 3,
};
enum v4l2_mpeg_audio_mode_extension {
 V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_4 = 0,
 V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_8 = 1,
 V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_12 = 2,
 V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_16 = 3,
};
enum v4l2_mpeg_audio_emphasis {
 V4L2_MPEG_AUDIO_EMPHASIS_NONE = 0,
 V4L2_MPEG_AUDIO_EMPHASIS_50_DIV_15_uS = 1,
 V4L2_MPEG_AUDIO_EMPHASIS_CCITT_J17 = 2,
};
enum v4l2_mpeg_audio_crc {
 V4L2_MPEG_AUDIO_CRC_NONE = 0,
 V4L2_MPEG_AUDIO_CRC_CRC16 = 1,
};
enum v4l2_mpeg_audio_ac3_bitrate {
 V4L2_MPEG_AUDIO_AC3_BITRATE_32K = 0,
 V4L2_MPEG_AUDIO_AC3_BITRATE_40K = 1,
 V4L2_MPEG_AUDIO_AC3_BITRATE_48K = 2,
 V4L2_MPEG_AUDIO_AC3_BITRATE_56K = 3,
 V4L2_MPEG_AUDIO_AC3_BITRATE_64K = 4,
 V4L2_MPEG_AUDIO_AC3_BITRATE_80K = 5,
 V4L2_MPEG_AUDIO_AC3_BITRATE_96K = 6,
 V4L2_MPEG_AUDIO_AC3_BITRATE_112K = 7,
 V4L2_MPEG_AUDIO_AC3_BITRATE_128K = 8,
 V4L2_MPEG_AUDIO_AC3_BITRATE_160K = 9,
 V4L2_MPEG_AUDIO_AC3_BITRATE_192K = 10,
 V4L2_MPEG_AUDIO_AC3_BITRATE_224K = 11,
 V4L2_MPEG_AUDIO_AC3_BITRATE_256K = 12,
 V4L2_MPEG_AUDIO_AC3_BITRATE_320K = 13,
 V4L2_MPEG_AUDIO_AC3_BITRATE_384K = 14,
 V4L2_MPEG_AUDIO_AC3_BITRATE_448K = 15,
 V4L2_MPEG_AUDIO_AC3_BITRATE_512K = 16,
 V4L2_MPEG_AUDIO_AC3_BITRATE_576K = 17,
 V4L2_MPEG_AUDIO_AC3_BITRATE_640K = 18,
};
enum v4l2_mpeg_audio_dec_playback {
 V4L2_MPEG_AUDIO_DEC_PLAYBACK_AUTO = 0,
 V4L2_MPEG_AUDIO_DEC_PLAYBACK_STEREO = 1,
 V4L2_MPEG_AUDIO_DEC_PLAYBACK_LEFT = 2,
 V4L2_MPEG_AUDIO_DEC_PLAYBACK_RIGHT = 3,
 V4L2_MPEG_AUDIO_DEC_PLAYBACK_MONO = 4,
 V4L2_MPEG_AUDIO_DEC_PLAYBACK_SWAPPED_STEREO = 5,
};
enum v4l2_mpeg_video_encoding {
 V4L2_MPEG_VIDEO_ENCODING_MPEG_1 = 0,
 V4L2_MPEG_VIDEO_ENCODING_MPEG_2 = 1,
 V4L2_MPEG_VIDEO_ENCODING_MPEG_4_AVC = 2,
};
enum v4l2_mpeg_video_aspect {
 V4L2_MPEG_VIDEO_ASPECT_1x1 = 0,
 V4L2_MPEG_VIDEO_ASPECT_4x3 = 1,
 V4L2_MPEG_VIDEO_ASPECT_16x9 = 2,
 V4L2_MPEG_VIDEO_ASPECT_221x100 = 3,
};
enum v4l2_mpeg_video_bitrate_mode {
 V4L2_MPEG_VIDEO_BITRATE_MODE_VBR = 0,
 V4L2_MPEG_VIDEO_BITRATE_MODE_CBR = 1,
};
enum v4l2_mpeg_video_header_mode {
 V4L2_MPEG_VIDEO_HEADER_MODE_SEPARATE = 0,
 V4L2_MPEG_VIDEO_HEADER_MODE_JOINED_WITH_1ST_FRAME = 1,
};
enum v4l2_mpeg_video_multi_slice_mode {
 V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_SINGLE = 0,
 V4L2_MPEG_VIDEO_MULTI_SICE_MODE_MAX_MB = 1,
 V4L2_MPEG_VIDEO_MULTI_SICE_MODE_MAX_BYTES = 2,
};
enum v4l2_mpeg_video_h264_entropy_mode {
 V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CAVLC = 0,
 V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CABAC = 1,
};
enum v4l2_mpeg_video_h264_level {
 V4L2_MPEG_VIDEO_H264_LEVEL_1_0 = 0,
 V4L2_MPEG_VIDEO_H264_LEVEL_1B = 1,
 V4L2_MPEG_VIDEO_H264_LEVEL_1_1 = 2,
 V4L2_MPEG_VIDEO_H264_LEVEL_1_2 = 3,
 V4L2_MPEG_VIDEO_H264_LEVEL_1_3 = 4,
 V4L2_MPEG_VIDEO_H264_LEVEL_2_0 = 5,
 V4L2_MPEG_VIDEO_H264_LEVEL_2_1 = 6,
 V4L2_MPEG_VIDEO_H264_LEVEL_2_2 = 7,
 V4L2_MPEG_VIDEO_H264_LEVEL_3_0 = 8,
 V4L2_MPEG_VIDEO_H264_LEVEL_3_1 = 9,
 V4L2_MPEG_VIDEO_H264_LEVEL_3_2 = 10,
 V4L2_MPEG_VIDEO_H264_LEVEL_4_0 = 11,
 V4L2_MPEG_VIDEO_H264_LEVEL_4_1 = 12,
 V4L2_MPEG_VIDEO_H264_LEVEL_4_2 = 13,
 V4L2_MPEG_VIDEO_H264_LEVEL_5_0 = 14,
 V4L2_MPEG_VIDEO_H264_LEVEL_5_1 = 15,
};
enum v4l2_mpeg_video_h264_loop_filter_mode {
 V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_ENABLED = 0,
 V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_DISABLED = 1,
 V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_DISABLED_AT_SLICE_BOUNDARY = 2,
};
enum v4l2_mpeg_video_h264_profile {
 V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE = 0,
 V4L2_MPEG_VIDEO_H264_PROFILE_CONSTRAINED_BASELINE = 1,
 V4L2_MPEG_VIDEO_H264_PROFILE_MAIN = 2,
 V4L2_MPEG_VIDEO_H264_PROFILE_EXTENDED = 3,
 V4L2_MPEG_VIDEO_H264_PROFILE_HIGH = 4,
 V4L2_MPEG_VIDEO_H264_PROFILE_HIGH_10 = 5,
 V4L2_MPEG_VIDEO_H264_PROFILE_HIGH_422 = 6,
 V4L2_MPEG_VIDEO_H264_PROFILE_HIGH_444_PREDICTIVE = 7,
 V4L2_MPEG_VIDEO_H264_PROFILE_HIGH_10_INTRA = 8,
 V4L2_MPEG_VIDEO_H264_PROFILE_HIGH_422_INTRA = 9,
 V4L2_MPEG_VIDEO_H264_PROFILE_HIGH_444_INTRA = 10,
 V4L2_MPEG_VIDEO_H264_PROFILE_CAVLC_444_INTRA = 11,
 V4L2_MPEG_VIDEO_H264_PROFILE_SCALABLE_BASELINE = 12,
 V4L2_MPEG_VIDEO_H264_PROFILE_SCALABLE_HIGH = 13,
 V4L2_MPEG_VIDEO_H264_PROFILE_SCALABLE_HIGH_INTRA = 14,
 V4L2_MPEG_VIDEO_H264_PROFILE_STEREO_HIGH = 15,
 V4L2_MPEG_VIDEO_H264_PROFILE_MULTIVIEW_HIGH = 16,
};
enum v4l2_mpeg_video_h264_vui_sar_idc {
 V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_UNSPECIFIED = 0,
 V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_1x1 = 1,
 V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_12x11 = 2,
 V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_10x11 = 3,
 V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_16x11 = 4,
 V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_40x33 = 5,
 V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_24x11 = 6,
 V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_20x11 = 7,
 V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_32x11 = 8,
 V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_80x33 = 9,
 V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_18x11 = 10,
 V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_15x11 = 11,
 V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_64x33 = 12,
 V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_160x99 = 13,
 V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_4x3 = 14,
 V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_3x2 = 15,
 V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_2x1 = 16,
 V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_EXTENDED = 17,
};
enum v4l2_mpeg_video_h264_sei_fp_arrangement_type {
 V4L2_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE_CHECKERBOARD = 0,
 V4L2_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE_COLUMN = 1,
 V4L2_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE_ROW = 2,
 V4L2_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE_SIDE_BY_SIDE = 3,
 V4L2_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE_TOP_BOTTOM = 4,
 V4L2_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE_TEMPORAL = 5,
};
enum v4l2_mpeg_video_h264_fmo_map_type {
 V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_INTERLEAVED_SLICES = 0,
 V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_SCATTERED_SLICES = 1,
 V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_FOREGROUND_WITH_LEFT_OVER = 2,
 V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_BOX_OUT = 3,
 V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_RASTER_SCAN = 4,
 V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_WIPE_SCAN = 5,
 V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_EXPLICIT = 6,
};
enum v4l2_mpeg_video_h264_fmo_change_dir {
 V4L2_MPEG_VIDEO_H264_FMO_CHANGE_DIR_RIGHT = 0,
 V4L2_MPEG_VIDEO_H264_FMO_CHANGE_DIR_LEFT = 1,
};
enum v4l2_mpeg_video_h264_hierarchical_coding_type {
 V4L2_MPEG_VIDEO_H264_HIERARCHICAL_CODING_B = 0,
 V4L2_MPEG_VIDEO_H264_HIERARCHICAL_CODING_P = 1,
};
enum v4l2_mpeg_video_mpeg4_level {
 V4L2_MPEG_VIDEO_MPEG4_LEVEL_0 = 0,
 V4L2_MPEG_VIDEO_MPEG4_LEVEL_0B = 1,
 V4L2_MPEG_VIDEO_MPEG4_LEVEL_1 = 2,
 V4L2_MPEG_VIDEO_MPEG4_LEVEL_2 = 3,
 V4L2_MPEG_VIDEO_MPEG4_LEVEL_3 = 4,
 V4L2_MPEG_VIDEO_MPEG4_LEVEL_3B = 5,
 V4L2_MPEG_VIDEO_MPEG4_LEVEL_4 = 6,
 V4L2_MPEG_VIDEO_MPEG4_LEVEL_5 = 7,
};
enum v4l2_mpeg_video_mpeg4_profile {
 V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE = 0,
 V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_SIMPLE = 1,
 V4L2_MPEG_VIDEO_MPEG4_PROFILE_CORE = 2,
 V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE_SCALABLE = 3,
 V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_CODING_EFFICIENCY = 4,
};
enum v4l2_mpeg_cx2341x_video_spatial_filter_mode {
 V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_MANUAL = 0,
 V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_AUTO = 1,
};
enum v4l2_mpeg_cx2341x_video_luma_spatial_filter_type {
 V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_OFF = 0,
 V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_1D_HOR = 1,
 V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_1D_VERT = 2,
 V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_2D_HV_SEPARABLE = 3,
 V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_2D_SYM_NON_SEPARABLE = 4,
};
enum v4l2_mpeg_cx2341x_video_chroma_spatial_filter_type {
 V4L2_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE_OFF = 0,
 V4L2_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE_1D_HOR = 1,
};
enum v4l2_mpeg_cx2341x_video_temporal_filter_mode {
 V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_MANUAL = 0,
 V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_AUTO = 1,
};
enum v4l2_mpeg_cx2341x_video_median_filter_type {
 V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF = 0,
 V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_HOR = 1,
 V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_VERT = 2,
 V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_HOR_VERT = 3,
 V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_DIAG = 4,
};
enum v4l2_mpeg_mfc51_video_frame_skip_mode {
 V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_DISABLED = 0,
 V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_LEVEL_LIMIT = 1,
 V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT = 2,
};
enum v4l2_mpeg_mfc51_video_force_frame_type {
 V4L2_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE_DISABLED = 0,
 V4L2_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE_I_FRAME = 1,
 V4L2_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE_NOT_CODED = 2,
};
enum v4l2_exposure_auto_type {
 V4L2_EXPOSURE_AUTO = 0,
 V4L2_EXPOSURE_MANUAL = 1,
 V4L2_EXPOSURE_SHUTTER_PRIORITY = 2,
 V4L2_EXPOSURE_APERTURE_PRIORITY = 3
};
enum v4l2_auto_n_preset_white_balance {
 V4L2_WHITE_BALANCE_MANUAL = 0,
 V4L2_WHITE_BALANCE_AUTO = 1,
 V4L2_WHITE_BALANCE_INCANDESCENT = 2,
 V4L2_WHITE_BALANCE_FLUORESCENT = 3,
 V4L2_WHITE_BALANCE_FLUORESCENT_H = 4,
 V4L2_WHITE_BALANCE_HORIZON = 5,
 V4L2_WHITE_BALANCE_DAYLIGHT = 6,
 V4L2_WHITE_BALANCE_FLASH = 7,
 V4L2_WHITE_BALANCE_CLOUDY = 8,
 V4L2_WHITE_BALANCE_SHADE = 9,
};
enum v4l2_iso_sensitivity_auto_type {
 V4L2_ISO_SENSITIVITY_MANUAL = 0,
 V4L2_ISO_SENSITIVITY_AUTO = 1,
};
enum v4l2_exposure_metering {
 V4L2_EXPOSURE_METERING_AVERAGE = 0,
 V4L2_EXPOSURE_METERING_CENTER_WEIGHTED = 1,
 V4L2_EXPOSURE_METERING_SPOT = 2,
};
enum v4l2_scene_mode {
 V4L2_SCENE_MODE_NONE = 0,
 V4L2_SCENE_MODE_BACKLIGHT = 1,
 V4L2_SCENE_MODE_BEACH_SNOW = 2,
 V4L2_SCENE_MODE_CANDLE_LIGHT = 3,
 V4L2_SCENE_MODE_DAWN_DUSK = 4,
 V4L2_SCENE_MODE_FALL_COLORS = 5,
 V4L2_SCENE_MODE_FIREWORKS = 6,
 V4L2_SCENE_MODE_LANDSCAPE = 7,
 V4L2_SCENE_MODE_NIGHT = 8,
 V4L2_SCENE_MODE_PARTY_INDOOR = 9,
 V4L2_SCENE_MODE_PORTRAIT = 10,
 V4L2_SCENE_MODE_SPORTS = 11,
 V4L2_SCENE_MODE_SUNSET = 12,
 V4L2_SCENE_MODE_TEXT = 13,
};
enum v4l2_auto_focus_range {
 V4L2_AUTO_FOCUS_RANGE_AUTO = 0,
 V4L2_AUTO_FOCUS_RANGE_NORMAL = 1,
 V4L2_AUTO_FOCUS_RANGE_MACRO = 2,
 V4L2_AUTO_FOCUS_RANGE_INFINITY = 3,
};
enum v4l2_preemphasis {
 V4L2_PREEMPHASIS_DISABLED = 0,
 V4L2_PREEMPHASIS_50_uS = 1,
 V4L2_PREEMPHASIS_75_uS = 2,
};
enum v4l2_flash_led_mode {
 V4L2_FLASH_LED_MODE_NONE,
 V4L2_FLASH_LED_MODE_FLASH,
 V4L2_FLASH_LED_MODE_TORCH,
};
enum v4l2_flash_strobe_source {
 V4L2_FLASH_STROBE_SOURCE_SOFTWARE,
 V4L2_FLASH_STROBE_SOURCE_EXTERNAL,
};
enum v4l2_jpeg_chroma_subsampling {
 V4L2_JPEG_CHROMA_SUBSAMPLING_444 = 0,
 V4L2_JPEG_CHROMA_SUBSAMPLING_422 = 1,
 V4L2_JPEG_CHROMA_SUBSAMPLING_420 = 2,
 V4L2_JPEG_CHROMA_SUBSAMPLING_411 = 3,
 V4L2_JPEG_CHROMA_SUBSAMPLING_410 = 4,
 V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY = 5,
};
enum v4l2_field {
 V4L2_FIELD_ANY = 0,
 V4L2_FIELD_NONE = 1,
 V4L2_FIELD_TOP = 2,
 V4L2_FIELD_BOTTOM = 3,
 V4L2_FIELD_INTERLACED = 4,
 V4L2_FIELD_SEQ_TB = 5,
 V4L2_FIELD_SEQ_BT = 6,
 V4L2_FIELD_ALTERNATE = 7,
 V4L2_FIELD_INTERLACED_TB = 8,
 V4L2_FIELD_INTERLACED_BT = 9,
};
enum v4l2_buf_type {
 V4L2_BUF_TYPE_VIDEO_CAPTURE = 1,
 V4L2_BUF_TYPE_VIDEO_OUTPUT = 2,
 V4L2_BUF_TYPE_VIDEO_OVERLAY = 3,
 V4L2_BUF_TYPE_VBI_CAPTURE = 4,
 V4L2_BUF_TYPE_VBI_OUTPUT = 5,
 V4L2_BUF_TYPE_SLICED_VBI_CAPTURE = 6,
 V4L2_BUF_TYPE_SLICED_VBI_OUTPUT = 7,
 V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY = 8,
 V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE = 9,
 V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE = 10,
 V4L2_BUF_TYPE_PRIVATE = 0x80,
};
enum v4l2_tuner_type {
 V4L2_TUNER_RADIO = 1,
 V4L2_TUNER_ANALOG_TV = 2,
 V4L2_TUNER_DIGITAL_TV = 3,
};
enum v4l2_memory {
 V4L2_MEMORY_MMAP = 1,
 V4L2_MEMORY_USERPTR = 2,
 V4L2_MEMORY_OVERLAY = 3,
 V4L2_MEMORY_DMABUF = 4,
};
enum v4l2_colorspace {
 V4L2_COLORSPACE_SMPTE170M = 1,
 V4L2_COLORSPACE_SMPTE240M = 2,
 V4L2_COLORSPACE_REC709 = 3,
 V4L2_COLORSPACE_BT878 = 4,
 V4L2_COLORSPACE_470_SYSTEM_M = 5,
 V4L2_COLORSPACE_470_SYSTEM_BG = 6,
 V4L2_COLORSPACE_JPEG = 7,
 V4L2_COLORSPACE_SRGB = 8,
};
enum v4l2_priority {
 V4L2_PRIORITY_UNSET = 0,
 V4L2_PRIORITY_BACKGROUND = 1,
 V4L2_PRIORITY_INTERACTIVE = 2,
 V4L2_PRIORITY_RECORD = 3,
 V4L2_PRIORITY_DEFAULT = V4L2_PRIORITY_INTERACTIVE,
};
struct v4l2_rect {
 __s32 left;
 __s32 top;
 __s32 width;
 __s32 height;
};
struct v4l2_fract {
 __u32 numerator;
 __u32 denominator;
};
struct v4l2_capability {
 __u8 driver[16];
 __u8 card[32];
 __u8 bus_info[32];
 __u32 version;
 __u32 capabilities;
 __u32 device_caps;
 __u32 reserved[3];
};
struct v4l2_pix_format {
 __u32 width;
 __u32 height;
 __u32 pixelformat;
 __u32 field;
 __u32 bytesperline;
 __u32 sizeimage;
 __u32 colorspace;
 __u32 priv;
};
struct v4l2_fmtdesc {
 __u32 index;
 __u32 type;
 __u32 flags;
 __u8 description[32];
 __u32 pixelformat;
 __u32 reserved[4];
};
enum v4l2_frmsizetypes {
 V4L2_FRMSIZE_TYPE_DISCRETE = 1,
 V4L2_FRMSIZE_TYPE_CONTINUOUS = 2,
 V4L2_FRMSIZE_TYPE_STEPWISE = 3,
};
struct v4l2_frmsize_discrete {
 __u32 width;
 __u32 height;
};
struct v4l2_frmsize_stepwise {
 __u32 min_width;
 __u32 max_width;
 __u32 step_width;
 __u32 min_height;
 __u32 max_height;
 __u32 step_height;
};
struct v4l2_frmsizeenum {
 __u32 index;
 __u32 pixel_format;
 __u32 type;
 union {
  struct v4l2_frmsize_discrete discrete;
  struct v4l2_frmsize_stepwise stepwise;
 };
 __u32 reserved[2];
};
enum v4l2_frmivaltypes {
 V4L2_FRMIVAL_TYPE_DISCRETE = 1,
 V4L2_FRMIVAL_TYPE_CONTINUOUS = 2,
 V4L2_FRMIVAL_TYPE_STEPWISE = 3,
};
struct v4l2_frmival_stepwise {
 struct v4l2_fract min;
 struct v4l2_fract max;
 struct v4l2_fract step;
};
struct v4l2_frmivalenum {
 __u32 index;
 __u32 pixel_format;
 __u32 width;
 __u32 height;
 __u32 type;
 union {
  struct v4l2_fract discrete;
  struct v4l2_frmival_stepwise stepwise;
 };
 __u32 reserved[2];
};
struct v4l2_timecode {
 __u32 type;
 __u32 flags;
 __u8 frames;
 __u8 seconds;
 __u8 minutes;
 __u8 hours;
 __u8 userbits[4];
};
struct v4l2_jpegcompression {
 int quality;
 int APPn;
 int APP_len;
 char APP_data[60];
 int COM_len;
 char COM_data[60];
 __u32 jpeg_markers;
};
struct v4l2_requestbuffers {
 __u32 count;
 __u32 type;
 __u32 memory;
 __u32 reserved[2];
};
struct v4l2_plane {
 __u32 bytesused;
 __u32 length;
 union {
  __u32 mem_offset;
  unsigned long userptr;
  __s32 fd;
 } m;
 __u32 data_offset;
 __u32 reserved[11];
};
struct v4l2_buffer {
 __u32 index;
 __u32 type;
 __u32 bytesused;
 __u32 flags;
 __u32 field;
 struct timeval timestamp;
 struct v4l2_timecode timecode;
 __u32 sequence;
 __u32 memory;
 union {
  __u32 offset;
  unsigned long userptr;
  struct v4l2_plane *planes;
  __s32 fd;
 } m;
 __u32 length;
 __u32 reserved2;
 __u32 reserved;
};
struct v4l2_exportbuffer {
 __u32 type;
 __u32 index;
 __u32 plane;
 __u32 flags;
 __s32 fd;
 __u32 reserved[11];
};
struct v4l2_framebuffer {
 __u32 capability;
 __u32 flags;
 void *base;
 struct v4l2_pix_format fmt;
};
struct v4l2_clip {
 struct v4l2_rect c;
 struct v4l2_clip *next;
};
struct v4l2_window {
 struct v4l2_rect w;
 __u32 field;
 __u32 chromakey;
 struct v4l2_clip *clips;
 __u32 clipcount;
 void *bitmap;
 __u8 global_alpha;
};
struct v4l2_captureparm {
 __u32 capability;
 __u32 capturemode;
 struct v4l2_fract timeperframe;
 __u32 extendedmode;
 __u32 readbuffers;
 __u32 reserved[4];
};
struct v4l2_outputparm {
 __u32 capability;
 __u32 outputmode;
 struct v4l2_fract timeperframe;
 __u32 extendedmode;
 __u32 writebuffers;
 __u32 reserved[4];
};
struct v4l2_cropcap {
 __u32 type;
 struct v4l2_rect bounds;
 struct v4l2_rect defrect;
 struct v4l2_fract pixelaspect;
};
struct v4l2_crop {
 __u32 type;
 struct v4l2_rect c;
};
struct v4l2_selection {
 __u32 type;
 __u32 target;
 __u32 flags;
 struct v4l2_rect r;
 __u32 reserved[9];
};
typedef __u64 v4l2_std_id;
struct v4l2_standard {
 __u32 index;
 v4l2_std_id id;
 __u8 name[24];
 struct v4l2_fract frameperiod;
 __u32 framelines;
 __u32 reserved[4];
};
struct v4l2_dv_preset {
 __u32 preset;
 __u32 reserved[4];
};
struct v4l2_dv_enum_preset {
 __u32 index;
 __u32 preset;
 __u8 name[32];
 __u32 width;
 __u32 height;
 __u32 reserved[4];
};
struct v4l2_bt_timings {
 __u32 width;
 __u32 height;
 __u32 interlaced;
 __u32 polarities;
 __u64 pixelclock;
 __u32 hfrontporch;
 __u32 hsync;
 __u32 hbackporch;
 __u32 vfrontporch;
 __u32 vsync;
 __u32 vbackporch;
 __u32 il_vfrontporch;
 __u32 il_vsync;
 __u32 il_vbackporch;
 __u32 standards;
 __u32 flags;
 __u32 reserved[14];
} __attribute__ ((packed));
struct v4l2_dv_timings {
 __u32 type;
 union {
  struct v4l2_bt_timings bt;
  __u32 reserved[32];
 };
} __attribute__ ((packed));
struct v4l2_enum_dv_timings {
 __u32 index;
 __u32 reserved[3];
 struct v4l2_dv_timings timings;
};
struct v4l2_bt_timings_cap {
 __u32 min_width;
 __u32 max_width;
 __u32 min_height;
 __u32 max_height;
 __u64 min_pixelclock;
 __u64 max_pixelclock;
 __u32 standards;
 __u32 capabilities;
 __u32 reserved[16];
} __attribute__ ((packed));
struct v4l2_dv_timings_cap {
 __u32 type;
 __u32 reserved[3];
 union {
  struct v4l2_bt_timings_cap bt;
  __u32 raw_data[32];
 };
};
struct v4l2_input {
 __u32 index;
 __u8 name[32];
 __u32 type;
 __u32 audioset;
 __u32 tuner;
 v4l2_std_id std;
 __u32 status;
 __u32 capabilities;
 __u32 reserved[3];
};
struct v4l2_output {
 __u32 index;
 __u8 name[32];
 __u32 type;
 __u32 audioset;
 __u32 modulator;
 v4l2_std_id std;
 __u32 capabilities;
 __u32 reserved[3];
};
struct v4l2_control {
 __u32 id;
 __s32 value;
};
struct v4l2_ext_control {
 __u32 id;
 __u32 size;
 __u32 reserved2[1];
 union {
  __s32 value;
  __s64 value64;
  char *string;
 };
} __attribute__ ((packed));
struct v4l2_ext_controls {
 __u32 ctrl_class;
 __u32 count;
 __u32 error_idx;
 __u32 reserved[2];
 struct v4l2_ext_control *controls;
};
enum v4l2_ctrl_type {
 V4L2_CTRL_TYPE_INTEGER = 1,
 V4L2_CTRL_TYPE_BOOLEAN = 2,
 V4L2_CTRL_TYPE_MENU = 3,
 V4L2_CTRL_TYPE_BUTTON = 4,
 V4L2_CTRL_TYPE_INTEGER64 = 5,
 V4L2_CTRL_TYPE_CTRL_CLASS = 6,
 V4L2_CTRL_TYPE_STRING = 7,
 V4L2_CTRL_TYPE_BITMASK = 8,
 V4L2_CTRL_TYPE_INTEGER_MENU = 9,
};
struct v4l2_queryctrl {
 __u32 id;
 __u32 type;
 __u8 name[32];
 __s32 minimum;
 __s32 maximum;
 __s32 step;
 __s32 default_value;
 __u32 flags;
 __u32 reserved[2];
};
struct v4l2_querymenu {
 __u32 id;
 __u32 index;
 union {
  __u8 name[32];
  __s64 value;
 };
 __u32 reserved;
} __attribute__ ((packed));
enum v4l2_dv_tx_mode {
 V4L2_DV_TX_MODE_DVI_D = 0,
 V4L2_DV_TX_MODE_HDMI = 1,
};
enum v4l2_dv_rgb_range {
 V4L2_DV_RGB_RANGE_AUTO = 0,
 V4L2_DV_RGB_RANGE_LIMITED = 1,
 V4L2_DV_RGB_RANGE_FULL = 2,
};
struct v4l2_tuner {
 __u32 index;
 __u8 name[32];
 __u32 type;
 __u32 capability;
 __u32 rangelow;
 __u32 rangehigh;
 __u32 rxsubchans;
 __u32 audmode;
 __s32 signal;
 __s32 afc;
 __u32 reserved[4];
};
struct v4l2_modulator {
 __u32 index;
 __u8 name[32];
 __u32 capability;
 __u32 rangelow;
 __u32 rangehigh;
 __u32 txsubchans;
 __u32 reserved[4];
};
struct v4l2_frequency {
 __u32 tuner;
 __u32 type;
 __u32 frequency;
 __u32 reserved[8];
};
struct v4l2_frequency_band {
 __u32 tuner;
 __u32 type;
 __u32 index;
 __u32 capability;
 __u32 rangelow;
 __u32 rangehigh;
 __u32 modulation;
 __u32 reserved[9];
};
struct v4l2_hw_freq_seek {
 __u32 tuner;
 __u32 type;
 __u32 seek_upward;
 __u32 wrap_around;
 __u32 spacing;
 __u32 rangelow;
 __u32 rangehigh;
 __u32 reserved[5];
};
struct v4l2_rds_data {
 __u8 lsb;
 __u8 msb;
 __u8 block;
} __attribute__ ((packed));
struct v4l2_audio {
 __u32 index;
 __u8 name[32];
 __u32 capability;
 __u32 mode;
 __u32 reserved[2];
};
struct v4l2_audioout {
 __u32 index;
 __u8 name[32];
 __u32 capability;
 __u32 mode;
 __u32 reserved[2];
};
struct v4l2_enc_idx_entry {
 __u64 offset;
 __u64 pts;
 __u32 length;
 __u32 flags;
 __u32 reserved[2];
};
struct v4l2_enc_idx {
 __u32 entries;
 __u32 entries_cap;
 __u32 reserved[4];
 struct v4l2_enc_idx_entry entry[(64)];
};
struct v4l2_encoder_cmd {
 __u32 cmd;
 __u32 flags;
 union {
  struct {
   __u32 data[8];
  } raw;
 };
};
struct v4l2_decoder_cmd {
 __u32 cmd;
 __u32 flags;
 union {
  struct {
   __u64 pts;
  } stop;
  struct {
   __s32 speed;
   __u32 format;
  } start;
  struct {
   __u32 data[16];
  } raw;
 };
};
struct v4l2_vbi_format {
 __u32 sampling_rate;
 __u32 offset;
 __u32 samples_per_line;
 __u32 sample_format;
 __s32 start[2];
 __u32 count[2];
 __u32 flags;
 __u32 reserved[2];
};
struct v4l2_sliced_vbi_format {
 __u16 service_set;
 __u16 service_lines[2][24];
 __u32 io_size;
 __u32 reserved[2];
};
struct v4l2_sliced_vbi_cap {
 __u16 service_set;
 __u16 service_lines[2][24];
 __u32 type;
 __u32 reserved[3];
};
struct v4l2_sliced_vbi_data {
 __u32 id;
 __u32 field;
 __u32 line;
 __u32 reserved;
 __u8 data[48];
};
struct v4l2_mpeg_vbi_itv0_line {
 __u8 id;
 __u8 data[42];
} __attribute__ ((packed));
struct v4l2_mpeg_vbi_itv0 {
 __le32 linemask[2];
 struct v4l2_mpeg_vbi_itv0_line line[35];
} __attribute__ ((packed));
struct v4l2_mpeg_vbi_ITV0 {
 struct v4l2_mpeg_vbi_itv0_line line[36];
} __attribute__ ((packed));
struct v4l2_mpeg_vbi_fmt_ivtv {
 __u8 magic[4];
 union {
  struct v4l2_mpeg_vbi_itv0 itv0;
  struct v4l2_mpeg_vbi_ITV0 ITV0;
 };
} __attribute__ ((packed));
struct v4l2_plane_pix_format {
 __u32 sizeimage;
 __u16 bytesperline;
 __u16 reserved[7];
} __attribute__ ((packed));
struct v4l2_pix_format_mplane {
 __u32 width;
 __u32 height;
 __u32 pixelformat;
 __u32 field;
 __u32 colorspace;
 struct v4l2_plane_pix_format plane_fmt[8];
 __u8 num_planes;
 __u8 reserved[11];
} __attribute__ ((packed));
struct v4l2_format {
 __u32 type;
 union {
  struct v4l2_pix_format pix;
  struct v4l2_pix_format_mplane pix_mp;
  struct v4l2_window win;
  struct v4l2_vbi_format vbi;
  struct v4l2_sliced_vbi_format sliced;
  __u8 raw_data[200];
 } fmt;
};
struct v4l2_streamparm {
 __u32 type;
 union {
  struct v4l2_captureparm capture;
  struct v4l2_outputparm output;
  __u8 raw_data[200];
 } parm;
};
struct v4l2_event_vsync {
 __u8 field;
} __attribute__ ((packed));
struct v4l2_event_ctrl {
 __u32 changes;
 __u32 type;
 union {
  __s32 value;
  __s64 value64;
 };
 __u32 flags;
 __s32 minimum;
 __s32 maximum;
 __s32 step;
 __s32 default_value;
};
struct v4l2_event_frame_sync {
 __u32 frame_sequence;
};
struct v4l2_event {
 __u32 type;
 union {
  struct v4l2_event_vsync vsync;
  struct v4l2_event_ctrl ctrl;
  struct v4l2_event_frame_sync frame_sync;
  __u8 data[64];
 } u;
 __u32 pending;
 __u32 sequence;
 struct timespec timestamp;
 __u32 id;
 __u32 reserved[8];
};
struct v4l2_event_subscription {
 __u32 type;
 __u32 id;
 __u32 flags;
 __u32 reserved[5];
};
struct v4l2_dbg_match {
 __u32 type;
 union {
  __u32 addr;
  char name[32];
 };
} __attribute__ ((packed));
struct v4l2_dbg_register {
 struct v4l2_dbg_match match;
 __u32 size;
 __u64 reg;
 __u64 val;
} __attribute__ ((packed));
struct v4l2_dbg_chip_ident {
 struct v4l2_dbg_match match;
 __u32 ident;
 __u32 revision;
} __attribute__ ((packed));
struct v4l2_create_buffers {
 __u32 index;
 __u32 count;
 __u32 memory;
 struct v4l2_format format;
 __u32 reserved[8];
};
typedef struct v4l2_buffer struct_v4l2_buffer;
typedef struct v4l2_create_buffers struct_v4l2_create_buffers;
typedef struct v4l2_ext_control struct_v4l2_ext_control;
typedef struct v4l2_ext_controls struct_v4l2_ext_controls;
typedef struct v4l2_format struct_v4l2_format;
typedef struct v4l2_framebuffer struct_v4l2_framebuffer;
typedef struct v4l2_input struct_v4l2_input;
typedef struct v4l2_standard struct_v4l2_standard;
static void
print_pixelformat(uint32_t fourcc)
{
 const union {
  uint32_t pixelformat;
  unsigned char cc[sizeof(uint32_t)];
 } u = {
  .pixelformat = fourcc
 };
 unsigned int i;
 tprints("v4l2_fourcc(");
 for (i = 0; i < sizeof(u.cc); ++i) {
  unsigned char c = u.cc[i];
  if (i)
   tprints(", ");
  if (c == '\'' || c == '\\') {
   char sym[] = {
    '\'',
    '\\',
    c,
    '\'',
    '\0'
   };
   tprints(sym);
  } else if (c >= ' ' && c <= 0x7e) {
   char sym[] = {
    '\'',
    c,
    '\'',
    '\0'
   };
   tprints(sym);
  } else {
   char hex[] = {
    '\'',
    '\\',
    'x',
    "0123456789abcdef"[c >> 4],
    "0123456789abcdef"[c & 0xf],
    '\'',
    '\0'
   };
   tprints(hex);
  }
 }
 tprints(")");
}
static
const struct xlat v4l2_device_capabilities_flags[] = {
  { (unsigned)(0x00000001), "V4L2_CAP_VIDEO_CAPTURE" },
  { (unsigned)(0x00000002), "V4L2_CAP_VIDEO_OUTPUT" },
  { (unsigned)(0x00000004), "V4L2_CAP_VIDEO_OVERLAY" },
  { (unsigned)(0x00000010), "V4L2_CAP_VBI_CAPTURE" },
  { (unsigned)(0x00000020), "V4L2_CAP_VBI_OUTPUT" },
  { (unsigned)(0x00000040), "V4L2_CAP_SLICED_VBI_CAPTURE" },
  { (unsigned)(0x00000080), "V4L2_CAP_SLICED_VBI_OUTPUT" },
  { (unsigned)(0x00000100), "V4L2_CAP_RDS_CAPTURE" },
  { (unsigned)(0x00000200), "V4L2_CAP_VIDEO_OUTPUT_OVERLAY" },
  { (unsigned)(0x00000400), "V4L2_CAP_HW_FREQ_SEEK" },
  { (unsigned)(0x00000800), "V4L2_CAP_RDS_OUTPUT" },
  { (unsigned)(0x00001000), "V4L2_CAP_VIDEO_CAPTURE_MPLANE" },
  { (unsigned)(0x00002000), "V4L2_CAP_VIDEO_OUTPUT_MPLANE" },
  { (unsigned)(0x00008000), "V4L2_CAP_VIDEO_M2M" },
  { (unsigned)(0x00004000), "V4L2_CAP_VIDEO_M2M_MPLANE" },
  { (unsigned)(0x00010000), "V4L2_CAP_TUNER" },
  { (unsigned)(0x00020000), "V4L2_CAP_AUDIO" },
  { (unsigned)(0x00040000), "V4L2_CAP_RADIO" },
  { (unsigned)(0x00080000), "V4L2_CAP_MODULATOR" },
  { (unsigned)(0x01000000), "V4L2_CAP_READWRITE" },
  { (unsigned)(0x02000000), "V4L2_CAP_ASYNCIO" },
  { (unsigned)(0x04000000), "V4L2_CAP_STREAMING" },
  { (unsigned)(0x80000000), "V4L2_CAP_DEVICE_CAPS" },
 { 0, 0 }
};
static int
print_v4l2_capability(struct tcb *tcp, const long arg)
{
 struct v4l2_capability caps;
 if ((!((tcp)->flags & 0x04)))
  return 0;
 tprints(", ");
 if (umoven_or_printaddr((tcp), (arg), sizeof(*(&caps)), (void *) (&caps)))
  return 1;
 tprints("{driver=");
 print_quoted_string((const char *) caps.driver,
       sizeof(caps.driver), 0x01);
 tprints(", card=");
 print_quoted_string((const char *) caps.card,
       sizeof(caps.card), 0x01);
 tprints(", bus_info=");
 print_quoted_string((const char *) caps.bus_info,
       sizeof(caps.bus_info), 0x01);
 tprintf(", version=%u.%u.%u, capabilities=",
  (caps.version >> 16) & 0xFF,
  (caps.version >> 8) & 0xFF,
  caps.version & 0xFF);
 printflags(v4l2_device_capabilities_flags, caps.capabilities,
     "V4L2_CAP_???");
 tprints(", device_caps=");
 printflags(v4l2_device_capabilities_flags, caps.device_caps,
     "V4L2_CAP_???");
 tprints("}");
 return 1;
}
static
const struct xlat v4l2_buf_types[] = {
  { (unsigned)(V4L2_BUF_TYPE_VIDEO_CAPTURE), "V4L2_BUF_TYPE_VIDEO_CAPTURE" },
  { (unsigned)(V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE), "V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE" },
  { (unsigned)(V4L2_BUF_TYPE_VIDEO_OUTPUT), "V4L2_BUF_TYPE_VIDEO_OUTPUT" },
  { (unsigned)(V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE), "V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE" },
  { (unsigned)(V4L2_BUF_TYPE_VIDEO_OVERLAY), "V4L2_BUF_TYPE_VIDEO_OVERLAY" },
  { (unsigned)(V4L2_BUF_TYPE_VBI_CAPTURE), "V4L2_BUF_TYPE_VBI_CAPTURE" },
  { (unsigned)(V4L2_BUF_TYPE_VBI_OUTPUT), "V4L2_BUF_TYPE_VBI_OUTPUT" },
  { (unsigned)(V4L2_BUF_TYPE_SLICED_VBI_CAPTURE), "V4L2_BUF_TYPE_SLICED_VBI_CAPTURE" },
  { (unsigned)(V4L2_BUF_TYPE_SLICED_VBI_OUTPUT), "V4L2_BUF_TYPE_SLICED_VBI_OUTPUT" },
  { (unsigned)(V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY), "V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY" },
 { 0, 0 }
};
static
const struct xlat v4l2_format_description_flags[] = {
  { (unsigned)(0x0001), "V4L2_FMT_FLAG_COMPRESSED" },
  { (unsigned)(0x0002), "V4L2_FMT_FLAG_EMULATED" },
 { 0, 0 }
};
static int
print_v4l2_fmtdesc(struct tcb *tcp, const long arg)
{
 struct v4l2_fmtdesc f;
 if ((!((tcp)->flags & 0x04))) {
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&f)), (void *) (&f)))
   return 0100 | 1;
  tprintf("{index=%u, type=", f.index);
  printxval(v4l2_buf_types, f.type, "V4L2_BUF_TYPE_???");
  return 0;
 }
 if (!((tcp)->u_error != 0) && !umoven((tcp), (arg), sizeof(*(&f)), (void *) (&f))) {
  tprints(", flags=");
  printflags(v4l2_format_description_flags, f.flags,
      "V4L2_FMT_FLAG_???");
  tprints(", description=");
  print_quoted_string((const char *) f.description,
        sizeof(f.description),
        0x01);
  tprints(", pixelformat=");
  print_pixelformat(f.pixelformat);
 }
 tprints("}");
 return 1;
}
static
const struct xlat v4l2_fields[] = {
  { (unsigned)(V4L2_FIELD_ANY), "V4L2_FIELD_ANY" },
  { (unsigned)(V4L2_FIELD_NONE), "V4L2_FIELD_NONE" },
  { (unsigned)(V4L2_FIELD_TOP), "V4L2_FIELD_TOP" },
  { (unsigned)(V4L2_FIELD_BOTTOM), "V4L2_FIELD_BOTTOM" },
  { (unsigned)(V4L2_FIELD_INTERLACED), "V4L2_FIELD_INTERLACED" },
  { (unsigned)(V4L2_FIELD_SEQ_TB), "V4L2_FIELD_SEQ_TB" },
  { (unsigned)(V4L2_FIELD_SEQ_BT), "V4L2_FIELD_SEQ_BT" },
  { (unsigned)(V4L2_FIELD_ALTERNATE), "V4L2_FIELD_ALTERNATE" },
  { (unsigned)(V4L2_FIELD_INTERLACED_TB), "V4L2_FIELD_INTERLACED_TB" },
  { (unsigned)(V4L2_FIELD_INTERLACED_BT), "V4L2_FIELD_INTERLACED_BT" },
 { 0, 0 }
};
static
const struct xlat v4l2_colorspaces[] = {
  { (unsigned)(V4L2_COLORSPACE_SMPTE170M), "V4L2_COLORSPACE_SMPTE170M" },
  { (unsigned)(V4L2_COLORSPACE_SMPTE240M), "V4L2_COLORSPACE_SMPTE240M" },
  { (unsigned)(V4L2_COLORSPACE_REC709), "V4L2_COLORSPACE_REC709" },
  { (unsigned)(V4L2_COLORSPACE_BT878), "V4L2_COLORSPACE_BT878" },
  { (unsigned)(V4L2_COLORSPACE_470_SYSTEM_M), "V4L2_COLORSPACE_470_SYSTEM_M" },
  { (unsigned)(V4L2_COLORSPACE_470_SYSTEM_BG), "V4L2_COLORSPACE_470_SYSTEM_BG" },
  { (unsigned)(V4L2_COLORSPACE_JPEG), "V4L2_COLORSPACE_JPEG" },
  { (unsigned)(V4L2_COLORSPACE_SRGB), "V4L2_COLORSPACE_SRGB" },
 { 0, 0 }
};
static void
print_v4l2_format_fmt(const char *prefix, const struct_v4l2_format *f)
{
 switch (f->type) {
 case V4L2_BUF_TYPE_VIDEO_CAPTURE:
 case V4L2_BUF_TYPE_VIDEO_OUTPUT:
  tprints(prefix);
  tprintf("fmt.pix={width=%u, height=%u, pixelformat=",
   f->fmt.pix.width, f->fmt.pix.height);
  print_pixelformat(f->fmt.pix.pixelformat);
  tprints(", field=");
  printxval(v4l2_fields, f->fmt.pix.field, "V4L2_FIELD_???");
  tprintf(", bytesperline=%u, sizeimage=%u, colorspace=",
   f->fmt.pix.bytesperline, f->fmt.pix.sizeimage);
  printxval(v4l2_colorspaces, f->fmt.pix.colorspace,
     "V4L2_COLORSPACE_???");
  tprints("}");
  break;
 case V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
 case V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE: {
  unsigned int i, max;
  tprints(prefix);
  tprintf("fmt.pix_mp={width=%u, height=%u, pixelformat=",
   f->fmt.pix_mp.width, f->fmt.pix_mp.height);
  print_pixelformat(f->fmt.pix_mp.pixelformat);
  tprints(", field=");
  printxval(v4l2_fields, f->fmt.pix_mp.field, "V4L2_FIELD_???");
  tprints(", colorspace=");
  printxval(v4l2_colorspaces, f->fmt.pix_mp.colorspace,
     "V4L2_COLORSPACE_???");
  tprints(", plane_fmt=[");
  max = f->fmt.pix_mp.num_planes;
  if (max > 8)
   max = 8;
  for (i = 0; i < max; i++) {
   if (i > 0)
    tprints(", ");
   tprintf("{sizeimage=%u, bytesperline=%u}",
    f->fmt.pix_mp.plane_fmt[i].sizeimage,
    f->fmt.pix_mp.plane_fmt[i].bytesperline);
  }
  tprintf("], num_planes=%u}", (unsigned) f->fmt.pix_mp.num_planes);
  break;
 }
 }
}
static int
print_v4l2_format(struct tcb *tcp, const long arg, const _Bool is_get)
{
 struct_v4l2_format f;
 if ((!((tcp)->flags & 0x04))) {
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&f)), (void *) (&f)))
   return 0100 | 1;
  tprints("{type=");
  printxval(v4l2_buf_types, f.type, "V4L2_BUF_TYPE_???");
  if (is_get)
   return 0;
  print_v4l2_format_fmt(", ", &f);
 } else {
  if (!((tcp)->u_error != 0) && !umoven((tcp), (arg), sizeof(*(&f)), (void *) (&f))) {
   const char *delim = is_get ? ", " : " => ";
   print_v4l2_format_fmt(delim, &f);
  }
  tprints("}");
 }
 return 1;
}
static
const struct xlat v4l2_memories[] = {
  { (unsigned)(V4L2_MEMORY_MMAP), "V4L2_MEMORY_MMAP" },
  { (unsigned)(V4L2_MEMORY_USERPTR), "V4L2_MEMORY_USERPTR" },
 { 0, 0 }
};
static int
print_v4l2_requestbuffers(struct tcb *tcp, const long arg)
{
 struct v4l2_requestbuffers reqbufs;
 if ((!((tcp)->flags & 0x04))) {
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&reqbufs)), (void *) (&reqbufs)))
   return 0100 | 1;
  tprintf("{count=%u, type=", reqbufs.count);
  printxval(v4l2_buf_types, reqbufs.type, "V4L2_BUF_TYPE_???");
  tprints(", memory=");
  printxval(v4l2_memories, reqbufs.memory, "V4L2_MEMORY_???");
  tprints("}");
  return 0;
 } else {
  static char outstr[sizeof("{count=}") + sizeof(int) * 3];
  if (((tcp)->u_error != 0) || umoven((tcp), (arg), sizeof(*(&reqbufs)), (void *) (&reqbufs)) < 0)
   return 1;
  sprintf(outstr, "{count=%u}", reqbufs.count);
  tcp->auxstr = outstr;
  return 1 + 020;
 }
}
static
const struct xlat v4l2_buf_flags[] = {
  { (unsigned)(0x0001), "V4L2_BUF_FLAG_MAPPED" },
  { (unsigned)(0x0002), "V4L2_BUF_FLAG_QUEUED" },
  { (unsigned)(0x0004), "V4L2_BUF_FLAG_DONE" },
  { (unsigned)(0x0008), "V4L2_BUF_FLAG_KEYFRAME" },
  { (unsigned)(0x0010), "V4L2_BUF_FLAG_PFRAME" },
  { (unsigned)(0x0020), "V4L2_BUF_FLAG_BFRAME" },
  { (unsigned)(0x0100), "V4L2_BUF_FLAG_TIMECODE" },
 { 0, 0 }
};
static int
print_v4l2_buffer(struct tcb *tcp, const unsigned int code, const long arg)
{
 struct_v4l2_buffer b;
 if ((!((tcp)->flags & 0x04))) {
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&b)), (void *) (&b)))
   return 0100 | 1;
  tprints("{type=");
  printxval(v4l2_buf_types, b.type, "V4L2_BUF_TYPE_???");
  if (code != (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((17)) << 0) | ((((sizeof(struct v4l2_buffer)))) << ((0 +8)+8))))
   tprintf(", index=%u", b.index);
 } else {
  if (!((tcp)->u_error != 0) && umoven((tcp), (arg), sizeof(*(&b)), (void *) (&b)) == 0) {
   if (code == (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((17)) << 0) | ((((sizeof(struct v4l2_buffer)))) << ((0 +8)+8))))
    tprintf(", index=%u", b.index);
   tprints(", memory=");
   printxval(v4l2_memories, b.memory, "V4L2_MEMORY_???");
   if (b.memory == V4L2_MEMORY_MMAP) {
    tprintf(", m.offset=%#x", b.m.offset);
   } else if (b.memory == V4L2_MEMORY_USERPTR) {
    tprints(", m.userptr=");
    printaddr((unsigned long) b.m.userptr);
   }
   tprintf(", length=%u, bytesused=%u, flags=",
    b.length, b.bytesused);
   printflags(v4l2_buf_flags, b.flags, "V4L2_BUF_FLAG_???");
   if (code == (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((17)) << 0) | ((((sizeof(struct v4l2_buffer)))) << ((0 +8)+8)))) {
    tprints(", timestamp = ");
    print_struct_timeval(&b.timestamp);
   }
   tprints(", ...");
  }
  tprints("}");
 }
 return 1;
}
static int
print_v4l2_framebuffer(struct tcb *tcp, const long arg)
{
 struct_v4l2_framebuffer b;
 tprints(", ");
 if (!umoven_or_printaddr((tcp), (arg), sizeof(*(&b)), (void *) (&b))) {
  tprintf("{capability=%#x, flags=%#x, base=",
   b.capability, b.flags);
  printaddr((unsigned long) b.base);
  tprints("}");
 }
 return 0100 | 1;
}
static int
print_v4l2_buf_type(struct tcb *tcp, const long arg)
{
 int type;
 tprints(", ");
 if (!umoven_or_printaddr((tcp), (arg), sizeof(*(&type)), (void *) (&type))) {
  tprints("[");
  printxval(v4l2_buf_types, type, "V4L2_BUF_TYPE_???");
  tprints("]");
 }
 return 0100 | 1;
}
static
const struct xlat v4l2_streaming_capabilities[] = {
  { (unsigned)(0x1000), "V4L2_CAP_TIMEPERFRAME" },
 { 0, 0 }
};
static
const struct xlat v4l2_capture_modes[] = {
  { (unsigned)(0x0001), "V4L2_MODE_HIGHQUALITY" },
 { 0, 0 }
};
static int
print_v4l2_streamparm(struct tcb *tcp, const long arg, const _Bool is_get)
{
 struct v4l2_streamparm s;
 if ((!((tcp)->flags & 0x04))) {
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&s)), (void *) (&s)))
   return 0100 | 1;
  tprints("{type=");
  printxval(v4l2_buf_types, s.type, "V4L2_BUF_TYPE_???");
  switch (s.type) {
   case V4L2_BUF_TYPE_VIDEO_CAPTURE:
   case V4L2_BUF_TYPE_VIDEO_OUTPUT:
    if (is_get)
     return 0;
    tprints(", ");
    break;
   default:
    tprints("}");
    return 0100 | 1;
  }
 } else {
  if (((tcp)->u_error != 0) || umoven((tcp), (arg), sizeof(*(&s)), (void *) (&s)) < 0) {
   tprints("}");
   return 1;
  }
  tprints(is_get ? ", " : " => ");
 }
 if (s.type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
  tprints("parm.capture={capability=");
  printflags(v4l2_streaming_capabilities,
      s.parm.capture.capability, "V4L2_CAP_???");
  tprints(", capturemode=");
  printflags(v4l2_capture_modes,
      s.parm.capture.capturemode, "V4L2_MODE_???");
  tprintf(", timeperframe=" "%u/%u",
   ((s.parm.capture.timeperframe).numerator), ((s.parm.capture.timeperframe).denominator));
  tprintf(", extendedmode=%u, readbuffers=%u}",
   s.parm.capture.extendedmode,
   s.parm.capture.readbuffers);
 } else {
  tprints("parm.output={capability=");
  printflags(v4l2_streaming_capabilities,
      s.parm.output.capability, "V4L2_CAP_???");
  tprintf(", outputmode=%u", s.parm.output.outputmode);
  tprintf(", timeperframe=" "%u/%u",
   ((s.parm.output.timeperframe).numerator), ((s.parm.output.timeperframe).denominator));
  tprintf(", extendedmode=%u, writebuffers=%u}",
   s.parm.output.extendedmode,
   s.parm.output.writebuffers);
 }
 if (((tcp)->flags & 0x04))
  tprints("}");
 return 1;
}
static int
print_v4l2_standard(struct tcb *tcp, const long arg)
{
 struct_v4l2_standard s;
 if ((!((tcp)->flags & 0x04))) {
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&s)), (void *) (&s)))
   return 0100 | 1;
  tprintf("{index=%u", s.index);
 } else {
  if (!((tcp)->u_error != 0) && !umoven((tcp), (arg), sizeof(*(&s)), (void *) (&s))) {
   tprints(", name=");
   print_quoted_string((const char *) s.name,
         sizeof(s.name),
         0x01);
   tprintf(", frameperiod=" "%u/%u",
    ((s.frameperiod).numerator), ((s.frameperiod).denominator));
   tprintf(", framelines=%d", s.framelines);
  }
  tprints("}");
 }
 return 1;
}
static
const struct xlat v4l2_input_types[] = {
  { (unsigned)(1), "V4L2_INPUT_TYPE_TUNER" },
  { (unsigned)(2), "V4L2_INPUT_TYPE_CAMERA" },
 { 0, 0 }
};
static int
print_v4l2_input(struct tcb *tcp, const long arg)
{
 struct_v4l2_input i;
 if ((!((tcp)->flags & 0x04))) {
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&i)), (void *) (&i)))
   return 0100 | 1;
  tprintf("{index=%u", i.index);
 } else {
  if (!((tcp)->u_error != 0) && !umoven((tcp), (arg), sizeof(*(&i)), (void *) (&i))) {
   tprints(", name=");
   print_quoted_string((const char *) i.name,
         sizeof(i.name),
         0x01);
   tprints(", type=");
   printxval(v4l2_input_types, i.type,
      "V4L2_INPUT_TYPE_???");
  }
  tprints("}");
 }
 return 1;
}
static
const struct xlat v4l2_control_ids[] = {
 { (unsigned)(0), "0" },
  { (unsigned)(((0x00980000 | 0x900)+0)), "V4L2_CID_BRIGHTNESS" },
  { (unsigned)(((0x00980000 | 0x900)+1)), "V4L2_CID_CONTRAST" },
  { (unsigned)(((0x00980000 | 0x900)+2)), "V4L2_CID_SATURATION" },
  { (unsigned)(((0x00980000 | 0x900)+3)), "V4L2_CID_HUE" },
  { (unsigned)(((0x00980000 | 0x900)+5)), "V4L2_CID_AUDIO_VOLUME" },
  { (unsigned)(((0x00980000 | 0x900)+6)), "V4L2_CID_AUDIO_BALANCE" },
  { (unsigned)(((0x00980000 | 0x900)+7)), "V4L2_CID_AUDIO_BASS" },
  { (unsigned)(((0x00980000 | 0x900)+8)), "V4L2_CID_AUDIO_TREBLE" },
  { (unsigned)(((0x00980000 | 0x900)+9)), "V4L2_CID_AUDIO_MUTE" },
  { (unsigned)(((0x00980000 | 0x900)+10)), "V4L2_CID_AUDIO_LOUDNESS" },
  { (unsigned)(((0x00980000 | 0x900)+11)), "V4L2_CID_BLACK_LEVEL" },
  { (unsigned)(((0x00980000 | 0x900)+12)), "V4L2_CID_AUTO_WHITE_BALANCE" },
  { (unsigned)(((0x00980000 | 0x900)+13)), "V4L2_CID_DO_WHITE_BALANCE" },
  { (unsigned)(((0x00980000 | 0x900)+14)), "V4L2_CID_RED_BALANCE" },
  { (unsigned)(((0x00980000 | 0x900)+15)), "V4L2_CID_BLUE_BALANCE" },
  { (unsigned)(((0x00980000 | 0x900)+16)), "V4L2_CID_GAMMA" },
  { (unsigned)((((0x00980000 | 0x900)+16))), "V4L2_CID_WHITENESS" },
  { (unsigned)(((0x00980000 | 0x900)+17)), "V4L2_CID_EXPOSURE" },
  { (unsigned)(((0x00980000 | 0x900)+18)), "V4L2_CID_AUTOGAIN" },
  { (unsigned)(((0x00980000 | 0x900)+19)), "V4L2_CID_GAIN" },
  { (unsigned)(((0x00980000 | 0x900)+20)), "V4L2_CID_HFLIP" },
  { (unsigned)(((0x00980000 | 0x900)+21)), "V4L2_CID_VFLIP" },
  { (unsigned)(((0x00980000 | 0x900)+22)), "V4L2_CID_HCENTER" },
  { (unsigned)(((0x00980000 | 0x900)+23)), "V4L2_CID_VCENTER" },
  { (unsigned)(((0x00980000 | 0x900)+24)), "V4L2_CID_POWER_LINE_FREQUENCY" },
  { (unsigned)(((0x00980000 | 0x900)+25)), "V4L2_CID_HUE_AUTO" },
  { (unsigned)(((0x00980000 | 0x900)+26)), "V4L2_CID_WHITE_BALANCE_TEMPERATURE" },
  { (unsigned)(((0x00980000 | 0x900)+27)), "V4L2_CID_SHARPNESS" },
  { (unsigned)(((0x00980000 | 0x900)+28)), "V4L2_CID_BACKLIGHT_COMPENSATION" },
  { (unsigned)(((0x00980000 | 0x900)+29)), "V4L2_CID_CHROMA_AGC" },
  { (unsigned)(((0x00980000 | 0x900)+36)), "V4L2_CID_CHROMA_GAIN" },
  { (unsigned)(((0x00980000 | 0x900)+30)), "V4L2_CID_COLOR_KILLER" },
  { (unsigned)(((0x00980000 | 0x900)+31)), "V4L2_CID_COLORFX" },
  { (unsigned)(((0x00980000 | 0x900)+42)), "V4L2_CID_COLORFX_CBCR" },
  { (unsigned)(((0x00980000 | 0x900)+32)), "V4L2_CID_AUTOBRIGHTNESS" },
  { (unsigned)(((0x00980000 | 0x900)+33)), "V4L2_CID_BAND_STOP_FILTER" },
  { (unsigned)(((0x00980000 | 0x900)+34)), "V4L2_CID_ROTATE" },
  { (unsigned)(((0x00980000 | 0x900)+35)), "V4L2_CID_BG_COLOR" },
  { (unsigned)(((0x00980000 | 0x900)+37)), "V4L2_CID_ILLUMINATORS_1" },
  { (unsigned)(((0x00980000 | 0x900)+38)), "V4L2_CID_ILLUMINATORS_2" },
  { (unsigned)(((0x00980000 | 0x900)+39)), "V4L2_CID_MIN_BUFFERS_FOR_CAPTURE" },
  { (unsigned)(((0x00980000 | 0x900)+40)), "V4L2_CID_MIN_BUFFERS_FOR_OUTPUT" },
  { (unsigned)(((0x00980000 | 0x900)+41)), "V4L2_CID_ALPHA_COMPONENT" },
  { (unsigned)(((0x009a0000 | 0x900)+1)), "V4L2_CID_EXPOSURE_AUTO" },
  { (unsigned)(((0x009a0000 | 0x900)+2)), "V4L2_CID_EXPOSURE_ABSOLUTE" },
  { (unsigned)(((0x009a0000 | 0x900)+3)), "V4L2_CID_EXPOSURE_AUTO_PRIORITY" },
  { (unsigned)(((0x009a0000 | 0x900)+4)), "V4L2_CID_PAN_RELATIVE" },
  { (unsigned)(((0x009a0000 | 0x900)+5)), "V4L2_CID_TILT_RELATIVE" },
  { (unsigned)(((0x009a0000 | 0x900)+6)), "V4L2_CID_PAN_RESET" },
  { (unsigned)(((0x009a0000 | 0x900)+7)), "V4L2_CID_TILT_RESET" },
  { (unsigned)(((0x009a0000 | 0x900)+8)), "V4L2_CID_PAN_ABSOLUTE" },
  { (unsigned)(((0x009a0000 | 0x900)+9)), "V4L2_CID_TILT_ABSOLUTE" },
  { (unsigned)(((0x009a0000 | 0x900)+10)), "V4L2_CID_FOCUS_ABSOLUTE" },
  { (unsigned)(((0x009a0000 | 0x900)+11)), "V4L2_CID_FOCUS_RELATIVE" },
  { (unsigned)(((0x009a0000 | 0x900)+12)), "V4L2_CID_FOCUS_AUTO" },
  { (unsigned)(((0x009a0000 | 0x900)+13)), "V4L2_CID_ZOOM_ABSOLUTE" },
  { (unsigned)(((0x009a0000 | 0x900)+14)), "V4L2_CID_ZOOM_RELATIVE" },
  { (unsigned)(((0x009a0000 | 0x900)+15)), "V4L2_CID_ZOOM_CONTINUOUS" },
  { (unsigned)(((0x009a0000 | 0x900)+16)), "V4L2_CID_PRIVACY" },
  { (unsigned)(((0x009a0000 | 0x900)+17)), "V4L2_CID_IRIS_ABSOLUTE" },
  { (unsigned)(((0x009a0000 | 0x900)+18)), "V4L2_CID_IRIS_RELATIVE" },
  { (unsigned)(((0x009a0000 | 0x900)+19)), "V4L2_CID_AUTO_EXPOSURE_BIAS" },
  { (unsigned)(((0x009a0000 | 0x900)+20)), "V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE" },
  { (unsigned)(((0x009a0000 | 0x900)+21)), "V4L2_CID_WIDE_DYNAMIC_RANGE" },
  { (unsigned)(((0x009a0000 | 0x900)+22)), "V4L2_CID_IMAGE_STABILIZATION" },
  { (unsigned)(((0x009a0000 | 0x900)+23)), "V4L2_CID_ISO_SENSITIVITY" },
  { (unsigned)(((0x009a0000 | 0x900)+24)), "V4L2_CID_ISO_SENSITIVITY_AUTO" },
  { (unsigned)(((0x009a0000 | 0x900)+25)), "V4L2_CID_EXPOSURE_METERING" },
  { (unsigned)(((0x009a0000 | 0x900)+26)), "V4L2_CID_SCENE_MODE" },
  { (unsigned)(((0x009a0000 | 0x900)+27)), "V4L2_CID_3A_LOCK" },
  { (unsigned)(((0x009a0000 | 0x900)+28)), "V4L2_CID_AUTO_FOCUS_START" },
  { (unsigned)(((0x009a0000 | 0x900)+29)), "V4L2_CID_AUTO_FOCUS_STOP" },
  { (unsigned)(((0x009a0000 | 0x900)+30)), "V4L2_CID_AUTO_FOCUS_STATUS" },
  { (unsigned)(((0x009a0000 | 0x900)+31)), "V4L2_CID_AUTO_FOCUS_RANGE" },
  { (unsigned)(0x08000000), "V4L2_CID_PRIVATE_BASE" },
 { 0, 0 }
};
static int
print_v4l2_control(struct tcb *tcp, const long arg, const _Bool is_get)
{
 struct v4l2_control c;
 if ((!((tcp)->flags & 0x04))) {
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&c)), (void *) (&c)))
   return 0100 | 1;
  tprints("{id=");
  printxval(v4l2_control_ids, c.id, "V4L2_CID_???");
  if (!is_get)
   tprintf(", value=%d", c.value);
  return 0;
 }
 if (!((tcp)->u_error != 0) && !umoven((tcp), (arg), sizeof(*(&c)), (void *) (&c))) {
  tprints(is_get ? ", " : " => ");
  tprintf("value=%d", c.value);
 }
 tprints("}");
 return 1;
}
static
const struct xlat v4l2_control_types[] = {
  { (unsigned)(V4L2_CTRL_TYPE_INTEGER), "V4L2_CTRL_TYPE_INTEGER" },
  { (unsigned)(V4L2_CTRL_TYPE_BOOLEAN), "V4L2_CTRL_TYPE_BOOLEAN" },
  { (unsigned)(V4L2_CTRL_TYPE_MENU), "V4L2_CTRL_TYPE_MENU" },
  { (unsigned)(V4L2_CTRL_TYPE_INTEGER_MENU), "V4L2_CTRL_TYPE_INTEGER_MENU" },
  { (unsigned)(V4L2_CTRL_TYPE_BITMASK), "V4L2_CTRL_TYPE_BITMASK" },
  { (unsigned)(V4L2_CTRL_TYPE_BUTTON), "V4L2_CTRL_TYPE_BUTTON" },
  { (unsigned)(V4L2_CTRL_TYPE_INTEGER64), "V4L2_CTRL_TYPE_INTEGER64" },
  { (unsigned)(V4L2_CTRL_TYPE_STRING), "V4L2_CTRL_TYPE_STRING" },
  { (unsigned)(V4L2_CTRL_TYPE_CTRL_CLASS), "V4L2_CTRL_TYPE_CTRL_CLASS" },
 { 0, 0 }
};
static
const struct xlat v4l2_control_flags[] = {
  { (unsigned)(0x0001), "V4L2_CTRL_FLAG_DISABLED" },
  { (unsigned)(0x0002), "V4L2_CTRL_FLAG_GRABBED" },
  { (unsigned)(0x0004), "V4L2_CTRL_FLAG_READ_ONLY" },
  { (unsigned)(0x0008), "V4L2_CTRL_FLAG_UPDATE" },
  { (unsigned)(0x0010), "V4L2_CTRL_FLAG_INACTIVE" },
  { (unsigned)(0x0020), "V4L2_CTRL_FLAG_SLIDER" },
  { (unsigned)(0x0040), "V4L2_CTRL_FLAG_WRITE_ONLY" },
  { (unsigned)(0x0080), "V4L2_CTRL_FLAG_VOLATILE" },
 { 0, 0 }
};
static int
print_v4l2_queryctrl(struct tcb *tcp, const long arg)
{
 struct v4l2_queryctrl c;
 if ((!((tcp)->flags & 0x04))) {
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&c)), (void *) (&c)))
   return 0100 | 1;
  tprints("{id=");
 } else {
  if (((tcp)->u_error != 0) || umoven((tcp), (arg), sizeof(*(&c)), (void *) (&c)) < 0) {
   tprints("}");
   return 1;
  }
  if (get_tcb_priv_ulong(tcp))
   tprints(" => ");
 }
 if ((!((tcp)->flags & 0x04)) || get_tcb_priv_ulong(tcp)) {
  const unsigned long next = c.id & 0x80000000;
  set_tcb_priv_ulong(tcp, next);
  if (next) {
   tprints("V4L2_CTRL_FLAG_NEXT_CTRL|");
   c.id &= ~0x80000000;
  }
  printxval(v4l2_control_ids, c.id, "V4L2_CID_???");
 }
 if (((tcp)->flags & 0x04)) {
  tprints(", type=");
  printxval(v4l2_control_types, c.type, "V4L2_CTRL_TYPE_???");
  tprints(", name=");
  print_quoted_string((const char *) c.name,
        sizeof(c.name),
        0x01);
  tprintf(", minimum=%d, maximum=%d, step=%d"
   ", default_value=%d, flags=",
   c.minimum, c.maximum, c.step, c.default_value);
  printflags(v4l2_control_flags, c.flags, "V4L2_CTRL_FLAG_???");
  tprints("}");
 }
 return 1;
}
static int
print_v4l2_cropcap(struct tcb *tcp, const long arg)
{
 struct v4l2_cropcap c;
 if ((!((tcp)->flags & 0x04))) {
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&c)), (void *) (&c)))
   return 0100 | 1;
  tprints("{type=");
  printxval(v4l2_buf_types, c.type, "V4L2_BUF_TYPE_???");
  return 0;
 }
 if (!((tcp)->u_error != 0) && !umoven((tcp), (arg), sizeof(*(&c)), (void *) (&c))) {
  tprintf(", bounds=" "{left=%d, top=%d, width=%u, height=%u}"
   ", defrect=" "{left=%d, top=%d, width=%u, height=%u}"
   ", pixelaspect=" "%u/%u",
   (c.bounds).left, (c.bounds).top, (c.bounds).width, (c.bounds).height,
   (c.defrect).left, (c.defrect).top, (c.defrect).width, (c.defrect).height,
   ((c.pixelaspect).numerator), ((c.pixelaspect).denominator));
 }
 tprints("}");
 return 1;
}
static int
print_v4l2_crop(struct tcb *tcp, const long arg, const _Bool is_get)
{
 struct v4l2_crop c;
 if ((!((tcp)->flags & 0x04))) {
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&c)), (void *) (&c)))
   return 0100 | 1;
  tprints("{type=");
  printxval(v4l2_buf_types, c.type, "V4L2_BUF_TYPE_???");
  if (is_get)
   return 0;
  tprintf(", c=" "{left=%d, top=%d, width=%u, height=%u}", (c.c).left, (c.c).top, (c.c).width, (c.c).height);
 } else {
  if (!((tcp)->u_error != 0) && !umoven((tcp), (arg), sizeof(*(&c)), (void *) (&c)))
   tprintf(", c=" "{left=%d, top=%d, width=%u, height=%u}", (c.c).left, (c.c).top, (c.c).width, (c.c).height);
 }
 tprints("}");
 return 0100 | 1;
}
static _Bool
print_v4l2_ext_control(struct tcb *tcp, void *elem_buf, size_t elem_size, void *data)
{
 const struct_v4l2_ext_control *p = elem_buf;
 tprints("{id=");
 printxval(v4l2_control_ids, p->id, "V4L2_CID_???");
 tprintf(", size=%u", p->size);
 if (p->size > 0) {
  tprints(", string=");
  printstr(tcp, (long) p->string, p->size);
 } else
 tprintf(", value=%d, value64=%lld", p->value,
  (long long) p->value64);
 tprints("}");
 return 1;
}
static
const struct xlat v4l2_control_classes[] = {
  { (unsigned)(0x00980000), "V4L2_CTRL_CLASS_USER" },
  { (unsigned)(0x00990000), "V4L2_CTRL_CLASS_MPEG" },
  { (unsigned)(0x009a0000), "V4L2_CTRL_CLASS_CAMERA" },
  { (unsigned)(0x009b0000), "V4L2_CTRL_CLASS_FM_TX" },
  { (unsigned)(0x009c0000), "V4L2_CTRL_CLASS_FLASH" },
  { (unsigned)(0x009d0000), "V4L2_CTRL_CLASS_JPEG" },
  { (unsigned)(0x009e0000), "V4L2_CTRL_CLASS_IMAGE_SOURCE" },
  { (unsigned)(0x009f0000), "V4L2_CTRL_CLASS_IMAGE_PROC" },
 { 0, 0 }
};
static int
print_v4l2_ext_controls(struct tcb *tcp, const long arg, const _Bool is_get)
{
 struct_v4l2_ext_controls c;
 if ((!((tcp)->flags & 0x04))) {
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&c)), (void *) (&c)))
   return 0100 | 1;
  tprints("{ctrl_class=");
  printxval(v4l2_control_classes, c.ctrl_class,
     "V4L2_CTRL_CLASS_???");
  tprintf(", count=%u", c.count);
  if (!c.count) {
   tprints("}");
   return 0100 | 1;
  }
  if (is_get)
   return 0;
  tprints(", ");
 } else {
  if (umoven((tcp), (arg), sizeof(*(&c)), (void *) (&c)) < 0) {
   tprints("}");
   return 1;
  }
  tprints(is_get ? ", " : " => ");
 }
 tprints("controls=");
 struct_v4l2_ext_control ctrl;
 _Bool fail = !print_array(tcp, (unsigned long) c.controls, c.count,
     &ctrl, sizeof(ctrl),
     umoven_or_printaddr_ignore_syserror,
     print_v4l2_ext_control, 0);
 if (((tcp)->flags & 0x04) && ((tcp)->u_error != 0))
  tprintf(", error_idx=%u", c.error_idx);
 if (((tcp)->flags & 0x04) || fail) {
  tprints("}");
  return 0100 | 1;
 }
 return 1;
}
static
const struct xlat v4l2_framesize_types[] = {
  { (unsigned)(V4L2_FRMSIZE_TYPE_DISCRETE), "V4L2_FRMSIZE_TYPE_DISCRETE" },
  { (unsigned)(V4L2_FRMSIZE_TYPE_CONTINUOUS), "V4L2_FRMSIZE_TYPE_CONTINUOUS" },
  { (unsigned)(V4L2_FRMSIZE_TYPE_STEPWISE), "V4L2_FRMSIZE_TYPE_STEPWISE" },
 { 0, 0 }
};
static int
print_v4l2_frmsizeenum(struct tcb *tcp, const long arg)
{
 struct v4l2_frmsizeenum s;
 if ((!((tcp)->flags & 0x04))) {
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&s)), (void *) (&s)))
   return 0100 | 1;
  tprintf("{index=%u, pixel_format=", s.index);
  print_pixelformat(s.pixel_format);
  return 0;
 }
 if (!((tcp)->u_error != 0) && !umoven((tcp), (arg), sizeof(*(&s)), (void *) (&s))) {
  tprints(", type=");
  printxval(v4l2_framesize_types, s.type, "V4L2_FRMSIZE_TYPE_???");
  switch (s.type) {
  case V4L2_FRMSIZE_TYPE_DISCRETE:
   tprintf(", discrete={width=%u, height=%u}",
    s.discrete.width, s.discrete.height);
   break;
  case V4L2_FRMSIZE_TYPE_STEPWISE:
   tprintf(", stepwise={min_width=%u, max_width=%u, "
    "step_width=%u, min_height=%u, max_height=%u, "
    "step_height=%u}",
    s.stepwise.min_width, s.stepwise.max_width,
    s.stepwise.step_width, s.stepwise.min_height,
    s.stepwise.max_height, s.stepwise.step_height);
   break;
  }
 }
 tprints("}");
 return 1;
}
static
const struct xlat v4l2_frameinterval_types[] = {
  { (unsigned)(V4L2_FRMIVAL_TYPE_DISCRETE), "V4L2_FRMIVAL_TYPE_DISCRETE" },
  { (unsigned)(V4L2_FRMIVAL_TYPE_CONTINUOUS), "V4L2_FRMIVAL_TYPE_CONTINUOUS" },
  { (unsigned)(V4L2_FRMIVAL_TYPE_STEPWISE), "V4L2_FRMIVAL_TYPE_STEPWISE" },
 { 0, 0 }
};
static int
print_v4l2_frmivalenum(struct tcb *tcp, const long arg)
{
 struct v4l2_frmivalenum f;
 if ((!((tcp)->flags & 0x04))) {
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&f)), (void *) (&f)))
   return 0100 | 1;
  tprintf("{index=%u, pixel_format=", f.index);
  print_pixelformat(f.pixel_format);
  tprintf(", width=%u, height=%u", f.width, f.height);
  return 0;
 }
 if (!((tcp)->u_error != 0) && !umoven((tcp), (arg), sizeof(*(&f)), (void *) (&f))) {
  tprints(", type=");
  printxval(v4l2_frameinterval_types, f.type,
     "V4L2_FRMIVAL_TYPE_???");
  switch (f.type) {
  case V4L2_FRMIVAL_TYPE_DISCRETE:
   tprintf(", discrete=" "%u/%u",
    ((f.discrete).numerator), ((f.discrete).denominator));
   break;
  case V4L2_FRMIVAL_TYPE_STEPWISE:
  case V4L2_FRMSIZE_TYPE_CONTINUOUS:
   tprintf(", stepwise={min=" "%u/%u" ", max="
    "%u/%u" ", step=" "%u/%u" "}",
    ((f.stepwise.min).numerator), ((f.stepwise.min).denominator),
    ((f.stepwise.max).numerator), ((f.stepwise.max).denominator),
    ((f.stepwise.step).numerator), ((f.stepwise.step).denominator));
   break;
  }
 }
 tprints("}");
 return 1;
}
static int
print_v4l2_create_buffers(struct tcb *tcp, const long arg)
{
 struct_v4l2_create_buffers b;
 if ((!((tcp)->flags & 0x04))) {
  tprints(", ");
  if (umoven_or_printaddr((tcp), (arg), sizeof(*(&b)), (void *) (&b)))
   return 0100 | 1;
  tprintf("{count=%u, memory=", b.count);
  printxval(v4l2_memories, b.memory, "V4L2_MEMORY_???");
  tprints(", format={type=");
  printxval(v4l2_buf_types, b.format.type,
     "V4L2_BUF_TYPE_???");
  print_v4l2_format_fmt(", ",
          (struct_v4l2_format *) &b.format);
  tprints("}}");
  return 0;
 } else {
  static const char fmt[] = "{index=%u, count=%u}";
  static char outstr[sizeof(fmt) + sizeof(int) * 6];
  if (((tcp)->u_error != 0) || umoven((tcp), (arg), sizeof(*(&b)), (void *) (&b)) < 0)
   return 1;
  sprintf(outstr, fmt, b.index, b.count);
  tcp->auxstr = outstr;
  return 1 + 020;
 }
}
MPERS_PRINTER_DECL(int, v4l2_ioctl, struct tcb *tcp, const unsigned int code, const long arg)
{
 if (!((tcp)->qual_flg & 0x004))
  return 0100;
 switch (code) {
 case (((2U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((0)) << 0) | ((((sizeof(struct v4l2_capability)))) << ((0 +8)+8))):
  return print_v4l2_capability(tcp, arg);
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((2)) << 0) | ((((sizeof(struct v4l2_fmtdesc)))) << ((0 +8)+8))):
  return print_v4l2_fmtdesc(tcp, arg);
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((4)) << 0) | ((((sizeof(struct v4l2_format)))) << ((0 +8)+8))):
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((5)) << 0) | ((((sizeof(struct v4l2_format)))) << ((0 +8)+8))):
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((64)) << 0) | ((((sizeof(struct v4l2_format)))) << ((0 +8)+8))):
  return print_v4l2_format(tcp, arg, code == (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((4)) << 0) | ((((sizeof(struct v4l2_format)))) << ((0 +8)+8))));
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((8)) << 0) | ((((sizeof(struct v4l2_requestbuffers)))) << ((0 +8)+8))):
  return print_v4l2_requestbuffers(tcp, arg);
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((9)) << 0) | ((((sizeof(struct v4l2_buffer)))) << ((0 +8)+8))):
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((15)) << 0) | ((((sizeof(struct v4l2_buffer)))) << ((0 +8)+8))):
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((17)) << 0) | ((((sizeof(struct v4l2_buffer)))) << ((0 +8)+8))):
  return print_v4l2_buffer(tcp, code, arg);
 case (((2U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((10)) << 0) | ((((sizeof(struct v4l2_framebuffer)))) << ((0 +8)+8))):
  if ((!((tcp)->flags & 0x04)))
   return 0;
 case (((1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((11)) << 0) | ((((sizeof(struct v4l2_framebuffer)))) << ((0 +8)+8))):
  return print_v4l2_framebuffer(tcp, arg);
 case (((1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((18)) << 0) | ((((sizeof(int)))) << ((0 +8)+8))):
 case (((1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((19)) << 0) | ((((sizeof(int)))) << ((0 +8)+8))):
  return print_v4l2_buf_type(tcp, arg);
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((21)) << 0) | ((((sizeof(struct v4l2_streamparm)))) << ((0 +8)+8))):
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((22)) << 0) | ((((sizeof(struct v4l2_streamparm)))) << ((0 +8)+8))):
  return print_v4l2_streamparm(tcp, arg, code == (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((21)) << 0) | ((((sizeof(struct v4l2_streamparm)))) << ((0 +8)+8))));
 case (((2U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((23)) << 0) | ((((sizeof(v4l2_std_id)))) << ((0 +8)+8))):
  if ((!((tcp)->flags & 0x04)))
   return 0;
 case (((1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((24)) << 0) | ((((sizeof(v4l2_std_id)))) << ((0 +8)+8))):
  tprints(", ");
  printnum_int64(tcp, arg, "%#" "l" "x");
  return 0100 | 1;
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((25)) << 0) | ((((sizeof(struct v4l2_standard)))) << ((0 +8)+8))):
  return print_v4l2_standard(tcp, arg);
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((26)) << 0) | ((((sizeof(struct v4l2_input)))) << ((0 +8)+8))):
  return print_v4l2_input(tcp, arg);
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((27)) << 0) | ((((sizeof(struct v4l2_control)))) << ((0 +8)+8))):
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((28)) << 0) | ((((sizeof(struct v4l2_control)))) << ((0 +8)+8))):
  return print_v4l2_control(tcp, arg, code == (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((27)) << 0) | ((((sizeof(struct v4l2_control)))) << ((0 +8)+8))));
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((36)) << 0) | ((((sizeof(struct v4l2_queryctrl)))) << ((0 +8)+8))):
  return print_v4l2_queryctrl(tcp, arg);
 case (((2U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((38)) << 0) | ((((sizeof(int)))) << ((0 +8)+8))):
  if ((!((tcp)->flags & 0x04)))
   return 0;
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((39)) << 0) | ((((sizeof(int)))) << ((0 +8)+8))):
  tprints(", ");
  printnum_int(tcp, arg, "%u");
  return 0100 | 1;
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((58)) << 0) | ((((sizeof(struct v4l2_cropcap)))) << ((0 +8)+8))):
  return print_v4l2_cropcap(tcp, arg);
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((59)) << 0) | ((((sizeof(struct v4l2_crop)))) << ((0 +8)+8))):
 case (((1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((60)) << 0) | ((((sizeof(struct v4l2_crop)))) << ((0 +8)+8))):
  return print_v4l2_crop(tcp, arg, code == (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((59)) << 0) | ((((sizeof(struct v4l2_crop)))) << ((0 +8)+8))));
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((72)) << 0) | ((((sizeof(struct v4l2_ext_controls)))) << ((0 +8)+8))):
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((73)) << 0) | ((((sizeof(struct v4l2_ext_controls)))) << ((0 +8)+8))):
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((71)) << 0) | ((((sizeof(struct v4l2_ext_controls)))) << ((0 +8)+8))):
  return print_v4l2_ext_controls(tcp, arg,
            code == (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((71)) << 0) | ((((sizeof(struct v4l2_ext_controls)))) << ((0 +8)+8))));
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((74)) << 0) | ((((sizeof(struct v4l2_frmsizeenum)))) << ((0 +8)+8))):
  return print_v4l2_frmsizeenum(tcp, arg);
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((75)) << 0) | ((((sizeof(struct v4l2_frmivalenum)))) << ((0 +8)+8))):
  return print_v4l2_frmivalenum(tcp, arg);
 case (((2U|1U) << (((0 +8)+8)+14)) | ((('V')) << (0 +8)) | (((92)) << 0) | ((((sizeof(struct v4l2_create_buffers)))) << ((0 +8)+8))):
  return print_v4l2_create_buffers(tcp, arg);
 default:
  return 0100;
 }
}
