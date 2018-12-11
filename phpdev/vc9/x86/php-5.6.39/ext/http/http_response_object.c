/*
    +--------------------------------------------------------------------+
    | PECL :: http                                                       |
    +--------------------------------------------------------------------+
    | Redistribution and use in source and binary forms, with or without |
    | modification, are permitted provided that the conditions mentioned |
    | in the accompanying LICENSE file are met.                          |
    +--------------------------------------------------------------------+
    | Copyright (c) 2004-2010, Michael Wallner <mike@php.net>            |
    +--------------------------------------------------------------------+
*/

/* $Id$ */

#define HTTP_WANT_SAPI
#define HTTP_WANT_MAGIC
#include "php_http.h"

/* broken static properties in PHP 5.0 */
#if defined(ZEND_ENGINE_2) && !defined(WONKY)

#include "php_ini.h"

#include "php_http_api.h"
#include "php_http_cache_api.h"
#include "php_http_exception_object.h"
#include "php_http_headers_api.h"
#include "php_http_response_object.h"
#include "php_http_send_api.h"

#define HTTP_BEGIN_ARGS(method, req_args) 		HTTP_BEGIN_ARGS_EX(HttpResponse, method, 0, req_args)
#define HTTP_EMPTY_ARGS(method)					HTTP_EMPTY_ARGS_EX(HttpResponse, method, 0)
#define HTTP_RESPONSE_ME(method, visibility)	PHP_ME(HttpResponse, method, HTTP_ARGS(HttpResponse, method), visibility|ZEND_ACC_STATIC)
#define HTTP_RESPONSE_ALIAS(method, func)		HTTP_STATIC_ME_ALIAS(method, func, HTTP_ARGS(HttpResponse, method))

HTTP_BEGIN_ARGS(setHeader, 1)
	HTTP_ARG_VAL(name, 0)
	HTTP_ARG_VAL(value, 0)
	HTTP_ARG_VAL(replace, 0)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(getHeader, 0)
	HTTP_ARG_VAL(name, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getETag);
HTTP_BEGIN_ARGS(setETag, 1)
	HTTP_ARG_VAL(etag, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getLastModified);
HTTP_BEGIN_ARGS(setLastModified, 1)
	HTTP_ARG_VAL(timestamp, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getCache);
HTTP_BEGIN_ARGS(setCache, 1)
	HTTP_ARG_VAL(cache, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getGzip);
HTTP_BEGIN_ARGS(setGzip, 1)
	HTTP_ARG_VAL(gzip, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getCacheControl);
HTTP_BEGIN_ARGS(setCacheControl, 1)
	HTTP_ARG_VAL(cache_control, 0)
	HTTP_ARG_VAL(max_age, 0)
	HTTP_ARG_VAL(must_revalidate, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getContentType);
HTTP_BEGIN_ARGS(setContentType, 1)
	HTTP_ARG_VAL(content_type, 0)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(guessContentType, 1)
	HTTP_ARG_VAL(magic_file, 0)
	HTTP_ARG_VAL(magic_mode, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getContentDisposition);
HTTP_BEGIN_ARGS(setContentDisposition, 1)
	HTTP_ARG_VAL(filename, 0)
	HTTP_ARG_VAL(send_inline, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getThrottleDelay);
HTTP_BEGIN_ARGS(setThrottleDelay, 1)
	HTTP_ARG_VAL(seconds, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getBufferSize);
HTTP_BEGIN_ARGS(setBufferSize, 1)
	HTTP_ARG_VAL(bytes, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getData);
HTTP_BEGIN_ARGS(setData, 1)
	HTTP_ARG_VAL(data, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getStream);
HTTP_BEGIN_ARGS(setStream, 1)
	HTTP_ARG_VAL(stream, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getFile);
