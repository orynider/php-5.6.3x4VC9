/* $OpenLDAP: pkg/ldap/include/lber_pvt.h,v 1.3.8.3 2000/07/04 17:58:48 kurt Exp $ */
/*
 * Copyright 1998-2000 The OpenLDAP Foundation, Redwood City, California, USA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted only
 * as authorized by the OpenLDAP Public License.  A copy of this
 * license is available at http://www.OpenLDAP.org/license.html or
 * in file LICENSE in the top-level directory of the distribution.
 */
/*
 * lber_pvt.h - Header for ber_pvt_ functions. These are meant to be used
 * 		by the OpenLDAP distribution only.
 */

#ifndef _LBER_PVT_H
#define _LBER_PVT_H 1

#include <lber.h>

LDAP_BEGIN_DECL

typedef struct sockbuf_buf {
	ber_len_t		buf_size;
	ber_len_t		buf_ptr;
	ber_len_t		buf_end;
	char			*buf_base;
} Sockbuf_Buf;

/*
 * bprint.c
 */
LBER_F( BER_LOG_PRINT_FN ) ber_pvt_log_print;

LBER_F( int )
ber_pvt_log_printf LDAP_P((
	int errlvl,
	int loglvl,
	const char *fmt,
	... )) LDAP_GCCATTR((format(printf, 3, 4)));

/*
 * sockbuf.c
 */
LBER_F( ber_slen_t )
ber_pvt_sb_do_write LDAP_P(( Sockbuf_IO_Desc *sbiod, Sockbuf_Buf *buf_out ));

LBER_F( void )
ber_pvt_sb_buf_init LDAP_P(( Sockbuf_Buf *buf ));

LBER_F( void )
ber_pvt_sb_buf_destroy LDAP_P(( Sockbuf_Buf *buf ));

LBER_F( int )
ber_pvt_sb_grow_buffer LDAP_P(( Sockbuf_Buf *buf, ber_len_t minsize ));

LBER_F( ber_len_t )
ber_pvt_sb_copy_out LDAP_P(( Sockbuf_Buf *sbb, char *buf, ber_len_t len ));

LBER_F( int )
ber_pvt_socket_set_nonblock LDAP_P(( ber_socket_t sd, int nb ));

LDAP_END_DECL

#endif

