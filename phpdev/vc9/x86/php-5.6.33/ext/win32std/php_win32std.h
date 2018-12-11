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
  | Author: Frank M. Kromann <frank@kromann.info>                        |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_WIN32STD_H
#define PHP_WIN32STD_H


#include "php.h"
#include "php_ini.h"
#include "zend_list.h"
#include "ext/standard/info.h"


extern zend_module_entry win32std_module_entry;
#define phpext_win32std_ptr &win32std_module_entry

#ifdef PHP_WIN32
#define PHP_WIN32STD_API __declspec(dllexport)
#else
#define PHP_WIN32STD_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define MAX_SUBKEY_LEN 512

extern int le_res_resource;
#define le_res_resource_name  "RES resource"

extern int le_key;
#define le_key_resource_name  "Registry hKey"


typedef struct _registry_hkey {
	HKEY hKey;
} registry_hkey;

void php_hkey_close(zend_rsrc_list_entry *rsrc TSRMLS_DC);

#define WIN32_STRERROR_BUFFER_LEN 256
const char * win32_strerror( char * buffer, long buffer_len);


 /* Res functions */
ZEND_MINIT_FUNCTION(win32std);
ZEND_MSHUTDOWN_FUNCTION(win32std);
ZEND_RINIT_FUNCTION(win32std);
ZEND_RSHUTDOWN_FUNCTION(win32std);
ZEND_MINFO_FUNCTION(win32std);


 /* Res functions */
PHP_FUNCTION(res_get);
PHP_FUNCTION(res_list);
PHP_FUNCTION(res_list_type);
PHP_FUNCTION(res_open);
PHP_FUNCTION(res_close);
PHP_FUNCTION(res_set);


 /* Res stream */
php_stream *php_res_stream_open(php_stream_wrapper *wrapper, char *path, char *mode, int options, char **opened_path, php_stream_context *context STREAMS_DC TSRMLS_DC);
extern php_stream_ops php_res_stream_ops;
extern php_stream_wrapper php_res_stream_wrapper;
void _php_res_destruction_handler(zend_rsrc_list_entry *rsrc TSRMLS_DC);


 /* Win32 wrapper functions   */
PHP_FUNCTION(win_shell_exec);
PHP_FUNCTION(win_play_wav);
PHP_FUNCTION(win_beep);
PHP_FUNCTION(win_create_link);
PHP_FUNCTION(win_message_box);
PHP_FUNCTION(win_browse_folder);
PHP_FUNCTION(win_browse_file);


 /* Registry functions */
PHP_FUNCTION(reg_create_key);
PHP_FUNCTION(reg_open_key);
PHP_FUNCTION(reg_close_key);
PHP_FUNCTION(reg_enum_key);
PHP_FUNCTION(reg_enum_value);
PHP_FUNCTION(reg_get_value);
PHP_FUNCTION(reg_set_value);


 /* Win32 STD API functions that call C++ Object */
int php_browse_for_folder( HWND wnd, const char * display, char path_buf[MAX_PATH] );
int php_create_link(LPCSTR lpszPathObj, LPSTR lpszPathLink, LPSTR lpszArgs, LPSTR lpszDesc, LPSTR lpszWorkingDir);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(win32std)
	int   global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(win32std)
*/

/* In every utility function you add that needs to use variables 
   in php_win32std_globals, call TSRM_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMG_CC
   after the last function argument and declare your utility function
   with TSRMG_DC after the last declared argument.  Always refer to
   the globals in your function as WIN32STD_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define WIN32STD_G(v) TSRMG(win32std_globals_id, zend_win32std_globals *, v)
#else
#define WIN32STD_G(v) (win32std_globals.v)
#endif



#endif	/* PHP_WIN32STD_H */
