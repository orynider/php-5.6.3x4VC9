
/* pngtarith.c
 */
#define _POSIX_SOURCE 1

/* Obtain a copy of the code to be tested (plus other things), disabling
 * stuff that is not required.
 */
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "pngpriv.h"
#include "png.h"

#define png_error png_fixed_warning
#define png_fixed_error png_fixed_warning

void png_fixed_warning(png_const_structrp png_ptr, png_const_charp msg)
{
   fprintf(stderr, "overflow in: %s\n", msg);
}

#define png_set_error_fn(pp, ep, efp, wfp) ((void)0)
#define png_malloc(pp, s) malloc(s)
#define png_malloc_warn(pp, s) malloc(s)
#define png_malloc_base(pp, s) malloc(s)
#define png_calloc(pp, s) calloc(1, (s))
#define png_free(pp, s) free(s)

#define png_safecat(b, sb, pos, str) (pos)
#define png_format_number(start, end, format, number) (start)

#define crc32(crc, pp, s) (crc)
#define inflateReset(zs) Z_OK

#define png_create_struct(type) (0)
#define png_destroy_struct(pp) ((void)0)
#define png_create_struct_2(type, m, mm) (0)
#define png_destroy_struct_2(pp, f, mm) ((void)0)


/* Validate ASCII to fp routines. */
static int verbose = 0;

/* Observe that valid FP numbers have the forms listed in the PNG extensions
 * specification:
 *
 * [+,-]{integer,integer.fraction,.fraction}[{e,E}[+,-]integer]

/* The characters (other than digits) that characterize the states: */
static const char none[] = "";
static const char hexdigits[16] = "0123456789ABCDEF";

#ifdef PNG_FLOATING_ARITHMETIC_SUPPORTED
#define LN2 .000010576586617430806112933839 /* log(2)/65536 */
#define L2INV 94548.46219969910586572651    /* 65536/log(2) */
#endif /* FLOATING_ARITHMETIC */


#define COUNT 1000000000