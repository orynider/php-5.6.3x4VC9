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

#define HTTP_WANT_CURL
#include "php_http.h"

#if defined(ZEND_ENGINE_2) && defined(HTTP_HAVE_CURL)

#include "zend_interfaces.h"

#include "php_http_api.h"
#include "php_http_cookie_api.h"
#include "php_http_exception_object.h"
#include "php_http_message_api.h"
#include "php_http_message_object.h"
#include "php_http_request_api.h"
#include "php_http_request_object.h"
#include "php_http_request_pool_api.h"
#include "php_http_url_api.h"

#define HTTP_BEGIN_ARGS(method, req_args) 	HTTP_BEGIN_ARGS_EX(HttpRequest, method, 0, req_args)
#define HTTP_EMPTY_ARGS(method)				HTTP_EMPTY_ARGS_EX(HttpRequest, method, 0)
#define HTTP_REQUEST_ME(method, visibility)	PHP_ME(HttpRequest, method, HTTP_ARGS(HttpRequest, method), visibility)
#define HTTP_REQUEST_ALIAS(method, func)	HTTP_STATIC_ME_ALIAS(method, func, HTTP_ARGS(HttpRequest, method))
#define HTTP_REQUEST_MALIAS(me, al, vis)	ZEND_FENTRY(me, ZEND_MN(HttpRequest_##al), HTTP_ARGS(HttpRequest, al), vis)

HTTP_BEGIN_ARGS(__construct, 0)
	HTTP_ARG_VAL(url, 0)
	HTTP_ARG_VAL(method, 0)
	HTTP_ARG_VAL(options, 0)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(factory, 0)
	HTTP_ARG_VAL(url, 0)
	HTTP_ARG_VAL(method, 0)
	HTTP_ARG_VAL(options, 0)
	HTTP_ARG_VAL(class_name, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getOptions);
HTTP_BEGIN_ARGS(setOptions, 0)
	HTTP_ARG_VAL(options, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getSslOptions);
HTTP_BEGIN_ARGS(setSslOptions, 0)
	HTTP_ARG_VAL(ssl_options, 0)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(addSslOptions, 0)
	HTTP_ARG_VAL(ssl_optins, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getHeaders);
HTTP_BEGIN_ARGS(setHeaders, 0)
	HTTP_ARG_VAL(headers, 0)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(addHeaders, 1)
	HTTP_ARG_VAL(headers, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getCookies);
