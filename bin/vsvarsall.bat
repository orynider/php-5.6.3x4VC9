@echo off
@echo Setting Environment
REM php_setvars and phpsdk_buildtree will break the batch run them after enviroment is set
::Versuin Overwrite by developer; ie @SET WindowsSdkVersion=v6.0A
@SET VSOverridePrefix=0
@SET SDKVersionOverride=8
@SET VCVersionOverride=9
@SET VSVersionOverride=9
@SET VSOverrideSufix=0
:: --------------------------------------------------------------------------------------------
:: Set the PlatformToolset that is used by MSBuild 4.0
:: To use the Visual Studio 2010 tools/headers/libraries, "set PlatformToolset=100"
:: --------------------------------------------------------------------------------------------
@SET VisualStudioVersion=%VSVersionOverride%.%VSOverrideSufix%
@SET PlatformToolset=Windows%SDKVersionOverride%.1SDK
@SET WindowsSdkVersion=v%SDKVersionOverride%.1
@SET PHP_SDK_BRANCH=5.6
::@SET PHP_SDK_BRANCH=7.2
@SET PHP_SDK_SUBVERSION=39
@SET PHP_VERSION_STRING=%PHP_SDK_BRANCH%.%PHP_SDK_SUBVERSION%
@SET FrameworkDir=%WinDir%\Microsoft.NET\Framework\
@SET ToolsVersion=4.0
@SET FrameworkVersion=v2.0.50727
@SET FrameworkVersion32=v4.0.30319
:: Set VS default path and rename c:\php-sdk\bin\vsvarsall.bat.in to c:\php-sdk\bin\vsvarsall.bat
@SET VCINSTALLDIR=c:\MsVS%VSOverridePrefix%%VCVersionOverride%\VC\
@SET VSINSTALLDIR=c:\MsVS%VSOverridePrefix%%VCVersionOverride%\
::@SET VCINSTALLDIR=%Path32%\Microsoft Visual Studio %VCVersionOverride%.0\VC\
::@SET VSINSTALLDIR=%Path32%\Microsoft Visual Studio %VCVersionOverride%.0\
::@SET WindowsKitsDirVar=Windows Kits 
@SET WindowsKitsDirVar=Microsoft SDKs\Windows
:: Set "\" for old versions of SDK 
::@SET %WindowsSdkVersion10%=\10.0.10240.0\
@SET %WindowsSdkVersion10%=\
if "%PHP_SDK_ROOT_PATH%" == "" SET PHP_SDK_ROOT_PATH=c:\php-5.6.3x4VC9\ & SET PHP_SDK_BIN_PATH=c:\php-5.6.3x4VC9\bin & echo Changed PHP_SDK_ROOT_PATH: %PHP_SDK_ROOT_PATH%
::if "%PHP_SDK_ROOT_PATH%" == "" SET PHP_SDK_ROOT_PATH=c:\php-sdk\ & SET PHP_SDK_BIN_PATH=c:\php-sdk\bin & echo Changed PHP_SDK_ROOT_PATH: %PHP_SDK_ROOT_PATH%
if "%PHP_SDK_VC%" == "" SET PHP_SDK_VC=vc%VCVersionOverride%
@SET PHP_SDK_BIN_PATH=%PHP_SDK_ROOT_PATH%\bin
@SET PHP_SDK_MSYS2_PATH=%PHP_SDK_ROOT_PATH%\msys2\usr\bin
@SET PHP_SDK_PHP_CMD=%PHP_SDK_BIN_PATH%\php\do_php.bat
@SET PATH=%PHP_SDK_BIN_PATH%;%PHP_SDK_MSYS2_PATH%;%PATH%

echo "Selecting %1 compilers."
@SET PHP_SDK_VERSION=%PHP_SDK_BRANCH%.%PHP_SDK_SUBVERSION%

if "%1" == "" SET PHP_SDK_ARCH=x86
:: --------------------------------------------------------------------------------------------
:: Set the default value for target and current CPU based on processor architecture.
:: --------------------------------------------------------------------------------------------
IF /I "%~1" == "/debug"		SET Configuration=Debug   
IF /I "%~1" == "/release"	SET Configuration=Release 
IF /I "%~1" == "/x86"		SET TARGET_CPU=x86          
IF /I "%~1" == "/x64"		SET TARGET_CPU=x64 
IF /I "%~1" == "/ARM"		SET TARGET_CPU=ARM          
IF /I "%~1" == "/ia64"		SET TARGET_CPU=IA64        
IF /I "%~1" == "/vista"		SET TARGET_PLATFORM=LH     
IF /I "%~1" == "/xp"		SET TARGET_PLATFORM=XP    
IF /I "%~1" == "/2003"		SET TARGET_PLATFORM=SRV   
IF /I "%~1" == "/2008"		SET TARGET_PLATFORM=LHS   
IF /I "%~1" == "/win7"		SET TARGET_PLATFORM=WIN7 
IF /I "%~1" == "/win10"		SET TARGET_PLATFORM=WIN10 
IF /I "%~1" == "/win8.1"	SET TARGET_PLATFORM=WIN8.1 
IF /I "%~1" == "/phone8.1"	SET TARGET_PLATFORM=phone8.1 
:: Initialize build configuration
if /i "%2" == "/x86"		SET PHP_SDK_ARCH=x86
if /i "%2" == "/amd64"		SET PHP_SDK_ARCH=amd64
if /i "%2" == "/x64"		SET PHP_SDK_ARCH=amd64
if /I "%2" == "/arm"		SET TARGET_CPU=arm   
if /i "%2" == "/ia64"		SET PHP_SDK_ARCH=ia64
if /i "%2" == "/x86_amd64"	SET PHP_SDK_ARCH=x86_amd64
if /i "%2" == "/x86_ia64"	SET PHP_SDK_ARCH=x86_ia64

