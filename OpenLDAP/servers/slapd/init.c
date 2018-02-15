/* init.c - initialize various things */
/* $OpenLDAP: pkg/ldap/servers/slapd/init.c,v 1.18.2.9 2000/10/11 02:41:31 kurt Exp $ */
/*
 * Copyright 1998-2000 The OpenLDAP Foundation, All Rights Reserved.
 * COPYING RESTRICTIONS APPLY, see COPYRIGHT file
 */

#include "portable.h"

//#include <stdio.h>

#include <ac/socket.h>
#include <ac/string.h>
#include <ac/time.h>

#include "slap.h"

/*
 * read-only global variables or variables only written by the listener
 * thread (after they are initialized) - no need to protect them with a mutex.
 */
int		slap_debug = 0;

#ifdef LDAP_DEBUG
int		ldap_syslog = LDAP_DEBUG_STATS;
#else
int		ldap_syslog;
#endif

#ifdef LOG_DEBUG
int		ldap_syslog_level = LOG_DEBUG;
#endif

struct berval **default_referral = NULL;
int		g_argc;
char		**g_argv;

/*
 * global variables that need mutex protection
 */
ldap_pvt_thread_pool_t	connection_pool;
ldap_pvt_thread_mutex_t	gmtime_mutex;
#if defined( SLAPD_CRYPT ) || defined( SLAPD_SPASSWD )
ldap_pvt_thread_mutex_t	passwd_mutex;
#endif

int				num_conns;
long			num_ops_initiated;
long			num_ops_completed;
ldap_pvt_thread_mutex_t	num_ops_mutex;

long			num_entries_sent;
long			num_refs_sent;
long			num_bytes_sent;
long			num_pdu_sent;
ldap_pvt_thread_mutex_t	num_sent_mutex;
/*
 * these mutexes must be used when calling the entry2str()
 * routine since it returns a pointer to static data.
 */
ldap_pvt_thread_mutex_t	entry2str_mutex;
ldap_pvt_thread_mutex_t	replog_mutex;

static const char* slap_name = NULL;
int slapMode = SLAP_UNDEFINED_MODE;

static ldap_pvt_thread_mutex_t	currenttime_mutex;

int
slap_init( int mode, const char *name )
{
	int rc;

	assert( mode );

	if( slapMode != SLAP_UNDEFINED_MODE ) {
		Debug( LDAP_DEBUG_ANY,
	   	 "%s init: init called twice (old=%d, new=%d)\n",
	   	 name, slapMode, mode );
		return 1;
	}

	slapMode = mode;

	switch ( slapMode & SLAP_MODE ) {
		case SLAP_SERVER_MODE:
		case SLAP_TOOL_MODE:
			Debug( LDAP_DEBUG_TRACE,
				"%s init: initiated %s.\n",	name,
				(mode & SLAP_MODE) == SLAP_TOOL_MODE ? "tool" : "server",
				0 );

			slap_name = name;
	
			(void) ldap_pvt_thread_initialize();

			ldap_pvt_thread_pool_init(&connection_pool, SLAP_MAX_WORKER_THREADS, 0);

			ldap_pvt_thread_mutex_init( &currenttime_mutex );
			ldap_pvt_thread_mutex_init( &entry2str_mutex );
			ldap_pvt_thread_mutex_init( &replog_mutex );
			ldap_pvt_thread_mutex_init( &num_ops_mutex );
			ldap_pvt_thread_mutex_init( &num_sent_mutex );

			ldap_pvt_thread_mutex_init( &gmtime_mutex );
#if defined( SLAPD_CRYPT ) || defined( SLAPD_SPASSWD )
			ldap_pvt_thread_mutex_init( &passwd_mutex );
#endif

			rc = slap_sasl_init();

			if( rc == 0 ) {
				rc = backend_init( );
			}
			break;

		default:
			Debug( LDAP_DEBUG_ANY,
	   	 		"%s init: undefined mode (%d).\n", name, mode, 0 );
			rc = 1;
			break;
	}

	return rc;
}

int slap_startup( Backend *be )
{
	int rc;

	Debug( LDAP_DEBUG_TRACE,
		"%s startup: initiated.\n",
		slap_name, 0, 0 );

	rc = backend_startup( be );

	return rc;
}

int slap_shutdown( Backend *be )
{
	int rc;

	Debug( LDAP_DEBUG_TRACE,
		"%s shutdown: initiated\n",
		slap_name, 0, 0 );

	slap_sasl_destroy();

	/* let backends do whatever cleanup they need to do */
	rc = backend_shutdown( be ); 

	return rc;
}

int slap_destroy(void)
{
	int rc;

	Debug( LDAP_DEBUG_TRACE,
		"%s shutdown: freeing system resources.\n",
		slap_name, 0, 0 );

	rc = backend_destroy();

	entry_destroy();

	ldap_pvt_thread_destroy();

	/* should destory the above mutex */
	return rc;
}

/* should create a utils.c for these */
time_t slap_get_time(void)
{
	time_t t;
	ldap_pvt_thread_mutex_lock( &currenttime_mutex );
	time( &t );
	ldap_pvt_thread_mutex_unlock( &currenttime_mutex );
	return t;
}
