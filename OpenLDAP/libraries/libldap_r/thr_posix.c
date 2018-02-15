/* $OpenLDAP: pkg/ldap/libraries/libldap_r/thr_posix.c,v 1.9.8.4 2000/07/06 15:37:48 kurt Exp $ */
/*
 * Copyright 1998-2000 The OpenLDAP Foundation, Redwood City, California, USA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted only
 * as authorized by the OpenLDAP Public License.  A copy of this
 * license is available at http://www.OpenLDAP.org/license.html or
 * in file LICENSE in the top-level directory of the distribution.
 */

/* thr_posix.c - wrapper around posix and posixish thread implementations.
 */

#include "portable.h"

#if defined( HAVE_PTHREADS )

#include <ac/errno.h>

#include "ldap_pvt_thread.h"


#if HAVE_PTHREADS_D4
#  define LDAP_INT_THREAD_ATTR_DEFAULT		pthread_attr_default
#  define LDAP_INT_THREAD_CONDATTR_DEFAULT	pthread_condattr_default
#  define LDAP_INT_THREAD_MUTEXATTR_DEFAULT	pthread_mutexattr_default
#else
#  define LDAP_INT_THREAD_ATTR_DEFAULT		NULL
#  define LDAP_INT_THREAD_CONDATTR_DEFAULT	NULL
#  define LDAP_INT_THREAD_MUTEXATTR_DEFAULT	NULL
#endif


int
ldap_int_thread_initialize( void )
{
	return 0;
}

int
ldap_int_thread_destroy( void )
{
#ifdef HAVE_PTHREAD_KILL_OTHER_THREADS_NP
	/* LinuxThreads: kill clones */
	pthread_kill_other_threads_np();
#endif
	return 0;
}

#ifdef LDAP_THREAD_HAVE_SETCONCURRENCY
int
ldap_pvt_thread_set_concurrency(int n)
{
#ifdef HAVE_PTHREAD_SETCONCURRENCY
	return pthread_setconcurrency( n );
#elif HAVE_THR_SETCONCURRENCY
	return thr_setconcurrency( n );
#else
	return 0;
#endif
}
#endif

#ifdef LDAP_THREAD_HAVE_GETCONCURRENCY
int
ldap_pvt_thread_get_concurrency(void)
{
#ifdef HAVE_PTHREAD_GETCONCURRENCY
	return pthread_getconcurrency();
#elif HAVE_THR_GETCONCURRENCY
	return thr_getconcurrency();
#else
	return 0;
#endif
}
#endif

int 
ldap_pvt_thread_create( ldap_pvt_thread_t * thread,
	int detach,
	void *(*start_routine)( void * ),
	void *arg)
{
	int rtn;
#if defined(HAVE_PTHREADS_FINAL) && defined(PTHREAD_CREATE_UNDETACHED)
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	if (!detach)
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_UNDETACHED);

	rtn = pthread_create( thread, &attr, start_routine, arg );
#else
	rtn = pthread_create( thread, LDAP_INT_THREAD_ATTR_DEFAULT,
				  start_routine, arg );
#endif

	if( detach ) {
#ifdef HAVE_PTHREADS_FINAL
		pthread_detach( *thread );
#else
		pthread_detach( thread );
#endif
	}
	return rtn;
}

void 
ldap_pvt_thread_exit( void *retval )
{
	pthread_exit( retval );
}

int 
ldap_pvt_thread_join( ldap_pvt_thread_t thread, void **thread_return )
{
#if !defined( HAVE_PTHREADS_FINAL )
	void *dummy;
	if (thread_return==NULL)
	  thread_return=&dummy;
#endif	
	return pthread_join( thread, thread_return );
}

int 
ldap_pvt_thread_kill( ldap_pvt_thread_t thread, int signo )
{
#ifdef HAVE_PTHREAD_KILL
	return pthread_kill( thread, signo );
#else
	/* pthread package with DCE */
	if (kill( getpid(), signo )<0)
		return errno;
	return 0;
#endif
}

