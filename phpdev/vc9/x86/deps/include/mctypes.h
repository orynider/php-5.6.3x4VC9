#ifndef __MCTYPES_H
#define __MCTYPES_H   1


/*
 |-----------------------------------------------------------------------------
 |        Sybase SQL Monitor
 |        Confidential Property of Sybase, Inc.
 |        (c) Copyright Sybase, Inc 1995,1997
 |        All rights reserved
 |-----------------------------------------------------------------------------
 |  FILE: mctypes.h
 |
 |  DESCRIPTION:
 |
 |  Contains typedefs for the Sqlmon Client Library.
 |
 |-----------------------------------------------------------------------------
 */


/*/////////////////////////////////////////////////////////////////////////////
 |
 |  Supportive Declarations
 |
 */

#include "mcconfig.h"

#include <stdlib.h>
/* stdlib provides size_t */

#include <cstypes.h>
/* cstypes provides CS_DATETIME */




/*/////////////////////////////////////////////////////////////////////////////
 |
 |   SMC DataTypes
 |
 */
typedef char             SMC_CHAR;
typedef char*            SMC_CHARP;
typedef char**           SMC_CHARPP;
typedef CS_CONST char*   SMC_CCHARP;
typedef wchar_t          SMC_WCHAR;
typedef wchar_t*         SMC_WCHARP;
typedef wchar_t**        SMC_WCHARPP;
typedef CS_CONST wchar_t* SMC_WCCHARP;
typedef int              SMC_BOOL;
typedef CS_DATETIME	 SMC_DATETIME;
typedef double           SMC_DOUBLE;
typedef double*          SMC_DOUBLEP;
typedef float            SMC_FLOAT;
typedef float*           SMC_FLOATP;
typedef int              SMC_INT;
typedef int*             SMC_INTP;
typedef long             SMC_LONG;
typedef long*            SMC_LONGP;
typedef size_t           SMC_SIZET;
typedef size_t*          SMC_SIZETP;
typedef void             SMC_VOID;
typedef void*            SMC_VOIDP;
typedef SMC_SIZET        SMC_CONNECT_ID;
typedef SMC_SIZETP       SMC_CONNECT_IDP;
typedef SMC_SIZET        SMC_COMMAND_ID;
typedef SMC_SIZETP       SMC_COMMAND_IDP;
typedef SMC_SIZET        SMC_VIEW_ID;
typedef SMC_SIZETP       SMC_VIEW_IDP;
typedef SMC_SIZET        SMC_FILTER_ID;
typedef SMC_SIZETP       SMC_FILTER_IDP;
typedef SMC_SIZET        SMC_ALARM_ID;
typedef SMC_SIZETP       SMC_ALARM_IDP;
typedef SMC_SIZET        SMC_SESSION_ID;
typedef SMC_SIZETP       SMC_SESSION_IDP;

typedef void
(*SMC_GEN_CALLBACK) PROTOTYPE((
		      SMC_CONNECT_ID clientId,
		      SMC_COMMAND_ID commandId,
		      SMC_VOIDP userDataHandle
));

typedef void
(*SMC_CALLBACK) PROTOTYPE((
		      SMC_CONNECT_ID clientID,
                      SMC_VOIDP      userDataHandle,
                      SMC_CHARP      Message
));

typedef void
(*SMC_ERR_CALLBACK) PROTOTYPE((
	              SMC_CONNECT_ID clientID,
                      SMC_SIZET      errNum,
                      SMC_SIZET      severity,
                      SMC_SIZET      mapSeverity,
                      SMC_SIZET      source,
                      SMC_CCHARP     errMsg,
                      SMC_SIZET      state
));


typedef struct SMC_CHARP_ARRAY_STRUCT {
  SMC_CHARPP   charpItems;
  SMC_INT      listLength;
  } SMC_CHARP_ARRAY_STRUCT;


typedef struct SMC_SIZET_ARRAY_STRUCT {
  SMC_SIZETP   sizetItems;
  SMC_INT      listLength;
  } SMC_SIZET_ARRAY_STRUCT;


