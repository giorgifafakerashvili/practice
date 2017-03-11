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




#endif