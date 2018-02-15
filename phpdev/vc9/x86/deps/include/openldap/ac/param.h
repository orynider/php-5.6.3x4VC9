/* Generic param.h */
/* $OpenLDAP: pkg/ldap/include/ac/param.h,v 1.2.2.1 2000/06/13 17:57:16 kurt Exp $ */
/*
 * Copyright 1999-2000 The OpenLDAP Foundation, Redwood City, California, USA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted only
 * as authorized by the OpenLDAP Public License.  A copy of this
 * license is available at http://www.OpenLDAP.org/license.html or
 * in file LICENSE in the top-level directory of the distribution.
 */

#ifndef _AC_PARAM_H
#define _AC_PARAM_H

#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif

#ifndef MAXPATHLEN
#	ifdef _MAX_PATH
#		define MAXPATHLEN	_MAX_PATH
#	endif
#endif

#endif /* _AC_PARAM_H */
