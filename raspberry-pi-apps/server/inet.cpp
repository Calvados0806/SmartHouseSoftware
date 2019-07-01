#include "inet.h"
#include <arpa/inet.h>

struct socket_inf* create_mcpsocket(const char* addr, short port)
{
    struct socket_inf* sinf = new struct socket_inf;

    if (-1 == (sinf->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))) {
        delete sinf;
        return NULL;
    }
    sinf->addinfo.sin_family = AF_INET;
    sinf->addinfo.sin_port = htons(port);
    sinf->addinfo.sin_addr.s_addr = inet_addr(addr);

    set_nonblock(sinf->fd);

    return sinf;
}


struct epoll_inf*  create_epollinf(struct socket_inf* socket, uint32_t event_mode)
{
    struct epoll_inf* einf = new struct epoll_inf;

    if (-1 == (einf->id = epoll_create1(0))) {
        delete einf;
        return NULL;
    }
    einf->epoll_event.data.fd = socket->fd;
    einf->epoll_event.events = event_mode;

    return einf;
}

struct socket_inf* mcp_accept(struct socket_inf* server_sock, struct epoll_inf* server_epoll)
{
    struct socket_inf* ret = new struct socket_inf;
    socklen_t size;

    ret->fd = accept(masterfd, (struct sockaddr*)(&ret->addinfo), &size);
    if (-1 == ret->fd) {
        delete ret;
        return NULL;
    }
    set_nonblock(ret->fd);

    struct epoll_event new_event;
    new_event.data.fd = ret->fd;
    new_event.events = EPOLLIN | EPOLLOUT;

    epoll_ctl(server_epoll->id, EPOLL_CTL_ADD, ret->fd, &new_event);
}