HTTP_BEGIN_ARGS(setCookies, 0)
	HTTP_ARG_VAL(cookies, 0)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(addCookies, 1)
	HTTP_ARG_VAL(cookies, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(enableCookies);
HTTP_BEGIN_ARGS(resetCookies, 0)
	HTTP_ARG_VAL(session_only, 0)
HTTP_END_ARGS;
HTTP_EMPTY_ARGS(flushCookies);

HTTP_EMPTY_ARGS(getUrl);
HTTP_BEGIN_ARGS(setUrl, 1)
	HTTP_ARG_VAL(url, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getMethod);
HTTP_BEGIN_ARGS(setMethod, 1)
	HTTP_ARG_VAL(request_method, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getContentType);
HTTP_BEGIN_ARGS(setContentType, 1)
	HTTP_ARG_VAL(content_type, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getQueryData);
HTTP_BEGIN_ARGS(setQueryData, 0)
	HTTP_ARG_VAL(query_data, 0)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(addQueryData, 1)
	HTTP_ARG_VAL(query_data, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getPostFields);
HTTP_BEGIN_ARGS(setPostFields, 0)
	HTTP_ARG_VAL(post_fields, 0)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(addPostFields, 1)
	HTTP_ARG_VAL(post_fields, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getPostFiles);
HTTP_BEGIN_ARGS(setPostFiles, 0)
	HTTP_ARG_VAL(post_files, 0)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(addPostFile, 2)
	HTTP_ARG_VAL(formname, 0)
	HTTP_ARG_VAL(filename, 0)
	HTTP_ARG_VAL(content_type, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getBody);
HTTP_BEGIN_ARGS(setBody, 0)
	HTTP_ARG_VAL(request_body_data, 0)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(addBody, 1)
	HTTP_ARG_VAL(request_body_data, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getPutFile);
HTTP_BEGIN_ARGS(setPutFile, 0)
	HTTP_ARG_VAL(filename, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getPutData);
HTTP_BEGIN_ARGS(setPutData, 0)
	HTTP_ARG_VAL(put_data, 0)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(addPutData, 1)
	HTTP_ARG_VAL(put_data, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getResponseData);
HTTP_BEGIN_ARGS(getResponseHeader, 0)
	HTTP_ARG_VAL(name, 0)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(getResponseCookies, 0)
	HTTP_ARG_VAL(flags, 0)
	HTTP_ARG_VAL(allowed_extras, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getResponseBody);
HTTP_EMPTY_ARGS(getResponseCode);
HTTP_EMPTY_ARGS(getResponseStatus);
HTTP_BEGIN_ARGS(getResponseInfo, 0)
	HTTP_ARG_VAL(name, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getMessageClass);
HTTP_BEGIN_ARGS(setMessageClass, 1)
	HTTP_ARG_VAL(message_class_name, 0)
HTTP_END_ARGS;

HTTP_EMPTY_ARGS(getResponseMessage);
HTTP_EMPTY_ARGS(getRawResponseMessage);
HTTP_EMPTY_ARGS(getRequestMessage);
HTTP_EMPTY_ARGS(getRawRequestMessage);
HTTP_EMPTY_ARGS(getHistory);
HTTP_EMPTY_ARGS(clearHistory);
HTTP_EMPTY_ARGS(send);

HTTP_BEGIN_ARGS(get, 1)
	HTTP_ARG_VAL(url, 0)
	HTTP_ARG_VAL(options, 0)
	HTTP_ARG_VAL(info, 1)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(head, 1)
	HTTP_ARG_VAL(url, 0)
	HTTP_ARG_VAL(options, 0)
	HTTP_ARG_VAL(info, 1)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(postData, 2)
	HTTP_ARG_VAL(url, 0)
	HTTP_ARG_VAL(data, 0)
	HTTP_ARG_VAL(options, 0)
	HTTP_ARG_VAL(info, 1)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(postFields, 2)
	HTTP_ARG_VAL(url, 0)
	HTTP_ARG_VAL(data, 0)
	HTTP_ARG_VAL(options, 0)
	HTTP_ARG_VAL(info, 1)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(putData, 2)
	HTTP_ARG_VAL(url, 0)
	HTTP_ARG_VAL(data, 0)
	HTTP_ARG_VAL(options, 0)
	HTTP_ARG_VAL(info, 1)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(putFile, 2)
	HTTP_ARG_VAL(url, 0)
	HTTP_ARG_VAL(file, 0)
	HTTP_ARG_VAL(options, 0)
	HTTP_ARG_VAL(info, 1)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(putStream, 2)
	HTTP_ARG_VAL(url, 0)
	HTTP_ARG_VAL(stream, 0)
	HTTP_ARG_VAL(options, 0)
	HTTP_ARG_VAL(info, 1)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(methodRegister, 1)
	HTTP_ARG_VAL(method_name, 0)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(methodUnregister, 1)
	HTTP_ARG_VAL(method, 0)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(methodName, 1)
	HTTP_ARG_VAL(method_id, 0)
HTTP_END_ARGS;

HTTP_BEGIN_ARGS(methodExists, 1)
	HTTP_ARG_VAL(method, 0)
HTTP_END_ARGS;

#ifdef HAVE_CURL_FORMGET
HTTP_BEGIN_ARGS(encodeBody, 2)
	HTTP_ARG_VAL(fields, 0)
	HTTP_ARG_VAL(files, 0)
HTTP_END_ARGS;
#endif

#define THIS_CE http_request_object_ce
zend_class_entry *http_request_object_ce;
zend_function_entry http_request_object_fe[] = {
	HTTP_REQUEST_ME(__construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)

	HTTP_REQUEST_ME(setOptions, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getOptions, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(setSslOptions, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getSslOptions, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(addSslOptions, ZEND_ACC_PUBLIC)

	HTTP_REQUEST_ME(addHeaders, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getHeaders, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(setHeaders, ZEND_ACC_PUBLIC)
	
	HTTP_REQUEST_ME(addCookies, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getCookies, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(setCookies, ZEND_ACC_PUBLIC)

	HTTP_REQUEST_ME(enableCookies, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(resetCookies, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(flushCookies, ZEND_ACC_PUBLIC)

	HTTP_REQUEST_ME(setMethod, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getMethod, ZEND_ACC_PUBLIC)

	HTTP_REQUEST_ME(setUrl, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getUrl, ZEND_ACC_PUBLIC)

	HTTP_REQUEST_ME(setContentType, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getContentType, ZEND_ACC_PUBLIC)

	HTTP_REQUEST_ME(setQueryData, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getQueryData, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(addQueryData, ZEND_ACC_PUBLIC)

	HTTP_REQUEST_ME(setPostFields, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getPostFields, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(addPostFields, ZEND_ACC_PUBLIC)
	
	HTTP_REQUEST_ME(setBody, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getBody, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(addBody, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_MALIAS(setRawPostData, setBody, ZEND_ACC_PUBLIC|ZEND_ACC_DEPRECATED)
	HTTP_REQUEST_MALIAS(getRawPostData, getBody, ZEND_ACC_PUBLIC|ZEND_ACC_DEPRECATED)
	HTTP_REQUEST_MALIAS(addRawPostData, addBody, ZEND_ACC_PUBLIC|ZEND_ACC_DEPRECATED)

	HTTP_REQUEST_ME(setPostFiles, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(addPostFile, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getPostFiles, ZEND_ACC_PUBLIC)

	HTTP_REQUEST_ME(setPutFile, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getPutFile, ZEND_ACC_PUBLIC)

	HTTP_REQUEST_ME(setPutData, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getPutData, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(addPutData, ZEND_ACC_PUBLIC)

	HTTP_REQUEST_ME(send, ZEND_ACC_PUBLIC)

	HTTP_REQUEST_ME(getResponseData, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getResponseHeader, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getResponseCookies, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getResponseCode, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getResponseStatus, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getResponseBody, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getResponseInfo, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getResponseMessage, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getRawResponseMessage, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getRequestMessage, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getRawRequestMessage, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(getHistory, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(clearHistory, ZEND_ACC_PUBLIC)

	HTTP_REQUEST_ME(getMessageClass, ZEND_ACC_PUBLIC)
	HTTP_REQUEST_ME(setMessageClass, ZEND_ACC_PUBLIC)

	HTTP_REQUEST_ME(factory, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)

	HTTP_REQUEST_ALIAS(get, http_get)
	HTTP_REQUEST_ALIAS(head, http_head)
	HTTP_REQUEST_ALIAS(postData, http_post_data)
	HTTP_REQUEST_ALIAS(postFields, http_post_fields)
	HTTP_REQUEST_ALIAS(putData, http_put_data)
	HTTP_REQUEST_ALIAS(putFile, http_put_file)
	HTTP_REQUEST_ALIAS(putStream, http_put_stream)

	HTTP_REQUEST_ALIAS(methodRegister, http_request_method_register)
	HTTP_REQUEST_ALIAS(methodUnregister, http_request_method_unregister)
	HTTP_REQUEST_ALIAS(methodName, http_request_method_name)
	HTTP_REQUEST_ALIAS(methodExists, http_request_method_exists)
#ifdef HAVE_CURL_FORMGET
	HTTP_REQUEST_ALIAS(encodeBody, http_request_body_encode)
#endif
	EMPTY_FUNCTION_ENTRY
};
static zend_object_handlers http_request_object_handlers;

PHP_MINIT_FUNCTION(http_request_object)
{
	HTTP_REGISTER_CLASS_EX(HttpRequest, http_request_object, NULL, 0);
	http_request_object_handlers.clone_obj = _http_request_object_clone_obj;

	zend_declare_property_null(THIS_CE, ZEND_STRS("options")-1, ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_null(THIS_CE, ZEND_STRS("postFields")-1, ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_null(THIS_CE, ZEND_STRS("postFiles")-1, ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_null(THIS_CE, ZEND_STRS("responseInfo")-1, ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_null(THIS_CE, ZEND_STRS("responseMessage")-1, ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_long(THIS_CE, ZEND_STRS("responseCode")-1, 0, ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_string(THIS_CE, ZEND_STRS("responseStatus")-1, "", ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_long(THIS_CE, ZEND_STRS("method")-1, HTTP_GET, ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_string(THIS_CE, ZEND_STRS("url")-1, "", ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_string(THIS_CE, ZEND_STRS("contentType")-1, "", ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_string(THIS_CE, ZEND_STRS("requestBody")-1, "", ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_string(THIS_CE, ZEND_STRS("queryData")-1, "", ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_string(THIS_CE, ZEND_STRS("putFile")-1, "", ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_string(THIS_CE, ZEND_STRS("putData")-1, "", ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_null(THIS_CE, ZEND_STRS("history")-1, ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_bool(THIS_CE, ZEND_STRS("recordHistory")-1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_string(THIS_CE, ZEND_STRS("messageClass")-1, "", ZEND_ACC_PRIVATE TSRMLS_CC);

#ifndef WONKY
	/*
	 * Request Method Constants
	*/
	/* HTTP/1.1 */
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_GET")-1, HTTP_GET TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_HEAD")-1, HTTP_HEAD TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_POST")-1, HTTP_POST TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_PUT")-1, HTTP_PUT TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_DELETE")-1, HTTP_DELETE TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_OPTIONS")-1, HTTP_OPTIONS TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_TRACE")-1, HTTP_TRACE TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_CONNECT")-1, HTTP_CONNECT TSRMLS_CC);
	/* WebDAV - RFC 2518 */
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_PROPFIND")-1, HTTP_PROPFIND TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_PROPPATCH")-1, HTTP_PROPPATCH TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_MKCOL")-1, HTTP_MKCOL TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_COPY")-1, HTTP_COPY TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_MOVE")-1, HTTP_MOVE TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_LOCK")-1, HTTP_LOCK TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_UNLOCK")-1, HTTP_UNLOCK TSRMLS_CC);
	/* WebDAV Versioning - RFC 3253 */
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_VERSION_CONTROL")-1, HTTP_VERSION_CONTROL TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_REPORT")-1, HTTP_REPORT TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_CHECKOUT")-1, HTTP_CHECKOUT TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_CHECKIN")-1, HTTP_CHECKIN TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_UNCHECKOUT")-1, HTTP_UNCHECKOUT TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_MKWORKSPACE")-1, HTTP_MKWORKSPACE TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_UPDATE")-1, HTTP_UPDATE TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_LABEL")-1, HTTP_LABEL TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_MERGE")-1, HTTP_MERGE TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_BASELINE_CONTROL")-1, HTTP_BASELINE_CONTROL TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_MKACTIVITY")-1, HTTP_MKACTIVITY TSRMLS_CC);
	/* WebDAV Access Control - RFC 3744 */
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("METH_ACL")-1, HTTP_ACL TSRMLS_CC);

	/*
	* HTTP Protocol Version Constants
	*/
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("VERSION_1_0")-1, CURL_HTTP_VERSION_1_0 TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("VERSION_1_1")-1, CURL_HTTP_VERSION_1_1 TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("VERSION_NONE")-1, CURL_HTTP_VERSION_NONE TSRMLS_CC); /* to be removed */
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("VERSION_ANY")-1, CURL_HTTP_VERSION_NONE TSRMLS_CC);

	/*
	* SSL Version Constants
	*/
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("SSL_VERSION_TLSv1")-1, CURL_SSLVERSION_TLSv1 TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("SSL_VERSION_SSLv2")-1, CURL_SSLVERSION_SSLv2 TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("SSL_VERSION_SSLv3")-1, CURL_SSLVERSION_SSLv3 TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("SSL_VERSION_ANY")-1, CURL_SSLVERSION_DEFAULT TSRMLS_CC);

	/*
	* DNS IPvX resolving
	*/
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("IPRESOLVE_V4")-1, CURL_IPRESOLVE_V4 TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("IPRESOLVE_V6")-1, CURL_IPRESOLVE_V6 TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("IPRESOLVE_ANY")-1, CURL_IPRESOLVE_WHATEVER TSRMLS_CC);

	/*
	* Auth Constants
	*/
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("AUTH_BASIC")-1, CURLAUTH_BASIC TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("AUTH_DIGEST")-1, CURLAUTH_DIGEST TSRMLS_CC);
#if HTTP_CURL_VERSION(7,19,3)
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("AUTH_DIGEST_IE")-1, CURLAUTH_DIGEST_IE TSRMLS_CC);
#endif
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("AUTH_NTLM")-1, CURLAUTH_NTLM TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("AUTH_GSSNEG")-1, CURLAUTH_GSSNEGOTIATE TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("AUTH_ANY")-1, CURLAUTH_ANY TSRMLS_CC);
	
	/*
	* Proxy Type Constants
	*/
#	if HTTP_CURL_VERSION(7,15,2)
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("PROXY_SOCKS4")-1, CURLPROXY_SOCKS4 TSRMLS_CC);
#	endif
#if HTTP_CURL_VERSION(7,18,0)
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("PROXY_SOCKS4A")-1, CURLPROXY_SOCKS5 TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("PROXY_SOCKS5_HOSTNAME")-1, CURLPROXY_SOCKS5 TSRMLS_CC);
#endif
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("PROXY_SOCKS5")-1, CURLPROXY_SOCKS5 TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("PROXY_HTTP")-1, CURLPROXY_HTTP TSRMLS_CC);
#	if HTTP_CURL_VERSION(7,19,4)
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("PROXY_HTTP_1_0")-1, CURLPROXY_HTTP_1_0 TSRMLS_CC);
#	endif
#endif /* WONKY */

	/*
	* Post Redirection Constants
	*/
#if HTTP_CURL_VERSION(7,19,1)
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("POSTREDIR_301")-1, CURL_REDIR_POST_301 TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("POSTREDIR_302")-1, CURL_REDIR_POST_302 TSRMLS_CC);
	zend_declare_class_constant_long(THIS_CE, ZEND_STRS("POSTREDIR_ALL")-1, CURL_REDIR_POST_ALL TSRMLS_CC);
#endif
	
	return SUCCESS;
}

zend_object_value _http_request_object_new(zend_class_entry *ce TSRMLS_DC)
{
	return http_request_object_new_ex(ce, NULL, NULL);
}

zend_object_value _http_request_object_new_ex(zend_class_entry *ce, CURL *ch, http_request_object **ptr TSRMLS_DC)
{
	zend_object_value ov;
	http_request_object *o;

	o = ecalloc(1, sizeof(http_request_object));
	o->zo.ce = ce;
	o->request = http_request_init_ex(NULL, ch, 0, NULL);
	
	if (ptr) {
		*ptr = o;
	}

#ifdef ZEND_ENGINE_2_4
	zend_object_std_init(o, ce TSRMLS_CC);
	object_properties_init(o, ce);
#else
	ALLOC_HASHTABLE(OBJ_PROP(o));
	zend_hash_init(OBJ_PROP(o), zend_hash_num_elements(&ce->default_properties), NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_copy(OBJ_PROP(o), &ce->default_properties, (copy_ctor_func_t) zval_add_ref, NULL, sizeof(zval *));
#endif

	ov.handle = putObject(http_request_object, o);
	ov.handlers = &http_request_object_handlers;

	return ov;
}

zend_object_value _http_request_object_clone_obj(zval *this_ptr TSRMLS_DC)
{
	zend_object_value new_ov;
	http_request_object *new_obj;
	getObject(http_request_object, old_obj);
	
	new_ov = http_request_object_new_ex(old_obj->zo.ce, NULL, &new_obj);
	if (old_obj->request->ch) {
		http_curl_init_ex(http_curl_copy(old_obj->request->ch), new_obj->request);
	}
	
	zend_objects_clone_members(&new_obj->zo, new_ov, &old_obj->zo, Z_OBJ_HANDLE_P(this_ptr) TSRMLS_CC);
	phpstr_append(&new_obj->request->conv.request, old_obj->request->conv.request.data, old_obj->request->conv.request.used);
	phpstr_append(&new_obj->request->conv.response, old_obj->request->conv.response.data, old_obj->request->conv.response.used);
	
	return new_ov;
}

void _http_request_object_free(zend_object *object TSRMLS_DC)
{
	http_request_object *o = (http_request_object *) object;

	http_request_free(&o->request);
	freeObject(o);
}

#define http_request_object_check_request_content_type(t) _http_request_object_check_request_content_type((t) TSRMLS_CC)
static inline void _http_request_object_check_request_content_type(zval *this_ptr TSRMLS_DC)
{
	zval *ctype = zend_read_property(THIS_CE, getThis(), ZEND_STRS("contentType")-1, 0 TSRMLS_CC);
				
	if (Z_STRLEN_P(ctype)) {
		zval **headers, *opts = zend_read_property(THIS_CE, getThis(), ZEND_STRS("options")-1, 0 TSRMLS_CC);
		
		if (	(Z_TYPE_P(opts) == IS_ARRAY) &&
				(SUCCESS == zend_hash_find(Z_ARRVAL_P(opts), "headers", sizeof("headers"), (void *) &headers)) && 
				(Z_TYPE_PP(headers) == IS_ARRAY)) {
			zval **ct_header;
			
			/* only override if not already set */
			if ((SUCCESS != zend_hash_find(Z_ARRVAL_PP(headers), "Content-Type", sizeof("Content-Type"), (void *) &ct_header))) {
				add_assoc_stringl(*headers, "Content-Type", Z_STRVAL_P(ctype), Z_STRLEN_P(ctype), 1);
			} else
			/* or not a string, zero length string or a string of spaces */
			if ((Z_TYPE_PP(ct_header) != IS_STRING) || !Z_STRLEN_PP(ct_header)) {
				add_assoc_stringl(*headers, "Content-Type", Z_STRVAL_P(ctype), Z_STRLEN_P(ctype), 1);
			} else {
				int i, only_space = 1;
				
				/* check for spaces only */
				for (i = 0; i < Z_STRLEN_PP(ct_header); ++i) {
					if (!HTTP_IS_CTYPE(space, Z_STRVAL_PP(ct_header)[i])) {
						only_space = 0;
						break;
					}
				}
				if (only_space) {
					add_assoc_stringl(*headers, "Content-Type", Z_STRVAL_P(ctype), Z_STRLEN_P(ctype), 1);
				}
			}
		} else {
			zval *headers;
		
			MAKE_STD_ZVAL(headers);
			array_init(headers);
			add_assoc_stringl(headers, "Content-Type", Z_STRVAL_P(ctype), Z_STRLEN_P(ctype), 1);
			zend_call_method_with_1_params(&getThis(), Z_OBJCE_P(getThis()), NULL, "addheaders", NULL, headers);
			zval_ptr_dtor(&headers);
		}
	}
}

#define http_request_object_message(zo, msg) _http_request_object_message((zo), (msg) TSRMLS_CC)
static inline zend_object_value _http_request_object_message(zval *this_ptr, http_message *msg TSRMLS_DC)
{
	zend_object_value ov;
	zval *zcn = zend_read_property(THIS_CE, getThis(), ZEND_STRS("messageClass")-1, 0 TSRMLS_CC);

	if (Z_STRLEN_P(zcn) && (SUCCESS == http_object_new(&ov, Z_STRVAL_P(zcn), Z_STRLEN_P(zcn), _http_message_object_new_ex, http_message_object_ce, msg, NULL))) {
		return ov;
	} else {
		return http_message_object_new_ex(http_message_object_ce, msg, NULL);
	}
}

STATUS _http_request_object_requesthandler(http_request_object *obj, zval *this_ptr TSRMLS_DC)
{
	STATUS status = SUCCESS;
	char *url = http_absolute_url(Z_STRVAL_P(zend_read_property(THIS_CE, getThis(), ZEND_STRS("url")-1, 0 TSRMLS_CC)));

	if (!url) {
		return FAILURE;
	}
	
	http_request_reset(obj->request);
	obj->request->url = url;
	HTTP_CHECK_CURL_INIT(obj->request->ch, http_curl_init(obj->request), return FAILURE);
	
	switch (obj->request->meth = Z_LVAL_P(zend_read_property(THIS_CE, getThis(), ZEND_STRS("method")-1, 0 TSRMLS_CC)))
	{
		case HTTP_GET:
		case HTTP_HEAD:
			break;

		case HTTP_PUT:
		{
			zval *put_file = zend_read_property(THIS_CE, getThis(), ZEND_STRS("putFile")-1, 0 TSRMLS_CC);
			
			http_request_object_check_request_content_type(getThis());
			
			if (Z_STRLEN_P(put_file)) {
				php_stream_statbuf ssb;
				php_stream *stream = php_stream_open_wrapper_ex(Z_STRVAL_P(put_file), "rb", REPORT_ERRORS|ENFORCE_SAFE_MODE, NULL, HTTP_DEFAULT_STREAM_CONTEXT);
				
				if (stream && SUCCESS == php_stream_stat(stream, &ssb)) {
					obj->request->body = http_request_body_init_ex(obj->request->body, HTTP_REQUEST_BODY_UPLOADFILE, stream, ssb.sb.st_size, 1);
				} else {
					status = FAILURE;
				}
			} else {
				zval *put_data = zend_read_property(THIS_CE, getThis(), ZEND_STRS("putData")-1, 0 TSRMLS_CC);
				obj->request->body = http_request_body_init_ex(obj->request->body, HTTP_REQUEST_BODY_CSTRING,
					estrndup(Z_STRVAL_P(put_data), Z_STRLEN_P(put_data)), Z_STRLEN_P(put_data), 1);
			}
			break;
		}

		case HTTP_POST:
		default:
		{
			/* check for raw request body */
			zval *raw_data = zend_read_property(THIS_CE, getThis(), ZEND_STRS("requestBody")-1, 0 TSRMLS_CC);
			
			if (Z_STRLEN_P(raw_data)) {
				http_request_object_check_request_content_type(getThis());
				obj->request->body = http_request_body_init_ex(obj->request->body, HTTP_REQUEST_BODY_CSTRING,
					estrndup(Z_STRVAL_P(raw_data), Z_STRLEN_P(raw_data)), Z_STRLEN_P(raw_data), 1);
			} else {
				zval *zfields = zend_read_property(THIS_CE, getThis(), ZEND_STRS("postFields")-1, 0 TSRMLS_CC), *zfiles = zend_read_property(THIS_CE, getThis(), ZEND_STRS("postFiles")-1, 0 TSRMLS_CC);
				HashTable *fields;
				HashTable *files;
				
				fields = (Z_TYPE_P(zfields) == IS_ARRAY) ? Z_ARRVAL_P(zfields) : NULL;
				files = (Z_TYPE_P(zfiles) == IS_ARRAY) ? Z_ARRVAL_P(zfiles) : NULL;
				
				if ((fields && zend_hash_num_elements(fields)) || (files && zend_hash_num_elements(files))) {
					if (!(obj->request->body = http_request_body_fill(obj->request->body, fields, files))) {
						status = FAILURE;
					}
				}
			}
			break;
		}
	}

	if (status == SUCCESS) {
		zval *qdata = zend_read_property(THIS_CE, getThis(), ZEND_STRS("queryData")-1, 0 TSRMLS_CC);
		zval *options = zend_read_property(THIS_CE, getThis(), ZEND_STRS("options")-1, 0 TSRMLS_CC);
		
		if (Z_STRLEN_P(qdata)) {
			if (!strchr(obj->request->url, '?')) {
				strlcat(obj->request->url, "?", HTTP_URL_MAXLEN);
			} else {
				strlcat(obj->request->url, "&", HTTP_URL_MAXLEN);
			}
			strlcat(obj->request->url, Z_STRVAL_P(qdata), HTTP_URL_MAXLEN);
		}
		
		http_request_prepare(obj->request, Z_ARRVAL_P(options));
		
		/* check if there's a onProgress method and add it as progress callback if one isn't already set */
		if (zend_hash_exists(&Z_OBJCE_P(getThis())->function_table, "onprogress", sizeof("onprogress"))) {
			zval **entry, *pcb;
			
			if (	(Z_TYPE_P(options) != IS_ARRAY)
				||	(SUCCESS != zend_hash_find(Z_ARRVAL_P(options), "onprogress", sizeof("onprogress"), (void *) &entry)
				||	(!HTTP_IS_CALLABLE(*entry, 0, NULL)))) {
				MAKE_STD_ZVAL(pcb);
				array_init(pcb);
				ZVAL_ADDREF(getThis());
				add_next_index_zval(pcb, getThis());
				add_next_index_stringl(pcb, "onprogress", lenof("onprogress"), 1);
				http_request_set_progress_callback(obj->request, pcb);
				zval_ptr_dtor(&pcb);
			}
		}
	}

	return status;
}

STATUS _http_request_object_responsehandler(http_request_object *obj, zval *this_ptr TSRMLS_DC)
{
	STATUS ret;
	zval *info;
	http_message *msg;
	
	/* always fetch info */
	MAKE_STD_ZVAL(info);
	array_init(info);
	http_request_info(obj->request, Z_ARRVAL_P(info));
	zend_update_property(THIS_CE, getThis(), ZEND_STRS("responseInfo")-1, info TSRMLS_CC);
	zval_ptr_dtor(&info);
	
	/* parse response message */
	phpstr_fix(&obj->request->conv.request);
	phpstr_fix(&obj->request->conv.response);
	
	if ((msg = http_message_parse(PHPSTR_VAL(&obj->request->conv.response), PHPSTR_LEN(&obj->request->conv.response)))) {
		zval *message;

		if (i_zend_is_true(zend_read_property(THIS_CE, getThis(), ZEND_STRS("recordHistory")-1, 0 TSRMLS_CC))) {
			zval *hist, *history = zend_read_property(THIS_CE, getThis(), ZEND_STRS("history")-1, 0 TSRMLS_CC);
			http_message *response = http_message_parse(PHPSTR_VAL(&obj->request->conv.response), PHPSTR_LEN(&obj->request->conv.response));
			http_message *request = http_message_parse(PHPSTR_VAL(&obj->request->conv.request), PHPSTR_LEN(&obj->request->conv.request));
			
			MAKE_STD_ZVAL(hist);
			ZVAL_OBJVAL(hist, http_request_object_message(getThis(), http_message_interconnect(response, request)), 0);
			if (Z_TYPE_P(history) == IS_OBJECT) {
				http_message_object_prepend(hist, history);
			}
			zend_update_property(THIS_CE, getThis(), ZEND_STRS("history")-1, hist TSRMLS_CC);
			zval_ptr_dtor(&hist);
		}

		zend_update_property_long(THIS_CE, getThis(), ZEND_STRS("responseCode")-1, msg->http.info.response.code TSRMLS_CC);
		zend_update_property_string(THIS_CE, getThis(), ZEND_STRS("responseStatus")-1, STR_PTR(msg->http.info.response.status) TSRMLS_CC);

		MAKE_STD_ZVAL(message);
		ZVAL_OBJVAL(message, http_request_object_message(getThis(), msg), 0);
		zend_update_property(THIS_CE, getThis(), ZEND_STRS("responseMessage")-1, message TSRMLS_CC);
		zval_ptr_dtor(&message);

		ret = SUCCESS;
	} else {
		/* update properties with empty values*/
		zval *znull;
		
		MAKE_STD_ZVAL(znull);
		ZVAL_NULL(znull);
		zend_update_property(THIS_CE, getThis(), ZEND_STRS("responseMessage")-1, znull TSRMLS_CC);
		zval_ptr_dtor(&znull);
		
		zend_update_property_long(THIS_CE, getThis(), ZEND_STRS("responseCode")-1, 0 TSRMLS_CC);
		zend_update_property_string(THIS_CE, getThis(), ZEND_STRS("responseStatus")-1, "" TSRMLS_CC);
		
		/* append request message to history */
		if (i_zend_is_true(zend_read_property(THIS_CE, getThis(), ZEND_STRS("recordHistory")-1, 0 TSRMLS_CC))) {
			http_message *request;
			
			if ((request = http_message_parse(PHPSTR_VAL(&obj->request->conv.request), PHPSTR_LEN(&obj->request->conv.request)))) {
				zval *hist, *history = zend_read_property(THIS_CE, getThis(), ZEND_STRS("history")-1, 0 TSRMLS_CC);
				
				MAKE_STD_ZVAL(hist);
				ZVAL_OBJVAL(hist, http_request_object_message(getThis(), request), 0);
				if (Z_TYPE_P(history) == IS_OBJECT) {
					http_message_object_prepend(hist, history);
				}
				zend_update_property(THIS_CE, getThis(), ZEND_STRS("history")-1, hist TSRMLS_CC);
				zval_ptr_dtor(&hist);
			}
		}
		
		ret = FAILURE;
	}
	
	http_request_set_progress_callback(obj->request, NULL);
	
	if (!EG(exception) && zend_hash_exists(&Z_OBJCE_P(getThis())->function_table, "onfinish", sizeof("onfinish"))) {
		zval *param;
		
		MAKE_STD_ZVAL(param);
		ZVAL_BOOL(param, ret == SUCCESS);
		with_error_handling(EH_NORMAL, NULL) {
			zend_call_method_with_1_params(&getThis(), Z_OBJCE_P(getThis()), NULL, "onfinish", NULL, param);
		} end_error_handling();
		zval_ptr_dtor(&param);
	}
	
	return ret;
}
#ifdef ZEND_ENGINE_2_4
#	define APK_DC TSRMLS_DC
#else
#	define APK_DC
#endif
static int apply_pretty_key(void *pDest APK_DC, int num_args, va_list args, zend_hash_key *hash_key)
{
	if (hash_key->arKey && hash_key->nKeyLength > 1) {
		hash_key->h = zend_hash_func(pretty_key(hash_key->arKey, hash_key->nKeyLength - 1, 1, 0), hash_key->nKeyLength);
	}
	return ZEND_HASH_APPLY_KEEP;
}

#define http_request_object_set_options_subr(key, ow, pk) \
	_http_request_object_set_options_subr(INTERNAL_FUNCTION_PARAM_PASSTHRU, (key), sizeof(key), (ow), (pk))
static inline void _http_request_object_set_options_subr(INTERNAL_FUNCTION_PARAMETERS, char *key, size_t len, int overwrite, int prettify_keys)
{
	zval *old_opts, *new_opts, *opts = NULL, **entry = NULL;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|a/!", &opts)) {
		RETURN_FALSE;
	}

	MAKE_STD_ZVAL(new_opts);
	array_init(new_opts);
	old_opts = zend_read_property(THIS_CE, getThis(), ZEND_STRS("options")-1, 0 TSRMLS_CC);
	if (Z_TYPE_P(old_opts) == IS_ARRAY) {
		array_copy(Z_ARRVAL_P(old_opts), Z_ARRVAL_P(new_opts));
	}

	if (SUCCESS == zend_hash_find(Z_ARRVAL_P(new_opts), key, len, (void *) &entry)) {
		if (overwrite) {
			zend_hash_clean(Z_ARRVAL_PP(entry));
		}
		if (opts && zend_hash_num_elements(Z_ARRVAL_P(opts))) {
			if (overwrite) {
				array_copy(Z_ARRVAL_P(opts), Z_ARRVAL_PP(entry));
			} else {
				array_join(Z_ARRVAL_P(opts), Z_ARRVAL_PP(entry), 0, prettify_keys ? ARRAY_JOIN_PRETTIFY : 0);
			}
		}
	} else if (opts) {
		if (prettify_keys) {
			zend_hash_apply_with_arguments(Z_ARRVAL_P(opts) HTTP_ZAPI_HASH_TSRMLS_CC, apply_pretty_key, 0, NULL);
		}
		ZVAL_ADDREF(opts);
		add_assoc_zval_ex(new_opts, key, len, opts);
	}
	zend_update_property(THIS_CE, getThis(), ZEND_STRS("options")-1, new_opts TSRMLS_CC);
	zval_ptr_dtor(&new_opts);

	RETURN_TRUE;
}

#define http_request_object_get_options_subr(key) \
	_http_request_get_options_subr(INTERNAL_FUNCTION_PARAM_PASSTHRU, (key), sizeof(key))
static inline void _http_request_get_options_subr(INTERNAL_FUNCTION_PARAMETERS, char *key, size_t len)
{
	NO_ARGS;

	if (return_value_used) {
		zval *opts, **options;

		opts = zend_read_property(THIS_CE, getThis(), ZEND_STRS("options")-1, 0 TSRMLS_CC);
		array_init(return_value);

		if (	(Z_TYPE_P(opts) == IS_ARRAY) && 
				(SUCCESS == zend_hash_find(Z_ARRVAL_P(opts), key, len, (void *) &options))) {
			convert_to_array(*options);
			array_copy(Z_ARRVAL_PP(options), Z_ARRVAL_P(return_value));
		}
	}
}


/* ### USERLAND ### */

/* {{{ proto void HttpRequest::__construct([string url[, int request_method = HTTP_METH_GET[, array options]]])
	Create a new HttpRequest object instance. */
PHP_METHOD(HttpRequest, __construct)
{
	char *URL = NULL;
	int URL_len;
	long meth = -1;
	zval *options = NULL;

	SET_EH_THROW_HTTP();
	if (SUCCESS == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|sla!", &URL, &URL_len, &meth, &options)) {
		if (URL) {
			zend_update_property_stringl(THIS_CE, getThis(), ZEND_STRS("url")-1, URL, URL_len TSRMLS_CC);
		}
		if (meth > -1) {
			zend_update_property_long(THIS_CE, getThis(), ZEND_STRS("method")-1, meth TSRMLS_CC);
		}
		if (options) {
			zend_call_method_with_1_params(&getThis(), Z_OBJCE_P(getThis()), NULL, "setoptions", NULL, options);
		}
	}
	SET_EH_NORMAL();
}
/* }}} */

/* {{{ proto HttpRequest HttpRequest::factory([string url[, int request_method HTTP_METH_GET[, array options[, string class_name = "HttpRequest"]]]])
	Create a new HttpRequest object instance. */
PHP_METHOD(HttpRequest, factory)
{
	char *cn = NULL, *URL = NULL;
	int cl = 0, URL_len = 0;
	long meth = -1;
	zval *options = NULL;
	zend_object_value ov;
	
	SET_EH_THROW_HTTP();
	if (	SUCCESS == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|sla!s", &URL, &URL_len, &meth, &options, &cn, &cl) &&
			SUCCESS == http_object_new(&ov, cn, cl, _http_request_object_new_ex, http_request_object_ce, NULL, NULL)) {
		RETVAL_OBJVAL(ov, 0);
		getThis() = return_value;
		if (URL) {
			zend_update_property_stringl(THIS_CE, getThis(), ZEND_STRS("url")-1, URL, URL_len TSRMLS_CC);
		}
		if (meth > -1) {
			zend_update_property_long(THIS_CE, getThis(), ZEND_STRS("method")-1, meth TSRMLS_CC);
		}
		if (options) {
			zend_call_method_with_1_params(&getThis(), Z_OBJCE_P(getThis()), NULL, "setoptions", NULL, options);
		}
	}
	SET_EH_NORMAL();
}
/* }}} */

/* {{{ proto bool HttpRequest::setOptions([array options])
	Set the request options to use.  See http_get() for a full list of available options. */
PHP_METHOD(HttpRequest, setOptions)
{
	HashKey key = initHashKey(0);
	HashPosition pos;
	zval *opts = NULL, *old_opts, *new_opts, *add_opts, **opt;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|a!/", &opts)) {
		RETURN_FALSE;
	}
	
	MAKE_STD_ZVAL(new_opts);
	array_init(new_opts);
		
	if (!opts || !zend_hash_num_elements(Z_ARRVAL_P(opts))) {
		zend_update_property(THIS_CE, getThis(), ZEND_STRS("options")-1, new_opts TSRMLS_CC);
		zval_ptr_dtor(&new_opts);
		RETURN_TRUE;
	}
	
	MAKE_STD_ZVAL(add_opts);
	array_init(add_opts);
	/* some options need extra attention -- thus cannot use array_merge() directly */
	FOREACH_KEYVAL(pos, opts, key, opt) {
		if (key.type == HASH_KEY_IS_STRING) {
#define KEYMATCH(k, s) ((sizeof(s)==k.len) && !strcasecmp(k.str, s))
			if (KEYMATCH(key, "headers")) {
				zend_call_method_with_1_params(&getThis(), Z_OBJCE_P(getThis()), NULL, "addheaders", NULL, *opt);
			} else if (KEYMATCH(key, "cookies")) {
				zend_call_method_with_1_params(&getThis(), Z_OBJCE_P(getThis()), NULL, "addcookies", NULL, *opt);
			} else if (KEYMATCH(key, "ssl")) {
				zend_call_method_with_1_params(&getThis(), Z_OBJCE_P(getThis()), NULL, "addssloptions", NULL, *opt);
			} else if (KEYMATCH(key, "url") || KEYMATCH(key, "uri")) {
				zend_call_method_with_1_params(&getThis(), Z_OBJCE_P(getThis()), NULL, "seturl", NULL, *opt);
			} else if (KEYMATCH(key, "method")) {
				zend_call_method_with_1_params(&getThis(), Z_OBJCE_P(getThis()), NULL, "setmethod", NULL, *opt);
			} else if (KEYMATCH(key, "flushcookies")) {
				getObject(http_request_object, obj);
				if (i_zend_is_true(*opt)) {
					http_request_flush_cookies(obj->request);
				}
			} else if (KEYMATCH(key, "resetcookies")) {
				getObject(http_request_object, obj);
				http_request_reset_cookies(obj->request, (zend_bool) i_zend_is_true(*opt));
			} else if (KEYMATCH(key, "enablecookies")) {
				getObject(http_request_object, obj);
				http_request_enable_cookies(obj->request);
			} else if (KEYMATCH(key, "recordHistory")) {
				zend_update_property(THIS_CE, getThis(), ZEND_STRS("recordHistory")-1, *opt TSRMLS_CC);
			} else if (KEYMATCH(key, "messageClass")) {
				zend_call_method_with_1_params(&getThis(), Z_OBJCE_P(getThis()), NULL, "setmessageclass", NULL, *opt);
			} else if (Z_TYPE_PP(opt) == IS_NULL) {
				old_opts = zend_read_property(THIS_CE, getThis(), ZEND_STRS("options")-1, 0 TSRMLS_CC);
				if (Z_TYPE_P(old_opts) == IS_ARRAY) {
					zend_hash_del(Z_ARRVAL_P(old_opts), key.str, key.len);
				}
			} else {
				ZVAL_ADDREF(*opt);
				add_assoc_zval_ex(add_opts, key.str, key.len, *opt);
			}
		}
	}
	
	old_opts = zend_read_property(THIS_CE, getThis(), ZEND_STRS("options")-1, 0 TSRMLS_CC);
	if (Z_TYPE_P(old_opts) == IS_ARRAY) {
		array_copy(Z_ARRVAL_P(old_opts), Z_ARRVAL_P(new_opts));
	}
	array_join(Z_ARRVAL_P(add_opts), Z_ARRVAL_P(new_opts), 0, 0);
	zend_update_property(THIS_CE, getThis(), ZEND_STRS("options")-1, new_opts TSRMLS_CC);
	zval_ptr_dtor(&new_opts);
	zval_ptr_dtor(&add_opts);
	
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto array HttpRequest::getOptions()
	Get currently set options. */
PHP_METHOD(HttpRequest, getOptions)
{
	NO_ARGS;

	if (return_value_used) {
		RETURN_PROP(options);
	}
}
/* }}} */

/* {{{ proto bool HttpRequest::setSslOptions([array options])
	Set SSL options. */
PHP_METHOD(HttpRequest, setSslOptions)
{
	http_request_object_set_options_subr("ssl", 1, 0);
}
/* }}} */

/* {{{ proto bool HttpRequest::addSslOptions(array options)
	Set additional SSL options. */
PHP_METHOD(HttpRequest, addSslOptions)
{
	http_request_object_set_options_subr("ssl", 0, 0);
}
/* }}} */

/* {{{ proto array HttpRequest::getSslOtpions()
	Get previously set SSL options. */
PHP_METHOD(HttpRequest, getSslOptions)
{
	http_request_object_get_options_subr("ssl");
}
/* }}} */

/* {{{ proto bool HttpRequest::addHeaders(array headers)
	Add request header name/value pairs. */
PHP_METHOD(HttpRequest, addHeaders)
{
	http_request_object_set_options_subr("headers", 0, 1);
}

/* {{{ proto bool HttpRequest::setHeaders([array headers])
	Set request header name/value pairs. */
PHP_METHOD(HttpRequest, setHeaders)
{
	http_request_object_set_options_subr("headers", 1, 1);
}
/* }}} */

/* {{{ proto array HttpRequest::getHeaders()
	Get previously set request headers. */
PHP_METHOD(HttpRequest, getHeaders)
{
	http_request_object_get_options_subr("headers");
}
/* }}} */

/* {{{ proto bool HttpRequest::setCookies([array cookies])
	Set cookies. */
PHP_METHOD(HttpRequest, setCookies)
{
	http_request_object_set_options_subr("cookies", 1, 0);
}
/* }}} */

/* {{{ proto bool HttpRequest::addCookies(array cookies)
	Add cookies. */
PHP_METHOD(HttpRequest, addCookies)
{
	http_request_object_set_options_subr("cookies", 0, 0);
}
/* }}} */

/* {{{ proto array HttpRequest::getCookies()
	Get previously set cookies. */
PHP_METHOD(HttpRequest, getCookies)
{
	http_request_object_get_options_subr("cookies");
}
/* }}} */

/* {{{ proto bool HttpRequest::enableCookies()
	Enable automatic sending of received cookies. Note that customly set cookies will be sent anyway. */
PHP_METHOD(HttpRequest, enableCookies)
{
	NO_ARGS {
		getObject(http_request_object, obj);
		RETURN_SUCCESS(http_request_enable_cookies(obj->request));
	}
	
}
/* }}} */

/* {{{ proto bool HttpRequest::resetCookies([bool session_only = FALSE])
	Reset all automatically received/sent cookies. Note that customly set cookies are not affected. */
PHP_METHOD(HttpRequest, resetCookies)
{
	zend_bool session_only = 0;
	getObject(http_request_object, obj);
	
	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|b", &session_only)) {
		RETURN_FALSE;
	}
	RETURN_SUCCESS(http_request_reset_cookies(obj->request, session_only));
}
/* }}} */

/* {{{ proto bool HttpRequest::flushCookies()
	Flush internal cookies to the cookiestore file */
PHP_METHOD(HttpRequest, flushCookies)
{
	NO_ARGS {
		getObject(http_request_object, obj);
		RETURN_SUCCESS(http_request_flush_cookies(obj->request));
	}
}
/* }}} */

/* {{{ proto bool HttpRequest::setUrl(string url)
	Set the request URL. */
PHP_METHOD(HttpRequest, setUrl)
{
	char *URL = NULL;
	int URL_len;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &URL, &URL_len)) {
		RETURN_FALSE;
	}

	zend_update_property_stringl(THIS_CE, getThis(), ZEND_STRS("url")-1, URL, URL_len TSRMLS_CC);
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string HttpRequest::getUrl()
	Get the previously set request URL. */
PHP_METHOD(HttpRequest, getUrl)
{
	NO_ARGS;

	if (return_value_used) {
		RETURN_PROP(url);
	}
}
/* }}} */

/* {{{ proto bool HttpRequest::setMethod(int request_method)
	Set the request method. */
PHP_METHOD(HttpRequest, setMethod)
{
	long meth;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &meth)) {
		RETURN_FALSE;
	}

	zend_update_property_long(THIS_CE, getThis(), ZEND_STRS("method")-1, meth TSRMLS_CC);
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto int HttpRequest::getMethod()
	Get the previously set request method. */
PHP_METHOD(HttpRequest, getMethod)
{
	NO_ARGS;

	if (return_value_used) {
		RETURN_PROP(method);
	}
}
/* }}} */

/* {{{ proto bool HttpRequest::setContentType(string content_type)
	Set the content type the post request should have. */
PHP_METHOD(HttpRequest, setContentType)
{
	char *ctype;
	int ct_len;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ctype, &ct_len)) {
		RETURN_FALSE;
	}

	if (ct_len) {
		HTTP_CHECK_CONTENT_TYPE(ctype, RETURN_FALSE);
	}
	zend_update_property_stringl(THIS_CE, getThis(), ZEND_STRS("contentType")-1, ctype, ct_len TSRMLS_CC);
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string HttpRequest::getContentType()
	Get the previously content type. */
PHP_METHOD(HttpRequest, getContentType)
{
	NO_ARGS;

	if (return_value_used) {
		RETURN_PROP(contentType);
	}
}
/* }}} */

/* {{{ proto bool HttpRequest::setQueryData([mixed query_data])
	Set the URL query parameters to use, overwriting previously set query parameters. */
PHP_METHOD(HttpRequest, setQueryData)
{
	zval *qdata = NULL;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z!", &qdata)) {
		RETURN_FALSE;
	}

	if ((!qdata) || Z_TYPE_P(qdata) == IS_NULL) {
		zend_update_property_stringl(THIS_CE, getThis(), ZEND_STRS("queryData")-1, "", 0 TSRMLS_CC);
	} else if ((Z_TYPE_P(qdata) == IS_ARRAY) || (Z_TYPE_P(qdata) == IS_OBJECT)) {
		char *query_data = NULL;
		
		if (SUCCESS != http_urlencode_hash(HASH_OF(qdata), &query_data)) {
			RETURN_FALSE;
		}
		
		zend_update_property_string(THIS_CE, getThis(), ZEND_STRS("queryData")-1, query_data TSRMLS_CC);
		efree(query_data);
	} else {
		zval *data = http_zsep(IS_STRING, qdata);
		
		zend_update_property_stringl(THIS_CE, getThis(), ZEND_STRS("queryData")-1, Z_STRVAL_P(data), Z_STRLEN_P(data) TSRMLS_CC);
		zval_ptr_dtor(&data);
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string HttpRequest::getQueryData()
	Get the current query data in form of an urlencoded query string. */
PHP_METHOD(HttpRequest, getQueryData)
{
	NO_ARGS;

	if (return_value_used) {
		RETURN_PROP(queryData);
	}
}
/* }}} */

/* {{{ proto bool HttpRequest::addQueryData(array query_params)
	Add parameters to the query parameter list, leaving previously set unchanged. */
PHP_METHOD(HttpRequest, addQueryData)
{
	zval *qdata, *old_qdata;
	char *query_data = NULL;
	size_t query_data_len = 0;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a/", &qdata)) {
		RETURN_FALSE;
	}

	old_qdata = zend_read_property(THIS_CE, getThis(), ZEND_STRS("queryData")-1, 0 TSRMLS_CC);

	if (SUCCESS != http_urlencode_hash_ex(HASH_OF(qdata), 1, Z_STRVAL_P(old_qdata), Z_STRLEN_P(old_qdata), &query_data, &query_data_len)) {
		RETURN_FALSE;
	}

	zend_update_property_stringl(THIS_CE, getThis(), ZEND_STRS("queryData")-1, query_data, query_data_len TSRMLS_CC);
	efree(query_data);

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool HttpRequest::addPostFields(array post_data)
	Adds POST data entries, leaving previously set unchanged, unless a post entry with the same name already exists. */
PHP_METHOD(HttpRequest, addPostFields)
{
	zval *post_data, *old_post, *new_post;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a/", &post_data)) {
		RETURN_FALSE;
	}

	if (zend_hash_num_elements(Z_ARRVAL_P(post_data))) {
		MAKE_STD_ZVAL(new_post);
		array_init(new_post);
		old_post = zend_read_property(THIS_CE, getThis(), ZEND_STRS("postFields")-1, 0 TSRMLS_CC);
		if (Z_TYPE_P(old_post) == IS_ARRAY) {
			array_copy(Z_ARRVAL_P(old_post), Z_ARRVAL_P(new_post));
		}
		array_join(Z_ARRVAL_P(post_data), Z_ARRVAL_P(new_post), 0, 0);
		zend_update_property(THIS_CE, getThis(), ZEND_STRS("postFields")-1, new_post TSRMLS_CC);
		zval_ptr_dtor(&new_post);
	}
	
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool HttpRequest::setPostFields([array post_data])
	Set the POST data entries, overwriting previously set POST data. */
PHP_METHOD(HttpRequest, setPostFields)
{
	zval *post, *post_data = NULL;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a/!", &post_data)) {
		RETURN_FALSE;
	}

	MAKE_STD_ZVAL(post);
	array_init(post);
	if (post_data && zend_hash_num_elements(Z_ARRVAL_P(post_data))) {
		array_copy(Z_ARRVAL_P(post_data), Z_ARRVAL_P(post));
	}
	zend_update_property(THIS_CE, getThis(), ZEND_STRS("postFields")-1, post TSRMLS_CC);
	zval_ptr_dtor(&post);

	RETURN_TRUE;
}
/* }}}*/

/* {{{ proto array HttpRequest::getPostFields()
	Get previously set POST data. */
PHP_METHOD(HttpRequest, getPostFields)
{
	NO_ARGS;

	if (return_value_used) {
		RETURN_PROP(postFields);
	}
}
/* }}} */

/* {{{ proto bool HttpRequest::setBody([string request_body_data])
	Set request body to send, overwriting previously set request body. Don't forget to specify a content type. */
PHP_METHOD(HttpRequest, setBody)
{
	char *raw_data = NULL;
	int data_len = 0;
	
	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &raw_data, &data_len)) {
		RETURN_FALSE;
	}
	
	if (!raw_data) {
		raw_data = "";
	}
	
	zend_update_property_stringl(THIS_CE, getThis(), ZEND_STRS("requestBody")-1, raw_data, data_len TSRMLS_CC);
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool HttpRequest::addBody(string request_body_data)
	Add request body data, leaving previously set request body data unchanged. */
