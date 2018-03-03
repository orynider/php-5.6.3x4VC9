#include <sys/types.h>			/* for namser.h */
#include <arpa/nameser.h>		/* for BYTE_ORDER */
#include <process.h>			/* for execv */
#include <ioctl.h>				/* for unix.h */
#include <unix.h>
#include <sys/select.h>			/* for select */

#define HAS_TEST_AND_SET

#undef HAVE_GETRUSAGE

#define strncasecmp strnicmp

#ifndef					NAN
#ifndef					__nan_bytes
#define __nan_bytes								{ 0, 0, 0, 0, 0, 0, 0xf8, 0x7f }
#endif   /* __nan_bytes */
extern unsigned char __nan[8];

#define							   NAN	   (*(const double *) __nan)
#endif   /* NAN */

typedef u_short ushort;

typedef unsigned char slock_t;

extern int	isnan(double dsrc);

extern double rint(double x);

extern char *crypt(const char *, const char *);

extern long random(void);
extern void srandom(unsigned int seed);
