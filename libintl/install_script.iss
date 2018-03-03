;InnoSetupVersion=5.0.4

[Setup]
AppName=LibIntl
AppVerName=LibIntl-0.14.4 (library for native language support; Complete package, except sources)
AppVersion=0.14.4
AppPublisher=GnuWin32
AppPublisherURL=http://gnuwin32.sourceforge.net
AppSupportURL=http://sourceforge.net/forum/forum.php?forum_id=74807
AppUpdatesURL=http://gnuwin32.sourceforge.net/packages/libintl.htm
DefaultDirName={reg:HKLM\Software\GnuWin32\LibIntl\0.14.4\pck,InstallPath|{reg:HKLM\Software\GnuWin32\LibIntl\0.14.4,InstallPath|{reg:HKLM\Software\GnuWin32\LibIntl,InstallPath|{reg:HKLM\Software\GnuWin32,InstallPath|{pf}\GnuWin32}}}}
DefaultGroupName=GnuWin32\LibIntl
UninstallDisplayName=GnuWin32: LibIntl version 0.14.4
UninstallFilesDir={app}\uninstall
OutputBaseFilename=libintl-0.14.4
Compression=lzma
PrivilegesRequired=none
AllowNoIcons=yes
LicenseFile=embedded\License.txt
WizardImageFile=embedded\WizardImage.bmp
WizardSmallImageFile=embedded\WizardSmallImage.bmp
;TimeStampsInUTC=yes