typedef union SMC_VALUE_UNION {             /*  Value Data 	        */
  SMC_INT       intValue;                   /*   Int value              */
  SMC_LONG      longValue;                  /*   Long value             */
  SMC_DOUBLE    doubleValue;                /*   Double value           */
  SMC_SIZET     sizetValue;                 /*   size_t value           */
  SMC_CHARP     stringValue;                /*   String value           */
  SMC_VOIDP     voidpValue;                 /*   Void* value            */
  SMC_DATETIME  datetimeValue;              /*   Sybase datetime value  */
} SMC_VALUE_UNION;


typedef SMC_VALUE_UNION* SMC_VALUE_UNIONP;


typedef enum {				/* Property Actions           */
  SMC_PROP_ACT_SET=0,
  SMC_PROP_ACT_GET,
  SMC_PROP_ACT_CLEAR
} SMC_PROP_ACTION;


typedef enum {				/* Property Types             */
  SMC_PROP_APPNAME=1,
  SMC_PROP_ERROR_CALLBACK,
  SMC_PROP_IFILE,
  SMC_PROP_LOGIN_TIMEOUT,
  SMC_PROP_PACKETSIZE,

  SMC_PROP_PASSWORD,
  SMC_PROP_SERVERMODE,
  SMC_PROP_SERVERNAME,
  SMC_PROP_TIMEOUT,
  SMC_PROP_USERDATA,

  SMC_PROP_USERNAME
} SMC_PROP_TYPE;


typedef enum {				/* Info Types                 */
  SMC_INFO_ALARM_ACTION_DATA=1,
  SMC_INFO_ALARM_ALARMID,
  SMC_INFO_ALARM_CURRENT_VALUE,
  SMC_INFO_ALARM_DATAITEM,
  SMC_INFO_ALARM_ROW,

  SMC_INFO_ALARM_THRESHOLD_VALUE,
  SMC_INFO_ALARM_TIMESTAMP,
  SMC_INFO_ALARM_VALUE_DATATYPE,
  SMC_INFO_ALARM_VIEWID,
  SMC_INFO_COMMAND_STATE,

  SMC_INFO_ERR_MAPSEVERITY,
  SMC_INFO_ERR_MSG,
  SMC_INFO_ERR_NUM,
  SMC_INFO_ERR_SEVERITY,
  SMC_INFO_ERR_SOURCE,

  SMC_INFO_ERR_STATE
} SMC_INFO_TYPE;


/*/////////////////////////////////////////////////////////////////////////////
 |
 |   SMC Preprocessor Defines
 |
 */

#define SMC_NULLTERM	(SMC_SIZET)(-1)
#define SMC_UNUSED	(SMC_SIZET)(-1)


/*/////////////////////////////////////////////////////////////////////////////
 |
 |   SMC DataItem DataTypes
 |
 */


