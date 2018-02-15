/*
 *	 Copyright 1999, Dmitry Kovalev <mit@openldap.org>, All rights reserved.
 *
 *	 Redistribution and use in source and binary forms are permitted only
 *	 as authorized by the OpenLDAP Public License.	A copy of this
 *	 license is available at http://www.OpenLDAP.org/license.html or
 *	 in file LICENSE in the top-level directory of the distribution.
 */

#include "portable.h"

#ifdef SLAPD_SQL

//#include <stdio.h>
#include <sys/types.h>
#include "slap.h"
#include "back-sql.h"
#include "sql-wrap.h"
#include "util.h"
#include "entry-id.h"

void backsql_init_search(backsql_srch_info *bsi,backsql_info *bi,char *nbase,int scope,
		 int slimit,int tlimit,time_t stoptime,Filter *filter,
		 SQLHDBC dbh,BackendDB *be,Connection *conn,Operation *op,char **attrs);

int backsql_bind(BackendDB *be,Connection *conn,Operation *op,
	const char *dn,const char *ndn,int method,struct berval *cred,char** edn)
{
 backsql_info *bi=(backsql_info*)be->be_private;
 backsql_entryID user_id,*res;
 SQLHDBC dbh;
 AttributeDescription *password = slap_schema.si_ad_userPassword;
 Entry		*e,user_entry;
 Attribute	*a;
 backsql_srch_info bsi;
 
 Debug(LDAP_DEBUG_TRACE,"==>backsql_bind()\n",0,0,0);
 
 if ( be_isroot_pw( be, conn, ndn, cred ) )
    {
     *edn=ch_strdup(be_root_dn(be));
     Debug(LDAP_DEBUG_TRACE,"<==backsql_bind() root bind\n",0,0,0);
     return LDAP_SUCCESS;
    }
 
 *edn=ch_strdup(ndn);
 
 if (method == LDAP_AUTH_SIMPLE)
  {	 
   dbh=backsql_get_db_conn(be,conn);

   if (!dbh)
    {
     Debug(LDAP_DEBUG_TRACE,"backsql_bind(): could not get connection handle - exiting\n",0,0,0);
     send_ldap_result(conn,op,LDAP_OTHER,"","SQL-backend error",NULL,NULL);
     return 1;
    }
  
   res=backsql_dn2id(bi,&user_id,dbh,ndn);
   if (res==NULL)
    {
     Debug(LDAP_DEBUG_TRACE,"backsql_bind(): could not retrieve bind dn id - no such entry\n",0,0,0);
     send_ldap_result( conn, op, LDAP_INVALID_CREDENTIALS,NULL, NULL, NULL, NULL );
     return 1;
    }
    
   backsql_init_search(&bsi,bi,(char*)ndn,LDAP_SCOPE_BASE,-1,-1,-1,NULL,dbh,
		 be,conn,op,NULL);
   e=backsql_id2entry(&bsi,&user_entry,&user_id);
   if (e==NULL)
    {
     Debug(LDAP_DEBUG_TRACE,"backsql_bind(): error in backsql_id2entry() - auth failed\n",0,0,0);
     send_ldap_result( conn, op, LDAP_OTHER,NULL, NULL, NULL, NULL );
     return 1;
    }
    
   if ( ! access_allowed( be, conn, op, e,password, NULL, ACL_AUTH ) )
    {
     send_ldap_result( conn, op, LDAP_INSUFFICIENT_ACCESS, NULL, NULL, NULL, NULL );
     return 1;
    }

   if ( (a = attr_find( e->e_attrs, password )) == NULL )
    {
     send_ldap_result( conn, op, LDAP_INAPPROPRIATE_AUTH, NULL, NULL, NULL, NULL );
     return 1;
    }

   if ( slap_passwd_check( conn, a, cred ) != 0 ) 
    {
     send_ldap_result( conn, op, LDAP_INVALID_CREDENTIALS,NULL, NULL, NULL, NULL );
     return 1;
    }
  }  
 else /*method != SIMPLE */
  {
   send_ldap_result( conn, op, LDAP_STRONG_AUTH_NOT_SUPPORTED,
		    NULL, "authentication method not supported", NULL, NULL );
   return 1;
  }
 Debug(LDAP_DEBUG_TRACE,"<==backsql_bind()\n",0,0,0);
 return 0;
}
 
int backsql_unbind(BackendDB *be,Connection *conn,Operation *op)
{
 Debug(LDAP_DEBUG_TRACE,"==>backsql_unbind()\n",0,0,0);
 send_ldap_result(conn,op,LDAP_SUCCESS,NULL,NULL,NULL,0);
 Debug(LDAP_DEBUG_TRACE,"<==backsql_unbind()\n",0,0,0);
 return 0;
}

#endif /* SLAPD_SQL */
