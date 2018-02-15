/* $OpenLDAP: pkg/ldap/libraries/libldap/references.c,v 1.10.4.5 2002/01/04 20:38:21 kurt Exp $ */
/*
 * Copyright 1998-2002 The OpenLDAP Foundation, All Rights Reserved.
 * COPYING RESTRICTIONS APPLY, see COPYRIGHT file
 */
/*
 *  references.c
 */

#include "portable.h"

#include <stdio.h>

#include <ac/stdlib.h>

#include <ac/socket.h>
#include <ac/string.h>
#include <ac/time.h>

#include "ldap-int.h"

LDAPMessage *
ldap_first_reference( LDAP *ld, LDAPMessage *chain )
{
	assert( ld != NULL );
	assert( LDAP_VALID( ld ) );
	assert( chain !=  NULL );

	if ( ld == NULL || chain == NULL ) {
		return NULL;
	}

	return chain->lm_msgtype == LDAP_RES_SEARCH_REFERENCE
		? chain
		: ldap_next_reference( ld, chain );
}

LDAPMessage *
ldap_next_reference( LDAP *ld, LDAPMessage *ref )
{
	assert( ld != NULL );
	assert( LDAP_VALID( ld ) );
	assert( ref !=  NULL );

	if ( ld == NULL || ref == NULL ) {
		return NULL;
	}

	for (
		ref = ref->lm_chain;
		ref != NULL;
		ref = ref->lm_chain )
	{
		if( ref->lm_msgtype == LDAP_RES_SEARCH_REFERENCE ) {
			return( ref );
		}
	}

	return( NULL );
}

int
ldap_count_references( LDAP *ld, LDAPMessage *chain )
{
	int	i;

	assert( ld != NULL );
	assert( LDAP_VALID( ld ) );
	assert( chain !=  NULL );

	if ( ld == NULL ) {
		return -1;
	}

	
	for ( i = 0; chain != NULL; chain = chain->lm_chain ) {
		if( chain->lm_msgtype == LDAP_RES_SEARCH_REFERENCE ) {
			i++;
		}
	}

	return( i );
}

int
ldap_parse_reference( 
	LDAP            *ld,    
	LDAPMessage     *ref,
	char            ***referralsp,
	LDAPControl     ***serverctrls,
	int             freeit)
{
	BerElement be;
	char **refs = NULL;
	int rc;

	assert( ld != NULL );
	assert( LDAP_VALID( ld ) );
	assert( ref !=  NULL );

	if( ld == NULL || ref == NULL ||
		ref->lm_msgtype != LDAP_RES_SEARCH_REFERENCE )
	{
		return LDAP_PARAM_ERROR;
	}

	/* make a private copy of BerElement */
	AC_MEMCPY(&be, ref->lm_ber, sizeof(be));
	
	if ( ber_scanf( &be, "{v" /*}*/, &refs ) == LBER_ERROR ) {
		rc = LDAP_DECODING_ERROR;
		goto free_and_return;
	}

	if ( serverctrls == NULL ) {
		rc = LDAP_SUCCESS;
		goto free_and_return;
	}

	if ( ber_scanf( &be, /*{*/ "}" ) == LBER_ERROR ) {
		rc = LDAP_DECODING_ERROR;
		goto free_and_return;
	}

	rc = ldap_int_get_controls( &be, serverctrls );

free_and_return:

	if( referralsp != NULL ) {
		/* provide references regradless of return code */
		*referralsp = refs;

	} else {
		LDAP_VFREE( refs );
	}

	if( freeit ) {
		ldap_msgfree( ref );
	}

	if( rc != LDAP_SUCCESS ) {
		ld->ld_errno = rc;

		if( ld->ld_matched != NULL ) {
			LDAP_FREE( ld->ld_matched );
			ld->ld_matched = NULL;
		}

		if( ld->ld_error != NULL ) {
			LDAP_FREE( ld->ld_error );
			ld->ld_error = NULL;
		}
	}

	return rc;
}