#define NUM_DATAITEM_NAMES 153
typedef enum  {                                    /* DataItem Name Table    */
  SMC_NAME_NONE=0,
  SMC_NAME_SPID,                                   /* Key DataItems          */
  SMC_NAME_KPID,
  SMC_NAME_DATA_CACHE_ID,
  SMC_NAME_DB_ID,

  SMC_NAME_OBJ_ID,
  SMC_NAME_ACT_STP_DB_ID,
  SMC_NAME_ACT_STP_ID,
  SMC_NAME_STP_STMT_NUM,
  SMC_NAME_STP_LINE_NUM,

  SMC_NAME_LOCK_TYPE,
  SMC_NAME_LOCK_RESULT,
  SMC_NAME_LOCK_RESULT_SUMMARY,
  SMC_NAME_LOCK_STATUS,
  SMC_NAME_ENGINE_NUM,

  SMC_NAME_PAGE_NUM,
  SMC_NAME_DEV_NAME,
  SMC_NAME_PROC_STATE,
  SMC_NAME_APPLICATION_NAME,
  SMC_NAME_LOGIN_NAME,                            /* Result DataItems        */

  SMC_NAME_CUR_APP_NAME,
  SMC_NAME_DB_NAME,
  SMC_NAME_DATA_CACHE_NAME,
  SMC_NAME_OWNER_NAME,
  SMC_NAME_OBJ_NAME,

  SMC_NAME_OBJ_TYPE,
  SMC_NAME_ACT_STP_DB_NAME,
  SMC_NAME_ACT_STP_OWNER_NAME,
  SMC_NAME_ACT_STP_NAME,
  SMC_NAME_APP_EXECUTION_CLASS,

  SMC_NAME_BLOCKING_SPID,
  SMC_NAME_CONNECT_TIME,
  SMC_NAME_CPU_BUSY_PCT, 
  SMC_NAME_CPU_PCT, 
  SMC_NAME_CPU_TIME, 

  SMC_NAME_CPU_YIELD,
  SMC_NAME_CUR_ENGINE,
  SMC_NAME_CUR_EXECUTION_CLASS,
  SMC_NAME_CUR_PROC_STATE,
  SMC_NAME_CUR_STMT_ACT_STP_DB_ID,

  SMC_NAME_CUR_STMT_ACT_STP_DB_NAME,
  SMC_NAME_CUR_STMT_ACT_STP_ID,
  SMC_NAME_CUR_STMT_ACT_STP_NAME,
  SMC_NAME_CUR_STMT_ACT_STP_OWNER_NAME,
  SMC_NAME_CUR_STMT_ACT_STP_TEXT,

  SMC_NAME_CUR_STMT_BATCH_ID,
  SMC_NAME_CUR_STMT_BATCH_TEXT,
  SMC_NAME_CUR_STMT_BATCH_TEXT_ENABLED,
  SMC_NAME_CUR_STMT_CONTEXT_ID,
  SMC_NAME_CUR_STMT_CPU_TIME,

  SMC_NAME_CUR_STMT_ELAPSED_TIME,
  SMC_NAME_CUR_STMT_LINE_NUM,
  SMC_NAME_CUR_STMT_LOCKS_GRANTED_IMMED,
  SMC_NAME_CUR_STMT_LOCKS_GRANTED_WAITED,
  SMC_NAME_CUR_STMT_LOCKS_NOT_GRANTED,

  SMC_NAME_CUR_STMT_NUM,
  SMC_NAME_CUR_STMT_PAGE_IO,
  SMC_NAME_CUR_STMT_PAGE_LOGICAL_READ,
  SMC_NAME_CUR_STMT_PAGE_PHYSICAL_READ,
  SMC_NAME_CUR_STMT_PAGE_WRITE,

  SMC_NAME_CUR_STMT_QUERY_PLAN_TEXT,
  SMC_NAME_CUR_STMT_START_TIME,
  SMC_NAME_CUR_STMT_TEXT_BYTE_OFFSET,
  SMC_NAME_DATA_CACHE_CONTENTION,
  SMC_NAME_DATA_CACHE_EFFICIENCY,

  SMC_NAME_DATA_CACHE_HIT,
  SMC_NAME_DATA_CACHE_HIT_PCT,
  SMC_NAME_DATA_CACHE_LARGE_IO_DENIED,
  SMC_NAME_DATA_CACHE_LARGE_IO_PERFORMED,
  SMC_NAME_DATA_CACHE_LARGE_IO_REQUESTED,

  SMC_NAME_DATA_CACHE_MISS,
  SMC_NAME_DATA_CACHE_PREFETCH_EFFICIENCY,
  SMC_NAME_DATA_CACHE_REF_AND_REUSE,
  SMC_NAME_DATA_CACHE_REUSE,
  SMC_NAME_DATA_CACHE_REUSE_DIRTY,

  SMC_NAME_DATA_CACHE_SIZE,
  SMC_NAME_DEADLOCK_CNT, 
  SMC_NAME_DEMAND_LOCK, 
  SMC_NAME_DEV_HIT,
  SMC_NAME_DEV_HIT_PCT,

  SMC_NAME_DEV_IO, 
  SMC_NAME_DEV_MISS,
  SMC_NAME_DEV_READ,
  SMC_NAME_DEV_WRITE,
  SMC_NAME_HOST_NAME,

  SMC_NAME_LOCK_CONTENTION_PCT,
  SMC_NAME_LOCK_CNT, 
  SMC_NAME_LOCK_HIT_PCT,
  SMC_NAME_LOCK_STATUS_CNT,
  SMC_NAME_LOCK_WAIT_TIME,

  SMC_NAME_LOCKS_BEING_BLOCKED_CNT,
  SMC_NAME_LOCKS_GRANTED_IMMED,
  SMC_NAME_LOCKS_GRANTED_WAITED,
  SMC_NAME_LOCKS_NOT_GRANTED,
  SMC_NAME_LOG_CONTENTION_PCT,

  SMC_NAME_MEM_CODE_SIZE, 
  SMC_NAME_MEM_KERNEL_STRUCT_SIZE, 
  SMC_NAME_MEM_PAGE_CACHE_SIZE, 
  SMC_NAME_MEM_PROC_BUFFER, 
  SMC_NAME_MEM_PROC_HEADER,

  SMC_NAME_MEM_SERVER_STRUCT_SIZE, 
  SMC_NAME_MOST_ACT_DEV_IO,
  SMC_NAME_MOST_ACT_DEV_NAME,
  SMC_NAME_NET_BYTE_IO, 
  SMC_NAME_NET_BYTES_RCVD, 

  SMC_NAME_NET_BYTES_SENT, 
  SMC_NAME_NET_DEFAULT_PKT_SIZE, 
  SMC_NAME_NET_MAX_PKT_SIZE, 
  SMC_NAME_NET_PKT_SIZE_RCVD, 
  SMC_NAME_NET_PKT_SIZE_SENT, 

  SMC_NAME_NET_PKTS_RCVD, 
  SMC_NAME_NET_PKTS_SENT, 
  SMC_NAME_NUM_ENGINES,
  SMC_NAME_NUM_PROCESSES,
  SMC_NAME_PAGE_HIT_PCT, 

  SMC_NAME_PAGE_INDEX_LOGICAL_READ,
  SMC_NAME_PAGE_INDEX_PHYSICAL_READ,
  SMC_NAME_PAGE_LOGICAL_READ,
  SMC_NAME_PAGE_IO,
  SMC_NAME_PAGE_PHYSICAL_READ, 

  SMC_NAME_PAGE_WRITE, 
  SMC_NAME_PROC_STATE_CNT, 
  SMC_NAME_TIMESTAMP, 
  SMC_NAME_TIMESTAMP_DATIM, 
  SMC_NAME_ELAPSED_TIME,

  SMC_NAME_SQL_SERVER_NAME,
  SMC_NAME_SQL_SERVER_VERSION,
  SMC_NAME_STP_CPU_TIME,
  SMC_NAME_STP_ELAPSED_TIME,
  SMC_NAME_STP_EXECUTION_CLASS,

  SMC_NAME_STP_HIT_PCT,
  SMC_NAME_STP_LINE_TEXT, 
  SMC_NAME_STP_NUM_TIMES_EXECUTED,
  SMC_NAME_STP_LOGICAL_READ,
  SMC_NAME_STP_PHYSICAL_READ,

  SMC_NAME_THREAD_EXCEEDED_MAX,
  SMC_NAME_THREAD_EXCEEDED_MAX_PCT,
  SMC_NAME_THREAD_MAX_USED,
  SMC_NAME_TIME_WAITED_ON_LOCK, 
  SMC_NAME_XACT, 

  SMC_NAME_XACT_DELETE, 
  SMC_NAME_XACT_DELETE_DEFERRED,
  SMC_NAME_XACT_DELETE_DIRECT,
  SMC_NAME_XACT_INSERT, 
  SMC_NAME_XACT_INSERT_CLUSTERED, 

  SMC_NAME_XACT_INSERT_HEAP, 
  SMC_NAME_XACT_SELECT,
  SMC_NAME_XACT_UPDATE, 
  SMC_NAME_XACT_UPDATE_DEFERRED, 
  SMC_NAME_XACT_UPDATE_DIRECT,

  SMC_NAME_XACT_UPDATE_EXPENSIVE,
  SMC_NAME_XACT_UPDATE_IN_PLACE, 
  SMC_NAME_XACT_UPDATE_NOT_IN_PLACE
} SMC_DATAITEM_NAME;



