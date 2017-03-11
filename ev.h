#ifndef EV_H_ 
#define EV_H_ 

#ifdef __cplusplus
	#define EV_CPP(x) x 

	#if __cplusplus >= 201103L
		#define EV_THROWN noexcept 
	#else
		#define EV_THROWN throw()
	#endif
#else 
	#define EV_CPP(x)
	#define EV_THROWN
#endif 


#ifndef EV_FEATURES
	#if defined __OPTIMIZE_CODE__
		#define EV_FEATURES	0x7c 
	#else 
		#define EV_FEATURES	0x7f 
	#endif 
#endif

#define EV_FEATURE_CODE ((EV_FEATURES) & 1) 
#define EV_FEATURE_DATA     ((EV_FEATURES) &  2)
#define EV_FEATURE_CONFIG   ((EV_FEATURES) &  4)
#define EV_FEATURE_API      ((EV_FEATURES) &  8)
#define EV_FEATURE_WATCHERS ((EV_FEATURES) & 16)
#define EV_FEATURE_BACKENDS ((EV_FEATURES) & 32)
#define EV_FEATURE_OS       ((EV_FEATURES) & 64)

#ifndef EV_MINPRI
	#define EV_MINPRI (EV_FEATURE_CONFIG ? -2 :0)
#endif 
#ifndef EV_MAXPRI
	#define EV_MAXPRI(EV_FEATURE_CONFIG  ? +2 : 0)
#endif

#ifndef EV_MULTIPLICITY 
	#define EV_MULTIPLICITY	EV_FEATURE_CONFIG
#endif 

#ifndef EV_PERIODIC_ENABLE 
	#define EV_PERIODIC_ENABLE	EV_FEATURE_WATCHERS
#endif 

#ifndef EV_STAT_ENABLE
# define EV_STAT_ENABLE EV_FEATURE_WATCHERS
#endif

#ifndef EV_PREPARE_ENABLE
# define EV_PREPARE_ENABLE EV_FEATURE_WATCHERS
#endif

#ifndef EV_CHECK_ENABLE
# define EV_CHECK_ENABLE EV_FEATURE_WATCHERS
#endif

#ifndef EV_IDLE_ENABLE
# define EV_IDLE_ENABLE EV_FEATURE_WATCHERS
#endif

#ifndef EV_FORK_ENABLE
# define EV_FORK_ENABLE EV_FEATURE_WATCHERS
#endif

#ifndef EV_CLEANUP_ENABLE
# define EV_CLEANUP_ENABLE EV_FEATURE_WATCHERS
#endif

#ifndef EV_SIGNAL_ENABLE
# define EV_SIGNAL_ENABLE EV_FEATURE_WATCHERS
#endif


#ifndef EV_CHILD_ENABLE
# ifdef _WIN32
#  define EV_CHILD_ENABLE 0
# else
#  define EV_CHILD_ENABLE EV_FEATURE_WATCHERS
#endif
#endif

#ifndef EV_ASYNC_ENABLE
# define EV_ASYNC_ENABLE EV_FEATURE_WATCHERS
#endif



#ifndef EV_EMBED_ENABLE
# define EV_EMBED_ENABLE EV_FEATURE_WATCHERS
#endif


#ifndef EV_WALK_ENABLE
# define EV_WALK_ENABLE 0 /* not yet */
#endif

#if EV_CHILD_ENABLE && !EV_SIGNAL_ENABLE
# undef EV_SIGNAL_ENABLE
# define EV_SIGNAL_ENABLE 1
#endif

typedef double ev_tmstamp; 

#ifndef EV_ATOMIC_T 
	#include <signal.h>
	#define EV_ATOMIC_T	sig_atomic_t volatile
#endif 

#if EV_STAT_ENABLE
	#ifdef _WIN32
		#include <time.h>
		#include <sys/types.h>
	#endif
	#include <sys/stat.h>
#endif

