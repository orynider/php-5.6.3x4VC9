/* config.c - ldbm backend configuration file routine */
/* $OpenLDAP: pkg/ldap/servers/slapd/back-ldbm/config.c,v 1.12.8.3 2000/06/13 17:57:34 kurt Exp $ */
/*
 * Copyright 1998-2000 The OpenLDAP Foundation, All Rights Reserved.
 * COPYING RESTRICTIONS APPLY, see COPYRIGHT file
 */

#include "portable.h"

//#include <stdio.h>

#include <ac/socket.h>
#include <ac/string.h>

#include "slap.h"
#include "back-ldbm.h"


int
ldbm_back_db_config(
    Backend	*be,
    const char	*fname,
    int		lineno,
    int		argc,
    char	**argv
)
{
	int rc;
	struct ldbminfo	*li = (struct ldbminfo *) be->be_private;

	if ( li == NULL ) {
		fprintf( stderr, "%s: line %d: ldbm database info is null!\n",
		    fname, lineno );
		return( 1 );
	}

	/* directory where database files live */
	if ( strcasecmp( argv[0], "directory" ) == 0 ) {
		if ( argc < 2 ) {
			fprintf( stderr,
		"%s: line %d: missing dir in \"directory <dir>\" line\n",
			    fname, lineno );
			return( 1 );
		}
		if ( li->li_directory )
			free( li->li_directory );
		li->li_directory = ch_strdup( argv[1] );

	/* mode with which to create new database files */
	} else if ( strcasecmp( argv[0], "mode" ) == 0 ) {
		if ( argc < 2 ) {
			fprintf( stderr,
			"%s: line %d: missing mode in \"mode <mode>\" line\n",
			    fname, lineno );
			return( 1 );
		}
		li->li_mode = strtol( argv[1], NULL, 0 );

	/* attribute to index */
	} else if ( strcasecmp( argv[0], "index" ) == 0 ) {
		if ( argc < 2 ) {
			fprintf( stderr,
"%s: line %d: missing attr in \"index <attr> [pres,eq,approx,sub]\" line\n",
			    fname, lineno );
			return( 1 );
		} else if ( argc > 3 ) {
			fprintf( stderr,
"%s: line %d: extra junk after \"index <attr> [pres,eq,approx,sub]\" line (ignored)\n",
			    fname, lineno );
		}
		rc = attr_index_config( li, fname, lineno, argc - 1, &argv[1] );

		if( rc != LDAP_SUCCESS ) return 1;

	/* size of the cache in entries */
	} else if ( strcasecmp( argv[0], "cachesize" ) == 0 ) {
		if ( argc < 2 ) {
			fprintf( stderr,
		"%s: line %d: missing size in \"cachesize <size>\" line\n",
			    fname, lineno );
			return( 1 );
		}
		li->li_cache.c_maxsize = atoi( argv[1] );

	/* size of each dbcache in bytes */
	} else if ( strcasecmp( argv[0], "dbcachesize" ) == 0 ) {
		if ( argc < 2 ) {
			fprintf( stderr,
		"%s: line %d: missing size in \"dbcachesize <size>\" line\n",
			    fname, lineno );
			return( 1 );
		}
		li->li_dbcachesize = atoi( argv[1] );

	/* no locking (not safe) */
	} else if ( strcasecmp( argv[0], "dbnolocking" ) == 0 ) {
		li->li_dblocking = 0;

	/* no write sync (not safe) */
	} else if ( ( strcasecmp( argv[0], "dbnosync" ) == 0 )
		|| ( strcasecmp( argv[0], "dbcachenowsync" ) == 0 ) )
	{
		li->li_dbwritesync = 0;

	/* anything else */
	} else {
		fprintf( stderr,
"%s: line %d: unknown directive \"%s\" in ldbm database definition (ignored)\n",
		    fname, lineno, argv[0] );
	}

	return 0;
}
