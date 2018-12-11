@rem how to make sqlite3.c
@rem how to make on Windows with MSVC:
nmake /f Makefile.msc sqlite3.c
@rem a DLL can be generated using MSVC with the following command:
cl sqlite3.c -link -dll -out:sqlite3.dll
@rem a DLL can be generated using MinGW compiler, the command-line is this:
rem gcc -shared sqlite3.c -o sqlite3.dll
