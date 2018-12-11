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

#ifndef PHP_HTTP_INFO_API_H
#define PHP_HTTP_INFO_API_H

#define IS_HTTP_REQUEST		1
#define IS_HTTP_RESPONSE	2

#define HTTP_INFO(ptr) (ptr)->http.info

#define HTTP_INFO_REQUEST_FMT_ARGS(_http_ptr, _EOL) "%s %s HTTP/%1.1f" _EOL, \
				(_http_ptr)->info.request.method?(_http_ptr)->info.request.method:"UNKNOWN", \
				(_http_ptr)->info.request.url?(_http_ptr)->info.request.url:"/", \
				(_http_ptr)->version>0.0?(_http_ptr)->version:1.1

#define HTTP_INFO_RESPONSE_FMT_ARGS(_http_ptr, _EOL) "HTTP/%1.1f %d%s%s" _EOL, \
				(_http_ptr)->version>0.0?(_http_ptr)->version:1.1, \
				(_http_ptr)->info.response.code?(_http_ptr)->info.response.code:200, \
				(_http_ptr)->info.response.status&&*(_http_ptr)->info.response.status ? " ":"", \
				STR_PTR((_http_ptr)->info.response.status)

typedef struct _http_request_info_t {
	char *method;
	char *url;
} http_request_info;

typedef struct _http_response_info_t {
	int code;
	char *status;
} http_response_info;

typedef union _http_info_union_t {
	http_request_info request;
	http_response_info response;
} http_info_union;

struct http_info {
	http_info_union info;
	double version;
};

typedef struct _http_info_t {
	struct http_info http;
	int type;
} http_info;

typedef void (*http_info_callback)(void **callback_data, HashTable **headers, http_info *info TSRMLS_DC);

#define http_info_default_callback _http_info_default_callback
PHP_HTTP_API void _http_info_default_callback(void **nothing, HashTable **headers, http_info *info TSRMLS_DC);
#define http_info_dtor _http_info_dtor
PHP_HTTP_API void _http_info_dtor(http_info *info);
#define http_info_parse(p, i) _http_info_parse_ex((p), (i), 1 TSRMLS_CC)
#define http_info_parse_ex(p, i, s) _http_info_parse_ex((p), (i), (s) TSRMLS_CC)
PHP_HTTP_API STATUS _http_info_parse_ex(const char *pre_header, http_info *info , zend_bool silent TSRMLS_DC);

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