if /i "%3" == "/vista"      SET TARGET_PLATFORM=LH     
if /i "%3" == "/xp"         SET TARGET_PLATFORM=XP    
if /i "%3" == "/2003"       SET TARGET_PLATFORM=SRV   
if /i "%3" == "/2008"       SET TARGET_PLATFORM=LHS   
if /i "%3" == "/win7"       SET TARGET_PLATFORM=WIN7 
IF /I "%3" == "/win10"		SET TARGET_PLATFORM=WIN10 
IF /I "%3" == "/win8.1"		SET TARGET_PLATFORM=WIN8.1 
IF /I "%3" == "/phone8.1"	SET TARGET_PLATFORM=phone8.1 

::IF /I "%PHP_SDK_ARCH%"=="" GOTO Error_Usage
IF /i "%PHP_SDK_ARCH%" == "" SET PHP_SDK_ARCH=x86

@SET CURRENT_CPU=%PHP_SDK_ARCH%
if "%TARGET_CPU%" == ""			SET TARGET_CPU=%PHP_SDK_ARCH%
if "%Configuration%" == ""		SET Configuration=Release
if "%TARGET_PLATFORM%" == ""	SET TARGET_PLATFORM=XP

rem We do an incremental Release build for all specs and all archs by default
set BUILD_FLAVOR=%Configuration%
set BUILD_COMMAND=/Build
set BUILD_SPEC=
set BUILD_ARCH=%TARGET_PLATFORM%
set BUILD_FAILED=

:: clear the temp variable
::SET Path32=

:: set WinSDK default dir
@SET WindowsSDKVersionOverride=%WindowsSdkVersion%
@SET WindowsSDKDir=%ProgramFiles%\Microsoft SDKs\Windows\%WindowsSdkVersion%\

IF EXIST "%WinDir%\Microsoft.NET\Framework\msbuild.exe" SET "FrameworkDir32=%WinDir%\Microsoft.NET\Framework\"
IF EXIST "%WinDir%\Microsoft.NET\Framework64\msbuild.exe" SET "FrameworkDir64=%WinDir%\Microsoft.NET\Framework64"

IF EXIST "%WinDir%\Microsoft.NET\Framework\v3.5\MSBuild.exe" SET "Framework35Version=v3.5"

:: Set the WindowsSdkDir path
FOR /F "tokens=2* delims=	 " %%A IN ('REG QUERY "%WinSDKRegKeyPath%" /v InstallationFolder') DO SET WindowsSDKDir=%%B
@SET "sdkdir=%WindowsSDKDir%"

@if "%VSINSTALLDIR%"=="" goto error_no_VSINSTALLDIR
@if "%VCINSTALLDIR%"=="" goto error_no_VCINSTALLDIR

@echo Setting environment for %PHP_SDK_ARCH% using Microsoft Visual Studio tools.

@call :GetWindowsSdkDir

:: find platform for default paths
echo NOTE: If the list of platforms is not already set, use the default list.
IF "%CURRENT_CPU%"=="x86" (
  SET Path32=%ProgramFiles%
	IF NOT DEFINED PLATFORMS (
	  SET PLATFORMS=x86 x86_amd64 x86_arm
	) 
) 
IF "%CURRENT_CPU%"=="x64" (
  SET Path32=%ProgramFiles(x86)%
	IF NOT DEFINED PLATFORMS (
	  SET PLATFORMS=x64 x64_amd64 x64_arm
	) 
)

:: Windows API headers and libraries.
@if not "%WindowsSdkDir%" == "" (
	set "PATH=%WindowsSdkDir%bin;%PATH%"
	set "INCLUDE=%WindowsSdkDir%include;%INCLUDE%"
	set "LIB=%WindowsSdkDir%lib;%LIB%"
)

@SET WindowsSdkDir=%ProgramFiles%\%WindowsKitsDirVar%\%WindowsSdkVersion%\
@SET WindowsSdkIncludeDir=%ProgramFiles%\%WindowsKitsDirVar%\%WindowsSdkVersion%\Include\
@SET WindowsSdkLibDir=%ProgramFiles%\%WindowsKitsDirVar%\%WindowsSdkVersion%\Lib\winv6.3\um\ 

@rem
@rem Root of Visual Studio IDE installed files.
@rem
@set DevEnvDir=%VSINSTALLDIR%\Common7\IDE
@set PATH=%VSINSTALLDIR%\Common7\IDE;%VSINSTALLDIR%\VC\BIN;%VSINSTALLDIR%\Common7\Tools;C:\Windows\Microsoft.NET\Framework\v3.5;C:\Windows\Microsoft.NET\Framework\v2.0.50727;%VSINSTALLDIR%\VC\VCPackages;%PATH%
@set INCLUDE=%VSINSTALLDIR%\VC\ATLMFC\INCLUDE;%VSINSTALLDIR%\VC\INCLUDE;%INCLUDE%
@set LIB=%VSINSTALLDIR%\VC\ATLMFC\LIB;%VSINSTALLDIR%\VC\LIB;%LIB%

