@echo off

call %~dp0vsvars-starter.bat -c vc15 -a x86 -p xp %*

exit /b %ERRORLEVEL%

