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
  | Author: Eric COLINET <e.colinet@laposte.net>                         |
  +----------------------------------------------------------------------+
*/


#include "php_win32std.h"

/*
TODO:
    - verifier play_soud avec res
    - resource delete bug ???
*/


#ifndef IS_INTRESOURCE
#define IS_INTRESOURCE(_r) (((DWORD)(_r) >> 16) == 0)
#endif

/* static */ int le_res_resource;


void _php_res_destruction_handler(zend_rsrc_list_entry *rsrc TSRMLS_DC) {
    HMODULE module = (HMODULE) rsrc->ptr;
    if( module )
		FreeLibrary(module);
}

/* {{{ proto resource res_open( module_name )
	Return a (PHP)resource that identify the (WIN)resource module handle
*/
PHP_FUNCTION(res_open)
{
	HMODULE h_module= NULL;
	char *module= NULL;
	long module_len;
    char buffer[WIN32_STRERROR_BUFFER_LEN];
    //res_resource * res_rc;

	if( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s", &module, &module_len ) == FAILURE ) 
		RETURN_LONG(-1);

	// if module=="" module is the current executable
	if( !module_len  )
        h_module= NULL;
    else {
	    h_module= LoadLibrary(module);
	    if( !h_module ) { 
		    zend_error(E_WARNING, "res_open '%s' failed: %s", module, win32_strerror(buffer, WIN32_STRERROR_BUFFER_LEN)); 
		    RETURN_FALSE
	    }
    }

    ZEND_REGISTER_RESOURCE( return_value, h_module, le_res_resource );
}
/* }}} */


/* {{{ proto bool res_close( resouce module )
	Close a module handle
*/
PHP_FUNCTION(res_close)
{
	zval *res_rc;
    HMODULE h;

	if( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "r", &res_rc ) == FAILURE ) 
		RETURN_FALSE
    
    ZEND_FETCH_RESOURCE(h, HMODULE, &res_rc, -1, le_res_resource_name, le_res_resource);

    zend_list_delete(Z_RESVAL_P(res_rc));

	RETURN_TRUE;
}
/* }}} */


/* {{{ proto res_get( resource module, string type, string name[, int lang] )
	Get a resource. 
	lang is experimental: 0 is neutral, 1 is user default, 2 is system default (see winnt.h LANG_* & SUBLANG_*).
*/
PHP_FUNCTION(res_get)
{
	DWORD size;
	HGLOBAL rc;
	HMODULE h_module= NULL;
	HRSRC hr;
	char *module= NULL, *name= NULL, *type= NULL;
	long name_len, type_len;
    long lang= MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);
    char buffer[WIN32_STRERROR_BUFFER_LEN];
    zval *res_rc;

	if( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "rss|l", &res_rc, &type, &type_len, &name, &name_len, &lang ) == FAILURE ) 
		RETURN_NULL();

    if( !name_len || !type_len ) {
        zend_error(E_WARNING, "res_get: name or type can't be empty"); 
        RETURN_NULL();
    }

    ZEND_FETCH_RESOURCE(h_module, HMODULE, &res_rc, -1, le_res_resource_name, le_res_resource);

    // Convert name and type to uppercase since lowercase don't work
    strupr(name);
    strupr(type);

    if( ZEND_NUM_ARGS()>3 )
        hr= FindResourceEx( h_module, name, type, (WORD)lang );
    else
        hr= FindResource( h_module, name, type );
	if( hr==NULL ) {
        zend_error(E_WARNING, "res_get: find '%s/%s' failed: %s", type, name, win32_strerror(buffer, WIN32_STRERROR_BUFFER_LEN)); 
		RETURN_NULL( );
	}

	rc= LoadResource( h_module, hr );
	if( rc==NULL ) {
        zend_error(E_WARNING, "res_get: load '%s/%s' failed: %s", type, name, win32_strerror(buffer, WIN32_STRERROR_BUFFER_LEN)); 
		RETURN_NULL( );
	}

	size= SizeofResource( h_module, hr );

	RETVAL_STRINGL((char*)rc, size, 1);
}
/* }}} */


