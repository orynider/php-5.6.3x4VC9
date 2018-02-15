# Microsoft Developer Studio Project File - Name="liblber" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=liblber - Win32 DLL Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "liblber.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "liblber.mak" CFG="liblber - Win32 DLL Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "liblber - Win32 Release_TS" (based on "Win32 (x86) Static Library")
!MESSAGE "liblber - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "liblber - Win32 Release_TS_SSL" (based on "Win32 (x86) Static Library")
!MESSAGE "liblber - Win32 Release_TS SASL" (based on "Win32 (x86) Static Library")
!MESSAGE "liblber - Win32 Debug_TS" (based on "Win32 (x86) Static Library")
!MESSAGE "liblber - Win32 Debug_TS_SSL" (based on "Win32 (x86) Static Library")
!MESSAGE "liblber - Win32 Debug_TS SASL" (based on "Win32 (x86) Static Library")
!MESSAGE "liblber - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "liblber - Win32 Single Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "liblber - Win32 Single Release" (based on "Win32 (x86) Static Library")
!MESSAGE "liblber - Win32 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "liblber - Win32 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "liblber - Win32 Release_TS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release_TS"
# PROP BASE Intermediate_Dir ".\Release_TS\liblber"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release_TS"
# PROP Intermediate_Dir ".\Release_TS"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "_WINDOWS" /YX /FD /c 
# ADD BASE MTL /nologo /D"NDEBUG" /mktyplib203 /tlb".\Release_TS\olber32_a.tlb" /win32 
# ADD MTL /nologo /D"NDEBUG" /mktyplib203 /tlb".\Release_TS\olber32_a.tlb" /win32 
# ADD BASE RSC /l 1033 /d "NDEBUG" 
# ADD RSC /l 1033 /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\Release_TS\olber32_a.bsc" 
# ADD BSC32 /nologo /o ".\Release_TS\olber32_a.bsc" 
LINK32=link.exe
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Release\olber32.lib"

!ELSEIF  "$(CFG)" == "liblber - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Debug"
# PROP Intermediate_Dir "..\..\Debug\liblber"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /GX /Z7 /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Debug\olber32.lib"

!ELSEIF  "$(CFG)" == "liblber - Win32 Release_TS_SSL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release_TS_SSL"
# PROP BASE Intermediate_Dir ".\Release_TS_SSL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release_TS_SSL"
# PROP Intermediate_Dir ".\Release_TS_SSL\liblber"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D"NDEBUG" /mktyplib203 /tlb".\Release_TS_SSL\olber32_a.tlb" /win32 
# ADD MTL /nologo /D"NDEBUG" /mktyplib203 /tlb".\Release_TS_SSL\olber32_a.tlb" /win32 
# ADD BASE RSC /l 1033 /d "NDEBUG" 
# ADD RSC /l 1033 /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\Release_TS_SSL\olber32_a.bsc" 
# ADD BSC32 /nologo /o ".\Release_TS_SSL\olber32_a.bsc" 
LINK32=link.exe
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Release\olber32.lib"

!ELSEIF  "$(CFG)" == "liblber - Win32 Release_TS SASL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release_TS_SASL"
# PROP BASE Intermediate_Dir ".\Release_TS_SASL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release_TS_SASL"
# PROP Intermediate_Dir ".\Release_TS_SASL\liblber"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "_WINDOWS" /YX /FD /c 
# ADD BASE MTL /nologo /D"NDEBUG" /mktyplib203 /tlb".\Release_TS_SASL\olber32_a.tlb" /win32 
# ADD MTL /nologo /D"NDEBUG" /mktyplib203 /tlb".\Release_TS_SASL\olber32_a.tlb" /win32 
# ADD BASE RSC /l 1033 /d "NDEBUG" 
# ADD RSC /l 1033 /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\Release_TS_SASL\olber32_a.bsc" 
# ADD BSC32 /nologo /o ".\Release_TS_SASL\olber32_a.bsc" 
LINK32=link.exe
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Release\olber32.lib"

!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug_TS"
# PROP BASE Intermediate_Dir ".\Debug_TS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug_TS"
# PROP Intermediate_Dir ".\Debug_TS\liblber"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D"_DEBUG" /mktyplib203 /tlb".\Debug_TS\olber32_a.tlb" /win32 
# ADD MTL /nologo /D"_DEBUG" /mktyplib203 /tlb".\Debug_TS\olber32_a.tlb" /win32 
# ADD BASE RSC /l 1033 /d "_DEBUG" 
# ADD RSC /l 1033 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\Debug_TS\olber32_a.bsc" 
# ADD BSC32 /nologo /o ".\Debug_TS\olber32_a.bsc" 
LINK32=link.exe
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Release\olber32.lib"