#if EV_MULTIPLICITY
struct ev_loop; 
#define EV_P 	struct ev_loop* loop 								/* a loop as sole parameter in declaration */ 
#define EV_P_ EV_P, 															/* a loop as first of multiple parameters */ 
#define EV_A 	loop 																/* a loop as sole argument to a function call */ 
#define EV_A_ EV_A, 															/* a loop as first of multiple arguments */ 
#define EV_DEFAULT_UC  ev_default_loop_uc_ ()    /* the default loop, if initialised, as sole arg */
#define EV_DEFAULT_UC_ EV_DEFAULT_UC,            /* the default loop as first of multiple arguments */
#define EV_DEFAULT  ev_default_loop (0)          /* the default loop as sole arg */
#define EV_DEFAULT_ EV_DEFAULT,                  /* the default loop as first of multiple arguments */
#else
#define EV_P void
#define EV_P_
#define EV_A
#define EV_A_
#define EV_DEFAULT
#define EV_DEFAULT_
#define EV_DEFAULT_UC
#define EV_DEFAULT_UC_
#undef EV_EMBED_ENABLE
#endif


/* EV_INLINE is used for function in header file */ 
#if __STDC_VERSION__ >= 199901L || __GNUc__ >= 3
	#define EV_INLINE 	static inline 
#else 
	#define EV_INLINE	static 
#endif

#ifdef EV_API_STATIC
# define EV_API_DECL static
#else
# define EV_API_DECL extern
#endif


#ifndef EV_PROTOTYPES
# define EV_PROTOTYPES 1
#endif

#define EV_VERSION_MAJOR 4
#define EV_VERSION_MINOR 22

/* eventmask, reventsl, events */ 

enum {
	EV_UNDEF	= (int) 0xFFFFFFFF,			/* guaranted to be invalid */ 
	EV_NONE 	= 		0x00,				/* no events */ 
	EV_READ 	= 	 	0x01,				/* ev_io detected read will not block */ 
	EV_WRITE	= 		0x02, 				/* ev_io detected write will not block */ 
	EV_IOFDSET	= 		0x80, 				/* internal use only */ 
	EV_IO 		= 		EV_READ, 			/* alias for type-detection */ 
	EV_TIMER	= 		0x0000100, 			/* timer timed out */ 
#if EV_COMPAT3
	EV_TIMEOUT	= 		EV_TIMER, 			/* pre. 4.0 API compatiblity */ 
#endif 
	EV_PERIODIC = 	   0x00000200, 		/* periodic timer timed out */ 
	EV_SIGNAL   = 	   0x00000400, 		/* signal was received */ 
	EV_CHILD    =      0x00000800, /* child/pid had status change */
  	EV_STAT     =      0x00001000, /* stat data changed */
  	EV_IDLE     =      0x00002000, /* event loop is idling */
  	EV_PREPARE  =      0x00004000, /* event loop about to poll */
  	EV_CHECK    =      0x00008000, /* event loop finished poll */
  	EV_EMBED    =      0x00010000, /* embedded event loop needs sweep */
  	EV_FORK     =      0x00020000, /* event loop resumed in child */
  	EV_CLEANUP  =      0x00040000, /* event loop resumed in child */
  	EV_ASYNC    =      0x00080000, /* async intra-loop signal */
  	EV_CUSTOM   =      0x01000000, /* for use by user code */
  	EV_ERROR    = (int)0x80000000  /* sent when an error occurs */
};			


/* can be used to add custom fields to all watchers, while loosing binary compatibility */ 
#ifndef EV_COMMON
	#define EV_COMMOM	void* data; 
#endif 


#ifndef EV_CB_DECLARE 
	#define EV_CB_DECLARE(type) void (*cb)(EV_P_ struct type* w, int revents); 
#endif 
#ifndef EV_CB_INVOKE
	#define EV_CB_INVOKE(wathcher, revents) (watcher)->cb(EV_A_ (watcher), (revents)) 
#endif


/* */ 
#define EV_CB(type, name) void name (EV_P_ struct ev_ ##type *w, int revents) 

#if EV_MINPRI == EV_MAXPRI
	#define EV_DECL_PRIORITY
#elif !defined(EV_DECL_PRIORITY)
	#define EV_DECL_PRIORITY int priority;
