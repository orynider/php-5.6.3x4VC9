# Microsoft Developer Studio Project File - Name="libldap" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libldap - Win32 Single Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libldap.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libldap.mak" CFG="libldap - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libldap - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libldap - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libldap - Win32 Single Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libldap - Win32 Single Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libldap - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Release"
# PROP Intermediate_Dir "..\..\Release\libldap"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Release\oldap32.lib"

!ELSEIF  "$(CFG)" == "libldap - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Debug"
# PROP Intermediate_Dir "..\..\Debug\libldap"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /GX /Z7 /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Debug\oldap32.lib"

!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libldap_"
# PROP BASE Intermediate_Dir "libldap_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\SDebug"
# PROP Intermediate_Dir "..\..\SDebug\libldap"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /GX /Z7 /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Debug\oldap32.lib"
# ADD LIB32 /nologo /out:"..\..\SDebug\oldap32.lib"

!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "libldap0"
# PROP BASE Intermediate_Dir "libldap0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\SRelease"
# PROP Intermediate_Dir "..\..\SRelease\libldap"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Release\oldap32.lib"
# ADD LIB32 /nologo /out:"..\..\SRelease\oldap32.lib"

!ENDIF 

# Begin Target

# Name "libldap - Win32 Debug"
# Name "libldap - Win32 Release"
# Name "libldap - Win32 Single Debug"
# Name "libldap - Win32 Single Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\abandon.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\add.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\addentry.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\bind.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\cache.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\charray.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\compare.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\controls.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\cyrus.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\delete.c


!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\disptmpl.c


!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\dn.c


!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\dnssrv.c


!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\dsparse.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\error.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\extended.c


!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\free.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\friendly.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\getattr.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\getdn.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\getentry.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\getfilter.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\getvalues.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\init.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\kbind.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\messages.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\modify.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\modrdn.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\open.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\options.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\os-ip.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\print.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\references.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\request.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\result.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\sasl.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\sbind.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\schema.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\search.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\sort.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\sortctrl.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\srchpref.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\string.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\tls.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\tmplout.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\ufn.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\unbind.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\url.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\utf-8.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\util-int.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\vlvctrl.c

!IF  "$(CFG)" == "libldap - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Release"

# ADD CPP /nologo /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Debug"

# ADD CPP /nologo /GZ /GX 
!ELSEIF  "$(CFG)" == "libldap - Win32 Single Release"

# ADD CPP /nologo /GX 
!ENDIF

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\srchpref.h
# End Source File
# Begin Source File

SOURCE=..\..\include\portable.h
# End Source File
# Begin Source File

SOURCE=..\..\include\disptmpl.h
# End Source File
# Begin Source File

SOURCE=.\ldap-int.h
# End Source File
# Begin Source File

SOURCE=..\..\include\ldap.h
# End Source File
# Begin Source File

SOURCE=..\..\include\ldap_cdefs.h
# End Source File
# Begin Source File

SOURCE=..\..\include\ldap_config.h
# End Source File
# Begin Source File

SOURCE=..\..\include\ldap_defaults.h
# End Source File
# Begin Source File

SOURCE=..\..\include\ldap_features.h
# End Source File
# Begin Source File

SOURCE=..\..\include\ldap_log.h
# End Source File
# Begin Source File

SOURCE=..\..\include\ldap_pvt.h
# End Source File
# Begin Source File

SOURCE=..\..\include\ldap_schema.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\LDAP_Win32_HOWTO.txt
# End Source File
# End Target
# End Project

