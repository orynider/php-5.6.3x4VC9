/*
  This file is part of libXMLRPC - a C library for xml-encoded function calls.

  Author: Dan Libby (dan@libby.com)
  Epinions.com may be contacted at feedback@epinions-inc.com
*/

/*  
  Copyright 2000 Epinions, Inc. 

  Subject to the following 3 conditions, Epinions, Inc.  permits you, free 
  of charge, to (a) use, copy, distribute, modify, perform and display this 
  software and associated documentation files (the "Software"), and (b) 
  permit others to whom the Software is furnished to do so as well.  

  1) The above copyright notice and this permission notice shall be included 
  without modification in all copies or substantial portions of the 
  Software.  

  2) THE SOFTWARE IS PROVIDED "AS IS", WITHOUT ANY WARRANTY OR CONDITION OF 
  ANY KIND, EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION ANY 
  IMPLIED WARRANTIES OF ACCURACY, MERCHANTABILITY, FITNESS FOR A PARTICULAR 
  PURPOSE OR NONINFRINGEMENT.  

  3) IN NO EVENT SHALL EPINIONS, INC. BE LIABLE FOR ANY DIRECT, INDIRECT, 
  SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES OR LOST PROFITS ARISING OUT 
  OF OR IN CONNECTION WITH THE SOFTWARE (HOWEVER ARISING, INCLUDING 
  NEGLIGENCE), EVEN IF EPINIONS, INC.  IS AWARE OF THE POSSIBILITY OF SUCH 
  DAMAGES.    

*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef PHP_WIN32
#include <php_config.h>
#else
#include <config.w32.h>
#include <stdlib.h>
#endif

static const char rcsid[] = "#(@) $Id$";

#include <errno.h>

#ifdef HAVE_GICONV_H
#include <giconv.h>
#else
#include <iconv.h>
#endif

#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "lib\config.h"
#include "lib\localcharset.h"

#ifdef __CYGWIN__
#include <cygwin/version.h>
#endif

#if ENABLE_EXTRA
/*
 * Consider all system dependent encodings, for any system,
 * and the extra encodings.
 */
#define USE_AIX
#define USE_OSF1
#define USE_DOS
#define USE_EXTRA
#else
/*
 * Consider those system dependent encodings that are needed for the
 * current system.
 */
#ifdef _AIX
#define USE_AIX
#endif
#if defined(__osf__) || defined(VMS)
#define USE_OSF1
#endif
#if defined(__DJGPP__) || (defined(_WIN32) && (defined(_MSC_VER) || defined(__MINGW32__)))
#define USE_DOS
#endif
#endif

/*
 * Data type for general conversion loop.
 */
struct loop_funcs {
  size_t (*loop_convert) (iconv_t icd,
                          const char* * inbuf, size_t *inbytesleft,
                          char* * outbuf, size_t *outbytesleft);
  size_t (*loop_reset) (iconv_t icd,
                        char* * outbuf, size_t *outbytesleft);
};

/*
 * Converters.
 */
#include "lib\converters.h"

/*
 * Transliteration tables.
 */
#include "lib\cjk_variants.h"
#include "lib\translit.h"


#if defined __APPLE__ && defined __MACH__ && HAVE_LANGINFO_CODESET
# define DARWIN7 /* Darwin 7 or newer, i.e. Mac OS X 10.3 or newer */
#endif

#if defined _WIN32 || defined __WIN32__
# define WINDOWS_NATIVE
# include <locale.h>
#endif

#if defined __EMX__
/* Assume EMX program runs on OS/2, even if compiled under DOS.  */
# ifndef OS2
#  define OS2
# endif
#endif

#if !defined WINDOWS_NATIVE
# include <unistd.h>
# if HAVE_LANGINFO_CODESET
#  include <langinfo.h>
# else
#  if 0 /* see comment below */
#   include <locale.h>
#  endif
# endif
# ifdef __CYGWIN__
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
# endif
#elif defined WINDOWS_NATIVE
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#endif
#if defined OS2
# define INCL_DOS
# include <os2.h>
#endif

/* For MB_CUR_MAX_L */
#if defined DARWIN7
# include <xlocale.h>
#endif

#if ENABLE_RELOCATABLE
# include "relocatable.h"
#else
# define relocate(pathname) (pathname)
#endif

/* Get LIBDIR.  */
#ifndef LIBDIR
# include "config.h"
#endif

/* Define O_NOFOLLOW to 0 on platforms where it does not exist.  */
#ifndef O_NOFOLLOW
# define O_NOFOLLOW 0
#endif

#if defined _WIN32 || defined __WIN32__ || defined __CYGWIN__ || defined __EMX__ || defined __DJGPP__
  /* Native Windows, Cygwin, OS/2, DOS */
# define ISSLASH(C) ((C) == '/' || (C) == '\\')
#endif

#ifndef DIRECTORY_SEPARATOR
# define DIRECTORY_SEPARATOR '/'
#endif

#ifndef ISSLASH
# define ISSLASH(C) ((C) == DIRECTORY_SEPARATOR)
#endif

#if HAVE_DECL_GETC_UNLOCKED
# undef getc
# define getc getc_unlocked
#endif

/* The following static variable is declared 'volatile' to avoid a
   possible multithread problem in the function get_charset_aliases. If we
   are running in a threaded environment, and if two threads initialize
   'charset_aliases' simultaneously, both will produce the same value,
   and everything will be ok if the two assignments to 'charset_aliases'
   are atomic. But I don't know what will happen if the two assignments mix.  */
