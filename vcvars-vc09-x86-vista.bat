@echo off

call %~dp0vsvars-starter.bat -c vc9 -a x86 -p vista %*

exit /b %ERRORLEVEL%

