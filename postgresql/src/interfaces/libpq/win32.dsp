# Microsoft Developer Studio Project File - Name="libpq" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libpq - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libpq.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libpq.mak" CFG="libpq - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libpq - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libpq - x64 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libpq - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libpq - x64 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libpq - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP BASE Intermediate_Dir "$(PlatformName)\$(ConfigurationName)\objs"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP Intermediate_Dir "$(PlatformName)\$(ConfigurationName)\objs"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /ZI /W3 /Od /D "FRONTEND" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_LIB" /D "_MBCS" /Gm /D "HAVE_VSNPRINTF" /D "HAVE_STRDUP" /D "HAVE_PG_CONFIG_H" /D "PGSQL_EXPORTS" /D "HAVE_PQSETNONBLOCKING" /D "HAVE_PQCMDTUPLES" /D "HAVE_PQCLIENTENCODING" /D "HAVE_PQESCAPE" /D "HAVE_PQPARAMETERSTATUS" /D "HAVE_PGTRANSACTIONSTATUS" /D "HAVE_PQEXECPARAMS" /D "HAVE_PQPREPARE" /D "HAVE_PQEXECPREPARED" /D "HAVE_PQRESULTERRORFIELD" /D "HAVE_PQSENDQUERYPARAMS" /D "HAVE_PQSENDPREPARE" /D "HAVE_PQSENDQUERYPREPARED" /D "HAVE_PQPUTCOPYDATA" /D "HAVE_PQPUTCOPYEND" /D "HAVE_PQGETCOPYDATA" /D "HAVE_PQSETERRORVERBOSITY" /D "HAVE_PQUNESCAPEBYTEA" /D "HAVE_PQFTABLE" /D "HAVE_PQESCAPE_CONN" /D "HAVE_PQESCAPE_BYTEA_CONN" /D "HAVE_PQFREEMEM" /D "HAVE_PGSQL_WITH_MULTIBYTE_SUPPORT" /D "HAVE_PQPROTOCOLVERSION" /D "HAVE_PG_LO_CREATE" /D "HAVE_PG_LO_IMPORT_WITH_OID" /D "HAVE_PG_LO_TRUNCATE" /D "HAVE_PG_LO64" /D "HAVE_PQESCAPELITERAL" /Fp"$(IntDir)/libpq.pch" /YX /Fo"$(IntDir)/" /Fd"$(IntDir)/" /GZ /FD /c /D_CRT_SECURE_NO_WARNINGS /GX  
# ADD CPP /nologo /MDd /ZI /W3 /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "_MBCS" /Gm /D "HAVE_VSNPRINTF" /D "HAVE_STRDUP" /D "HAVE_PG_CONFIG_H" /D "PGSQL_EXPORTS" /D "HAVE_PQSETNONBLOCKING" /D "HAVE_PQCMDTUPLES" /D "HAVE_PQCLIENTENCODING" /D "HAVE_PQESCAPE" /D "HAVE_PQPARAMETERSTATUS" /D "HAVE_PGTRANSACTIONSTATUS" /D "HAVE_PQEXECPARAMS" /D "HAVE_PQPREPARE" /D "HAVE_PQEXECPREPARED" /D "HAVE_PQRESULTERRORFIELD" /D "HAVE_PQSENDQUERYPARAMS" /D "HAVE_PQSENDPREPARE" /D "HAVE_PQSENDQUERYPREPARED" /D "HAVE_PQPUTCOPYDATA" /D "HAVE_PQPUTCOPYEND" /D "HAVE_PQGETCOPYDATA" /D "HAVE_PQSETERRORVERBOSITY" /D "HAVE_PQUNESCAPEBYTEA" /D "HAVE_PQFTABLE" /D "HAVE_PQESCAPE_CONN" /D "HAVE_PQESCAPE_BYTEA_CONN" /D "HAVE_PQFREEMEM" /D "HAVE_PGSQL_WITH_MULTIBYTE_SUPPORT" /D "HAVE_PQPROTOCOLVERSION" /D "HAVE_PG_LO_CREATE" /D "HAVE_PG_LO_IMPORT_WITH_OID" /D "HAVE_PG_LO_TRUNCATE" /D "HAVE_PG_LO64" /D "HAVE_PQESCAPELITERAL" /Fp"$(IntDir)/libpq.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /GZ /c /D_CRT_SECURE_NO_WARNINGS /GX
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 2057 /d "_DEBUG" 
# ADD RSC /l 2057 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\Debug\libpq.bsc" 
# ADD BSC32 /nologo /o ".\Debug\libpq.bsc" 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\libpq_a_debug.lib" 
# ADD LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\libpq_a_debug.lib" 

