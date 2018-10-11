#include "mcp.h"

#define EVENTS 13

void main_loop(struct socket_inf* sock, struct epoll_inf* epll)
{
    while (1) {
        struct epoll_event events[EVENTS];
        int ev_count = epoll_wait(epll->id, events, EVENTS, -1);

        for (int i = 0; i < ev_count; ++i) {
            if (events[i].data.fd != sock->fd) {
                // TODO(Calvados) : call function handle slave sockets
            }
            else {
                handle_master(sock, epll);
            }
        }
    }
}