@set LIBPATH=%WinDir%\Microsoft.NET\Framework\v3.5;%WinDir%\Microsoft.NET\Framework\v2.0.50727;%VSINSTALLDIR%\VC\ATLMFC\LIB;%VSINSTALLDIR%\VC\LIB;%LIBPATH%
@set mc=%ProgramFiles%\%WindowsKitsDirVar%\Windows\%WindowsSdkVersion%\bin\MC.Exe

:: Windows C library headers and libraries.
WindowsCrtIncludeDir=%ProgramFiles%\%WindowsKitsDirVar%\%WindowsSdkVersion%\Include%WindowsSdkVersion10%ucrt
WindowsCrtLibDir=%ProgramFiles%\%WindowsKitsDirVar%\%WindowsSdkVersion%\Lib%WindowsSdkVersion10%ucrt\

@goto end

:GetWindowsSdkDir
@call :GetWindowsSdkDirHelper HKLM > nul 2>&1
@if errorlevel 1 call :GetWindowsSdkDirHelper HKCU > nul 2>&1
@if errorlevel 1 set WindowsSdkDir=%VCINSTALLDIR%\PlatformSDK\
@exit /B 0

:GetWindowsSdkDirHelper
@for /F "tokens=1,2*" %%i in ('reg query "%1\SOFTWARE\Microsoft\Microsoft SDKs\Windows" /v "CurrentInstallFolder"') DO (
	if "%%i"=="CurrentInstallFolder" (
		SET "WindowsSdkDir=%%k"
	)
)
@if "%WindowsSdkDir%" == "" exit /B 1
@exit /B 0

:error_no_VSINSTALLDIR
@echo ERROR: VSINSTALLDIR variable is not set. 
@goto end

:error_no_VCINSTALLDIR
@echo ERROR: VCINSTALLDIR variable is not set. 
@goto end

:end
@echo OFF
:: --------------------------------------------------------------------------------------------
:: Set the default value for target and current CPU based on processor architecture.
:: --------------------------------------------------------------------------------------------
IF "x%TARGET_CPU%x"=="xx" (
IF /I "%PROCESSOR_ARCHITECTURE%"=="x86" SET "TARGET_CPU=x86" & SET "CURRENT_CPU=x86"
IF /I "%PROCESSOR_ARCHITEW6432%"=="x86" SET "TARGET_CPU=x86" & SET "CURRENT_CPU=x86"
IF /I "%PROCESSOR_ARCHITECTURE%"=="AMD64" SET "TARGET_CPU=x64" & SET "CURRENT_CPU=x64"
IF /I "%PROCESSOR_ARCHITEW6432%"=="AMD64" SET "TARGET_CPU=x64" & SET "CURRENT_CPU=x64"
IF /I "%PROCESSOR_ARCHITECTURE%"=="x64"   SET "TARGET_CPU=x64" & SET "CURRENT_CPU=x64"
IF /I "%PROCESSOR_ARCHITECTURE%"=="IA64"  SET "TARGET_CPU=IA64" & SET "CURRENT_CPU=IA64"
IF /I "%PROCESSOR_ARCHITEW6432%"=="IA64"  SET "TARGET_CPU=IA64" & SET "CURRENT_CPU=IA64"
GOTO Parse_Args
)
:: --------------------------------------------------------------------------------------------
:: Parse command line argument values.
:: Note: For ambiguous arguments the last one wins (ex: /debug /release)
:: --------------------------------------------------------------------------------------------
:Parse_Args
IF /I "%~1"=="/debug"      SET "Configuration=Debug"   & SHIFT & GOTO Parse_Args
IF /I "%~1"=="/release"    SET "Configuration=Release" & SHIFT & GOTO Parse_Args
IF /I "%~1"=="/x86"        SET "TARGET_CPU=x86"           & SHIFT & GOTO Parse_Args
IF /I "%~1"=="/x64"        SET "TARGET_CPU=x64"           & SHIFT & GOTO Parse_Args
IF /I "%~1"=="/ia64"       SET "TARGET_CPU=IA64"          & SHIFT & GOTO Parse_Args
IF /I "%~1"=="/vista"      SET "TARGET_PLATFORM=LH"       & SHIFT & GOTO Parse_Args
IF /I "%~1"=="/xp"         SET "TARGET_PLATFORM=XP"       & SHIFT & GOTO Parse_Args
IF /I "%~1"=="/2003"       SET "TARGET_PLATFORM=SRV"      & SHIFT & GOTO Parse_Args
IF /I "%~1"=="/2008"       SET "TARGET_PLATFORM=LHS"      & SHIFT & GOTO Parse_Args
IF /I "%~1"=="/win7"       SET "TARGET_PLATFORM=WIN7"     & SHIFT & GOTO Parse_Args
IF /I "%~1"=="-h"          GOTO Error_Usage
IF /I "%~1"=="/?"          GOTO Error_Usage
IF    "x%~1"=="x"          GOTO Done_Args

:Done_Args

:: --------------------------------------------------------------------------------------------
:: Prevent path duplication if setenv is run multiple times within a single command session
:: --------------------------------------------------------------------------------------------
IF "x%ORIGINALPATH%x"=="xx" (
  SET "ORIGINALPATH=%PATH%"
) ELSE (
  SET "PATH=%ORIGINALPATH%"
)

:: --------------------------------------------------------------------------------------------
:: Default the build configuration to DEBUG if one is not specified.
:: Set the command prompt text color based on the build configuration.
:: --------------------------------------------------------------------------------------------
IF "x%Configuration%"=="x" SET Configuration=Debug
IF "%Configuration%"=="Debug" (
    SET DEBUGMSG=Debug
        COLOR 0E
) ELSE IF "%Configuration%"=="Release" (
    SET DEBUGMSG=Release
        COLOR 02
) ELSE GOTO Error_Usage

