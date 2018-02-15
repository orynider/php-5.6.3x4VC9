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

#include "test_apr.h"
#include "apr_errno.h"
#include "apr_general.h"
#include "apr_user.h"

#if APR_HAS_USER
static void uid_current(CuTest *tc)
{
    apr_uid_t uid;
    apr_gid_t gid;
    apr_status_t rv;

    rv = apr_uid_current(&uid, &gid, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
}

static void username(CuTest *tc)
{
    apr_uid_t uid;
    apr_gid_t gid;
    apr_uid_t retreived_uid;
    apr_gid_t retreived_gid;
    apr_status_t rv;
    char *uname = NULL;

    rv = apr_uid_current(&uid, &gid, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_uid_name_get(&uname, uid, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertPtrNotNull(tc, uname);

    rv = apr_uid_get(&retreived_uid, &retreived_gid, uname, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    CuAssertIntEquals(tc, APR_SUCCESS, apr_uid_compare(uid, retreived_uid));
#ifdef WIN32
    /* ### this fudge was added for Win32 but makes the test return NotImpl
     * on Unix if run as root, when !gid is also true. */
    if (!gid || !retreived_gid) {
        /* The function had no way to recover the gid (this would have been
         * an ENOTIMPL if apr_uid_ functions didn't try to double-up and
         * also return apr_gid_t values, which was bogus.
         */
        if (!gid) {
            CuNotImpl(tc, "Groups from apr_uid_current");
        }
        else {
            CuNotImpl(tc, "Groups from apr_uid_get");
        }        
    }
    else {
#endif
        CuAssertIntEquals(tc, APR_SUCCESS, apr_gid_compare(gid, retreived_gid));
#ifdef WIN32
    }
#endif
}

static void groupname(CuTest *tc)
{
    apr_uid_t uid;
    apr_gid_t gid;
    apr_gid_t retreived_gid;
    apr_status_t rv;
    char *gname = NULL;

    rv = apr_uid_current(&uid, &gid, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_gid_name_get(&gname, gid, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertPtrNotNull(tc, gname);

    rv = apr_gid_get(&retreived_gid, gname, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    CuAssertIntEquals(tc, APR_SUCCESS, apr_gid_compare(gid, retreived_gid));
}

#ifndef WIN32

static void fail_userinfo(CuTest *tc)
{
    apr_uid_t uid;
    apr_gid_t gid;
    apr_status_t rv;
    char *tmp;

    errno = 0;
    gid = uid = 9999999;
    tmp = NULL;
    rv = apr_uid_name_get(&tmp, uid, p);
    CuAssert(tc, "apr_uid_name_get should fail or "
                "return a user name",
                rv != APR_SUCCESS || tmp != NULL);

    errno = 0;
    tmp = NULL;
    rv = apr_gid_name_get(&tmp, gid, p);
    CuAssert(tc, "apr_gid_name_get should fail or "
             "return a group name",
             rv != APR_SUCCESS || tmp != NULL);
    
    gid = 424242;
    errno = 0;
    rv = apr_gid_get(&gid, "I_AM_NOT_A_GROUP", p);
    CuAssert(tc, "apr_gid_get should fail or "
             "set a group number",
             rv != APR_SUCCESS || gid == 424242);

    gid = uid = 424242;
    errno = 0;
    rv = apr_uid_get(&uid, &gid, "I_AM_NOT_A_USER", p);
    CuAssert(tc, "apr_gid_get should fail or "
             "set a user and group number",
             rv != APR_SUCCESS || uid == 424242 || gid == 4242442);

    errno = 0;
    tmp = NULL;
    rv = apr_uid_homepath_get(&tmp, "I_AM_NOT_A_USER", p);
    CuAssert(tc, "apr_uid_homepath_get should fail or "
             "set a path name",
             rv != APR_SUCCESS || tmp != NULL);
}

#else
static void fail_userinfo(CuTest *tc)
{
    CuNotImpl(tc, "Intregal uid/gid not present on this platform");
}
#endif

#else
static void users_not_impl(CuTest *tc)
{
    CuNotImpl(tc, "Users not implemented on this platform");
}
#endif

CuSuite *testuser(void)
{
    CuSuite *suite = CuSuiteNew("Users");

#if !APR_HAS_USER
    SUITE_ADD_TEST(suite, users_not_impl);
#else
    SUITE_ADD_TEST(suite, uid_current);
    SUITE_ADD_TEST(suite, username);
    SUITE_ADD_TEST(suite, groupname);
    SUITE_ADD_TEST(suite, fail_userinfo);
#endif

    return suite;
}
