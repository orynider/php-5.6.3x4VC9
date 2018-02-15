# $OpenLDAP: pkg/ldap/build/lib-static.mk,v 1.2.8.2 2000/06/13 17:57:00 kurt Exp $
## Copyright 1998-2000 The OpenLDAP Foundation
## COPYING RESTRICTIONS APPLY.  See COPYRIGHT File in top level directory
## of this package for details.
##---------------------------------------------------------------------------
##
## Makefile Template for Static Libraries
##

$(LIBRARY): version.o
	$(AR) ru $@ $(OBJS) version.o
	@$(RANLIB) $@;	\
	$(RM) ../$@;	\
	(d=`$(PWD)` ; cd .. ; $(LN_S) `$(BASENAME) $$d`/$@ $@)

Makefile: $(top_srcdir)/build/lib-static.mk