HTTP_BEGIN_ARGS(setFile, 1)
	HTTP_ARG_VAL(filepath, 0)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(send, 0)
	HTTP_ARG_VAL(clean_ob, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(capture);

HTTP_BEGIN_ARGS(redirect, 0)
	HTTP_ARG_VAL(url, 0)
	HTTP_ARG_VAL(params, 0)
	HTTP_ARG_VAL(session, 0)
	HTTP_ARG_VAL(permanent, 0)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(status, 1)
	HTTP_ARG_VAL(code, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getRequestHeaders);
HTTP_EMPTY_ARGS(getRequestBody);
HTTP_EMPTY_ARGS(getRequestBodyStream);

#define THIS_CE http_response_object_ce
zend_class_entry *http_response_object_ce;
zend_function_entry http_response_object_fe[] = {

	HTTP_RESPONSE_ME(setHeader, ZEND_ACC_PUBLIC)
	HTTP_RESPONSE_ME(getHeader, ZEND_ACC_PUBLIC)

	HTTP_RESPONSE_ME(setETag, ZEND_ACC_PUBLIC)
	HTTP_RESPONSE_ME(getETag, ZEND_ACC_PUBLIC)
	
	HTTP_RESPONSE_ME(setLastModified, ZEND_ACC_PUBLIC)
	HTTP_RESPONSE_ME(getLastModified, ZEND_ACC_PUBLIC)

	HTTP_RESPONSE_ME(setContentDisposition, ZEND_ACC_PUBLIC)
	HTTP_RESPONSE_ME(getContentDisposition, ZEND_ACC_PUBLIC)

	HTTP_RESPONSE_ME(setContentType, ZEND_ACC_PUBLIC)
	HTTP_RESPONSE_ME(getContentType, ZEND_ACC_PUBLIC)
	
	HTTP_RESPONSE_ME(guessContentType, ZEND_ACC_PUBLIC)

	HTTP_RESPONSE_ME(setCache, ZEND_ACC_PUBLIC)
	HTTP_RESPONSE_ME(getCache, ZEND_ACC_PUBLIC)

	HTTP_RESPONSE_ME(setCacheControl, ZEND_ACC_PUBLIC)
	HTTP_RESPONSE_ME(getCacheControl, ZEND_ACC_PUBLIC)

	HTTP_RESPONSE_ME(setGzip, ZEND_ACC_PUBLIC)
	HTTP_RESPONSE_ME(getGzip, ZEND_ACC_PUBLIC)

	HTTP_RESPONSE_ME(setThrottleDelay, ZEND_ACC_PUBLIC)
	HTTP_RESPONSE_ME(getThrottleDelay, ZEND_ACC_PUBLIC)

	HTTP_RESPONSE_ME(setBufferSize, ZEND_ACC_PUBLIC)
	HTTP_RESPONSE_ME(getBufferSize, ZEND_ACC_PUBLIC)

	HTTP_RESPONSE_ME(setData, ZEND_ACC_PUBLIC)
	HTTP_RESPONSE_ME(getData, ZEND_ACC_PUBLIC)

	HTTP_RESPONSE_ME(setFile, ZEND_ACC_PUBLIC)
	HTTP_RESPONSE_ME(getFile, ZEND_ACC_PUBLIC)

	HTTP_RESPONSE_ME(setStream, ZEND_ACC_PUBLIC)
	HTTP_RESPONSE_ME(getStream, ZEND_ACC_PUBLIC)

	HTTP_RESPONSE_ME(send, ZEND_ACC_PUBLIC)
	HTTP_RESPONSE_ME(capture, ZEND_ACC_PUBLIC)

	HTTP_RESPONSE_ALIAS(redirect, http_redirect)
	HTTP_RESPONSE_ALIAS(status, http_send_status)
	HTTP_RESPONSE_ALIAS(getRequestHeaders, http_get_request_headers)
	HTTP_RESPONSE_ALIAS(getRequestBody, http_get_request_body)
	HTTP_RESPONSE_ALIAS(getRequestBodyStream, http_get_request_body_stream)

	EMPTY_FUNCTION_ENTRY
};

PHP_MINIT_FUNCTION(http_response_object)
{
	HTTP_REGISTER_CLASS(HttpResponse, http_response_object, NULL, 0);
	
	zend_declare_property_bool(THIS_CE, ZEND_STRS("sent")-1, 0, (ZEND_ACC_STATIC|ZEND_ACC_PRIVATE) TSRMLS_CC);
	zend_declare_property_bool(THIS_CE, ZEND_STRS("catch")-1, 0, (ZEND_ACC_STATIC|ZEND_ACC_PRIVATE) TSRMLS_CC);
	zend_declare_property_long(THIS_CE, ZEND_STRS("mode")-1, -1, (ZEND_ACC_STATIC|ZEND_ACC_PRIVATE) TSRMLS_CC);
	zend_declare_property_long(THIS_CE, ZEND_STRS("stream")-1, 0, (ZEND_ACC_STATIC|ZEND_ACC_PRIVATE) TSRMLS_CC);
	zend_declare_property_null(THIS_CE, ZEND_STRS("file")-1, (ZEND_ACC_STATIC|ZEND_ACC_PRIVATE) TSRMLS_CC);
	zend_declare_property_null(THIS_CE, ZEND_STRS("data")-1, (ZEND_ACC_STATIC|ZEND_ACC_PRIVATE) TSRMLS_CC);
	zend_declare_property_bool(THIS_CE, ZEND_STRS("cache")-1, 0, (ZEND_ACC_STATIC|ZEND_ACC_PROTECTED) TSRMLS_CC);
	zend_declare_property_bool(THIS_CE, ZEND_STRS("gzip")-1, 0, (ZEND_ACC_STATIC|ZEND_ACC_PROTECTED) TSRMLS_CC);
	zend_declare_property_null(THIS_CE, ZEND_STRS("eTag")-1, (ZEND_ACC_STATIC|ZEND_ACC_PROTECTED) TSRMLS_CC);
	zend_declare_property_long(THIS_CE, ZEND_STRS("lastModified")-1, 0, (ZEND_ACC_STATIC|ZEND_ACC_PROTECTED) TSRMLS_CC);
	zend_declare_property_null(THIS_CE, ZEND_STRS("cacheControl")-1, (ZEND_ACC_STATIC|ZEND_ACC_PROTECTED) TSRMLS_CC);
	zend_declare_property_null(THIS_CE, ZEND_STRS("contentType")-1, (ZEND_ACC_STATIC|ZEND_ACC_PROTECTED) TSRMLS_CC);
	zend_declare_property_null(THIS_CE, ZEND_STRS("contentDisposition")-1, (ZEND_ACC_STATIC|ZEND_ACC_PROTECTED) TSRMLS_CC);
	zend_declare_property_long(THIS_CE, ZEND_STRS("bufferSize")-1, 0, (ZEND_ACC_STATIC|ZEND_ACC_PROTECTED) TSRMLS_CC);
	zend_declare_property_double(THIS_CE, ZEND_STRS("throttleDelay")-1, 0.0, (ZEND_ACC_STATIC|ZEND_ACC_PROTECTED) TSRMLS_CC);

#ifndef WONKY
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("REDIRECT")-1, HTTP_REDIRECT TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("REDIRECT_PERM")-1, HTTP_REDIRECT_PERM TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("REDIRECT_FOUND")-1, HTTP_REDIRECT_FOUND TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("REDIRECT_POST")-1, HTTP_REDIRECT_POST TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("REDIRECT_PROXY")-1, HTTP_REDIRECT_PROXY TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("REDIRECT_TEMP")-1, HTTP_REDIRECT_TEMP TSRMLS_CC);
#endif /* WONKY */
	
	return SUCCESS;
}