#endif 

/* shared by all wartchers */ 

#define EV_WATCHER(type)						\
	int active; /* private */ 				\
	int pending; /* private */ 				\
	EV_DECL_PRIORITY /* private */ 		\
	EV_COMMON /* rw */ 								\
	EV_CB_DECLARE(type) /* private */ \


#define EV_WATCHER_LIST(type) 			\
	EV_WATCHER(type) 									\
	struct ev_watcher_list* next; /* private */ \


#define EV_WATCHER_TIME(type) 			\
	EV_WATCHER(type)									\
	ev_tstamp at; /* private */ 			\

/* base class, nothing to see here unsless you subclass */ 

typedef struct ev_watcher {
	EV_WATCHER(ev_watcher); 
} ew_watcher; 

/* 	base class, nothing to see here unsless you sublcass */ 
typedef struct ev_watcher_list {
	EV_WATCHER_LIST(ev_watcher_list)

} ew_watcher_list; 

/* base class, nothing to see here unless you subclass */ 
typedef struct ev_watcher_time {
	EW_WATCHER_TIME(ev_Watcher_time) 
} ev_watcher_time; 

/* invoked when fd is either EV_READABLE or EV_WRITABLE */ 
/* revents EV_READ, EV_WRITE */ 
typedef struct ev_io {
	EV_WATCHER_LIST(ev_io); 

	int fd; /* ro */ 
	int events; /* ro */ 

} ev_io; 

/* invoke after a specific time, repeatbable (based on monotonic clock ) 
 * revents EV_TIMEOUT */ 
typedef struct ev_timer {
	EV_WATCHER_LIST(ev_timer) 

	ev_tstamp repeat; /* rw */ 
} ev_timer; 

/* 
 * Invoke at some specific time, possibly repeating at regular 
 * intervals (based on UTC) 
 * revents EV_PERIODIC */ 
typedef struct ev_periodic {
	EV_WATCHER_LIST(ev_periodic)

	ev_tstamp offset; /* rw */ 
	ev_tstamp interval /* rw */ 
	ev_tstamp (*reschedule_cb)(struct ev_periodic* w, ev_tstamp now) EV_THROWN; /* rw */ 

} ev_periodic;  

/* 
 * Invoked when the given signal has 
 * been received 
 */ 
typedef struct ev_signal {
	EV_WATCHER_LIST(ev_signal)

	int signum; /* ro */ 
} ev_signal; 

typedef struct ev_child {
	EW_WATCHER_LIST(ev_child) 

	int flags; /* private */ 
	int pid; /* ro */ 
	int rpid; /* rw holds the received pid */ 
	int rstatus; /* rw, holds the exit status, and use macros from sys/wait.h */ 
} ev_child; 


#if EV_STAT_ENABLE
	/* st_nlink = 0 means missing file or other errors */ 
	#ifdef _WIN32
		typedef struct _stat64 ev_statdata; 
	#else
		typedef struct stat ev_statdata; 
	#endif

/* 
 * Invoke each tiem the stat data changes for a given path 
 */ 
typedef struct ev_stat {
	EV_WATCHER_LIST(ev_stat)

	ev_timer timer; /* private */ 
	ev_tstamp interval /* ro */ 
	const char* path; /* ro */ 
	ev_statdata prev; /* ro */ 
	ev_statdata attr; /* ro */ 

	int wd; /* wd for inotify, fd for kqueue */ 
} ev_stat;

#endif 

#if EV_IDLE_ENABLE
/* 
 * Invoked when thenothing else needs to be done, keeps the process 
 * from blocking 
 */ 
typedef struct ev_idle {
	EV_WATCHER_LIST(ev_idle) 

} ev_idle;

#endif 

/* 
 * Invoked for each run the mainloop, just before the blocking call 
 * you can still change events in any way you like 
 * revents EV_PREPARE 
 */ 	
typedef struct ev_prepare {
	EV_WATCHER(ev_prepare)
} ev_prepare; 

/* 
 * Invoked for each run of the mainloop, just after the blocking call 
 */ 
