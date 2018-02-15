#ifndef __MCPUBLIC_H
#define __MCPUBLIC_H 1


/*
 |------------------------------------------------------------------------------
 |          Sybase SQL Monitor
 |          Confidential Property of Sybase, Inc.
 |          (c) Copyright Sybase, Inc 1995,1997
 |          All rights reserved
*/


/*//////////////////////////////////////////////////////////////////////////////
 |
 |  supportive declarations
 |
 */

#include "mctypes.h"


/*
 |//////////////////////////////////////////////////////////////////////////////
 |//////////////////////////////////////////////////////////////////////////////
 |/////                                                                    /////
 |/////                                                                    /////
 |/////           F u n c t i o n   P r o t o t y p e s                    /////
 |/////                                                                    /////
 |//////////////////////////////////////////////////////////////////////////////
 |//////////////////////////////////////////////////////////////////////////////
 */


/*
** Declare all functions.
*/
MC_START_EXTERN_C


extern SMC_RETURN_CODE CS_PUBLIC
smc_async_refresh PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* identifies a client's connection   */
					/*                                    */
  SMC_SIZET		step,		/* relative position of the next      */
                                        /*   sample to be retrieved from the  */
                                        /*   Historical Server in playback    */
                                        /*   mode (when available)            */
  SMC_VOIDP		userDataHandle,	/* pointer to user-supplied data.     */
                                        /*                                    */
  SMC_GEN_CALLBACK	notifyCallback,	/* pointer to a notification callback */
					/*   function                         */
  SMC_GEN_CALLBACK	errCallback,	/* pointer to an error callback       */
					/*   function                         */
  SMC_COMMAND_IDP	commandIdHandle	/* returned value that identifies an  */
					/*   asynchronous command             */
  ));


extern SMC_RETURN_CODE CS_PUBLIC
smc_cancel PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* identifies a client's connection   */
                                        /*                                    */
  SMC_COMMAND_ID	commandId,	/* identifies an asynchronous command */
					/*                                    */
  SMC_CANCEL_TYPE	cancelType	/* type of cancel                     */
  ));


extern SMC_ERR_CALLBACK CS_PUBLIC
smc_change_error_handler PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* dataCenter for error handler       */
					/*		                      */
  SMC_ERR_CALLBACK	newErrHandler	/* error Handler function     	      */
  ));


extern SMC_RETURN_CODE CS_PUBLIC
smc_close PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* identifies a client's connection   */
					/*				      */
  SMC_CLOSE_TYPE	closeType	/* type of close		      */
  ));


extern SMC_RETURN_CODE CS_PUBLIC  
smc_connect PROTOTYPE ((
  SMC_SERVER_MODE	serverMode,	/* identifies type of server the      */
					/*   client will be connected to      */
  SMC_CHARP		serverName,	/* identifies a valid server name     */
					/*                                    */
  SMC_CHARP		userName,	/* identifies a valid user login      */
					/*                                    */
  SMC_CHARP		userPassword,	/* identifies a valid password for    */
					/*   the user login                   */
  SMC_CHARP		interfaceFile,	/* explicit pathname of interfaces    */
					/*   file 	    	    	      */
  SMC_ERR_CALLBACK	ErrCallback,	/* error callback function address    */
					/*                                    */
  SMC_SIZET		packetSize,	/* Sets connection packet size	      */
					/*   (0 ==> Sybase default)	      */
  SMC_SIZET		loginTimeout,	/* Sets login timeout for server      */
					/*   connections (0 ==> default)      */
  SMC_CONNECT_IDP	clientIdHandle	/* returned value that identifies a   */
					/*   client's connection              */
  ));


extern SMC_RETURN_CODE CS_PUBLIC
smc_connect_alloc PROTOTYPE ((
  SMC_GEN_CALLBACK      ErrCallback,    /* error callback function address    */
                                        /*                                    */
  SMC_CONNECT_IDP	clientIdHandle	/* returned value that identifies a   */
					/*   client's connection              */
  ));


extern SMC_RETURN_CODE CS_PUBLIC
smc_connect_drop PROTOTYPE ((
  SMC_CONNECT_ID	clientId	/* identifies a client's connection   */
  ));


extern SMC_RETURN_CODE CS_PUBLIC
smc_connect_ex PROTOTYPE ((
  SMC_CONNECT_ID	clientId	/* identifies a client's connection   */
  ));


