/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "apr_arch_networkio.h"
#include "apr_network_io.h"
#include "apr_strings.h"
#include "apr_support.h"
#include "apr_portable.h"
#include "apr_arch_inherit.h"

#if defined(BEOS) && !defined(BEOS_BONE)
#define close closesocket
#endif

static char generic_inaddr_any[16] = {0}; /* big enough for IPv4 or IPv6 */

static apr_status_t socket_cleanup(void *sock)
{
    apr_socket_t *thesocket = sock;

    if (close(thesocket->socketdes) == 0) {
        thesocket->socketdes = -1;
        return APR_SUCCESS;
    }
    else {
        return errno;
    }
}

static void set_socket_vars(apr_socket_t *sock, int family, int type, int protocol)
{
    sock->type = type;
    sock->protocol = protocol;
    apr_sockaddr_vars_set(sock->local_addr, family, 0);
    apr_sockaddr_vars_set(sock->remote_addr, family, 0);
    sock->netmask = 0;
#if defined(BEOS) && !defined(BEOS_BONE)
    /* BeOS pre-BONE has TCP_NODELAY on by default and it can't be
     * switched off!
     */
    sock->netmask |= APR_TCP_NODELAY;
#endif
}

static void alloc_socket(apr_socket_t **new, apr_pool_t *p)
{
    *new = (apr_socket_t *)apr_pcalloc(p, sizeof(apr_socket_t));
    (*new)->cntxt = p;
    (*new)->local_addr = (apr_sockaddr_t *)apr_pcalloc((*new)->cntxt,
                                                       sizeof(apr_sockaddr_t));
    (*new)->local_addr->pool = p;
    (*new)->remote_addr = (apr_sockaddr_t *)apr_pcalloc((*new)->cntxt,
                                                        sizeof(apr_sockaddr_t));
    (*new)->remote_addr->pool = p;
}

apr_status_t apr_socket_protocol_get(apr_socket_t *sock, int *protocol)
{
    *protocol = sock->protocol;
    return APR_SUCCESS;
}

apr_status_t apr_socket_create_ex(apr_socket_t **new, int ofamily, int type,
                                  int protocol, apr_pool_t *cont)
{
    int family = ofamily;

    if (family == APR_UNSPEC) {
#if APR_HAVE_IPV6
        family = APR_INET6;
#else
        family = APR_INET;
#endif
    }

    alloc_socket(new, cont);

    (*new)->socketdes = socket(family, type, protocol);

#if APR_HAVE_IPV6
    if ((*new)->socketdes < 0 && ofamily == APR_UNSPEC) {
        family = APR_INET;
        (*new)->socketdes = socket(family, type, protocol);
    }
#endif

    if ((*new)->socketdes < 0) {
        return errno;
    }
    set_socket_vars(*new, family, type, protocol);

    (*new)->timeout = -1;
    (*new)->inherit = 0;
    apr_pool_cleanup_register((*new)->cntxt, (void *)(*new), socket_cleanup,
                              socket_cleanup);
    return APR_SUCCESS;
} 

apr_status_t apr_socket_create(apr_socket_t **new, int family, int type,
                               apr_pool_t *cont)
{
    return apr_socket_create_ex(new, family, type, 0, cont);
}

apr_status_t apr_socket_shutdown(apr_socket_t *thesocket, 
                                 apr_shutdown_how_e how)
{
    return (shutdown(thesocket->socketdes, how) == -1) ? errno : APR_SUCCESS;
}

apr_status_t apr_socket_close(apr_socket_t *thesocket)
{
    return apr_pool_cleanup_run(thesocket->cntxt, thesocket, socket_cleanup);
}

apr_status_t apr_socket_bind(apr_socket_t *sock, apr_sockaddr_t *sa)
{
    if (bind(sock->socketdes, 
             (struct sockaddr *)&sa->sa, sa->salen) == -1) {
        return errno;
    }
    else {
        sock->local_addr = sa;
        /* XXX IPv6 - this assumes sin_port and sin6_port at same offset */
        if (sock->local_addr->sa.sin.sin_port == 0) { /* no need for ntohs() when comparing w/ 0 */
            sock->local_port_unknown = 1; /* kernel got us an ephemeral port */
        }
        return APR_SUCCESS;
    }
}

apr_status_t apr_socket_listen(apr_socket_t *sock, apr_int32_t backlog)
{
    if (listen(sock->socketdes, backlog) == -1)
        return errno;
    else
        return APR_SUCCESS;
}