typedef  SMC_DATAITEM_NAME*   SMC_DATAITEM_NAMEP;


typedef enum SMC_DATAITEM_TYPE {
  SMC_DI_TYPE_NONE=0,
  SMC_DI_TYPE_CHARP,
  SMC_DI_TYPE_DATIM,
  SMC_DI_TYPE_DOUBLE,
  SMC_DI_TYPE_ENUMS,
  SMC_DI_TYPE_INT,
  SMC_DI_TYPE_LONG
} SMC_DATAITEM_TYPE;


typedef  SMC_DATAITEM_TYPE*  SMC_DATAITEM_TYPEP;


#define NUM_DATAITEM_STATS 7
typedef enum {                                 /* DataItem StatType Table    */
  SMC_STAT_NONE=0,
  SMC_STAT_VALUE_SAMPLE,
  SMC_STAT_VALUE_SESSION,
  SMC_STAT_RATE_SAMPLE,
  SMC_STAT_RATE_SESSION,
  SMC_STAT_AVG_SAMPLE,
  SMC_STAT_AVG_SESSION
} SMC_DATAITEM_STATTYPE;


typedef struct SMC_DATAITEM_STRUCT {      
  SMC_DATAITEM_NAME       dataItemName;        /* Name and StatType uniquely */
  SMC_DATAITEM_STATTYPE   dataItemStatType;    /*    define a DataItem       */
  } SMC_DATAITEM_STRUCT;


