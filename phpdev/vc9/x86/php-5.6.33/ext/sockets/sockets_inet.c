/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Authors: FlorincB <orynider@rdslink.ro>                    |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_network.h"
#include "ext/standard/file.h"
#include "ext/standard/info.h"
#include "php_ini.h"

#ifdef PHP_WIN32
# include "windows_common.h"
# include <win32/inet.h>
# include <windows.h>
# include <Ws2tcpip.h>
# include "php_sockets.h"
# include <win32/sockets.h>
# include <errno.h>
#else
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <netinet/tcp.h>
# include <sys/un.h>
# include <arpa/inet.h>
# include <sys/time.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/uio.h>
# define IS_INVALID_SOCKET(a)	(a->bsd_socket < 0)
# define set_errno(a) (//errno = a)
# include "php_sockets.h"
# if HAVE_IF_NAMETOINDEX
#  include <net/if.h>
# endif
#endif

#ifdef PHP_WIN32
#include "win32/php_win32_globals.h"
#include "win32/time.h"
#endif

typedef struct yy_buffer_state *YY_BUFFER_STATE;

#include "zend.h"
#include "zend_ini_scanner.h"
#include "zend_language_scanner.h"
#include <zend_language_parser.h>

#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#ifndef PHP_WIN32
#include <sys/types.h>
#include <sys/stat.h>
#endif

#ifdef NETWARE
#include <netinet/in.h>
#endif

#ifndef PHP_WIN32
# include <netdb.h>
#else
#include "win32/inet.h"
#endif

#if HAVE_ARPA_INET_H
# include <arpa/inet.h>
#endif

#if HAVE_UNISTD_H
# include <unistd.h>
#endif

#if HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif

#if HAVE_LOCALE_H
# include <locale.h>
#endif

#if HAVE_SYS_MMAN_H
# include <sys/mman.h>
#endif

#if HAVE_SYS_LOADAVG_H
# include <sys/loadavg.h>
#endif

#ifdef PHP_WIN32
# include "win32/unistd.h"
#endif

#ifndef INADDR_NONE
#define INADDR_NONE ((unsigned long int) -1)
#endif

#include <stddef.h>

#include "sockaddr_conv.h"
#include "multicast.h"
#include "sendrecvmsg.h"

#ifndef HAVE_IPV6
#include <wspiapi.h>
#define HAVE_GETADDRINFO main_network_has_ipv6
#define HAVE_GAI_STRERROR main_network_has_ipv6
#define HAVE_IPV6 main_network_has_ipv6
#endif

/**
 * @borrowed from file src/inet_pton.c
 *Copyright (C) 1996-2001  Internet Software Consortium.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
*
 * @brief inet_pton for Windows
 * @author http://net-snmp.sourceforge.net
 #ifndef HAVE_INET_PTON
 */

#if HAVE_ARPA_NAMESER_H
#include <arpa/nameser.h>
#endif

  /*
   * Net-SNMP Win32 additions
   */
#if HAVE_WINSOCK_H
#include <winsock2.h>
#include <errno.h>
#include <stdio.h>
#endif

#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT            WSAEAFNOSUPPORT
#endif

#ifndef IN6ADDRSZ
#define	IN6ADDRSZ	16
#endif

#ifndef INT16SZ
#define	INT16SZ		2
#endif
  /*
   * End of Net-SNMP Win32 additions
   */

#ifndef INADDRSZ
#define	INADDRSZ	4
#endif

/*
 *  Don't even consider trying to compile this on a system where
 * sizeof(int) < 4.  sizeof(int) > 4 is fine; all the world's not a VAX.
 */

int inet_pton324(const char *src, u_char *dst, int pton);
#if USE_IPV6
int inet_pton326(const char *src, u_char *dst);
#endif

/* int
 * inet_pton(af, src, dst)
 *	convert from presentation format (which usually means ASCII printable)
 *	to network format (which is usually some kind of binary format).
 * return:
 *	1 if the address was valid for the specified address family
 *	0 if the address wasn't valid (`dst' is untouched in this case)
 *	-1 if some other error occurred (`dst' is untouched in this case, too)
 * author:
 *	Paul Vixie, 1996.
 */