/* ### USERLAND ### */

/* {{{ proto static bool HttpResponse::setHeader(string name[, mixed value[, bool replace = true]])
	Send an HTTP header. */
PHP_METHOD(HttpResponse, setHeader)
{
	zend_bool replace = 1;
	char *name;
	int name_len = 0;
	zval *value = NULL;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|z/!b", &name, &name_len, &value, &replace)) {
		RETURN_FALSE;
	}
	if (SG(headers_sent)) {
		http_error(HE_WARNING, HTTP_E_HEADER, "Cannot add another header when headers have already been sent");
		RETURN_FALSE;
	}
	if (!name_len) {
		http_error(HE_WARNING, HTTP_E_HEADER, "Cannot send anonymous headers");
		RETURN_FALSE;
	}
	http_send_header_zval_ex(name, name_len, &value, replace);
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto static mixed HttpResponse::getHeader([string name])
	Get header(s) about to be sent. */
PHP_METHOD(HttpResponse, getHeader)
{
	char *name = NULL;
	int name_len = 0;
	
	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &name, &name_len)) {
		RETURN_FALSE;
	}
	
	if (name && name_len) {
		zval **header;
		HashTable headers_ht;
		
		zend_hash_init(&headers_ht, sizeof(zval *), NULL, ZVAL_PTR_DTOR, 0);
		if (	(SUCCESS == http_get_response_headers(&headers_ht)) &&
				(SUCCESS == zend_hash_find(&headers_ht, name, name_len + 1, (void *) &header))) {
			RETVAL_ZVAL(*header, 1, 0);
		} else {
			RETVAL_NULL();
		}
		zend_hash_destroy(&headers_ht);
	} else {
		array_init(return_value);
		http_get_response_headers(Z_ARRVAL_P(return_value));
	}
}
/* }}} */

/* {{{ proto static bool HttpResponse::setCache(bool cache)
	Whether it should be attempted to cache the entity. */
PHP_METHOD(HttpResponse, setCache)
{
	zend_bool do_cache = 0;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &do_cache)) {
		RETURN_FALSE;
	}

	RETURN_SUCCESS(zend_update_static_property_bool(THIS_CE, ZEND_STRS("cache")-1, do_cache TSRMLS_CC));
}
/* }}} */

