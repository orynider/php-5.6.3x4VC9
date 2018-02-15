/* close.c - close ldbm backend */
/* $OpenLDAP: pkg/ldap/servers/slapd/back-ldbm/close.c,v 1.6.8.3 2000/06/13 17:57:34 kurt Exp $ */
/*
 * Copyright 1998-2000 The OpenLDAP Foundation, All Rights Reserved.
 * COPYING RESTRICTIONS APPLY, see COPYRIGHT file
 */

#include "portable.h"

//#include <stdio.h>

#include <ac/socket.h>

#include "slap.h"
#include "back-ldbm.h"

int
ldbm_back_db_close( Backend *be )
{
	Debug( LDAP_DEBUG_TRACE, "ldbm backend syncing\n", 0, 0, 0 );
	ldbm_cache_flush_all( be );
	Debug( LDAP_DEBUG_TRACE, "ldbm backend done syncing\n", 0, 0, 0 );

	cache_release_all( &((struct ldbminfo *) be->be_private)->li_cache );

	return 0;
}
