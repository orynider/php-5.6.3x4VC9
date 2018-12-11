# Microsoft Developer Studio Project File - Name="php" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=php - Win32 Release_TS_inline
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "php.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "php.mak" CFG="php - Win32 Release_TS_inline"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "php - Win32 Release_TS_inline" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "php - Win32 Debug_TS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "php - Win32 Release_TS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "php - Win32 Release_TS_inline"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\Release_TS_inline"
# PROP BASE Intermediate_Dir ".\Release_TS_inline"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\Release_TS_inline"
# PROP Intermediate_Dir ".\Release_TS_inline"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /I "." /I "..\..\..\php_build\cli30\include\" /I "..\..\include" /I "..\..\win32" /I "..\..\Zend" /I "..\.." /I "..\..\..\bindlib_w32" /I "..\..\main" /I "..\..\tsrm" /W3 /O2 /Ob1 /D "_WINDOWS" /D "ZEND_WIN32" /D "PHP_WIN32" /D "WIN32" /D "_MBCS" /D "_USE_32BIT_TIME_T" /D "NDebug" /D "NDEBUG" /D "ZEND_WIN32_FORCE_INLINE" /D "ZEND_DEBUG" /D "ZTS" /D "_MBCS" /GF /Gy /Fp".\Release_TS_inline/php5cli.pch" /Fo".\Release_TS_inline/" /Fd".\Release_TS_inline/" /c /GX 
# ADD CPP /nologo /MD /I "." /I "..\..\..\php_build\cli30\include\" /I "..\..\include" /I "..\..\win32" /I "..\..\Zend" /I "..\.." /I "..\..\..\bindlib_w32" /I "..\..\main" /I "..\..\tsrm" /W3 /O2 /Ob1 /D "_WINDOWS" /D "ZEND_WIN32" /D "PHP_WIN32" /D "WIN32" /D "_MBCS" /D "_USE_32BIT_TIME_T" /D "NDebug" /D "NDEBUG" /D "ZEND_WIN32_FORCE_INLINE" /D "ZEND_DEBUG" /D "ZTS" /D "_MBCS" /GF /Gy /Fp".\Release_TS_inline/php5cli.pch" /Fo".\Release_TS_inline/" /Fd".\Release_TS_inline/" /c /GX 
# ADD BASE MTL /nologo /D"NDEBUG" /mktyplib203 /tlb".\..\..\Release_TS_inline\php5cli.tlb" /win32 
# ADD MTL /nologo /D"NDEBUG" /mktyplib203 /tlb".\..\..\Release_TS_inline\php5cli.tlb" /win32 
# ADD BASE RSC /l 1033 /d "NDEBUG" 
# ADD RSC /l 1033 /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\..\..\Release_TS_inline\php5cli.bsc" 
# ADD BSC32 /nologo /o ".\..\..\Release_TS_inline\php5cli.bsc" 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libxml2_a_dll.lib php5embed.lib odbc32.lib odbccp32.lib /nologo /dll /out:".\..\..\Release_TS_inline\php5cli.dll" /version:4.0 /incremental:no /libpath:"..\..\..\deps\cli30\lib\" /libpath:"..\..\Release_TS_inline" /libpath:"..\..\TSRM\Release_TS_inline" /libpath:"..\..\Zend\Release_TS_inline" /libpath:"..\..\..\deps\lib\" /pdb:".\..\..\Release_TS_inline\php5cli.pdb" /pdbtype:sept /subsystem:windows /base:"0x62000000" /implib:".\..\..\Release_TS_inline/php5cli.lib" /machine:ix86 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libxml2_a_dll.lib php5embed.lib odbc32.lib odbccp32.lib /nologo /dll /out:".\..\..\Release_TS_inline\php5cli.dll" /version:4.0 /incremental:no /libpath:"..\..\..\deps\cli30\lib\" /libpath:"..\..\Release_TS_inline" /libpath:"..\..\TSRM\Release_TS_inline" /libpath:"..\..\Zend\Release_TS_inline" /libpath:"..\..\..\deps\lib\" /pdb:".\..\..\Release_TS_inline\php5cli.pdb" /pdbtype:sept /subsystem:windows /base:"0x62000000" /implib:".\..\..\Release_TS_inline/php5cli.lib" /machine:ix86 

