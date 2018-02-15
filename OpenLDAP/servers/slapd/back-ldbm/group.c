/* group.c - ldbm backend acl group routine */
/* $OpenLDAP: pkg/ldap/servers/slapd/back-ldbm/group.c,v 1.17.2.4 2000/06/17 16:16:59 kurt Exp $ */
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
#include "proto-back-ldbm.h"


/* return 0 IFF op_dn is a value in member attribute
 * of entry with gr_dn AND that entry has an objectClass
 * value of groupOfNames
 */
int
ldbm_back_group(
	Backend	*be,
	Entry	*target,
	const char	*gr_ndn,
	const char	*op_ndn,
	ObjectClass *group_oc,
	AttributeDescription *group_at
)
{
	struct ldbminfo *li = (struct ldbminfo *) be->be_private;    
	Entry        *e;
	int          rc = 1;
	Attribute   *attr;
	struct berval bv;

	AttributeDescription *ad_objectClass = slap_schema.si_ad_objectClass;
	const char *group_oc_name = NULL;
	const char *group_at_name = group_at->ad_cname->bv_val;

	if( group_oc->soc_names && group_oc->soc_names[0] ) {
		group_oc_name = group_oc->soc_names[0];
	} else {
		group_oc_name = group_oc->soc_oid;
	}

	Debug( LDAP_DEBUG_ARGS,
		"=> ldbm_back_group: gr dn: \"%s\"\n",
		gr_ndn, 0, 0 ); 
	Debug( LDAP_DEBUG_ARGS,
		"=> ldbm_back_group: op dn: \"%s\"\n",
		op_ndn, 0, 0 ); 
	Debug( LDAP_DEBUG_ARGS,
		"=> ldbm_back_group: oc: \"%s\" at: \"%s\"\n", 
		group_oc_name, group_at_name, 0 ); 

	Debug( LDAP_DEBUG_ARGS,
		"=> ldbm_back_group: tr dn: \"%s\"\n",
		target->e_ndn, 0, 0 ); 

	if (strcmp(target->e_ndn, gr_ndn) == 0) {
		/* we already have a LOCKED copy of the entry */
		e = target;
        	Debug( LDAP_DEBUG_ARGS,
			"=> ldbm_back_group: target is group: \"%s\"\n",
			gr_ndn, 0, 0 );

	} else {
		/* can we find group entry with reader lock */
		if ((e = dn2entry_r(be, gr_ndn, NULL )) == NULL) {
			Debug( LDAP_DEBUG_ACL,
				"=> ldbm_back_group: cannot find group: \"%s\"\n",
					gr_ndn, 0, 0 ); 
			return( 1 );
		}
		
		Debug( LDAP_DEBUG_ACL,
			"=> ldbm_back_group: found group: \"%s\"\n",
			gr_ndn, 0, 0 ); 
    }

	/* find it's objectClass and member attribute values
	 * make sure this is a group entry
	 * finally test if we can find op_dn in the member attribute value list *
	 */
        
	rc = 1;
        
	
	if( is_entry_alias( e ) ) {
		Debug( LDAP_DEBUG_ACL,
			"<= ldbm_back_group: group is an alias\n", 0, 0, 0 );
		goto return_results;
	}

	if( is_entry_referral( e ) ) {
		Debug( LDAP_DEBUG_ACL,
			"<= ldbm_back_group: group is an referral\n", 0, 0, 0 );
		goto return_results;
	}

	if( !is_entry_objectclass( e, group_oc ) ) {
		Debug( LDAP_DEBUG_ACL,
			"<= ldbm_back_group: failed to find %s in objectClass\n", 
				group_oc_name, 0, 0 ); 
		goto return_results;
	}

	if ((attr = attr_find(e->e_attrs, group_at)) == NULL) {
		Debug( LDAP_DEBUG_ACL,
			"<= ldbm_back_group: failed to find %s\n",
			group_at_name, 0, 0 ); 
		goto return_results;
	}

	Debug( LDAP_DEBUG_ACL,
		"<= ldbm_back_group: found objectClass %s and %s\n",
		group_oc_name, group_at_name, 0 ); 

	bv.bv_val = (char *) op_ndn;
	bv.bv_len = strlen( op_ndn );         

	if( value_find( group_at, attr->a_vals, &bv ) != LDAP_SUCCESS ) {
		Debug( LDAP_DEBUG_ACL,
			"<= ldbm_back_group: \"%s\" not in \"%s\": %s\n", 
			op_ndn, gr_ndn, group_at_name ); 
		goto return_results;
	}



	Debug( LDAP_DEBUG_ACL,
		"<= ldbm_back_group: \"%s\" is in \"%s\": %s\n", 
		op_ndn, gr_ndn, group_at_name ); 

	rc = 0;

return_results:
	if( target != e ) {
		/* free entry and reader lock */
		cache_return_entry_r( &li->li_cache, e );                 
	}

	Debug( LDAP_DEBUG_TRACE, "ldbm_back_group: rc=%d\n", rc, 0, 0 ); 
	return(rc);
}

