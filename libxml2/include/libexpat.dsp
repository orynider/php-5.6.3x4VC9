# Microsoft Developer Studio Project File - Name="libexpat" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libexpat - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libexpat.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libexpat.mak" CFG="libexpat - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libexpat - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libexpat - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libexpat - x64 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libexpat - x64 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libexpat - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "LibR"
# PROP BASE Intermediate_Dir "LibR"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "LibR"
# PROP Intermediate_Dir "LibR"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /O2 /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_LIB" /D "_CRT_SECURE_NO_WARNINGS" /FD /c
# ADD CPP /nologo /MD /W3 /Zi /O2 /Oy- /I "." /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_LIB" /D "_CRT_SECURE_NO_WARNINGS" /D "COMPILED_FROM_DSP" /D "libexpat_STATIC" /Fo"$(INTDIR)\" /Fd"$(OUTDIR)\libexpat" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"LibR\libexpatMT.lib"

!ELSEIF  "$(CFG)" == "libexpat - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "LibD"
# PROP BASE Intermediate_Dir "LibD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "LibD"
# PROP Intermediate_Dir "LibD"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_CRT_SECURE_NO_WARNINGS" /FD /EHsc /c
# ADD CPP /nologo /MDd /W3 /Zi /Od /I "." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_CRT_SECURE_NO_WARNINGS" /D "COMPILED_FROM_DSP" /D "libexpat_STATIC" /Fo"$(INTDIR)\" /Fd"$(OUTDIR)\libexpat" /FD /EHsc /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"LibD\libexpatMTd.lib"

!ELSEIF  "$(CFG)" == "libexpat - x64 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "x64\LibR"
# PROP BASE Intermediate_Dir "x64\LibR"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x64\LibR"
# PROP Intermediate_Dir "x64\LibR"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /O2 /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_LIB" /D "_CRT_SECURE_NO_WARNINGS" /FD /c
# ADD CPP /nologo /MD /W3 /Zi /O2 /Oy- /I "." /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_LIB" /D "_CRT_SECURE_NO_WARNINGS" /D "COMPILED_FROM_DSP" /D "libexpat_STATIC" /Fo"$(INTDIR)\" /Fd"$(OUTDIR)\libexpat" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"x64\LibR\libexpat.lib"

!ELSEIF  "$(CFG)" == "libexpat - x64 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "x64\LibD"
# PROP BASE Intermediate_Dir "x64\LibD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x64\LibD"
# PROP Intermediate_Dir "x64\LibD"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_CRT_SECURE_NO_WARNINGS" /FD /EHsc /c
# ADD CPP /nologo /MDd /W3 /Zi /Od /I "." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_CRT_SECURE_NO_WARNINGS" /D "COMPILED_FROM_DSP" /D "libexpat_STATIC" /Fo"$(INTDIR)\" /Fd"$(OUTDIR)\libexpat" /FD /EHsc /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"x64\LibD\libexpatD.lib"

!ENDIF 

# Begin Target

# Name "libexpat - Win32 Release"
# Name "libexpat - Win32 Debug"
# Name "libexpat - x64 Release"
# Name "libexpat - x64 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File
SOURCE=.\libxml\loadlibrary.c
# End Source File
# Begin Source File
SOURCE=.\libxml\xmlparse.c
# End Source File
# Begin Source File
SOURCE=.\libxml\xmlrole.c
# End Source File
# Begin Source File
SOURCE=.\libxml\xmltok.c
# End Source File
# Begin Source File
SOURCE=.\libxml\xmltok_impl.c
# End Source File
# Begin Source File
SOURCE=.\libxml\xmltok_ns.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File
SOURCE=.\libxml\ascii.h" 	
# End Source File
# Begin Source File	
SOURCE=.\libxml\asciitab.h" 
# End Source File
# Begin Source File		
SOURCE=.\libxml\expat.h" 
# End Source File
# Begin Source File		
SOURCE=.\libxml\expat_external.h" 
# End Source File
# Begin Source File		
SOURCE=.\libxml\iasciitab.h" 
# End Source File
# Begin Source File		
SOURCE=.\libxml\internal.h" 
# End Source File
# Begin Source File		
SOURCE=.\libxml\latin1tab.h" 
# End Source File
# Begin Source File		
SOURCE=.\libxml\nametab.h" 
# End Source File
# Begin Source File		
SOURCE=.\libxml\siphash.h" 
# End Source File
# Begin Source File		
SOURCE=.\libxml\utf8tab.h" 
# End Source File
# Begin Source File		
SOURCE=.\libxml\xmlrole.h" 
# End Source File
# Begin Source File		
SOURCE=.\libxml\xmltok.h" 
# End Source File
# Begin Source File		
SOURCE=.\libxml\xmltok_impl.h" 
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
