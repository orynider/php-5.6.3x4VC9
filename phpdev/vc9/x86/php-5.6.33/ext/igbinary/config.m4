dnl config.m4 for extension igbinary

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(igbinary, for igbinary support,
dnl Make sure that the comment is aligned:
dnl [  --with-igbinary             Include igbinary support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(igbinary, whether to enable igbinary support,
  [  --enable-igbinary          Enable igbinary support])

if test "$PHP_IGBINARY" != "no"; then
  AC_CHECK_HEADERS([stdbool.h],, AC_MSG_ERROR([stdbool.h not exists]))
  AC_CHECK_HEADERS([stddef.h],, AC_MSG_ERROR([stddef.h not exists]))
  AC_CHECK_HEADERS([stdint.h],, AC_MSG_ERROR([stdint.h not exists]))

  AC_MSG_CHECKING(PHP version)

  AC_TRY_COMPILE([
  #include <$phpincludedir/main/php_version.h>
  ],[
#if PHP_MAJOR_VERSION > 5
#error PHP > 5
#endif
  ],[
  subdir=src/php5
  PHP_IGBINARY_SRC_FILES="$subdir/igbinary.c $subdir/hash_si.c $subdir/hash_si_ptr.c"
  AC_MSG_RESULT([PHP 5])
  ],[
  subdir=src/php7
  PHP_IGBINARY_SRC_FILES="$subdir/igbinary.c $subdir/hash_si.c $subdir/hash_si_ptr.c"
  AC_MSG_RESULT([PHP 7])
  ])

  AC_MSG_CHECKING([for APC/APCU includes])
  if test -f "$phpincludedir/ext/apcu/apc_serializer.h"; then
    apc_inc_path="$phpincludedir"
    AC_MSG_RESULT([APCU in $apc_inc_path])
    AC_DEFINE(HAVE_APCU_SUPPORT,1,[Whether to enable apcu support])
  elif test "$subdir" == src/php5 && test -f "$phpincludedir/ext/apc/apc_serializer.h"; then
    apc_inc_path="$phpincludedir"
    AC_MSG_RESULT([APC in $apc_inc_path])
    AC_DEFINE(HAVE_APC_SUPPORT,1,[Whether to enable apc support])
  elif test "$subdir" == src/php5 && test -f "${srcdir}/$subdir/apc_serializer.h"; then
    AC_MSG_RESULT([apc_serializer.h bundled])
    AC_DEFINE(HAVE_APC_SUPPORT,1,[Whether to enable apc support])
    AC_DEFINE(USE_BUNDLED_APC,1,[Whether to use bundled apc includes])
  else
    AC_MSG_RESULT([not found])
  fi

  AC_CHECK_SIZEOF([long])

  dnl GCC
  AC_MSG_CHECKING(compiler type)
  if test ! -z "`$CC --version | grep -i CLANG`"; then
    AC_MSG_RESULT(clang)
    if test -z "`echo $CFLAGS | grep -- -O0`"; then
      PHP_IGBINARY_CFLAGS="$CFLAGS -Wall -O2"
    fi
  elif test "$GCC" = yes; then
    AC_MSG_RESULT(gcc)
    if test -z "`echo $CFLAGS | grep -- '-O[0123]'`"; then
      PHP_IGBINARY_CFLAGS="$CFLAGS -O2 -Wall -Wpointer-arith -Wmissing-prototypes -Wstrict-prototypes -Wcast-align -Wshadow -Wwrite-strings -Wswitch -finline-limit=10000 --param large-function-growth=10000 --param inline-unit-growth=10000"
    fi
  elif test "$ICC" = yes; then
    AC_MSG_RESULT(icc)
    if test -z "`echo $CFLAGS | grep -- -O0`"; then
      PHP_IGBINARY_CFLAGS="$CFLAGS -no-prec-div -O3 -x0 -unroll2"
    fi
  else
    AC_MSG_RESULT(other)
  fi

  PHP_ADD_MAKEFILE_FRAGMENT(Makefile.bench)
  PHP_INSTALL_HEADERS([ext/igbinary], [igbinary.h $subdir/igbinary.h php_igbinary.h $subdir/php_igbinary.h])
  PHP_NEW_EXTENSION(igbinary, $PHP_IGBINARY_SRC_FILES, $ext_shared,, $PHP_IGBINARY_CFLAGS)
  PHP_ADD_EXTENSION_DEP(igbinary, session, true)
  PHP_ADD_BUILD_DIR($abs_builddir/$subdir, 1)
  PHP_SUBST(IGBINARY_SHARED_LIBADD)
fi
