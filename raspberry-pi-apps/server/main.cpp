#include "inet.h"
#include "mcp.h"

int main(void)
{
    socket_inf *server_socket = create_mcpsocket("127.0.0.1", 5678);
    epoll_inf *server_epoll = create_epollinf(server_socket, EPOLLIN);

    if (-1 == mcp_bind(server_socket)) {
        delete server_socket;
        delete server_epoll;
        return -1;
    }
    mcp_listen(server_socket, SOMAXCONN);
    register_epollinf(server_socket, server_epoll);

    return 0;
}
