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
*  Accepts new connections
*
*  @param server_sock - server socket object
*  @param server_epoll - server epoll object
*  @return - pointer to client server object
*/
struct socket_inf* mcp_accept(struct socket_inf* server_sock, struct epoll_inf* server_epoll);

/*
*
*  Sends data to client
*
*  @param client_sock - client socket object
*  @param buffer - data buffer
*  @param bufflen - buffer size
*  @return - how much bytes was sent, -1 on error
*/
inline int mcp_send(struct socket_inf* client_sock, void *buffer, int bufflen)
{
    return send(client_sock->fd, buffer, bufflen, MSG_NOSIGNAL);
}

/*
*
*  Receives data from client
*
*  @param client_sock - client socket object
*  @param buffer - data buffer
*  @param bufflen - buffer size
*  @return - how much bytes was received, -1 on error
*/
inline int mcp_receive(struct socket_inf* client_sock, void *buffer, int bufflen)
{
    return recv(client_sock->fd, buffer, bufflen, MSG_NOSIGNAL);
}

/*
*
*  Binds socket to address and port
*
*  @param socket - socket object
*  @return - zero on success, -1 on error
*/
inline int mcp_bind(struct socket_inf* socket)
{
    return bind(socket->fd, reinterpret_cast<struct sockaddr *>(&socket->addinfo),
                sizeof socket->addinfo);
}

/*
*
*  listens socket
*
*  @param socket - socket object
*  @return - zero on success, -1 on error
*/
inline void mcp_listen(struct socket_inf* socket, int count)
{
    listen(socket->fd, count);
}

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
