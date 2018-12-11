/*
  +----------------------------------------------------------------------+
  | PHP Version 4                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2002 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available at through the world-wide-web at                           |
  | http://www.php.net/license/3_0.txt.                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Frank M. Kromann <frank@kromann.info>                        |
  +----------------------------------------------------------------------+

  $Id: header,v 1.10 2002/02/28 08:25:27 sebastian Exp $ 
*/


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_win32std.h"

/* True global resources - no need for thread safety here */
/*static*/ int le_key;


void php_hkey_close(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	registry_hkey *hKey = (registry_hkey *)rsrc->ptr;

	RegCloseKey(hKey->hKey);
	efree(hKey);
}

static HKEY _registry_get_hkey(zval **zhKey TSRMLS_DC) {
	HKEY hKey;
	switch (Z_TYPE_PP(zhKey)) {
		case IS_LONG :
			switch (Z_LVAL_PP(zhKey)) {
				case 0 :
					hKey = HKEY_CLASSES_ROOT;
					break;
				case 1 :
					hKey = HKEY_CURRENT_CONFIG;
					break;
				case 2 :
					hKey = HKEY_CURRENT_USER;
					break;
				case 3 :
					hKey = HKEY_LOCAL_MACHINE;
					break;
				case 4 :
					hKey = HKEY_USERS;
					break;
			}
			break;
		case IS_RESOURCE :
			{
				registry_hkey *open_hkey;

				open_hkey = (registry_hkey *) zend_fetch_resource(zhKey TSRMLS_CC, -1, le_key_resource_name, NULL, 1, le_key);
				if (open_hkey)
					hKey = open_hkey->hKey;
				else
					hKey = NULL;
			}
			break;
		default :
			hKey = NULL;
			break;
	}

	return hKey;
}


/* {{{ proto void reg_close_key(resource hKey)
   */
PHP_FUNCTION(reg_close_key)
{
	zval *zhKey;
	registry_hkey *reg_hkey;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zhKey) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(reg_hkey, registry_hkey *, &zhKey, -1, le_key_resource_name, le_key);

	zend_list_delete(Z_RESVAL_P(zhKey));
}
/* }}} */


/* {{{ proto resource reg_create_key(mixed hKey, string subkey [, int samDesired = KEY_ALL_ACCESS])
   */
PHP_FUNCTION(reg_create_key)
{
	zval *zhKey;
	long samDesired_arg = 0;
	char *arg = NULL;
	int arg_len;

	HKEY hKey;
	HKEY hkResult;
	REGSAM samDesired = KEY_ALL_ACCESS;
	DWORD dwDisposition;
	LONG rc;

    char buffer[WIN32_STRERROR_BUFFER_LEN];

	registry_hkey *reg_hkey;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zs|l", &zhKey, &arg, &arg_len, &samDesired_arg) == FAILURE) {
		return;
	}

	hKey = _registry_get_hkey(&zhKey TSRMLS_CC);

	rc = RegCreateKeyEx(hKey, arg, 0, NULL, REG_OPTION_NON_VOLATILE, samDesired, NULL, &hkResult, &dwDisposition);
	if (rc != ERROR_SUCCESS) {
        zend_error( E_WARNING, "Can't create registry key: %s", win32_strerror(buffer, WIN32_STRERROR_BUFFER_LEN) );
		RETURN_FALSE;
	}
	else {
		reg_hkey = (registry_hkey *) emalloc(sizeof(registry_hkey));
		reg_hkey->hKey = hkResult;
		ZEND_REGISTER_RESOURCE(return_value, reg_hkey, le_key);
	}
}
/* }}} */

/* {{{ proto mixed reg_enum_key(mixed hKey[, int index=1])
   */
PHP_FUNCTION(reg_enum_key)
{
	zval *zhKey;
	long index = -1;
	char buf[MAX_SUBKEY_LEN];
	DWORD buf_len = MAX_SUBKEY_LEN;
	FILETIME LastWriteTime;

	HKEY hKey;
	LONG rc;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|l", &zhKey, &index) == FAILURE) {
		return;
	}

	hKey = _registry_get_hkey(&zhKey TSRMLS_CC);

	if( index>-1 ) {
		rc = RegEnumKeyEx(hKey, index, buf, &buf_len, NULL, NULL, NULL, &LastWriteTime);
		if (rc != ERROR_SUCCESS) {
			if( rc!=ERROR_NO_MORE_ITEMS )
				zend_error( E_WARNING, "Can't enum registry keys: %s", win32_strerror(buf, MAX_SUBKEY_LEN) );
			RETURN_FALSE;
		}
		else {
			RETURN_STRINGL(buf, buf_len, 1);
		}
	}

	// Return array
	array_init(return_value);
	for( index= 0, buf_len = MAX_SUBKEY_LEN; (rc= RegEnumKeyEx(hKey, index, buf, &buf_len, NULL, NULL, NULL, &LastWriteTime))==ERROR_SUCCESS; index++ ) {
		add_next_index_string( return_value, buf, buf_len+1 );
		buf_len = MAX_SUBKEY_LEN;
	}
	if( rc!=ERROR_NO_MORE_ITEMS )
		zend_error( E_WARNING, "Can't enum registry keys: %s", win32_strerror(buf, MAX_SUBKEY_LEN) );
}
/* }}} */

/* {{{ proto mixed reg_enum_value(mixed hKey[, int index=-1])
   */