static int inet_pton32(int af, const char *src, void *dst)
{
	switch (af) {
	case AF_INET:
		return (inet_pton324(src, dst, 1));
#if USE_IPV6
	case AF_INET6:
		return (inet_pton326(src, dst));
#endif
	default:
		//errno = EAFNOSUPPORT;
		return (-1);
	}
	/* NOTREACHED */
}
/* int
 * inet_pton4(src, dst, pton)
 *	when last arg is 0: inet_aton(). with hexadecimal, octal and shorthand.
 *	when last arg is 1: inet_pton(). decimal dotted-quad only.
 * return:
 *	1 if `src' is a valid input, else 0.
 * notice:
 *	does not touch `dst' unless it's returning 1.
 * author:
 *	Paul Vixie, 1996.
 */
static int inet_pton324(const char *src, u_char *dst, int pton)
{
	u_int val;
	u_int digit;
	int base, n;
	unsigned char c;
	u_int parts[4];
	register u_int *pp = parts;

	c = *src;
	for (;;) {
		/*
		 * Collect number up to ``.''.
		 * Values are specified as for C:
		 * 0x=hex, 0=octal, isdigit=decimal.
		 */
		if (!isdigit(c))
			return (0);
		val = 0; base = 10;
		if (c == '0') {
			c = *++src;
			if (c == 'x' || c == 'X')
				base = 16, c = *++src;
			else if (isdigit(c) && c != '9')
				base = 8;
		}
		/* inet_pton() takes decimal only */
		if (pton && base != 10)
			return (0);
		for (;;) {
			if (isdigit(c)) {
				digit = c - '0';
				if (digit >= base)
					break;
				val = (val * base) + digit;
				c = *++src;
			} else if (base == 16 && isxdigit(c)) {
				digit = c + 10 - (islower(c) ? 'a' : 'A');
				if (digit >= 16)
					break;
				val = (val << 4) | digit;
				c = *++src;
			} else
				break;
		}
		if (c == '.') {
			/*
			 * Internet format:
			 *	a.b.c.d
			 *	a.b.c	(with c treated as 16 bits)
			 *	a.b	(with b treated as 24 bits)
			 *	a	(with a treated as 32 bits)
			 */
			if (pp >= parts + 3)
				return (0);
			*pp++ = val;
			c = *++src;
		} else
			break;
	}
	/*
	 * Check for trailing characters.
	 */
	if (c != '\0' && !isspace(c))
		return (0);
	/*
	 * Concoct the address according to
	 * the number of parts specified.
	 */
	n = pp - parts + 1;
	/* inet_pton() takes dotted-quad only.  it does not take shorthand. */
	if (pton && n != 4)
		return (0);
	switch (n) {

	case 0:
		return (0);		/* initial nondigit */

	case 1:				/* a -- 32 bits */
		break;

	case 2:				/* a.b -- 8.24 bits */
		if (parts[0] > 0xff || val > 0xffffff)
			return (0);
		val |= parts[0] << 24;
		break;

	case 3:				/* a.b.c -- 8.8.16 bits */
		if ((parts[0] | parts[1]) > 0xff || val > 0xffff)
			return (0);
		val |= (parts[0] << 24) | (parts[1] << 16);
		break;

	case 4:				/* a.b.c.d -- 8.8.8.8 bits */
		if ((parts[0] | parts[1] | parts[2] | val) > 0xff)
			return (0);
		val |= (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8);
		break;
	}
	if (dst) {
		val = htonl(val);
		memcpy(dst, &val, INADDRSZ);
	}
	return (1);
}

#if USE_IPV6
/* int
 * inet_pton6(src, dst)
 *	convert presentation level address to network order binary form.
 * return:
 *	1 if `src' is a valid [RFC1884 2.2] address, else 0.
 * notice:
 *	(1) does not touch `dst' unless it's returning 1.
 *	(2) :: in a full address is silently ignored.
 * credit:
 *	inspired by Mark Andrews.
 * author:
 *	Paul Vixie, 1996.
 */
