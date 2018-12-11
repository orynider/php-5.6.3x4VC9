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


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
//#include <Windows.h> //(#include Mmsystem.h)
#include "php_win32std.h"
#include "ext/standard/php_smart_str.h"



/* Return the Win32 error string for the last called Win32 function */
const char * win32_strerror( char * buffer, long buffer_len)
{
	if( !buffer || !buffer_len ) return NULL;
    *buffer= 0;

    FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, NULL, 
		GetLastError(), 0, buffer, buffer_len, NULL);

	return buffer;
}




/**************************************************************************************/
/**************************************************************************************/
/****************************** Win32 Functions ***************************************/
/**************************************************************************************/
/**************************************************************************************/

/* {{{ proto bool win_shell_execute(string absolute_path[, string action, string args, string dir])
    Execute a shell action on a file or directory
    Common actions: open, edit, explore, find, print, properties
    The shell act the same way when you double click on an icon (action=NULL) or when you choose a menu item on the right click button
    This way you can also execute programs that are totaly detached from the current one (useful with DirectX games for exemple).
*/
PHP_FUNCTION(win_shell_execute)
{
	char *action= NULL, *file= NULL, *args=NULL, *dir=NULL;
	int  action_len= 4, file_len=0, args_len=0, dir_len=0, ret;

	if( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s|sss", &file, &file_len, &action, &action_len, &args, &args_len, &dir, &dir_len ) == FAILURE ) 
		RETURN_FALSE;

    ret= (int)ShellExecute( NULL, action, file, args, dir, SW_SHOW );
	if( ret<=32 )
	{
		switch( ret )
		{
			case 0:
				zend_error(E_WARNING,"shell_execute failed - No more system memory");
				break;
#define SHELL_EXEC_ERROR(err) case err: zend_error( E_WARNING, "Unable to execute shell [%s] on '%s' (%s)", action, file, #err ); break;
			SHELL_EXEC_ERROR(ERROR_FILE_NOT_FOUND );
			SHELL_EXEC_ERROR(ERROR_PATH_NOT_FOUND);
			SHELL_EXEC_ERROR(ERROR_BAD_FORMAT );
			SHELL_EXEC_ERROR(SE_ERR_ACCESSDENIED );
			SHELL_EXEC_ERROR(SE_ERR_ASSOCINCOMPLETE);
			SHELL_EXEC_ERROR(SE_ERR_DDEBUSY);
			SHELL_EXEC_ERROR(SE_ERR_DDEFAIL );
			SHELL_EXEC_ERROR(SE_ERR_DDETIMEOUT );
			SHELL_EXEC_ERROR(SE_ERR_DLLNOTFOUND );
			SHELL_EXEC_ERROR(SE_ERR_NOASSOC );
			SHELL_EXEC_ERROR(SE_ERR_OOM );
			SHELL_EXEC_ERROR(SE_ERR_SHARE);
#undef SHELL_EXEC_ERROR
		}
		RETURN_FALSE
	}
    RETURN_TRUE
}
/* }}} */


/* {{{ proto: play_wav( file[, loop])
	file may be either NULL to stop playback or a file name to start it
	loop can be set to loop playback (default to false)
	module may be opened by res_open a file must represent the resource id (NOT IMPL)
*/
PHP_FUNCTION(win_play_wav)
{
	char *file= NULL;
	int  file_len=0;
	int ret;
	int default_flags;
	zend_bool loop= 0;

	if( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &file, &file_len, &loop ) == FAILURE ) 
		RETURN_FALSE;

	if( !*file ) file= NULL;

	default_flags= SND_ASYNC | SND_NOSTOP | SND_NOWAIT;

	if( file==NULL )
		default_flags= SND_PURGE;
	else if( loop )
		default_flags|= SND_LOOP;

	ret= PlaySound( file, NULL, default_flags | SND_FILENAME ); 
	if( ret ) 
		RETURN_TRUE;
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto bool win_beep(string type)
    plays the system sound used by default for pre-defined events:
        '*': System Asterisk 
        '!': System Exclamation 
        'H': System Hand 
        '?': System Question 
        '1': System Default 
        '0': Standard beep using the computer speaker
*/
PHP_FUNCTION(win_beep)
{
	UINT beep_type;
	char * str= "";
	int str_len= 0;

	if( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|s", &str, &str_len ) == FAILURE ) 
		RETURN_FALSE;

	switch(*str)
	{
	case '*': // System Asterisk 
		beep_type= MB_ICONASTERISK;
		break;
	case '!': // System Exclamation 
		beep_type= MB_ICONEXCLAMATION;
		break;
	case 'H': // System Hand 
		beep_type= MB_ICONHAND;
		break;
	case '?': // System Question 
		beep_type= MB_ICONQUESTION;
		break;
	case '1': // System Default 
		beep_type= MB_OK;
		break;
	default:
	case '0': // Standard beep using the computer speaker
		beep_type= 0xFFFFFFFF;
		zend_printf("Default\n");
		break;
	}
	if( !MessageBeep( beep_type ) )
		RETURN_FALSE;
	RETURN_TRUE;
}
/* }}} */


/* {{{ proto int win_create_link( file, link_file, args, descr, workingdir )
   Create a MS link file (.lnk) 
   Don't forget the .lnk at the end of link_file !
*/
PHP_FUNCTION(win_create_link)
{
    char *file, *link, *args=NULL, *descr=NULL, *workingdir=NULL;
    int file_len, link_len, args_len, descr_len, workingdir_len;

    if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|sss", &file, &file_len, &link, &link_len, &args, &args_len, &descr, &descr_len, &workingdir, &workingdir_len) == FAILURE ) {
		return;
	}
    if( !php_create_link(file, link, args, descr, workingdir) ) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}
/* }}} */


/* {{{ proto int win_message_box( text[, type, caption] )
   Prompt a typical Win32 message box.
   Use the Messages Box Constants to modify the appearance of the message box
*/
PHP_FUNCTION(win_message_box)
{
    char *text, *caption= "PHP";
    int text_len, caption_len, type=MB_OK;
	
    if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ls", &text, &text_len, &type, &caption, &caption_len) == FAILURE ) {
		RETURN_FALSE;
	}

    RETURN_LONG(MessageBox(NULL, text, caption, type|MB_TASKMODAL));
}
/* }}} */



