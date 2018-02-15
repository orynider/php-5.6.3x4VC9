/* io.c - ber general i/o routines */
/* $OpenLDAP: pkg/ldap/libraries/liblber/io.c,v 1.38.4.7 2001/05/10 04:43:46 kurt Exp $ */
/*
 * Copyright 1998-2000 The OpenLDAP Foundation, All Rights Reserved.
 * COPYING RESTRICTIONS APPLY, see COPYRIGHT file
 */
/* Portions
 * Copyright (c) 1990 Regents of the University of Michigan.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and that due credit is given
 * to the University of Michigan at Ann Arbor. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 */

#include "portable.h"

//#include <stdio.h>

#include <ac/stdlib.h>

#include <ac/ctype.h>
#include <ac/errno.h>
#include <ac/socket.h>
#include <ac/string.h>
#include <ac/unistd.h>

#ifdef HAVE_IO_H
#include <io.h>
#endif

#include "lber-int.h"

#define EXBUFSIZ	1024

static ber_slen_t
BerRead(
	Sockbuf *sb,
	unsigned char *buf,
	ber_len_t len )
{
	ber_slen_t	c;
	ber_slen_t	nread = 0;

	assert( sb != NULL );
	assert( buf != NULL );

	assert( SOCKBUF_VALID( sb ) );

	while ( len > 0 ) {
		if ( (c = ber_int_sb_read( sb, buf, len )) <= 0 ) {
			if ( nread > 0 )
				break;
			return( c );
		}
		buf+=c;
		nread+=c;
		len-=c;
	}

	return( nread );
}

ber_slen_t
ber_read(
	BerElement *ber,
	char *buf,
	ber_len_t len )
{
	ber_len_t	actuallen, nleft;

	assert( ber != NULL );
	assert( buf != NULL );

	assert( BER_VALID( ber ) );

	nleft = ber_pvt_ber_remaining( ber );
	actuallen = nleft < len ? nleft : len;

	AC_MEMCPY( buf, ber->ber_ptr, actuallen );

	ber->ber_ptr += actuallen;

	return( (ber_slen_t) actuallen );
}

ber_slen_t
ber_write(
	BerElement *ber,
	LDAP_CONST char *buf,
	ber_len_t len,
	int nosos )
{
	assert( ber != NULL );
	assert( buf != NULL );

	assert( BER_VALID( ber ) );

	if ( nosos || ber->ber_sos == NULL ) {
		if ( ber->ber_ptr + len > ber->ber_end ) {
			if ( ber_realloc( ber, len ) != 0 )
				return( -1 );
		}
		AC_MEMCPY( ber->ber_ptr, buf, (size_t)len );
		ber->ber_ptr += len;
		return( (ber_slen_t) len );

	} else {
		if ( ber->ber_sos->sos_ptr + len > ber->ber_end ) {
			if ( ber_realloc( ber, len ) != 0 )
				return( -1 );
		}
		AC_MEMCPY( ber->ber_sos->sos_ptr, buf, (size_t)len );
		ber->ber_sos->sos_ptr += len;
		ber->ber_sos->sos_clen += len;
		return( (ber_slen_t) len );
	}
}

int
ber_realloc( BerElement *ber, ber_len_t len )
{
	ber_len_t	need, have, total;
	Seqorset	*s;
	long		off;
	char		*oldbuf;

	assert( ber != NULL );
	assert( len > 0 );

	assert( BER_VALID( ber ) );

	total = ber_pvt_ber_total( ber );
	have = total / EXBUFSIZ;
	need = (len < EXBUFSIZ ? 1 : (len + (EXBUFSIZ - 1)) / EXBUFSIZ);
	total = have * EXBUFSIZ + need * EXBUFSIZ;

	oldbuf = ber->ber_buf;

	ber->ber_buf = (char *) LBER_REALLOC( oldbuf, total );
	
	if ( ber->ber_buf == NULL ) {
		ber->ber_buf = oldbuf;
		return( -1 );
	}

	ber->ber_end = ber->ber_buf + total;

	/*
	 * If the stinking thing was moved, we need to go through and
	 * reset all the sos and ber pointers.  Offsets would've been
	 * a better idea... oh well.
	 */

	if ( ber->ber_buf != oldbuf ) {
		ber->ber_ptr = ber->ber_buf + (ber->ber_ptr - oldbuf);

		for ( s = ber->ber_sos; s != NULL; s = s->sos_next ) {
			off = s->sos_first - oldbuf;
			s->sos_first = ber->ber_buf + off;

			off = s->sos_ptr - oldbuf;
			s->sos_ptr = ber->ber_buf + off;
		}
	}

	return( 0 );
}

