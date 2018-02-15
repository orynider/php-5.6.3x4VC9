#! /bin/sh
# $OpenLDAP: pkg/ldap/tests/scripts/conf.sh,v 1.1 2000/10/01 20:46:52 kurt Exp $
sed -e s%@BACKEND@%$BACKEND% -e s%#$BACKEND#%%
