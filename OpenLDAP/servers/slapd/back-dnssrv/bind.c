/* bind.c - DNS SRV backend bind function */
/* $OpenLDAP: pkg/ldap/servers/slapd/back-dnssrv/bind.c,v 1.7.2.2 2000/06/17 16:16:59 kurt Exp $ */
/*
 * Copyright 2000 The OpenLDAP Foundation, All Rights Reserved.
 * COPYING RESTRICTIONS APPLY, see COPYRIGHT file
 */


#include "portable.h"

//#include <stdio.h>

#include <ac/socket.h>
#include <ac/string.h>

#include "slap.h"
#include "external.h"

int
dnssrv_back_bind(
    Backend		*be,
    Connection		*conn,
    Operation		*op,
    const char		*dn,
    const char		*ndn,
    int			method,
    struct berval	*cred,
	char		**edn )
{
	Debug( LDAP_DEBUG_TRACE, "DNSSRV: bind %s (%d)\n",
		dn == NULL ? "" : dn, 
		method, NULL );
		
	if( method == LDAP_AUTH_SIMPLE && cred != NULL && cred->bv_len ) {
		Statslog( LDAP_DEBUG_STATS,
		   	"conn=%ld op=%d DNSSRV BIND dn=\"%s\" provided passwd\n",
	   		 op->o_connid, op->o_opid,
			dn == NULL ? "" : dn , 0, 0 );

		Debug( LDAP_DEBUG_TRACE,
			"DNSSRV: BIND dn=\"%s\" provided cleartext password\n",
			dn == NULL ? "" : dn, 0, 0 );

		send_ldap_result( conn, op, LDAP_UNWILLING_TO_PERFORM,
			NULL, "you shouldn\'t send strangers your password",
			NULL, NULL );

	} else {
		Debug( LDAP_DEBUG_TRACE, "DNSSRV: BIND dn=\"%s\"\n",
			dn == NULL ? "" : dn, 0, 0 );

		send_ldap_result( conn, op, LDAP_UNWILLING_TO_PERFORM,
			NULL, "anonymous bind expected",
			NULL, NULL );
	}

	return 1;
}