#if __STDC__ != 1
# define volatile /* empty */
#endif
/* Pointer to the contents of the charset.alias file, if it has already been
   read, else NULL.  Its format is:
   ALIAS_1 '\0' CANONICAL_1 '\0' ... ALIAS_n '\0' CANONICAL_n '\0' '\0'  */
static const char * volatile charset_aliases;

/* Return a pointer to the contents of the charset.alias file.  */
static const char *
get_charset_aliases (void)
{
  const char *cp;

  cp = charset_aliases;
  if (cp == NULL)
    {
#if !(defined DARWIN7 || defined VMS || defined WINDOWS_NATIVE || defined __CYGWIN__ || defined OS2)
      const char *dir;
      const char *base = "charset.alias";
      char *file_name;

      /* Make it possible to override the charset.alias location.  This is
         necessary for running the testsuite before "make install".  */
      dir = getenv ("CHARSETALIASDIR");
      if (dir == NULL || dir[0] == '\0')
        dir = relocate (LIBDIR);

      /* Concatenate dir and base into freshly allocated file_name.  */
      {
        size_t dir_len = strlen (dir);
        size_t base_len = strlen (base);
        int add_slash = (dir_len > 0 && !ISSLASH (dir[dir_len - 1]));
        file_name = (char *) malloc (dir_len + add_slash + base_len + 1);
        if (file_name != NULL)
          {
            memcpy (file_name, dir, dir_len);
            if (add_slash)
              file_name[dir_len] = DIRECTORY_SEPARATOR;
            memcpy (file_name + dir_len + add_slash, base, base_len + 1);
          }
      }

      if (file_name == NULL)
        /* Out of memory.  Treat the file as empty.  */
        cp = "";
      else
        {
          int fd;

          /* Open the file.  Reject symbolic links on platforms that support
             O_NOFOLLOW.  This is a security feature.  Without it, an attacker
             could retrieve parts of the contents (namely, the tail of the
             first line that starts with "* ") of an arbitrary file by placing
             a symbolic link to that file under the name "charset.alias" in
             some writable directory and defining the environment variable
             CHARSETALIASDIR to point to that directory.  */
          fd = open (file_name,
                     O_RDONLY | (HAVE_WORKING_O_NOFOLLOW ? O_NOFOLLOW : 0));
          if (fd < 0)
            /* File not found.  Treat it as empty.  */
            cp = "";
          else
            {
              FILE *fp;

              fp = fdopen (fd, "r");
              if (fp == NULL)
                {
                  /* Out of memory.  Treat the file as empty.  */
                  close (fd);
                  cp = "";
                }
              else
                {
                  /* Parse the file's contents.  */
                  char *res_ptr = NULL;
                  size_t res_size = 0;

                  for (;;)
                    {
                      int c;
                      char buf1[50+1];
                      char buf2[50+1];
                      size_t l1, l2;
                      char *old_res_ptr;

                      c = getc (fp);
                      if (c == EOF)
                        break;
                      if (c == '\n' || c == ' ' || c == '\t')
                        continue;
                      if (c == '#')
                        {
                          /* Skip comment, to end of line.  */
                          do
                            c = getc (fp);
                          while (!(c == EOF || c == '\n'));
                          if (c == EOF)
                            break;
                          continue;
                        }
                      ungetc (c, fp);
                      if (fscanf (fp, "%50s %50s", buf1, buf2) < 2)
                        break;
                      l1 = strlen (buf1);
                      l2 = strlen (buf2);
                      old_res_ptr = res_ptr;
                      if (res_size == 0)
                        {
                          res_size = l1 + 1 + l2 + 1;
                          res_ptr = (char *) malloc (res_size + 1);
                        }
                      else
                        {
                          res_size += l1 + 1 + l2 + 1;
                          res_ptr = (char *) realloc (res_ptr, res_size + 1);
                        }
                      if (res_ptr == NULL)
                        {
                          /* Out of memory. */
                          res_size = 0;
                          free (old_res_ptr);
                          break;
                        }
                      strcpy (res_ptr + res_size - (l2 + 1) - (l1 + 1), buf1);
                      strcpy (res_ptr + res_size - (l2 + 1), buf2);
                    }
                  fclose (fp);
                  if (res_size == 0)
                    cp = "";
                  else
                    {
                      *(res_ptr + res_size) = '\0';
                      cp = res_ptr;
                    }
                }
            }

          free (file_name);
        }

#else

# if defined DARWIN7
      /* To avoid the trouble of installing a file that is shared by many
         GNU packages -- many packaging systems have problems with this --,
         simply inline the aliases here.  */
      cp = "ISO8859-1" "\0" "ISO-8859-1" "\0"
           "ISO8859-2" "\0" "ISO-8859-2" "\0"
           "ISO8859-4" "\0" "ISO-8859-4" "\0"
           "ISO8859-5" "\0" "ISO-8859-5" "\0"
           "ISO8859-7" "\0" "ISO-8859-7" "\0"
           "ISO8859-9" "\0" "ISO-8859-9" "\0"
           "ISO8859-13" "\0" "ISO-8859-13" "\0"
           "ISO8859-15" "\0" "ISO-8859-15" "\0"
           "KOI8-R" "\0" "KOI8-R" "\0"
           "KOI8-U" "\0" "KOI8-U" "\0"
           "CP866" "\0" "CP866" "\0"
           "CP949" "\0" "CP949" "\0"
           "CP1131" "\0" "CP1131" "\0"
           "CP1251" "\0" "CP1251" "\0"
           "eucCN" "\0" "GB2312" "\0"
           "GB2312" "\0" "GB2312" "\0"
           "eucJP" "\0" "EUC-JP" "\0"
           "eucKR" "\0" "EUC-KR" "\0"
           "Big5" "\0" "BIG5" "\0"
           "Big5HKSCS" "\0" "BIG5-HKSCS" "\0"
           "GBK" "\0" "GBK" "\0"
           "GB18030" "\0" "GB18030" "\0"
           "SJIS" "\0" "SHIFT_JIS" "\0"
           "ARMSCII-8" "\0" "ARMSCII-8" "\0"
           "PT154" "\0" "PT154" "\0"
         /*"ISCII-DEV" "\0" "?" "\0"*/
           "*" "\0" "UTF-8" "\0";
# endif

# if defined VMS
      /* To avoid the troubles of an extra file charset.alias_vms in the
         sources of many GNU packages, simply inline the aliases here.  */
      /* The list of encodings is taken from the OpenVMS 7.3-1 documentation
         "Compaq C Run-Time Library Reference Manual for OpenVMS systems"
         section 10.7 "Handling Different Character Sets".  */
      cp = "ISO8859-1" "\0" "ISO-8859-1" "\0"
           "ISO8859-2" "\0" "ISO-8859-2" "\0"
           "ISO8859-5" "\0" "ISO-8859-5" "\0"
           "ISO8859-7" "\0" "ISO-8859-7" "\0"
           "ISO8859-8" "\0" "ISO-8859-8" "\0"
           "ISO8859-9" "\0" "ISO-8859-9" "\0"
           /* Japanese */
           "eucJP" "\0" "EUC-JP" "\0"
           "SJIS" "\0" "SHIFT_JIS" "\0"
           "DECKANJI" "\0" "DEC-KANJI" "\0"
           "SDECKANJI" "\0" "EUC-JP" "\0"
           /* Chinese */
           "eucTW" "\0" "EUC-TW" "\0"
           "DECHANYU" "\0" "DEC-HANYU" "\0"
           "DECHANZI" "\0" "GB2312" "\0"
           /* Korean */
           "DECKOREAN" "\0" "EUC-KR" "\0";
# endif

# if defined WINDOWS_NATIVE || defined __CYGWIN__
      /* To avoid the troubles of installing a separate file in the same
         directory as the DLL and of retrieving the DLL's directory at
         runtime, simply inline the aliases here.  */

      cp = "CP936" "\0" "GBK" "\0"
           "CP1361" "\0" "JOHAB" "\0"
           "CP20127" "\0" "ASCII" "\0"
           "CP20866" "\0" "KOI8-R" "\0"
           "CP20936" "\0" "GB2312" "\0"
           "CP21866" "\0" "KOI8-RU" "\0"
           "CP28591" "\0" "ISO-8859-1" "\0"
           "CP28592" "\0" "ISO-8859-2" "\0"
           "CP28593" "\0" "ISO-8859-3" "\0"
           "CP28594" "\0" "ISO-8859-4" "\0"
           "CP28595" "\0" "ISO-8859-5" "\0"
           "CP28596" "\0" "ISO-8859-6" "\0"
           "CP28597" "\0" "ISO-8859-7" "\0"
           "CP28598" "\0" "ISO-8859-8" "\0"
           "CP28599" "\0" "ISO-8859-9" "\0"
           "CP28605" "\0" "ISO-8859-15" "\0"
           "CP38598" "\0" "ISO-8859-8" "\0"
           "CP51932" "\0" "EUC-JP" "\0"
           "CP51936" "\0" "GB2312" "\0"
           "CP51949" "\0" "EUC-KR" "\0"
           "CP51950" "\0" "EUC-TW" "\0"
           "CP54936" "\0" "GB18030" "\0"
           "CP65001" "\0" "UTF-8" "\0";
# endif
# if defined OS2
      /* To avoid the troubles of installing a separate file in the same
         directory as the DLL and of retrieving the DLL's directory at
         runtime, simply inline the aliases here.  */

      /* The list of encodings is taken from "List of OS/2 Codepages"
         by Alex Taylor:
         <http://altsan.org/os2/toolkits/uls/index.html#codepages>.
         See also "IBM Globalization - Code page identifiers":
         <http://www-01.ibm.com/software/globalization/cp/cp_cpgid.html>.  */
      cp = "CP813" "\0" "ISO-8859-7" "\0"
           "CP878" "\0" "KOI8-R" "\0"
           "CP819" "\0" "ISO-8859-1" "\0"
           "CP912" "\0" "ISO-8859-2" "\0"
           "CP913" "\0" "ISO-8859-3" "\0"
           "CP914" "\0" "ISO-8859-4" "\0"
           "CP915" "\0" "ISO-8859-5" "\0"
           "CP916" "\0" "ISO-8859-8" "\0"
           "CP920" "\0" "ISO-8859-9" "\0"
           "CP921" "\0" "ISO-8859-13" "\0"
           "CP923" "\0" "ISO-8859-15" "\0"
           "CP954" "\0" "EUC-JP" "\0"
           "CP964" "\0" "EUC-TW" "\0"
           "CP970" "\0" "EUC-KR" "\0"
           "CP1089" "\0" "ISO-8859-6" "\0"
           "CP1208" "\0" "UTF-8" "\0"
           "CP1381" "\0" "GB2312" "\0"
           "CP1386" "\0" "GBK" "\0"
           "CP3372" "\0" "EUC-JP" "\0";
# endif
#endif

      charset_aliases = cp;
    }

  return cp;
}

