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

typedef struct _res_stream_data{
	HMODULE		module;
	char		*data;
    size_t		size;
    size_t		pos;
} res_stream_data;



static size_t php_res_read(php_stream *stream, char *buf, size_t count TSRMLS_DC)
{
	res_stream_data *self = (res_stream_data *)stream->abstract;
    int read;

    read= count<self->size-self->pos?count:self->size-self->pos;
    memcpy(buf, self->data+self->pos, read);
    self->pos+= read;

    if( self->pos==self->size )
		stream->eof= 1;
	
	return read;
}

static int php_res_seek(php_stream *stream, off_t offset, int whence, off_t *newoffs TSRMLS_DC)
{
	res_stream_data *self = (res_stream_data *)stream->abstract;
    
    *newoffs= self->pos;
	assert(self!=NULL);
    
    switch( whence ) {
        case SEEK_SET:
            *newoffs= offset;
            break;
        case SEEK_CUR:
            *newoffs+= offset;
            break;
        case SEEK_END:
            *newoffs= self->size+offset;
            break;
        default:
            return -1;
    }
    if( *newoffs<0 || *newoffs>(off_t)self->size ) {
        *newoffs= self->pos;
        return -1;
    }
    self->pos= *newoffs;
    return 0;
}

static int php_res_close(php_stream *stream, int close_handle TSRMLS_DC)
{
	res_stream_data *self = (res_stream_data *)stream->abstract;
    if( self->module ) FreeLibrary(self->module);
    efree(self);
	return 1;
}

/* Stream operation entry */
php_stream_ops php_res_stream_ops = {
	NULL,php_res_read,  /* write, read */
	php_res_close,NULL, /* close, flush */
	"RES",
	php_res_seek, /* seek */
	NULL, /* cast */
	NULL, /* stat */
	NULL  /* set_option */
};


php_stream *php_res_stream_open(php_stream_wrapper *wrapper, char *path, char *mode,
		int options, char **opened_path, php_stream_context *context STREAMS_DC TSRMLS_DC);

/* Wrapper operation entry */
static php_stream_wrapper_ops php_res_wrapper_ops = {
	php_res_stream_open,
	NULL, /* close */
	NULL, /* stat */
	NULL, /* stat_url */
	NULL, /* opendir */
	"RES"
};


/* Wrapper entry */
php_stream_wrapper php_res_stream_wrapper =	{
	&php_res_wrapper_ops,
	NULL,
	0, /* is_url */
};



/* Can handle
    "res://c:\adir\another\file.dll/#145/#12"
    "res://c:\adir\another\file.dll/#145/#12/"
    "res://c:/adir/another/file.dll/#145/#12"
    "res://c:\adir\another\file.dll/TYPE/NAME"
*/

php_stream *php_res_stream_open(php_stream_wrapper *wrapper, char *path, char *mode,
		int options, char **opened_path, php_stream_context *context STREAMS_DC TSRMLS_DC)
{
	res_stream_data *self;
	php_stream *stream = NULL;
    char *ptr, *type, *name, buffer[WIN32_STRERROR_BUFFER_LEN], *path_copy;
    int path_len;
	HRSRC hr;

	/* check: read only */
	if( strchr(mode, '+') || strchr(mode, 'a') || strchr(mode, 'w')) {
		//if (options & REPORT_ERRORS) {
			zend_error(E_WARNING, "cannot open a res stream for writing");
		//}
		return NULL;
	}

	self = emalloc(sizeof(res_stream_data));
    memset(self, 0, sizeof(res_stream_data));

    if( strncasecmp("res://", path, 6)==0 )
	    path+= 6;

	path_copy= estrdup(path);
    ptr= path_copy;

    // can't end with /
    path_len= strlen(path_copy);
    if( path_copy[path_len-1]=='/' ) path_copy[path_len]= 0;

    // search name
    ptr= path_copy;
    ptr= strrchr(ptr, '/');
    if( !ptr ) {
        zend_error(E_WARNING, "bad res string" );
        efree(self);
        efree(path_copy);
        return NULL;
    }
    name= ptr+1;
    *ptr= 0;

    // search type
    ptr= path_copy;
    ptr= strrchr(ptr, '/');
    if( !ptr ) {
        zend_error(E_WARNING, "bad res string" );
        efree(self);
        efree(path_copy);
        return NULL;
    }
    type= ptr+1;
    *ptr= 0;

    if( *path_copy ) {
        self->module= LoadLibrary(path_copy);
	    if( !self->module ) { 
		    zend_error(E_WARNING, "open '%s' failed: %s", path_copy, win32_strerror(buffer, WIN32_STRERROR_BUFFER_LEN)); 
            efree(self);
            efree(path_copy);
		    return NULL;
	    }
    }
    else
        self->module= NULL; // Current exe

    // Convert name and type to uppercase since lowercase don't work
    strupr(name);
    strupr(type);

	hr= FindResource( self->module, name, type );
	if( hr==NULL ) {
        zend_error(E_WARNING, "find '%s/%s' failed: %s", type, name, win32_strerror(buffer, WIN32_STRERROR_BUFFER_LEN)); 
        if( self->module ) FreeLibrary(self->module);
        efree(self);
        efree(path_copy);
		return NULL;
	}

	self->data= LoadResource( self->module, hr );
	if( self->data==NULL ) {
        zend_error(E_WARNING, "load '%s/%s' failed: %s", type, name, win32_strerror(buffer, WIN32_STRERROR_BUFFER_LEN));
        if( self->module ) FreeLibrary(self->module);
        efree(self);
        efree(path_copy);
		return NULL;
	}

	self->size= SizeofResource( self->module, hr );
    efree(path_copy);

    // Allocate stream and return it
    stream = php_stream_alloc_rel(&php_res_stream_ops, self, 0, mode);
    if (stream) {
	    stream->flags |= PHP_STREAM_FLAG_NO_BUFFER;
	    //stream->flags |= PHP_STREAM_FLAG_NO_SEEK;
	    return stream;
    }
	
    efree( self );

	return NULL;
}


