/* $OpenLDAP: pkg/ldap/libraries/libldap/disptmpl.c,v 1.16.6.3 2000/07/04 17:58:51 kurt Exp $ */
/*
 * Copyright 1998-2000 The OpenLDAP Foundation, All Rights Reserved.
 * COPYING RESTRICTIONS APPLY, see COPYRIGHT file
 */
/*  Portions
 * Copyright (c) 1993, 1994 Regents of the University of Michigan.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and that due credit is given
 * to the University of Michigan at Ann Arbor. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 * disptmpl.c:  display template library routines for LDAP clients
 * 7 March 1994 by Mark C Smith
 */

#include "portable.h"

#include <stdio.h>

#include <ac/stdlib.h>

#include <ac/string.h>
#include <ac/time.h>
#include <ac/unistd.h>

#ifdef HAVE_SYS_FILE_H
#include <sys/file.h>
#endif

#include "ldap-int.h"
#include "disptmpl.h"

static void free_disptmpl LDAP_P(( struct ldap_disptmpl *tmpl ));
static int read_next_tmpl LDAP_P(( char **bufp, ber_len_t *blenp,
	struct ldap_disptmpl **tmplp, int dtversion ));

static const char *const	tmploptions[] = {
    "addable", "modrdn",
    "altview",
    NULL
};


static const unsigned long	tmploptvals[] = {
    LDAP_DTMPL_OPT_ADDABLE, LDAP_DTMPL_OPT_ALLOWMODRDN,
    LDAP_DTMPL_OPT_ALTVIEW,
};


static const char *const	itemtypes[] = {
    "cis",			"mls",			"dn",
    "bool",			"jpeg",			"jpegbtn",
    "fax",			"faxbtn",		"audiobtn",
    "time",			"date",			"url",
    "searchact",		"linkact",		"adddnact",
    "addact",			"verifyact",		"mail",
    NULL
};

static const unsigned long	itemsynids[] = {
    LDAP_SYN_CASEIGNORESTR,	LDAP_SYN_MULTILINESTR,	LDAP_SYN_DN,
    LDAP_SYN_BOOLEAN,		LDAP_SYN_JPEGIMAGE,	LDAP_SYN_JPEGBUTTON,
    LDAP_SYN_FAXIMAGE,		LDAP_SYN_FAXBUTTON,	LDAP_SYN_AUDIOBUTTON,
    LDAP_SYN_TIME,		LDAP_SYN_DATE,		LDAP_SYN_LABELEDURL,
    LDAP_SYN_SEARCHACTION,	LDAP_SYN_LINKACTION,	LDAP_SYN_ADDDNACTION,
    LDAP_SYN_ADDDNACTION,	LDAP_SYN_VERIFYDNACTION,LDAP_SYN_RFC822ADDR,
};


static const char *const	itemoptions[] = {
    "ro",		       		"sort",
    "1val",				"hide",
    "required",				"hideiffalse",
    NULL
};


static const unsigned long	itemoptvals[] = {
    LDAP_DITEM_OPT_READONLY,		LDAP_DITEM_OPT_SORTVALUES,
    LDAP_DITEM_OPT_SINGLEVALUED,	LDAP_DITEM_OPT_HIDEIFEMPTY,
    LDAP_DITEM_OPT_VALUEREQUIRED,	LDAP_DITEM_OPT_HIDEIFFALSE,
};


#define ADDEF_CONSTANT	"constant"
#define ADDEF_ADDERSDN	"addersdn"


int
ldap_init_templates( char *file, struct ldap_disptmpl **tmpllistp )
{
    FILE	*fp;
    char	*buf;
    long	rlen, len;
    int		rc, eof;

    *tmpllistp = NULL;

    if (( fp = fopen( file, "r" )) == NULL ) {
	return( LDAP_TMPL_ERR_FILE );
    }

    if ( fseek( fp, 0L, SEEK_END ) != 0 ) {	/* move to end to get len */
	fclose( fp );
	return( LDAP_TMPL_ERR_FILE );
    }

    len = ftell( fp );

    if ( fseek( fp, 0L, SEEK_SET ) != 0 ) {	/* back to start of file */
	fclose( fp );
	return( LDAP_TMPL_ERR_FILE );
    }

    if (( buf = LDAP_MALLOC( (size_t)len )) == NULL ) {
	fclose( fp );
	return( LDAP_TMPL_ERR_MEM );
    }

    rlen = fread( buf, 1, (size_t)len, fp );
    eof = feof( fp );
    fclose( fp );

    if ( rlen != len && !eof ) {	/* error:  didn't get the whole file */
	LDAP_FREE( buf );
	return( LDAP_TMPL_ERR_FILE );
    }

    rc = ldap_init_templates_buf( buf, rlen, tmpllistp );
    LDAP_FREE( buf );

    return( rc );
}