apr_status_t apr_socket_accept(apr_socket_t **new, apr_socket_t *sock,
                               apr_pool_t *connection_context)
{
    alloc_socket(new, connection_context);
    set_socket_vars(*new, sock->local_addr->sa.sin.sin_family, SOCK_STREAM, sock->protocol);

#ifndef HAVE_POLL
    (*new)->connected = 1;
#endif
    (*new)->timeout = -1;
    
    (*new)->socketdes = accept(sock->socketdes, 
                               (struct sockaddr *)&(*new)->remote_addr->sa,
                               &(*new)->remote_addr->salen);

    if ((*new)->socketdes < 0) {
        return errno;
    }
#ifdef TPF
    if ((*new)->socketdes == 0) { 
        /* 0 is an invalid socket for TPF */
        return APR_EINTR;
    }
#endif

    *(*new)->local_addr = *sock->local_addr;

    /* The above assignment just overwrote the pool entry. Setting the local_addr 
       pool for the accepted socket back to what it should be.  Otherwise all 
       allocations for this socket will come from a server pool that is not
       freed until the process goes down.*/
    (*new)->local_addr->pool = connection_context;

    /* fix up any pointers which are no longer valid */
    if (sock->local_addr->sa.sin.sin_family == AF_INET) {
        (*new)->local_addr->ipaddr_ptr = &(*new)->local_addr->sa.sin.sin_addr;
    }
#if APR_HAVE_IPV6
    else if (sock->local_addr->sa.sin.sin_family == AF_INET6) {
        (*new)->local_addr->ipaddr_ptr = &(*new)->local_addr->sa.sin6.sin6_addr;
    }
#endif
    (*new)->remote_addr->port = ntohs((*new)->remote_addr->sa.sin.sin_port);
    if (sock->local_port_unknown) {
        /* not likely for a listening socket, but theoretically possible :) */
        (*new)->local_port_unknown = 1;
    }

#if APR_TCP_NODELAY_INHERITED
    if (apr_is_option_set(sock->netmask, APR_TCP_NODELAY) == 1) {
        apr_set_option(&(*new)->netmask, APR_TCP_NODELAY, 1);
    }
#endif /* TCP_NODELAY_INHERITED */
#if APR_O_NONBLOCK_INHERITED
    if (apr_is_option_set(sock->netmask, APR_SO_NONBLOCK) == 1) {
        apr_set_option(&(*new)->netmask, APR_SO_NONBLOCK, 1);
    }
#endif /* APR_O_NONBLOCK_INHERITED */

    if (sock->local_interface_unknown ||
        !memcmp(sock->local_addr->ipaddr_ptr,
                generic_inaddr_any,
                sock->local_addr->ipaddr_len)) {
        /* If the interface address inside the listening socket's local_addr wasn't 
         * up-to-date, we don't know local interface of the connected socket either.
         *
         * If the listening socket was not bound to a specific interface, we
         * don't know the local_addr of the connected socket.
         */
        (*new)->local_interface_unknown = 1;
    }

    (*new)->inherit = 0;
    apr_pool_cleanup_register((*new)->cntxt, (void *)(*new), socket_cleanup,
                              socket_cleanup);
    return APR_SUCCESS;
}

apr_status_t apr_socket_connect(apr_socket_t *sock, apr_sockaddr_t *sa)
{
    int rc;        

    do {
        rc = connect(sock->socketdes,
                     (const struct sockaddr *)&sa->sa.sin,
                     sa->salen);
    } while (rc == -1 && errno == EINTR);

    /* we can see EINPROGRESS the first time connect is called on a non-blocking
     * socket; if called again, we can see EALREADY
     */
    if (rc == -1 && (errno == EINPROGRESS || errno == EALREADY) &&
        apr_is_option_set(sock->netmask, APR_SO_TIMEOUT)) {
        rc = apr_wait_for_io_or_timeout(NULL, sock, 0);
        if (rc != APR_SUCCESS) {
            return rc;
        }

#ifdef SO_ERROR
        {
            int error;
            apr_socklen_t len = sizeof(error);
            if ((rc = getsockopt(sock->socketdes, SOL_SOCKET, SO_ERROR, 
                                 (char *)&error, &len)) < 0) {
                return errno;
            }
            if (error) {
                return error;
            }
        }
#endif /* SO_ERROR */
    }

    if (rc == -1 && errno != EISCONN) {
        return errno;
    }

    sock->remote_addr = sa;
    if (sock->local_addr->port == 0) {
        /* connect() got us an ephemeral port */
        sock->local_port_unknown = 1;
    }
    if (!memcmp(sock->local_addr->ipaddr_ptr,
                generic_inaddr_any,
                sock->local_addr->ipaddr_len)) {
        /* not bound to specific local interface; connect() had to assign
         * one for the socket
         */
        sock->local_interface_unknown = 1;
    }
#ifndef HAVE_POLL
    sock->connected=1;
#endif
    return APR_SUCCESS;
}

apr_status_t apr_socket_data_get(void **data, const char *key, apr_socket_t *sock)
{
    sock_userdata_t *cur = sock->userdata;

    *data = NULL;

    while (cur) {
        if (!strcmp(cur->key, key)) {
            *data = cur->data;
            break;
        }
        cur = cur->next;
    }

    return APR_SUCCESS;
}