!ELSEIF  "$(CFG)" == "libpq - x64 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP BASE Intermediate_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP Intermediate_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /Zi /W3 /Od /D "FRONTEND" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_LIB" /D "_MBCS" /Gm /D "HAVE_VSNPRINTF" /D "HAVE_STRDUP" /D "HAVE_PG_CONFIG_H" /D "PGSQL_EXPORTS" /D "HAVE_PQSETNONBLOCKING" /D "HAVE_PQCMDTUPLES" /D "HAVE_PQCLIENTENCODING" /D "HAVE_PQESCAPE" /D "HAVE_PQPARAMETERSTATUS" /D "HAVE_PGTRANSACTIONSTATUS" /D "HAVE_PQEXECPARAMS" /D "HAVE_PQPREPARE" /D "HAVE_PQEXECPREPARED" /D "HAVE_PQRESULTERRORFIELD" /D "HAVE_PQSENDQUERYPARAMS" /D "HAVE_PQSENDPREPARE" /D "HAVE_PQSENDQUERYPREPARED" /D "HAVE_PQPUTCOPYDATA" /D "HAVE_PQPUTCOPYEND" /D "HAVE_PQGETCOPYDATA" /D "HAVE_PQSETERRORVERBOSITY" /D "HAVE_PQUNESCAPEBYTEA" /D "HAVE_PQFTABLE" /D "HAVE_PQESCAPE_CONN" /D "HAVE_PQESCAPE_BYTEA_CONN" /D "HAVE_PQFREEMEM" /D "HAVE_PGSQL_WITH_MULTIBYTE_SUPPORT" /D "HAVE_PQPROTOCOLVERSION" /D "HAVE_PG_LO_CREATE" /D "HAVE_PG_LO_IMPORT_WITH_OID" /D "HAVE_PG_LO_TRUNCATE" /D "HAVE_PG_LO64" /D "HAVE_PQESCAPELITERAL" /Fp"$(IntDir)/libpq.pch" /YX /Fo"$(IntDir)/" /Fd"$(IntDir)/" /GZ /FD /c /D_CRT_SECURE_NO_WARNINGS /GX 
# ADD CPP /nologo /MDd /Zi /W3 /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "_MBCS" /Gm /D "HAVE_VSNPRINTF" /D "HAVE_STRDUP" /D "HAVE_PG_CONFIG_H" /D "PGSQL_EXPORTS" /D "HAVE_PQSETNONBLOCKING" /D "HAVE_PQCMDTUPLES" /D "HAVE_PQCLIENTENCODING" /D "HAVE_PQESCAPE" /D "HAVE_PQPARAMETERSTATUS" /D "HAVE_PGTRANSACTIONSTATUS" /D "HAVE_PQEXECPARAMS" /D "HAVE_PQPREPARE" /D "HAVE_PQEXECPREPARED" /D "HAVE_PQRESULTERRORFIELD" /D "HAVE_PQSENDQUERYPARAMS" /D "HAVE_PQSENDPREPARE" /D "HAVE_PQSENDQUERYPREPARED" /D "HAVE_PQPUTCOPYDATA" /D "HAVE_PQPUTCOPYEND" /D "HAVE_PQGETCOPYDATA" /D "HAVE_PQSETERRORVERBOSITY" /D "HAVE_PQUNESCAPEBYTEA" /D "HAVE_PQFTABLE" /D "HAVE_PQESCAPE_CONN" /D "HAVE_PQESCAPE_BYTEA_CONN" /D "HAVE_PQFREEMEM" /D "HAVE_PGSQL_WITH_MULTIBYTE_SUPPORT" /D "HAVE_PQPROTOCOLVERSION" /D "HAVE_PG_LO_CREATE" /D "HAVE_PG_LO_IMPORT_WITH_OID" /D "HAVE_PG_LO_TRUNCATE" /D "HAVE_PG_LO64" /D "HAVE_PQESCAPELITERAL" /Fp"$(IntDir)/libpq.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /GZ /c /D_CRT_SECURE_NO_WARNINGS /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 2057 /d "_DEBUG" 
# ADD RSC /l 2057 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\Debug\libpq.bsc" 
# ADD BSC32 /nologo /o ".\Debug\libpq.bsc" 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\libpq_a_debug.lib" 
# ADD LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\libpq_a_debug.lib" 

