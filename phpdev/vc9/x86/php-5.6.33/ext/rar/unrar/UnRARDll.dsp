# Microsoft Developer Studio Project File - Name="UnRAR" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=UnRAR - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UnRAR.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UnRAR.mak" CFG="UnRAR - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UnRAR - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UnRAR - x64 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UnRAR - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UnRAR - x64 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UnRAR - Win32 release_nocrypt" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UnRAR - x64 release_nocrypt" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UnRAR - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "build\unrardll32\$(ConfigurationName)"
# PROP BASE Intermediate_Dir "build\unrardll32\$(ConfigurationName)\obj"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "build\unrardll32\$(ConfigurationName)"
# PROP Intermediate_Dir "build\unrardll32\$(ConfigurationName)\obj"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /ZI /W3 /Od /D "RARDLL" /D "UNRAR" /D "SILENT" /D "_MBCS" /Zp4 /YX /Gd /GZ /c  
# ADD CPP /nologo /MTd /ZI /W3 /Od /D "RARDLL" /D "UNRAR" /D "SILENT" /D "_MBCS" /Zp4 /YX /Gd /GZ /c  
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:"build\unrardll32\$(ConfigurationName)\unrar.dll" /incremental:yes /def:"dll.def" /debug /pdbtype:sept /subsystem:console /machine:ix86 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:"build\unrardll32\$(ConfigurationName)\unrar.dll" /incremental:yes /def:"dll.def" /debug /pdbtype:sept /subsystem:console /machine:ix86 

!ELSEIF  "$(CFG)" == "UnRAR - x64 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "build\unrardll64\$(ConfigurationName)"
# PROP BASE Intermediate_Dir "build\unrardll64\$(ConfigurationName)\obj"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "build\unrardll64\$(ConfigurationName)"
# PROP Intermediate_Dir "build\unrardll64\$(ConfigurationName)\obj"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /Zi /W3 /Od /D "RARDLL" /D "UNRAR" /D "SILENT" /D "_MBCS" /Zp4 /YX /Gd /GZ /c  
# ADD CPP /nologo /MTd /Zi /W3 /Od /D "RARDLL" /D "UNRAR" /D "SILENT" /D "_MBCS" /Zp4 /YX /Gd /GZ /c  
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:"build\unrardll64\$(ConfigurationName)\unrar64.dll" /incremental:yes /def:"dll.def" /debug /pdbtype:sept /subsystem:console 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:"build\unrardll64\$(ConfigurationName)\unrar64.dll" /incremental:yes /def:"dll.def" /debug /pdbtype:sept /subsystem:console 

!ELSEIF  "$(CFG)" == "UnRAR - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "build\unrardll32\$(ConfigurationName)"
# PROP BASE Intermediate_Dir "build\unrardll32\$(ConfigurationName)\obj"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "build\unrardll32\$(ConfigurationName)"
# PROP Intermediate_Dir "build\unrardll32\$(ConfigurationName)\obj"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /Zi /W3 /O2 /Oi /Oy /D "RARDLL" /D "UNRAR" /D "SILENT" /D "_MBCS" /Zp4 /Gy /YX /Gd /c  
# ADD CPP /nologo /MT /Zi /W3 /O2 /Oi /Oy /D "RARDLL" /D "UNRAR" /D "SILENT" /D "_MBCS" /Zp4 /Gy /YX /Gd /c  
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:"build\unrardll32\$(ConfigurationName)\unrar.dll" /incremental:no /def:"dll.def" /debug /pdbtype:sept /subsystem:console /opt:ref /opt:icf /machine:ix86 /SAFESEH
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:"build\unrardll32\$(ConfigurationName)\unrar.dll" /incremental:no /def:"dll.def" /debug /pdbtype:sept /subsystem:console /opt:ref /opt:icf /machine:ix86 /SAFESEH

!ELSEIF  "$(CFG)" == "UnRAR - x64 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "build\unrardll64\$(ConfigurationName)"
# PROP BASE Intermediate_Dir "build\unrardll64\$(ConfigurationName)\obj"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "build\unrardll64\$(ConfigurationName)"
# PROP Intermediate_Dir "build\unrardll64\$(ConfigurationName)\obj"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /Zi /W3 /O2 /Oi /Oy /D "RARDLL" /D "UNRAR" /D "SILENT" /D "_MBCS" /Zp4 /Gy /YX /Gd /c  
# ADD CPP /nologo /MT /Zi /W3 /O2 /Oi /Oy /D "RARDLL" /D "UNRAR" /D "SILENT" /D "_MBCS" /Zp4 /Gy /YX /Gd /c  
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:"build\unrardll64\$(ConfigurationName)\unrar64.dll" /incremental:no /def:"dll.def" /debug /pdbtype:sept /subsystem:console /opt:ref /opt:icf 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:"build\unrardll64\$(ConfigurationName)\unrar64.dll" /incremental:no /def:"dll.def" /debug /pdbtype:sept /subsystem:console /opt:ref /opt:icf 

