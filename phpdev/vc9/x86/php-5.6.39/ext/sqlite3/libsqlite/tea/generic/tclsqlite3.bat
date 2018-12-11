@rem how to make tclsqlite3.c
@rem how to make on Windows with MSVC:
nmake /f Makefile.msc tclsqlite3.c
@rem a DLL can be generated using MSVC with the following command:
cl tclsqlite3.c -link -dll -out:tclsqlite3.dll
@rem a DLL can be generated using MinGW compiler, the command-line is this:
rem gcc -shared tclsqlite3.c -o tclsqlite3.dll