:: --------------------------------------------------------------------------------------------
:: Default to LHS if no target type specified and configure for appropriate target
:: --------------------------------------------------------------------------------------------
IF "x%TARGET_PLATFORM%"=="x" (
FOR /F "tokens=1,2,3 delims=;." %%i IN ('Cmd /c Ver') DO (
    IF "%%i"=="Microsoft Windows XP [Version 5" (
      SET TARGET_PLATFORM=XP
    ) ELSE IF "%%i"=="Microsoft Windows [Version 5" (
      SET TARGET_PLATFORM=SRV
    ) ELSE IF "%%i"=="Microsoft Windows [Version 6" (
      IF "%%k" == "6000]" (
        SET TARGET_PLATFORM=LH
      ) ELSE IF "%%k" == "6001]" (
        SET TARGET_PLATFORM=LHS
      ) ELSE IF "%%k" == "7600]" (
        SET TARGET_PLATFORM=WIN7
    ) ELSE (
        SET TARGET_PLATFORM=WIN7
    )
    ) ELSE (
      SET TARGET_PLATFORM=WIN7
    )
  )
)

:: --------------------------------------------------------------------------------------------
:: Determine which registry keys to look at based on architecture type.  Set default values for
:: VC and VS root, which would be used if one or both the corresponding registry keys are not
:: found.
:: --------------------------------------------------------------------------------------------
SET RegKeyPath=HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\VisualStudio\SxS\VC7
SET VSRegKeyPath=HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\VisualStudio\SxS\VS7
SET WinSDKRegKeyPath=HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Microsoft SDKs\Windows\%WindowsSdkVersion%

:: Set the framework paths and versions
FOR /F "tokens=2* delims=	 " %%A IN ('REG QUERY "%RegKeyPath%" /v FrameworkDir32') DO SET FrameworkDir32=%%B
FOR /F "tokens=2* delims=	 " %%A IN ('REG QUERY "%RegKeyPath%" /v FrameworkDir64') DO SET FrameworkDir64=%%B
FOR /F "tokens=2* delims=	 " %%A IN ('REG QUERY "%RegKeyPath%" /v FrameworkVer32') DO SET FrameworkVersion32=%%B
FOR /F "tokens=2* delims=	 " %%A IN ('REG QUERY "%RegKeyPath%" /v FrameworkVer64') DO SET FrameworkVersion64=%%B

SET FrameworkDir32=%WinDir%\Microsoft.NET\Framework\
SET FrameworkDir=%FrameworkDir32%
SET FrameworkVersion=%FrameworkVersion32%

IF NOT "%CURRENT_CPU%"=="x86"  GOTO SetRegPathFor64Bit

GOTO Done_SetRegPath

:SetRegPathFor64Bit
SET RegKeyPath=HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\VisualStudio\SxS\VC7
SET VSRegKeyPath=HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\VisualStudio\SxS\VS7
::SET "VCINSTALLDIR=%ProgramFiles(x86)%\Microsoft Visual Studio 10.0\VC\"
::SET "VSINSTALLDIR=%ProgramFiles(x86)%\Microsoft Visual Studio 10.0\"

:: if 64 bit
IF EXIST "%FrameworkDir64%" (
  SET "FrameworkDir=%FrameworkDir64%"
  SET "FrameworkVersion=%FrameworkVersion64%"
)

:Done_SetRegPath
:: --------------------------------------------------------------------------------------------
:: Set the CL.exe option to find the framework for linking
:: --------------------------------------------------------------------------------------------
IF "%CURRENT_CPU%"=="x86" (
  SET CL=/AI %FrameworkDir%%FrameworkVersion%
) ELSE (
  SET CL=/AI %FrameworkDir%\%FrameworkVersion%
)

:: --------------------------------------------------------------------------------------------
:: Save the default values for VCINSTALLDIR and VSINSTALLDIR just in case we get unexpected output from
:: the calls to REG in the next section
:: --------------------------------------------------------------------------------------------
SET "VCINSTALLDIR_Orig=%VCINSTALLDIR%"
SET "VSINSTALLDIR_Orig=%VSINSTALLDIR%"

:: --------------------------------------------------------------------------------------------
:: Read the value for VCINSTALLDIR and VSINSTALLDIR from the registry.
:: Note: The second call to REG will fail if VS is not installed.  These calls to REG are
:: checking to see if VS is installed in a custom location.  This behavior is expected in
:: this scenario.
:: --------------------------------------------------------------------------------------------
FOR /F "tokens=2* delims=	 " %%A IN ('REG QUERY "%RegKeyPath%" /v %VCVersionOverride%.0') DO SET VCINSTALLDIR=%%B
FOR /F "tokens=2* delims=	 " %%A IN ('REG QUERY "%VSRegKeyPath%" /v %VCVersionOverride%.0') DO SET VSINSTALLDIR=%%B