typedef SMC_DATAITEM_STRUCT*   SMC_DATAITEM_STRUCTP;


typedef enum                                             /* Error sources */
{
  SMC_SRC_UNKNOWN=0,
  SMC_SRC_HS,
  SMC_SRC_SMC,
  SMC_SRC_CT,
  SMC_SRC_SS,
  SMC_SRC_SMS,
  SMC_SRC_DDE
} SMC_SOURCE;


typedef enum {						/* Error severities */
  SMC_ERR_SEV_INFO=1,
  SMC_ERR_SEV_WARN,
  SMC_ERR_SEV_FATAL
} SMC_ERR_SEVERITY;


typedef enum {						/* Cancel Types */
  SMC_CANCEL_PENDING=1
} SMC_CANCEL_TYPE;


typedef enum {
  SMC_CLOSE_REQUEST=1
} SMC_CLOSE_TYPE;


typedef enum {						/* Command States */
  SMC_COMMAND_STATE_PENDING=0,
  SMC_COMMAND_STATE_IN_PROGRESS,
  SMC_COMMAND_STATE_DONE
} SMC_COMMAND_STATE;


typedef SMC_COMMAND_STATE*     SMC_COMMAND_STATEP;


typedef enum {						/* Connection States */
  SMC_CONNECT_STATE_AVAILABLE=1,
  SMC_CONNECT_STATE_BUSY,
  SMC_CONNECT_STATE_ERROR
} SMC_CONNECT_STATE;


typedef SMC_CONNECT_STATE*     SMC_CONNECT_STATEP;


#define NUM_LOCK_RESS 7
#define NUM_LOCK_RESS_PRE119 6		/* Number of result types for pre-11.9 servers */
typedef enum {                                          /* Lock Result Table */
  SMC_LOCK_R_GRANTED=1,
  SMC_LOCK_R_NOTNEEDED,
  SMC_LOCK_R_WAITED,
  SMC_LOCK_R_DIDNTWAIT,
  SMC_LOCK_R_DEADLOCK,
  SMC_LOCK_R_INTERRUPTED,
  SMC_LOCK_R_TIMEDOUT
} SMC_LOCK_RESULT;


#define NUM_LOCK_RESSUMS 2
typedef enum {                                 /* Lock Result Summary Table  */
  SMC_LOCK_RS_GRANTED=1,
  SMC_LOCK_RS_NOTGRANTED
} SMC_LOCK_RESULT_SUMMARY;


#define NUM_LOCK_STATUS 4
typedef enum {                                          /* Lock Status Table */
  SMC_LOCK_S_HELD_BLOCKING=1,
  SMC_LOCK_S_HELD_NOTBLOCKING,
  SMC_LOCK_S_REQUESTED_BLOCKED,
  SMC_LOCK_S_REQUESTED_NOTBLOCKED
} SMC_LOCK_STATUS;
 