/* {{{ proto static bool HttpResponse::getCache()
	Get current caching setting. */
PHP_METHOD(HttpResponse, getCache)
{
	NO_ARGS;

	if (return_value_used) {
		zval *cache = http_zsep(IS_BOOL, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("cache")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		RETVAL_ZVAL(cache, 1, 1);
	}
}
/* }}}*/

/* {{{ proto static bool HttpResponse::setGzip(bool gzip)
	Enable on-thy-fly gzipping of the sent entity. */
PHP_METHOD(HttpResponse, setGzip)
{
	zend_bool do_gzip = 0;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &do_gzip)) {
		RETURN_FALSE;
	}

	RETURN_SUCCESS(zend_update_static_property_bool(THIS_CE, ZEND_STRS("gzip")-1, do_gzip TSRMLS_CC));
}
/* }}} */

/* {{{ proto static bool HttpResponse::getGzip()
	Get current gzipping setting. */
PHP_METHOD(HttpResponse, getGzip)
{
	NO_ARGS;

	if (return_value_used) {
		zval *gzip = http_zsep(IS_BOOL, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("gzip")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		RETVAL_ZVAL(gzip, 1, 1);
	}
}
/* }}} */

/* {{{ proto static bool HttpResponse::setCacheControl(string control[, int max_age = 0[, bool must_revalidate = true]])
	Set a custom cache-control header, usually being "private" or "public"; The max_age parameter controls how long the cache entry is valid on the client side. */
PHP_METHOD(HttpResponse, setCacheControl)
{
	char *ccontrol, *cctl;
	int cc_len;
	long max_age = 0;
	zend_bool must_revalidate = 1;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|lb", &ccontrol, &cc_len, &max_age, &must_revalidate)) {
		RETURN_FALSE;
	}

	if (strcmp(ccontrol, "public") && strcmp(ccontrol, "private") && strcmp(ccontrol, "no-cache")) {
		http_error_ex(HE_WARNING, HTTP_E_INVALID_PARAM, "Cache-Control '%s' doesn't match public, private or no-cache", ccontrol);
		RETURN_FALSE;
	} else {
		size_t cctl_len = spprintf(&cctl, 0, "%s,%s max-age=%ld", ccontrol, must_revalidate?" must-revalidate,":"", max_age);
		RETVAL_SUCCESS(zend_update_static_property_stringl(THIS_CE, ZEND_STRS("cacheControl")-1, cctl, cctl_len TSRMLS_CC));
		efree(cctl);
	}
}
/* }}} */

/* {{{ proto static string HttpResponse::getCacheControl()
	Get current Cache-Control header setting. */
PHP_METHOD(HttpResponse, getCacheControl)
{
	NO_ARGS;

	if (return_value_used) {
		zval *cctl = http_zsep(IS_STRING, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("cacheControl")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		RETVAL_ZVAL(cctl, 1, 1);
	}
}
/* }}} */

/* {{{ proto static bool HttpResponse::setContentType(string content_type)
	Set the content-type of the sent entity. */
PHP_METHOD(HttpResponse, setContentType)
{
	char *ctype;
	int ctype_len;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ctype, &ctype_len)) {
		RETURN_FALSE;
	}

	HTTP_CHECK_CONTENT_TYPE(ctype, RETURN_FALSE);
	RETURN_SUCCESS(zend_update_static_property_stringl(THIS_CE, ZEND_STRS("contentType")-1, ctype, ctype_len TSRMLS_CC));
}
/* }}} */

/* {{{ proto static string HttpResponse::getContentType()
	Get current Content-Type header setting. */
