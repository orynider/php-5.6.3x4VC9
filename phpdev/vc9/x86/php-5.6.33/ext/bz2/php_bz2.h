/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Sterling Hughes <sterling@php.net>                           |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

/* BZ2's version number. */
#define SDL_VERSION 5
#define SDL_MAJOR_VERSION 1
#define SDL_MINOR_VERSION 0
#define SDL_PATCH_LEVEL 6
#define SDL_RELEASE_LEVEL 6
#define SDL_RELEASE_SERIAL 0

#define VERSION                     "1.06.000"
#define VER_PRODUCTVERSION_STR      "5.6.33\0"
#define VER_PRODUCTVERSION          5,6,33,000
#define VER_PRODUCTVERSION_DW       (0x05633000 | 100)

#define VER_ORIGINALFILENAME_STR	"php_bz2.dll\0"
#define VERSION_VALUE "1.06\0"  // should be X.Y : ie. if VERSION_DIGITALVALUE == 4, 7, 1, 0 , then X = 4, Y = 71 
#define VERSION_DIGITALVALUE 1, 0, 6, 0

#ifndef VER_INTERNALNAME_STR
#define VER_INTERNALNAME_STR	"php_bz2.dll\0"
#endif

#ifndef PHP_BZ2_H
#define PHP_BZ2_H

#if HAVE_BZ2

extern zend_module_entry bz2_module_entry;
#define phpext_bz2_ptr &bz2_module_entry

/* Bzip2 includes */
#include <bzlib.h>

#else
#define phpext_bz2_ptr NULL
#endif

#ifdef PHP_WIN32
#	ifdef PHP_BZ2_EXPORTS
#		define PHP_BZ2_API __declspec(dllexport)
#	elif defined(COMPILE_DL_BZ2)
#		define PHP_BZ2_API __declspec(dllimport)
#	else
#		define PHP_BZ2_API /* nothing special */
#	endif
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_BZ2_API __attribute__ ((visibility("default")))
#else
#	define PHP_BZ2_API
#endif

PHP_BZ2_API php_stream *_php_stream_bz2open(php_stream_wrapper *wrapper, const char *path, const char *mode, int options, char **opened_path, php_stream_context *context STREAMS_DC TSRMLS_DC);
PHP_BZ2_API php_stream *_php_stream_bz2open_from_BZFILE(BZFILE *bz, const char *mode, php_stream *innerstream STREAMS_DC TSRMLS_DC);

#define php_stream_bz2open_from_BZFILE(bz, mode, innerstream)	_php_stream_bz2open_from_BZFILE((bz), (mode), (innerstream) STREAMS_CC TSRMLS_CC)
#define php_stream_bz2open(wrapper, path, mode, options, opened_path)	_php_stream_bz2open((wrapper), (path), (mode), (options), (opened_path), NULL STREAMS_CC TSRMLS_CC)

extern php_stream_filter_factory php_bz2_filter_factory;
extern php_stream_ops php_stream_bz2io_ops;
#define PHP_STREAM_IS_BZIP2	&php_stream_bz2io_ops

/* 400kb */
#define PHP_BZ2_FILTER_DEFAULT_BLOCKSIZE        4

/* BZ2 Internal Default */
#define PHP_BZ2_FILTER_DEFAULT_WORKFACTOR       0

#endif


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
