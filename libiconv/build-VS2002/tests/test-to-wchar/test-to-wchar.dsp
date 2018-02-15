# Microsoft Developer Studio Project File - Name="test-to-wchar" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=test-to-wchar - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "test-to-wchar.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test-to-wchar.mak" CFG="test-to-wchar - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test-to-wchar - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "test-to-wchar - x64 Debug" (based on "Win32 (x86) Application")
!MESSAGE "test-to-wchar - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "test-to-wchar - x64 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "test-to-wchar - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "$(SolutionDir)$(ConfigurationName)"
# PROP BASE Intermediate_Dir "$(ConfigurationName)"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "$(SolutionDir)$(ConfigurationName)"
# PROP Intermediate_Dir "$(ConfigurationName)"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /I "..\..\..\include" /I "..\..\..\lib" /I "..\..\..\srclib" /ZI /W3 /Od /D "LIBICONV_DLL" /D "_CRT_SECURE_NO_WARNINGS" /D "_DEBUG" /GF /Gm /GZ /c /GX 
# ADD CPP /nologo /MDd /I "..\..\..\include" /I "..\..\..\lib" /I "..\..\..\srclib" /ZI /W3 /Od /D "LIBICONV_DLL" /D "_CRT_SECURE_NO_WARNINGS" /D "_DEBUG" /GF /Gm /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(OutDir)\libiconv.lib /nologo /debug /pdbtype:sept /subsystem:windows /machine:ix86 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(OutDir)\libiconv.lib /nologo /debug /pdbtype:sept /subsystem:windows /machine:ix86 

!ELSEIF  "$(CFG)" == "test-to-wchar - x64 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "$(SolutionDir)$(PlatformName)\$(ConfigurationName)"
# PROP BASE Intermediate_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "$(SolutionDir)$(PlatformName)\$(ConfigurationName)"
# PROP Intermediate_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /I "..\..\..\include" /I "..\..\..\lib" /I "..\..\..\srclib" /Zi /W3 /Od /D "LIBICONV_DLL" /D "_CRT_SECURE_NO_WARNINGS" /D "_DEBUG" /GF /Gm /GZ /c /GX 
# ADD CPP /nologo /MDd /I "..\..\..\include" /I "..\..\..\lib" /I "..\..\..\srclib" /Zi /W3 /Od /D "LIBICONV_DLL" /D "_CRT_SECURE_NO_WARNINGS" /D "_DEBUG" /GF /Gm /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(OutDir)\libiconv.lib /nologo /debug /pdbtype:sept /subsystem:windows 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(OutDir)\libiconv.lib /nologo /debug /pdbtype:sept /subsystem:windows 

!ELSEIF  "$(CFG)" == "test-to-wchar - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "$(SolutionDir)$(ConfigurationName)"
# PROP BASE Intermediate_Dir "$(ConfigurationName)"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "$(SolutionDir)$(ConfigurationName)"
# PROP Intermediate_Dir "$(ConfigurationName)"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /I "..\..\..\include" /I "..\..\..\lib" /I "..\..\..\srclib" /Zi /W3 /O2 /Oi /D "LIBICONV_DLL" /D "_CRT_SECURE_NO_WARNINGS" /D "NDEBUG" /GF /Gy /c /GX 
# ADD CPP /nologo /MD /I "..\..\..\include" /I "..\..\..\lib" /I "..\..\..\srclib" /Zi /W3 /O2 /Oi /D "LIBICONV_DLL" /D "_CRT_SECURE_NO_WARNINGS" /D "NDEBUG" /GF /Gy /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(OutDir)\libiconv.lib /nologo /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /machine:ix86 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(OutDir)\libiconv.lib /nologo /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /machine:ix86 

!ELSEIF  "$(CFG)" == "test-to-wchar - x64 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "$(SolutionDir)$(PlatformName)\$(ConfigurationName)"
# PROP BASE Intermediate_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "$(SolutionDir)$(PlatformName)\$(ConfigurationName)"
# PROP Intermediate_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /I "..\..\..\include" /I "..\..\..\lib" /I "..\..\..\srclib" /Zi /W3 /O2 /Oi /D "LIBICONV_DLL" /D "_CRT_SECURE_NO_WARNINGS" /D "NDEBUG" /GF /Gy /c /GX 
# ADD CPP /nologo /MD /I "..\..\..\include" /I "..\..\..\lib" /I "..\..\..\srclib" /Zi /W3 /O2 /Oi /D "LIBICONV_DLL" /D "_CRT_SECURE_NO_WARNINGS" /D "NDEBUG" /GF /Gy /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(OutDir)\libiconv.lib /nologo /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(OutDir)\libiconv.lib /nologo /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf 

!ENDIF

# Begin Target

# Name "test-to-wchar - Win32 Debug"
# Name "test-to-wchar - x64 Debug"
# Name "test-to-wchar - Win32 Release"
# Name "test-to-wchar - x64 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx"
# Begin Source File

SOURCE=..\..\..\tests\test-to-wchar.c
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

