/* $OpenLDAP: pkg/ldap/servers/slurpd/reject.c,v 1.4.8.2 2000/06/13 17:57:41 kurt Exp $ */
/*
 * Copyright (c) 1996 Regents of the University of Michigan.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and that due credit is given
 * to the University of Michigan at Ann Arbor. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 */


/*
 * reject.c - routines to write replication records to reject files.
 * An Re struct is writted to a reject file if it cannot be propagated
 * to a replica LDAP server.
 */

#include "portable.h"

//#include <stdio.h>

#include <ac/errno.h>
#include <ac/unistd.h>

#include <sys/stat.h>
#include <fcntl.h>

#include "slurp.h"
#include "globals.h"

/*
 * Write a replication record to a reject file.  The reject file has the
 * same name as the replica's private copy of the file but with ".rej"
 * appended (e.g. "/usr/tmp/<hostname>:<port>.rej")
 *
 * If errmsg is non-NULL, use that as the error message in the reject
 * file.  Otherwise, use ldap_err2string( lderr ).
 */
void
write_reject(
    Ri		*ri,
    Re		*re,
    int		lderr,
    char	*errmsg
)
{
    char	rejfile[ MAXPATHLEN ];
    FILE	*rfp, *lfp;
    int		rc;

    ldap_pvt_thread_mutex_lock( &sglob->rej_mutex );
    sprintf( rejfile, "%s/%s:%d.rej", sglob->slurpd_rdir,
	    ri->ri_hostname, ri->ri_port );

    if ( access( rejfile, F_OK ) < 0 ) {
	/* Doesn't exist - try to create */
	int rjfd;
	if (( rjfd = open( rejfile, O_RDWR | O_APPEND | O_CREAT,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP )) < 0 ) {
	    Debug( LDAP_DEBUG_ANY,
		"Error: write_reject: Cannot create \"%s\": %s\n",
		rejfile, sys_errlist[ errno ], 0 );
	    ldap_pvt_thread_mutex_unlock( &sglob->rej_mutex );
	    return;
	} else {
	    close( rjfd );
	}
    }
    if (( rc = acquire_lock( rejfile, &rfp, &lfp )) < 0 ) {
	Debug( LDAP_DEBUG_ANY, "Error: cannot open reject file \"%s\"\n",
		rejfile, 0, 0 );
    } else {
	fseek( rfp, 0, 2 );
	if ( errmsg != NULL ) {
	    fprintf( rfp, "%s: %s\n", ERROR_STR, errmsg );
	} else {
	    fprintf( rfp, "%s: %s\n", ERROR_STR, ldap_err2string( lderr ));
	}
	if ((rc = re->re_write( ri, re, rfp )) < 0 ) {
	    Debug( LDAP_DEBUG_ANY,
		    "Error: cannot write reject file \"%s\"\n",
		    rejfile, 0, 0 );
	}
	(void) relinquish_lock( rejfile, rfp, lfp );
	Debug( LDAP_DEBUG_ANY,
		"Error: ldap operation failed, data written to \"%s\"\n",
		rejfile, 0, 0 );
    }
    ldap_pvt_thread_mutex_unlock( &sglob->rej_mutex );
    return;
}