void
ber_free( BerElement *ber, int freebuf )
{
#ifdef LDAP_MEMORY_DEBUG
	assert( ber != NULL );
#endif

	if( ber == NULL ) {
		return;
	}

	assert( BER_VALID( ber ) );

	if ( freebuf ) {
		Seqorset *s, *next;
		LBER_FREE( ber->ber_buf );

		for( s = ber->ber_sos ; s != NULL ; s = next ) {
			next = s->sos_next;
			LBER_FREE( s );
		}
	}

	ber->ber_buf = NULL;
	ber->ber_sos = NULL;
	ber->ber_valid = LBER_UNINITIALIZED;

	LBER_FREE( (char *) ber );
}

int
ber_flush( Sockbuf *sb, BerElement *ber, int freeit )
{
	ber_len_t	nwritten, towrite;
	ber_slen_t	rc;	

	assert( sb != NULL );
	assert( ber != NULL );

	assert( SOCKBUF_VALID( sb ) );
	assert( BER_VALID( ber ) );

	if ( ber->ber_rwptr == NULL ) {
		ber->ber_rwptr = ber->ber_buf;
	}
	towrite = ber->ber_ptr - ber->ber_rwptr;

	if ( sb->sb_debug ) {
		ber_log_printf( LDAP_DEBUG_ANY, sb->sb_debug,
			"ber_flush: %ld bytes to sd %ld%s\n",
			towrite, (long) sb->sb_fd,
			ber->ber_rwptr != ber->ber_buf ?  " (re-flush)" : "" );
		ber_log_bprint( LDAP_DEBUG_PACKETS, sb->sb_debug,
			ber->ber_rwptr, towrite );
	}

	nwritten = 0;
	do {
		rc = ber_int_sb_write( sb, ber->ber_rwptr, towrite );
		if (rc<=0) {
			return -1;
		}
		towrite -= rc;
		nwritten += rc;
		ber->ber_rwptr += rc;
	} while ( towrite > 0 );

	if ( freeit )
		ber_free( ber, 1 );

	return( 0 );
}

BerElement *
ber_alloc_t( int options )
{
	BerElement	*ber;

    ber_int_options.lbo_valid = LBER_INITIALIZED;

	ber = (BerElement *) LBER_CALLOC( 1, sizeof(BerElement) );

	if ( ber == NULL ) {
		return NULL;
	}

	ber->ber_valid = LBER_VALID_BERELEMENT;
	ber->ber_tag = LBER_DEFAULT;
	ber->ber_options = options;
	ber->ber_debug = ber_int_debug;

	assert( BER_VALID( ber ) );
	return ber;
}

BerElement *
ber_alloc( void )	/* deprecated */
{
	return ber_alloc_t( 0 );
}

BerElement *
der_alloc( void )	/* deprecated */
{
	return ber_alloc_t( LBER_USE_DER );
}

BerElement *
ber_dup( BerElement *ber )
{
	BerElement	*new;

	assert( ber != NULL );
	assert( BER_VALID( ber ) );

	if ( (new = ber_alloc_t( ber->ber_options )) == NULL ) {
		return NULL;
	}

	*new = *ber;

	assert( BER_VALID( new ) );
	return( new );
}


/* OLD U-Mich ber_init() */
void
ber_init_w_nullc( BerElement *ber, int options )
{
	assert( ber != NULL );

    ber_int_options.lbo_valid = LBER_INITIALIZED;

	(void) memset( (char *)ber, '\0', sizeof( BerElement ));
	ber->ber_valid = LBER_VALID_BERELEMENT;
	ber->ber_tag = LBER_DEFAULT;
	ber->ber_options = (char) options;
	ber->ber_debug = ber_int_debug;

	assert( BER_VALID( ber ) );
}