int
ldap_init_templates_buf( char *buf, ber_len_t buflen,
	struct ldap_disptmpl **tmpllistp )
{
    int				rc=-1, version;
    char			**toks;
    struct ldap_disptmpl	*prevtmpl, *tmpl;

    *tmpllistp = prevtmpl = NULL;

    if ( ldap_int_next_line_tokens( &buf, &buflen, &toks ) != 2 ||
	    strcasecmp( toks[ 0 ], "version" ) != 0 ) {
	LDAP_VFREE( toks );
	return( LDAP_TMPL_ERR_SYNTAX );
    }
    version = atoi( toks[ 1 ] );
    LDAP_VFREE( toks );
    if ( version != LDAP_TEMPLATE_VERSION ) {
	return( LDAP_TMPL_ERR_VERSION );
    }

    while ( buflen > 0 && ( rc = read_next_tmpl( &buf, &buflen, &tmpl,
	    version )) == 0 && tmpl != NULL ) {
	if ( prevtmpl == NULL ) {
	    *tmpllistp = tmpl;
	} else {
	    prevtmpl->dt_next = tmpl;
	}
	prevtmpl = tmpl;
    }

    if ( rc != 0 ) {
	ldap_free_templates( *tmpllistp );
    }

    return( rc );
}
	    


void
ldap_free_templates( struct ldap_disptmpl *tmpllist )
{
    struct ldap_disptmpl	*tp, *nexttp;

    if ( tmpllist != NULL ) {
	for ( tp = tmpllist; tp != NULL; tp = nexttp ) {
	    nexttp = tp->dt_next;
	    free_disptmpl( tp );
	}
    }
}


static void
free_disptmpl( struct ldap_disptmpl *tmpl )
{
    if ( tmpl != NULL ) {
	if ( tmpl->dt_name != NULL ) {
	    LDAP_FREE(  tmpl->dt_name );
	}

	if ( tmpl->dt_pluralname != NULL ) {
	    LDAP_FREE( tmpl->dt_pluralname );
	}

	if ( tmpl->dt_iconname != NULL ) {
	    LDAP_FREE( tmpl->dt_iconname );
	}

	if ( tmpl->dt_authattrname != NULL ) {
	    LDAP_FREE( tmpl->dt_authattrname );
	}

	if ( tmpl->dt_defrdnattrname != NULL ) {
	    LDAP_FREE( tmpl->dt_defrdnattrname );
	}

	if ( tmpl->dt_defaddlocation != NULL ) {
	    LDAP_FREE( tmpl->dt_defaddlocation );
	}

	if (  tmpl->dt_oclist != NULL ) {
	    struct ldap_oclist	*ocp, *nextocp;

	    for ( ocp = tmpl->dt_oclist; ocp != NULL; ocp = nextocp ) {
		nextocp = ocp->oc_next;
		LDAP_VFREE( ocp->oc_objclasses );
		LDAP_FREE( ocp );
	    }
	}

	if (  tmpl->dt_adddeflist != NULL ) {
	    struct ldap_adddeflist	*adp, *nextadp;

	    for ( adp = tmpl->dt_adddeflist; adp != NULL; adp = nextadp ) {
		nextadp = adp->ad_next;
		if( adp->ad_attrname != NULL ) {
		    LDAP_FREE( adp->ad_attrname );
		}
		if( adp->ad_value != NULL ) {
		    LDAP_FREE( adp->ad_value );
		}
		LDAP_FREE( adp );
	    }
	}

	if (  tmpl->dt_items != NULL ) {
	    struct ldap_tmplitem	*rowp, *nextrowp, *colp, *nextcolp;

	    for ( rowp = tmpl->dt_items; rowp != NULL; rowp = nextrowp ) {
		nextrowp = rowp->ti_next_in_col;
		for ( colp = rowp; colp != NULL; colp = nextcolp ) {
		    nextcolp = colp->ti_next_in_row;
		    if ( colp->ti_attrname != NULL ) {
			LDAP_FREE( colp->ti_attrname );
		    }
		    if ( colp->ti_label != NULL ) {
			LDAP_FREE( colp->ti_label );
		    }
		    if ( colp->ti_args != NULL ) {
			LDAP_VFREE( colp->ti_args );
		    }
		    LDAP_FREE( colp );
		}
	    }
	}

	LDAP_FREE( tmpl );
    }
}


