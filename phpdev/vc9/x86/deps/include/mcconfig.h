/*
 | /remote/sqlmon/concord/monclt/generic/include/mcconfig.h,v
 | 1.6
 | 1996/01/19 20:14:23
 */


#ifndef __MCCONFIG_H
#define __MCCONFIG_H   1


/*
 |------------------------------------------------------------------------------
 |          Sybase SQL Monitor
 |          Confidential Property of Sybase, Inc.
 |          (c) Copyright Sybase, Inc 1995,1996
 |          All rights reserved
 */


/*//////////////////////////////////////////////////////////////////////////////
 |
 |  supportive declarations
 |
 */

#if defined(_ANSI_C_SOURCE) && !defined(_NO_PROTO)
#define CS_FORCE_PROTOTYPES 1
#endif
#include "csconfig.h"


/*/////////////////////////////////////////////////////////////////////////////
 |
 |  macros
 |
 */

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

/*
 | Define wrappers to insure that all function prototypes defined in the
 | Monitor Client Library header files have the correct C function linkage
 | when used with C++ compilers.
 */
#if defined(__cplusplus)
#define MC_START_EXTERN_C       extern "C" {
#define MC_END_EXTERN_C         }
#else
#define MC_START_EXTERN_C
#define MC_END_EXTERN_C
#endif /* defined(__cplusplus) */


#endif   /*   __MCCONFIG_H   */
/*-----------------------------------------------------------------------------*/