/* {{{ proto int win_browse_folder( [string dir, string caption=""] )
   Prompt a "browse for folder" message box
*/
PHP_FUNCTION(win_browse_folder)
{
    char *dir=NULL, *caption=NULL, system_dir[MAX_PATH+1]= "";
    int dir_len, caption_len;

    if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|ss", &dir, &dir_len, &caption, &caption_len) == FAILURE ) {
		return;
	}

	if( dir ) {
		strncpy( system_dir, dir, MAX_PATH );
		system_dir[MAX_PATH]= 0;
	}

    if( !php_browse_for_folder(NULL, caption, system_dir) ) {
        RETURN_NULL()
    }

    RETVAL_STRING( system_dir, 1 );
}
/* }}} */


/* {{{ proto string win_browse_file( [open, path, filename, ext, filter] )
    open or save dialog box, starting path, default filename, default extension, filter in M$ format 
    Filter exemple: "HTML File\0*.htm;*.html\0INI file\0*.ini\0All files\0*.*\0\0"
	or: array( "HTML File" => "*.htm;*.html", "INI File" => "*.ini", "All file" => "*.*" )
*/
PHP_FUNCTION(win_browse_file)
{
    char *ext= NULL, *path= NULL, *file= NULL, *key;
    int open=1, ext_len, path_len, file_len, free_filter= 0, key_len, not_string;
	zval *zfilter= NULL, **entry;
    char fileBuffer[MAX_PATH]= "";
    OPENFILENAME ofn;
    BOOL res;
 	HashPosition pos;
	smart_str smart_filter= {0};
  
    if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|lsssz", &open,
        &path, &path_len, &file, &file_len, &ext, &ext_len, &zfilter) == FAILURE )
		RETURN_NULL();

    if( file ) strcpy(fileBuffer, file );

    memset(&ofn, 0, sizeof(OPENFILENAME));
    ofn.lStructSize= sizeof(OPENFILENAME);
    ofn.hwndOwner= NULL;
    ofn.lpstrFilter= NULL;
    ofn.lpstrFile= fileBuffer;
    ofn.nMaxFile= MAX_PATH;
    //ofn.lpstrFileTitle
    //ofn.nMaxFileTitle
    ofn.lpstrInitialDir= path;
    //ofn.lpstrTitle= "Choose file";
    ofn.lpstrDefExt= ext;
    ofn.Flags= OFN_CREATEPROMPT|OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY;
    //OFN_FILEMUSTEXIST

	/* Filter */
	free_filter= 0;
	if( zfilter && Z_TYPE_P(zfilter)==IS_ARRAY ) {
		not_string= 0;
		zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(zfilter), &pos);
		while (zend_hash_get_current_data_ex(Z_ARRVAL_P(zfilter), (void **)&entry, &pos) == SUCCESS) {
			if( zend_hash_get_current_key_ex(Z_ARRVAL_P(zfilter), &key, &key_len, &key_len, 0, &pos)!=HASH_KEY_IS_STRING ) { not_string= 1; break; }
			if( Z_TYPE_PP(entry)!=IS_STRING ) { /*not_string= 1;*/ 
				zend_error( E_WARNING, "win_browse_file: filter key '%s' must have a string value", key ); 
				zend_hash_move_forward_ex(Z_ARRVAL_P(zfilter), &pos);
				continue; 
			}

			smart_str_appends( &smart_filter, key );
			smart_str_appendc( &smart_filter, '\0' );
			smart_str_appends( &smart_filter, Z_STRVAL_PP(entry) );
			smart_str_appendc( &smart_filter, '\0' );

			zend_hash_move_forward_ex(Z_ARRVAL_P(zfilter), &pos);
		}
		if(not_string ) {
			zend_error( E_WARNING, "win_browse_file: filter must be an associative array" );
			smart_str_free(&smart_filter);
		}
		smart_str_appendc( &smart_filter, '\0' );
		ofn.lpstrFilter= smart_filter.c;
		free_filter= 1;
	} 
	else if( zfilter && Z_TYPE_P(zfilter)==IS_STRING ) {
		ofn.lpstrFilter= Z_STRVAL_P(zfilter);
	}
	else if( zfilter ) {
		zend_error( E_WARNING, "win_browse_file: the filter parameter must be an array" );
	}


    if( open )
        res= GetOpenFileName(&ofn);
    else
        res= GetSaveFileName(&ofn);
	if( free_filter )
		smart_str_free(&smart_filter);
    if( !res )
        RETURN_NULL()
    else 
        RETVAL_STRING(fileBuffer,1)
}
/* }}} */