struct ldap_disptmpl *
ldap_first_disptmpl( struct ldap_disptmpl *tmpllist )
{
    return( tmpllist );
}


struct ldap_disptmpl *
ldap_next_disptmpl( struct ldap_disptmpl *tmpllist,
	struct ldap_disptmpl *tmpl )
{
    return( tmpl == NULL ? tmpl : tmpl->dt_next );
}


struct ldap_disptmpl *
ldap_name2template( char *name, struct ldap_disptmpl *tmpllist )
{
    struct ldap_disptmpl	*dtp;

    for ( dtp = ldap_first_disptmpl( tmpllist ); dtp != NULL;
	    dtp = ldap_next_disptmpl( tmpllist, dtp )) {
	if ( strcasecmp( name, dtp->dt_name ) == 0 ) {
	    return( dtp );
	}
    }

    return( NULL );
}


struct ldap_disptmpl *
ldap_oc2template( char **oclist, struct ldap_disptmpl *tmpllist )
{
    struct ldap_disptmpl	*dtp;
    struct ldap_oclist		*oclp;
    int				i, j, needcnt, matchcnt;

    if ( tmpllist == NULL || oclist == NULL || oclist[ 0 ] == NULL ) {
	return( NULL );
    }

    for ( dtp = ldap_first_disptmpl( tmpllist ); dtp != NULL;
		dtp = ldap_next_disptmpl( tmpllist, dtp )) {
	for ( oclp = dtp->dt_oclist; oclp != NULL;
		oclp = oclp->oc_next ) {
	    needcnt = matchcnt = 0;
	    for ( i = 0; oclp->oc_objclasses[ i ] != NULL; ++i ) {
		for ( j = 0; oclist[ j ] != NULL; ++j ) {
		    if ( strcasecmp( oclist[ j ], oclp->oc_objclasses[ i ] )
			    == 0 ) {
			++matchcnt;
		    }
		}
		++needcnt;
	    }

	    if ( matchcnt == needcnt ) {
		return( dtp );
	    }
	}
    }

    return( NULL );
}


struct ldap_tmplitem *
ldap_first_tmplrow( struct ldap_disptmpl *tmpl )
{
    return( tmpl->dt_items );
}


struct ldap_tmplitem *
ldap_next_tmplrow( struct ldap_disptmpl *tmpl, struct ldap_tmplitem *row )
{
    return( row == NULL ? row : row->ti_next_in_col );
}


struct ldap_tmplitem *
ldap_first_tmplcol( struct ldap_disptmpl *tmpl, struct ldap_tmplitem *row )
{
    return( row );
}


struct ldap_tmplitem *
ldap_next_tmplcol( struct ldap_disptmpl *tmpl, struct ldap_tmplitem *row,
	struct ldap_tmplitem *col )
{
    return( col == NULL ? col : col->ti_next_in_row );
}


