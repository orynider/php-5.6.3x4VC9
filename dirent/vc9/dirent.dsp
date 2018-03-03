# Microsoft Developer Studio Project File - Name="dirent" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=dirent - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dirent.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dirent.mak" CFG="dirent - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dirent - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "dirent - x64 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "dirent - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "dirent - x64 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dirent - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /ZI /W3 /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "_MBCS" /Gm /Fp"$(IntDir)/dirent.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /GZ /c /D_CRT_SECURE_NO_WARNINGS/GX 
# ADD CPP /nologo /MDd /ZI /W3 /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "_MBCS" /Gm /Fp"$(IntDir)/dirent.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /GZ /c /D_CRT_SECURE_NO_WARNINGS/GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 2057 /d "_DEBUG" 
# ADD RSC /l 2057 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\Debug\dirent.bsc" 
# ADD BSC32 /nologo /o ".\Debug\dirent.bsc" 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\dirent_a_debug.lib" 
# ADD LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\dirent_a_debug.lib" 

!ELSEIF  "$(CFG)" == "dirent - x64 Debug"

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
# ADD BASE CPP /nologo /MDd /Zi /W3 /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "_MBCS" /Gm /Fp"$(IntDir)/dirent.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /GZ /c /D_CRT_SECURE_NO_WARNINGS/GX 
# ADD CPP /nologo /MDd /Zi /W3 /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "_MBCS" /Gm /Fp"$(IntDir)/dirent.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /GZ /c /D_CRT_SECURE_NO_WARNINGS/GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 2057 /d "_DEBUG" 
# ADD RSC /l 2057 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\Debug\dirent.bsc" 
# ADD BSC32 /nologo /o ".\Debug\dirent.bsc" 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\dirent_a_debug.lib" 
# ADD LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\dirent_a_debug.lib" 

!ELSEIF  "$(CFG)" == "dirent - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /O2 /Ob1 /D "WIN32" /D "NDEBUG" /D "_LIB" /D "__USE_FILE_OFFSET64" /D "HAVE_READDIR_R" /D "_MBCS" /GF /Gy /Fp"$(IntDir)/dirent.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /c /D_CRT_SECURE_NO_WARNINGS/GX 
# ADD CPP /nologo /MD /W3 /O2 /Ob1 /D "WIN32" /D "NDEBUG" /D "_LIB" /D "__USE_FILE_OFFSET64" /D "HAVE_READDIR_R" /D "_MBCS" /GF /Gy /Fp"$(IntDir)/dirent.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /c /D_CRT_SECURE_NO_WARNINGS/GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 2057 /d "NDEBUG" 
# ADD RSC /l 2057 /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\Release\dirent.bsc" 
# ADD BSC32 /nologo /o ".\Release\dirent.bsc" 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\dirent_a.lib" 
# ADD LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\dirent_a.lib" 

!ELSEIF  "$(CFG)" == "dirent - x64 Release"

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
# ADD BASE CPP /nologo /MD /W3 /O2 /Ob1 /D "WIN32" /D "NDEBUG" /D "_LIB" /D "_MBCS" /GF /Gy /Fp"$(IntDir)/dirent.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /c /D_CRT_SECURE_NO_WARNINGS/GX 
# ADD CPP /nologo /MD /W3 /O2 /Ob1 /D "WIN32" /D "NDEBUG" /D "_LIB" /D "_MBCS" /GF /Gy /Fp"$(IntDir)/dirent.pch" /Fo"$(IntDir)/" /Fd"$(IntDir)/" /c /D_CRT_SECURE_NO_WARNINGS/GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 2057 /d "NDEBUG" 
# ADD RSC /l 2057 /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\Release\dirent.bsc" 
# ADD BSC32 /nologo /o ".\Release\dirent.bsc" 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\dirent_a.lib" 
# ADD LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\dirent_a.lib" 

!ENDIF

# Begin Target

# Name "dirent - Win32 Debug"
# Name "dirent - x64 Debug"
# Name "dirent - Win32 Release"
# Name "dirent - x64 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\dirent.c

!IF  "$(CFG)" == "dirent - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "dirent - x64 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "dirent - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "dirent - x64 Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\dirent.h
# End Source File
# End Group
# End Target
# End Project