/* Determine the current locale's character encoding, and canonicalize it
   into one of the canonical names listed in config.charset.
   The result must not be freed; it is statically allocated.
   If the canonical name cannot be determined, the result is a non-canonical
   name.  */

#ifdef STATIC
STATIC
#endif
const char *
locale_charset (void)
{
  const char *codeset;
  const char *aliases;

#if !(defined WINDOWS_NATIVE || defined OS2)

# if HAVE_LANGINFO_CODESET

  /* Most systems support nl_langinfo (CODESET) nowadays.  */
  codeset = nl_langinfo (CODESET);

#  ifdef __CYGWIN__
  /* Cygwin < 1.7 does not have locales.  nl_langinfo (CODESET) always
     returns "US-ASCII".  Return the suffix of the locale name from the
     environment variables (if present) or the codepage as a number.  */
  if (codeset != NULL && strcmp (codeset, "US-ASCII") == 0)
    {
      const char *locale;
      static char buf[2 + 10 + 1];

      locale = getenv ("LC_ALL");
      if (locale == NULL || locale[0] == '\0')
        {
          locale = getenv ("LC_CTYPE");
          if (locale == NULL || locale[0] == '\0')
            locale = getenv ("LANG");
        }
      if (locale != NULL && locale[0] != '\0')
        {
          /* If the locale name contains an encoding after the dot, return
             it.  */
          const char *dot = strchr (locale, '.');

          if (dot != NULL)
            {
              const char *modifier;

              dot++;
              /* Look for the possible @... trailer and remove it, if any.  */
              modifier = strchr (dot, '@');
              if (modifier == NULL)
                return dot;
              if (modifier - dot < sizeof (buf))
                {
                  memcpy (buf, dot, modifier - dot);
                  buf [modifier - dot] = '\0';
                  return buf;
                }
            }
        }

      /* The Windows API has a function returning the locale's codepage as a
         number: GetACP().  This encoding is used by Cygwin, unless the user
         has set the environment variable CYGWIN=codepage:oem (which very few
         people do).
         Output directed to console windows needs to be converted (to
         GetOEMCP() if the console is using a raster font, or to
         GetConsoleOutputCP() if it is using a TrueType font).  Cygwin does
         this conversion transparently (see winsup/cygwin/fhandler_console.cc),
         converting to GetConsoleOutputCP().  This leads to correct results,
         except when SetConsoleOutputCP has been called and a raster font is
         in use.  */
      sprintf (buf, "CP%u", GetACP ());
      codeset = buf;
    }
#  endif

# else

  /* On old systems which lack it, use setlocale or getenv.  */
  const char *locale = NULL;

  /* But most old systems don't have a complete set of locales.  Some
     (like SunOS 4 or DJGPP) have only the C locale.  Therefore we don't
     use setlocale here; it would return "C" when it doesn't support the
     locale name the user has set.  */
#  if 0
  locale = setlocale (LC_CTYPE, NULL);
#  endif
  if (locale == NULL || locale[0] == '\0')
    {
      locale = getenv ("LC_ALL");
      if (locale == NULL || locale[0] == '\0')
        {
          locale = getenv ("LC_CTYPE");
          if (locale == NULL || locale[0] == '\0')
            locale = getenv ("LANG");
        }
    }

  /* On some old systems, one used to set locale = "iso8859_1". On others,
     you set it to "language_COUNTRY.charset". In any case, we resolve it
     through the charset.alias file.  */
  codeset = locale;

# endif

#elif defined WINDOWS_NATIVE

  static char buf[2 + 10 + 1];

  /* The Windows API has a function returning the locale's codepage as
     a number, but the value doesn't change according to what the
     'setlocale' call specified.  So we use it as a last resort, in
     case the string returned by 'setlocale' doesn't specify the
     codepage.  */
  char *current_locale = setlocale (LC_ALL, NULL);
  char *pdot;

  /* If they set different locales for different categories,
     'setlocale' will return a semi-colon separated list of locale
     values.  To make sure we use the correct one, we choose LC_CTYPE.  */
  if (strchr (current_locale, ';'))
    current_locale = setlocale (LC_CTYPE, NULL);

  pdot = strrchr (current_locale, '.');
  if (pdot && 2 + strlen (pdot + 1) + 1 <= sizeof (buf))
    sprintf (buf, "CP%s", pdot + 1);
  else
    {
      /* The Windows API has a function returning the locale's codepage as a
        number: GetACP().
        When the output goes to a console window, it needs to be provided in
        GetOEMCP() encoding if the console is using a raster font, or in
        GetConsoleOutputCP() encoding if it is using a TrueType font.
        But in GUI programs and for output sent to files and pipes, GetACP()
        encoding is the best bet.  */
      sprintf (buf, "CP%u", GetACP ());
    }
  codeset = buf;

#elif defined OS2

  const char *locale;
  static char buf[2 + 10 + 1];
  ULONG cp[3];
  ULONG cplen;

  codeset = NULL;

  /* Allow user to override the codeset, as set in the operating system,
     with standard language environment variables.  */
  locale = getenv ("LC_ALL");
  if (locale == NULL || locale[0] == '\0')
    {
      locale = getenv ("LC_CTYPE");
      if (locale == NULL || locale[0] == '\0')
        locale = getenv ("LANG");
    }
  if (locale != NULL && locale[0] != '\0')
    {
      /* If the locale name contains an encoding after the dot, return it.  */
      const char *dot = strchr (locale, '.');

      if (dot != NULL)
        {
          const char *modifier;

          dot++;
          /* Look for the possible @... trailer and remove it, if any.  */
          modifier = strchr (dot, '@');
          if (modifier == NULL)
            return dot;
          if (modifier - dot < sizeof (buf))
            {
              memcpy (buf, dot, modifier - dot);
              buf [modifier - dot] = '\0';
              return buf;
            }
        }

      /* For the POSIX locale, don't use the system's codepage.  */
      if (strcmp (locale, "C") == 0 || strcmp (locale, "POSIX") == 0)
        codeset = "";
    }

  if (codeset == NULL)
    {
      /* OS/2 has a function returning the locale's codepage as a number.  */
      if (DosQueryCp (sizeof (cp), cp, &cplen))
        codeset = "";
      else
        {
          sprintf (buf, "CP%u", cp[0]);
          codeset = buf;
        }
    }

#endif

  if (codeset == NULL)
    /* The canonical name cannot be determined.  */
    codeset = "";

  /* Resolve alias. */
  for (aliases = get_charset_aliases ();
       *aliases != '\0';
       aliases += strlen (aliases) + 1, aliases += strlen (aliases) + 1)
    if (strcmp (codeset, aliases) == 0
        || (aliases[0] == '*' && aliases[1] == '\0'))
      {
        codeset = aliases + strlen (aliases) + 1;
        break;
      }

  /* Don't return an empty string.  GNU libc and GNU libiconv interpret
     the empty string as denoting "the locale's character encoding",
     thus GNU libiconv would call this function a second time.  */
  if (codeset[0] == '\0')
    codeset = "ASCII";

#ifdef DARWIN7
  /* Mac OS X sets MB_CUR_MAX to 1 when LC_ALL=C, and "UTF-8"
     (the default codeset) does not work when MB_CUR_MAX is 1.  */
  if (strcmp (codeset, "UTF-8") == 0 && MB_CUR_MAX_L (uselocale (NULL)) <= 1)
    codeset = "ASCII";
#endif

  return codeset;
}



