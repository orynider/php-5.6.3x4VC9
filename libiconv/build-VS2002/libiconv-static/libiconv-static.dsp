# Microsoft Developer Studio Project File - Name="libiconv-static" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libiconv-static - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libiconv-static.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libiconv-static.mak" CFG="libiconv-static - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libiconv-static - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libiconv-static - x64 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libiconv-static - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libiconv-static - x64 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libiconv-static - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /I "..\..\include" /I "..\..\lib" /I "..\..\srclib" /ZI /W3 /Od /D "BUILDING_LIBICONV" /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "_DEBUG" /GF /Gm /GZ /c /GX 
# ADD CPP /nologo /MDd /I "..\..\include" /I "..\..\lib" /I "..\..\srclib" /ZI /W3 /Od /D "BUILDING_LIBICONV" /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "_DEBUG" /GF /Gm /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo 
# ADD LIB32 /nologo 

!ELSEIF  "$(CFG)" == "libiconv-static - x64 Debug"

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
# ADD BASE CPP /nologo /MDd /I "..\..\include" /I "..\..\lib" /I "..\..\srclib" /Zi /W3 /Od /D "BUILDING_LIBICONV" /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "_DEBUG" /GF /Gm /GZ /c /GX 
# ADD CPP /nologo /MDd /I "..\..\include" /I "..\..\lib" /I "..\..\srclib" /Zi /W3 /Od /D "BUILDING_LIBICONV" /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "_DEBUG" /GF /Gm /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo 
# ADD LIB32 /nologo 

!ELSEIF  "$(CFG)" == "libiconv-static - Win32 Release"

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
# ADD BASE CPP /nologo /MD /I "..\..\include" /I "..\..\lib" /I "..\..\srclib" /Zi /W3 /O2 /Oi /D "BUILDING_LIBICONV" /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "NDEBUG" /GF /Gy /c /GX 
# ADD CPP /nologo /MD /I "..\..\include" /I "..\..\lib" /I "..\..\srclib" /Zi /W3 /O2 /Oi /D "BUILDING_LIBICONV" /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "NDEBUG" /GF /Gy /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo 
# ADD LIB32 /nologo 

!ELSEIF  "$(CFG)" == "libiconv-static - x64 Release"

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
# ADD BASE CPP /nologo /MD /I "..\..\include" /I "..\..\lib" /I "..\..\srclib" /Zi /W3 /O2 /Oi /D "BUILDING_LIBICONV" /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "NDEBUG" /GF /Gy /c /GX 
# ADD CPP /nologo /MD /I "..\..\include" /I "..\..\lib" /I "..\..\srclib" /Zi /W3 /O2 /Oi /D "BUILDING_LIBICONV" /D "LIBICONV_STATIC" /D "_CRT_SECURE_NO_WARNINGS" /D "NDEBUG" /GF /Gy /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo 
# ADD LIB32 /nologo 

!ENDIF

# Begin Target

# Name "libiconv-static - Win32 Debug"
# Name "libiconv-static - x64 Debug"
# Name "libiconv-static - Win32 Release"
# Name "libiconv-static - x64 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx"
# Begin Group "lib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\lib\iconv.c
# End Source File
# End Group
# Begin Group "libcharset"