/* New C-API ber_init() */
/* This function constructs a BerElement containing a copy
** of the data in the bv argument.
*/
BerElement *
ber_init( struct berval *bv )
{
	BerElement *ber;

	assert( bv != NULL );

    ber_int_options.lbo_valid = LBER_INITIALIZED;

	if ( bv == NULL ) {
		return NULL;
	}

	ber = ber_alloc_t( 0 );

	if( ber == NULL ) {
		/* allocation failed */
		return NULL;
	}

	/* copy the data */
	if ( ((ber_len_t) ber_write ( ber, bv->bv_val, bv->bv_len, 0 ))
		!= bv->bv_len )
	{
		/* write failed, so free and return NULL */
		ber_free( ber, 1 );
		return NULL;
	}

	ber_reset( ber, 1 );	/* reset the pointer to the start of the buffer */
	return ber;
}

/* New C-API ber_flatten routine */
/* This routine allocates a struct berval whose contents are a BER
** encoding taken from the ber argument.  The bvPtr pointer pointers to
** the returned berval.
*/
int ber_flatten(
	BerElement *ber,
	struct berval **bvPtr)
{
	struct berval *bv;
 
	assert( bvPtr != NULL );

    ber_int_options.lbo_valid = LBER_INITIALIZED;

	if(bvPtr == NULL) {
		return -1;
	}

	bv = LBER_MALLOC( sizeof(struct berval) );
	if ( bv == NULL ) {
		return -1;
	}

	if ( ber == NULL ) {
		/* ber is null, create an empty berval */
		bv->bv_val = NULL;
		bv->bv_len = 0;

	} else {
		/* copy the berval */
		ber_len_t len = ber_pvt_ber_write( ber );

		bv->bv_val = (char *) LBER_MALLOC( len + 1 );
		if ( bv->bv_val == NULL ) {
			LBER_FREE( bv );
			return -1;
		}

		AC_MEMCPY( bv->bv_val, ber->ber_buf, len );
		bv->bv_val[len] = '\0';
		bv->bv_len = len;
	}
    
	*bvPtr = bv;
	return 0;
}

void
ber_reset( BerElement *ber, int was_writing )
{
	assert( ber != NULL );
	assert( BER_VALID( ber ) );

	if ( was_writing ) {
		ber->ber_end = ber->ber_ptr;
		ber->ber_ptr = ber->ber_buf;

	} else {
		ber->ber_ptr = ber->ber_end;
	}

	ber->ber_rwptr = NULL;
}

/*
 * A rewrite of ber_get_next that can safely be called multiple times 
 * for the same packet. It will simply continue where it stopped until
 * a full packet is read.
 */

