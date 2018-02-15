/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * ap_ldap.h is generated from ap_ldap.h.in by configure -- do not edit ap_ldap.h
 */
/**
 * @file ap_ldap.h
 * @brief  AP-UTIL LDAP 
 */
#ifndef AP_LDAP_H
#define AP_LDAP_H

/**
 * @defgroup AP_Util_LDAP LDAP
 * @ingroup AP_Util
 * @{
 */

#include "apr_optional.h"

/* this will be defined if LDAP support was compiled into apr-util */
#define AP_HAS_LDAP		   1

/* identify the LDAP toolkit used */
#define AP_HAS_NETSCAPE_LDAPSDK    0
#define AP_HAS_SOLARIS_LDAPSDK     0
#define AP_HAS_NOVELL_LDAPSDK      0
#define AP_HAS_MOZILLA_LDAPSDK     0
#define AP_HAS_OPENLDAP_LDAPSDK    0
#define AP_HAS_MICROSOFT_LDAPSDK   1
#define AP_HAS_TIVOLI_LDAPSDK      0
#define AP_HAS_ZOS_LDAPSDK         0
#define AP_HAS_OTHER_LDAPSDK       0


/*
 * Handle the case when LDAP is enabled
 */
#if AP_HAS_LDAP

/*
 * The following #defines are DEPRECATED and should not be used for
 * anything. They remain to maintain binary compatibility.
 * The original code defined the OPENLDAP SDK as present regardless
 * of what really was there, which was way bogus. In addition, the
 * ap_ldap_url_parse*() functions have been rewritten specifically for
 * APR, so the AP_HAS_LDAP_URL_PARSE macro is forced to zero.
 */
#if AP_HAS_TIVOLI_LDAPSDK
#define AP_HAS_LDAP_SSL 0
#else
#define AP_HAS_LDAP_SSL 1
#endif
#define AP_HAS_LDAP_URL_PARSE 0

#if AP_HAS_OPENLDAP_LDAPSDK && !defined(LDAP_DEPRECATED) 
/* Ensure that the "deprecated" interfaces are still exposed
 * with OpenLDAP >= 2.3; these were exposed by default in earlier
 * releases. */
#define LDAP_DEPRECATED 1
#endif

/*
 * Include the standard LDAP header files.
 */

#include <winldap.h>


/*
 * Detected standard functions
 */
#define AP_HAS_LDAPSSL_CLIENT_INIT 0
#define AP_HAS_LDAPSSL_CLIENT_DEINIT 0
#define AP_HAS_LDAPSSL_ADD_TRUSTED_CERT 0
#define AP_HAS_LDAP_START_TLS_S 0
#define AP_HAS_LDAP_SSLINIT 1
#define AP_HAS_LDAPSSL_INIT 0
#define AP_HAS_LDAPSSL_INSTALL_ROUTINES 0


/*
 * Make sure the secure LDAP port is defined
 */
#ifndef LDAPS_PORT
#define LDAPS_PORT 636  /* ldaps:/// default LDAP over TLS port */
#endif


/*
 * For ldap function calls that input a size limit on the number of returned elements
 * Some SDKs do not have the define for LDAP_DEFAULT_LIMIT (-1) or LDAP_NO_LIMIT (0)
 * LDAP_DEFAULT_LIMIT is preferred as it allows inheritance from whatever the SDK
 * or process is configured for.
 */
#ifdef LDAP_DEFAULT_LIMIT
#define AP_LDAP_SIZELIMIT LDAP_DEFAULT_LIMIT
#else
#ifdef LDAP_NO_LIMIT
#define AP_LDAP_SIZELIMIT LDAP_NO_LIMIT
#endif
#endif

#ifndef AP_LDAP_SIZELIMIT
#define AP_LDAP_SIZELIMIT 0 /* equivalent to LDAP_NO_LIMIT, and what goes on the wire */
#endif

/*
 * z/OS is missing some defines
 */
#ifndef LDAP_VERSION_MAX
#define LDAP_VERSION_MAX  LDAP_VERSION
#endif
#if AP_HAS_ZOS_LDAPSDK
#define LDAP_VENDOR_NAME "IBM z/OS"
#endif

/* Note: Macros defining const casting has been removed in APR v1.0,
 * pending real support for LDAP v2.0 toolkits.
 *
 * In the mean time, please use an LDAP v3.0 toolkit.
 */
#if LDAP_VERSION_MAX <= 2
#error Support for LDAP v2.0 toolkits has been removed from apr-util. Please use an LDAP v3.0 toolkit.
#endif 

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * This structure allows the C LDAP API error codes to be returned
 * along with plain text error messages that explain to us mere mortals
 * what really happened.
 */
typedef struct ap_ldap_err_t {
    const char *reason;
    const char *msg;
    int rc;
} ap_ldap_err_t;

#ifdef __cplusplus
}
#endif

/* The MS SDK returns LDAP_UNAVAILABLE when the backend has closed the connection
 * between LDAP calls. Protect with AP_HAS_MICROSOFT_LDAPSDK in case someone 
 * manually chooses another SDK on Windows 
 */
#if AP_HAS_MICROSOFT_LDAPSDK
#define AP_LDAP_IS_SERVER_DOWN(s)    ((s) == LDAP_SERVER_DOWN \
                                   || (s) == LDAP_UNAVAILABLE)
#else
#define AP_LDAP_IS_SERVER_DOWN(s)    ((s) == LDAP_SERVER_DOWN)
#endif

#include "ap_ldap_url.h"
#include "ap_ldap_init.h"
#include "ap_ldap_option.h"
#include "ap_ldap_rebind.h"

/** @} */
#endif /* AP_HAS_LDAP */
#endif /* AP_LDAP_H */