:: --------------------------------------------------------------------------------------------
:: Hide the error output from the call to 'REG' since VCINSTALLDIR and VSINSTALLDIR have already been set
:: to a default value.
:: --------------------------------------------------------------------------------------------
echo NOTE: Check for MSVC 2012, 2013, and 2015 specially because the Windows
echo      SDK directory handling is slightly different for those versions.
IF "%VisualStudioVersion%" == "9.0" (
  IF NOT DEFINED NSDKLIBPATH (
    SET SET_NSDKLIBPATH=1
  )
) ELSE IF "%VisualStudioVersion%" == "10.0" (
  IF NOT DEFINED NSDKLIBPATH (
    SET SET_NSDKLIBPATH=1
  )
) ELSE IF "%VisualStudioVersion%" == "11.0" (
  IF NOT DEFINED NSDKLIBPATH (
    SET SET_NSDKLIBPATH=1
  )
) ELSE IF "%VisualStudioVersion%" == "12.0" (
  IF NOT DEFINED NSDKLIBPATH (
    SET SET_NSDKLIBPATH=1
  )
) ELSE IF "%VisualStudioVersion%" == "14.0" (
  IF NOT DEFINED NSDKLIBPATH (
    SET SET_NSDKLIBPATH=1
  )
)
:: --------------------------------------------------------------------------------------------
:: Versions of Reg.exe on XP SP2 and SP3 have different output than other versions.  Detect
:: incorrect output and reset VCINSTALLDIR and VSINSTALLDIR as needed
:: --------------------------------------------------------------------------------------------
IF "%VCINSTALLDIR%"=="VERSION 3.0" SET "VCINSTALLDIR=%VCINSTALLDIR_Orig%"
IF "%VSINSTALLDIR%"=="VERSION 3.0" SET "VSINSTALLDIR=%VSINSTALLDIR_Orig%"

:: --------------------------------------------------------------------------------------------
:: Setup our VCTools environment path based on target CPU and processor architecture
:: When the native compilers are not installed for the specified CPU, attempt to locate the
:: cross-tools for non-native compilation.
:: --------------------------------------------------------------------------------------------
SET "VCTools=%VCINSTALLDIR%Bin"

IF "%CURRENT_CPU%" =="x64" (
  IF "%TARGET_CPU%" == "x64" (
    IF EXIST "%VCTools%\amd64\cl.exe" (
      SET "VCTools=%VCTools%\amd64;%VCTools%\VCPackages;"
      SET "SdkTools=%WindowsSdkDir%Bin\NETFX 4.0 Tools\x64;%WindowsSdkDir%Bin\x64;%WindowsSdkDir%Bin;"
      SET "FxTools=%FrameworkDir64%\%FrameworkVersion%;%FrameworkDir32%%FrameworkVersion%;%windir%\Microsoft.NET\Framework64\v3.5;%windir%\Microsoft.NET\Framework\v3.5;"
    ) ELSE (
      SET VCTools=
      ECHO The x64 compilers are not currently installed.
      ECHO Please go to Add/Remove Programs to update your installation.
      ECHO .
    )
  ) ELSE IF "%TARGET_CPU%" == "IA64" (
    IF EXIST "%VCTools%\x86_ia64\cl.exe" (
      SET "VCTools=%VCTools%\x86_ia64;%VCTools%\VCPackages;"
      SET "SdkTools=%WindowsSdkDir%Bin\NETFX 4.0 Tools\x64;%WindowsSdkDir%Bin\x64;%WindowsSdkDir%Bin;"
      SET "FxTools=%FrameworkDir64%\%FrameworkVersion%;%FrameworkDir32%%FrameworkVersion%;%windir%\Microsoft.NET\Framework64\v3.5;%windir%\Microsoft.NET\Framework\v3.5;"
    ) ELSE (
      SET VCTools=
      ECHO The IA64 compilers are not currently installed.
      ECHO Please go to Add/Remove Programs to update your installation.
      ECHO .
    )
  ) ELSE IF "%TARGET_CPU%" == "x86" (
    IF EXIST "%VCTools%\cl.exe" (
      SET "VCTools=%VCTools%;%VCTools%\VCPackages;"
      SET "SdkTools=%WindowsSdkDir%Bin\NETFX 4.0 Tools;%WindowsSdkDir%Bin;"
      SET "FxTools=%FrameworkDir32%%FrameworkVersion%;%windir%\Microsoft.NET\Framework\v3.5;"
    ) ELSE (
      SET VCTools=
      ECHO The x86 compilers are not currently installed.
      ECHO Please go to Add/Remove Programs to update your installation.
      ECHO .
    )
  )
) ELSE IF "%CURRENT_CPU%" =="IA64" (
  IF "%TARGET_CPU%" == "IA64" (
    IF EXIST "%VCTools%\IA64\cl.exe" (
      SET "VCTools=%VCTools%\IA64;%VCTools%;%VCTools%\VCPackages;"
      SET "SdkTools=%WindowsSdkDir%Bin\NETFX 4.0 Tools\IA64;%WindowsSdkDir%Bin\IA64;%WindowsSdkDir%Bin;"
      SET "FxTools=%FrameworkDir64%\%FrameworkVersion%;%FrameworkDir32%%FrameworkVersion%;%windir%\Microsoft.NET\Framework64\v3.5;%windir%\Microsoft.NET\Framework\v3.5;"
    ) ELSE (
      SET VCTools=
      ECHO The IA64 compilers are not currently installed.
      ECHO Please go to Add/Remove Programs to update your installation.
      ECHO .
    )
  ) ELSE IF "%TARGET_CPU%" == "x64" (
    IF EXIST "%VCTools%\x86_amd64\cl.exe" (
      SET "VCTools=%VCTools%\x86_amd64;%VCTools%\VCPackages;"
      SET "SdkTools=%WindowsSdkDir%Bin\NETFX 4.0 Tools\IA64;%WindowsSdkDir%Bin\IA64;%WindowsSdkDir%Bin;"
      SET "FxTools=%FrameworkDir64%\%FrameworkVersion%;%FrameworkDir32%%FrameworkVersion%;%windir%\Microsoft.NET\Framework64\v3.5;%windir%\Microsoft.NET\Framework\v3.5;"
    ) ELSE (
      SET VCTools=
      ECHO The VC compilers are not currently installed.
      ECHO Please go to Add/Remove Programs to update your installation.
      ECHO .
    )
  ) ELSE IF "%TARGET_CPU%" == "x86" (
    IF EXIST "%VCTools%\cl.exe" (
      SET "VCTools=%VCTools%;%VCTools%\VCPackages;"
      SET "SdkTools=%WindowsSdkDir%Bin\NETFX 4.0 Tools;%WindowsSdkDir%Bin;"
      SET "FxTools=%FrameworkDir32%%FrameworkVersion%;%windir%\Microsoft.NET\Framework\v3.5;"
    ) ELSE (
      SET VCTools=
      ECHO The x86 compilers are not currently installed.
      ECHO Please go to Add/Remove Programs to update your installation.
      ECHO .
    )
  )
) ELSE IF "%CURRENT_CPU%"=="x86" (
  IF "%TARGET_CPU%" == "x64" (
    IF EXIST "%VCTools%\x86_amd64\cl.exe" (
      SET "VCTools=%VCTools%\x86_amd64;%VCTools%\VCPackages;"
      SET "SdkTools=%WindowsSdkDir%Bin\NETFX 4.0 Tools;%WindowsSdkDir%Bin;"
      SET "FxTools=%FrameworkDir32%%FrameworkVersion%;%windir%\Microsoft.NET\Framework\v3.5;"
    ) ELSE (
      SET VCTools=
      ECHO The x64 cross compilers are not currently installed.
      ECHO Please go to Add/Remove Programs to update your installation.
      ECHO .
    )
  ) ELSE IF "%TARGET_CPU%" == "IA64" (
    IF EXIST "%VCTools%\x86_IA64\cl.exe" (
      SET "VCTools=%VCTools%\x86_IA64;%VCTools%;%VCTools%\VCPackages;"
      SET "SdkTools=%WindowsSdkDir%Bin\NETFX 4.0 Tools;%WindowsSdkDir%Bin;"
      SET "FxTools=%FrameworkDir32%%FrameworkVersion%;%windir%\Microsoft.NET\Framework\v3.5;"
    ) ELSE (
      SET VCTools=
      ECHO The IA64 compilers are not currently installed.
      ECHO Please go to Add/Remove Programs to update your installation.
      ECHO .
    )
  ) ELSE IF "%TARGET_CPU%" == "x86" (
    IF EXIST "%VCTools%\cl.exe" (
      SET "VCTools=%VCTools%;%VCTools%\VCPackages;"
      SET "SdkTools=%WindowsSdkDir%Bin\NETFX 4.0 Tools;%WindowsSdkDir%Bin;"
      SET "FxTools=%FrameworkDir32%%FrameworkVersion%;%windir%\Microsoft.NET\Framework\v3.5;"
    ) ELSE (
      SET VCTools=
      ECHO The x86 compilers are not currently installed. x86-x86
      ECHO Please go to Add/Remove Programs to update your installation.
      ECHO .
    )
  )
) ELSE IF EXIST "%VCTools%\cl.exe" (
  SET "VCTools=%VCTools%;%VCTools%\VCPackages;"
  SET "SdkTools=%WindowsSdkDir%Bin\NETFX 4.0 Tools;%WindowsSdkDir%Bin;"
  SET "FxTools=%FrameworkDir32%%FrameworkVersion%;%windir%\Microsoft.NET\Framework\v3.5;"
) ELSE (
  SET VCTools=
  ECHO The x86 compilers are not currently installed. default
  ECHO Please go to Add/Remove Programs to update your installation.
  ECHO .
)

