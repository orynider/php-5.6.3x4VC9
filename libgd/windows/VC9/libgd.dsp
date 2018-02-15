# Microsoft Developer Studio Project File - Name="libgd2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=libgd2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libgd2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libgd2.mak" CFG="libgd2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libgd2 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "libgd2 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libgd2 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "libgd2___Win32_Release"
# PROP BASE Intermediate_Dir "libgd2___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\gdbuild\/"
# PROP Intermediate_Dir "..\..\..\gdbuild\/"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MSWIN32" /D "BGDWIN32" /D "HAVE_FT2BUILD_H" /D "HAVE_GD_H" /D "HAVE_ICONV_H" /D "HAVE_LIBFREETYPE" /D "HAVE_LIBJPEG" /D "HAVE_LIBPNG" /D "HAVE_LIBWEBP" /D "HAVE_LIBZ" /D "HAVE_LIBXPM" /D "HAVE_LIBTIFF" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# Begin Custom Build - Creating static library libgd2_a.lib...
InputPath=..\..\..\gdbuild\libgd2.dll
SOURCE="$(InputPath)"

"..\..\..\gdbuild\libgd2_a.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	lib /nologo /out:..\..\..\gdbuild\libgd2_a.lib ..\..\..\gdbuild\*.obj

# End Custom Build

!ELSEIF  "$(CFG)" == "libgd2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libgd2___Win32_Debug"
# PROP BASE Intermediate_Dir "libgd2___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\gdbuild\/"
# PROP Intermediate_Dir "..\..\..\gdbuild\/"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MSWIN32" /D "BGDWIN32" /D "HAVE_FT2BUILD_H" /D "HAVE_GD_H" /D "HAVE_ICONV_H" /D "HAVE_LIBFREETYPE" /D "HAVE_LIBJPEG" /D "HAVE_LIBPNG" /D "HAVE_LIBWEBP" /D "HAVE_LIBZ" /D "HAVE_LIBXPM" /D "HAVE_LIBTIFF" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Creating static library libgd2_a.lib...
InputPath=..\..\..\gdbuild\libgd2.dll
SOURCE="$(InputPath)"

"..\..\..\gdbuild\libgd2_a.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	lib /nologo /out:..\..\..\gdbuild\libgd2_a.lib ..\..\..\gdbuild\*.obj

# End Custom Build

!ENDIF 

# Begin Target

# Name "libgd2 - Win32 Release"
# Name "libgd2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File
SOURCE=..\..\src\gd.c
# End Source File
# Begin Source File
SOURCE=..\..\src\gd_bmp.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_color.c
# End Source File
# Begin Source File
SOURCE=..\..\src\gd_color_map.c
# End Source File
# Begin Source File
SOURCE=..\..\src\gd_color_match.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_crop.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_filename.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_filter.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_gd.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_gd2.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_gif_in.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_gif_out.c
# End Source File
# Begin Source File
SOURCE=..\..\src\gd_interpolation.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_io.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_io_dp.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_io_file.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_io_ss.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_io_stream.cxx
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_jpeg.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_matrix.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_nnquant.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_png.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_rotate.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_security.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_ss.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_tga.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_tiff.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_topal.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_transform.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_version.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_wbmp.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_webp.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_xbm.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gdcache.c
# End Source File
# Begin Source File
SOURCE=..\..\src\gdfontg.c
# End Source File
# Begin Source File
SOURCE=..\..\src\gdfontl.c
# End Source File
# Begin Source File
SOURCE=..\..\src\gdfontmb.c
# End Source File
# Begin Source File
SOURCE=..\..\src\gdfonts.c
# End Source File
# Begin Source File
SOURCE=..\..\src\gdfontt.c
# End Source File
# Begin Source File
SOURCE=..\..\src\gdft.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gdfx.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gdhelpers.c
# End Source File
# Begin Source File
SOURCE=..\..\src\gdkanji.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gdpp.cxx
# End Source File
# Begin Source File	
SOURCE=..\..\src\gdtables.c
# End Source File
# Begin Source File	
SOURCE=..\..\src\gdxpm.c
# End Source File
# Begin Source File
SOURCE=..\..\src\wbmp.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File
SOURCE=..\..\src\gd.h
# End Source File
# Begin Source File
SOURCE=..\..\src\entities.h
# End Source File
# Begin Source File
SOURCE=..\..\src\bmp.h
# End Source File
# Begin Source File
SOURCE=..\..\src\gd.h
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_color.h
# End Source File
# Begin Source File
SOURCE=..\..\src\gd_color_map.h
# End Source File
# Begin Source File
SOURCE=..\..\src\gd_errors.h
# End Source File
# Begin Source File	
SOURCE=..\..\src\gd_intern.h
# End Source File
# Begin Source File
SOURCE=..\..\src\gd_io.h
# End Source File
# Begin Source File
SOURCE=..\..\src\gd_io_stream.h
# End Source File
# Begin Source File
SOURCE=..\..\src\gd_nnquant.h
# End Source File
# Begin Source File
SOURCE=..\..\src\gd_tga.h
# End Source File
# Begin Source File
SOURCE=..\..\src\gdcache.h
# End Source File
# Begin Source File
SOURCE=..\..\src\gdfontg.h
# End Source File
# Begin Source File
SOURCE=..\..\src\gdfontl.h
# End Source File
# Begin Source File
SOURCE=..\..\src\gdfontmb.h
# End Source File
# Begin Source File
SOURCE=..\..\src\gdfonts.h
# End Source File
# Begin Source File
SOURCE=..\..\src\gdfontt.h
# End Source File
# Begin Source File
SOURCE=..\..\src\gdfx.h
# End Source File
# Begin Source File
SOURCE=..\..\src\gdhelpers.h
# End Source File
# Begin Source File
SOURCE=..\..\src\gdpp.h
# End Source File
# Begin Source File
SOURCE=..\..\src\jisx0208.h
# End Source File
# Begin Source File
SOURCE=..\..\src\wbmp.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