char **
ldap_tmplattrs( struct ldap_disptmpl *tmpl, char **includeattrs,
	int exclude, unsigned long syntaxmask )
{
/*
 * this routine should filter out duplicate attributes...
 */
    struct ldap_tmplitem	*tirowp, *ticolp;
    int			i, attrcnt, memerr;
    char		**attrs;

    attrcnt = 0;
    memerr = 0;

    if (( attrs = (char **)LDAP_MALLOC( sizeof( char * ))) == NULL ) {
	return( NULL );
    }

    if ( includeattrs != NULL ) {
	for ( i = 0; !memerr && includeattrs[ i ] != NULL; ++i ) {
	    if (( attrs = (char **)LDAP_REALLOC( attrs, ( attrcnt + 2 ) *
		    sizeof( char * ))) == NULL || ( attrs[ attrcnt++ ] =
		    LDAP_STRDUP( includeattrs[ i ] )) == NULL ) {
		memerr = 1;
	    } else {
		attrs[ attrcnt ] = NULL;
	    }
	}
    }

    for ( tirowp = ldap_first_tmplrow( tmpl );
	    !memerr && tirowp != NULL;
	    tirowp = ldap_next_tmplrow( tmpl, tirowp )) {
	for ( ticolp = ldap_first_tmplcol( tmpl, tirowp );
		ticolp != NULL;
		ticolp = ldap_next_tmplcol( tmpl, tirowp, ticolp )) {

	    if ( syntaxmask != 0 ) {
		if (( exclude &&
			( syntaxmask & ticolp->ti_syntaxid ) != 0 ) ||
			( !exclude &&
			( syntaxmask & ticolp->ti_syntaxid ) == 0 )) {
		    continue;
		}
	    }

	    if ( ticolp->ti_attrname != NULL ) {
		if (( attrs = (char **)LDAP_REALLOC( attrs, ( attrcnt + 2 ) *
			sizeof( char * ))) == NULL || ( attrs[ attrcnt++ ] =
			LDAP_STRDUP( ticolp->ti_attrname )) == NULL ) {
		    memerr = 1;
		} else {
		    attrs[ attrcnt ] = NULL;
		}
	    }
	}
    }

    if ( memerr || attrcnt == 0 ) {
	for ( i = 0; i < attrcnt; ++i ) {
	    if ( attrs[ i ] != NULL ) {
		LDAP_FREE( attrs[ i ] );
	    }
	}

	LDAP_FREE( (char *)attrs );
	return( NULL );
    }

    return( attrs );
}