[Files]
Source: "{app}\bin\libintl3.dll"; DestDir: "{app}\bin"; Components: bin; Flags: overwritereadonly 
Source: "{app}\contrib\libintl\0.14.4\depends-GnuWin32.lst"; DestDir: "{app}\contrib\libintl\0.14.4"; Components: bin; Flags: overwritereadonly 
Source: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src\AUTHORS"; DestDir: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src"; Components: bin; Flags: overwritereadonly 
Source: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src\ChangeLog"; DestDir: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src"; Components: bin; Flags: overwritereadonly 
Source: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src\COPYING"; DestDir: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src"; Components: bin; Flags: overwritereadonly 
Source: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src\INSTALL"; DestDir: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src"; Components: bin; Flags: overwritereadonly 
Source: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src\NEWS"; DestDir: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src"; Components: bin; Flags: overwritereadonly 
Source: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src\README"; DestDir: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src"; Components: bin; Flags: overwritereadonly 
Source: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src\README.mingw"; DestDir: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src"; Components: bin; Flags: overwritereadonly 
Source: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src\README.vms"; DestDir: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src"; Components: bin; Flags: overwritereadonly 
Source: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src\README.woe32"; DestDir: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src"; Components: bin; Flags: overwritereadonly 
Source: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src\THANKS"; DestDir: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src"; Components: bin; Flags: overwritereadonly 
Source: "{app}\manifest\libintl-0.14.4-bin.mft"; DestDir: "{app}\manifest"; Components: bin; Flags: overwritereadonly 
Source: "{app}\manifest\libintl-0.14.4-bin.ver"; DestDir: "{app}\manifest"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\aclocal\lib-ld.m4"; DestDir: "{app}\share\aclocal"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\aclocal\lib-link.m4"; DestDir: "{app}\share\aclocal"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\aclocal\lib-prefix.m4"; DestDir: "{app}\share\aclocal"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\ABOUT-NLS"; DestDir: "{app}\share\gettext"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\bindtextdom.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\ChangeLog"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\config.charset"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\COPYING.LIB-2.0"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\COPYING.LIB-2.1"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\dcgettext.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\dcigettext.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\dcngettext.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\dgettext.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\dngettext.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\explodename.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\finddomain.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\gettext.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\intl-compat.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\l10nflist.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\langprefs.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\libgnuintl.h.in"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\loadmsgcat.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\localcharset.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\locale.alias"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\localealias.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\localename.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\log.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\Makefile.in"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\ngettext.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\os2compat.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\osdep.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\plural-exp.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\plural.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\plural.y"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\printf-args.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\printf-parse.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\printf.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\ref-add.sin"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\ref-del.sin"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\relocatable.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\textdomain.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\vasnprintf.c"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\VERSION"; DestDir: "{app}\share\gettext\intl"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\be\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\be\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\ca\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\ca\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\cs\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\cs\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\da\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\da\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\de\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\de\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\el\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\el\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\en@boldquot\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\en@boldquot\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\en@quot\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\en@quot\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\es\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\es\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\et\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\et\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\fi\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\fi\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\fr\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\fr\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\ga\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\ga\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\gl\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\gl\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\id\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\id\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\it\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\it\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\ja\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\ja\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\ko\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\ko\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\locale.alias"; DestDir: "{app}\share\locale"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\nl\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\nl\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\nn\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\nn\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\no\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\no\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\pl\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\pl\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\pt\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\pt\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\pt_BR\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\pt_BR\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\ro\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\ro\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\ru\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\ru\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\sk\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\sk\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\sl\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\sl\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\sr\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\sr\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\sv\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\sv\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\tr\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\tr\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\uk\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\uk\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\vi\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\vi\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\zh_CN\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\zh_CN\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\share\locale\zh_TW\LC_MESSAGES\gettext-runtime.mo"; DestDir: "{app}\share\locale\zh_TW\LC_MESSAGES"; Components: bin; Flags: overwritereadonly 
Source: "{app}\bin\libiconv2.dll"; DestDir: "{app}\bin"; Components: bin; Flags: overwritereadonly 
Source: "{app}\manifest\libintl-0.14.4-dep.ver"; DestDir: "{app}\manifest"; Components: bin; Flags: overwritereadonly 
Source: "{app}\manifest\libintl-0.14.4-dep.mft"; DestDir: "{app}\manifest"; Components: bin; Flags: overwritereadonly 
Source: "{app}\doc\libintl\tutorial.html"; DestDir: "{app}\doc\libintl"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\html\bind_textdomain_codeset.3.html"; DestDir: "{app}\man\html"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\html\bindtextdomain.3.html"; DestDir: "{app}\man\html"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\html\dcgettext.3.html"; DestDir: "{app}\man\html"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\html\dcngettext.3.html"; DestDir: "{app}\man\html"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\html\dgettext.3.html"; DestDir: "{app}\man\html"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\html\dngettext.3.html"; DestDir: "{app}\man\html"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\html\gettext.3.html"; DestDir: "{app}\man\html"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\html\ngettext.3.html"; DestDir: "{app}\man\html"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\html\textdomain.3.html"; DestDir: "{app}\man\html"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\man3\bind_textdomain_codeset.3"; DestDir: "{app}\man\man3"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\man3\bindtextdomain.3"; DestDir: "{app}\man\man3"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\man3\dcgettext.3"; DestDir: "{app}\man\man3"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\man3\dcngettext.3"; DestDir: "{app}\man\man3"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\man3\dgettext.3"; DestDir: "{app}\man\man3"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\man3\dngettext.3"; DestDir: "{app}\man\man3"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\man3\gettext.3"; DestDir: "{app}\man\man3"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\man3\ngettext.3"; DestDir: "{app}\man\man3"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\man3\textdomain.3"; DestDir: "{app}\man\man3"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\pdf\libintl-man.pdf"; DestDir: "{app}\man\pdf"; Components: doc; Flags: overwritereadonly 
Source: "{app}\man\ps\libintl-man.ps.gz"; DestDir: "{app}\man\ps"; Components: doc; Flags: overwritereadonly 
Source: "{app}\manifest\libintl-0.14.4-doc.mft"; DestDir: "{app}\manifest"; Components: doc; Flags: overwritereadonly 
Source: "{app}\manifest\libintl-0.14.4-doc.ver"; DestDir: "{app}\manifest"; Components: doc; Flags: overwritereadonly 
Source: "{app}\include\libintl.h"; DestDir: "{app}\include"; Components: lib; Flags: overwritereadonly 
Source: "{app}\lib\libintl-bcc.lib"; DestDir: "{app}\lib"; Components: lib; Flags: overwritereadonly 
Source: "{app}\lib\libintl.def"; DestDir: "{app}\lib"; Components: lib; Flags: overwritereadonly 
Source: "{app}\lib\libintl.dll.a"; DestDir: "{app}\lib"; Components: lib; Flags: overwritereadonly 
Source: "{app}\lib\libintl.lib"; DestDir: "{app}\lib"; Components: lib; Flags: overwritereadonly 
Source: "{app}\manifest\libintl-0.14.4-lib.mft"; DestDir: "{app}\manifest"; Components: lib; Flags: overwritereadonly 
Source: "{app}\manifest\libintl-0.14.4-lib.ver"; DestDir: "{app}\manifest"; Components: lib; Flags: overwritereadonly 
Source: "{app}\share\gettext\gettext.h"; DestDir: "{app}\share\gettext"; Components: lib; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\eval-plural.h"; DestDir: "{app}\share\gettext\intl"; Components: lib; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\gettextP.h"; DestDir: "{app}\share\gettext\intl"; Components: lib; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\gmo.h"; DestDir: "{app}\share\gettext\intl"; Components: lib; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\hash-string.h"; DestDir: "{app}\share\gettext\intl"; Components: lib; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\loadinfo.h"; DestDir: "{app}\share\gettext\intl"; Components: lib; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\localcharset.h"; DestDir: "{app}\share\gettext\intl"; Components: lib; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\os2compat.h"; DestDir: "{app}\share\gettext\intl"; Components: lib; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\plural-exp.h"; DestDir: "{app}\share\gettext\intl"; Components: lib; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\printf-args.h"; DestDir: "{app}\share\gettext\intl"; Components: lib; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\printf-parse.h"; DestDir: "{app}\share\gettext\intl"; Components: lib; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\relocatable.h"; DestDir: "{app}\share\gettext\intl"; Components: lib; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\vasnprintf.h"; DestDir: "{app}\share\gettext\intl"; Components: lib; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\vasnwprintf.h"; DestDir: "{app}\share\gettext\intl"; Components: lib; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\wprintf-parse.h"; DestDir: "{app}\share\gettext\intl"; Components: lib; Flags: overwritereadonly 
Source: "{app}\share\gettext\intl\xsize.h"; DestDir: "{app}\share\gettext\intl"; Components: lib; Flags: overwritereadonly 