:: --------------------------------------------------------------------------------------------
:: Set the values for VS directories.
:: --------------------------------------------------------------------------------------------
SET "DevEnvDir=%VSINSTALLDIR%Common7\IDE"
SET "VSTools=%VSINSTALLDIR%Common7\IDE;%VSINSTALLDIR%Common7\Tools;"
SET "VCLibraries=%VCINSTALLDIR%Lib"
SET "VCIncludes=%VCINSTALLDIR%INCLUDE"

:: --------------------------------------------------------------------------------------------
:: Display SDK environment information
:: --------------------------------------------------------------------------------------------
SET OSLibraries=%WindowsSdkDir%Lib
SET OSIncludes=%WindowsSdkDir%INCLUDE;%WindowsSdkDir%INCLUDE\gl

ECHO Setting SDK environment relative to %WindowsSdkDir%.
:: --------------------------------------------------------------------------------------------
:: Set whether this is a cross-compile enviornment
:: --------------------------------------------------------------------------------------------
IF "%CURRENT_CPU%"=="%TARGET_CPU%" (
  SET CommandPromptType=Native
) ELSE (
  SET CommandPromptType=Cross
)

:: Clear the paths
@set PATH=%FxTools%;%VSTools%;%VCTools%;%SdkTools%;%WindowsSdkDir%bin\NETFX 4.0 Tools;%PATH%
@set INCLUDE=%INCLUDE%
@set LIB=%LIB%

GOTO Set_%TARGET_CPU%

:Set_x86
IF NOT "x!VCINSTALLDIR!x"=="xx" (
  IF EXIST "!VCINSTALLDIR!ATLMFC" (
    SET "INCLUDE=!VCINSTALLDIR!ATLMFC\INCLUDE;%INCLUDE%"
    SET "LIB=!VCINSTALLDIR!ATLMFC\LIB;%LIB%"
  )
)

