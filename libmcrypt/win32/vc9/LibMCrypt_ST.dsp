# Microsoft Developer Studio Project File - Name="LibMCrypt_ST" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=LibMCrypt_ST - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LibMCrypt_ST.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LibMCrypt_ST.mak" CFG="LibMCrypt_ST - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LibMCrypt_ST - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LibMCrypt_ST - x64 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LibMCrypt_ST - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibMCrypt_ST - x64 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LibMCrypt_ST - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /I "..\..\" /I "..\..\lib" /I "..\..\..\..\deps\include" /I ""C:\php-sdk\phpdev\vc9\x86\deps\include"" /Zi /W3 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_LIB" /D "_MBCS" /Gm /Fp"$(IntDir)/libmcrypt.pch" /Fd"$(OutDir)\$(ProjectName)_a_debug.pdb" /FR /GZ /c /D_CRT_SECURE_NO_WARNINGS/GX 
# ADD CPP /nologo /MDd /I "..\..\" /I "..\..\lib" /I "..\..\..\..\deps\include" /I ""C:\php-sdk\phpdev\vc9\x86\deps\include"" /Zi /W3 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_LIB" /D "_MBCS" /Gm /Fp"$(IntDir)/libmcrypt.pch" /Fd"$(OutDir)\$(ProjectName)_a_debug.pdb" /FR /GZ /c /D_CRT_SECURE_NO_WARNINGS/GX 
# ADD BASE MTL /nologo /D"_DEBUG" /mktyplib203 /tlb"$(PlatformName)\$(ConfigurationName)\libmcrypt.tlb" /win32 
# ADD MTL /nologo /D"_DEBUG" /mktyplib203 /tlb"$(PlatformName)\$(ConfigurationName)\libmcrypt.tlb" /win32 
# ADD BASE RSC /l 2057 /d "_DEBUG" 
# ADD RSC /l 2057 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o "$(PlatformName)\$(ConfigurationName)\objs\libmcrypt.bsc" 
# ADD BSC32 /nologo /o "$(PlatformName)\$(ConfigurationName)\objs\libmcrypt.bsc" 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\$(ProjectName)_a_debug.lib" 
# ADD LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\$(ProjectName)_a_debug.lib" 
# Begin Custom Build - Creating static library libmcrypt_a_debug.lib...
SOURCE="$(InputPath)"

BuildCmds= \
	lib \nologo \out:$(OutDir)\libmcrypt_a_debug.lib $(intDir)\*.obj \


"$(OutDir)\libmcrypt_a_debug.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "LibMCrypt_ST - x64 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP BASE Intermediate_Dir "$(OutDir)\objs"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP Intermediate_Dir "$(OutDir)\objs"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /I "..\..\" /I "..\..\lib" /I "..\..\..\..\deps\include" /I ""C:\php-sdk\phpdev\vc9\x86\deps\include"" /Zi /W3 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MBCS" /Gm /Fp"$(IntDir)/libmcrypt.pch" /Fd"$(OutDir)\$(ProjectName)_a_debug.lib" /FR /GZ /c /D_CRT_SECURE_NO_WARNINGS/GX 
# ADD CPP /nologo /MDd /I "..\..\" /I "..\..\lib" /I "..\..\..\..\deps\include" /I ""C:\php-sdk\phpdev\vc9\x86\deps\include"" /Zi /W3 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MBCS" /Gm /Fp"$(IntDir)/libmcrypt.pch" /Fd"$(OutDir)\$(ProjectName)_a_debug.lib" /FR /GZ /c /D_CRT_SECURE_NO_WARNINGS/GX 
# ADD BASE MTL /nologo /D"_DEBUG" /mktyplib203 /tlb"$(PlatformName)\$(ConfigurationName)\libmcrypt.tlb" /win32 
# ADD MTL /nologo /D"_DEBUG" /mktyplib203 /tlb"$(PlatformName)\$(ConfigurationName)\libmcrypt.tlb" /win32 
# ADD BASE RSC /l 2057 /d "_DEBUG" 
# ADD RSC /l 2057 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o "$(OutDir)\objs\libmcrypt.bsc" 
# ADD BSC32 /nologo /o "$(OutDir)\objs\libmcrypt.bsc" 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo 
# ADD LIB32 /nologo 
# Begin Custom Build - Creating static library libmcrypt_a_debug.lib...
SOURCE="$(InputPath)"

BuildCmds= \
	lib \nologo \out:$(OutDir)\libmcrypt_a_debug.lib $(intDir)\*.obj \