#define NUM_LOCK_TYPES 11
#define NUM_LOCK_TYPES_PRE119 7		/* Number of lock types for pre-11.9 servers */
typedef enum {                                            /* Lock Type Table */
  SMC_LOCK_T_EX_TAB=1,
  SMC_LOCK_T_SH_TAB,
  SMC_LOCK_T_EX_INT,
  SMC_LOCK_T_SH_INT,
  SMC_LOCK_T_EX_PAGE,
  SMC_LOCK_T_SH_PAGE,
  SMC_LOCK_T_UP_PAGE,
  SMC_LOCK_T_EX_ROW,
  SMC_LOCK_T_SH_ROW,
  SMC_LOCK_T_UP_ROW,
  SMC_LOCK_T_SH_NKL
} SMC_LOCK_TYPE;


#define NUM_OBJ_TYPES 3
typedef enum {                                          /* Object Type Table */
  SMC_OBJ_T_NONE=0,
  SMC_OBJ_T_STP,
  SMC_OBJ_T_TBL
} SMC_OBJ_TYPE;


#define NUM_PROC_STATES 16
typedef enum {                                     /*  Process States Table */
  SMC_PROC_STATE_NONE=0,        /*  4.9.2 or later */
  SMC_PROC_STATE_ALARM_SLEEP,   /* 10.0.1 or later */
  SMC_PROC_STATE_BACKGROUND,    /* 10.0.1 or later */
  SMC_PROC_STATE_BAD_STATUS,    /* 10.0.1 or later */
  SMC_PROC_STATE_INFECTED,      /*  4.9.2 or later */
  SMC_PROC_STATE_LOCK_SLEEP,    /* 10.0.1 or later */
  SMC_PROC_STATE_RECV_SLEEP,    /* 10.0.1 or later */
  SMC_PROC_STATE_RUNNABLE,      /*  4.9.2 or later */
  SMC_PROC_STATE_RUNNING,       /*  4.9.2 or later */
  SMC_PROC_STATE_SEND_SLEEP,    /* 10.0.1 or later */
  SMC_PROC_STATE_SLEEPING,      /*  4.9.2 or later */
  SMC_PROC_STATE_STOPPED,       /* 10.0.1 or later */
  SMC_PROC_STATE_TERMINATING,   /*  4.9.2 */
  SMC_PROC_STATE_YIELDING,      /*  4.9.2 */
  SMC_PROC_STATE_REMOTE_IO,	/*   11.5 or later */
  SMC_PROC_STATE_SYNC_SLEEP	/*   11.5 or later */
} SMC_PROCESS_STATE;


/*/////////////////////////////////////////////////////////////////////////////
 |
 |   SMC Alarm DataTypes
 |
 */
typedef enum {                                   /* Alarm Action Type Table  */
  SMC_ALARM_A_EXEC_PROC=1,                       /*                          */
  SMC_ALARM_A_LOG_TO_FILE,                       /*                          */
  SMC_ALARM_A_NOTIFY			         /* call callback func	     */
} SMC_ALARM_ACTION_TYPE;


typedef struct SMC_ALARM_ROW_ID
{
    SMC_DATAITEM_STRUCT		dataItem;
    SMC_CHARP			dataItemNameText;
    SMC_DATAITEM_TYPE		dataItemType;
    SMC_VALUE_UNION		currentValue;
} SMC_ALARM_ROW_ID; 


typedef struct SMC_ALARM_ROW_ID* SMC_ALARM_ROW_IDP;


typedef void
(*SMC_ALARM_CALLBACK) PROTOTYPE((
    SMC_CONNECT_ID		clientId,
    SMC_VIEW_ID			viewId,
    SMC_ALARM_ID		alarmId,
    SMC_VOIDP			userDataHandle,
    SMC_CHARP			alarmActionData,
    SMC_CHARP			timestamp,
    SMC_DATAITEM_STRUCTP        dataItem,
    SMC_CHARP			dataItemNameText,
    SMC_CHARP			dataItemStatTypeText,
    SMC_DATAITEM_TYPE		dataItemType,
    SMC_VALUE_UNIONP		currentValue,
    SMC_VALUE_UNIONP		thresholdValue,
    SMC_CHARP			serverName,
    SMC_INT			numRowIds,
    SMC_ALARM_ROW_IDP		rowIdArray
));