PHP_METHOD(HttpRequest, addBody)
{
	char *raw_data;
	int data_len;
	
	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &raw_data, &data_len)) {
		RETURN_FALSE;
	}
	
	if (data_len) {
		zval *data = zend_read_property(THIS_CE, getThis(), ZEND_STRS("requestBody")-1, 0 TSRMLS_CC);
		
		if (Z_STRLEN_P(data)) {
			Z_STRVAL_P(data) = erealloc(Z_STRVAL_P(data), (Z_STRLEN_P(data) += data_len) + 1);
			Z_STRVAL_P(data)[Z_STRLEN_P(data)] = '\0';
			memcpy(Z_STRVAL_P(data) + Z_STRLEN_P(data) - data_len, raw_data, data_len);
		} else {
			zend_update_property_stringl(THIS_CE, getThis(), ZEND_STRS("requestBody")-1, raw_data, data_len TSRMLS_CC);
		}
	}
	
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string HttpRequest::getBody()
	Get previously set request body data. */
PHP_METHOD(HttpRequest, getBody)
{
	NO_ARGS;
	
	if (return_value_used) {
		RETURN_PROP(requestBody);
	}
}
/* }}} */

/* {{{ proto bool HttpRequest::addPostFile(string name, string file[, string content_type = "application/x-octetstream"])
	Add a file to the POST request, leaving previously set files unchanged. */