!ELSEIF  "$(CFG)" == "UnRAR - Win32 release_nocrypt"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "build\unrardll32\$(ConfigurationName)"
# PROP BASE Intermediate_Dir "build\unrardll32\$(ConfigurationName)\obj"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "build\unrardll32\$(ConfigurationName)"
# PROP Intermediate_Dir "build\unrardll32\$(ConfigurationName)\obj"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /Zi /W3 /O2 /Oi /Oy /D "RARDLL" /D "UNRAR" /D "SILENT" /D "RAR_NOCRYPT" /D "_MBCS" /Zp4 /Gy /YX /Gd /c  
# ADD CPP /nologo /MT /Zi /W3 /O2 /Oi /Oy /D "RARDLL" /D "UNRAR" /D "SILENT" /D "RAR_NOCRYPT" /D "_MBCS" /Zp4 /Gy /YX /Gd /c  
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:"build\unrardll32\$(ConfigurationName)\unrar_nocrypt.dll" /incremental:no /def:"dll_nocrypt.def" /debug /pdbtype:sept /subsystem:console /opt:ref /opt:icf /machine:ix86 /SAFESEH
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:"build\unrardll32\$(ConfigurationName)\unrar_nocrypt.dll" /incremental:no /def:"dll_nocrypt.def" /debug /pdbtype:sept /subsystem:console /opt:ref /opt:icf /machine:ix86 /SAFESEH

!ELSEIF  "$(CFG)" == "UnRAR - x64 release_nocrypt"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "build\unrardll64\$(ConfigurationName)"
# PROP BASE Intermediate_Dir "build\unrardll64\$(ConfigurationName)\obj"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "build\unrardll64\$(ConfigurationName)"
# PROP Intermediate_Dir "build\unrardll64\$(ConfigurationName)\obj"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /Zi /W3 /O2 /Oi /Oy /D "RARDLL" /D "UNRAR" /D "SILENT" /D "RAR_NOCRYPT" /D "_MBCS" /Zp4 /Gy /YX /Gz /c  
# ADD CPP /nologo /MT /Zi /W3 /O2 /Oi /Oy /D "RARDLL" /D "UNRAR" /D "SILENT" /D "RAR_NOCRYPT" /D "_MBCS" /Zp4 /Gy /YX /Gz /c  
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:"build\unrardll64\$(ConfigurationName)\unrar64_nocrypt.dll" /incremental:no /def:"dll_nocrypt.def" /debug /pdbtype:sept /subsystem:console /opt:ref /opt:icf 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /out:"build\unrardll64\$(ConfigurationName)\unrar64_nocrypt.dll" /incremental:no /def:"dll_nocrypt.def" /debug /pdbtype:sept /subsystem:console /opt:ref /opt:icf 

!ENDIF

# Begin Target

# Name "UnRAR - Win32 Debug"
# Name "UnRAR - x64 Debug"
# Name "UnRAR - Win32 Release"
# Name "UnRAR - x64 Release"
# Name "UnRAR - Win32 release_nocrypt"
# Name "UnRAR - x64 release_nocrypt"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx"
# Begin Source File

SOURCE=archive.cpp
# End Source File
# Begin Source File

SOURCE=arcread.cpp
# End Source File
# Begin Source File

SOURCE=blake2s.cpp
# End Source File
# Begin Source File

SOURCE=cmddata.cpp
# End Source File
# Begin Source File

SOURCE=consio.cpp
# End Source File
# Begin Source File

SOURCE=crc.cpp
# End Source File
# Begin Source File

SOURCE=crypt.cpp
# End Source File
# Begin Source File

SOURCE=dll.cpp
# End Source File
# Begin Source File

SOURCE=encname.cpp
# End Source File
# Begin Source File

SOURCE=errhnd.cpp
# End Source File
# Begin Source File

SOURCE=extinfo.cpp
# End Source File
# Begin Source File

SOURCE=extract.cpp
# End Source File
# Begin Source File

SOURCE=filcreat.cpp
# End Source File
# Begin Source File

SOURCE=file.cpp
# End Source File
# Begin Source File

