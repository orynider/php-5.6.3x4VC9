dnl $Id: config.m4,v 1.1.1.2 2001/07/19 00:19:23 zarzycki Exp $
dnl config.m4 for extension mhash
dnl don't forget to call PHP_EXTENSION(mhash)

PHP_ARG_WITH(mhash, for mhash support,
[  --with-mhash[=DIR]      Include mhash support.  DIR is the mhash
                          install directory.])

if test "$PHP_MHASH" != "no"; then
  for i in /usr/local /usr /opt/mhash $PHP_MHASH; do
    if test -f $i/include/mhash.h; then
      MHASH_DIR=$i
    fi
  done

  if test -z "$MHASH_DIR"; then
    AC_MSG_ERROR(Please reinstall libmhash - I cannot find mhash.h)
  fi
  PHP_ADD_INCLUDE($MHASH_DIR/include)
  PHP_ADD_LIBRARY_WITH_PATH(mhash, $MHASH_DIR/lib, MHASH_SHARED_LIBADD)
  PHP_SUBST(MHASH_SHARED_LIBADD)

  AC_DEFINE(HAVE_LIBMHASH,1,[ ])

  PHP_EXTENSION(mhash, $ext_shared)
fi