typedef struct ev_check {
	EW_WATCHER(ev_check)
} ev_check; 

#if EV_FORK_ENABLE
/* 
 * The callback gets invoked before check if the child process when a fork 
 * was detected 
 */ 
typedef struct ev_fork {
	EV_WATCHER(ev_fork) 
} ev_fork;

#endif 

#if EV_CLEANUP_ENABLE
/* 
 * Is invoked jsut before the loop gets destroyed 
 * revetns EV_CLEANUP
 */
typedef struct ev_cleanup {
	EV_WATCHER(ev_cleanup)
} ev_cleanup; 

#endif 


#if EV_EMBED_ENABLE
/* 
 * used to embed  an event loop inside another 
 * the callback gets invoked when the event loop 
 * has handled events, and can be 0
 */ 
typedef struct ev_embed {
	EV_WATCHER(ev_embed) 

	struct ev_loop* other; /* ro */ 
	ev_io io; 
	ev_prepare prepare; 
	ev_timer timer; 
	ev_check check; 
	ev_periodic periodic; 
	ev_idle idle; 
	ev_fork _fork; 
#if EV_CLEANUP_ENABLE
	ev_cleanup cleanup; /* unused */ 
#endif 
} ev_embed; 
#endif 

#if EV_ASYNC_ENABLE
/* 
 * invoked when sombedy calls ev_async_send on the watcher 
 * reven EV_ASYNC 
 */ 
typedef struct ev_async {
	EV_WATCHER(ev_async) 

	EV_ATOMIC_T sent; /* private */ 

}  ev_async; 

 

#define ev_async_pending(w) (+(w)->sent)
#endif

union ev_any_watcher
{
  struct ev_watcher w;
  struct ev_watcher_list wl;

  struct ev_io io;
  struct ev_timer timer;
  struct ev_periodic periodic;
  struct ev_signal signal;
  struct ev_child child;
#if EV_STAT_ENABLE
  struct ev_stat stat;
#endif
#if EV_IDLE_ENABLE
  struct ev_idle idle;
#endif
  struct ev_prepare prepare;
  struct ev_check check;
#if EV_FORK_ENABLE
  struct ev_fork fork;
#endif
#if EV_CLEANUP_ENABLE
  struct ev_cleanup cleanup;
#endif
#if EV_EMBED_ENABLE
  struct ev_embed embed;
#endif
#if EV_ASYNC_ENABLE
  struct ev_async async;
#endif
};



/* flag bits for ev_default_loop and ev_loop_new */
enum {
  /* the default */
  EVFLAG_AUTO      = 0x00000000U, /* not quite a mask */
  /* flag bits */
  EVFLAG_NOENV     = 0x01000000U, /* do NOT consult environment */
  EVFLAG_FORKCHECK = 0x02000000U, /* check for a fork in each iteration */
  /* debugging/feature disable */
  EVFLAG_NOINOTIFY = 0x00100000U, /* do not attempt to use inotify */
#if EV_COMPAT3
  EVFLAG_NOSIGFD   = 0, /* compatibility to pre-3.9 */
#endif
  EVFLAG_SIGNALFD  = 0x00200000U, /* attempt to use signalfd */
  EVFLAG_NOSIGMASK = 0x00400000U  /* avoid modifying the signal mask */
};

/* method bits to be ored together */
enum {
  EVBACKEND_SELECT  = 0x00000001U, /* about anywhere */
  EVBACKEND_POLL    = 0x00000002U, /* !win */
  EVBACKEND_EPOLL   = 0x00000004U, /* linux */
  EVBACKEND_KQUEUE  = 0x00000008U, /* bsd */
  EVBACKEND_DEVPOLL = 0x00000010U, /* solaris 8 */ /* NYI */
  EVBACKEND_PORT    = 0x00000020U, /* solaris 10 */
  EVBACKEND_ALL     = 0x0000003FU, /* all known backends */
  EVBACKEND_MASK    = 0x0000FFFFU  /* all future backends */
};