/* {{{ proto bool res_set( string file, string type, string name, string data[, int lang] )
	Add or modify a resource in 'file' (dll or exe)
	lang is experimental: 0 is neutral, 1 is user default, 2 is system default (see winnt.h LANG_* & SUBLANG_*).
*/
PHP_FUNCTION(res_set)
{
	HANDLE h_module;
	char *module, *type, *name, *data;
	int module_len, type_len, name_len, data_len;
    char buffer[WIN32_STRERROR_BUFFER_LEN];
    long lang= MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);


	if( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "ssss|l", 
		&module, &module_len, 
		&type, &type_len, 
		&name, &name_len,
		&data, &data_len, &lang ) == FAILURE ) 
		RETURN_FALSE;

	//zend_error( E_WARNING, "res_set modifie res://%s/%s/%s avec %d octets",
	//	module, type, name, data_len );

	if( !module_len || !type_len || !name_len ) {
        zend_error(E_WARNING, "res_set: module file, type or name can't be empty" );
		RETURN_FALSE;
	}

    // Convert name and type to uppercase since lowercase don't work
    strupr(name);
    strupr(type);

    h_module= BeginUpdateResource( module, FALSE );
	if( h_module==NULL ) { 
        zend_error(E_WARNING, "res_set: error opening module: %s", win32_strerror(buffer, WIN32_STRERROR_BUFFER_LEN) );
		RETURN_FALSE; 
	}

	if( UpdateResource( h_module, type, name, (WORD)lang, data, data_len )==0 ) {
        zend_error(E_WARNING, "res_set: error updating module: %s", win32_strerror(buffer, WIN32_STRERROR_BUFFER_LEN) );
        EndUpdateResource(h_module, TRUE);
        RETURN_FALSE;
	}

	EndUpdateResource(h_module, FALSE);

	RETURN_TRUE;
}
/* }}} */


long php_res_list_get_int_type( const char * string_type )
{
	if( !strcmp( string_type, "RT_CURSOR" ) ) return (long)RT_CURSOR;
	if( !strcmp( string_type, "RT_BITMAP" ) ) return (long)RT_BITMAP;
	if( !strcmp( string_type, "RT_ICON" ) ) return (long)RT_ICON;
	if( !strcmp( string_type, "RT_MENU" ) ) return (long)RT_MENU;
	if( !strcmp( string_type, "RT_DIALOG" ) ) return (long)RT_DIALOG;
	if( !strcmp( string_type, "RT_STRING" ) ) return (long)RT_STRING;
	if( !strcmp( string_type, "RT_FONTDIR" ) ) return (long)RT_FONTDIR;
	if( !strcmp( string_type, "RT_FONT" ) ) return (long)RT_FONT;
	if( !strcmp( string_type, "RT_ACCELERATOR" ) ) return (long)RT_ACCELERATOR;
	if( !strcmp( string_type, "RT_RCDATA" ) ) return (long)RT_RCDATA;
	if( !strcmp( string_type, "RT_MESSAGETABLE" ) ) return (long)RT_MESSAGETABLE;
	if( !strcmp( string_type, "RT_GROUP_CURSOR" ) ) return (long)RT_GROUP_CURSOR;
	if( !strcmp( string_type, "RT_GROUP_ICON" ) ) return (long)RT_GROUP_ICON;
	if( !strcmp( string_type, "RT_VERSION" ) ) return (long)RT_VERSION;
	if( !strcmp( string_type, "RT_DLGINCLUDE" ) ) return (long)RT_DLGINCLUDE;
	if( !strcmp( string_type, "RT_PLUGPLAY" ) ) return (long)RT_PLUGPLAY;
	if( !strcmp( string_type, "RT_VXD" ) ) return (long)RT_VXD;
	if( !strcmp( string_type, "RT_ANICURSOR" ) ) return (long)RT_ANICURSOR;
	if( !strcmp( string_type, "RT_ANIICON" ) ) return (long)RT_ANIICON;
	if( !strcmp( string_type, "RT_HTML" ) ) return (long)RT_HTML;
	//if( !strcmp( string_type, "RT_NOT_DOCUMENTED" ) ) return 241;
	return -1;
}


BOOL CALLBACK php_res_list_callback( 
  HMODULE h_module,  // module handle
  LPCTSTR lpszType,  // pointer to resource type
  LPTSTR lpszName,   // pointer to resource name
  LONG lParam        // application-defined parameter
)
{
	char buffer[8];
	zval * array= (zval*) lParam;
	if( !IS_INTRESOURCE(lpszName) )
		add_next_index_string(array, lpszName, 1);
	else 	{
		sprintf( buffer, "#%d", lpszName );
		add_next_index_string(array, buffer, 1);
	}
	return TRUE;
}