PHP_FUNCTION(reg_enum_value)
{
	zval *zhKey;
	long index = -1;
	char buf[MAX_SUBKEY_LEN];
	DWORD buf_len = MAX_SUBKEY_LEN;
	HKEY hKey;
	LONG rc;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|l", &zhKey, &index) == FAILURE) {
		return;
	}

	hKey = _registry_get_hkey(&zhKey TSRMLS_CC);

	if( index>-1 ) {
		rc = RegEnumValue(hKey, index, buf, &buf_len, NULL, NULL, NULL, NULL);
		if (rc != ERROR_SUCCESS) {
			if( rc!=ERROR_NO_MORE_ITEMS )
				zend_error( E_WARNING, "Can't enum registry values: %s", win32_strerror(buf, MAX_SUBKEY_LEN) );
			RETURN_FALSE;
		}
		else {
			RETURN_STRINGL(buf, buf_len, 1);
		}
	}

	// Return array
	array_init(return_value);
	for( index= 0, buf_len = MAX_SUBKEY_LEN; (rc= RegEnumValue(hKey, index, buf, &buf_len, NULL, NULL, NULL, NULL))==ERROR_SUCCESS; index++ ) {
		add_next_index_string( return_value, buf, buf_len+1 );
		buf_len = MAX_SUBKEY_LEN;
	}
	if( rc!=ERROR_NO_MORE_ITEMS )
		zend_error( E_WARNING, "Can't enum registry values: %s", win32_strerror(buf, MAX_SUBKEY_LEN) );
}
/* }}} */

/* {{{ proto resource reg_open_key(mixed hKey, string subkey [, int samDesired = KEY_ALL_ACCESS])
   */
PHP_FUNCTION(reg_open_key)
{
	zval *zhKey;
	long samDesired_arg = 0;
	char *arg = NULL;
	int arg_len;

	HKEY hKey;
	HKEY hkResult;
	REGSAM samDesired = KEY_ALL_ACCESS;
	LONG rc;

    char buffer[WIN32_STRERROR_BUFFER_LEN];

	registry_hkey *reg_hkey;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zs|l", &zhKey, &arg, &arg_len, &samDesired_arg) == FAILURE) {
		return;
	}

	hKey = _registry_get_hkey(&zhKey TSRMLS_CC);

	rc = RegOpenKeyEx(hKey, arg, 0, samDesired, &hkResult);
	if (rc != ERROR_SUCCESS) {
        zend_error( E_WARNING, "Can't open registry key: %s", win32_strerror(buffer, WIN32_STRERROR_BUFFER_LEN) );
		RETURN_FALSE;
	}
	else {
		reg_hkey = (registry_hkey *) emalloc(sizeof(registry_hkey));
		reg_hkey->hKey = hkResult;
		ZEND_REGISTER_RESOURCE(return_value, reg_hkey, le_key);
	}
}
/* }}} */

/* {{{ proto bool reg_set_value(mixed hKey, string value_name, int type, mixed value)
   */
PHP_FUNCTION(reg_set_value)
{
	zval *zhKey, *value;
	long value_type = REG_DWORD;
	char *value_name = NULL;
	int value_len;

	HKEY hKey;
	CONST BYTE *lpData;  // address of value data
	DWORD cbData;         // size of value data
	LONG rc;

    char buffer[WIN32_STRERROR_BUFFER_LEN];

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zslz", &zhKey, &value_name, &value_len, &value_type, &value) == FAILURE) {
		return;
	}

	hKey = _registry_get_hkey(&zhKey TSRMLS_CC);

	switch (value_type) {
		case REG_DWORD :
			convert_to_long(value);
			lpData = (BYTE *)&Z_LVAL_P(value);
			cbData = sizeof(DWORD);
			break;
		case REG_EXPAND_SZ:
		case REG_SZ :
			convert_to_string(value);
			lpData = Z_STRVAL_P(value);
			cbData = Z_STRLEN_P(value) + 1;
			break;
		default :
            zend_error( E_WARNING, "registry value type not handled" );
			RETURN_FALSE;
			break;
	}
	rc = RegSetValueEx(hKey, value_name, 0, value_type, lpData, cbData);
	if (rc != ERROR_SUCCESS) {
        zend_error( E_WARNING, "Can't set registry value for value '%s': %s", value_name, win32_strerror(buffer, WIN32_STRERROR_BUFFER_LEN) );
		RETURN_FALSE;
	}
	else {
		RETURN_TRUE;
	}
}
/* }}} */

/* {{{ proto mixed reg_get_value(mixed hKey, string value_name)
   */
PHP_FUNCTION(reg_get_value)
{
	zval *zhKey;
	char *value_name = NULL;
	int value_len;

	HKEY hKey;
	DWORD value_type;
	BYTE *buf = NULL;
	DWORD buf_len;
	LONG rc;

    char buffer[WIN32_STRERROR_BUFFER_LEN];

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zs", &zhKey, &value_name, &value_len) == FAILURE) {
		return;
	}

	hKey = _registry_get_hkey(&zhKey TSRMLS_CC);

	rc = RegQueryValueEx(hKey, value_name, NULL, &value_type, NULL, &buf_len);
	if (rc != ERROR_SUCCESS) {
		RETURN_FALSE;
	}
	else {
		buf = (BYTE *)emalloc(buf_len);
		rc = RegQueryValueEx(hKey, value_name, NULL, &value_type, buf, &buf_len);
		if (rc != ERROR_SUCCESS) {
            zend_error( E_WARNING, "Can't get registry value '%s': %s", value_name, win32_strerror(buffer, WIN32_STRERROR_BUFFER_LEN) );
			RETVAL_FALSE;
		}
		else {
			switch (value_type) {
				case REG_DWORD :
					RETVAL_LONG(*((DWORD *)buf));
					break;
				case REG_EXPAND_SZ:
				case REG_SZ :
					RETVAL_STRINGL((char *)buf, buf_len-1, 1);
					break;
				default :
					RETVAL_FALSE;
					break;
			}
		}
		if (buf) efree(buf);
	}
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