!ELSEIF  "$(CFG)" == "libpq - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP BASE Intermediate_Dir "$(PlatformName)\$(ConfigurationName)\objs"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP Intermediate_Dir "$(PlatformName)\$(ConfigurationName)\objs"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /O2 /Ob1 /D "WIN32" /D "NDEBUG" /D "_LIB" /D "__USE_FILE_OFFSET64" /D "HAVE_READDIR_R" /D "_MBCS" /GF /Gy /D "HAVE_VSNPRINTF" /D "HAVE_STRDUP" /D "HAVE_PG_CONFIG_H" /D "PGSQL_EXPORTS" /D "HAVE_PQSETNONBLOCKING" /D "HAVE_PQCMDTUPLES" /D "HAVE_PQCLIENTENCODING" /D "HAVE_PQESCAPE" /D "HAVE_PQPARAMETERSTATUS" /D "HAVE_PGTRANSACTIONSTATUS" /D "HAVE_PQEXECPARAMS" /D "HAVE_PQPREPARE" /D "HAVE_PQEXECPREPARED" /D "HAVE_PQRESULTERRORFIELD" /D "HAVE_PQSENDQUERYPARAMS" /D "HAVE_PQSENDPREPARE" /D "HAVE_PQSENDQUERYPREPARED" /D "HAVE_PQPUTCOPYDATA" /D "HAVE_PQPUTCOPYEND" /D "HAVE_PQGETCOPYDATA" /D "HAVE_PQSETERRORVERBOSITY" /D "HAVE_PQUNESCAPEBYTEA" /D "HAVE_PQFTABLE" /D "HAVE_PQESCAPE_CONN" /D "HAVE_PQESCAPE_BYTEA_CONN" /D "HAVE_PQFREEMEM" /D "HAVE_PGSQL_WITH_MULTIBYTE_SUPPORT" /D "HAVE_PQPROTOCOLVERSION" /D "HAVE_PG_LO_CREATE" /D "HAVE_PG_LO_IMPORT_WITH_OID" /D "HAVE_PG_LO_TRUNCATE" /D "HAVE_PG_LO64" /D "HAVE_PQESCAPELITERAL" /Fp"$(IntDir)/libpq.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /c /D_CRT_SECURE_NO_WARNINGS /GX 
# ADD CPP /nologo /MD /W3 /O2 /Ob1 /D "WIN32" /D "NDEBUG" /D "_LIB" /D "__USE_FILE_OFFSET64" /D "HAVE_READDIR_R" /D "_MBCS" /GF /Gy /D "HAVE_VSNPRINTF" /D "HAVE_STRDUP" /D "HAVE_PG_CONFIG_H" /D "PGSQL_EXPORTS" /D "HAVE_PQSETNONBLOCKING" /D "HAVE_PQCMDTUPLES" /D "HAVE_PQCLIENTENCODING" /D "HAVE_PQESCAPE" /D "HAVE_PQPARAMETERSTATUS" /D "HAVE_PGTRANSACTIONSTATUS" /D "HAVE_PQEXECPARAMS" /D "HAVE_PQPREPARE" /D "HAVE_PQEXECPREPARED" /D "HAVE_PQRESULTERRORFIELD" /D "HAVE_PQSENDQUERYPARAMS" /D "HAVE_PQSENDPREPARE" /D "HAVE_PQSENDQUERYPREPARED" /D "HAVE_PQPUTCOPYDATA" /D "HAVE_PQPUTCOPYEND" /D "HAVE_PQGETCOPYDATA" /D "HAVE_PQSETERRORVERBOSITY" /D "HAVE_PQUNESCAPEBYTEA" /D "HAVE_PQFTABLE" /D "HAVE_PQESCAPE_CONN" /D "HAVE_PQESCAPE_BYTEA_CONN" /D "HAVE_PQFREEMEM" /D "HAVE_PGSQL_WITH_MULTIBYTE_SUPPORT" /D "HAVE_PQPROTOCOLVERSION" /D "HAVE_PG_LO_CREATE" /D "HAVE_PG_LO_IMPORT_WITH_OID" /D "HAVE_PG_LO_TRUNCATE" /D "HAVE_PG_LO64" /D "HAVE_PQESCAPELITERAL" /Fp"$(IntDir)/libpq.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /c /D_CRT_SECURE_NO_WARNINGS /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 2057 /d "NDEBUG" 
# ADD RSC /l 2057 /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\Release\libpq.bsc" 
# ADD BSC32 /nologo /o ".\Release\libpq.bsc" 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\libpq_a.lib" 
# ADD LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\libpq_a.lib" 

