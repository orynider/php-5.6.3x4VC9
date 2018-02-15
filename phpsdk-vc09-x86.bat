@echo off

call %~dp0phpsdk-starter.bat -c vc9 -a x86 %*

exit /b %ERRORLEVEL%

