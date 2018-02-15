::cmd /c bin\phpsdk_buildtree.bat phpdev

::echo Downloading php-src and deps
::curl -L -o php-5.6.33-src.zip https://github.com/php/php-src/archive/php-5.6.33-src.zip || goto :error
::7z x php-5.6.33-src.zip
::del /Q php-5.6.33.zip
::ren php-5.6.33-src php-5.6.33
::move php-5.6.33 phpdev\vc15\x86\php-5.6.33
cd phpdev\vc15\x86\php-5.6.33
cmd /c phpsdk_deps --update --branch 5.6 || goto :error

cmd /c buildconf
cmd /c configure --disable-all --enable-cgi --enable-cli --enable-cli-win32 --enable-embed --enable-isapi --enable-phpdbg --enable-phpdbgs --enable-snapshot-build --enable-bcmath --enable-calendar --enable-com-dotnet || goto :error
nmake || goto :error


rem cd %PHP_SDK_ROOT_PATH%\

::echo Testing PHP
::set PHP_RELEASE_PATH=%~dp0php-sdk\phpdev\vc9\x86\php-7.2.1\x86\Release
::curl -L -o %PHP_RELEASE_PATH%\phpunit.phar https://phar.phpunit.de/phpunit-5.7.phar || goto :error
::cd %~dp0php\tests
::echo PHP Test in Windows is unavailable yet.
REM Don't ``goto :error`` here before the extension can run on Windows.
rem cmd /c testphp5.bat