static int
read_next_tmpl( char **bufp, ber_len_t *blenp, struct ldap_disptmpl **tmplp,
	int dtversion )
{
    int				i, j, tokcnt, samerow, adsource;
    char			**toks, *itemopts;
    struct ldap_disptmpl	*tmpl;
    struct ldap_oclist		*ocp, *prevocp = NULL;
    struct ldap_adddeflist	*adp, *prevadp = NULL;
    struct ldap_tmplitem	*rowp = NULL, *ip, *previp = NULL;

    *tmplp = NULL;

    /*
     * template name comes first
     */
    if (( tokcnt = ldap_int_next_line_tokens( bufp, blenp, &toks )) != 1 ) {
	LDAP_VFREE( toks );
	return( tokcnt == 0 ? 0 : LDAP_TMPL_ERR_SYNTAX );
    }

    if (( tmpl = (struct ldap_disptmpl *)LDAP_CALLOC( 1,
	    sizeof( struct ldap_disptmpl ))) == NULL ) {
	LDAP_VFREE( toks );
	return(  LDAP_TMPL_ERR_MEM );
    }
    tmpl->dt_name = toks[ 0 ];
    LDAP_FREE( (char *)toks );

    /*
     * template plural name comes next
     */
    if (( tokcnt = ldap_int_next_line_tokens( bufp, blenp, &toks )) != 1 ) {
	LDAP_VFREE( toks );
	free_disptmpl( tmpl );
	return( LDAP_TMPL_ERR_SYNTAX );
    }
    tmpl->dt_pluralname = toks[ 0 ];
    LDAP_FREE( (char *)toks );

    /*
     * template icon name is next
     */
    if (( tokcnt = ldap_int_next_line_tokens( bufp, blenp, &toks )) != 1 ) {
	LDAP_VFREE( toks );
	free_disptmpl( tmpl );
	return( LDAP_TMPL_ERR_SYNTAX );
    }
    tmpl->dt_iconname = toks[ 0 ];
    LDAP_FREE( (char *)toks );

    /*
     * template options come next
     */
    if (( tokcnt = ldap_int_next_line_tokens( bufp, blenp, &toks )) < 1 ) {
	LDAP_VFREE( toks );
	free_disptmpl( tmpl );
	return( LDAP_TMPL_ERR_SYNTAX );
    }
    for ( i = 0; toks[ i ] != NULL; ++i ) {
	for ( j = 0; tmploptions[ j ] != NULL; ++j ) {
	    if ( strcasecmp( toks[ i ], tmploptions[ j ] ) == 0 ) {
		tmpl->dt_options |= tmploptvals[ j ];
	    }
	}
    }
    LDAP_VFREE( toks );

    /*
     * object class list is next
     */
    while (( tokcnt = ldap_int_next_line_tokens( bufp, blenp, &toks )) > 0 ) {
	if (( ocp = (struct ldap_oclist *)LDAP_CALLOC( 1,
		sizeof( struct ldap_oclist ))) == NULL ) {
	    LDAP_VFREE( toks );
	    free_disptmpl( tmpl );
	    return( LDAP_TMPL_ERR_MEM );
	}
	ocp->oc_objclasses = toks;
	if ( tmpl->dt_oclist == NULL ) {
	    tmpl->dt_oclist = ocp;
	} else {
	    prevocp->oc_next = ocp;
	}
	prevocp = ocp;
    }
    if ( tokcnt < 0 ) {
	free_disptmpl( tmpl );
	return( LDAP_TMPL_ERR_SYNTAX );
    }

    /*
     * read name of attribute to authenticate as
     */
    if (( tokcnt = ldap_int_next_line_tokens( bufp, blenp, &toks )) != 1 ) {
	LDAP_VFREE( toks );
	free_disptmpl( tmpl );
	return( LDAP_TMPL_ERR_SYNTAX );
    }
    if ( toks[ 0 ][ 0 ] != '\0' ) {
	tmpl->dt_authattrname = toks[ 0 ];
    } else {
	LDAP_FREE( toks[ 0 ] );
    }
    LDAP_FREE( (char *)toks );

    /*
     * read default attribute to use for RDN
     */
    if (( tokcnt = ldap_int_next_line_tokens( bufp, blenp, &toks )) != 1 ) {
	LDAP_VFREE( toks );
	free_disptmpl( tmpl );
	return( LDAP_TMPL_ERR_SYNTAX );
    }
    tmpl->dt_defrdnattrname = toks[ 0 ];
    LDAP_FREE( (char *)toks );

    /*
     * read default location for new entries
     */
    if (( tokcnt = ldap_int_next_line_tokens( bufp, blenp, &toks )) != 1 ) {
	LDAP_VFREE( toks );
	free_disptmpl( tmpl );
	return( LDAP_TMPL_ERR_SYNTAX );
    }
    if ( toks[ 0 ][ 0 ] != '\0' ) {
	tmpl->dt_defaddlocation = toks[ 0 ];
    } else {
	LDAP_FREE( toks[ 0 ] );
    }
    LDAP_FREE( (char *)toks );

    /*
     * read list of rules used to define default values for new entries
     */
    while (( tokcnt = ldap_int_next_line_tokens( bufp, blenp, &toks )) > 0 ) {
	if ( strcasecmp( ADDEF_CONSTANT, toks[ 0 ] ) == 0 ) {
	    adsource = LDAP_ADSRC_CONSTANTVALUE;
	} else if ( strcasecmp( ADDEF_ADDERSDN, toks[ 0 ] ) == 0 ) {
	    adsource = LDAP_ADSRC_ADDERSDN;
	} else {
	    adsource = 0;
	}
	if ( adsource == 0 || tokcnt < 2 ||
		( adsource == LDAP_ADSRC_CONSTANTVALUE && tokcnt != 3 ) ||
		( adsource == LDAP_ADSRC_ADDERSDN && tokcnt != 2 )) {
	    LDAP_VFREE( toks );
	    free_disptmpl( tmpl );
	    return( LDAP_TMPL_ERR_SYNTAX );
	}
		
	if (( adp = (struct ldap_adddeflist *)LDAP_CALLOC( 1,
		sizeof( struct ldap_adddeflist ))) == NULL ) {
	    LDAP_VFREE( toks );
	    free_disptmpl( tmpl );
	    return( LDAP_TMPL_ERR_MEM );
	}
	adp->ad_source = adsource;
	adp->ad_attrname = toks[ 1 ];
	if ( adsource == LDAP_ADSRC_CONSTANTVALUE ) {
	    adp->ad_value = toks[ 2 ];
	}
	LDAP_FREE( toks[ 0 ] );
	LDAP_FREE( (char *)toks );

	if ( tmpl->dt_adddeflist == NULL ) {
	    tmpl->dt_adddeflist = adp;
	} else {
	    prevadp->ad_next = adp;
	}
	prevadp = adp;
    }

    /*
     * item list is next
     */
    samerow = 0;
    while (( tokcnt = ldap_int_next_line_tokens( bufp, blenp, &toks )) > 0 ) {
	if ( strcasecmp( toks[ 0 ], "item" ) == 0 ) {
	    if ( tokcnt < 4 ) {
		LDAP_VFREE( toks );
		free_disptmpl( tmpl );
		return( LDAP_TMPL_ERR_SYNTAX );
	    }

	    if (( ip = (struct ldap_tmplitem *)LDAP_CALLOC( 1,
		    sizeof( struct ldap_tmplitem ))) == NULL ) {
		LDAP_VFREE( toks );
		free_disptmpl( tmpl );
		return( LDAP_TMPL_ERR_MEM );
	    }

	    /*
	     * find syntaxid from config file string
	     */
	    while (( itemopts = strrchr( toks[ 1 ], ',' )) != NULL ) {
		*itemopts++ = '\0';
		for ( i = 0; itemoptions[ i ] != NULL; ++i ) {
		    if ( strcasecmp( itemopts, itemoptions[ i ] ) == 0 ) {
			break;
		    }
		}
		if ( itemoptions[ i ] == NULL ) {
		    LDAP_VFREE( toks );
		    free_disptmpl( tmpl );
		    return( LDAP_TMPL_ERR_SYNTAX );
		}
		ip->ti_options |= itemoptvals[ i ];
	    }

	    for ( i = 0; itemtypes[ i ] != NULL; ++i ) {
		if ( strcasecmp( toks[ 1 ], itemtypes[ i ] ) == 0 ) {
		    break;
		}
	    }
	    if ( itemtypes[ i ] == NULL ) {
		LDAP_VFREE( toks );
		free_disptmpl( tmpl );
		return( LDAP_TMPL_ERR_SYNTAX );
	    }

	    LDAP_FREE( toks[ 0 ] );
	    LDAP_FREE( toks[ 1 ] );
	    ip->ti_syntaxid = itemsynids[ i ];
	    ip->ti_label = toks[ 2 ];
	    if ( toks[ 3 ][ 0 ] == '\0' ) {
		ip->ti_attrname = NULL;
		LDAP_FREE( toks[ 3 ] );
	    } else {
		ip->ti_attrname = toks[ 3 ];
	    }
	    if ( toks[ 4 ] != NULL ) {	/* extra args. */
		for ( i = 0; toks[ i + 4 ] != NULL; ++i ) {
		    ;
		}
		if (( ip->ti_args = (char **) LDAP_CALLOC( i + 1, sizeof( char * )))
			== NULL ) {
		    free_disptmpl( tmpl );
		    return( LDAP_TMPL_ERR_MEM );
		}
		for ( i = 0; toks[ i + 4 ] != NULL; ++i ) {
		    ip->ti_args[ i ] = toks[ i + 4 ];
		}
	    }
	    LDAP_FREE( (char *)toks );

	    if ( tmpl->dt_items == NULL ) {
		tmpl->dt_items = rowp = ip;
	    } else if ( samerow ) {
		previp->ti_next_in_row = ip;
	    } else {
		rowp->ti_next_in_col = ip;
		rowp = ip;
	    }
	    previp = ip;
	    samerow = 0;
	} else if ( strcasecmp( toks[ 0 ], "samerow" ) == 0 ) {
	    LDAP_VFREE( toks );
	    samerow = 1;
	} else {
	    LDAP_VFREE( toks );
	    free_disptmpl( tmpl );
	    return( LDAP_TMPL_ERR_SYNTAX );
	}
    }
    if ( tokcnt < 0 ) {
	free_disptmpl( tmpl );
	return( LDAP_TMPL_ERR_SYNTAX );
    }

    *tmplp = tmpl;
    return( 0 );
}
