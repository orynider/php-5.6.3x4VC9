rem cmd /c bin\phpsdk_buildtree.bat phpdev

rem echo Downloading php-src and deps
rem curl -L -o php-src.zip https://github.com/php/php-src/archive/php-7.2.1.zip || goto :error
rem 7z x php-src.zip
rem del /Q php-src.zip
rem ren php-src-php-7.2.1 php-7.2.1
rem move php-7.2.1 phpdev\vc9\x86\php-7.2.1
cd phpdev\vc9\x86\php-7.2.1
cmd /c phpsdk_deps --update --branch 7.2 --force || goto :error

echo Building Protobuf Extension for PHP
mkdir ..\pecl\protobuf
xcopy ..\..\..\..\..\php\ext\google\protobuf ..\pecl\protobuf
rem cmd /c buildconf
rem cmd /c configure --disable-all --enable-cli --enable-protobuf=shared --disable-zts --force || goto :error
rem nmake || goto :error

rem echo Testing PHP
rem set PHP_RELEASE_PATH=%~dp0php-sdk\phpdev\vc9\x86\php-7.2.1\x86\Release
rem curl -L -o %PHP_RELEASE_PATH%\phpunit.phar https://phar.phpunit.de/phpunit-5.7.phar || goto :error
rem cd %~dp0php\tests
rem echo PHP Test in Windows is unavailable yet.
REM Don't ``goto :error`` here before the extension can run on Windows.
rem cmd /c test.bat