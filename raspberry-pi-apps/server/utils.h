#ifndef UTILS_H
#define UTILS_H

#include <fcntl.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>

/*
*  Struct contains useful information
*  about socket
*/
struct socket_inf
{
    int fd;
    struct sockaddr_in addinfo;
};

/*
*  Struct contains useful information
*  about epoll object
*/
struct epoll_inf
{
    int id;
    struct epoll_event ev;
};

/*
*  Make socket non blocked
*
*  @param fd - socket file descriptor
*  @return - status code
*/
inline int set_nonblock(int fd)
{
    int flags;
#if defined(O_NONBLOCK)
    if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
        flags = 0;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
    flags = 1;
    return ioctl(fd, FIONBIO, &flags);
#endif
}

#endif // UTILS_H
