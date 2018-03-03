/*-------------------------------------------------------------------------
 *
 * sets.h
 *
 *
 *
 * Portions Copyright (c) 1996-2001, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * $Id: sets.h,v 1.12 2001/11/05 17:46:36 momjian Exp $
 *
 *-------------------------------------------------------------------------
 */
#ifndef SETS_H
#define SETS_H

#include "fmgr.h"


/* Temporary name of a set function, before SetDefine changes it. */
#define GENERICSETNAME "ZYX#Set#ZYX"

extern Oid	SetDefine(char *querystr, char *typename);

extern Datum seteval(PG_FUNCTION_ARGS);

#endif   /* SETS_H */
