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