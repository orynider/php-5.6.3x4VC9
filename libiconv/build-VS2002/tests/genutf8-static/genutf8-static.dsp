# Microsoft Developer Studio Project File - Name="genutf8" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=genutf8 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "genutf8.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "genutf8.mak" CFG="genutf8 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "genutf8 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "genutf8 - x64 Debug" (based on "Win32 (x86) Application")
!MESSAGE "genutf8 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "genutf8 - x64 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "genutf8 - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /I "..\..\..\src" /I "..\..\..\srclib" /ZI /W3 /Od /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "_DEBUG" /GF /Gm /GZ /c /GX 
# ADD CPP /nologo /MDd /I "..\..\..\src" /I "..\..\..\srclib" /ZI /W3 /Od /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "_DEBUG" /GF /Gm /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /debug /pdbtype:sept /subsystem:windows /machine:ix86 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /debug /pdbtype:sept /subsystem:windows /machine:ix86 

!ELSEIF  "$(CFG)" == "genutf8 - x64 Debug"

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
# ADD BASE CPP /nologo /MDd /I "..\..\..\src" /I "..\..\..\srclib" /Zi /W3 /Od /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "_DEBUG" /GF /Gm /GZ /c /GX 
# ADD CPP /nologo /MDd /I "..\..\..\src" /I "..\..\..\srclib" /Zi /W3 /Od /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "_DEBUG" /GF /Gm /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /debug /pdbtype:sept /subsystem:windows 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /debug /pdbtype:sept /subsystem:windows 

!ELSEIF  "$(CFG)" == "genutf8 - Win32 Release"

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
# ADD BASE CPP /nologo /MD /I "..\..\..\src" /I "..\..\..\srclib" /Zi /W3 /O2 /Oi /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "NDEBUG" /GF /Gy /c /GX 
# ADD CPP /nologo /MD /I "..\..\..\src" /I "..\..\..\srclib" /Zi /W3 /O2 /Oi /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "NDEBUG" /GF /Gy /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /machine:ix86 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /machine:ix86 

!ELSEIF  "$(CFG)" == "genutf8 - x64 Release"

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
# ADD BASE CPP /nologo /MD /I "..\..\..\src" /I "..\..\..\srclib" /Zi /W3 /O2 /Oi /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "NDEBUG" /GF /Gy /c /GX 
# ADD CPP /nologo /MD /I "..\..\..\src" /I "..\..\..\srclib" /Zi /W3 /O2 /Oi /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "NDEBUG" /GF /Gy /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf 

!ENDIF

# Begin Target

# Name "genutf8 - Win32 Debug"
# Name "genutf8 - x64 Debug"
# Name "genutf8 - Win32 Release"
# Name "genutf8 - x64 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx"
# Begin Source File

SOURCE=..\..\..\tests\genutf8.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;inc;xsd"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx;tiff;tif;png;wav"
# End Group
# End Target
# End Project