/*
 * Table of all supported encodings.
 */
struct encoding {
  struct mbtowc_funcs ifuncs; /* conversion multibyte -> unicode */
  struct wctomb_funcs ofuncs; /* conversion unicode -> multibyte */
  int oflags;                 /* flags for unicode -> multibyte conversion */
};
#define DEFALIAS(xxx_alias,xxx) /* nothing */
enum {
#define DEFENCODING(xxx_names,xxx,xxx_ifuncs1,xxx_ifuncs2,xxx_ofuncs1,xxx_ofuncs2) \
  ei_##xxx ,
#include "lib\encodings.def"
#ifdef USE_AIX
# include "lib\encodings_aix.def"
#endif
#ifdef USE_OSF1
# include "lib\encodings_osf1.def"
#endif
#ifdef USE_DOS
# include "lib\encodings_dos.def"
#endif
#ifdef USE_EXTRA
# include "lib\encodings_extra.def"
#endif
#include "lib\encodings_local.def"
#undef DEFENCODING
ei_for_broken_compilers_that_dont_like_trailing_commas
};
#include "lib\flags.h"
static struct encoding const all_encodings[] = {
#define DEFENCODING(xxx_names,xxx,xxx_ifuncs1,xxx_ifuncs2,xxx_ofuncs1,xxx_ofuncs2) \
  { xxx_ifuncs1,xxx_ifuncs2, xxx_ofuncs1,xxx_ofuncs2, ei_##xxx##_oflags },
#include "lib\encodings.def"
#ifdef USE_AIX
# include "lib\encodings_aix.def"
#endif
#ifdef USE_OSF1
# include "lib\encodings_osf1.def"
#endif
#ifdef USE_DOS
# include "lib\encodings_dos.def"
#endif
#ifdef USE_EXTRA
# include "lib\encodings_extra.def"
#endif
#undef DEFENCODING
#define DEFENCODING(xxx_names,xxx,xxx_ifuncs1,xxx_ifuncs2,xxx_ofuncs1,xxx_ofuncs2) \
  { xxx_ifuncs1,xxx_ifuncs2, xxx_ofuncs1,xxx_ofuncs2, 0 },
#include "lib\encodings_local.def"
#undef DEFENCODING
};
#undef DEFALIAS

/*
 * Conversion loops.
 */
#include "lib\loops.h"

/*
 * Alias lookup function.
 * Defines
 *   struct alias { int name; unsigned int encoding_index; };
 *   const struct alias * aliases_lookup (const char *str, unsigned int len);
 *   #define MAX_WORD_LENGTH ...
 */
#if defined _AIX
# include "lib\aliases_sysaix.h"
#elif defined hpux || defined __hpux
# include "lib\aliases_syshpux.h"
#elif defined __osf__
# include "lib\aliases_sysosf1.h"
#elif defined __sun
# include "lib\aliases_syssolaris.h"
#else
# include "lib\aliases.h"
#endif

/*
 * System dependent alias lookup function.
 * Defines
 *   const struct alias * aliases2_lookup (const char *str);
 */
#if defined(USE_AIX) || defined(USE_OSF1) || defined(USE_DOS) || defined(USE_EXTRA) /* || ... */
struct stringpool2_t {
#define S(tag,name,encoding_index) char stringpool_##tag[sizeof(name)];
#include "lib\aliases2.h"
#undef S
};
static const struct stringpool2_t stringpool2_contents = {
#define S(tag,name,encoding_index) name,
#include "lib\aliases2.h"
#undef S
};
#define stringpool2 ((const char *) &stringpool2_contents)
static const struct alias sysdep_aliases[] = {
#define S(tag,name,encoding_index) { (int)(long)&((struct stringpool2_t *)0)->stringpool_##tag, encoding_index },
#include "lib\aliases2.h"
#undef S
};
#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static const struct alias *
aliases2_lookup (register const char *str)
{
  const struct alias * ptr;
  unsigned int count;
  for (ptr = sysdep_aliases, count = sizeof(sysdep_aliases)/sizeof(sysdep_aliases[0]); count > 0; ptr++, count--)
    if (!strcmp(str, stringpool2 + ptr->name))
      return ptr;
  return NULL;
}
#else
#define aliases2_lookup(str)  NULL
#define stringpool2  NULL
#endif

#if 0
/* Like !strcasecmp, except that the both strings can be assumed to be ASCII
   and the first string can be assumed to be in uppercase. */
static int strequal (const char* str1, const char* str2)
{
  unsigned char c1;
  unsigned char c2;
  for (;;) {
    c1 = * (unsigned char *) str1++;
    c2 = * (unsigned char *) str2++;
    if (c1 == 0)
      break;
    if (c2 >= 'a' && c2 <= 'z')
      c2 -= 'a'-'A';
    if (c1 != c2)
      break;
  }
  return (c1 == c2);
}
#endif

iconv_t iconv_open (const char* tocode, const char* fromcode)
{
  struct conv_struct * cd;
  unsigned int from_index;
  int from_wchar;
  unsigned int to_index;
  int to_wchar;
  int transliterate;
  int discard_ilseq;

#include "lib\iconv_open1.h"

  cd = (struct conv_struct *) malloc(from_wchar != to_wchar
                                     ? sizeof(struct wchar_conv_struct)
                                     : sizeof(struct conv_struct));
  if (cd == NULL) {
    errno = ENOMEM;
    return (iconv_t)(-1);
  }

#include "lib\iconv_open2.h"

  return (iconv_t)cd;
invalid:
  errno = EINVAL;
  return (iconv_t)(-1);
}

size_t iconv (iconv_t icd, ICONV_CONST char* * inbuf, size_t *inbytesleft, char* * outbuf, size_t *outbytesleft)
{
  conv_t cd = (conv_t) icd;
  if (inbuf == NULL || *inbuf == NULL)
    return cd->lfuncs.loop_reset(icd,outbuf,outbytesleft);
  else
    return cd->lfuncs.loop_convert(icd, (const char* *)inbuf,inbytesleft, outbuf,outbytesleft);
}

int iconv_close (iconv_t icd)
{
  conv_t cd = (conv_t) icd;
  free(cd);
  return 0;
}

#ifndef LIBICONV_PLUG

/*
 * Verify that a 'struct conv_struct' and a 'struct wchar_conv_struct' each
 * fit in an iconv_allocation_t.
 * If this verification fails, iconv_allocation_t must be made larger and
 * the major version in LIBICONV_VERSION_INFO must be bumped.
 * Currently 'struct conv_struct' has 21 integer/pointer fields, and
 * 'struct wchar_conv_struct' additionally has an 'mbstate_t' field.
 */
typedef int verify_size_1[2 * (sizeof (struct conv_struct) <= sizeof (iconv_allocation_t)) - 1];
typedef int verify_size_2[2 * (sizeof (struct wchar_conv_struct) <= sizeof (iconv_allocation_t)) - 1];

int iconv_open_into (const char* tocode, const char* fromcode,
                     iconv_allocation_t* resultp)
{
  struct conv_struct * cd;
  unsigned int from_index;
  int from_wchar;
  unsigned int to_index;
  int to_wchar;
  int transliterate;
  int discard_ilseq;

#include "lib\iconv_open1.h"

  cd = (struct conv_struct *) resultp;

#include "lib\iconv_open2.h"

  return 0;
invalid:
  errno = EINVAL;
  return -1;
}

int iconvctl (iconv_t icd, int request, void* argument)
{
  conv_t cd = (conv_t) icd;
  switch (request) {
    case ICONV_TRIVIALP:
      *(int *)argument =
        ((cd->lfuncs.loop_convert == unicode_loop_convert
          && cd->iindex == cd->oindex)
         || cd->lfuncs.loop_convert == wchar_id_loop_convert
         ? 1 : 0);
      return 0;
    case ICONV_GET_TRANSLITERATE:
      *(int *)argument = cd->transliterate;
      return 0;
    case ICONV_SET_TRANSLITERATE:
      cd->transliterate = (*(const int *)argument ? 1 : 0);
      return 0;
    case ICONV_GET_DISCARD_ILSEQ:
      *(int *)argument = cd->discard_ilseq;
      return 0;
    case ICONV_SET_DISCARD_ILSEQ:
      cd->discard_ilseq = (*(const int *)argument ? 1 : 0);
      return 0;
    case ICONV_SET_HOOKS:
      if (argument != NULL) {
        cd->hooks = *(const struct iconv_hooks *)argument;
      } else {
        cd->hooks.uc_hook = NULL;
        cd->hooks.wc_hook = NULL;
        cd->hooks.data = NULL;
      }
      return 0;
    case ICONV_SET_FALLBACKS:
      if (argument != NULL) {
        cd->fallbacks = *(const struct iconv_fallbacks *)argument;
      } else {
        cd->fallbacks.mb_to_uc_fallback = NULL;
        cd->fallbacks.uc_to_mb_fallback = NULL;
        cd->fallbacks.mb_to_wc_fallback = NULL;
        cd->fallbacks.wc_to_mb_fallback = NULL;
        cd->fallbacks.data = NULL;
      }
      return 0;
    default:
      errno = EINVAL;
      return -1;
  }
}

/* An alias after its name has been converted from 'int' to 'const char*'. */
struct nalias { const char* name; unsigned int encoding_index; };

static int compare_by_index (const void * arg1, const void * arg2)
{
  const struct nalias * alias1 = (const struct nalias *) arg1;
  const struct nalias * alias2 = (const struct nalias *) arg2;
  return (int)alias1->encoding_index - (int)alias2->encoding_index;
}

static int compare_by_name (const void * arg1, const void * arg2)
{
  const char * name1 = *(const char **)arg1;
  const char * name2 = *(const char **)arg2;
  /* Compare alphabetically, but put "CS" names at the end. */
  int sign = strcmp(name1,name2);
  if (sign != 0) {
    sign = ((name1[0]=='C' && name1[1]=='S') - (name2[0]=='C' && name2[1]=='S'))
           * 4 + (sign >= 0 ? 1 : -1);
  }
  return sign;
}

void iconvlist (int (*do_one) (unsigned int namescount,
                               const char * const * names,
                               void* data),
                void* data)
{
#define aliascount1  sizeof(aliases)/sizeof(aliases[0])
#ifndef aliases2_lookup
#define aliascount2  sizeof(sysdep_aliases)/sizeof(sysdep_aliases[0])
#else
#define aliascount2  0
#endif
#define aliascount  (aliascount1+aliascount2)
  struct nalias aliasbuf[aliascount];
  const char * namesbuf[aliascount];
  size_t num_aliases;
  {
    /* Put all existing aliases into a buffer. */
    size_t i;
    size_t j;
    j = 0;
    for (i = 0; i < aliascount1; i++) {
      const struct alias * p = &aliases[i];
      if (p->name >= 0
          && p->encoding_index != ei_local_char
          && p->encoding_index != ei_local_wchar_t) {
        aliasbuf[j].name = stringpool + p->name;
        aliasbuf[j].encoding_index = p->encoding_index;
        j++;
      }
    }
#ifndef aliases2_lookup
    for (i = 0; i < aliascount2; i++) {
      aliasbuf[j].name = stringpool2 + sysdep_aliases[i].name;
      aliasbuf[j].encoding_index = sysdep_aliases[i].encoding_index;
      j++;
    }
#endif
    num_aliases = j;
  }
  /* Sort by encoding_index. */
  if (num_aliases > 1)
    qsort(aliasbuf, num_aliases, sizeof(struct nalias), compare_by_index);
  {
    /* Process all aliases with the same encoding_index together. */
    size_t j;
    j = 0;
    while (j < num_aliases) {
      unsigned int ei = aliasbuf[j].encoding_index;
      size_t i = 0;
      do
        namesbuf[i++] = aliasbuf[j++].name;
      while (j < num_aliases && aliasbuf[j].encoding_index == ei);
      if (i > 1)
		  qsort(namesbuf, i, sizeof(const char *), compare_by_name);
	  /* Call the callback. */
	  if (do_one(i,namesbuf,data))
		  break;
	}
  }
#undef aliascount
#undef aliascount2
#undef aliascount1
}

/*
 * Table of canonical names of encodings.
 * Instead of strings, it contains offsets into stringpool and stringpool2.
 */
static const unsigned short all_canonical[] = {
#if defined _AIX
# include "lib\canonical_sysaix.h"
#elif defined hpux || defined __hpux
# include "lib\canonical_syshpux.h"
#elif defined __osf__
# include "lib\canonical_sysosf1.h"
#elif defined __sun
# include "lib\canonical_syssolaris.h"
#else
# include "lib\canonical.h"
#endif
#ifdef USE_AIX
# if defined _AIX
#  include "lib\canonical_aix_sysaix.h"
# else
#  include "lib\canonical_aix.h"
# endif
#endif
#ifdef USE_OSF1
# if defined __osf__
#  include "lib\canonical_osf1_sysosf1.h"
# else
#  include "lib\canonical_osf1.h"
# endif
#endif
#ifdef USE_DOS
# include "lib\canonical_dos.h"
#endif
#ifdef USE_EXTRA
# include "lib\canonical_extra.h"
#endif
#if defined _AIX
# include "lib\canonical_local_sysaix.h"
#elif defined hpux || defined __hpux
# include "lib\canonical_local_syshpux.h"
#elif defined __osf__
# include "lib\canonical_local_sysosf1.h"
#elif defined __sun
# include "lib\canonical_local_syssolaris.h"
#else
# include "lib\canonical_local.h"
#endif
};

const char * iconv_canonicalize (const char * name)
{
  const char* code;
  char buf[MAX_WORD_LENGTH+10+1];
  const char* cp;
  char* bp;
  const struct alias * ap;
  unsigned int count;
  unsigned int index;
  const char* pool;

  /* Before calling aliases_lookup, convert the input string to upper case,
   * and check whether it's entirely ASCII (we call gperf with option "-7"
   * to achieve a smaller table) and non-empty. If it's not entirely ASCII,
   * or if it's too long, it is not a valid encoding name.
   */
  for (code = name;;) {
    /* Search code in the table. */
    for (cp = code, bp = buf, count = MAX_WORD_LENGTH+10+1; ; cp++, bp++) {
      unsigned char c = * (unsigned char *) cp;
      if (c >= 0x80)
        goto invalid;
      if (c >= 'a' && c <= 'z')
        c -= 'a'-'A';
      *bp = c;
      if (c == '\0')
        break;
      if (--count == 0)
        goto invalid;
    }
    for (;;) {
      if (bp-buf >= 10 && memcmp(bp-10,"//TRANSLIT",10)==0) {
        bp -= 10;
        *bp = '\0';
        continue;
      }
      if (bp-buf >= 8 && memcmp(bp-8,"//IGNORE",8)==0) {
        bp -= 8;
        *bp = '\0';
        continue;
      }
      break;
    }
    if (buf[0] == '\0') {
      code = locale_charset();
      /* Avoid an endless loop that could occur when using an older version
         of localcharset.c. */
      if (code[0] == '\0')
        goto invalid;
      continue;
    }
    pool = stringpool;
    ap = aliases_lookup(buf,bp-buf);
    if (ap == NULL) {
      pool = stringpool2;
      ap = aliases2_lookup(buf);
      if (ap == NULL)
        goto invalid;
    }
    if (ap->encoding_index == ei_local_char) {
      code = locale_charset();
      /* Avoid an endless loop that could occur when using an older version
         of localcharset.c. */
      if (code[0] == '\0')
        goto invalid;
      continue;
    }
    if (ap->encoding_index == ei_local_wchar_t) {
      /* On systems which define __STDC_ISO_10646__, wchar_t is Unicode.
         This is also the case on native Woe32 systems and Cygwin >= 1.7, where
         we know that it is UTF-16.  */
#if ((defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__) || (defined __CYGWIN__ && CYGWIN_VERSION_DLL_MAJOR >= 1007)
      if (sizeof(wchar_t) == 4) {
        index = ei_ucs4internal;
        break;
      }
      if (sizeof(wchar_t) == 2) {
# if WORDS_LITTLEENDIAN
        index = ei_utf16le;
# else
        index = ei_utf16be;
# endif
        break;
      }
#elif __STDC_ISO_10646__
      if (sizeof(wchar_t) == 4) {
        index = ei_ucs4internal;
        break;
      }
      if (sizeof(wchar_t) == 2) {
        index = ei_ucs2internal;
        break;
      }
      if (sizeof(wchar_t) == 1) {
        index = ei_iso8859_1;
        break;
      }
#endif
    }
    index = ap->encoding_index;
    break;
  }
  return all_canonical[index] + pool;
 invalid:
  return name;
}

int _libiconv_version = _LIBICONV_VERSION;

#if defined __FreeBSD__ && !defined __gnu_freebsd__
/* GNU libiconv is the native FreeBSD iconv implementation since 2002.
   It wants to define the symbols 'iconv_open', 'iconv', 'iconv_close'.
*/
#define strong_alias(name, aliasname) _strong_alias(name, aliasname)
#define _strong_alias(name, aliasname) \
	extern __typeof (name) aliasname __attribute__ ((alias (#name)));
//#undef iconv_open
//#undef iconv
//#undef iconv_close
strong_alias (libiconv_open, iconv_open)
strong_alias (libiconv, iconv)
strong_alias (libiconv_close, iconv_close)
#endif

#endif

#include "encodings.h"

#ifndef ICONV_CSNMAXLEN
#define ICONV_CSNMAXLEN 64
#endif

static char* convert(const char* src, int src_len, int *new_len, const char* from_enc, const char* to_enc) {
   char* outbuf = 0;

   if(src && src_len && from_enc && to_enc) {
      size_t outlenleft = src_len;
      size_t inlenleft = src_len;
      int outlen = src_len;
      iconv_t ic;
      char* out_ptr = 0;

      if(strlen(to_enc) >= ICONV_CSNMAXLEN || strlen(from_enc) >= ICONV_CSNMAXLEN) {
         return NULL;
      }
      ic = iconv_open(to_enc, from_enc);
      if(ic != (iconv_t)-1) {
         size_t st;
         outbuf = (char*)malloc(outlen + 1);

         if(outbuf) {
            out_ptr = (char*)outbuf;
            while(inlenleft) {
               st = iconv(ic, (char**)&src, &inlenleft, &out_ptr, &outlenleft);
               if(st == -1) {
                  if(errno == E2BIG) {
                     int diff = out_ptr - outbuf;
                     outlen += inlenleft;
                     outlenleft += inlenleft;
                     outbuf = (char*)realloc(outbuf, outlen + 1);
                     if(!outbuf) {
                        break;
                     }
                     out_ptr = outbuf + diff;
                  }
                  else {
                     free(outbuf);
                     outbuf = 0;
                     break;
                  }
               }
            }
         }
         iconv_close(ic);
      }
      outlen -= outlenleft;

      if(new_len) {
         *new_len = outbuf ? outlen : 0;
      }
      if(outbuf) {
         outbuf[outlen] = 0;
      }
   }
   return outbuf;
}

/* returns a new string that must be freed */
char* utf8_encode(const char *s, int len, int *newlen, const char* encoding)
{
   return convert(s, len, newlen, encoding, "UTF-8");
}

/* returns a new string, possibly decoded */
char* utf8_decode(const char *s, int len, int *newlen, const char* encoding)
{
   return convert(s, len, newlen, "UTF-8", encoding);
}

