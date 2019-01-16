#include "mcp.h"

void main_loop(struct socket_inf* socket, struct epoll_inf* epoll_obj,
               size_t max_conns, mcp_callback_t handle_server_socket,
               mcp_callback_t handle_slave_sockets)
{
    while (1) {
        struct epoll_event events[max_conns];
        int count = epoll_wait(epoll_obj->id, events, max_conns, -1);

        for (int i = 0; i < count; i++) {
            if (events[i].data.fd == socket->fd) {
                handle_server_socket(socket, epoll_obj, events, count);
            }
            else {
                handle_slave_sockets(socket, epoll_obj, events, count);
            }
        }
    }
}