/* {{{ proto array res_list( resource module, string type )
	return the resource list for a given type
*/
PHP_FUNCTION(res_list)
{
	char *module= NULL, *type= NULL;
	long type_len;
	HMODULE h_module= NULL;
	BOOL ret= FALSE;
	long int_type=-1;
    char buffer[WIN32_STRERROR_BUFFER_LEN];
    zval * res_rc;

	if( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "rs", &res_rc, &type, &type_len ) == FAILURE ) 
		RETURN_FALSE;
    ZEND_FETCH_RESOURCE(h_module, HMODULE, &res_rc, -1, le_res_resource_name, le_res_resource);

	if( !type || !type[0] ) RETURN_FALSE;
	if( *type=='#' )
		sscanf( type, "#%x", &int_type );
	if( !strncmp( type, "RT_", 3 ) )
		int_type= php_res_list_get_int_type( type );

	if( !array_init( return_value ) ) 	{
		if( int_type==-1 )
			ret= EnumResourceNames( h_module, type, php_res_list_callback, (LONG)return_value );
		else
			ret= EnumResourceNames( h_module, MAKEINTRESOURCE(int_type), php_res_list_callback, (LONG)return_value );
		if( !ret ) 	{
			if(	GetLastError()!=1813 ) // No resource of this type
				{ zend_error(E_WARNING, "res_list_type %s", win32_strerror(buffer, WIN32_STRERROR_BUFFER_LEN)); RETURN_FALSE; }
			else
				ret= TRUE;
		}
	}

	if( !ret )
		RETURN_FALSE;
}
/* }}} */


BOOL CALLBACK php_res_list_type_callback(
  HMODULE hModule,  // resource-module handle
  LPTSTR lpszType,  // pointer to resource type
  LONG lParam       // application-defined parameter
)
{
	zval * array;
	char buffer[8];

	array= (zval*) lParam;

	if( !IS_INTRESOURCE(lpszType) )
		add_next_index_string(array, lpszType, 1);
	else {
		sprintf( buffer, "#%d", lpszType );
		add_next_index_string(array, buffer, 1);
	}

	return TRUE;
}


BOOL CALLBACK php_res_list_type_string_callback(
  HMODULE hModule,  // resource-module handle
  LPTSTR lpszType,  // pointer to resource type
  LONG lParam       // application-defined parameter
)
{
	zval * array;
	char buffer[8];

	array= (zval*) lParam;

    if( !IS_INTRESOURCE(lpszType) ) {
		add_next_index_string(array, lpszType, 1);
        return TRUE;
    }
#define RES_LIST_TYPE_STRING(type) case type: add_next_index_string(array, #type, 1); break;
	switch( (DWORD)lpszType ) {
        RES_LIST_TYPE_STRING(RT_CURSOR)
        RES_LIST_TYPE_STRING(RT_BITMAP)
        RES_LIST_TYPE_STRING(RT_ICON)
        RES_LIST_TYPE_STRING(RT_MENU)
        RES_LIST_TYPE_STRING(RT_DIALOG)
        RES_LIST_TYPE_STRING(RT_STRING)
        RES_LIST_TYPE_STRING(RT_FONTDIR)
        RES_LIST_TYPE_STRING(RT_FONT)
        RES_LIST_TYPE_STRING(RT_ACCELERATOR)
        RES_LIST_TYPE_STRING(RT_RCDATA)
        RES_LIST_TYPE_STRING(RT_MESSAGETABLE)
        RES_LIST_TYPE_STRING(RT_GROUP_CURSOR)
        RES_LIST_TYPE_STRING(RT_GROUP_ICON)
        RES_LIST_TYPE_STRING(RT_VERSION)
        RES_LIST_TYPE_STRING(RT_DLGINCLUDE)
        RES_LIST_TYPE_STRING(RT_PLUGPLAY)
        RES_LIST_TYPE_STRING(RT_VXD)
        RES_LIST_TYPE_STRING(RT_ANICURSOR)
        RES_LIST_TYPE_STRING(RT_ANIICON)
        RES_LIST_TYPE_STRING(RT_HTML)
	default:
		sprintf( buffer, "#%d", lpszType );
		add_next_index_string(array, buffer, 1);
		break;
	}
#undef RES_LIST_TYPE_STRING
	return TRUE;
}


/* {{{ proto array res_list_type( resource module [, bool as_string=true] )
	return the resource type list for a given module
	as_string specify if known type should be translated to string (but such string can't be used in res_get)
*/
PHP_FUNCTION(res_list_type)
{
	char *module= NULL;
	HMODULE h_module= NULL;
	BOOL ret= FALSE;
	zend_bool as_string= 1;
    char buffer[WIN32_STRERROR_BUFFER_LEN];
    zval *res_rc;

	if( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "r|b", &res_rc, &as_string ) == FAILURE ) 
		RETURN_FALSE;
    ZEND_FETCH_RESOURCE(h_module, HMODULE, &res_rc, -1, le_res_resource_name, le_res_resource);

	if( !array_init( return_value ) ) {
		if( !as_string )
			ret= EnumResourceTypes( h_module, php_res_list_type_callback, (LONG)return_value );
		else
			ret= EnumResourceTypes( h_module, php_res_list_type_string_callback, (LONG)return_value );

		if( !ret )
			{ zend_error(E_WARNING, "res_list_type %d - %s", GetLastError(), win32_strerror(buffer, WIN32_STRERROR_BUFFER_LEN)); RETURN_FALSE; }
	}

	if( !ret )
		RETURN_FALSE;
}
/* }}} */
