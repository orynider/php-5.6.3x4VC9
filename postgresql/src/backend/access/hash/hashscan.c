/*-------------------------------------------------------------------------
 *
 * hashscan.c
 *	  manage scans on hash tables
 *
 * Portions Copyright (c) 1996-2001, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 *
 * IDENTIFICATION
 *	  $Header: /cvsroot/pgsql-server/src/backend/access/hash/hashscan.c,v 1.25 2001/07/15 22:48:15 tgl Exp $
 *
 * NOTES
 *	  Because we can be doing an index scan on a relation while we
 *	  update it, we need to avoid missing data that moves around in
 *	  the index.  The routines and global variables in this file
 *	  guarantee that all scans in the local address space stay
 *	  correctly positioned.  This is all we need to worry about, since
 *	  write locking guarantees that no one else will be on the same
 *	  page at the same time as we are.
 *
 *	  The scheme is to manage a list of active scans in the current
 *	  backend.	Whenever we add or remove records from an index, we
 *	  check the list of active scans to see if any has been affected.
 *	  A scan is affected only if it is on the same relation, and the
 *	  same page, as the update.
 *
 *-------------------------------------------------------------------------
 */

#include "postgres.h"

#include "access/hash.h"

static void _hash_scandel(IndexScanDesc scan, BlockNumber blkno, OffsetNumber offno);
static bool _hash_scantouched(IndexScanDesc scan, BlockNumber blkno, OffsetNumber offno);

typedef struct HashScanListData
{
	IndexScanDesc hashsl_scan;
	struct HashScanListData *hashsl_next;
} HashScanListData;

typedef HashScanListData *HashScanList;

static HashScanList HashScans = (HashScanList) NULL;


/*
 * AtEOXact_hash() --- clean up hash subsystem at xact abort or commit.
 *
 * This is here because it needs to touch this module's static var HashScans.
 */
void
AtEOXact_hash(void)
{
	/*
	 * Note: these actions should only be necessary during xact abort; but
	 * they can't hurt during a commit.
	 */

	/*
	 * Reset the active-scans list to empty. We do not need to free the
	 * list elements, because they're all palloc()'d, so they'll go away
	 * at end of transaction anyway.
	 */
	HashScans = NULL;

	/* If we were building a hash, we ain't anymore. */
	BuildingHash = false;
}

/*
 *	_Hash_regscan() -- register a new scan.
 */
void
_hash_regscan(IndexScanDesc scan)
{
	HashScanList new_el;

	new_el = (HashScanList) palloc(sizeof(HashScanListData));
	new_el->hashsl_scan = scan;
	new_el->hashsl_next = HashScans;
	HashScans = new_el;
}

/*
 *	_hash_dropscan() -- drop a scan from the scan list
 */
void
_hash_dropscan(IndexScanDesc scan)
{
	HashScanList chk,
				last;

	last = (HashScanList) NULL;
	for (chk = HashScans;
		 chk != (HashScanList) NULL && chk->hashsl_scan != scan;
		 chk = chk->hashsl_next)
		last = chk;

	if (chk == (HashScanList) NULL)
		elog(ERROR, "hash scan list trashed; can't find 0x%p", (void *) scan);

	if (last == (HashScanList) NULL)
		HashScans = chk->hashsl_next;
	else
		last->hashsl_next = chk->hashsl_next;

	pfree(chk);
}

void
_hash_adjscans(Relation rel, ItemPointer tid)
{
	HashScanList l;
	Oid			relid;

	relid = RelationGetRelid(rel);
	for (l = HashScans; l != (HashScanList) NULL; l = l->hashsl_next)
	{
		if (relid == l->hashsl_scan->relation->rd_id)
			_hash_scandel(l->hashsl_scan, ItemPointerGetBlockNumber(tid),
						  ItemPointerGetOffsetNumber(tid));
	}
}

static void
_hash_scandel(IndexScanDesc scan, BlockNumber blkno, OffsetNumber offno)
{
	ItemPointer current;
	Buffer		buf;
	Buffer		metabuf;
	HashScanOpaque so;

	if (!_hash_scantouched(scan, blkno, offno))
		return;

	metabuf = _hash_getbuf(scan->relation, HASH_METAPAGE, HASH_READ);

	so = (HashScanOpaque) scan->opaque;
	buf = so->hashso_curbuf;

	current = &(scan->currentItemData);
	if (ItemPointerIsValid(current)
		&& ItemPointerGetBlockNumber(current) == blkno
		&& ItemPointerGetOffsetNumber(current) >= offno)
	{
		_hash_step(scan, &buf, BackwardScanDirection, metabuf);
		so->hashso_curbuf = buf;
	}

	current = &(scan->currentMarkData);
	if (ItemPointerIsValid(current)
		&& ItemPointerGetBlockNumber(current) == blkno
		&& ItemPointerGetOffsetNumber(current) >= offno)
	{
		ItemPointerData tmp;

		tmp = *current;
		*current = scan->currentItemData;
		scan->currentItemData = tmp;
		_hash_step(scan, &buf, BackwardScanDirection, metabuf);
		so->hashso_mrkbuf = buf;
		tmp = *current;
		*current = scan->currentItemData;
		scan->currentItemData = tmp;
	}
}

static bool
_hash_scantouched(IndexScanDesc scan,
				  BlockNumber blkno,
				  OffsetNumber offno)
{
	ItemPointer current;

	current = &(scan->currentItemData);
	if (ItemPointerIsValid(current)
		&& ItemPointerGetBlockNumber(current) == blkno
		&& ItemPointerGetOffsetNumber(current) >= offno)
		return true;

	current = &(scan->currentMarkData);
	if (ItemPointerIsValid(current)
		&& ItemPointerGetBlockNumber(current) == blkno
		&& ItemPointerGetOffsetNumber(current) >= offno)
		return true;

	return false;
}