!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS_SSL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug_TS_SSL"
# PROP BASE Intermediate_Dir ".\Debug_TS_SSL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug_TS_SSL"
# PROP Intermediate_Dir ".\Debug_TS_SSL\liblber"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "_WINDOWS" /YX /FD /c 
# ADD BASE MTL /nologo /D"_DEBUG" /mktyplib203 /tlb".\Debug_TS_SSL\olber32_a.tlb" /win32 
# ADD MTL /nologo /D"_DEBUG" /mktyplib203 /tlb".\Debug_TS_SSL\olber32_a.tlb" /win32 
# ADD BASE RSC /l 1033 /d "_DEBUG" 
# ADD RSC /l 1033 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\Debug_TS_SSL\olber32_a.bsc" 
# ADD BSC32 /nologo /o ".\Debug_TS_SSL\olber32_a.bsc" 
LINK32=link.exe
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Release\olber32.lib"

!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS SASL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug_TS_SASL"
# PROP BASE Intermediate_Dir ".\Debug_TS_SASL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug_TS_SASL"
# PROP Intermediate_Dir ".\Debug_TS_SASL\liblber"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D"_DEBUG" /mktyplib203 /tlb".\Debug_TS_SASL\olber32_a.tlb" /win32 
# ADD MTL /nologo /D"_DEBUG" /mktyplib203 /tlb".\Debug_TS_SASL\olber32_a.tlb" /win32 
# ADD BASE RSC /l 1033 /d "_DEBUG" 
# ADD RSC /l 1033 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o ".\Debug_TS_SASL\olber32_a.bsc" 
# ADD BSC32 /nologo /o ".\Debug_TS_SASL\olber32_a.bsc" 
LINK32=link.exe
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Release\olber32.lib"

!ELSEIF  "$(CFG)" == "liblber - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Release"
# PROP Intermediate_Dir "..\..\Release\liblber"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Release\olber32.lib"

!ELSEIF  "$(CFG)" == "liblber - Win32 Single Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "liblber_"
# PROP BASE Intermediate_Dir "liblber_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Sdebug"
# PROP Intermediate_Dir "..\..\SDebug\liblber"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /GX /Z7 /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Debug\olber32.lib"
# ADD LIB32 /nologo /out:"..\..\SDebug\olber32.lib"

!ELSEIF  "$(CFG)" == "liblber - Win32 Single Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "liblber0"
# PROP BASE Intermediate_Dir "liblber0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\SRelease"
# PROP Intermediate_Dir "..\..\SRelease\liblber"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Release\olber32.lib"
# ADD LIB32 /nologo /out:"..\..\SRelease\olber32.lib"

!ELSEIF  "$(CFG)" == "liblber - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "liblber_"
# PROP BASE Intermediate_Dir "liblber_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\DLLDebug"
# PROP Intermediate_Dir "..\..\DLLDebug\liblber"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /GX /Z7 /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\Debug\olber32.lib"
# ADD LIB32 /nologo /out:"..\..\DLLDebug\olber32.lib"

!ELSEIF  "$(CFG)" == "liblber - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "liblber0"
# PROP BASE Intermediate_Dir "liblber0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "liblber0"
# PROP Intermediate_Dir "liblber0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\Release\olber32.lib"
# ADD LIB32 /nologo /out:"..\..\Release\olber32.lib"

!ENDIF

# Begin Target

# Name "liblber - Win32 Release_TS"
# Name "liblber - Win32 Debug"
# Name "liblber - Win32 Release_TS_SSL"
# Name "liblber - Win32 Release_TS SASL"
# Name "liblber - Win32 Debug_TS"
# Name "liblber - Win32 Debug_TS_SSL"
# Name "liblber - Win32 Debug_TS SASL"
# Name "liblber - Win32 Release"
# Name "liblber - Win32 Single Debug"
# Name "liblber - Win32 Single Release"
# Name "liblber - Win32 DLL Debug"
# Name "liblber - Win32 DLL Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=bprint.c

!IF  "$(CFG)" == "liblber - Win32 Release_TS"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release_TS_SSL"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release_TS SASL"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS_SSL"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS SASL"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=decode.c

!IF  "$(CFG)" == "liblber - Win32 Release_TS"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release_TS_SSL"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release_TS SASL"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS_SSL"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS SASL"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=encode.c

!IF  "$(CFG)" == "liblber - Win32 Release_TS"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release_TS_SSL"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release_TS SASL"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS_SSL"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS SASL"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=io.c

!IF  "$(CFG)" == "liblber - Win32 Release_TS"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release_TS_SSL"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release_TS SASL"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS_SSL"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS SASL"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=memory.c

!IF  "$(CFG)" == "liblber - Win32 Release_TS"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release_TS_SSL"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release_TS SASL"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS_SSL"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS SASL"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=nt_err.c

!IF  "$(CFG)" == "liblber - Win32 Release_TS"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release_TS_SSL"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release_TS SASL"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS_SSL"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS SASL"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=options.c

!IF  "$(CFG)" == "liblber - Win32 Release_TS"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release_TS_SSL"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release_TS SASL"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS_SSL"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS SASL"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=sockbuf.c

!IF  "$(CFG)" == "liblber - Win32 Release_TS"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release_TS_SSL"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release_TS SASL"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS_SSL"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Debug_TS SASL"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "liblber - Win32 Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=lber-int.h
# End Source File
# Begin Source File

SOURCE=..\..\include\lber.h
# End Source File
# Begin Source File

SOURCE=..\..\include\lber_pvt.h
# End Source File
# Begin Source File

SOURCE=..\..\include\lber_types.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project