PHP_METHOD(HttpRequest, addPostFile)
{
	zval *entry, *old_post, *new_post;
	char *name, *file, *type = NULL;
	int name_len, file_len, type_len = 0;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|s", &name, &name_len, &file, &file_len, &type, &type_len)) {
		RETURN_FALSE;
	}

	if (type_len) {
		HTTP_CHECK_CONTENT_TYPE(type, RETURN_FALSE);
	} else {
		type = "application/x-octetstream";
		type_len = sizeof("application/x-octetstream") - 1;
	}

	MAKE_STD_ZVAL(entry);
	array_init(entry);

	add_assoc_stringl(entry, "name", name, name_len, 1);
	add_assoc_stringl(entry, "type", type, type_len, 1);
	add_assoc_stringl(entry, "file", file, file_len, 1);

	MAKE_STD_ZVAL(new_post);
	array_init(new_post);
	old_post = zend_read_property(THIS_CE, getThis(), ZEND_STRS("postFiles")-1, 0 TSRMLS_CC);
	if (Z_TYPE_P(old_post) == IS_ARRAY) {
		array_copy(Z_ARRVAL_P(old_post), Z_ARRVAL_P(new_post));
	}
	add_next_index_zval(new_post, entry);
	zend_update_property(THIS_CE, getThis(), ZEND_STRS("postFiles")-1, new_post TSRMLS_CC);
	zval_ptr_dtor(&new_post);

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool HttpRequest::setPostFiles([array post_files])
	Set files to post, overwriting previously set post files. */