SET "LIB=%VCLibraries%;%OSLibraries%;%FxTools%;%LIB%"
SET "LIBPATH=%FxTools%;%VCLibraries%;%LIBPATH%"
SET "INCLUDE=%VCIncludes%;%OSIncludes%;%INCLUDE%"


GOTO Set_%TARGET_PLATFORM%

:Set_x64
IF NOT "x!VCINSTALLDIR!x"=="xx" (
  IF EXIST "!VCINSTALLDIR!ATLMFC\LIB\AMD64" (
    SET "INCLUDE=!VCINSTALLDIR!ATLMFC\INCLUDE;%INCLUDE%"
    SET "LIB=!VCINSTALLDIR!ATLMFC\LIB\AMD64;%LIB%"
  )
)

SET "LIB=%VCLibraries%\amd64;%OSLibraries%\X64;%LIB%"
SET "LIBPATH=%FxTools%;%VCLibraries%\amd64;%LIBPATH%"
SET "INCLUDE=%VCIncludes%;%OSIncludes%;%INCLUDE%"


GOTO Set_%TARGET_PLATFORM%

:Set_IA64
IF NOT "x!VCINSTALLDIR!x"=="xx" (
  IF EXIST "!VCINSTALLDIR!ATLMFC\LIB\IA64" (
    SET "INCLUDE=!VCINSTALLDIR!ATLMFC\INCLUDE;%INCLUDE%"
    SET "LIB=!VCINSTALLDIR!ATLMFC\LIB\IA64;%LIB%"
  )
)

SET "LIB=%VCLibraries%\IA64;%OSLibraries%\IA64;%LIB%"
SET "LIBPATH=%FxTools%;%VCLibraries%\ia64;%LIBPATH%"
SET "INCLUDE=%VCIncludes%;%OSIncludes%;%INCLUDE%"


GOTO Set_%TARGET_PLATFORM%

:: --------------------------------------------------------------------------------------------
:: Set Windows 7 specific variables
:: --------------------------------------------------------------------------------------------
:Set_WIN7
ECHO Targeting Windows 7 %TARGET_CPU% %DEBUGMSG%
ECHO.
SET APPVER=6.1
TITLE Microsoft Windows 7 %TARGET_CPU% %DEBUGMSG% Build Environment
GOTO End_Success

:: --------------------------------------------------------------------------------------------
:: Set Windows 8 specific variables
:: --------------------------------------------------------------------------------------------
:Set_WIN8
ECHO Targeting Windows 8 %TARGET_CPU% %DEBUGMSG%
ECHO.
SET APPVER=6.3
TITLE Microsoft Windows 8 %TARGET_CPU% %DEBUGMSG% Build Environment
GOTO End_Success

:: --------------------------------------------------------------------------------------------
:: Set Windows 8.1 specific variables
:: --------------------------------------------------------------------------------------------
:Set_WIN8.1
ECHO Targeting Windows 8.1 %TARGET_CPU% %DEBUGMSG%
ECHO.
SET APPVER=6.4
TITLE Microsoft Windows 8.1 %TARGET_CPU% %DEBUGMSG% Build Environment
GOTO End_Success

:: --------------------------------------------------------------------------------------------
:: Set Windows Server 2008 specific variables
:: --------------------------------------------------------------------------------------------
:Set_LHS
ECHO Targeting Windows Server 2008 %TARGET_CPU% %DEBUGMSG%
ECHO.
SET APPVER=6.0
TITLE Microsoft Windows Server 2008 %TARGET_CPU% %DEBUGMSG% Build Environment
GOTO End_Success

:: --------------------------------------------------------------------------------------------
:: Set Windows Vista  specific variables
:: --------------------------------------------------------------------------------------------
:Set_LH
ECHO Targeting Windows Vista %TARGET_CPU% %DEBUGMSG%
ECHO.
SET APPVER=6.0
TITLE Microsoft Windows Vista %TARGET_CPU% %DEBUGMSG% Build Environment
GOTO End_Success

:: --------------------------------------------------------------------------------------------
:: Set Windows Server 2003 specific variables
:: --------------------------------------------------------------------------------------------
:Set_SRV
ECHO Targeting Windows Server 2003 %TARGET_CPU% %DEBUGMSG%
ECHO.
SET APPVER=5.02
TITLE Microsoft Windows Server 2003 %TARGET_CPU% %DEBUGMSG% Build Environment
GOTO End_Success

:: --------------------------------------------------------------------------------------------
:: Set Windows XP specific variables
:: --------------------------------------------------------------------------------------------
:Set_XP
ECHO Targeting Windows XP %TARGET_CPU% %DEBUGMSG%
ECHO.
SET APPVER=5.01
TITLE Microsoft Windows XP %TARGET_CPU% %DEBUGMSG% Build Environment
GOTO End_Success

