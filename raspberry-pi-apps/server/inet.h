#ifndef INET_H
#define INET_H

#include "utils.h"

/*
*  Creates socket and configurates it.
*
*  @param addr - ipv4 address
*  @param port - computer port for server
*  @return - pointer to socket_inf object,
*            defined in "utils.h" (needful operator delete)
*/
struct socket_inf* create_mcpsocket(const char* addr, short port);

/*
*  Creates epoll object and configurates it.
*
*  @param socket - socket object
*  @param event_mode - event`s mode number
*  @return - pointer to epoll_inf object,
*            defined in "utils.h" (needful operator delete)
*/
struct epoll_inf*  create_epollinf(struct socket_inf* socket, uint32_t event_mode);

/*
*
*  Registers epoll_inf object to handle events
*
*  @param socket - socket object
*  @param epollinf - epoll object bounded with this socket
*/
inline void register_epollinf(struct socket_inf* socket, struct epoll_inf* epollinf)
{
    epoll_ctl(epollinf->id, EPOLL_CTL_ADD, socket->fd, &epollinf->ev);
}

/*
*
*  Shutdowns socket file descriptor.
*
*  @param socket - socket object
*  @param how - close mode
*  @return - status code
*/
inline int shutdown_mcpsocket(struct socket_inf* socket, int how)
{
    shutdown(socket->fd, how);
    close(socket->fd);
}

#endif // INET_H
