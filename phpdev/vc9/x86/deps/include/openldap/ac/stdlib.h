/* Generic stdlib.h */
/* $OpenLDAP: pkg/ldap/include/ac/stdlib.h,v 1.2.8.3 2000/06/13 17:57:16 kurt Exp $ */
/*
 * Copyright 1998-2000 The OpenLDAP Foundation, Redwood City, California, USA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted only
 * as authorized by the OpenLDAP Public License.  A copy of this
 * license is available at http://www.OpenLDAP.org/license.html or
 * in file LICENSE in the top-level directory of the distribution.
 */

#ifndef _AC_STDLIB_H
#define _AC_STDLIB_H

#if defined( HAVE_CSRIMALLOC )
#include <stdio.h>
#define MALLOC_TRACE
#include <libmalloc.h>
#endif

#include <stdlib.h>

/* Ignore malloc.h if we have STDC_HEADERS */
#if defined(HAVE_MALLOC_H) && !defined(STDC_HEADERS)
#	include <malloc.h>
#endif

#ifndef EXIT_SUCCESS
#	define EXIT_SUCCESS 0
#	define EXIT_FAILURE 1
#endif

#endif /* _AC_STDLIB_H */