SOURCE=filefn.cpp
# End Source File
# Begin Source File

SOURCE=filestr.cpp
# End Source File
# Begin Source File

SOURCE=find.cpp
# End Source File
# Begin Source File

SOURCE=getbits.cpp
# End Source File
# Begin Source File

SOURCE=global.cpp

!IF  "$(CFG)" == "UnRAR - Win32 Debug"

# ADD CPP /nologo /GZ /GX 
# SUBTRACT CPP /YX /Yc /Yu
!ELSEIF  "$(CFG)" == "UnRAR - x64 Debug"

# ADD CPP /nologo /GZ /GX 
# SUBTRACT CPP /YX /Yc /Yu
!ELSEIF  "$(CFG)" == "UnRAR - Win32 Release"

# ADD CPP /nologo /GX 
# SUBTRACT CPP /YX /Yc /Yu
!ELSEIF  "$(CFG)" == "UnRAR - x64 Release"

# ADD CPP /nologo /GX 
# SUBTRACT CPP /YX /Yc /Yu
!ELSEIF  "$(CFG)" == "UnRAR - Win32 release_nocrypt"

# ADD CPP /nologo /GX 
# SUBTRACT CPP /YX /Yc /Yu
!ELSEIF  "$(CFG)" == "UnRAR - x64 release_nocrypt"

# ADD CPP /nologo /GX 
# SUBTRACT CPP /YX /Yc /Yu
!ENDIF

# End Source File
# Begin Source File

SOURCE=hash.cpp
# End Source File
# Begin Source File

SOURCE=headers.cpp
# End Source File
# Begin Source File

SOURCE=isnt.cpp
# End Source File
# Begin Source File

SOURCE=match.cpp
# End Source File
# Begin Source File

SOURCE=options.cpp
# End Source File
# Begin Source File

SOURCE=pathfn.cpp
# End Source File
# Begin Source File

SOURCE=qopen.cpp
# End Source File
# Begin Source File

SOURCE=rar.cpp
# End Source File
# Begin Source File

SOURCE=rarpch.cpp

!IF  "$(CFG)" == "UnRAR - Win32 Debug"

# ADD CPP /nologo /Yc"rar.hpp" /GZ /GX 
!ELSEIF  "$(CFG)" == "UnRAR - x64 Debug"

# ADD CPP /nologo /Yc"rar.hpp" /GZ /GX 
!ELSEIF  "$(CFG)" == "UnRAR - Win32 Release"

# ADD CPP /nologo /Yc"rar.hpp" /GX 
!ELSEIF  "$(CFG)" == "UnRAR - x64 Release"

# ADD CPP /nologo /Yc"rar.hpp" /GX 
!ELSEIF  "$(CFG)" == "UnRAR - Win32 release_nocrypt"

# ADD CPP /nologo /Yc"rar.hpp" /GX 
!ELSEIF  "$(CFG)" == "UnRAR - x64 release_nocrypt"

# ADD CPP /nologo /Yc"rar.hpp" /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=rarvm.cpp
# End Source File
# Begin Source File

SOURCE=rawread.cpp
# End Source File
# Begin Source File

SOURCE=rdwrfn.cpp
# End Source File
# Begin Source File

SOURCE=rijndael.cpp
# End Source File
# Begin Source File

SOURCE=rs.cpp
# End Source File
# Begin Source File

SOURCE=rs16.cpp
# End Source File
# Begin Source File

SOURCE=scantree.cpp
# End Source File
# Begin Source File

SOURCE=secpassword.cpp
# End Source File
# Begin Source File

SOURCE=sha1.cpp
# End Source File
# Begin Source File

SOURCE=sha256.cpp
# End Source File
# Begin Source File

SOURCE=smallfn.cpp
# End Source File
# Begin Source File

SOURCE=strfn.cpp
# End Source File
# Begin Source File

SOURCE=strlist.cpp
# End Source File
# Begin Source File

SOURCE=system.cpp
# End Source File
# Begin Source File

SOURCE=threadpool.cpp
# End Source File
# Begin Source File

SOURCE=timefn.cpp
# End Source File
# Begin Source File

SOURCE=ui.cpp
# End Source File
# Begin Source File

SOURCE=unicode.cpp
# End Source File
# Begin Source File

SOURCE=unpack.cpp
# End Source File
# Begin Source File

SOURCE=volume.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;inc;xsd"
# Begin Source File

SOURCE=rar.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx;tiff;tif;png;wav"
# Begin Source File

SOURCE=dll.rc
# End Source File
# End Group
# End Target
# End Project

