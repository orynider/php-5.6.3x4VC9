/*-------------------------------------------------------------------------
 *
 * indexvalid.c
 *	  index tuple qualification validity checking code
 *
 * Portions Copyright (c) 1996-2001, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 *
 * IDENTIFICATION
 *	  $Header: /cvsroot/pgsql-server/src/backend/access/common/indexvalid.c,v 1.27 2001/07/15 22:48:15 tgl Exp $
 *
 *-------------------------------------------------------------------------
 */

#include "postgres.h"

#include "access/iqual.h"
#include "executor/execdebug.h"

/* ----------------------------------------------------------------
 *				  index scan key qualification code
 * ----------------------------------------------------------------
 */
int			NIndexTupleProcessed;


/* ----------------
 *		index_keytest - does this index tuple satisfy the scan key(s)?
 * ----------------
 */
bool
index_keytest(IndexTuple tuple,
			  TupleDesc tupdesc,
			  int scanKeySize,
			  ScanKey key)
{
	IncrIndexProcessed();

	while (scanKeySize > 0)
	{
		Datum		datum;
		bool		isNull;
		Datum		test;

		datum = index_getattr(tuple,
							  key->sk_attno,
							  tupdesc,
							  &isNull);

		if (isNull)
		{
			/* XXX eventually should check if SK_ISNULL */
			return false;
		}

		if (key->sk_flags & SK_ISNULL)
			return false;

		if (key->sk_flags & SK_COMMUTE)
			test = FunctionCall2(&key->sk_func, key->sk_argument, datum);
		else
			test = FunctionCall2(&key->sk_func, datum, key->sk_argument);

		if (DatumGetBool(test) == !!(key->sk_flags & SK_NEGATE))
			return false;

		key++;
		scanKeySize--;
	}

	return true;
}
