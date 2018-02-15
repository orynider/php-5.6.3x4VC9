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

#include "apr_file_io.h"
#include "apr_file_info.h"
#include "apr_network_io.h"
#include "apr_errno.h"
#include "apr_general.h"
#include "apr_poll.h"
#include "apr_lib.h"
#include "test_apr.h"

#define DIRNAME "data"
#define FILENAME DIRNAME "/file_datafile.txt"
#define TESTSTR  "This is the file data file."

#define TESTREAD_BLKSIZE 1024
#define APR_BUFFERSIZE   4096 /* This should match APR's buffer size. */



static void test_open_noreadwrite(CuTest *tc)
{
    apr_status_t rv;
    apr_file_t *thefile = NULL;

    rv = apr_file_open(&thefile, FILENAME,
                       APR_CREATE | APR_EXCL, 
                       APR_UREAD | APR_UWRITE | APR_GREAD, p);
    CuAssertTrue(tc, rv != APR_SUCCESS);
    CuAssertIntEquals(tc, 1, APR_STATUS_IS_EACCES(rv));
    CuAssertPtrEquals(tc, NULL, thefile); 
}

static void test_open_excl(CuTest *tc)
{
    apr_status_t rv;
    apr_file_t *thefile = NULL;

    rv = apr_file_open(&thefile, FILENAME,
                       APR_CREATE | APR_EXCL | APR_WRITE, 
                       APR_UREAD | APR_UWRITE | APR_GREAD, p);
    CuAssertTrue(tc, rv != APR_SUCCESS);
    CuAssertIntEquals(tc, 1, APR_STATUS_IS_EEXIST(rv));
    CuAssertPtrEquals(tc, NULL, thefile); 
}

