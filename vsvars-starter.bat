@echo off

setlocal enableextensions enabledelayedexpansion

rem this will be eventually overridden by phpsdk_setvars, but nothing wrong to use the same name here
set PHP_SDK_ROOT_PATH=%~dp0
set PHP_SDK_ROOT_PATH=%PHP_SDK_ROOT_PATH:~0,-1%

:getopt
if /i "%1" equ "-h" goto help
if /i "%1" equ "-c" set CRT=%2 & shift
if /i "%1" equ "-a" set ARCH=%2 & shift
if /i "%1" equ "-p" set PLATFORM=%2 & shift
if /i "%1" equ "-t" set TASK=%2 & shift
if /i "%1" equ "--task-args" set TASK_ARGS=%2 & shift
shift
if not (%1)==() goto getopt

if "%CRT%" equ "" goto help
if "%ARCH%" equ "" goto help
if "%PLATFORM%" equ "" goto help
if "%TASK%" equ "" set TASK=Release
goto skip_help

:help
	echo Usage: vsvars-starter.bat args
	exit /b 0

:skip_help
set CRT=%CRT: =%
set ARCH=%ARCH: =%
set PLATFORM=%PLATFORM: =%
set TASK=%TASK: =%

set PHP_SDK_RUN_FROM_ROOT=1

title VS VARS %CRT% %ARCH% %PLATFORM%
echo "%comspec% calling %PHP_SDK_ROOT_PATH%\bin\vsvarsall.bat (/Debug /Release | /x86 /x64 /ia64 | /vista /xp /2003 /2008 /win7)"
%comspec% /k ""%PHP_SDK_ROOT_PATH%\bin\vsvarsall.bat"" /%TASK% /%ARCH% /%PLATFORM%
 
exit /b !ERRORLEVEL!