PHP_METHOD(HttpRequest, setPostFiles)
{
	zval *files = NULL, *post;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a!/", &files)) {
		RETURN_FALSE;
	}

	MAKE_STD_ZVAL(post);
	array_init(post);
	if (files && (Z_TYPE_P(files) == IS_ARRAY)) {
		array_copy(Z_ARRVAL_P(files), Z_ARRVAL_P(post));
	}
	zend_update_property(THIS_CE, getThis(), ZEND_STRS("postFiles")-1, post TSRMLS_CC);
	zval_ptr_dtor(&post);

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto array HttpRequest::getPostFiles()
	Get all previously added POST files. */
PHP_METHOD(HttpRequest, getPostFiles)
{
	NO_ARGS;

	if (return_value_used) {
		RETURN_PROP(postFiles);
	}
}
/* }}} */

/* {{{ proto bool HttpRequest::setPutFile([string file])
	Set file to put. Affects only PUT requests. */
PHP_METHOD(HttpRequest, setPutFile)
{
	char *file = "";
	int file_len = 0;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &file, &file_len)) {
		RETURN_FALSE;
	}

	zend_update_property_stringl(THIS_CE, getThis(), ZEND_STRS("putFile")-1, file, file_len TSRMLS_CC);
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string HttpRequest::getPutFile()
	Get previously set put file. */