"$(OutDir)\libmcrypt_a_debug.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "LibMCrypt_ST - Win32 Release"

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
# ADD BASE CPP /nologo /MD /I "..\..\" /I "..\..\lib" /I "..\..\..\..\deps\include" /W3 /O2 /Ob1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_LIB" /D "_MBCS" /GF /Gy /Fp"$(IntDir)/libmcrypt.pch" /Fd"$(OutDir)/" /c /D_CRT_SECURE_NO_WARNINGS/GX 
# ADD CPP /nologo /MD /I "..\..\" /I "..\..\lib" /I "..\..\..\..\deps\include" /W3 /O2 /Ob1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_LIB" /D "_MBCS" /GF /Gy /Fp"$(IntDir)/libmcrypt.pch" /Fd"$(OutDir)/" /c /D_CRT_SECURE_NO_WARNINGS/GX 
# ADD BASE MTL /nologo /D"NDEBUG" /mktyplib203 /tlb"$(PlatformName)\$(ConfigurationName)\libmcrypt.tlb" /win32 
# ADD MTL /nologo /D"NDEBUG" /mktyplib203 /tlb"$(PlatformName)\$(ConfigurationName)\libmcrypt.tlb" /win32 
# ADD BASE RSC /l 2057 /d "NDEBUG" 
# ADD RSC /l 2057 /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o "$(PlatformName)\$(ConfigurationName)\objs\libmcrypt.bsc" 
# ADD BSC32 /nologo /o "$(PlatformName)\$(ConfigurationName)\objs\libmcrypt.bsc" 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\$(ProjectName)_a.lib" 
# ADD LIB32 /nologo /out:"$(PlatformName)\$(ConfigurationName)\$(ProjectName)_a.lib" 
# Begin Custom Build - Creating static library libmcrypt_a.lib...
SOURCE="$(InputPath)"

BuildCmds= \
	lib \nologo \out:$(OutDir)\libmcrypt_a.lib $(IntDir)\*.obj \


"$(OutDir)\libmcrypt_a.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "LibMCrypt_ST - x64 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP BASE Intermediate_Dir "$(OutDir)\objs"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "$(PlatformName)\$(ConfigurationName)"
# PROP Intermediate_Dir "$(OutDir)\objs"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /I "..\..\" /I "..\..\lib" /I "..\..\..\..\deps\include" /W3 /O2 /Ob1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MBCS" /GF /Gy /Fp"$(IntDir)/libmcrypt.pch" /Fd"$(OutDir)/" /c /D_CRT_SECURE_NO_WARNINGS/GX 
# ADD CPP /nologo /MD /I "..\..\" /I "..\..\lib" /I "..\..\..\..\deps\include" /W3 /O2 /Ob1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MBCS" /GF /Gy /Fp"$(IntDir)/libmcrypt.pch" /Fd"$(OutDir)/" /c /D_CRT_SECURE_NO_WARNINGS/GX 
# ADD BASE MTL /nologo /D"NDEBUG" /mktyplib203 /tlb"$(PlatformName)\$(ConfigurationName)\libmcrypt.tlb" /win32 
# ADD MTL /nologo /D"NDEBUG" /mktyplib203 /tlb"$(PlatformName)\$(ConfigurationName)\libmcrypt.tlb" /win32 
# ADD BASE RSC /l 2057 /d "NDEBUG" 
# ADD RSC /l 2057 /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o "$(OutDir)\objs\libmcrypt.bsc" 
# ADD BSC32 /nologo /o "$(OutDir)\objs\libmcrypt.bsc" 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo 
# ADD LIB32 /nologo 
# Begin Custom Build - Creating static library libmcrypt_a.lib...
SOURCE="$(InputPath)"

BuildCmds= \
	lib \nologo \out:$(OutDir)\libmcrypt_a.lib $(IntDir)\*.obj \


"$(OutDir)\libmcrypt_a.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF

# Begin Target

# Name "LibMCrypt_ST - Win32 Debug"
# Name "LibMCrypt_ST - x64 Debug"
# Name "LibMCrypt_ST - Win32 Release"
# Name "LibMCrypt_ST - x64 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\lib\bzero.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\mcrypt.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\mcrypt_extra.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\mcrypt_modules.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\mcrypt_symb.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\mcrypt_threads.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\win32_comp.c
# End Source File
# Begin Source File

SOURCE=..\..\lib\xmemory.c
# End Source File
# Begin Group "modes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\modules\modes\cbc.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\modes\cfb.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\modes\ctr.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\modes\ecb.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\modes\ncfb.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\modes\nofb.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\modes\ofb.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\modes\stream.c
# End Source File
# End Group
# Begin Group "algorithms"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\modules\algorithms\3-way.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\arcfour.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\blowfish-compat.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\blowfish.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\cast-128.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\cast-256.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\des.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\enigma.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\gost.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\loki97.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\panama.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\rc2.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\rijndael-128.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\rijndael-192.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\rijndael-256.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\safer128.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\safer64.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\saferplus.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\serpent.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\tripledes.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\twofish.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\wake.c
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\xtea.c
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\lib\bzero.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\libdefs.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\mcrypt_internal.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\mcrypt_modules.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\win32_comp.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\xmemory.h
# End Source File
# Begin Group "modes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\modules\modes\cbc.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\modes\cfb.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\modes\ctr.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\modes\ecb.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\modes\ncfb.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\modes\nofb.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\modes\ofb.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\modes\stream.h
# End Source File
# End Group
# Begin Group "algoirthms"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\modules\algorithms\3-way.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\arcfour.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\blowfish.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\cast-128.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\cast-128_sboxes.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\cast-256.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\des.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\enigma.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\panama.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\rc2.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\rijndael.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\safer.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\saferplus.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\serpent.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\tripledes.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\twofish.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\wake.h
# End Source File
# Begin Source File

SOURCE=..\..\modules\algorithms\xtea.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project

