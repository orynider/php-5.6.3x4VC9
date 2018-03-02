/* Provide relocatable packages.
   Copyright (C) 2003, 2005, 2008-2011 Free Software Foundation, Inc.
   Written by Bruno Haible <bruno@clisp.org>, 2003.

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU Library General Public License as published
   by the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>.  */

#ifndef _RELOCATABLE_H
#define _RELOCATABLE_H

#ifdef __cplusplus
extern "C" {
#endif


/* This can be enabled through the configure --enable-relocatable option.  */
#if ENABLE_RELOCATABLE

/* When building a DLL, we must export some functions.  Note that because
   this is a private .h file, we don't need to use __declspec(dllimport)
   in any case.  */
#if HAVE_VISIBILITY && BUILDING_DLL
# define RELOCATABLE_DLL_EXPORTED __attribute__((__visibility__("default")))
#elif defined _MSC_VER && BUILDING_DLL
# define RELOCATABLE_DLL_EXPORTED __declspec(dllexport)
#else
# define RELOCATABLE_DLL_EXPORTED
#endif

/* Sets the original and the current installation prefix of the package.
   Relocation simply replaces a pathname starting with the original prefix
   by the corresponding pathname with the current prefix instead.  Both
   prefixes should be directory names without trailing slash (i.e. use ""
   instead of "/").  */
extern RELOCATABLE_DLL_EXPORTED void
       set_relocation_prefix (const char *orig_prefix,
                              const char *curr_prefix);
							  
/* Requests for iconvctl. */
#define ICONV_TRIVIALP            0  /* int *argument */
#define ICONV_GET_TRANSLITERATE   1  /* int *argument */
#define ICONV_SET_TRANSLITERATE   2  /* const int *argument */
#define ICONV_GET_DISCARD_ILSEQ   3  /* int *argument */
#define ICONV_SET_DISCARD_ILSEQ   4  /* const int *argument */

/* Listing of locale independent encodings. */
#define iconvlist libiconvlist
extern RELOCATABLE_DLL_EXPORTED void 
			iconvlist (int (*do_one) (unsigned int namescount,
                                      const char * const * names,
                                      void* data),
                       void* data);

/* Support for relocatable packages.  */

/* Sets the original and the current installation prefix of the package.
   Relocation simply replaces a pathname starting with the original prefix
   by the corresponding pathname with the current prefix instead.  Both
   prefixes should be directory names without trailing slash (i.e. use ""
   instead of "/").  */
extern RELOCATABLE_DLL_EXPORTED void libiconv_set_relocation_prefix (const char *orig_prefix, const char *curr_prefix);							  

/* Returns the pathname, relocated according to the current installation
   directory.
   The returned string is either PATHNAME unmodified or a freshly allocated
   string that you can free with free() after casting it to 'char *'.  */
extern const char * relocate (const char *pathname);

/* Memory management: relocate() potentially allocates memory, because it has
   to construct a fresh pathname.  If this is a problem because your program
   calls relocate() frequently, think about caching the result.  Or free the
   return value if it was different from the argument pathname.  */

/* Convenience function:
   Computes the current installation prefix, based on the original
   installation prefix, the original installation directory of a particular
   file, and the current pathname of this file.
   Returns it, freshly allocated.  Returns NULL upon failure.  */
extern char * compute_curr_prefix (const char *orig_installprefix,
                                   const char *orig_installdir,
                                   const char *curr_pathname);

#else

/* By default, we use the hardwired pathnames.  */
#define relocate(pathname) (pathname)

#endif


#ifdef __cplusplus
}
#endif

#endif /* _RELOCATABLE_H */