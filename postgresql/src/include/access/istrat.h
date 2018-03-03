/*-------------------------------------------------------------------------
 *
 * istrat.h
 *	  POSTGRES index strategy definitions.
 *
 *
 * Portions Copyright (c) 1996-2001, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * $Id: istrat.h,v 1.23 2001/11/05 17:46:31 momjian Exp $
 *
 *-------------------------------------------------------------------------
 */
#ifndef ISTRAT_H
#define ISTRAT_H

#include "utils/rel.h"

/*
 * StrategyNumberIsValid
 *		True iff the strategy number is valid.
 */
#define StrategyNumberIsValid(strategyNumber) \
	((bool) ((strategyNumber) != InvalidStrategy))

/*
 * StrategyNumberIsInBounds
 *		True iff strategy number is within given bounds.
 *
 * Note:
 *		Assumes StrategyNumber is an unsigned type.
 *		Assumes the bounded interval to be (0,max].
 */
#define StrategyNumberIsInBounds(strategyNumber, maxStrategyNumber) \
	((bool)(InvalidStrategy < (strategyNumber) && \
			(strategyNumber) <= (maxStrategyNumber)))

/*
 * StrategyMapIsValid
 *		True iff the index strategy mapping is valid.
 */
#define StrategyMapIsValid(map) PointerIsValid(map)

/*
 * IndexStrategyIsValid
 *		True iff the index strategy is valid.
 */
#define IndexStrategyIsValid(s) PointerIsValid(s)

extern StrategyMap IndexStrategyGetStrategyMap(IndexStrategy indexStrategy,
					  StrategyNumber maxStrategyNum, AttrNumber attrNum);

extern Size AttributeNumberGetIndexStrategySize(AttrNumber maxAttributeNumber,
									StrategyNumber maxStrategyNumber);
extern StrategyNumber RelationGetStrategy(Relation relation,
			   AttrNumber attributeNumber, StrategyEvaluation evaluation,
					RegProcedure procedure);
extern void IndexSupportInitialize(IndexStrategy indexStrategy,
					   RegProcedure *indexSupport,
					   bool *isUnique,
					   Oid indexObjectId,
					   Oid accessMethodObjectId,
					   StrategyNumber maxStrategyNumber,
					   StrategyNumber maxSupportNumber,
					   AttrNumber maxAttributeNumber);

#endif   /* ISTRAT_H */
