/* Generic Regex */
/* $OpenLDAP: pkg/ldap/include/ac/regex.h,v 1.4.8.2 2000/06/13 17:57:16 kurt Exp $ */
/*
 * Copyright 1998-2000 The OpenLDAP Foundation, Redwood City, California, USA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted only
 * as authorized by the OpenLDAP Public License.  A copy of this
 * license is available at http://www.OpenLDAP.org/license.html or
 * in file LICENSE in the top-level directory of the distribution.
 */
#ifndef _AC_REGEX_H_
#define _AC_REGEX_H_

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#ifndef HAVE_REGEX_H
/*	NO POSIX REGEX!!
	you'll need to install a POSIX compatible REGEX library.
	Either Henry Spencer's or GNU regex will do.

	For NT: http://people.delphi.com/gjc/hs_regex.html
*/
#error "No POSIX REGEX available."

#elif HAVE_GNUREGEX_H
	/* system has GNU gnuregex.h */ 
#	include <gnuregex.h>
#else
	/* have regex.h, assume it's POSIX compliant */
#	include "gl/regex.h"
#endif /* regex.h */

#endif /* _AC_REGEX_H_ */