/*/////////////////////////////////////////////////////////////////////////////
 |
 |   SMC Filter DataTypes
 |
 */
typedef enum {                                   /* Filter Type Table        */
  SMC_FILT_T_EQ=1,                               /*   Equality               */
  SMC_FILT_T_NEQ,                                /*   Not Equality           */
  SMC_FILT_T_GE,                                 /*   Range, values >= lb    */
  SMC_FILT_T_LE,                                 /*   Range, values <= ub    */
  SMC_FILT_T_GE_AND_LE,                          /*   Range, lb <= val <= ub */
  SMC_FILT_T_TOP_N                               /*   Top N values           */
} SMC_FILTER_TYPE;


typedef struct SMC_FILTER_STRUCT {          /* Complete filter specification */
  SMC_FILTER_TYPE           filterType;
  SMC_VALUE_UNIONP	    filterValueListHandle;
  SMC_SIZET                 filterValueListLength;
  SMC_DATAITEM_TYPE         filterDatatype;
  SMC_FILTER_ID             filterId;
} SMC_FILTER_STRUCT;


/*/////////////////////////////////////////////////////////////////////////////
 |
 |   SMC API Function Return Codes
 |   Note: These correspond to error numbers.
 |   Note also: This enum type must be kept in synch with the "text"
 |   array in cerr.cpp, which supplies the corresponding error text
 |   for each error.
 */
typedef enum {                                               /* Return Codes */
  SMC_RET_SUCCESS=0,
  SMC_RET_FAILURE,
  SMC_RET_FAILED_NEW,                  /* memory errors */
  SMC_RET_CONNECTION_ERROR,            /* connect errors */
  SMC_RET_UNABLE_TO_CONNECT_TO_SMS,

  SMC_RET_UNABLE_TO_CONNECT_TO_SS,
  SMC_RET_MISSING_RESULT_TABLE,
  SMC_RET_INVALID_USER_PASSWD,
  SMC_RET_INVALID_PARAMETER,           /* parameter errors */
  SMC_RET_INVALID_CACHE,

  SMC_RET_INVALID_DCID,
  SMC_RET_INVALID_COMMAND,
  SMC_RET_INVALID_VIEWID,
  SMC_RET_INVALID_DINAME,
  SMC_RET_INVALID_DISTAT,

  SMC_RET_INVALID_DI_STRUCT,
  SMC_RET_DI_STAT_MISMATCH,
  SMC_RET_INVALID_DI_COMBO,
  SMC_RET_INVALID_DATATYPE,
  SMC_RET_INVALID_VALUE_COUNT,

  SMC_RET_INVALID_FILTER_VALUE,
  SMC_RET_INVALID_FILTER_RANGE,
  SMC_RET_DATAITEM_CONTAINS_FILTER,
  SMC_RET_INVALID_COMPOSITE_FILTER,
  SMC_RET_INVALID_SVR_MODE,

  SMC_RET_MISSING_DATAITEM,
  SMC_RET_INVALID_FILTERID,
  SMC_RET_INVALID_ALARMID,
  SMC_RET_INVALID_ALARM_VALUE,
  SMC_RET_INVALID_DINAME_FOR_ALARM,

  SMC_RET_INVALID_API_FUNC_SEQUENCE,
  SMC_RET_INVALID_API_FUNCTION,
  SMC_RET_INVALID_PROPERTY,
  SMC_RET_INVALID_INFOTYPE,
  SMC_RET_CONNECT_NOT_CLOSED,

  SMC_RET_ARITHMETIC_OVERFLOW,
  SMC_RET_LOGIN_LACKS_SA_ROLE,
  SMC_RET_INTERNAL_ERROR               /* internal error */

} SMC_RETURN_CODE;


/*/////////////////////////////////////////////////////////////////////////////
 |
 |   SMC API Renamed Function Return Codes
 |
 */

