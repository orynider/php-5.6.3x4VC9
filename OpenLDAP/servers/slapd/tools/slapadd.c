/* $OpenLDAP: pkg/ldap/servers/slapd/tools/slapadd.c,v 1.5.2.8 2000/10/30 18:16:09 kurt Exp $ */
/*
 * Copyright 1998-2000 The OpenLDAP Foundation, All Rights Reserved.
 * COPYING RESTRICTIONS APPLY, see COPYRIGHT file
 */
#include "portable.h"

//#include <stdio.h>

#include <ac/stdlib.h>

#include <ac/ctype.h>
#include <ac/string.h>
#include <ac/socket.h>
#include <ac/unistd.h>

#include "slapcommon.h"

int
main( int argc, char **argv )
{
	char		*buf;
	int         lineno;
	int         lmax;
	int			rc = EXIT_SUCCESS;

	slap_tool_init( "slapadd", SLAPADD, argc, argv );

	if( !be->be_entry_open ||
		!be->be_entry_close ||
		!be->be_entry_put )
	{
		fprintf( stderr, "%s: database doesn't support necessary operations.\n",
			progname );
		exit( EXIT_FAILURE );
	}

	buf = NULL;
	lmax = 0;
	lineno = 0;

	if( be->be_entry_open( be, 1 ) != 0 ) {
		fprintf( stderr, "%s: could not open database.\n",
			progname );
		exit( EXIT_FAILURE );
	}

	while( ldif_read_record( ldiffp, &lineno, &buf, &lmax ) ) {
		ID id;
		Entry *e = str2entry( buf );

		if( e == NULL ) {
			fprintf( stderr, "%s: could not parse entry (line=%d)\n",
				progname, lineno );
			rc = EXIT_FAILURE;
			if( continuemode ) continue;
			break;
		}

		/* make sure the DN is valid */
		if( dn_normalize( e->e_ndn ) == NULL ) {
			fprintf( stderr, "%s: invalid dn=\"%s\" (line=%d)\n",
				progname, e->e_dn, lineno );
			rc = EXIT_FAILURE;
			entry_free( e );
			if( continuemode ) continue;
			break;
		}

		/* make sure the DN is not empty */
		if( e->e_ndn == '\0' ) {
			fprintf( stderr, "%s: empty dn=\"%s\" (line=%d)\n",
				progname, e->e_dn, lineno );
			rc = EXIT_FAILURE;
			entry_free( e );
			if( continuemode ) continue;
			break;
		}

		/* check backend */
		if( select_backend( e->e_ndn, is_entry_referral(e) ) != be )
		{
			fprintf( stderr, "%s: database (%s) not configured to "
				"hold dn=\"%s\" (line=%d)\n",
				progname,
				be ? be->be_suffix[0] : "<none>",
				e->e_dn, lineno );
			rc = EXIT_FAILURE;
			entry_free( e );
			if( continuemode ) continue;
			break;
		}

		if( global_schemacheck ) {
			/* check schema */
			const char *text;
			if ( entry_schema_check( e, NULL, &text ) != LDAP_SUCCESS ) {
				fprintf( stderr, "%s: dn=\"%s\" (line=%d): %s\n",
					progname, e->e_dn, lineno, text );
				rc = EXIT_FAILURE;
				entry_free( e );
				if( continuemode ) continue;
				break;
			}
		}

		id = be->be_entry_put( be, e );
		if( id == NOID ) {
			fprintf( stderr, "%s: could not add entry dn=\"%s\" (line=%d)\n",
				progname, e->e_dn, lineno );
			rc = EXIT_FAILURE;
			entry_free( e );
			if( continuemode ) continue;
			break;

		}
		
		if ( verbose ) {
			fprintf( stderr, "added: \"%s\" (%08lx)\n",
				e->e_dn, (long) id );
		}

		entry_free( e );
	}

	ch_free( buf );

	be->be_entry_close( be );

	if( be->be_sync ) {
		be->be_sync( be );
	}

	slap_tool_destroy();
	return rc;
}
