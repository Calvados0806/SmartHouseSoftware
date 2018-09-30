#ifndef MCP_H
#define MCP_H

#include "inet.h"

/*
*  Executes some actions with socket
*
*  @param socket - socket object
*  @param epoll_obj - epoll object
*/
void main_loop(struct socket_inf* socket, struct epoll_inf* epoll_obj);

#endif // MCP_H