PHP_METHOD(HttpRequest, getPutFile)
{
	NO_ARGS;

	if (return_value_used) {
		RETURN_PROP(putFile);
	}
}
/* }}} */

/* {{{ proto bool HttpRequest::setPutData([string put_data])
	Set PUT data to send, overwriting previously set PUT data. */
PHP_METHOD(HttpRequest, setPutData)
{
	char *put_data = NULL;
	int data_len = 0;
	
	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &put_data, &data_len)) {
		RETURN_FALSE;
	}
	
	if (!put_data) {
		put_data = "";
	}
	
	zend_update_property_stringl(THIS_CE, getThis(), ZEND_STRS("putData")-1, put_data, data_len TSRMLS_CC);
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool HttpRequest::addPutData(string put_data)
	Add PUT data, leaving previously set PUT data unchanged. */
PHP_METHOD(HttpRequest, addPutData)
{
	char *put_data;
	int data_len;
	
	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &put_data, &data_len)) {
		RETURN_FALSE;
	}
	
	if (data_len) {
		zval *data = zend_read_property(THIS_CE, getThis(), ZEND_STRS("putData")-1, 0 TSRMLS_CC);
		
		if (Z_STRLEN_P(data)) {
			Z_STRVAL_P(data) = erealloc(Z_STRVAL_P(data), (Z_STRLEN_P(data) += data_len) + 1);
			Z_STRVAL_P(data)[Z_STRLEN_P(data)] = '\0';
			memcpy(Z_STRVAL_P(data) + Z_STRLEN_P(data) - data_len, put_data, data_len);
		} else {
			zend_update_property_stringl(THIS_CE, getThis(), ZEND_STRS("putData")-1, put_data, data_len TSRMLS_CC);
		}
	}
	
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string HttpRequest::getPutData()
	Get previously set PUT data. */