extern SMC_RETURN_CODE CS_PUBLIC
smc_connect_props PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* identifies a client's connection   */
					/*                                    */
  SMC_PROP_ACTION	propertyAction,	/* [SMC_PROP_ACT_SET|SMC_PROP_ACT_GET|*/
					/*   SMC_PROP_ACT_CLEAR]              */
  SMC_PROP_TYPE		property,	/* symbolic name of property          */
					/*                                    */
  SMC_VALUE_UNIONP	propertyValue,	/* pointer to union which holds a     */
					/*   value for setting or getting     */
  SMC_SIZET		bufferLength,   /* the length of data in bytes of     */
					/*   *propertyValue                   */
  SMC_SIZETP		outputLengthHandle /* the length of *propertyValue    */
					/*    when getting a property         */
  ));


extern SMC_RETURN_CODE CS_PUBLIC  
smc_create_alarm PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* identifies a client's connection   */
					/*                                    */
  SMC_VIEW_ID           viewId,		/* identifies a client's view         */
                                      	/*                                    */
  SMC_DATAITEM_STRUCTP	dataItemHandle,	/* name and statType uniquely identify*/
					/*   a dataitem in a client's view.   */
  SMC_VALUE_UNIONP	alarmValueDataHandle,
					/* [int | long | float]               */
					/*                                    */
  SMC_DATAITEM_TYPE	alarmDatatype,	/* data type of alarmValueData        */
					/*                                    */
  SMC_ALARM_ACTION_TYPE	alarmActionType,/* [NOTIFY | EXEC_PROC | LOG_TO_FILE] */
					/*                                    */
  SMC_CHARP		alarmActionData,/* string to pass to callback function*/
					/*   or filename for log or program   */
  SMC_VOIDP		userDataHandle, /* pointer to user-supplied data.     */
  SMC_ALARM_CALLBACK	alarmCallback,  /* function to call to invoke the     */
					/*   alarm	    	    	      */
  SMC_ALARM_IDP		alarmId		/* id returned by this function       */
  ));


extern SMC_RETURN_CODE CS_PUBLIC
smc_create_alarm_ex PROTOTYPE ((
  SMC_CONNECT_ID	clientId,       /* identifies a client's connection   */
                                        /*                                    */
  SMC_VIEW_ID		viewId,         /* identifies a client's view         */
                                        /*                                    */
  SMC_DATAITEM_STRUCTP	dataItemHandle, /* name and statType uniquely identify*/
                                        /*   a dataitem in a client's view.   */
  SMC_VALUE_UNIONP	alarmValueDataHandle,
                                        /* [int | long | float]               */
                                        /*                                    */
  SMC_DATAITEM_TYPE	alarmDatatype,  /* data type of alarmValueData        */
                                        /*                                    */
  SMC_ALARM_ACTION_TYPE	alarmActionType,/* [NOTIFY | EXEC_PROC | LOG_TO_FILE] */
                                        /*                                    */
  SMC_CHARP		alarmActionData,/* string to pass to callback function*/
                                        /*   or filename for log or program   */
  SMC_VOIDP		userDataHandle, /* pointer to user-supplied data.     */
  SMC_GEN_CALLBACK	alarmCallback,  /* function to call to invoke the     */
                                        /*   alarm                            */
  SMC_ALARM_IDP		alarmId         /* id returned by this function       */
  ));


extern SMC_RETURN_CODE CS_PUBLIC  
smc_create_filter PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* identifies a client's connection   */
					/*                                    */
  SMC_VIEW_ID		viewId,		/* identifies a client's view         */
					/*                                    */
  SMC_DATAITEM_STRUCTP	dataItemHandle,	/* points to a name and statType which uniquely */
					/* identify a dataitem in a client's view    */
  SMC_FILTER_TYPE	filterType,     /* filter type                        */
					/*                                    */
  SMC_VALUE_UNIONP
			filterValueListHandle, 
					/* points to an array of filter	      */
					/*   values	    	    	      */
  SMC_SIZET             filterValueListLength, 
					/* the number of filter values        */
					/*                                    */
  SMC_DATAITEM_TYPE	filterDatatype,	/* datatype of the filter values      */
					/*                                    */
  SMC_FILTER_IDP	filterIdHandle  /* returned value that identifies the */
					/*   filter uniquely within the view  */
  ));