!ELSEIF  "$(CFG)" == "php - Win32 Debug_TS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\Debug_TS"
# PROP BASE Intermediate_Dir ".\Debug_TS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\Debug_TS"
# PROP Intermediate_Dir ".\Debug_TS"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /I "." /I "..\..\..\php_build\cli30\include\" /I "..\..\include" /I "..\..\win32" /I "..\..\Zend" /I "..\.." /I "..\..\..\bindlib_w32" /I "..\..\main" /I "..\..\tsrm" /ZI /W3 /Od /D "_WINDOWS" /D "ZEND_WIN32" /D "PHP_WIN32" /D "WIN32" /D "_MBCS" /D "_USE_32BIT_TIME_T" /D "NDebug" /D "NDEBUG" /D "ZEND_WIN32_FORCE_INLINE" /D "ZEND_DEBUG" /D "ZTS" /D "_MBCS" /Gm /Fp".\Debug_TS/php5cli.pch" /Fo".\Debug_TS/" /Fd".\Debug_TS/" /FR /GZ /c /GX 
# ADD CPP /nologo /MDd /I "." /I "..\..\..\php_build\cli30\include\" /I "..\..\include" /I "..\..\win32" /I "..\..\Zend" /I "..\.." /I "..\..\..\bindlib_w32" /I "..\..\main" /I "..\..\tsrm" /ZI /W3 /Od /D "_WINDOWS" /D "ZEND_WIN32" /D "PHP_WIN32" /D "WIN32" /D "_MBCS" /D "_USE_32BIT_TIME_T" /D "NDebug" /D "NDEBUG" /D "ZEND_WIN32_FORCE_INLINE" /D "ZEND_DEBUG" /D "ZTS" /D "_MBCS" /Gm /Fp".\Debug_TS/php5cli.pch" /Fo".\Debug_TS/" /Fd".\Debug_TS/" /FR /GZ /c /GX 
# ADD BASE MTL /nologo /D"_DEBUG" /mktyplib203 /tlb".\..\..\Debug_TS\php5cli.tlb" /win32 
# ADD MTL /nologo /D"_DEBUG" /mktyplib203 /tlb".\..\..\Debug_TS\php5cli.tlb" /win32 
# ADD BASE RSC /l 1033 /d "_DEBUG" 
# ADD RSC /l 1033 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\..\..\Debug_TS\php5cli.bsc" 
# ADD BSC32 /nologo /o ".\..\..\Debug_TS\php5cli.bsc" 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libxml2_a_dll.lib php5embed.lib odbc32.lib odbccp32.lib /nologo /out:".\..\..\Debug_TS\php5cli.dll" /version:4.0 /incremental:yes /libpath:"..\..\..\deps\cli30\lib\" /libpath:"..\..\Debug_TS" /libpath:"..\..\TSRM\Debug_TS" /libpath:"..\..\Zend\Debug_TS" /libpath:"..\..\..\deps\lib\" /debug /pdb:".\..\..\Debug_TS\php5cli.pdb" /pdbtype:sept /subsystem:windows /base:"0x62000000" /implib:".\..\..\Debug_TS/php5cli.lib" /machine:ix86 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libxml2_a_dll.lib php5embed.lib odbc32.lib odbccp32.lib /nologo /out:".\..\..\Debug_TS\php5cli.dll" /version:4.0 /incremental:yes /libpath:"..\..\..\deps\cli30\lib\" /libpath:"..\..\Debug_TS" /libpath:"..\..\TSRM\Debug_TS" /libpath:"..\..\Zend\Debug_TS" /libpath:"..\..\..\deps\lib\" /debug /pdb:".\..\..\Debug_TS\php5cli.pdb" /pdbtype:sept /subsystem:windows /base:"0x62000000" /implib:".\..\..\Debug_TS/php5cli.lib" /machine:ix86 