PHP_METHOD(HttpResponse, getContentType)
{
	NO_ARGS;

	if (return_value_used) {
		zval *ctype = http_zsep(IS_STRING, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("contentType")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		RETVAL_ZVAL(ctype, 1, 1);
	}
}
/* }}} */

/* {{{ proto static string HttpResponse::guessContentType(string magic_file[, int magic_mode = MAGIC_MIME])
	Attempts to guess the content type of supplied payload through libmagic. */
PHP_METHOD(HttpResponse, guessContentType)
{
#ifdef HTTP_HAVE_MAGIC
	char *magic_file, *ct = NULL;
	int magic_file_len;
	long magic_mode = MAGIC_MIME;
	
	RETVAL_FALSE;
	SET_EH_THROW_HTTP();
	if (SUCCESS == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &magic_file, &magic_file_len, &magic_mode)) {
		switch (Z_LVAL_P(*zend_std_get_static_property(THIS_CE, ZEND_STRS("mode")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC))) {
			case SEND_DATA:
			{
				zval *data = *zend_std_get_static_property(THIS_CE, ZEND_STRS("data")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC);
				ct = http_guess_content_type(magic_file, magic_mode, Z_STRVAL_P(data), Z_STRLEN_P(data), SEND_DATA);
				break;
			}
			
			case SEND_RSRC:
			{
				php_stream *s;
				zval *z = *zend_std_get_static_property(THIS_CE, ZEND_STRS("stream")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC);
				z->type = IS_RESOURCE;
				php_stream_from_zval(s, &z);
				ct = http_guess_content_type(magic_file, magic_mode, s, 0, SEND_RSRC);
				break;
			}
			
			default:
				ct = http_guess_content_type(magic_file, magic_mode, Z_STRVAL_P(*zend_std_get_static_property(THIS_CE, ZEND_STRS("file")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)), 0, -1);
				break;
		}
		if (ct) {
			zend_update_static_property_string(THIS_CE, ZEND_STRS("contentType")-1, ct TSRMLS_CC);
			RETVAL_STRING(ct, 0);
		}
	}
	SET_EH_NORMAL();
#else
	http_error(HE_THROW, HTTP_E_RUNTIME, "Cannot guess Content-Type; libmagic not available");
	RETURN_FALSE;
#endif
}
/* }}} */

/* {{{ proto static bool HttpResponse::setContentDisposition(string filename[, bool inline = false])
	Set the Content-Disposition. */
PHP_METHOD(HttpResponse, setContentDisposition)
{
	char *file, *cd;
	int file_len;
	size_t cd_len;
	zend_bool send_inline = 0;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &file, &file_len, &send_inline)) {
		RETURN_FALSE;
	}

	cd_len = spprintf(&cd, 0, "%s; filename=\"%s\"", send_inline ? "inline" : "attachment", file);
	RETVAL_SUCCESS(zend_update_static_property_stringl(THIS_CE, ZEND_STRS("contentDisposition")-1, cd, cd_len TSRMLS_CC));
	efree(cd);
}
/* }}} */

/* {{{ proto static string HttpResponse::getContentDisposition()
	Get current Content-Disposition setting. */
PHP_METHOD(HttpResponse, getContentDisposition)
{
	NO_ARGS;

	if (return_value_used) {
		zval *cdisp = http_zsep(IS_STRING, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("contentDisposition")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		RETVAL_ZVAL(cdisp, 1, 1);
	}
}
/* }}} */

/* {{{ proto static bool HttpResponse::setETag(string etag)
	Set a custom ETag.  Use this only if you know what you're doing. */
PHP_METHOD(HttpResponse, setETag)
{
	char *etag;
	int etag_len;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &etag, &etag_len)) {
		RETURN_FALSE;
	}

	RETURN_SUCCESS(zend_update_static_property_stringl(THIS_CE, ZEND_STRS("eTag")-1, etag, etag_len TSRMLS_CC));
}
/* }}} */

/* {{{ proto static string HttpResponse::getETag()
	Get calculated or previously set custom ETag. */
PHP_METHOD(HttpResponse, getETag)
{
	NO_ARGS;

	if (return_value_used) {
		zval *etag = http_zsep(IS_STRING, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("eTag")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		RETVAL_ZVAL(etag, 1, 1);
	}
}
/* }}} */

/* {{{ proto static bool HttpResponse::setLastModified(int timestamp)
	Set a custom Last-Modified date. */
PHP_METHOD(HttpResponse, setLastModified)
{
	long lm;
	
	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &lm)) {
		RETURN_FALSE;
	}
	
	RETURN_SUCCESS(zend_update_static_property_long(THIS_CE, ZEND_STRS("lastModified")-1, lm TSRMLS_CC));
}
/* }}} */

/* {{{ proto static int HttpResponse::getLastModified()
	Get calculated or previously set custom Last-Modified date. */
PHP_METHOD(HttpResponse, getLastModified)
{
	NO_ARGS;
	
	if (return_value_used) {
		zval *lmod = http_zsep(IS_LONG, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("lastModified")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		RETVAL_ZVAL(lmod, 1, 1);
	}
}
/* }}} */

/* {{{ proto static bool HttpResponse::setThrottleDelay(double seconds)
	Sets the throttle delay for use with HttpResponse::setBufferSize(). */
PHP_METHOD(HttpResponse, setThrottleDelay)
{
	double seconds;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &seconds)) {
		RETURN_FALSE;
	}
	RETURN_SUCCESS(zend_update_static_property_double(THIS_CE, ZEND_STRS("throttleDelay")-1, seconds TSRMLS_CC));
}
/* }}} */

