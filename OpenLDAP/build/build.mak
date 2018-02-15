# $OpenLDAP: pkg/ldap/build/build.mak,v 1.2.2.1 2000/06/13 17:57:00 kurt Exp $
#
# Copyright 1998-2000 The OpenLDAP Foundation, All Rights Reserved.
# COPYING RESTRICTIONS APPLY, see COPYRIGHT file
#

all: build.txt

build.txt: version
	copy version build.txt