ber_tag_t
ber_get_next(
	Sockbuf *sb,
	ber_len_t *len,
	BerElement *ber )
{
	assert( sb != NULL );
	assert( len != NULL );
	assert( ber != NULL );

	assert( SOCKBUF_VALID( sb ) );
	assert( BER_VALID( ber ) );

	ber_log_printf( LDAP_DEBUG_TRACE, ber->ber_debug,
		"ber_get_next\n" );

	/*
	 * Any ber element looks like this: tag length contents.
	 * Assuming everything's ok, we return the tag byte (we
	 * can assume a single byte), return the length in len,
	 * and the rest of the undecoded element in buf.
	 *
	 * Assumptions:
	 *	1) small tags (less than 128)
	 *	2) definite lengths
	 *	3) primitive encodings used whenever possible
	 */
	
	if (ber->ber_rwptr == NULL) {
		/* XXYYZ
		 * dtest does like this assert.
		 */
		/* assert( ber->ber_buf == NULL ); */
		ber->ber_rwptr = (char *) &ber->ber_tag;
		ber->ber_tag = 0;
	}

#undef PTR_IN_VAR
#define PTR_IN_VAR( ptr, var ) \
	(((ptr)>=(char *) &(var)) && ((ptr)< (char *) &(var)+sizeof(var)))
	
	if (PTR_IN_VAR(ber->ber_rwptr, ber->ber_tag)) {
		if (ber->ber_rwptr == (char *) &ber->ber_tag) {
			if (ber_int_sb_read( sb, ber->ber_rwptr, 1)<=0)
				return LBER_DEFAULT;

			if ((ber->ber_rwptr[0] & LBER_BIG_TAG_MASK)
				!= LBER_BIG_TAG_MASK)
			{
				ber->ber_tag = ber->ber_rwptr[0];
				ber->ber_rwptr = (char *) &ber->ber_usertag;
				goto get_lenbyte;
			}
			ber->ber_rwptr++;
		}
		do {
			/* reading the tag... */
			if (ber_int_sb_read( sb, ber->ber_rwptr, 1)<=0) {
				return LBER_DEFAULT;
			}

			if (! (ber->ber_rwptr[0] & LBER_MORE_TAG_MASK) ) {
				ber->ber_tag>>=sizeof(ber->ber_tag) -
				  ((char *) &ber->ber_tag - ber->ber_rwptr);
				ber->ber_rwptr = (char *) &ber->ber_usertag;
				goto get_lenbyte;
			}
		} while( PTR_IN_VAR(ber->ber_rwptr, ber->ber_tag ));

		errno = ERANGE; /* this is a serious error. */
		return LBER_DEFAULT;
	}

get_lenbyte:
	if (ber->ber_rwptr==(char *) &ber->ber_usertag) {
		unsigned char c;
		if (ber_int_sb_read( sb, (char *) &c, 1)<=0) {
			return LBER_DEFAULT;
		}

		if (c & 0x80U) {
			int len = c & 0x7fU;
			if ( (len==0) || ( len>sizeof( ber->ber_len ) ) ) {
				errno = ERANGE;
				return LBER_DEFAULT;
			}

			ber->ber_rwptr = (char *) &ber->ber_len +
				sizeof(ber->ber_len) - len;
			ber->ber_len = 0;

		} else {
			ber->ber_len = c;
			goto fill_buffer;
		}
	}

	if (PTR_IN_VAR(ber->ber_rwptr, ber->ber_len)) {
		unsigned char netlen[sizeof(ber_len_t)];

		ber_slen_t res;
		ber_slen_t to_go;
		to_go = (char *) &ber->ber_len + sizeof( ber->ber_len ) -
			ber->ber_rwptr;
		assert( to_go > 0 );

		res = BerRead( sb, netlen, to_go );
		if (res <= 0) {
			return LBER_DEFAULT;
		}
		ber->ber_rwptr += res;

		/* convert length. */
		for( to_go = 0; to_go < res ; to_go++ ) {
			ber->ber_len <<= 8;
			ber->ber_len |= netlen[to_go];
		}

		if (PTR_IN_VAR(ber->ber_rwptr, ber->ber_len)) {
			return LBER_DEFAULT;
		}
	}

fill_buffer:	
	/* now fill the buffer. */

	/* make sure length is reasonable */
	if ( ber->ber_len == 0 ||
		( sb->sb_max_incoming && ber->ber_len > sb->sb_max_incoming ))
	{
		errno = ERANGE;
		return LBER_DEFAULT;
	}

	if (ber->ber_buf==NULL) {
		ber->ber_buf = (char *) LBER_MALLOC( ber->ber_len );
		if (ber->ber_buf==NULL) {
			return LBER_DEFAULT;
		}
		ber->ber_rwptr = ber->ber_buf;
		ber->ber_ptr = ber->ber_buf;
		ber->ber_end = ber->ber_buf + ber->ber_len;
	}

	if ((ber->ber_rwptr>=ber->ber_buf) && (ber->ber_rwptr<ber->ber_end)) {
		ber_slen_t res;
		ber_slen_t to_go;
		
		to_go = ber->ber_end - ber->ber_rwptr;
		assert( to_go > 0 );
		
		res = ber_int_sb_read( sb, ber->ber_rwptr, to_go );
		if (res<=0)
			return LBER_DEFAULT;
		ber->ber_rwptr+=res;
		
		if (res<to_go) {
#if defined( EWOULDBLOCK )
			errno = EWOULDBLOCK;
#elif defined( EAGAIN )
			errno = EAGAIN;
#endif			
			return LBER_DEFAULT;
		}
		
		ber->ber_rwptr = NULL;
		*len = ber->ber_len;
		if ( ber->ber_debug ) {
			ber_log_printf( LDAP_DEBUG_TRACE, ber->ber_debug,
				"ber_get_next: tag 0x%lx len %ld contents:\n",
				ber->ber_tag, ber->ber_len );
			ber_log_dump( LDAP_DEBUG_BER, ber->ber_debug, ber, 1 );
		}
		return (ber->ber_tag);
	}

	assert( 0 ); /* ber structure is messed up ?*/
	return LBER_DEFAULT;
}