:: --------------------------------------------------------------------------------------------
:: Display command usage and goto cleanup code.
:: --------------------------------------------------------------------------------------------
:Error_Usage
ECHO Usage: "Setenv [/Debug | /Release][/x86 | /x64 | /ia64][/vista | /xp | /2003 | /2008 | /win7][-h | /?]"
ECHO cmd line: %1 , %2 , %3
ECHO                 /Debug   - Create a Debug configuration build environment
ECHO                 /Release - Create a Release configuration build environment
ECHO                 /x86     - Create 32-bit x86 applications
ECHO                 /x64     - Create 64-bit x64 applications
ECHO                 /ia64    - Create 64-bit ia64 applications
ECHO                 /vista   - Windows Vista applications
ECHO                 /xp      - Create Windows XP SP2 applications
ECHO                 /2003    - Create Windows Server 2003 applications
ECHO                 /2008    - Create Windows Server 2008 or Vista SP1 applications
ECHO                 /win7    - Create Windows 7 applications
ECHO.
ECHO Note:
ECHO * Platform(x86/x64/ia64) and PlatformToolSet(v90/v100/WindowsSDK7.1) set in project or solution will override the environment
ECHO * To upgrade VC6 or later projects to VC2010 format use the VCUpgrade.exe tool.
SET VCBUILD_DEFAULT_OPTIONS=
GOTO CleanUp

:: --------------------------------------------------------------------------------------------
:: End Successfully.  
:: If Windows 7 headers,libs and tools are not used, display a warning message.
:: If necessary, display warning about compiling on Windows 9x platforms.
:: --------------------------------------------------------------------------------------------
:End_Success
SET PHP_CVSROOT=-d :pserver:cvsread@cvs.php.net:/repository
SET PUTTYBASE=%ProgramFiles%\PUTTY\
SET SSH_USER=orynider
SET SSH_HOST=windows.php.net
SET SSH_KEY=%PHP_SDK_ROOT_PATH%\keys\windows.php.net.ppk
SET REMOTE_PATH=/home/web/windows.php.net/docroot/downloads/snaps
SET HOMEPATH=\users\OryNider
SET HOMEDRIVE=C:

IF "x%OS%x" == "xWindows_NTx" SET "DEBUGMSG=" & GOTO CleanUp

ECHO *** WARNING ***
ECHO You are currently building on a Windows 9x based platform.  Most samples have 
ECHO NMAKE create a destination directory for created objects and executables.  
ECHO There is a known issue with the OS where NMAKE fails to create this destination
ECHO directory when the current directory is several directories deep.  To fix this 
ECHO problem, you must create the destination directory by hand from the command 
ECHO line before calling NMAKE. 
ECHO.

:DisplayWarningMsg_NoVersion
ECHO **********************************************************************************
ECHO WARNING: The VC++ Compiler Toolset is not using Windows SDK %WindowsSdkVersion% 
ECHO **********************************************************************************
:: -------------------------------------------------------------------
:: Persist Old Values and
:: -------------------------------------------------------------------
::SET TARGET_PLATFORM=
::SET Configuration=
::SET CURRENT_CPU=
::SET TARGET_CPU=
:: -------------------------------------------------------------------
:: Clean up
:: -------------------------------------------------------------------
:CleanUp
echo DevEnvDir: %DevEnvDir%
echo VSTools: %VSTools%
echo VCLibraries: %VCLibraries%
echo VCIncludes: %VCIncludes%

ECHO ****************************************************************************
ECHO *   The VC++ Compiler Toolset is using Windows SDK %WindowsSdkVersion%                    * 
ECHO ****************************************************************************

:: Clear the paths for php-sdk
@set PHP_SDK_VERPATH=%PHP_SDK_ROOT_PATH%\phpdev\vc%VCVersionOverride%\%PHP_SDK_ARCH%\php-%PHP_SDK_VERSION%
@set PHP_SDK_DEPSPATH=%PHP_SDK_ROOT_PATH%\phpdev\vc%VCVersionOverride%\%PHP_SDK_ARCH%\deps\
@set PHP_SDK_DEPSINCLUDE=%PHP_SDK_ROOT_PATH%\phpdev\vc%VCVersionOverride%\%PHP_SDK_ARCH%\deps\include\
@set PHP_SDK_DEPSLIB=%PHP_SDK_ROOT_PATH%\phpdev\vc%VCVersionOverride%\%PHP_SDK_ARCH%\deps\lib\

@set PATH=%PHP_SDK_ROOT_PATH%\bin\;%ProgramFiles%\Git\mingw32\bin\;%PHP_SDK_VERPATH%;%PHP_SDK_VERPATH%\sapi\;%PHP_SDK_VERPATH%\sapi\aolserver\;%PHP_SDK_VERPATH%\sapi\aolserver\include\;%PATH%
@set INCLUDE=%PHP_SDK_ROOT_PATH%\php_build\zlib;%INCLUDE%
::@set LIB=%PHP_SDK_DEPSLIB%;%LIB%
@set LIB=%LIB%
@echo The environment is using Windows SDK %WindowsSdkDir% and /%PHP_SDK_ARCH% /%TARGET_PLATFORM% /%Configuration%

@rem This directory contains Tcl source files that work on all the platforms
@rem where Tcl runs (e.g. UNIX, PCs, and MacOSX).  Platform-specific
@rem sources are in the directories ../unix, ../win, and ../macosx.
@SET TCLDIR=%PHP_SDK_VERPATH%\ext\sqlite3\generic\
@SET PHP_BUILD_DIR=%PHP_SDK_ROOT_PATH%\php_build\
@SET ZLIB_INCLUDE_DIR=%PHP_SDK_ROOT_PATH%\php_build\zlib\

echo "Check release folder @ %PHP_SDK_VERPATH%\Release_TS\"
rem cd %PHP_SDK_ROOT_PATH%\
IF EXIST %PHP_SDK_VERPATH%\ cd %PHP_SDK_VERPATH%\
cmd /c phpsdk_deps --update --branch %PHP_SDK_BRANCH%

::cd %PHP_SDK_ROOT_PATH%\

rem pause
rem buildconf
rem pause
