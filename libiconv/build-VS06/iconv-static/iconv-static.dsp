# Microsoft Developer Studio Project File - Name="iconv" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=iconv - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "iconv.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "iconv.mak" CFG="iconv - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "iconv - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "iconv - x64 Debug" (based on "Win32 (x86) Application")
!MESSAGE "iconv - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "iconv - x64 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "iconv - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "$(SolutionDir)$(ConfigurationName)\static"
# PROP BASE Intermediate_Dir "$(ConfigurationName)"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "$(SolutionDir)$(ConfigurationName)\static"
# PROP Intermediate_Dir "$(ConfigurationName)"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /I "..\..\src" /I "..\..\include" /I "..\..\srclib" /I "..\..\lib" /ZI /W3 /Od /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "_DEBUG" /GF /Gm /GZ /c /GX 
# ADD CPP /nologo /MDd /I "..\..\src" /I "..\..\include" /I "..\..\srclib" /I "..\..\lib" /ZI /W3 /Od /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "_DEBUG" /GF /Gm /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(OutDir)\..\libiconv-static.lib /nologo /debug /pdbtype:sept /subsystem:windows /machine:ix86 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(OutDir)\..\libiconv-static.lib /nologo /debug /pdbtype:sept /subsystem:windows /machine:ix86 

!ELSEIF  "$(CFG)" == "iconv - x64 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "$(SolutionDir)$(PlatformName)\$(ConfigurationName)\static"
# PROP BASE Intermediate_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "$(SolutionDir)$(PlatformName)\$(ConfigurationName)\static"
# PROP Intermediate_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /I "..\..\src" /I "..\..\include" /I "..\..\srclib" /I "..\..\lib" /Zi /W3 /Od /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "_DEBUG" /GF /Gm /GZ /c /GX 
# ADD CPP /nologo /MDd /I "..\..\src" /I "..\..\include" /I "..\..\srclib" /I "..\..\lib" /Zi /W3 /Od /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "_DEBUG" /GF /Gm /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(OutDir)\..\libiconv-static.lib /nologo /debug /pdbtype:sept /subsystem:windows 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(OutDir)\..\libiconv-static.lib /nologo /debug /pdbtype:sept /subsystem:windows 

!ELSEIF  "$(CFG)" == "iconv - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "$(SolutionDir)$(ConfigurationName)\static"
# PROP BASE Intermediate_Dir "$(ConfigurationName)"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "$(SolutionDir)$(ConfigurationName)\static"
# PROP Intermediate_Dir "$(ConfigurationName)"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /I "..\..\src" /I "..\..\include" /I "..\..\srclib" /I "..\..\lib" /Zi /W3 /O2 /Oi /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "NDEBUG" /GF /Gy /c /GX 
# ADD CPP /nologo /MD /I "..\..\src" /I "..\..\include" /I "..\..\srclib" /I "..\..\lib" /Zi /W3 /O2 /Oi /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "NDEBUG" /GF /Gy /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(OutDir)\..\libiconv-static.lib /nologo /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /machine:ix86 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(OutDir)\..\libiconv-static.lib /nologo /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /machine:ix86 

!ELSEIF  "$(CFG)" == "iconv - x64 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "$(SolutionDir)$(PlatformName)\$(ConfigurationName)\static"
# PROP BASE Intermediate_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "$(SolutionDir)$(PlatformName)\$(ConfigurationName)\static"
# PROP Intermediate_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /I "..\..\src" /I "..\..\include" /I "..\..\srclib" /I "..\..\lib" /Zi /W3 /O2 /Oi /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "NDEBUG" /GF /Gy /c /GX 
# ADD CPP /nologo /MD /I "..\..\src" /I "..\..\include" /I "..\..\srclib" /I "..\..\lib" /Zi /W3 /O2 /Oi /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "NDEBUG" /GF /Gy /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(OutDir)\..\libiconv-static.lib /nologo /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(OutDir)\..\libiconv-static.lib /nologo /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf 

!ENDIF

# Begin Target

# Name "iconv - Win32 Debug"
# Name "iconv - x64 Debug"
# Name "iconv - Win32 Release"
# Name "iconv - x64 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx"
# Begin Group "src"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\iconv.c

!IF  "$(CFG)" == "iconv - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "iconv - x64 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "iconv - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "iconv - x64 Release"

# PROP Exclude_From_Build 1

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\iconv_no_i18n.c
# End Source File
# End Group
# Begin Group "srclib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\srclib\progname.c
# End Source File
# Begin Source File

SOURCE=..\..\srclib\safe-read.c
# End Source File
# Begin Group "uniwidth"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\srclib\uniwidth\width.c
# End Source File
# End Group
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;inc;xsd"
# Begin Group "include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\include\iconv.h
# End Source File
# End Group
# Begin Group "src"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\config.h
# End Source File
# End Group
# Begin Group "srclib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\srclib\binary-io.h
# End Source File
# Begin Source File

SOURCE=..\..\srclib\gettext.h
# End Source File
# Begin Source File

SOURCE=..\..\srclib\localcharset.h
# End Source File
# Begin Source File

SOURCE=..\..\srclib\progname.h
# End Source File
# Begin Source File

SOURCE=..\..\srclib\safe-read.h
# End Source File
# Begin Source File

SOURCE=..\..\srclib\streq.h
# End Source File
# Begin Source File

SOURCE=..\..\srclib\unitypes.h
# End Source File
# Begin Source File

SOURCE=..\..\srclib\uniwidth.h
# End Source File
# Begin Source File

SOURCE=..\..\srclib\xalloc.h
# End Source File
# Begin Group "uniwidth"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\srclib\uniwidth\cjk.h
# End Source File
# End Group
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx;tiff;tif;png;wav"
# Begin Source File

SOURCE=..\..\win32\iconv.rc
# End Source File
# End Group
# End Target
# End Project

