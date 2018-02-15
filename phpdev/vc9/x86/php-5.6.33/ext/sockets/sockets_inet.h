#include <php_network.h>
#include "php_sockets.h" /* php_socket */

#ifndef PHP_WIN32
# include <netinet/in.h>
#else
# include <Winsock2.h>
#endif

#ifndef PHP_WIN32
# include <netdb.h>
#else
#include "win32/inet.h"
#endif

#if HAVE_ARPA_INET_H
# include <arpa/inet.h>
#endif

//const char  *inet_ntop32(int, const void *restrict, char *restrict, socklen_t);
//int			inet_pton32(int, const char *restrict, void *restrict);

const char *inet_ntop32(int af, const void *restrict src, char *restrict dst, socklen_t size);
int inet_pton32(int af, const char *restrict src, void *restrict dst);