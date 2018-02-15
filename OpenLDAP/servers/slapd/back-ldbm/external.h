/* $OpenLDAP: pkg/ldap/servers/slapd/back-ldbm/external.h,v 1.5.4.6 2000/07/29 01:53:15 kurt Exp $ */
/*
 * Copyright 1998-2000 The OpenLDAP Foundation, All Rights Reserved.
 * COPYING RESTRICTIONS APPLY, see COPYRIGHT file
 */

#ifndef _LDBM_EXTERNAL_H
#define _LDBM_EXTERNAL_H

LDAP_BEGIN_DECL

extern int	ldbm_back_initialize LDAP_P(( BackendInfo *bi ));
extern int	ldbm_back_open LDAP_P(( BackendInfo *bi ));
extern int	ldbm_back_close LDAP_P(( BackendInfo *bi ));
extern int	ldbm_back_destroy LDAP_P(( BackendInfo *bi ));

extern int	ldbm_back_db_init LDAP_P(( BackendDB *bd ));
extern int	ldbm_back_db_open LDAP_P(( BackendDB *bd ));
extern int	ldbm_back_db_close LDAP_P(( BackendDB *bd ));
extern int	ldbm_back_db_destroy LDAP_P(( BackendDB *bd ));

extern int	ldbm_back_db_config LDAP_P(( BackendDB *bd,
	const char *fname, int lineno,
	int argc, char **argv ));

extern int ldbm_back_extended LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op,
	const char *reqoid,
	struct berval *reqdata,
	char **rspoid,
	struct berval **rspdata,
	LDAPControl *** rspctrls,
	const char **text,
	struct berval *** refs ));

extern int ldbm_back_bind LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op,
	const char *dn, const char *ndn, int method,
	struct berval *cred, char** edn ));

extern int	ldbm_back_unbind LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op ));

extern int	ldbm_back_search LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op,
	const char *base, const char *nbase,
	int scope, int deref, int sizelimit, int timelimit,
	Filter *filter, const char *filterstr,
	char **attrs, int attrsonly ));

extern int	ldbm_back_compare LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op,
	const char *dn, const char *ndn,
	AttributeAssertion *ava ));

extern int	ldbm_back_modify LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op,
	const char *dn, const char *ndn, Modifications *ml ));

extern int	ldbm_back_modrdn LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op,
	const char *dn, const char *ndn,
	const char* newrdn, int deleteoldrdn,
	const char *newSuperior ));

extern int	ldbm_back_add LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op, Entry *e ));

extern int	ldbm_back_delete LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op,
	const char *dn, const char *ndn ));

extern int	ldbm_back_abandon LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op, ber_int_t msgid ));

extern int	ldbm_back_group LDAP_P(( BackendDB *bd,
	Entry *target,
	const char* gr_ndn,
	const char* op_ndn,
	ObjectClass* group_oc,
	AttributeDescription* group_at));

extern int	ldbm_back_attribute LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op,
	Entry *target,
	const char* e_ndn,
	AttributeDescription* entry_at,
	struct berval ***vals));


/* hooks for slap tools */
extern int ldbm_tool_entry_open LDAP_P(( BackendDB *be, int mode ));
extern int ldbm_tool_entry_close LDAP_P(( BackendDB *be ));
extern ID ldbm_tool_entry_first LDAP_P(( BackendDB *be ));
extern ID ldbm_tool_entry_next LDAP_P(( BackendDB *be ));
extern Entry* ldbm_tool_entry_get LDAP_P(( BackendDB *be, ID id ));
extern ID ldbm_tool_entry_put LDAP_P(( BackendDB *be, Entry *e ));

extern int ldbm_tool_entry_reindex LDAP_P(( BackendDB *be, ID id ));
extern int ldbm_tool_sync LDAP_P(( BackendDB *be ));

extern int ldbm_back_referrals LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op,
	const char *dn, const char *ndn,
	const char **text ));

LDAP_END_DECL

#endif /* _LDBM_EXTERNAL_H */