[Dirs]
Name: "{app}\bin"; Flags: uninsalwaysuninstall 
Name: "{app}\contrib\libintl\0.14.4"; Flags: uninsalwaysuninstall 
Name: "{app}\contrib\libintl\0.14.4\libintl-0.14.4-src"; Flags: uninsalwaysuninstall 
Name: "{app}\include"; Flags: uninsalwaysuninstall 
Name: "{app}\lib"; Flags: uninsalwaysuninstall 
Name: "{app}\man\cat1"; Flags: uninsalwaysuninstall 
Name: "{app}\man\cat3"; Flags: uninsalwaysuninstall 
Name: "{app}\share"; Flags: uninsalwaysuninstall 
Name: "{app}\share\aclocal"; Flags: uninsalwaysuninstall 
Name: "{app}\share\gettext"; Flags: uninsalwaysuninstall 
Name: "{app}\share\gettext\intl"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\be"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\be\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\ca"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\ca\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\cs"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\cs\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\da"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\da\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\de"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\de\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\el"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\el\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\en@boldquot"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\en@boldquot\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\en@quot"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\en@quot\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\es"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\es\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\et"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\et\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\fi"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\fi\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\fr"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\fr\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\ga"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\ga\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\gl"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\gl\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\id"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\id\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\it"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\it\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\ja"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\ja\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\ko"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\ko\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\nl"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\nl\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\nn"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\nn\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\no"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\no\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\pl"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\pl\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\pt"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\pt\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\pt_BR"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\pt_BR\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\ro"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\ro\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\ru"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\ru\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\sk"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\sk\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\sl"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\sl\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\sr"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\sr\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\sv"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\sv\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\tr"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\tr\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\uk"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\uk\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\vi"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\vi\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\zh_CN"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\zh_CN\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\zh_TW"; Flags: uninsalwaysuninstall 
Name: "{app}\share\locale\zh_TW\LC_MESSAGES"; Flags: uninsalwaysuninstall 
Name: "{app}\doc"; Flags: uninsalwaysuninstall 
Name: "{app}\doc\libintl"; Flags: uninsalwaysuninstall 
Name: "{app}\doc\libintl\0.14.4"; Flags: uninsalwaysuninstall 
Name: "{app}\doc\libintl\0.14.4\libintl-0.14.4"; Flags: uninsalwaysuninstall 
Name: "{app}\man\cat1"; Flags: uninsalwaysuninstall 
Name: "{app}\man\cat3"; Flags: uninsalwaysuninstall 
Name: "{app}\man\html"; Flags: uninsalwaysuninstall 
Name: "{app}\man\man1"; Flags: uninsalwaysuninstall 
Name: "{app}\man\man3"; Flags: uninsalwaysuninstall 
Name: "{app}\man\pdf"; Flags: uninsalwaysuninstall 
Name: "{app}\man\ps"; Flags: uninsalwaysuninstall 