PHP_METHOD(HttpRequest, getPutData)
{
	NO_ARGS;
	
	if (return_value_used) {
		RETURN_PROP(putData);
	}
}
/* }}} */

/* {{{ proto array HttpRequest::getResponseData()
	Get all response data after the request has been sent. */
PHP_METHOD(HttpRequest, getResponseData)
{
	NO_ARGS;

	if (return_value_used) {
		char *body;
		size_t body_len;
		zval *headers, *message = zend_read_property(THIS_CE, getThis(), ZEND_STRS("responseMessage")-1, 0 TSRMLS_CC);
		
		if (Z_TYPE_P(message) == IS_OBJECT) {
			getObjectEx(http_message_object, msg, message);
			
			array_init(return_value);
			
			MAKE_STD_ZVAL(headers);
			array_init(headers);
			zend_hash_copy(Z_ARRVAL_P(headers), &msg->message->hdrs, (copy_ctor_func_t) zval_add_ref, NULL, sizeof(zval *));
			add_assoc_zval(return_value, "headers", headers);
			
			phpstr_data(PHPSTR(msg->message), &body, &body_len);
			add_assoc_stringl(return_value, "body", body, body_len, 0);
		}
	}
}
/* }}} */

/* {{{ proto mixed HttpRequest::getResponseHeader([string name])
	Get response header(s) after the request has been sent. */
PHP_METHOD(HttpRequest, getResponseHeader)
{
	if (return_value_used) {
		zval *header;
		char *header_name = NULL;
		int header_len = 0;

		if (SUCCESS == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &header_name, &header_len)) {
			zval *message = zend_read_property(THIS_CE, getThis(), ZEND_STRS("responseMessage")-1, 0 TSRMLS_CC);
			
			if (Z_TYPE_P(message) == IS_OBJECT) {
				getObjectEx(http_message_object, msg, message);
				
				if (header_len) {
					if ((header = http_message_header_ex(msg->message, pretty_key(header_name, header_len, 1, 1), header_len + 1, 0))) {
						RETURN_ZVAL(header, 1, 1);
					}
				} else {
					array_init(return_value);
					zend_hash_copy(Z_ARRVAL_P(return_value), &msg->message->hdrs, (copy_ctor_func_t) zval_add_ref, NULL, sizeof(zval *));
					return;
				}
			}
		}
		RETURN_FALSE;
	}
}
/* }}} */

/* {{{ proto array HttpRequest::getResponseCookies([int flags[, array allowed_extras]])
	Get response cookie(s) after the request has been sent. */