static int inet_pton326(const char *src, u_char *dst)
{
	static const char xdigits_l[] = "0123456789abcdef",
			  xdigits_u[] = "0123456789ABCDEF";
	u_char tmp[IN6ADDRSZ], *tp, *endp, *colonp;
	const char *xdigits, *curtok;
	int ch, saw_xdigit;
	u_int val;

	memset((tp = tmp), '\0', IN6ADDRSZ);
	endp = tp + IN6ADDRSZ;
	colonp = NULL;
	/* Leading :: requires some special handling. */
	if (*src == ':')
		if (*++src != ':')
			return (0);
	curtok = src;
	saw_xdigit = 0;
	val = 0;
	while ((ch = *src++) != '\0') {
		const char *pch;

		if ((pch = strchr((xdigits = xdigits_l), ch)) == NULL)
			pch = strchr((xdigits = xdigits_u), ch);
		if (pch != NULL) {
			val <<= 4;
			val |= (pch - xdigits);
			if (val > 0xffff)
				return (0);
			saw_xdigit = 1;
			continue;
		}
		if (ch == ':') {
			curtok = src;
			if (!saw_xdigit) {
				if (colonp)
					return (0);
				colonp = tp;
				continue;
			} else if (*src == '\0')
				return (0);
			if (tp + INT16SZ > endp)
				return (0);
			*tp++ = (u_char) (val >> 8) & 0xff;
			*tp++ = (u_char) val & 0xff;
			saw_xdigit = 0;
			val = 0;
			continue;
		}
		if (ch == '.' && ((tp + INADDRSZ) <= endp) &&
		    inet_pton4(curtok, tp, 1) > 0) {
			tp += INADDRSZ;
			saw_xdigit = 0;
			break;	/* '\0' was seen by inet_pton4(). */
		}
		return (0);
	}
	if (saw_xdigit) {
		if (tp + INT16SZ > endp)
			return (0);
		*tp++ = (u_char) (val >> 8) & 0xff;
		*tp++ = (u_char) val & 0xff;
	}
	if (colonp != NULL) {
		/*
		 * Since some memmove()'s erroneously fail to handle
		 * overlapping regions, we'll do the shift by hand.
		 */
		const int n = tp - colonp;
		int i;

		if (tp == endp)
			return (0);
		for (i = 1; i <= n; i++) {
			endp[- i] = colonp[n - i];
			colonp[n - i] = 0;
		}
		tp = endp;
	}
	if (tp != endp)
		return (0);
	memcpy(dst, tmp, IN6ADDRSZ);
	return (1);
}
#endif
/**
 * @borrowed from file src/inet_pton.c
 * @brief inet_pton for Windows
 * @author http://net-snmp.sourceforge.net
 #endif /* HAVE_INET_PTON /*
 */
 
 /**
 *  @borrowed from file src/inet_ntop.c
 *Copyright (C) 1996-2001  Internet Software Consortium.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 */
 
#define NS_INT16SZ   2
#define NS_IN6ADDRSZ  16

/*
 * WARNING: Don't even consider trying to compile this on a system where
 * sizeof(int) < 4.  sizeof(int) > 4 is fine; all the world's not a VAX.
 */

static const char *inet_ntop324(const unsigned char *src, char *dst,
            size_t size);

#ifdef AF_INET6
static const char *inet_ntop326(const unsigned char *src, char *dst,
            size_t size);
#endif

/* char *
 * isc_net_ntop(af, src, dst, size)
 *  convert a network format address to presentation format.
 * return:
 *  pointer to presentation format address (`dst'), or NULL (see errno).
 * author:
 *  Paul Vixie, 1996.
 */
const char *
inet_ntop32(int af, const void *src, char *dst, size_t size)
{
  switch (af) {
  case AF_INET:
    return (inet_ntop324(src, dst, size));
#ifdef AF_INET6
  case AF_INET6:
    return (inet_ntop326(src, dst, size));
#endif
  default:
	  //errno = EAFNOSUPPORT;
	  return (NULL);
  }
  /* NOTREACHED */
}