# PROP Default_Filter ""
# Begin Group "lib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\libcharset\lib\localcharset.c
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
# Begin Group "lib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\lib\aliases.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\aliases2.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\aliases_aix.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\aliases_aix_sysaix.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\aliases_dos.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\aliases_extra.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\aliases_osf1.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\aliases_osf1_sysosf1.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\aliases_sysaix.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\aliases_syshpux.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\aliases_sysosf1.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\aliases_syssolaris.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\armscii_8.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\ascii.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\atarist.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\big5.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\big5_2003.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\big5hkscs1999.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\big5hkscs2001.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\big5hkscs2004.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\big5hkscs2008.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\c99.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\canonical.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\canonical_aix.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\canonical_aix_sysaix.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\canonical_dos.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\canonical_extra.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\canonical_local.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\canonical_local_sysaix.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\canonical_local_syshpux.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\canonical_local_sysosf1.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\canonical_local_syssolaris.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\canonical_osf1.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\canonical_osf1_sysosf1.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\canonical_sysaix.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\canonical_syshpux.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\canonical_sysosf1.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\canonical_syssolaris.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\ces_big5.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\ces_gbk.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cjk_variants.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cns11643.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cns11643_1.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cns11643_15.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cns11643_2.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cns11643_3.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cns11643_4.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cns11643_4a.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cns11643_4b.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cns11643_5.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cns11643_6.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cns11643_7.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cns11643_inv.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\config.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\converters.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp1046.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp1124.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp1125.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp1129.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp1131.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp1133.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp1161.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp1162.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp1163.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp1250.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp1251.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp1252.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp1253.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp1254.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp1255.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp1256.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp1257.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp1258.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp437.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp737.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp775.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp850.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp852.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp853.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp855.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp856.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp857.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp858.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp860.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp861.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp862.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp863.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp864.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp865.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp866.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp869.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp874.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp922.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp932.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp932ext.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp936.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp936ext.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp943.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp949.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp950.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\cp950ext.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\dec_hanyu.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\dec_kanji.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\encodings.def
# End Source File
# Begin Source File

SOURCE=..\..\lib\encodings_aix.def
# End Source File
# Begin Source File

SOURCE=..\..\lib\encodings_dos.def
# End Source File
# Begin Source File

SOURCE=..\..\lib\encodings_extra.def
# End Source File
# Begin Source File

SOURCE=..\..\lib\encodings_local.def
# End Source File
# Begin Source File

SOURCE=..\..\lib\encodings_osf1.def
# End Source File
# Begin Source File

SOURCE=..\..\lib\euc_cn.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\euc_jisx0213.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\euc_jp.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\euc_kr.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\euc_tw.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\flags.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\flushwc.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\gb18030.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\gb18030ext.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\gb18030uni.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\gb2312.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\gbk.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\gbkext1.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\gbkext2.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\gbkext_inv.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\georgian_academy.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\georgian_ps.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\hkscs1999.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\hkscs2001.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\hkscs2004.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\hkscs2008.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\hp_roman8.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\hz.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iconv_open1.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iconv_open2.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso2022_cn.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso2022_cnext.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso2022_jp.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso2022_jp1.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso2022_jp2.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso2022_jp3.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso2022_kr.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso646_cn.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso646_jp.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso8859_1.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso8859_10.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso8859_11.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso8859_13.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso8859_14.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso8859_15.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso8859_16.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso8859_2.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso8859_3.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso8859_4.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso8859_5.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso8859_6.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso8859_7.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso8859_8.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\iso8859_9.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\isoir165.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\isoir165ext.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\java.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\jisx0201.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\jisx0208.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\jisx0212.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\jisx0213.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\johab.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\johab_hangul.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\koi8_r.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\koi8_ru.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\koi8_t.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\koi8_u.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\ksc5601.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\loop_unicode.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\loop_wchar.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\loops.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\mac_arabic.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\mac_centraleurope.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\mac_croatian.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\mac_cyrillic.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\mac_greek.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\mac_hebrew.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\mac_iceland.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\mac_roman.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\mac_romania.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\mac_thai.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\mac_turkish.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\mac_ukraine.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\mulelao.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\nextstep.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\pt154.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\riscos1.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\rk1048.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\shift_jisx0213.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\sjis.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\tcvn.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\tds565.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\tis620.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\translit.def
# End Source File
# Begin Source File

SOURCE=..\..\lib\translit.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\ucs2.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\ucs2be.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\ucs2internal.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\ucs2le.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\ucs2swapped.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\ucs4.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\ucs4be.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\ucs4internal.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\ucs4le.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\ucs4swapped.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\uhc_1.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\uhc_2.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\utf16.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\utf16be.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\utf16le.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\utf32.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\utf32be.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\utf32le.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\utf7.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\utf8.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\vietcomb.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\viscii.h
# End Source File
# End Group
# Begin Group "srclib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\srclib\localcharset.h
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
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx;tiff;tif;png;wav"
# End Group
# End Target
# End Project

