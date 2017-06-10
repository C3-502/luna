#ifndef SOCKET_H
#define SOCKET_H

#include <unistd.h>
#include <string>

#include "ipv4_addr.h"

namespace luna {

namespace socket {

int tcp_socket();
int bind(int fd, const IPv4Addr& addr);
int listen(int fd, int backlog);

int recv(int fd, char* buf, uint32_t count);
int send(int fd, const char* msg, uint32_t count);
int set_nonblock(int fd);
int set_reuse_addr(int fd);
}

}


#endif // SOCKET_H
