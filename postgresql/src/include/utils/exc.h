/*-------------------------------------------------------------------------
 *
 * exc.h
 *	  POSTGRES exception handling definitions.
 *
 *
 * Portions Copyright (c) 1996-2001, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * $Id: exc.h,v 1.22 2001/11/05 17:46:36 momjian Exp $
 *
 *-------------------------------------------------------------------------
 */
#ifndef EXC_H
#define EXC_H

#include <setjmp.h>

extern char *ExcFileName;
extern Index ExcLineNumber;

typedef sigjmp_buf ExcContext;

typedef Exception *ExcId;
typedef long ExcDetail;
typedef char *ExcData;

typedef struct ExcFrame
{
	struct ExcFrame *link;
	ExcContext	context;
	ExcId		id;
	ExcDetail	detail;
	ExcData		data;
	ExcMessage	message;
} ExcFrame;

extern ExcFrame *ExcCurFrameP;

/* These are not used anywhere 1998/6/15 */
#define ExcBegin() \
do { \
	ExcFrame		exception;�\
	\
	exception.link = ExcCurFrameP; \
	if (sigsetjmp(exception.context, 1) == 0) \
	{ \
		ExcCurFrameP = &exception;

#define ExcExcept() \
	} \
		ExcCurFrameP = exception.link; \
	} \
	else \
	{ \
		{

#define ExcEnd() \
			} \
		} \
} while(0)

#define raise4(x, t, d, message) \
		ExcRaise(&(x), (ExcDetail)(t), (ExcData)(d), (ExcMessage)(message))

#define reraise() \
		raise4(*exception.id,exception.detail,exception.data,exception.message)

typedef void ExcProc (Exception *, ExcDetail, ExcData, ExcMessage);


/*
 * prototypes for functions in exc.c
 */
extern void EnableExceptionHandling(bool on);
extern void ExcRaise(Exception *excP,
		 ExcDetail detail,
		 ExcData data,
		 ExcMessage message);


/*
 * prototypes for functions in excabort.c
 */
extern void ExcAbort(const Exception *excP, ExcDetail detail, ExcData data,
		 ExcMessage message);

#endif   /* EXC_H */