extern SMC_RETURN_CODE CS_PUBLIC  
smc_create_recording_session PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* identifies a client's connection   */
					/*                                    */
  SMC_CHARP		SMSName,	/* SQL Monitor Server Name    	      */
					/*                                    */
  SMC_INT		sampleInterval, /* time between samples    	      */
					/*                                    */
  SMC_CHARP		directoryName,  /* directory for session's files      */
					/*   home directory 	    	      */
  SMC_CHARP		startTime,	/* start time for session    	      */
					/*                                    */
  SMC_CHARP		endTime,	/* end time for session	    	      */
					/*                                    */
  SMC_HS_SESS_PROT_LEVEL	protectionLevel,/* session's protection level */
					/*                                    */
  SMC_HS_SESS_ERR_OPT	errOption,	/* error option	    	    	      */
					/*                                    */
  SMC_HS_SESS_SCRIPT_OPT	scriptType,	/* script type	    	      */
					/*                                    */
  SMC_SESSION_IDP	sessionIdHandle /* return value that identifies a     */
					/*   recording session	    	      */
  ));

extern SMC_RETURN_CODE CS_PUBLIC 
smc_create_playback_session PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* Identifies client's connection */
  SMC_SESSION_IDP	sessionIdArray,	/* Input sessions for playback */
  SMC_SIZET		numInputSessions, /* Number of input sessions */
  SMC_CHARP		startTime,	/* Start time for session */
  SMC_CHARP		endTime,	/* End time for session */
  SMC_HS_PLAYBACK_OPT	playbackType,	/* Whether to play back the original */
					/* data, renormalize, or summarize   */
					/* over different time intervals     */
  SMC_SIZET		summarizationInterval,
					/* Size of time intervals over which */
					/* to summarize data		     */
  SMC_HS_ESTIM_OPT	estimationOption,/* Whether certain data items may   */
					/* be estimated			     */
  SMC_HS_MISSDATA_OPT missingDataOption,/* Whether playback will include     */
					/* samples for which no data is	     */
					/* available from the input sessions */
  SMC_HS_TARGET_OPT	playbackTarget, /* Whether to send data to the client*/
					/* or to create a new session	     */
  SMC_CHARP		directoryName,	/* Where to create new session	     */
  SMC_HS_SESS_PROT_LEVEL protectionLevel,/* Session's protection level	     */
  SMC_HS_SESS_SCRIPT_OPT scriptType,	/* Type of script to generate	     */
  SMC_HS_SESS_DELETE_OPT deleteOption,	/* Specifies if files associated with */
					/* a session are to be deleted or    */
          				/* retained			     */
  SMC_SESSION_IDP	sessionIdHandle /* Return value that identifies a    */
					/* new session created from playback */
));

extern SMC_RETURN_CODE CS_PUBLIC  
smc_create_view PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* identifies a client's connection   */
					/*                                    */
  SMC_DATAITEM_STRUCTP	dataItemListHandle, 
					/* points to an array of dataitems    */
					/*   contained in a client's view     */
  SMC_SIZET		dataItemListLength,
					/* the number of dataitems contained  */
					/*   in a client's view               */
  SMC_CHARP		viewName,	/* view name used for recording       */
					/*                                    */
  SMC_VIEW_IDP		viewIdHandle	/* returned value that identifies a   */
					/*   client's view                    */
  ));


extern SMC_RETURN_CODE CS_PUBLIC  
smc_disconnect PROTOTYPE ((
  SMC_CONNECT_ID	clientId	/* identifies a client's connection   */
  ));


extern SMC_RETURN_CODE CS_PUBLIC  
smc_drop_alarm PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* identifies a client's connection   */
					/*                                    */
  SMC_VIEW_ID		viewId,         /* identifies a client's view         */
					/*                                    */
  SMC_ALARM_ID		alarmId		/* identifies the alarm to be dropped */
  ));


extern SMC_RETURN_CODE CS_PUBLIC  
smc_drop_filter PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* identifies a client's connection   */
					/*                                    */
  SMC_VIEW_ID		viewId,		/* identifies a client's view         */
					/*                                    */
  SMC_FILTER_ID		filterId        /* identifies the filter to be 	      */
					/*   dropped	    	    	      */
  ));


extern SMC_RETURN_CODE CS_PUBLIC  
smc_drop_view PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* identifies a client's connection   */
					/*                                    */
  SMC_VIEW_ID		viewId		/* identifies the view to be dropped  */
  ));


