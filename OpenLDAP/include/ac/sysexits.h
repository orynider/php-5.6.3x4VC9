/* Generic sysexits */
/* $OpenLDAP: pkg/ldap/include/ac/sysexits.h,v 1.1.10.2 2000/06/13 17:57:16 kurt Exp $ */
/*
 * Copyright 1999-2000 The OpenLDAP Foundation, Redwood City, California, USA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted only
 * as authorized by the OpenLDAP Public License.  A copy of this
 * license is available at http://www.OpenLDAP.org/license.html or
 * in file LICENSE in the top-level directory of the distribution.
 */
#ifndef _AC_SYSEXITS_H_
#define _AC_SYSEXITS_H_

#ifdef HAVE_SYSEXITS_H
#	include <sysexits.h>
#else
#	include <sysexits-compat.h>
#endif

#endif /* _AC_SYSEXITS_H_ */