#if EV_PROTOTYPES
EV_API_DECL int ev_version_major (void) EV_THROW;
EV_API_DECL int ev_version_minor (void) EV_THROW;

V_API_DECL unsigned int ev_supported_backends (void) EV_THROW;
EV_API_DECL unsigned int ev_recommended_backends (void) EV_THROW;
EV_API_DECL unsigned int ev_embeddable_backends (void) EV_THROW;

EV_API_DECL ev_tstamp ev_time (void) EV_THROW;
EV_API_DECL void ev_sleep (ev_tstamp delay) EV_THROW; /* sleep for a while */


EV_API_DECL void ev_set_allocator (void *(*cb)(void *ptr, long size) EV_THROW) EV_THROW;

EV_API_DECL void ev_set_syserr_cb (void (*cb)(const char *msg) EV_THROW) EV_THROW;
	

#if EV_MULTIPLICITY

EV_API_DECL struct ev_loop *ev_default_loop (unsigned int flags EV_CPP (= 0)) EV_THROW;


#ifdef EV_API_STATIC
EV_API_DECL struct ev_loop *ev_default_loop_ptr;
#endif

EV_INLINE struct ev_loop*
ev_default_loop(void) EV_THROW {
	extern struct ev_loop* ev_default_loop_ptr; 

	return ev_default_loop; 
} 

EV_INLINE int 
ev_is_default_loop(EV_P) EV_THROWN {
	return EV_A == EV_DEFAULT_UC; 
} 

/* 
 * Create and destroy alternative loops that dont' handle 
 * singals 
 */ 
EV_API_DECL struct ev_loop *ev_loop_new (unsigned int flags EV_CPP (= 0)) EV_THROW;

EV_API_DECL ev_tstamp ev_now (EV_P) EV_THROW; /* time w.r.t. timers and the eventloop, updated after each poll */
 
#else

EV_API_DECL int ev_default_loop (unsigned int flags EV_CPP (= 0)) EV_THROW; /* returns true when successful */

EV_API_DECL ev_tstamp ev_rt_now;

EV_INLINE ev_tstamp
ev_now (void) EV_THROW
{
  return ev_rt_now;
}

EV_INLINE int
ev_is_default_loop (void) EV_THROW
{
  return 1;
}

#endif /* multiplicity */


/* destroy event loops, also works for the default loop */
EV_API_DECL void ev_loop_destroy (EV_P);

EV_API_DECL void ev_loop_fork (EV_P) EV_THROW;

EV_API_DECL unsigned int ev_backend (EV_P) EV_THROW; /* backend in use by loop */

EV_API_DECL void ev_now_update (EV_P) EV_THROW; /* update event loop time */


#if EV_WALK_ENABLE
EV_API_DECL void ev_walk (EV_P_ int types, void (*cb)(EV_P_ int type, void *w)) EV_THROW;
#endif
#endif /* prototypes */


/* ev_run flags values */
enum {
  EVRUN_NOWAIT = 1, /* do not block/wait */
  EVRUN_ONCE   = 2  /* block *once* only */
};


/* ev_break how values */
enum {
  EVBREAK_CANCEL = 0, /* undo unloop */
  EVBREAK_ONE    = 1, /* unloop once */
  EVBREAK_ALL    = 2  /* unloop all loops */
};

EV_API_DECL int  ev_run (EV_P_ int flags EV_CPP (= 0));
EV_API_DECL void ev_break (EV_P_ int how EV_CPP (= EVBREAK_ONE)) EV_THROW; /* break out of the loop */


/*
 * ref/unref can be used to add or remove a refcount on the mainloop. every watcher
 * keeps one reference. if you have a long-running watcher you never unregister that
 * should not keep ev_loop from running, unref() after starting, and ref() before stopping.
 */
EV_API_DECL void ev_ref   (EV_P) EV_THROW;
EV_API_DECL void ev_unref (EV_P) EV_THROW;



EV_API_DECL void ev_once (EV_P_ int fd, int events, ev_tstamp timeout, void (*cb)(int revents, void *arg), void *arg) EV_THROW;









#endif