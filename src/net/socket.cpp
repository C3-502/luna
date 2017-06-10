#include "socket.h"
#include "../util/common_inc.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>

namespace luna {

namespace socket {

int tcp_socket()
{
    return socket(AF_INET, SOCK_STREAM, 0);
}

int bind(int fd, const IPv4Addr &addr)
{
    struct sockaddr_in sock_addr = addr.transformToSocketAddr();
    return ::bind(fd, (sockaddr*) &sock_addr, sizeof(sock_addr));
}

int listen(int fd, int backlog)
{
    return ::listen(fd, backlog);
}

int recv(int fd, char *buf, uint32_t count)
{
    return ::read(fd, buf, count);
}

int send(int fd, const char *msg, uint32_t count)
{
    return ::write(fd, msg, count);
}

int set_nonblock(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    int ret = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    if (ret < 0)
    {
        ERROR_LOG("fcntl");
        return LUNA_RUNTIME_ERROR;
    }
    return LUNA_RUNTIME_OK;
}

int set_reuse_addr(int fd)
{
    int optval = 1;
    return ::setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
                        &optval, static_cast<socklen_t>(sizeof optval));
}

}

}