apr_status_t apr_socket_data_set(apr_socket_t *sock, void *data, const char *key,
                                 apr_status_t (*cleanup) (void *))
{
    sock_userdata_t *new = apr_palloc(sock->cntxt, sizeof(sock_userdata_t));

    new->key = apr_pstrdup(sock->cntxt, key);
    new->data = data;
    new->next = sock->userdata;
    sock->userdata = new;

    if (cleanup) {
        apr_pool_cleanup_register(sock->cntxt, data, cleanup, cleanup);
    }

    return APR_SUCCESS;
}

apr_status_t apr_os_sock_get(apr_os_sock_t *thesock, apr_socket_t *sock)
{
    *thesock = sock->socketdes;
    return APR_SUCCESS;
}

apr_status_t apr_os_sock_make(apr_socket_t **apr_sock, 
                              apr_os_sock_info_t *os_sock_info, 
                              apr_pool_t *cont)
{
    alloc_socket(apr_sock, cont);
#ifdef APR_ENABLE_FOR_1_0 /* no protocol field yet */
    set_socket_vars(*apr_sock, os_sock_info->family, os_sock_info->type, os_sock_info->protocol);
#else
    set_socket_vars(*apr_sock, os_sock_info->family, os_sock_info->type, 0);
#endif
    (*apr_sock)->timeout = -1;
    (*apr_sock)->socketdes = *os_sock_info->os_sock;
    if (os_sock_info->local) {
        memcpy(&(*apr_sock)->local_addr->sa.sin, 
               os_sock_info->local, 
               (*apr_sock)->local_addr->salen);
        /* XXX IPv6 - this assumes sin_port and sin6_port at same offset */
        (*apr_sock)->local_addr->port = ntohs((*apr_sock)->local_addr->sa.sin.sin_port);
    }
    else {
        (*apr_sock)->local_port_unknown = (*apr_sock)->local_interface_unknown = 1;
    }
    if (os_sock_info->remote) {
#ifndef HAVE_POLL
        (*apr_sock)->connected = 1;
#endif
        memcpy(&(*apr_sock)->remote_addr->sa.sin, 
               os_sock_info->remote,
               (*apr_sock)->remote_addr->salen);
        /* XXX IPv6 - this assumes sin_port and sin6_port at same offset */
        (*apr_sock)->remote_addr->port = ntohs((*apr_sock)->remote_addr->sa.sin.sin_port);
    }
    else {
        (*apr_sock)->remote_addr_unknown = 1;
    }
        
    (*apr_sock)->inherit = 0;
    apr_pool_cleanup_register((*apr_sock)->cntxt, (void *)(*apr_sock), 
                              socket_cleanup, socket_cleanup);
    return APR_SUCCESS;
}

apr_status_t apr_os_sock_put(apr_socket_t **sock, apr_os_sock_t *thesock, 
                           apr_pool_t *cont)
{
    /* XXX Bogus assumption that *sock points at anything legit */
    if ((*sock) == NULL) {
        alloc_socket(sock, cont);
        /* XXX IPv6 figure out the family here! */
        /* XXX figure out the actual socket type here */
        /* *or* just decide that apr_os_sock_put() has to be told the family and type */
        set_socket_vars(*sock, APR_INET, SOCK_STREAM, 0);
        (*sock)->timeout = -1;
    }
    (*sock)->local_port_unknown = (*sock)->local_interface_unknown = 1;
    (*sock)->remote_addr_unknown = 1;
    (*sock)->socketdes = *thesock;
    return APR_SUCCESS;
}

APR_IMPLEMENT_INHERIT_SET(socket, inherit, cntxt, socket_cleanup)

APR_IMPLEMENT_INHERIT_UNSET(socket, inherit, cntxt, socket_cleanup)

/* deprecated */
apr_status_t apr_shutdown(apr_socket_t *thesocket, apr_shutdown_how_e how)
{
    return apr_socket_shutdown(thesocket, how);
}

/* deprecated */
apr_status_t apr_bind(apr_socket_t *sock, apr_sockaddr_t *sa)
{
    return apr_socket_bind(sock, sa);
}

/* deprecated */
apr_status_t apr_listen(apr_socket_t *sock, apr_int32_t backlog)
{
    return apr_socket_listen(sock, backlog);
}

/* deprecated */
apr_status_t apr_accept(apr_socket_t **new, apr_socket_t *sock,
                        apr_pool_t *connection_context)
{
    return apr_socket_accept(new, sock, connection_context);
}

/* deprecated */
apr_status_t apr_connect(apr_socket_t *sock, apr_sockaddr_t *sa)
{
    return apr_socket_connect(sock, sa);
}