PHP_METHOD(HttpRequest, getResponseCookies)
{
	if (return_value_used) {
		long flags = 0;
		zval *allowed_extras_array = NULL;
		
		if (SUCCESS == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|la!", &flags, &allowed_extras_array)) {
			int i = 0;
			HashKey key = initHashKey(0);
			char **allowed_extras = NULL;
			zval **header = NULL, **entry = NULL, *message = zend_read_property(THIS_CE, getThis(), ZEND_STRS("responseMessage")-1, 0 TSRMLS_CC);
			HashPosition pos, pos1, pos2;
			
			if (Z_TYPE_P(message) == IS_OBJECT) {
				getObjectEx(http_message_object, msg, message);
				
				array_init(return_value);
				
				if (allowed_extras_array) {
					allowed_extras = ecalloc(zend_hash_num_elements(Z_ARRVAL_P(allowed_extras_array)) + 1, sizeof(char *));
					FOREACH_VAL(pos, allowed_extras_array, entry) {
						zval *data = http_zsep(IS_STRING, *entry);
						allowed_extras[i++] = estrndup(Z_STRVAL_P(data), Z_STRLEN_P(data));
						zval_ptr_dtor(&data);
					}
				}
				
				FOREACH_HASH_KEYVAL(pos1, &msg->message->hdrs, key, header) {
					if (key.type == HASH_KEY_IS_STRING && !strcasecmp(key.str, "Set-Cookie")) {
						http_cookie_list list;
						
						if (Z_TYPE_PP(header) == IS_ARRAY) {
							zval **single_header;
							
							FOREACH_VAL(pos2, *header, single_header) {
								zval *data = http_zsep(IS_STRING, *single_header);
								
								if (http_parse_cookie_ex(&list, Z_STRVAL_P(data), flags, allowed_extras)) {
									zval *cookie;
									
									MAKE_STD_ZVAL(cookie);
									object_init(cookie);
									http_cookie_list_tostruct(&list, cookie);
									add_next_index_zval(return_value, cookie);
									http_cookie_list_dtor(&list);
								}
								zval_ptr_dtor(&data);
							}
						} else {
							zval *data = http_zsep(IS_STRING, *header);
							if (http_parse_cookie_ex(&list, Z_STRVAL_P(data), flags, allowed_extras)) {
								zval *cookie;
								
								MAKE_STD_ZVAL(cookie);
								object_init(cookie);
								http_cookie_list_tostruct(&list, cookie);
								add_next_index_zval(return_value, cookie);
								http_cookie_list_dtor(&list);
							}
							zval_ptr_dtor(&data);
						}
					}
				}
				
				if (allowed_extras) {
					for (i = 0; allowed_extras[i]; ++i) {
						efree(allowed_extras[i]);
					}
					efree(allowed_extras);
				}
				
				return;
			}
		}
		RETURN_FALSE;
	}
}
/* }}} */

/* {{{ proto string HttpRequest::getResponseBody()
	Get the response body after the request has been sent. */
PHP_METHOD(HttpRequest, getResponseBody)
{
	NO_ARGS;

	if (return_value_used) {
		zval *message = zend_read_property(THIS_CE, getThis(), ZEND_STRS("responseMessage")-1, 0 TSRMLS_CC);
		
		if (Z_TYPE_P(message) == IS_OBJECT) {
			getObjectEx(http_message_object, msg, message);
			RETURN_PHPSTR_DUP(&msg->message->body);
		} else {
			RETURN_FALSE;
		}
	}
}
/* }}} */

/* {{{ proto int HttpRequest::getResponseCode()
	Get the response code after the request has been sent. */
PHP_METHOD(HttpRequest, getResponseCode)
{
	NO_ARGS;

	if (return_value_used) {
		RETURN_PROP(responseCode);
	}
}
/* }}} */

/* {{{ proto string HttpRequest::getResponseStatus()
	Get the response status (i.e. the string after the response code) after the message has been sent. */
PHP_METHOD(HttpRequest, getResponseStatus)
{
	NO_ARGS;
	
	if (return_value_used) {
		RETURN_PROP(responseStatus);
	}
}
/* }}} */

/* {{{ proto mixed HttpRequest::getResponseInfo([string name])
	Get response info after the request has been sent. */
PHP_METHOD(HttpRequest, getResponseInfo)
{
	if (return_value_used) {
		zval *info, **infop;
		char *info_name = NULL;
		int info_len = 0;

		if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &info_name, &info_len)) {
			RETURN_FALSE;
		}

		info = zend_read_property(THIS_CE, getThis(), ZEND_STRS("responseInfo")-1, 0 TSRMLS_CC);
		
		if (Z_TYPE_P(info) != IS_ARRAY) {
			RETURN_FALSE;
		}

		if (info_len && info_name) {
			if (SUCCESS == zend_hash_find(Z_ARRVAL_P(info), pretty_key(info_name, info_len, 0, 0), info_len + 1, (void *) &infop)) {
				RETURN_ZVAL(*infop, 1, 0);
			} else {
				http_error_ex(HE_NOTICE, HTTP_E_INVALID_PARAM, "Could not find response info named %s", info_name);
				RETURN_FALSE;
			}
		} else {
			RETURN_ZVAL(info, 1, 0);
		}
	}
}
/* }}}*/

/* {{{ proto HttpMessage HttpRequest::getResponseMessage()
	Get the full response as HttpMessage object after the request has been sent. */
PHP_METHOD(HttpRequest, getResponseMessage)
{
	NO_ARGS {
		zval *message;

		SET_EH_THROW_HTTP();
		message = zend_read_property(THIS_CE, getThis(), ZEND_STRS("responseMessage")-1, 0 TSRMLS_CC);
		if (Z_TYPE_P(message) == IS_OBJECT) {
			RETVAL_OBJECT(message, 1);
		} else {
			http_error(HE_WARNING, HTTP_E_RUNTIME, "HttpRequest does not contain a response message");
		}
		SET_EH_NORMAL();
	}
}
/* }}} */

/* {{{ proto HttpMessage HttpRequest::getRequestMessage()
	Get sent HTTP message. */
PHP_METHOD(HttpRequest, getRequestMessage)
{
	NO_ARGS;

	if (return_value_used) {
		http_message *msg;
		getObject(http_request_object, obj);

		SET_EH_THROW_HTTP();
		if ((msg = http_message_parse(PHPSTR_VAL(&obj->request->conv.request), PHPSTR_LEN(&obj->request->conv.request)))) {
			RETVAL_OBJVAL(http_request_object_message(getThis(), msg), 0);
		}
		SET_EH_NORMAL();
	}
}
/* }}} */

/* {{{ proto string HttpRequest::getRawRequestMessage()
	Get sent HTTP message. */
PHP_METHOD(HttpRequest, getRawRequestMessage)
{
	NO_ARGS;

	if (return_value_used) {
		getObject(http_request_object, obj);

		RETURN_PHPSTR_DUP(&obj->request->conv.request);
	}
}
/* }}} */

/* {{{ proto string HttpRequest::getRawResponseMessage()
	Get the entire HTTP response. */
PHP_METHOD(HttpRequest, getRawResponseMessage)
{
	NO_ARGS;

	if (return_value_used) {
		getObject(http_request_object, obj);

		RETURN_PHPSTR_DUP(&obj->request->conv.response);
	}
}
/* }}} */

/* {{{ proto HttpMessage HttpRequest::getHistory()
	Get all sent requests and received responses as an HttpMessage object. */
PHP_METHOD(HttpRequest, getHistory)
{
	NO_ARGS;

	if (return_value_used) {
		zval *hist;
		
		SET_EH_THROW_HTTP();
		hist = zend_read_property(THIS_CE, getThis(), ZEND_STRS("history")-1, 0 TSRMLS_CC);
		if (Z_TYPE_P(hist) == IS_OBJECT) {
			RETVAL_OBJECT(hist, 1);
		} else {
			http_error(HE_WARNING, HTTP_E_RUNTIME, "The history is empty");
		}
		SET_EH_NORMAL();
	}
}
/* }}} */

/* {{{ proto void HttpRequest::clearHistory()
	Clear the history. */
PHP_METHOD(HttpRequest, clearHistory)
{
	NO_ARGS {
		zval *hist;
		
		MAKE_STD_ZVAL(hist);
		ZVAL_NULL(hist);
		zend_update_property(THIS_CE, getThis(), ZEND_STRS("history")-1, hist TSRMLS_CC);
		zval_ptr_dtor(&hist);
	}
}
/* }}} */

/* {{{ proto string HttpRequest::getMessageClass()
	Get the message class name. */
PHP_METHOD(HttpRequest, getMessageClass)
{
	NO_ARGS;

	if (return_value_used) {
		RETURN_PROP("messageClass");
	}
}
/* }}} */

/* {{{ proto void setMessageClass(string class_name)
	Set the message class name. */
PHP_METHOD(HttpRequest, setMessageClass)
{
	char *cn;
	int cl;

	if (SUCCESS == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &cn, &cl)) {
		zend_update_property_stringl(THIS_CE, getThis(), ZEND_STRS("messageClass")-1, cn, cl TSRMLS_CC);
	}
}
/* }}} */

/* {{{ proto HttpMessage HttpRequest::send()
	Send the HTTP request. */
PHP_METHOD(HttpRequest, send)
{
	getObject(http_request_object, obj);

	NO_ARGS;

	SET_EH_THROW_HTTP();

	RETVAL_FALSE;
	
	if (obj->pool) {
		http_error(HE_WARNING, HTTP_E_RUNTIME, "Cannot perform HttpRequest::send() while attached to an HttpRequestPool");
	} else if (SUCCESS == http_request_object_requesthandler(obj, getThis())) {
		http_request_exec(obj->request);
		if (SUCCESS == http_request_object_responsehandler(obj, getThis())) {
			RETVAL_OBJECT(zend_read_property(THIS_CE, getThis(), ZEND_STRS("responseMessage")-1, 0 TSRMLS_CC), 1);
		}
	}

	SET_EH_NORMAL();
}
/* }}} */

#endif /* ZEND_ENGINE_2 && HTTP_HAVE_CURL */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

