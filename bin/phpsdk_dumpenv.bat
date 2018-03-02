@echo off

if "%PHP_SDK_OS_ARCH%"=="" (
	echo PHP SDK is not setup
	exit /b 3
)

cmd /c "exit /b 0"

echo.

call %PHP_SDK_BIN_PATH%\phpsdk_version.bat
echo.

if "%PHP_SDK_OS_ARCH%"=="x64" (
	echo OS architecture:    64-bit 
) else (
	echo OS architecture:    32-bit 
)

if "%PHP_SDK_ARCH%"=="x64" (
	echo Build architecture: 64-bit 
) else (
	echo Build architecture: 32-bit 
)

echo Visual C++:         %PHP_SDK_VC_NUM%
echo PHP-SDK path:       %PHP_SDK_ROOT_PATH%


exit /b %errorlevel%