[Registry]
Root: HKLM; Subkey: "Software\GnuWin32"; Flags: uninsdeletekeyifempty 
Root: HKLM; Subkey: "Software\GnuWin32"; ValueName: "InstallPath"; ValueType: String; ValueData: "{app}"; 
Root: HKLM; Subkey: "Software\GnuWin32\LibIntl"; Flags: uninsdeletekeyifempty 
Root: HKLM; Subkey: "Software\GnuWin32\LibIntl\0.14.4"; Flags: uninsdeletekeyifempty 
Root: HKLM; Subkey: "Software\GnuWin32\LibIntl\0.14.4\pck"; Flags: uninsdeletekey 
Root: HKLM; Subkey: "Software\GnuWin32\LibIntl"; ValueName: "InstallPath"; ValueType: String; ValueData: "{app}"; Flags: uninsdeletevalue 
Root: HKLM; Subkey: "Software\GnuWin32\LibIntl\0.14.4"; ValueName: "InstallPath"; ValueType: String; ValueData: "{app}"; Flags: uninsdeletevalue 
Root: HKLM; Subkey: "Software\GnuWin32\LibIntl\0.14.4\pck"; ValueName: "InstallPath"; ValueType: String; ValueData: "{app}"; Flags: uninsdeletevalue 

[Run]
Filename: "http://prdownloads.sourceforge.net/gnuwin32/libintl-0.14.4-src.zip?download"; Description: "Download sources"; Tasks: downloadsrc; Flags: shellexec hidewizard nowait

[Icons]
Name: "{group}\Uninstall LibIntl-0.14.4"; Filename: "{uninstallexe}"; 
Name: "{group}\man\pdf\libintl-man.pdf"; Filename: "{app}\man\pdf\libintl-man.pdf"; WorkingDir: "{app}\man\pdf"; Components: doc; Tasks: docicon; 
Name: "{group}\libintl-man.pdf"; Filename: "{app}\man\pdf\libintl-man.pdf"; WorkingDir: "{app}\man\pdf"; Components: doc; Tasks: docicon; 

[Tasks]
Name: "docicon"; Description: "Create document shortcuts in Start Menu folder"; GroupDescription: "Additional icons:"; Components: "doc"; 
Name: "downloadsrc"; Description: "Download Sources"; 

[Components]
Name: "bin"; Description: "Binaries"; Types: "full compact"; 
Name: "doc"; Description: "Documentation"; Types: "full"; 
Name: "lib"; Description: "Developer files"; Types: "full"; 

[UninstallDelete]
Type: dirifempty; Name: "{app}\bin"; 
Type: dirifempty; Name: "{app}\contrib"; 
Type: dirifempty; Name: "{app}\doc"; 
Type: dirifempty; Name: "{app}\etc"; 
Type: dirifempty; Name: "{app}\lib"; 
Type: dirifempty; Name: "{app}\libexec"; 
Type: dirifempty; Name: "{app}\man\man1"; 
Type: dirifempty; Name: "{app}\man\man2"; 
Type: dirifempty; Name: "{app}\man\man3"; 
Type: dirifempty; Name: "{app}\man\man4"; 
Type: dirifempty; Name: "{app}\man\man5"; 
Type: dirifempty; Name: "{app}\man\man6"; 
Type: dirifempty; Name: "{app}\man\man7"; 
Type: dirifempty; Name: "{app}\man\man8"; 
Type: dirifempty; Name: "{app}\man\man9"; 
Type: dirifempty; Name: "{app}\man\man1p"; 
Type: dirifempty; Name: "{app}\man\man2p"; 
Type: dirifempty; Name: "{app}\man\man3p"; 
Type: dirifempty; Name: "{app}\man\man4p"; 
Type: dirifempty; Name: "{app}\man\man5p"; 
Type: dirifempty; Name: "{app}\man\man6p"; 
Type: dirifempty; Name: "{app}\man\man7p"; 
Type: dirifempty; Name: "{app}\man\man8p"; 
Type: dirifempty; Name: "{app}\man\man9p"; 
Type: dirifempty; Name: "{app}\man\cat1"; 
Type: dirifempty; Name: "{app}\man\cat2"; 
Type: dirifempty; Name: "{app}\man\cat3"; 
Type: dirifempty; Name: "{app}\man\cat4"; 
Type: dirifempty; Name: "{app}\man\cat5"; 
Type: dirifempty; Name: "{app}\man\cat6"; 
Type: dirifempty; Name: "{app}\man\cat7"; 
Type: dirifempty; Name: "{app}\man\cat8"; 
Type: dirifempty; Name: "{app}\man\cat9"; 
Type: dirifempty; Name: "{app}\man\cat1p"; 
Type: dirifempty; Name: "{app}\man\cat2p"; 
Type: dirifempty; Name: "{app}\man\cat3p"; 
Type: dirifempty; Name: "{app}\man\cat4p"; 
Type: dirifempty; Name: "{app}\man\cat5p"; 
Type: dirifempty; Name: "{app}\man\cat6p"; 
Type: dirifempty; Name: "{app}\man\cat7p"; 
Type: dirifempty; Name: "{app}\man\cat8p"; 
Type: dirifempty; Name: "{app}\man\cat9p"; 
Type: dirifempty; Name: "{app}\man\pdf"; 
Type: dirifempty; Name: "{app}\man\ps"; 
Type: dirifempty; Name: "{app}\man\html"; 
Type: dirifempty; Name: "{app}\man"; 
Type: dirifempty; Name: "{app}\sbin"; 
Type: dirifempty; Name: "{app}\share\locale\ca\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\da\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\de\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\de_DE\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\el\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\eo\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\es\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\et\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\fi\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\fr\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\gl\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\he\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\hr\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\hu\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\id\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\it\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\ja\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\ko\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\ll\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\lv\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\nb\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\nl\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\nn\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\pl\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\pt\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\pt_BR\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\ru\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\sk\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\sl\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\sv\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\tr\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\uk\LC_MESSAGES"; 
Type: dirifempty; Name: "{app}\share\locale\ca"; 
Type: dirifempty; Name: "{app}\share\locale\da"; 
Type: dirifempty; Name: "{app}\share\locale\de"; 
Type: dirifempty; Name: "{app}\share\locale\de_DE"; 
Type: dirifempty; Name: "{app}\share\locale\el"; 
Type: dirifempty; Name: "{app}\share\locale\eo"; 
Type: dirifempty; Name: "{app}\share\locale\es"; 
Type: dirifempty; Name: "{app}\share\locale\et"; 
Type: dirifempty; Name: "{app}\share\locale\fi"; 
Type: dirifempty; Name: "{app}\share\locale\fr"; 
Type: dirifempty; Name: "{app}\share\locale\gl"; 
Type: dirifempty; Name: "{app}\share\locale\he"; 
Type: dirifempty; Name: "{app}\share\locale\hr"; 
Type: dirifempty; Name: "{app}\share\locale\hu"; 
Type: dirifempty; Name: "{app}\share\locale\id"; 
Type: dirifempty; Name: "{app}\share\locale\it"; 
Type: dirifempty; Name: "{app}\share\locale\ja"; 
Type: dirifempty; Name: "{app}\share\locale\ko"; 
Type: dirifempty; Name: "{app}\share\locale\ll"; 
Type: dirifempty; Name: "{app}\share\locale\lv"; 
Type: dirifempty; Name: "{app}\share\locale\nb"; 
Type: dirifempty; Name: "{app}\share\locale\nl"; 
Type: dirifempty; Name: "{app}\share\locale\nn"; 
Type: dirifempty; Name: "{app}\share\locale\pl"; 
Type: dirifempty; Name: "{app}\share\locale\pt"; 
Type: dirifempty; Name: "{app}\share\locale\pt_BR"; 
Type: dirifempty; Name: "{app}\share\locale\ru"; 
Type: dirifempty; Name: "{app}\share\locale\sk"; 
Type: dirifempty; Name: "{app}\share\locale\sl"; 
Type: dirifempty; Name: "{app}\share\locale\sv"; 
Type: dirifempty; Name: "{app}\share\locale\tr"; 
Type: dirifempty; Name: "{app}\share\locale\uk"; 
Type: dirifempty; Name: "{app}\share\locale"; 
Type: dirifempty; Name: "{app}\share"; 
Type: dirifempty; Name: "{app}\src"; 
Type: dirifempty; Name: "{app}\tmp"; 
Type: dirifempty; Name: "{app}\uninstall"; 
Type: dirifempty; Name: "{app}\var"; 
Type: dirifempty; Name: "{app}"; 

[Types]
Name: "full"; 
Name: "compact"; 
Name: "custom"; 

[CustomMessages]
default.NameAndVersion=%1 version %2
default.AdditionalIcons=Additional icons:
default.CreateDesktopIcon=Create a &desktop icon
default.CreateQuickLaunchIcon=Create a &Quick Launch icon
default.ProgramOnTheWeb=%1 on the Web
default.UninstallProgram=Uninstall %1
default.LaunchProgram=Launch %1
default.AssocFileExtension=&Associate %1 with the %2 file extension
default.AssocingFileExtension=Associating %1 with the %2 file extension...

[Languages]
; These files are stubs
; To achieve better results after recompilation, use the real language files
Name: "default"; MessagesFile: "embedded\default.isl"; 
