#ifndef INET_H
#define INET_H

#include "utils.h"

/*
*  Creates socket and configurates it.
*
*  @param addr - ipv4 address
*  @param port - computer port for server
*  @return - pointer to socket_inf structure,
*            defined in "utils.h" (needful operator delete)
*/
struct socket_inf* create_mcpsocket(const char* addr, short port);

/*
*  Creates epoll object and configurates it.
*
*  @param socket - socket object
*  @param event_mode - event`s mode number
*  @return - pointer to epoll_inf structure,
*            defined in "utils.h" (needful operator delete)
*/
struct epoll_inf*  create_epollinf(struct socket_inf* socket, uint32_t event_mode);

#endif // INET_H