!ELSEIF  "$(CFG)" == "libpq - x64 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP BASE Intermediate_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP Intermediate_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /O2 /Ob1 /D "WIN32" /D "NDEBUG" /D "_LIB" /D "_MBCS" /GF /Gy /D "HAVE_VSNPRINTF" /D "HAVE_STRDUP" /D "HAVE_PG_CONFIG_H" /D "PGSQL_EXPORTS" /D "HAVE_PQSETNONBLOCKING" /D "HAVE_PQCMDTUPLES" /D "HAVE_PQCLIENTENCODING" /D "HAVE_PQESCAPE" /D "HAVE_PQPARAMETERSTATUS" /D "HAVE_PGTRANSACTIONSTATUS" /D "HAVE_PQEXECPARAMS" /D "HAVE_PQPREPARE" /D "HAVE_PQEXECPREPARED" /D "HAVE_PQRESULTERRORFIELD" /D "HAVE_PQSENDQUERYPARAMS" /D "HAVE_PQSENDPREPARE" /D "HAVE_PQSENDQUERYPREPARED" /D "HAVE_PQPUTCOPYDATA" /D "HAVE_PQPUTCOPYEND" /D "HAVE_PQGETCOPYDATA" /D "HAVE_PQSETERRORVERBOSITY" /D "HAVE_PQUNESCAPEBYTEA" /D "HAVE_PQFTABLE" /D "HAVE_PQESCAPE_CONN" /D "HAVE_PQESCAPE_BYTEA_CONN" /D "HAVE_PQFREEMEM" /D "HAVE_PGSQL_WITH_MULTIBYTE_SUPPORT" /D "HAVE_PQPROTOCOLVERSION" /D "HAVE_PG_LO_CREATE" /D "HAVE_PG_LO_IMPORT_WITH_OID" /D "HAVE_PG_LO_TRUNCATE" /D "HAVE_PG_LO64" /D "HAVE_PQESCAPELITERAL" /Fp"$(IntDir)/libpq.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /c /D_CRT_SECURE_NO_WARNINGS /GX
# ADD CPP /nologo /MD /W3 /O2 /Ob1 /D "WIN32" /D "NDEBUG" /D "_LIB" /D "_MBCS" /GF /Gy /D "HAVE_VSNPRINTF" /D "HAVE_STRDUP" /D "HAVE_PG_CONFIG_H" /D "PGSQL_EXPORTS" /D "HAVE_PQSETNONBLOCKING" /D "HAVE_PQCMDTUPLES" /D "HAVE_PQCLIENTENCODING" /D "HAVE_PQESCAPE" /D "HAVE_PQPARAMETERSTATUS" /D "HAVE_PGTRANSACTIONSTATUS" /D "HAVE_PQEXECPARAMS" /D "HAVE_PQPREPARE" /D "HAVE_PQEXECPREPARED" /D "HAVE_PQRESULTERRORFIELD" /D "HAVE_PQSENDQUERYPARAMS" /D "HAVE_PQSENDPREPARE" /D "HAVE_PQSENDQUERYPREPARED" /D "HAVE_PQPUTCOPYDATA" /D "HAVE_PQPUTCOPYEND" /D "HAVE_PQGETCOPYDATA" /D "HAVE_PQSETERRORVERBOSITY" /D "HAVE_PQUNESCAPEBYTEA" /D "HAVE_PQFTABLE" /D "HAVE_PQESCAPE_CONN" /D "HAVE_PQESCAPE_BYTEA_CONN" /D "HAVE_PQFREEMEM" /D "HAVE_PGSQL_WITH_MULTIBYTE_SUPPORT" /D "HAVE_PQPROTOCOLVERSION" /D "HAVE_PG_LO_CREATE" /D "HAVE_PG_LO_IMPORT_WITH_OID" /D "HAVE_PG_LO_TRUNCATE" /D "HAVE_PG_LO64" /D "HAVE_PQESCAPELITERAL" /Fp"$(IntDir)/libpq.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /c /D_CRT_SECURE_NO_WARNINGS /GX
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 2057 /d "NDEBUG" 
# ADD RSC /l 2057 /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\Release\libpq.bsc" 
# ADD BSC32 /nologo /o ".\Release\libpq.bsc" 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\libpq_a.lib" 
# ADD LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\libpq_a.lib" 