int 
ldap_pvt_thread_yield( void )
{
#ifdef _POSIX_THREAD_IS_GNU_PTH
	sched_yield();
	return 0;

#elif HAVE_SCHED_YIELD
	return sched_yield();

#elif HAVE_PTHREAD_YIELD
	pthread_yield();
	return 0;

#elif HAVE_THR_YIELD
	return thr_yield();

#else
	return 0;
#endif   
}

int 
ldap_pvt_thread_cond_init( ldap_pvt_thread_cond_t *cond )
{
	return pthread_cond_init( cond, LDAP_INT_THREAD_CONDATTR_DEFAULT );
}

int 
ldap_pvt_thread_cond_destroy( ldap_pvt_thread_cond_t *cond )
{
	return pthread_cond_destroy( cond );
}
	
int 
ldap_pvt_thread_cond_signal( ldap_pvt_thread_cond_t *cond )
{
	return pthread_cond_signal( cond );
}

int
ldap_pvt_thread_cond_broadcast( ldap_pvt_thread_cond_t *cond )
{
	return pthread_cond_broadcast( cond );
}

int 
ldap_pvt_thread_cond_wait( ldap_pvt_thread_cond_t *cond, 
		      ldap_pvt_thread_mutex_t *mutex )
{
	return pthread_cond_wait( cond, mutex );
}

int 
ldap_pvt_thread_mutex_init( ldap_pvt_thread_mutex_t *mutex )
{
	return pthread_mutex_init( mutex, LDAP_INT_THREAD_MUTEXATTR_DEFAULT );
}

int 
ldap_pvt_thread_mutex_destroy( ldap_pvt_thread_mutex_t *mutex )
{
	return pthread_mutex_destroy( mutex );
}

int 
ldap_pvt_thread_mutex_lock( ldap_pvt_thread_mutex_t *mutex )
{
	return pthread_mutex_lock( mutex );
}

int 
ldap_pvt_thread_mutex_trylock( ldap_pvt_thread_mutex_t *mutex )
{
	return pthread_mutex_trylock( mutex );
}

int 
ldap_pvt_thread_mutex_unlock( ldap_pvt_thread_mutex_t *mutex )
{
	return pthread_mutex_unlock( mutex );
}

#ifdef LDAP_THREAD_HAVE_RDWR
#ifdef HAVE_PTHREAD_RWLOCK_DESTROY
int 
ldap_pvt_thread_rdwr_init( ldap_pvt_thread_rdwr_t *rw )
{
	return pthread_rwlock_init( rw, NULL );
}

int 
ldap_pvt_thread_rdwr_destroy( ldap_pvt_thread_rdwr_t *rw )
{
	return pthread_rwlock_destroy( rw );
}

int ldap_pvt_thread_rdwr_rlock( ldap_pvt_thread_rdwr_t *rw )
{
	return pthread_rwlock_rdlock( rw );
}

int ldap_pvt_thread_rdwr_rtrylock( ldap_pvt_thread_rdwr_t *rw )
{
	return pthread_rwlock_tryrdlock( rw );
}

int ldap_pvt_thread_rdwr_runlock( ldap_pvt_thread_rdwr_t *rw )
{
	return pthread_rwlock_unlock( rw );
}

int ldap_pvt_thread_rdwr_wlock( ldap_pvt_thread_rdwr_t *rw )
{
	return pthread_rwlock_wrlock( rw );
}

int ldap_pvt_thread_rdwr_wtrylock( ldap_pvt_thread_rdwr_t *rw )
{
	return pthread_rwlock_trywrlock( rw );
}

int ldap_pvt_thread_rdwr_wunlock( ldap_pvt_thread_rdwr_t *rw )
{
	return pthread_rwlock_unlock( rw );
}

#endif /* HAVE_PTHREAD_RDLOCK_DESTROY */
#endif /* LDAP_THREAD_HAVE_RDWR */
#endif /* HAVE_PTHREADS */

