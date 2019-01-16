#ifndef MCP_H
#define MCP_H

#include "inet.h"

typedef void (*mcp_callback_t)(struct socket_inf* server_sock,
                               struct epoll_inf* epollinf,
                               struct epoll_event events[],
                               size_t events_size);

/*
*  Executes some actions with socket
*
*  @param socket - server socket object
*  @param epoll_obj - epoll object
*  @param max_conns - maximum connections count
*  @param handle_server_socket - pointer to handle server socket function
*  @param handle_slave_sockets - pointer to handle slave sockets function
*/
void main_loop(struct socket_inf* socket, struct epoll_inf* epoll_obj,
               size_t max_conns, mcp_callback_t handle_server_socket,
               mcp_callback_t handle_slave_sockets);

#endif // MCP_H