!ELSEIF  "$(CFG)" == "php - Win32 Release_TS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\Release_TS"
# PROP BASE Intermediate_Dir ".\Release_TS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\Release_TS"
# PROP Intermediate_Dir ".\Release_TS"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /I "." /I "..\..\..\php_build\cli30\include\" /I "..\..\include" /I "..\..\win32" /I "..\..\Zend" /I "..\.." /I "..\..\..\bindlib_w32" /I "..\..\main" /I "..\..\tsrm" /W3 /O2 /Ob1 /D "_WINDOWS" /D "ZEND_WIN32" /D "PHP_WIN32" /D "WIN32" /D "_MBCS" /D "_USE_32BIT_TIME_T" /D "NDebug" /D "NDEBUG" /D "ZEND_WIN32_FORCE_INLINE" /D "ZEND_DEBUG" /D "ZTS" /D "_MBCS" /GF /Gy /Fp".\Release_TS/php5cli.pch" /Fo".\Release_TS/" /Fd".\Release_TS/" /c /GX 
# ADD CPP /nologo /MD /I "." /I "..\..\..\php_build\cli30\include\" /I "..\..\include" /I "..\..\win32" /I "..\..\Zend" /I "..\.." /I "..\..\..\bindlib_w32" /I "..\..\main" /I "..\..\tsrm" /W3 /O2 /Ob1 /D "_WINDOWS" /D "ZEND_WIN32" /D "PHP_WIN32" /D "WIN32" /D "_MBCS" /D "_USE_32BIT_TIME_T" /D "NDebug" /D "NDEBUG" /D "ZEND_WIN32_FORCE_INLINE" /D "ZEND_DEBUG" /D "ZTS" /D "_MBCS" /GF /Gy /Fp".\Release_TS/php5cli.pch" /Fo".\Release_TS/" /Fd".\Release_TS/" /c /GX 
# ADD BASE MTL /nologo /D"NDEBUG" /mktyplib203 /tlb".\..\..\Release_TS\php5cli.tlb" /win32 
# ADD MTL /nologo /D"NDEBUG" /mktyplib203 /tlb".\..\..\Release_TS\php5cli.tlb" /win32 
# ADD BASE RSC /l 1033 /d "NDEBUG" 
# ADD RSC /l 1033 /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\..\..\Release_TS\php5cli.bsc" 
# ADD BSC32 /nologo /o ".\..\..\Release_TS\php5cli.bsc" 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libxml2_a_dll.lib php5embed.lib odbc32.lib odbccp32.lib /nologo /dll /out:".\..\..\Release_TS\php5cli.dll" /version:4.0 /incremental:no /libpath:"..\..\..\deps\cli30\lib\" /libpath:"..\..\Release_TS" /libpath:"..\..\TSRM\Release_TS" /libpath:"..\..\Zend\Release_TS" /libpath:"..\..\..\deps\lib\" /pdb:".\..\..\Release_TS\php5cli.pdb" /pdbtype:sept /subsystem:windows /base:"0x62000000" /implib:".\..\..\Release_TS/php5cli.lib" /machine:ix86 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libxml2_a_dll.lib php5embed.lib odbc32.lib odbccp32.lib /nologo /dll /out:".\..\..\Release_TS\php5cli.dll" /version:4.0 /incremental:no /libpath:"..\..\..\deps\cli30\lib\" /libpath:"..\..\Release_TS" /libpath:"..\..\TSRM\Release_TS" /libpath:"..\..\Zend\Release_TS" /libpath:"..\..\..\deps\lib\" /pdb:".\..\..\Release_TS\php5cli.pdb" /pdbtype:sept /subsystem:windows /base:"0x62000000" /implib:".\..\..\Release_TS/php5cli.lib" /machine:ix86 

!ENDIF

# Begin Target

# Name "php - Win32 Release_TS_inline"
# Name "php - Win32 Debug_TS"
# Name "php - Win32 Release_TS"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=php_cli.c

!IF  "$(CFG)" == "php - Win32 Release_TS_inline"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "php - Win32 Debug_TS"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "php - Win32 Release_TS"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=php_cli.c

!IF  "$(CFG)" == "php - Win32 Release_TS_inline"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "php - Win32 Debug_TS"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "php - Win32 Release_TS"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=php_cli_process_title.c

!IF  "$(CFG)" == "php - Win32 Release_TS_inline"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "php - Win32 Debug_TS"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "php - Win32 Release_TS"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=php_cli_server.c

!IF  "$(CFG)" == "php - Win32 Release_TS_inline"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "php - Win32 Debug_TS"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "php - Win32 Release_TS"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=php_http_parser.c

!IF  "$(CFG)" == "php - Win32 Release_TS_inline"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "php - Win32 Debug_TS"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "php - Win32 Release_TS"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=ps_title.c

!IF  "$(CFG)" == "php - Win32 Release_TS_inline"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "php - Win32 Debug_TS"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "php - Win32 Release_TS"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\Release_TS\php-win.exe.res
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=php_cli.h
# End Source File
# End Group
# End Target
# End Project