/*******************************************************************/
/*******************************************************************/
/************************** PHP EXT STUFF **************************/
/*******************************************************************/
/*******************************************************************/


/* If you declare any globals in php_win32std.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(win32std)
*/



/* True global resources - no need for thread safety here */
//static int le_win32std;



/* {{{ win32std_functions[]
 *
 * Every user visible function must have an entry in win32std_functions[].
 */
function_entry win32std_functions[] = {

	/* Res */
	PHP_FE(res_get,			NULL)
	PHP_FE(res_list,		    NULL)
	PHP_FE(res_list_type,	NULL)
	PHP_FE(res_open,		NULL)
	PHP_FE(res_close,		NULL)
	PHP_FE(res_set,			NULL)

	/* Win32 */
	PHP_FE(win_shell_execute,	NULL)
	PHP_FE(win_play_wav,		NULL)
	PHP_FE(win_beep,			    NULL)
	PHP_FE(win_message_box,	NULL)
	PHP_FE(win_create_link,		NULL)
	PHP_FE(win_browse_folder,	NULL)
	PHP_FE(win_browse_file,		NULL)

	/* Registry */
	PHP_FE(reg_close_key,		NULL)
	PHP_FE(reg_create_key,		NULL)
	PHP_FE(reg_enum_key,	    NULL)
	PHP_FE(reg_enum_value,	    NULL)
	PHP_FE(reg_open_key,		NULL)
	PHP_FE(reg_set_value,		NULL)
	PHP_FE(reg_get_value,	NULL)

    {NULL, NULL, NULL}	/* Must be the last line in win32std_functions[] */
};
/* }}} */