!ENDIF

# Begin Target

# Name "libpq - Win32 Debug"
# Name "libpq - x64 Debug"
# Name "libpq - Win32 Release"
# Name "libpq - x64 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=fe-auth.c
# End Source File
# Begin Source File	
SOURCE=md5.c
	
# End Source File
# Begin Source File	
SOURCE=fe-auth.c
	
# End Source File
# Begin Source File	
SOURCE=fe-connect.c
	
# End Source File
# Begin Source File	
SOURCE=fe-exec.c
	
# End Source File
# Begin Source File	
SOURCE=fe-lobj.c
	
# End Source File
# Begin Source File	
SOURCE=fe-misc.c
	
# End Source File
# Begin Source File	
SOURCE=fe-print.c
	
# End Source File
# Begin Source File	
SOURCE=pqexpbuffer.c
	
# End Source File
# Begin Source File	
SOURCE=libpqdll.c
	
# End Source File
# Begin Source File	
SOURCE=wchar.c
	
# End Source File
# Begin Source File	
SOURCE=encnames.c

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=fe-auth.h
# End Source File
# Begin Source File
SOURCE=fe-connect.h

# End Source File
# Begin Source File
SOURCE=fe-exec.h

# End Source File
# Begin Source File
SOURCE=fe-lobj.h

# End Source File
# Begin Source File
SOURCE=fe-misc.h

# End Source File
# Begin Source File
SOURCE=fe-print.h

# End Source File
# Begin Source File
SOURCE=pqexpbuffer.h

# End Source File
# End Group
# End Target
# End Project