/* const char *
 * inet_ntop4(src, dst, size)
 *  format an IPv4 address
 * return:
 *  `dst' (as a const)
 * notes:
 *  (1) uses no statics
 *  (2) takes a unsigned char* not an in_addr as input
 * author:
 *  Paul Vixie, 1996.
 */
static const char *
inet_ntop324(const unsigned char *src, char *dst, size_t size)
{
  static const char *fmt = "%u.%u.%u.%u";
  char tmp[sizeof "255.255.255.255"];
  size_t len;

  len = snprintf(tmp, sizeof tmp, fmt, src[0], src[1], src[2], src[3]);
  if (len >= size) {
	  //errno = ENOSPC;
    return (NULL);
  }
  memcpy(dst, tmp, len + 1);

  return (dst);
}

/* const char *
 * isc_inet_ntop6(src, dst, size)
 *  convert IPv6 binary address into presentation (printable) format
 * author:
 *  Paul Vixie, 1996.
 */
#ifdef AF_INET6
static const char *
inet_ntop326(const unsigned char *src, char *dst, size_t size)
{
  /*
   * Note that int32_t and int16_t need only be "at least" large enough
   * to contain a value of the specified size.  On some systems, like
   * Crays, there is no such thing as an integer variable with 16 bits.
   * Keep this in mind if you think this function should have been coded
   * to use pointer overlays.  All the world's not a VAX.
   */
  char tmp[sizeof "ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255"], *tp;
  struct { int base, len; } best, cur;
  unsigned int words[NS_IN6ADDRSZ / NS_INT16SZ];
  int i, inc;

  /*
   * Preprocess:
   *  Copy the input (bytewise) array into a wordwise array.
   *  Find the longest run of 0x00's in src[] for :: shorthanding.
   */
  memset(words, '\0', sizeof words);
  for (i = 0; i < NS_IN6ADDRSZ; i++)
    words[i / 2] |= (src[i] << ((1 - (i % 2)) << 3));
  best.base = -1;
  cur.base = -1;
  for (i = 0; i < (NS_IN6ADDRSZ / NS_INT16SZ); i++) {
    if (words[i] == 0) {
      if (cur.base == -1)
        cur.base = i, cur.len = 1;
      else
        cur.len++;
    } else {
      if (cur.base != -1) {
        if (best.base == -1 || cur.len > best.len)
          best = cur;
        cur.base = -1;
      }
    }
  }
  if (cur.base != -1) {
    if (best.base == -1 || cur.len > best.len)
      best = cur;
  }
  if (best.base != -1 && best.len < 2)
    best.base = -1;

  /*
   * Format the result.
   */
  tp = tmp;
  for (i = 0; i < (NS_IN6ADDRSZ / NS_INT16SZ); i++) {
    /* Are we inside the best run of 0x00's? */
    if (best.base != -1 && i >= best.base &&
        i < (best.base + best.len)) {
      if (i == best.base)
        *tp++ = ':';
      continue;
    }
    /* Are we following an initial run of 0x00s or any real hex? */
    if (i != 0)
      *tp++ = ':';
    /* Is this address an encapsulated IPv4? */
    if (i == 6 && best.base == 0 &&
        (best.len == 6 || (best.len == 5 && words[5] == 0xffff))) {
      if (!inet_ntop324(src+12, tp, sizeof tmp - (tp - tmp)))
        return (NULL);
      tp += strlen(tp);
      break;
    }
    inc = snprintf(tp, 5, "%x", words[i]);
    tp += inc;
  }
  /* Was it a trailing run of 0x00's? */
  if (best.base != -1 && (best.base + best.len) ==
      (NS_IN6ADDRSZ / NS_INT16SZ))
    *tp++ = ':';
  *tp++ = '\0';

  /*
   * Check for overflow, copy, and we're done.
   */
  if ((size_t)(tp - tmp) > size) {
	  //errno = ENOSPC;
    return (NULL);
  }
  memcpy(dst, tmp, tp - tmp);
  return (dst);
}
#endif /* AF_INET6 */


/* end of src/inet_ntop.c */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */
