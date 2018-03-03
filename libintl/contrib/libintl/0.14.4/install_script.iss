;InnoSetupVersion=5.0.4

[Setup]
AppName=LibIntl-src
AppVerName=LibIntl-0.14.4 (library for native language support; Sources)
AppVersion=0.14.4
AppPublisher=GnuWin32
AppPublisherURL=http://gnuwin32.sourceforge.net
AppSupportURL=http://sourceforge.net/forum/forum.php?forum_id=74807
AppUpdatesURL=http://gnuwin32.sourceforge.net/packages/libintl.htm
DefaultDirName={reg:HKLM\Software\GnuWin32\LibIntl-src\0.14.4\src,InstallPath|{reg:HKLM\Software\GnuWin32\LibIntl\0.14.4,InstallPath|{reg:HKLM\Software\GnuWin32\LibIntl,InstallPath|{reg:HKLM\Software\GnuWin32,InstallPath|{pf}\GnuWin32}}}}
DefaultGroupName=GnuWin32\LibIntl
UninstallDisplayName=GnuWin32: LibIntl version 0.14.4
UninstallFilesDir={app}\uninstall
OutputBaseFilename=libintl-0.14.4-src
Compression=lzma
PrivilegesRequired=none
AllowNoIcons=yes
LicenseFile=embedded\License.txt
WizardImageFile=embedded\WizardImage.bmp
WizardSmallImageFile=embedded\WizardSmallImage.bmp
;TimeStampsInUTC=yes

[Files]
Source: "{app}\manifest\libintl-0.14.4-src.mft"; DestDir: "{app}\manifest"; Components: src; Flags: overwritereadonly 
Source: "{app}\manifest\libintl-0.14.4-src.ver"; DestDir: "{app}\manifest"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\AUTHORS"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\bindtextdom.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\ChangeLog"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\config.charset"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\COPYING"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\COPYING.LIB-2.0"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\COPYING.LIB-2.1"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\dcgettext.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\dcigettext.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\dcngettext.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\dgettext.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\dngettext.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\eval-plural.h"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\explodename.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\finddomain.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\gettext.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\gettextP.h"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\gmo.h"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\hash-string.h"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\INSTALL"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\intl-compat.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\l10nflist.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\langprefs.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\libgnuintl.h.in"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\libgnuintl.h.msvc-shared"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\libgnuintl.h.msvc-static"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\libgnuintl.h_vms"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\libintl.glibc"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\loadinfo.h"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\loadmsgcat.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\localcharset.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\localcharset.h"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\locale.alias"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\localealias.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\localename.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\log.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\Makefile.in"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\Makefile.msvc"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\Makefile.vms"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\NEWS"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\ngettext.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\os2compat.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\os2compat.h"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\osdep.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\PACKAGING"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\plural-exp.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\plural-exp.h"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\plural.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\plural.y"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\printf-args.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\printf-args.h"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\printf-parse.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\printf-parse.h"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\printf.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\README"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\README.mingw"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\README.vms"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\README.woe32"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\ref-add.sin"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\ref-del.sin"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\relocatable.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\relocatable.h"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\textdomain.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\THANKS"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\vasnprintf.c"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\vasnprintf.h"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\vasnwprintf.h"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\wprintf-parse.h"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4-src\xsize.h"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4\libgnuintl.h.msvc-shared"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4\libgnuintl.h.msvc-static"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4\libgnuintl.h_vms"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4"; Components: src; Flags: overwritereadonly 
Source: "{app}\src\libintl\0.14.4\libintl-0.14.4\Makefile"; DestDir: "{app}\src\libintl\0.14.4\libintl-0.14.4"; Components: src; Flags: overwritereadonly 

[Dirs]
Name: "{app}\src\libintl\0.14.4"; Flags: uninsalwaysuninstall 
Name: "{app}\src\libintl\0.14.4\libintl-0.14.4-src"; Flags: uninsalwaysuninstall 
Name: "{app}\src\libintl\0.14.4\libintl-0.14.4"; Flags: uninsalwaysuninstall 

[Registry]
Root: HKLM; Subkey: "Software\GnuWin32"; Flags: uninsdeletekeyifempty 
Root: HKLM; Subkey: "Software\GnuWin32"; ValueName: "InstallPath"; ValueType: String; ValueData: "{app}"; 
Root: HKLM; Subkey: "Software\GnuWin32\LibIntl"; Flags: uninsdeletekeyifempty 
Root: HKLM; Subkey: "Software\GnuWin32\LibIntl\0.14.4"; Flags: uninsdeletekeyifempty 
Root: HKLM; Subkey: "Software\GnuWin32\LibIntl\0.14.4\src"; Flags: uninsdeletekey 
Root: HKLM; Subkey: "Software\GnuWin32\LibIntl"; ValueName: "InstallPath"; ValueType: String; ValueData: "{app}"; Flags: uninsdeletevalue 
Root: HKLM; Subkey: "Software\GnuWin32\LibIntl\0.14.4"; ValueName: "InstallPath"; ValueType: String; ValueData: "{app}"; Flags: uninsdeletevalue 
Root: HKLM; Subkey: "Software\GnuWin32\LibIntl\0.14.4\src"; ValueName: "InstallPath"; ValueType: String; ValueData: "{app}"; Flags: uninsdeletevalue 

[Icons]
Name: "{group}\Uninstall LibIntl-src-0.14.4"; Filename: "{uninstallexe}"; 

[Components]
Name: "src"; Description: "Sources"; Types: "full"; 

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
