/* Generic unistd.h */
#ifndef _AC_UNISTD_H
#define _AC_UNISTD_H

#ifdef HAVE_SYS_TYPES_H
#	include <sys/types.h>
#endif

#ifdef HAVE_UNISTD_H
#	include <unistd.h>
#endif

#ifdef HAVE_PROCESS_H
#	include <process.h>
#endif

/* note: callers of crypt(3) should include <ac/crypt.h> */

/*
 * Windows: although sleep() will be resolved by both MSVC and Mingw GCC
 * linkers, the function is not declared in header files. This is
 * because Windows' version of the function is called _sleep(), and it
 * is declared in stdlib.h
 */

#ifdef _WIN32
#define sleep _sleep
#endif

#endif /* _AC_UNISTD_H */