#if ZEND_MODULE_API_NO < 20010901
# error Module made for PHP 4.1.x
#endif

/* {{{ win32std_module_entry
 */
zend_module_entry win32std_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"win32std",
	win32std_functions,
	ZEND_MINIT(win32std),
	ZEND_MSHUTDOWN(win32std),
	ZEND_RINIT(win32std),		/* Replace with NULL if there's nothing to do at request start */
	ZEND_RSHUTDOWN(win32std),	/* Replace with NULL if there's nothing to do at request end */
#if ZEND_MODULE_API_NO >= 20010901
	ZEND_MINFO(win32std),
#endif
    "0.1", /* Replace with version number for your extension */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_WIN32STD
ZEND_GET_MODULE(win32std)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("win32std.value",      "42", PHP_INI_ALL, OnUpdateInt, global_value, zend_win32std_globals, win32std_globals)
    STD_PHP_INI_ENTRY("win32std.string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_win32std_globals, win32std_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_win32std_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_win32std_init_globals(zend_win32std_globals *win32std_globals)
{
	win32std_globals->value = 0;
	win32std_globals->string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */	
ZEND_MINIT_FUNCTION(win32std)
{
	/* If you have INI entries, uncomment these lines 
	ZEND_INIT_MODULE_GLOBALS(win32std, php_win32std_init_globals, NULL);
	REGISTER_INI_ENTRIES();
	*/

    /**
    * Resources
    **/
	le_res_resource = zend_register_list_destructors_ex(_php_res_destruction_handler, NULL, le_res_resource_name, module_number);
	php_register_url_stream_wrapper("res", &php_res_stream_wrapper TSRMLS_CC);

    /* Resource type constants */
	REGISTER_STRING_CONSTANT("RT_CURSOR", ("#1"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_BITMAP", ("#2"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_ICON", ("#3"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_MENU", ("#4"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_DIALOG", ("#5"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_STRING", ("#6"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_FONTDIR", ("#7"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_FONT", ("#8"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_ACCELERATOR", ("#9"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_RCDATA", ("#10"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_MESSAGETABLE", ("#11"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_GROUP_CURSOR", ("#12"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_GROUP_ICON", ("#14"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_VERSION", ("#16"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_DLGINCLUDE", ("#17"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_PLUGPLAY", ("#19"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_VXD", ("#20"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_ANICURSOR", ("#21"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_ANIICON", ("#22"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_HTML", ("#23"), CONST_CS|CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("RT_NOT_DOCUMENTED", ("#241"), CONST_CS|CONST_PERSISTENT);

    /**
    * Messages box
    **/
    /* Message box type constants */
	REGISTER_LONG_CONSTANT("MB_OK", MB_OK, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_OKCANCEL", MB_OKCANCEL, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_RETRYCANCEL", MB_RETRYCANCEL, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_YESNO", MB_YESNO, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_YESNOCANCEL", MB_YESNOCANCEL, CONST_CS|CONST_PERSISTENT);

    /* Message box icon constants */
	REGISTER_LONG_CONSTANT("MB_ICONEXCLAMATION", MB_ICONEXCLAMATION, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_ICONWARNING", MB_ICONWARNING, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_ICONINFORMATION", MB_ICONINFORMATION, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_ICONASTERISK", MB_ICONASTERISK, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_ICONQUESTION", MB_ICONQUESTION, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_ICONSTOP", MB_ICONSTOP, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_ICONERROR", MB_ICONERROR, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_ICONHAND", MB_ICONHAND, CONST_CS|CONST_PERSISTENT);

    /* Message box default button constants */
	REGISTER_LONG_CONSTANT("MB_DEFBUTTON1", MB_DEFBUTTON1, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_DEFBUTTON2", MB_DEFBUTTON2, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_DEFBUTTON3", MB_DEFBUTTON3, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_DEFBUTTON4", MB_DEFBUTTON4, CONST_CS|CONST_PERSISTENT);

    /* Message box return constants */
	REGISTER_LONG_CONSTANT("MB_IDABORT", IDABORT, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_IDCANCEL", IDCANCEL, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_IDNO", IDNO, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_IDOK", IDOK, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_IDYES", IDYES, CONST_CS|CONST_PERSISTENT);
//    REGISTER_LONG_CONSTANT("MB_IDCONTINUE", IDCONTINUE, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_IDIGNORE", IDIGNORE, CONST_CS|CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("MB_IDRETRY", IDRETRY, CONST_CS|CONST_PERSISTENT);
//	REGISTER_LONG_CONSTANT("MB_IDTRYAGAIN", IDTRYAGAIN, CONST_CS|CONST_PERSISTENT);

    /**
    * Registry
    **/
	le_key = zend_register_list_destructors_ex(php_hkey_close, NULL, le_key_resource_name, module_number);

    /* Registry main key constants */
	REGISTER_LONG_CONSTANT("HKEY_CLASSES_ROOT", 0, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("HKEY_CURRENT_CONFIG", 1, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("HKEY_CURRENT_USER", 2, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("HKEY_LOCAL_MACHINE", 3, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("HKEY_USERS", 4, CONST_CS | CONST_PERSISTENT);

    /* Registry access type */
	REGISTER_LONG_CONSTANT("KEY_ALL_ACCESS", KEY_ALL_ACCESS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KEY_WRITE",  KEY_WRITE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("KEY_READ", KEY_READ, CONST_CS | CONST_PERSISTENT);

    /* Registry value type */
	REGISTER_LONG_CONSTANT("REG_BINARY", REG_BINARY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("REG_DWORD", REG_DWORD, CONST_CS | CONST_PERSISTENT);
//	REGISTER_LONG_CONSTANT("REG_DWORD_LITTLE_ENDIAN", REG_DWORD_LITTLE_ENDIAN, CONST_CS | CONST_PERSISTENT);
//	REGISTER_LONG_CONSTANT("REG_DWORD_BIG_ENDIAN", REG_DWORD_BIG_ENDIAN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("REG_EXPAND_SZ", REG_EXPAND_SZ, CONST_CS | CONST_PERSISTENT);
//	REGISTER_LONG_CONSTANT("REG_LINK", REG_LINK, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("REG_MULTI_SZ", REG_MULTI_SZ, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("REG_NONE", REG_NONE, CONST_CS | CONST_PERSISTENT);
//	REGISTER_LONG_CONSTANT("REG_RESOURCE_LIST", REG_RESOURCE_LIST, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("REG_SZ", REG_SZ, CONST_CS | CONST_PERSISTENT);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
ZEND_MSHUTDOWN_FUNCTION(win32std)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
ZEND_RINIT_FUNCTION(win32std)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
ZEND_RSHUTDOWN_FUNCTION(win32std)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
ZEND_MINFO_FUNCTION(win32std)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "win32std", "enabled");
	php_info_print_table_row(2, "resource support", "enabled");
	php_info_print_table_row(2, "message box support", "enabled");
	php_info_print_table_row(2, "registry support", "enabled");
	php_info_print_table_end();
    
	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_win32std_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_win32std_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char string[256];

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = sprintf(string, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "win32std", arg);
	RETURN_STRINGL(string, len, 1);
}
/* }}} */



/*
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}*/

//_DEBUG,__WIN32__,ZEND_DEBUG=1,_WINDOWS,_USRDLL,ZTS,ZEND_WIN32,PHP_WIN32,WIN32,_MBCS,USE_WSAPI
//_DEBUG,__WIN32__,USE_TLS,WIN32,_MBCS,ZEND_DEBUG=1,NDEBUG,_WINDOWS,_USRDLL,SBEE_EXPORTS,COMPILE_DL_SBEE,ZTS=1,ZEND_WIN32,PHP_WIN32,HAVE_SBEE=1

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 tw=78 fdm=marker
 * vim<600: sw=4 ts=4 tw=78
 */
