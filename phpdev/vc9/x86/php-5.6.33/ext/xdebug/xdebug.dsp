# Microsoft Developer Studio Project File - Name="xdebug" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=xdebug - Win32 Debug_TS
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "xdebug.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "xdebug.mak" CFG="xdebug - Win32 Debug_TS"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xdebug - Win32 Release_TS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xdebug - Win32 Debug_TS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "xdebug - Win32 Release_TS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_TS"
# PROP BASE Intermediate_Dir "Release_TS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_TS"
# PROP Intermediate_Dir "Release_TS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XDEBUG_EXPORTS" /D "MEMORY_LIMIT" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\.." /I "..\..\Zend" /I "..\..\TSRM" /I "..\..\main" /D "WIN32" /D "COMPILE_DL_XDEBUG" /D ZTS=1 /D HAVE_XDEBUG=1 /D ZEND_DEBUG=0 /D "NDEBUG" /D "_WINDOWS" /D "ZEND_WIN32" /D "PHP_WIN32" /D "HAVE_EXECUTE_DATA_PTR" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 php4ts.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /machine:I386 /out:"Release_TS/php_xdebug.dll" /libpath:"..\..\Release_TS" /libpath:"..\..\Release_TS_Inline" /libpath:"..\php4\Release_TS"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "xdebug - Win32 Debug_TS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_TS"
# PROP BASE Intermediate_Dir "Debug_TS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_TS"
# PROP Intermediate_Dir "Debug_TS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XDEBUG_EXPORTS" /D "MEMORY_LIMIT" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\..\Zend" /I "..\..\TSRM" /I "..\..\main" /D ZEND_DEBUG=1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "COMPILE_DL_XDEBUG" /D ZTS=1 /D "ZEND_WIN32" /D "PHP_WIN32" /D HAVE_XDEBUG=1 /D "HAVE_EXECUTE_DATA_PTR" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 php4ts_debug.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /debug /machine:I386 /out:"Debug_TS/php_xdebug.dll" /pdbtype:sept /libpath:"..\..\Debug_TS"

!ENDIF 

# Begin Target

# Name "xdebug - Win32 Release_TS"
# Name "xdebug - Win32 Debug_TS"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File
SOURCE=.\usefulstuff.c
# End Source File
# Begin Source File
SOURCE=.\xdebug.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_branch_info.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_code_coverage.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_com.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_compat.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_handler_dbgp.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_handlers.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_llist.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_monitor.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_hash.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_private.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_profiler.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_set.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_stack.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_str.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_superglobals.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_tracing.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_trace_textual.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_trace_computerized.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_trace_html.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_var.c
# End Source File
# Begin Source File 
SOURCE=.\xdebug_xml.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\php_xdebug.h
# End Source File
# Begin Source File

SOURCE=.\usefulstuff.h
# End Source File
# Begin Source File

SOURCE=.\xdebug_code_coverage.h
# End Source File
# Begin Source File

SOURCE=.\xdebug_com.h
# End Source File
# Begin Source File

SOURCE=.\xdebug_compat.h
# End Source File
# Begin Source File

SOURCE=.\xdebug_handler_dbgp.h
# End Source File
# Begin Source File

SOURCE=.\xdebug_handler_gdb.h
# End Source File
# Begin Source File

SOURCE=.\xdebug_handler_php3.h
# End Source File
# Begin Source File

SOURCE=.\xdebug_handlers.h
# End Source File
# Begin Source File

SOURCE=.\xdebug_hash.h
# End Source File
# Begin Source File

SOURCE=.\xdebug_llist.h
# End Source File
# Begin Source File

SOURCE=.\xdebug_mm.h
# End Source File
# Begin Source File

SOURCE=.\xdebug_set.h
# End Source File
# Begin Source File

SOURCE=.\xdebug_str.h
# End Source File
# Begin Source File

SOURCE=.\xdebug_superglobals.h
# End Source File
# Begin Source File

SOURCE=.\xdebug_var.h
# End Source File
# End Group
# End Target
# End Project
