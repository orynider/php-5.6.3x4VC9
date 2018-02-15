/* $OpenLDAP: pkg/ldap/servers/slapd/back-shell/external.h,v 1.3.4.2 2000/06/13 17:57:37 kurt Exp $ */
/*
 * Copyright 1998-2000 The OpenLDAP Foundation, All Rights Reserved.
 * COPYING RESTRICTIONS APPLY, see COPYRIGHT file
 */
#ifndef _SHELL_EXTERNAL_H
#define _SHELL_EXTERNAL_H

LDAP_BEGIN_DECL

extern int	shell_back_initialize LDAP_P(( BackendInfo *bi ));
extern int	shell_back_open LDAP_P(( BackendInfo *bi ));
extern int	shell_back_close LDAP_P(( BackendInfo *bi ));
extern int	shell_back_destroy LDAP_P(( BackendInfo *bi ));

extern int	shell_back_db_init LDAP_P(( BackendDB *bd ));
extern int	shell_back_db_destroy LDAP_P(( BackendDB *bd ));

extern int	shell_back_db_config LDAP_P(( BackendDB *bd,
	const char *fname, int lineno, int argc, char **argv ));

extern int shell_back_bind LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op,
	const char *dn, const char *ndn, int method,
	struct berval *cred, char** edn ));

extern int	shell_back_unbind LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op ));

extern int	shell_back_search LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op,
	const char *base, const char *nbase,
	int scope, int deref, int sizelimit, int timelimit,
	Filter *filter, const char *filterstr,
	char **attrs, int attrsonly ));

extern int	shell_back_compare LDAP_P((BackendDB *bd,
	Connection *conn, Operation *op,
	const char *dn, const char *ndn,
	AttributeAssertion *ava ));

extern int	shell_back_modify LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op,
	const char *dn, const char *ndn,
	Modifications *ml ));

extern int	shell_back_modrdn LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op,
	const char *dn, const char *ndn,
	const char *newrdn, int deleteoldrdn,
	const char *newSuperior ));

extern int	shell_back_add LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op, Entry *e ));

extern int	shell_back_delete LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op,
	const char *dn, const char *ndn ));

extern int	shell_back_abandon LDAP_P(( BackendDB *bd,
	Connection *conn, Operation *op, int msgid ));

LDAP_END_DECL

#endif /* _SHELL_EXTERNAL_H */