/* {{{ proto static double HttpResponse::getThrottleDelay()
	Get the current throttle delay. */
PHP_METHOD(HttpResponse, getThrottleDelay)
{
	NO_ARGS;

	if (return_value_used) {
		zval *tdel = http_zsep(IS_DOUBLE, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("throttleDelay")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		RETVAL_ZVAL(tdel, 1, 1);
	}
}
/* }}} */

/* {{{ proto static bool HttpResponse::setBufferSize(int bytes)
	Sets the send buffer size for use with HttpResponse::setThrottleDelay(). */
PHP_METHOD(HttpResponse, setBufferSize)
{
	long bytes;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &bytes)) {
		RETURN_FALSE;
	}
	RETURN_SUCCESS(zend_update_static_property_long(THIS_CE, ZEND_STRS("bufferSize")-1, bytes TSRMLS_CC));
}
/* }}} */

/* {{{ proto static int HttpResponse::getBufferSize()
	Get current buffer size. */
PHP_METHOD(HttpResponse, getBufferSize)
{
	NO_ARGS;

	if (return_value_used) {
		zval *bsize = http_zsep(IS_LONG, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("bufferSize")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		RETVAL_ZVAL(bsize, 1, 1);
	}
}
/* }}} */

/* {{{ proto static bool HttpResponse::setData(mixed data)
	Set the data to be sent. */
PHP_METHOD(HttpResponse, setData)
{
	char *etag;
	zval *the_data;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z/", &the_data)) {
		RETURN_FALSE;
	}
	if (Z_TYPE_P(the_data) != IS_STRING) {
		convert_to_string(the_data);
	}

	if (	(SUCCESS != zend_update_static_property(THIS_CE, ZEND_STRS("data")-1, the_data TSRMLS_CC)) ||
			(SUCCESS != zend_update_static_property_long(THIS_CE, ZEND_STRS("mode")-1, SEND_DATA TSRMLS_CC))) {
		RETURN_FALSE;
	}
	
	zend_update_static_property_long(THIS_CE, ZEND_STRS("lastModified")-1, http_last_modified(the_data, SEND_DATA) TSRMLS_CC);
	if ((etag = http_etag(Z_STRVAL_P(the_data), Z_STRLEN_P(the_data), SEND_DATA))) {
		zend_update_static_property_string(THIS_CE, ZEND_STRS("eTag")-1, etag TSRMLS_CC);
		efree(etag);
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto static string HttpResponse::getData()
	Get the previously set data to be sent. */
PHP_METHOD(HttpResponse, getData)
{
	NO_ARGS;

	if (return_value_used) {
		zval *the_data = *zend_std_get_static_property(THIS_CE, ZEND_STRS("data")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC);
		
		RETURN_ZVAL(the_data, 1, 0);
	}
}
/* }}} */

/* {{{ proto static bool HttpResponse::setStream(resource stream)
	Set the resource to be sent. */
PHP_METHOD(HttpResponse, setStream)
{
	char *etag;
	zval *the_stream;
	php_stream *the_real_stream;
	php_stream_statbuf ssb;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &the_stream)) {
		RETURN_FALSE;
	}
	
	php_stream_from_zval(the_real_stream, &the_stream);
	if (php_stream_stat(the_real_stream, &ssb)) {
		RETURN_FALSE;
	}

	if (	(SUCCESS != zend_update_static_property_long(THIS_CE, ZEND_STRS("stream")-1, Z_LVAL_P(the_stream) TSRMLS_CC)) ||
			(SUCCESS != zend_update_static_property_long(THIS_CE, ZEND_STRS("mode")-1, SEND_RSRC TSRMLS_CC))) {
		RETURN_FALSE;
	}
	zend_list_addref(Z_LVAL_P(the_stream));
	
	zend_update_static_property_long(THIS_CE, ZEND_STRS("lastModified")-1, http_last_modified(the_real_stream, SEND_RSRC) TSRMLS_CC);
	if ((etag = http_etag(the_real_stream, 0, SEND_RSRC))) {
		zend_update_static_property_string(THIS_CE, ZEND_STRS("eTag")-1, etag TSRMLS_CC);
		efree(etag);
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto static resource HttpResponse::getStream()
	Get the previously set resource to be sent. */
PHP_METHOD(HttpResponse, getStream)
{
	NO_ARGS;

	if (return_value_used) {
		zval *stream = http_zsep(IS_LONG, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("stream")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		RETVAL_RESOURCE(Z_LVAL_P(stream));
		zval_ptr_dtor(&stream);
	}
}
/* }}} */

/* {{{ proto static bool HttpResponse::setFile(string file)
	Set the file to be sent. */
PHP_METHOD(HttpResponse, setFile)
{
	char *the_file, *etag;
	int file_len;
	php_stream_statbuf ssb;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &the_file, &file_len)) {
		RETURN_FALSE;
	}
	
	if (php_stream_stat_path(the_file, &ssb)) {
		RETURN_FALSE;
	}
	
	if (	(SUCCESS != zend_update_static_property_stringl(THIS_CE, ZEND_STRS("file")-1, the_file, file_len TSRMLS_CC)) ||
			(SUCCESS != zend_update_static_property_long(THIS_CE, ZEND_STRS("mode")-1, -1 TSRMLS_CC))) {
		RETURN_FALSE;
	}

	zend_update_static_property_long(THIS_CE, ZEND_STRS("lastModified")-1, http_last_modified(the_file, -1) TSRMLS_CC);
	if ((etag = http_etag(the_file, 0, -1))) {
		zend_update_static_property_string(THIS_CE, ZEND_STRS("eTag")-1, etag TSRMLS_CC);
		efree(etag);
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto static string HttpResponse::getFile()
	Get the previously set file to be sent. */
PHP_METHOD(HttpResponse, getFile)
{
	NO_ARGS;

	if (return_value_used) {
		zval *file = http_zsep(IS_STRING, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("file")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		RETVAL_ZVAL(file, 1, 1);
	}
}
/* }}} */

/* {{{ proto static bool HttpResponse::send([bool clean_ob = true])
	Finally send the entity. */
PHP_METHOD(HttpResponse, send)
{
	zval *sent;
	zend_bool clean_ob = 1;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|b", &clean_ob)) {
		RETURN_FALSE;
	}
	
	HTTP_CHECK_HEADERS_SENT(RETURN_FALSE);

	sent = *zend_std_get_static_property(THIS_CE, ZEND_STRS("sent")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC);
	if (Z_LVAL_P(sent)) {
		http_error(HE_WARNING, HTTP_E_RESPONSE, "Cannot send HttpResponse, response has already been sent");
		RETURN_FALSE;
	} else {
		Z_LVAL_P(sent) = 1;
	}

	/* capture mode */
	if (i_zend_is_true(*zend_std_get_static_property(THIS_CE, ZEND_STRS("catch")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC))) {
		zval *zetag, *the_data;

		MAKE_STD_ZVAL(the_data);
#ifdef PHP_OUTPUT_NEWAPI
		php_output_get_contents(the_data TSRMLS_CC);
#else
		php_ob_get_buffer(the_data TSRMLS_CC);
#endif
		zend_update_static_property(THIS_CE, ZEND_STRS("data")-1, the_data TSRMLS_CC);
		ZVAL_LONG(*zend_std_get_static_property(THIS_CE, ZEND_STRS("mode")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC), SEND_DATA);

		zetag = http_zsep(IS_STRING, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("eTag")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		if (!Z_STRLEN_P(zetag)) {
			char *etag = http_etag(Z_STRVAL_P(the_data), Z_STRLEN_P(the_data), SEND_DATA);
			if (etag) {
				zend_update_static_property_string(THIS_CE, ZEND_STRS("eTag")-1, etag TSRMLS_CC);
				efree(etag);
			}
		}
		zval_ptr_dtor(&the_data);
		zval_ptr_dtor(&zetag);

		clean_ob = 1;
	}

	if (clean_ob) {
		/* interrupt on-the-fly etag generation */
		HTTP_G->etag.started = 0;
		/* discard previous output buffers */
#ifdef PHP_OUTPUT_NEWAPI
		php_output_discard_all(TSRMLS_C);
#else
		php_end_ob_buffers(0 TSRMLS_CC);
#endif
	}

	/* caching */
	if (i_zend_is_true(*zend_std_get_static_property(THIS_CE, ZEND_STRS("cache")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC))) {
		zval *cctl, *etag, *lmod;
		
		lmod = http_zsep(IS_LONG, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("lastModified")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		etag = http_zsep(IS_STRING, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("eTag")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		cctl = http_zsep(IS_STRING, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("cacheControl")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		
		if (Z_LVAL_P(lmod) || Z_STRLEN_P(etag)) {
			if (Z_STRLEN_P(cctl)) {
				http_send_cache_control(Z_STRVAL_P(cctl), Z_STRLEN_P(cctl));
			} else {
				http_send_cache_control(HTTP_DEFAULT_CACHECONTROL, lenof(HTTP_DEFAULT_CACHECONTROL));
			}
			if (Z_STRLEN_P(etag)) {
				http_send_etag(Z_STRVAL_P(etag), Z_STRLEN_P(etag));
			}
			if (Z_LVAL_P(lmod)) {
				http_send_last_modified(Z_LVAL_P(lmod));
			}
		}
		
		zval_ptr_dtor(&etag);
		zval_ptr_dtor(&lmod);
		zval_ptr_dtor(&cctl);
	}

	/* content type */
	{
		zval *ctype = http_zsep(IS_STRING, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("contentType")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		if (Z_STRLEN_P(ctype)) {
			http_send_content_type(Z_STRVAL_P(ctype), Z_STRLEN_P(ctype));
		} else {
			char *ctypes = INI_STR("default_mimetype");
			size_t ctlen = ctypes ? strlen(ctypes) : 0;

			if (ctlen) {
				http_send_content_type(ctypes, ctlen);
			} else {
				http_send_content_type("application/x-octetstream", lenof("application/x-octetstream"));
			}
		}
		zval_ptr_dtor(&ctype);
	}

	/* content disposition */
	{
		zval *cd = http_zsep(IS_STRING, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("contentDisposition")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		if (Z_STRLEN_P(cd)) {
			http_send_header_ex("Content-Disposition", lenof("Content-Disposition"), Z_STRVAL_P(cd), Z_STRLEN_P(cd), 1, NULL);
		}
		zval_ptr_dtor(&cd);
	}

	/* throttling */
	{
		zval *bsize = http_zsep(IS_LONG, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("bufferSize")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		zval *delay = http_zsep(IS_DOUBLE, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("throttleDelay")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
		HTTP_G->send.buffer_size    = Z_LVAL_P(bsize);
		HTTP_G->send.throttle_delay = Z_DVAL_P(delay);
		zval_ptr_dtor(&bsize);
		zval_ptr_dtor(&delay);
	}

	/* gzip */
	HTTP_G->send.deflate.response = i_zend_is_true(*zend_std_get_static_property(THIS_CE, ZEND_STRS("gzip")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC));
	
	/* send */
	switch (Z_LVAL_P(*zend_std_get_static_property(THIS_CE, ZEND_STRS("mode")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC))) {
		case SEND_DATA:
		{
			zval *zdata = http_zsep(IS_STRING, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("data")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
			RETVAL_SUCCESS(http_send_data(Z_STRVAL_P(zdata), Z_STRLEN_P(zdata)));
			zval_ptr_dtor(&zdata);
			return;
		}

		case SEND_RSRC:
		{
			php_stream *the_real_stream;
			zval *the_stream = http_zsep(IS_LONG, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("stream")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
			the_stream->type = IS_RESOURCE;
			php_stream_from_zval(the_real_stream, &the_stream);
			RETVAL_SUCCESS(http_send_stream(the_real_stream));
			zval_ptr_dtor(&the_stream);
			return;
		}

		default:
		{
			zval *file = http_zsep(IS_STRING, *(zend_std_get_static_property(THIS_CE, ZEND_STRS("file")-1, 0 ZEND_LITERAL_NIL_CC TSRMLS_CC)));
			RETVAL_SUCCESS(http_send_file(Z_STRVAL_P(file)));
			zval_ptr_dtor(&file);
			return;
		}
	}
}
/* }}} */

/* {{{ proto static void HttpResponse::capture()
	Capture script output.
 */
PHP_METHOD(HttpResponse, capture)
{
	NO_ARGS;
	
	HTTP_CHECK_HEADERS_SENT(RETURN_FALSE);

	zend_update_static_property_long(THIS_CE, ZEND_STRS("catch")-1, 1 TSRMLS_CC);
#ifdef PHP_OUTPUT_NEWAPI
	php_output_discard_all(TSRMLS_C);
	php_output_start_default(TSRMLS_C);
#else
	php_end_ob_buffers(0 TSRMLS_CC);
	php_start_ob_buffer(NULL, 0, 0 TSRMLS_CC);
#endif

	/* register shutdown function */
	{
		zval func, retval, arg, *argp[1];

		INIT_PZVAL(&arg);
		INIT_PZVAL(&func);
		INIT_PZVAL(&retval);
		ZVAL_STRINGL(&func, "register_shutdown_function", lenof("register_shutdown_function"), 0);

		array_init(&arg);
		add_next_index_stringl(&arg, "HttpResponse", lenof("HttpResponse"), 1);
		add_next_index_stringl(&arg, "send", lenof("send"), 1);
		argp[0] = &arg;
		call_user_function(EG(function_table), NULL, &func, &retval, 1, argp TSRMLS_CC);
		zval_dtor(&arg);
	}
}
/* }}} */

#endif /* ZEND_ENGINE_2 && !WONKY */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

