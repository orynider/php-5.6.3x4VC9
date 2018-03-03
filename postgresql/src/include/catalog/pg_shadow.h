/*-------------------------------------------------------------------------
 *
 * pg_shadow.h
 *	  definition of the system "shadow" relation (pg_shadow)
 *	  along with the relation's initial contents.
 *		  pg_user is now a public accessible view on pg_shadow.
 *
 *
 * Portions Copyright (c) 1996-2001, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * $Id: pg_shadow.h,v 1.17 2001/11/05 17:46:32 momjian Exp $
 *
 * NOTES
 *	  the genbki.sh script reads this file and generates .bki
 *	  information from the DATA() statements.
 *
 *		  WHENEVER the definition for pg_shadow changes, the
 *		  view creation of pg_user must be changed in initdb.sh!
 *
 *-------------------------------------------------------------------------
 */
#ifndef PG_SHADOW_H
#define PG_SHADOW_H


/* ----------------
 *		pg_shadow definition.  cpp turns this into
 *		typedef struct FormData_pg_shadow
 * ----------------
 */
CATALOG(pg_shadow) BOOTSTRAP BKI_WITHOUT_OIDS
{
	NameData	usename;
	int4		usesysid;
	bool		usecreatedb;
	bool		usetrace;
	bool		usesuper;
	bool		usecatupd;
	text		passwd;
	int4		valuntil;
} FormData_pg_shadow;

/* ----------------
 *		Form_pg_shadow corresponds to a pointer to a tuple with
 *		the format of pg_shadow relation.
 * ----------------
 */
typedef FormData_pg_shadow *Form_pg_shadow;

/* ----------------
 *		compiler constants for pg_shadow
 * ----------------
 */
#define Natts_pg_shadow				8
#define Anum_pg_shadow_usename			1
#define Anum_pg_shadow_usesysid			2
#define Anum_pg_shadow_usecreatedb		3
#define Anum_pg_shadow_usetrace			4
#define Anum_pg_shadow_usesuper			5
#define Anum_pg_shadow_usecatupd		6
#define Anum_pg_shadow_passwd			7
#define Anum_pg_shadow_valuntil			8

/* ----------------
 *		initial contents of pg_shadow
 *
 * The uppercase quantities will be replaced at initdb time with
 * user choices.
 * ----------------
 */
DATA(insert ( "POSTGRES" PGUID t t t t _null_ _null_ ));

#define BOOTSTRAP_USESYSID 1

#endif   /* PG_SHADOW_H */