static void test_open_read(CuTest *tc)
{
    apr_status_t rv;
    apr_file_t *filetest = NULL;

    rv = apr_file_open(&filetest, FILENAME, 
                       APR_READ, 
                       APR_UREAD | APR_UWRITE | APR_GREAD, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertPtrNotNull(tc, filetest);
    apr_file_close(filetest);
}

static void test_read(CuTest *tc)
{
    apr_status_t rv;
    apr_size_t nbytes = 256;
    char *str = apr_pcalloc(p, nbytes + 1);
    apr_file_t *filetest = NULL;
    
    rv = apr_file_open(&filetest, FILENAME, 
                       APR_READ, 
                       APR_UREAD | APR_UWRITE | APR_GREAD, p);

    apr_assert_success(tc, "Opening test file " FILENAME, rv);
    rv = apr_file_read(filetest, str, &nbytes);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertIntEquals(tc, strlen(TESTSTR), nbytes);
    CuAssertStrEquals(tc, TESTSTR, str);

    apr_file_close(filetest);
}

static void test_filename(CuTest *tc)
{
    const char *str;
    apr_status_t rv;
    apr_file_t *filetest = NULL;
    
    rv = apr_file_open(&filetest, FILENAME, 
                       APR_READ, 
                       APR_UREAD | APR_UWRITE | APR_GREAD, p);
    apr_assert_success(tc, "Opening test file " FILENAME, rv);

    rv = apr_file_name_get(&str, filetest);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertStrEquals(tc, FILENAME, str);

    apr_file_close(filetest);
}
    
static void test_fileclose(CuTest *tc)
{
    char str;
    apr_status_t rv;
    apr_size_t one = 1;
    apr_file_t *filetest = NULL;
    
    rv = apr_file_open(&filetest, FILENAME, 
                       APR_READ, 
                       APR_UREAD | APR_UWRITE | APR_GREAD, p);
    apr_assert_success(tc, "Opening test file " FILENAME, rv);

    rv = apr_file_close(filetest);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    /* We just closed the file, so this should fail */
    rv = apr_file_read(filetest, &str, &one);
    CuAssertIntEquals(tc, 1, APR_STATUS_IS_EBADF(rv));
}

static void test_file_remove(CuTest *tc)
{
    apr_status_t rv;
    apr_file_t *filetest = NULL;

    rv = apr_file_remove(FILENAME, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_file_open(&filetest, FILENAME, APR_READ, 
                       APR_UREAD | APR_UWRITE | APR_GREAD, p);
    CuAssertIntEquals(tc, 1, APR_STATUS_IS_ENOENT(rv));
}

static void test_open_write(CuTest *tc)
{
    apr_status_t rv;
    apr_file_t *filetest = NULL;

    filetest = NULL;
    rv = apr_file_open(&filetest, FILENAME, 
                       APR_WRITE, 
                       APR_UREAD | APR_UWRITE | APR_GREAD, p);
    CuAssertIntEquals(tc, 1, APR_STATUS_IS_ENOENT(rv));
    CuAssertPtrEquals(tc, NULL, filetest);
}

static void test_open_writecreate(CuTest *tc)
{
    apr_status_t rv;
    apr_file_t *filetest = NULL;

    filetest = NULL;
    rv = apr_file_open(&filetest, FILENAME, 
                       APR_WRITE | APR_CREATE, 
                       APR_UREAD | APR_UWRITE | APR_GREAD, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    apr_file_close(filetest);
}

static void test_write(CuTest *tc)
{
    apr_status_t rv;
    apr_size_t bytes = strlen(TESTSTR);
    apr_file_t *filetest = NULL;

    rv = apr_file_open(&filetest, FILENAME, 
                       APR_WRITE | APR_CREATE, 
                       APR_UREAD | APR_UWRITE | APR_GREAD, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_file_write(filetest, TESTSTR, &bytes);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    apr_file_close(filetest);
}

static void test_open_readwrite(CuTest *tc)
{
    apr_status_t rv;
    apr_file_t *filetest = NULL;

    filetest = NULL;
    rv = apr_file_open(&filetest, FILENAME, 
                       APR_READ | APR_WRITE, 
                       APR_UREAD | APR_UWRITE | APR_GREAD, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertPtrNotNull(tc, filetest);

    apr_file_close(filetest);
}

static void test_seek(CuTest *tc)
{
    apr_status_t rv;
    apr_off_t offset = 5;
    apr_size_t nbytes = 256;
    char *str = apr_pcalloc(p, nbytes + 1);
    apr_file_t *filetest = NULL;

    rv = apr_file_open(&filetest, FILENAME, 
                       APR_READ, 
                       APR_UREAD | APR_UWRITE | APR_GREAD, p);
    apr_assert_success(tc, "Open test file " FILENAME, rv);

    rv = apr_file_read(filetest, str, &nbytes);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertIntEquals(tc, strlen(TESTSTR), nbytes);
    CuAssertStrEquals(tc, TESTSTR, str);

    memset(str, 0, nbytes + 1);

    rv = apr_file_seek(filetest, SEEK_SET, &offset);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    
    rv = apr_file_read(filetest, str, &nbytes);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertIntEquals(tc, strlen(TESTSTR) - 5, nbytes);
    CuAssertStrEquals(tc, TESTSTR + 5, str);

    apr_file_close(filetest);

    /* Test for regression of sign error bug with SEEK_END and
       buffered files. */
    rv = apr_file_open(&filetest, FILENAME,
                       APR_READ | APR_BUFFERED,
                       APR_UREAD | APR_UWRITE | APR_GREAD, p);
    apr_assert_success(tc, "Open test file " FILENAME, rv);

    offset = -5;
    rv = apr_file_seek(filetest, SEEK_END, &offset);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertIntEquals(tc, strlen(TESTSTR) - 5, offset);

    memset(str, 0, nbytes + 1);
    nbytes = 256;
    rv = apr_file_read(filetest, str, &nbytes);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertIntEquals(tc, 5, nbytes);
    CuAssertStrEquals(tc, TESTSTR + strlen(TESTSTR) - 5, str);

    apr_file_close(filetest);
}                

static void test_userdata_set(CuTest *tc)
{
    apr_status_t rv;
    apr_file_t *filetest = NULL;

    rv = apr_file_open(&filetest, FILENAME, 
                       APR_WRITE, 
                       APR_UREAD | APR_UWRITE | APR_GREAD, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_file_data_set(filetest, "This is a test",
                           "test", apr_pool_cleanup_null);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    apr_file_close(filetest);
}

static void test_userdata_get(CuTest *tc)
{
    apr_status_t rv;
    char *teststr;
    apr_file_t *filetest = NULL;

    rv = apr_file_open(&filetest, FILENAME, 
                       APR_WRITE, 
                       APR_UREAD | APR_UWRITE | APR_GREAD, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_file_data_set(filetest, "This is a test",
                           "test", apr_pool_cleanup_null);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_file_data_get((void **)&teststr, "test", filetest);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertStrEquals(tc, "This is a test", teststr);

    apr_file_close(filetest);
}

static void test_userdata_getnokey(CuTest *tc)
{
    apr_status_t rv;
    char *teststr;
    apr_file_t *filetest = NULL;

    rv = apr_file_open(&filetest, FILENAME, 
                       APR_WRITE, 
                       APR_UREAD | APR_UWRITE | APR_GREAD, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_file_data_get((void **)&teststr, "nokey", filetest);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertPtrEquals(tc, NULL, teststr);
    apr_file_close(filetest);
}

static void test_getc(CuTest *tc)
{
    apr_file_t *f = NULL;
    apr_status_t rv;
    char ch;

    rv = apr_file_open(&f, FILENAME, APR_READ, 0, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    apr_file_getc(&ch, f);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertIntEquals(tc, (int)TESTSTR[0], (int)ch);
    apr_file_close(f);
}

static void test_ungetc(CuTest *tc)
{
    apr_file_t *f = NULL;
    apr_status_t rv;
    char ch;

    rv = apr_file_open(&f, FILENAME, APR_READ, 0, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    apr_file_getc(&ch, f);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertIntEquals(tc, (int)TESTSTR[0], (int)ch);

    apr_file_ungetc('X', f);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    apr_file_getc(&ch, f);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertIntEquals(tc, 'X', (int)ch);

    apr_file_close(f);
}

static void test_gets(CuTest *tc)
{
    apr_file_t *f = NULL;
    apr_status_t rv;
    char *str = apr_palloc(p, 256);

    rv = apr_file_open(&f, FILENAME, APR_READ, 0, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_file_gets(str, 256, f);
    /* Only one line in the test file, so APR will encounter EOF on the first
     * call to gets, but we should get APR_SUCCESS on this call and
     * APR_EOF on the next.
     */
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertStrEquals(tc, TESTSTR, str);
    rv = apr_file_gets(str, 256, f);
    CuAssertIntEquals(tc, APR_EOF, rv);
    CuAssertStrEquals(tc, "", str);
    apr_file_close(f);
}

static void test_bigread(CuTest *tc)
{
    apr_file_t *f = NULL;
    apr_status_t rv;
    char buf[APR_BUFFERSIZE * 2];
    apr_size_t nbytes;

    /* Create a test file with known content.
     */
    rv = apr_file_open(&f, "data/created_file", 
                       APR_CREATE | APR_WRITE | APR_TRUNCATE, 
                       APR_UREAD | APR_UWRITE, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    nbytes = APR_BUFFERSIZE;
    memset(buf, 0xFE, nbytes);

    rv = apr_file_write(f, buf, &nbytes);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertIntEquals(tc, APR_BUFFERSIZE, nbytes);

    rv = apr_file_close(f);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    f = NULL;
    rv = apr_file_open(&f, "data/created_file", APR_READ, 0, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    nbytes = sizeof buf;
    rv = apr_file_read(f, buf, &nbytes);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertIntEquals(tc, APR_BUFFERSIZE, nbytes);

    rv = apr_file_close(f);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_file_remove("data/created_file", p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
}

/* Test that the contents of file FNAME are equal to data EXPECT of
 * length EXPECTLEN. */
static void file_contents_equal(CuTest *tc,
                                const char *fname,
                                const void *expect,
                                apr_size_t expectlen)
{
    void *actual = apr_palloc(p, expectlen);
    apr_file_t *f;
    apr_status_t rv;
    int rc;
    
    rv = apr_file_open(&f, fname, APR_READ|APR_BUFFERED, 0, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_file_read_full(f, actual, expectlen, NULL);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rc = memcmp(expect, actual, expectlen);
    CuAssertIntEquals(tc, 0, rc);

    rv = apr_file_close(f);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
}

#define LINE1 "this is a line of text\n"
#define LINE2 "this is a second line of text\n"

static void test_writev_buffered(CuTest *tc)
{
    apr_status_t rv;
    apr_file_t *f;
    apr_size_t nbytes;
    struct iovec vec[2];
    const char *fname = "data/testwritev_buffered.dat";

    rv = apr_file_open(&f, fname,
                       APR_WRITE | APR_CREATE | APR_TRUNCATE |
                       APR_BUFFERED, APR_OS_DEFAULT, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    nbytes = strlen(TESTSTR);
    rv = apr_file_write(f, TESTSTR, &nbytes);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    vec[0].iov_base = LINE1;
    vec[0].iov_len = strlen(LINE1);
    vec[1].iov_base = LINE2;
    vec[1].iov_len = strlen(LINE2);

    rv = apr_file_writev(f, vec, 2, &nbytes);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_file_close(f);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    file_contents_equal(tc, fname, TESTSTR LINE1 LINE2,
                        strlen(TESTSTR) + strlen(LINE1) + strlen(LINE2));
}

static void test_writev_buffered_seek(CuTest *tc)
{
    apr_file_t *f;
    apr_status_t rv;
    apr_off_t off = 0;
    struct iovec vec[3];
    apr_size_t nbytes = strlen(TESTSTR);
    char *str = apr_pcalloc(p, nbytes+1);
    const char *fname = "data/testwritev_buffered.dat";

    rv = apr_file_open(&f, fname,
                       APR_WRITE | APR_READ | APR_BUFFERED,
                       APR_OS_DEFAULT, p);

    rv = apr_file_read(f, str, &nbytes);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertStrEquals(tc, TESTSTR, str);

    rv = apr_file_seek(f, APR_SET, &off);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    vec[0].iov_base = LINE1;
    vec[0].iov_len = strlen(LINE1);
    vec[1].iov_base = LINE2;
    vec[1].iov_len = strlen(LINE2);
    vec[2].iov_base = TESTSTR;
    vec[2].iov_len = strlen(TESTSTR);

    rv = apr_file_writev(f, vec, 3, &nbytes);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_file_close(f);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    file_contents_equal(tc, fname, LINE1 LINE2 TESTSTR,
                        strlen(LINE1) + strlen(LINE2) + strlen(TESTSTR));

    rv = apr_file_remove(fname, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
}

/* This is a horrible name for this function.  We are testing APR, not how
 * Apache uses APR.  And, this function tests _way_ too much stuff.
 */
static void test_mod_neg(CuTest *tc)
{
    apr_status_t rv;
    apr_file_t *f;
    const char *s;
    int i;
    apr_size_t nbytes;
    char buf[8192];
    apr_off_t cur;
    const char *fname = "data/modneg.dat";

    rv = apr_file_open(&f, fname, 
                       APR_CREATE | APR_WRITE, APR_UREAD | APR_UWRITE, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    s = "body56789\n";
    nbytes = strlen(s);
    rv = apr_file_write(f, s, &nbytes);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertIntEquals(tc, strlen(s), nbytes);
    
    for (i = 0; i < 7980; i++) {
        s = "0";
        nbytes = strlen(s);
        rv = apr_file_write(f, s, &nbytes);
        CuAssertIntEquals(tc, APR_SUCCESS, rv);
        CuAssertIntEquals(tc, strlen(s), nbytes);
    }
    
    s = "end456789\n";
    nbytes = strlen(s);
    rv = apr_file_write(f, s, &nbytes);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertIntEquals(tc, strlen(s), nbytes);

    for (i = 0; i < 10000; i++) {
        s = "1";
        nbytes = strlen(s);
        rv = apr_file_write(f, s, &nbytes);
        CuAssertIntEquals(tc, APR_SUCCESS, rv);
        CuAssertIntEquals(tc, strlen(s), nbytes);
    }
    
    rv = apr_file_close(f);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_file_open(&f, fname, APR_READ, 0, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_file_gets(buf, 11, f);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertStrEquals(tc, "body56789\n", buf);

    cur = 0;
    rv = apr_file_seek(f, APR_CUR, &cur);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssert(tc, "File Pointer Mismatch, expected 10", cur == 10);

    nbytes = sizeof(buf);
    rv = apr_file_read(f, buf, &nbytes);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertIntEquals(tc, nbytes, sizeof(buf));

    cur = -((apr_off_t)nbytes - 7980);
    rv = apr_file_seek(f, APR_CUR, &cur);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssert(tc, "File Pointer Mismatch, expected 7990", cur == 7990);

    rv = apr_file_gets(buf, 11, f);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertStrEquals(tc, "end456789\n", buf);

    rv = apr_file_close(f);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_file_remove(fname, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
}

static void test_truncate(CuTest *tc)
{
    apr_status_t rv;
    apr_file_t *f;
    const char *fname = "data/testtruncate.dat";
    const char *s;
    apr_size_t nbytes;
    apr_finfo_t finfo;

    apr_file_remove(fname, p);

    rv = apr_file_open(&f, fname,
                       APR_CREATE | APR_WRITE, APR_UREAD | APR_UWRITE, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    
    s = "some data";
    nbytes = strlen(s);
    rv = apr_file_write(f, s, &nbytes);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssertIntEquals(tc, strlen(s), nbytes);

    rv = apr_file_close(f);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_file_open(&f, fname,
                       APR_TRUNCATE | APR_WRITE, APR_UREAD | APR_UWRITE, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_file_close(f);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);

    rv = apr_stat(&finfo, fname, APR_FINFO_SIZE, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
    CuAssert(tc, "File size mismatch, expected 0 (empty)", finfo.size == 0);

    rv = apr_file_remove(fname, p);
    CuAssertIntEquals(tc, APR_SUCCESS, rv);
}

static void test_fail_write_flush(CuTest *tc)
{
    apr_file_t *f;
    const char *fname = "data/testflush.dat";
    apr_status_t rv;
    char buf[APR_BUFFERSIZE];
    int n;

    apr_file_remove(fname, p);

    apr_assert_success(tc, "open test file",
                       apr_file_open(&f, fname,
                                     APR_CREATE|APR_READ|APR_BUFFERED,
                                     APR_UREAD|APR_UWRITE, p));

    memset(buf, 'A', sizeof buf);

    /* Try three writes.  One of these should fail when it exceeds the
     * internal buffer and actually tries to write to the file, which
     * was opened read-only and hence should be unwritable. */
    for (n = 0, rv = APR_SUCCESS; n < 4 && rv == APR_SUCCESS; n++) {
        apr_size_t bytes = sizeof buf;
        rv = apr_file_write(f, buf, &bytes);
    }

    CuAssert(tc, "failed to write to read-only buffered fd",
             rv != APR_SUCCESS);

    apr_file_close(f);
    apr_file_remove(fname, p);
}

static void test_fail_read_flush(CuTest *tc)
{
    apr_file_t *f;
    const char *fname = "data/testflush.dat";
    apr_status_t rv;
    char buf[2];

    apr_file_remove(fname, p);

    apr_assert_success(tc, "open test file",
                       apr_file_open(&f, fname,
                                     APR_CREATE|APR_READ|APR_BUFFERED,
                                     APR_UREAD|APR_UWRITE, p));

    /* this write should be buffered. */
    apr_assert_success(tc, "buffered write should succeed",
                       apr_file_puts("hello", f));

    /* Now, trying a read should fail since the write must be flushed,
     * and should fail with something other than EOF since the file is
     * opened read-only. */
    rv = apr_file_read_full(f, buf, 2, NULL);

    CuAssert(tc, "read should flush buffered write and fail",
             rv != APR_SUCCESS && rv != APR_EOF);

    /* Likewise for gets */
    rv = apr_file_gets(buf, 2, f);

    CuAssert(tc, "gets should flush buffered write and fail",
             rv != APR_SUCCESS && rv != APR_EOF);

    apr_file_close(f);
    apr_file_remove(fname, p);
}

static void test_xthread(CuTest *tc)
{
    apr_file_t *f;
    const char *fname = "data/testxthread.dat";
    apr_status_t rv;
    apr_int32_t flags = APR_CREATE|APR_READ|APR_WRITE|APR_APPEND|APR_XTHREAD;
    char buf[128] = { 0 };

    /* Test for bug 38438, opening file with append + xthread and seeking to 
       the end of the file resulted in writes going to the beginning not the
       end. */

    apr_file_remove(fname, p);

    rv = apr_file_open(&f, fname, flags, APR_UREAD|APR_UWRITE, p);
    CuAssert(tc, "open test file", rv == APR_SUCCESS);

    rv = apr_file_puts("hello", f);
    CuAssert(tc, "write should succeed", rv == APR_SUCCESS);

    apr_file_close(f);
    
    rv = apr_file_open(&f, fname, flags, APR_UREAD|APR_UWRITE, p);
    CuAssert(tc, "open test file", rv == APR_SUCCESS);

    /* Seek to the end. */
    {
        apr_off_t offset = 0;

        rv = apr_file_seek(f, APR_END, &offset);
    }

    rv = apr_file_puts("world", f);
    CuAssert(tc, "more writes should succeed", rv == APR_SUCCESS);

    /* Back to the beginning. */
    {
        apr_off_t offset = 0;
        
        rv = apr_file_seek(f, APR_SET, &offset);
    }
    
    apr_file_read_full(f, buf, sizeof(buf), NULL);

    CuAssertStrEquals(tc, "helloworld", buf);

    apr_file_close(f);
}

CuSuite *testfile(void)
{
    CuSuite *suite = CuSuiteNew("File I/O");

    SUITE_ADD_TEST(suite, test_open_noreadwrite);
    SUITE_ADD_TEST(suite, test_open_excl);
    SUITE_ADD_TEST(suite, test_open_read);
    SUITE_ADD_TEST(suite, test_open_readwrite);
    SUITE_ADD_TEST(suite, test_read); 
    SUITE_ADD_TEST(suite, test_seek);
    SUITE_ADD_TEST(suite, test_filename);
    SUITE_ADD_TEST(suite, test_fileclose);
    SUITE_ADD_TEST(suite, test_file_remove);
    SUITE_ADD_TEST(suite, test_open_write);
    SUITE_ADD_TEST(suite, test_open_writecreate);
    SUITE_ADD_TEST(suite, test_write);
    SUITE_ADD_TEST(suite, test_userdata_set);
    SUITE_ADD_TEST(suite, test_userdata_get);
    SUITE_ADD_TEST(suite, test_userdata_getnokey);
    SUITE_ADD_TEST(suite, test_getc);
    SUITE_ADD_TEST(suite, test_ungetc);
    SUITE_ADD_TEST(suite, test_gets);
    SUITE_ADD_TEST(suite, test_bigread);
    SUITE_ADD_TEST(suite, test_writev_buffered);
    SUITE_ADD_TEST(suite, test_writev_buffered_seek);
    SUITE_ADD_TEST(suite, test_mod_neg);
    SUITE_ADD_TEST(suite, test_truncate);
    SUITE_ADD_TEST(suite, test_fail_write_flush);
    SUITE_ADD_TEST(suite, test_fail_read_flush);
    SUITE_ADD_TEST(suite, test_xthread);

    return suite;
}