extern SMC_RETURN_CODE CS_PUBLIC
smc_get_command_info PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* identifies a client's connection   */
					/*                                    */
  SMC_COMMAND_ID	commandId,	/* identifies a callback context      */
					/*                                    */
  SMC_INFO_TYPE		infoType,	/* symbolic name of infoType          */
					/*                                    */
  SMC_VALUE_UNIONP	infoValue,	/* pointer to union which holds a     */
					/*   value you are getting            */
  SMC_SIZETP            outputLengthHandle /* the length of *propertyValue    */
					/*    when getting a property         */
  ));


extern SMC_RETURN_CODE CS_PUBLIC
smc_get_connection_state PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* identifies a client's connection   */
					/*                                    */
  SMC_CONNECT_STATEP	connectStateHandle
					/* Pointer to a variable declared as  */
					/*   SMC_CONNECT_STATE where a value  */
					/*   is written                       */
  ));


extern SMC_RETURN_CODE CS_PUBLIC  
smc_get_dataitem_value PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* identifies a client's connection   */
					/*                                    */
  SMC_VIEW_ID           viewId,		/* identifies a client's view         */
					/*                                    */
  SMC_DATAITEM_STRUCTP  dataItemHandle, /* identifies a dataitem contained    */
					/*   in a client's view               */
  SMC_SIZET             row,		/* identifies the row of interest     */
					/*                                    */
  SMC_VALUE_UNIONP	returnVal	/* return value that contains one     */
					/*   dataitem value                   */
  ));


extern SMC_RETURN_CODE CS_PUBLIC  
smc_get_dataitem_type PROTOTYPE ((
  SMC_DATAITEM_STRUCTP	dataItemHandle,	/* pointer to name and statType       */
					/*   which uniquely identify a dataitem              */
  SMC_DATAITEM_TYPEP    ptrType		/* pointer to the data type           */
  ));



extern SMC_RETURN_CODE CS_PUBLIC  
smc_get_row_count PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* identifies a client's connection   */
					/*                                    */
  SMC_VIEW_ID		viewId,		/* identifies a client's view         */
					/*                                    */
  SMC_SIZETP		rowCountHandle	/* returned value that contains the   */
					/*   number of rows of data 	      */
					/*   collected for the view during    */
					/*   the sample interval              */
  ));


extern SMC_RETURN_CODE CS_PUBLIC  
smc_get_version_string PROTOTYPE ((
  SMC_CHARPP            versionBuffer   /* buffer from version string         */
  ));


extern SMC_RETURN_CODE CS_PUBLIC  
smc_initiate_playback PROTOTYPE ((
  SMC_CONNECT_ID	clientId	/* identifies a client's connection   */
  ));


extern SMC_RETURN_CODE CS_PUBLIC  
smc_initiate_recording PROTOTYPE ((
  SMC_CONNECT_ID	clientId	/* identifies a client's connection   */
  ));


extern SMC_RETURN_CODE CS_PUBLIC  
smc_refresh PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* identifies a client's connection   */
					/*                                    */
  SMC_VOIDP		userDataHandle, /* pointer to user-supplied data      */
					/*                                    */
  SMC_CALLBACK		RefreshCallBack,/* pointer to a refresh CallBack      */
					/*  function                          */
					/*                                    */
  SMC_SIZET		step		/* relative position of the next      */
					/*   sample to be retrieved from the  */
					/*   Historical Server in playback    */
					/*   mode (when available)    	      */
  ));


extern SMC_RETURN_CODE CS_PUBLIC
smc_refresh_ex PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* identifies a client's connection   */
					/*                                    */
  SMC_SIZET		step		/* relative position of the next      */
					/*   sample to be retrieved from the  */
					/*   Historical Server in playback    */
					/*   mode (when available)            */
  ));


extern SMC_RETURN_CODE CS_PUBLIC  
smc_terminate_playback PROTOTYPE ((
  SMC_CONNECT_ID	clientId	/* identifies a client's connection   */
  ));


extern SMC_RETURN_CODE CS_PUBLIC  
smc_terminate_recording PROTOTYPE ((
  SMC_CONNECT_ID	clientId,	/* Identifies client's connection */
  SMC_SESSION_ID	sessionId,	/* Unique identifier for the session */
					/* to be terminated */
  SMC_HS_SESS_DELETE_OPT deleteOption	/* Specifies if files associated with */
					/* a session are to be deleted or */
          				/* retained */
  ));


MC_END_EXTERN_C


#endif   /*   __MCPUBLIC_H   */
/*--------------------------------------------------------------------------*/
