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

/**
 * The LDAP rebind functions provide an implementation of
 * a rebind procedure that can be used to allow clients to chase referrals,
 * using the same credentials used to log in originally.
 *
 * Use of this implementation is optional.
 *
 * @file ap_ldap_rebind.h
 * @brief Apache LDAP library
 */

#ifndef AP_LDAP_REBIND_H
#define AP_LDAP_REBIND_H

/**
 * @addtogroup AP_Util_LDAP
 * @{
 **/

/*
 * Handle the case when LDAP is enabled
 */
#if AP_HAS_LDAP

#if defined(DOXYGEN)
#include "ap_ldap.h"
#endif

/**
 * LDAP initialize rebind lock
 *
 * This function creates the lock for controlling access to the xref list..
 * @param pool Pool to use when creating the xref_lock.
 */
APR_DECLARE_OPTIONAL_FN(apr_status_t, ap_ldap_rebind_init, (apr_pool_t *pool));


/**
 * LDAP rebind_add function
 *
 * This function creates a cross reference entry for the specified ldap
 * connection. The rebind callback function will look up this ldap 
 * connection so it can retrieve the bindDN and bindPW for use in any 
 * binds while referrals are being chased.
 *
 * This function will add the callback to the LDAP handle passed in.
 *
 * A cleanup is registered within the pool provided to remove this
 * entry when the pool is removed. Alternatively ap_ldap_rebind_remove()
 * can be called to explicitly remove the entry at will.
 *
 * @param pool The pool to use
 * @param ld The LDAP connectionhandle
 * @param bindDN The bind DN to be used for any binds while chasing 
 *               referrals on this ldap connection.
 * @param bindPW The bind Password to be used for any binds while 
 *               chasing referrals on this ldap connection.
 */
APR_DECLARE_OPTIONAL_FN(apr_status_t, ap_ldap_rebind_add, (apr_pool_t *pool,
                                                           LDAP *ld,
                                                           const char *bindDN,
                                                           const char *bindPW));

/**
 * LDAP rebind_remove function
 *
 * This function removes the rebind cross reference entry for the
 * specified ldap connection.
 *
 * If not explicitly removed, this function will be called automatically
 * when the pool is cleaned up.
 *
 * @param ld The LDAP connectionhandle
 */
APR_DECLARE_OPTIONAL_FN(apr_status_t, ap_ldap_rebind_remove, (LDAP *ld));

#endif /* AP_HAS_LDAP */

/** @} */

#endif /* AP_LDAP_REBIND_H */