#define SMC_RET_INSUFFICIENT_MEMORY          SMC_RET_FAILED_NEW
#define SMC_RET_INVALID_CONNECT              SMC_RET_INVALID_DCID
#define SMC_RET_INVALID_DATAITEM_FOR_ALARM   SMC_RET_INVALID_DINAME_FOR_ALARM


typedef enum {                                          /* Server Mode Table */
  SMC_SERVER_M_NONE=0,
  SMC_SERVER_M_LIVE,
  SMC_SERVER_M_HISTORICAL
} SMC_SERVER_MODE; 


/*
 | SQL Monitor Historical Server related enumeration types and structures
 */

/* Filters as known to the SQL Monitor Historical Server                     */
typedef enum {
    SMC_HS_FILT_T_EQ=1,    /* Equal filter                               */
    SMC_HS_FILT_T_NEQ,     /* Not equal filter	                         */
    SMC_HS_FILT_T_RANGE,   /* Range filter                               */
    SMC_HS_FILT_T_TOP      /* Top-n filter                               */
} SMC_HS_FILTER_TYPE;    

/* Protection level for access of recorded data                              */
typedef enum {   
    SMC_HS_SESS_PROT_PRIVATE=1,      /* recorded data is password-protected  */
    SMC_HS_SESS_PROT_PUBLIC          /* unrestricted access to recorded data */
} SMC_HS_SESS_PROT_LEVEL;


/* Defines what to do with session on errors */
typedef enum {
    SMC_HS_SESS_ERR_CONT=1,   /* keep recording when non-fatal errors     */
                              /* are detected                             */
    SMC_HS_SESS_ERR_HALT      /* terminate recording session on non-fatal */
                              /* errors                                   */
} SMC_HS_SESS_ERR_OPT;


/* Defines the type of script (if any) created by the Historical Server
   to help the user to manipulate the data of a recording session */
typedef enum {
    SMC_HS_SESS_SCRIPT_SYBASE=0,/* script to create Sybase SQL Server tables */
    SMC_HS_SESS_SCRIPT_NONE     /* no script */
} SMC_HS_SESS_SCRIPT_OPT;

/* Defines treatment of a session's data and error files when an active      */
/* recording session is explicitly terminated                                */
typedef enum { 
    SMC_HS_DELETE_FILES=0,	/* delete the files			*/
    SMC_HS_RETAIN_FILES		/* keep the files			*/
} SMC_HS_SESS_DELETE_OPT;    

/* Types of playback */
typedef enum
{
    SMC_HS_PBTYPE_ENTIRE=0,	/* playback is summarized, with one playback */					/* sample for the entire session	     */
    SMC_HS_PBTYPE_ACTUAL,	/* playback samples correspond to input	     */
				/* samples, but are re-normalized	     */
    SMC_HS_PBTYPE_INTERVAL,	/* playback is summarized over explicit,     */
				/* uniform, user-supplied playback intervals */
    SMC_HS_PBTYPE_RAW		/* playback samples correspond exactly to    */
				/* input samples			     */
} SMC_HS_PLAYBACK_OPT;

/* Defines whether estimation is allowed during playback */
typedef enum
{
    SMC_HS_ESTIM_ALLOW=0,	/* estimation is allowed	*/
    SMC_HS_ESTIM_DISALLOW	/* estimation is not allowed	*/
} SMC_HS_ESTIM_OPT;

/* Defines treatment of missing data during playback */
typedef enum
{
    SMC_HS_MISSDATA_SKIP=0,	/* playback skips over samples with no data */
    SMC_HS_MISSDATA_SHOW	/* samples are played back even if there is */
				/* no data for the sample interval	    */
} SMC_HS_MISSDATA_OPT;

/* Defines whether playback is sent to client or written to a new session */
typedef enum
{
    SMC_HS_TARGET_CLIENT=0,	/* send playback to client		*/
    SMC_HS_TARGET_FILE		/* create new session from playback	*/
} SMC_HS_TARGET_OPT;


#endif   /*   __MCTYPES_H   */
/*---------------------------------------------------------------------------*/
