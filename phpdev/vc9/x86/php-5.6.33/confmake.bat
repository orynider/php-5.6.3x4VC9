rem buildconf
rem configure --help
::bcmath
::calendar
::com_dotnet 
::ctype
::date
::ereg
::exif
::fileinfo
::filter     
::ftp        
::hash       
::json       
::mbstring  
::mysql     
::mysqli    
::mysqlnd    
::odbc       
::opcache   
::pcre       
::pdo        
::pdo_mysql 
::pdo_odbc  
::pdo_sqlite
::phar       
::reflection 
::session    
::shmop     
::sockets   
::spl        
::sqlite    
::sqlite3    
::standard   
::tokenizer  
::zip        
::Enabled SAPI:
::-------------
::Sapi Name |
::-------------
::cgi       |
::cli       |
::cli_win32 |
::embed     |
::isapi     |
::phpdbg    |
::phpdbgs   |
configure --disable-all --enable-cgi --enable-cli --enable-cli-win32 --enable-embed --enable-isapi --enable-phpdbg --enable-phpdbgs --enable-snapshot-build --enable-bcmath --enable-calendar --enable-com-dotnet --enable-ctype --with-ereg --enable-mbstring --enable-exif --enable-fileinfo --enable-filter --enable-ftp --enable-hash --enable-json --enable-zip --with-mysql --enable-odbc --enable-opcache --enable-phar --enable-phar-native-ssl --enable-session --enable-shmop --with-mcrypt --enable-sockets --enable-pdo --with-mysqlnd --with-mysqli --with-sqlite3 

configure --enable-debug


::--with-tokenizer  
    
::--with-pdo        
::--with-pdo_mysql 
::--with-pdo_odbc  
::--with-pdo_sqlite
::--with-xdebug=shared
::--with-sqlite        
pause
nmake