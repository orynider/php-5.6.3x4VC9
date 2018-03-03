@echo off
assoc .js
ftype jsfile
reg query hkcr\jsfile\shell /s
reg query HKEY_CLASSES_ROOT\CLSID\{B54F3741-5B07-11cf-A4B0-00AA004A55E8}\InprocServer32
reg query HKEY_CLASSES_ROOT\CLSID\{f414c260-6ac0-11cf-b6d1-00aa00bbbb58}\
rem If any of these InprocServer32 registry values listed as below exists, update the value(s) to the correct path which is  the Windows version jscript.dll file: "C:\Windows\System32\jscript.dll"
reg query HKEY_CLASSES_ROOT\CLSID\{f414c260-6ac0-11cf-b6d1-00aa00bbbb58}\InprocServer32
reg query HKEY_CLASSES_ROOT\Wow6432Node\CLSID\{f414c260-6ac0-11cf-b6d1-00aa00bbbb58}\InprocServer32
reg query HKEY_LOCAL_MACHINE\SOFTWARE\Classes\CLSID\{f414c260-6ac0-11cf-b6d1-00aa00bbbb58}\InprocServer32
reg query HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Wow6432Node\CLSID\{f414c260-6ac0-11cf-b6d1-00aa00bbbb58}\InprocServer32

:: reg add HKEY_CLASSES_ROOT\CLSID\{f414c260-6ac0-11cf-b6d1-00aa00bbbb58}\InprocServer32
:: reg add HKEY_CLASSES_ROOT\Wow6432Node\CLSID\{f414c260-6ac0-11cf-b6d1-00aa00bbbb58}\InprocServer32
:: reg add HKEY_LOCAL_MACHINE\SOFTWARE\Classes\CLSID\{f414c260-6ac0-11cf-b6d1-00aa00bbbb58}\InprocServer32
:: reg add HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Wow6432Node\CLSID\{f414c260-6ac0-11cf-b6d1-00aa00bbbb58}\InprocServer32

rem If any of these InprocServer32 registry values listed as below exists, update the value(s) to the correct path which is  the Windows version jscript9.dll file: "C:\Windows\System32\jscript9.dll"
reg query HKEY_CLASSES_ROOT\CLSID\{16d51579-a30b-4c8b-a276-0ff4dc41e755}\InprocServer32
reg query HKEY_CLASSES_ROOT\Wow6432Node\CLSID\{16d51579-a30b-4c8b-a276-0ff4dc41e755}\InprocServer32
reg query HKEY_LOCAL_MACHINE\SOFTWARE\Classes\CLSID\{16d51579-a30b-4c8b-a276-0ff4dc41e755}\InprocServer32
reg query HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Wow6432Node\CLSID\{16d51579-a30b-4c8b-a276-0ff4dc41e755}\InprocServer32

:: reg add HKEY_CLASSES_ROOT\CLSID\{16d51579-a30b-4c8b-a276-0ff4dc41e755}\InprocServer32
:: reg add HKEY_CLASSES_ROOT\Wow6432Node\CLSID\{16d51579-a30b-4c8b-a276-0ff4dc41e755}\InprocServer32
:: reg add HKEY_LOCAL_MACHINE\SOFTWARE\Classes\CLSID\{16d51579-a30b-4c8b-a276-0ff4dc41e755}\InprocServer32
:: reg add HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Wow6432Node\CLSID\{16d51579-a30b-4c8b-a276-0ff4dc41e755}\InprocServer32

call %~dp0vsvars-starter.bat -c vc9 -a x86 -p xp %*

exit /b %ERRORLEVEL%

