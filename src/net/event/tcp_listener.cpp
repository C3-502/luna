#include "tcp_listener.h"

namespace luna {

TcpListener::TcpListener(const IPv4Addr &addr_, uint32_t backlog_, uint32_t maxAccpet_)
    : addr(addr_), backlog(backlog_), maxAccpet(maxAccpet_)
{

}

int TcpListener::startListen()
{
    LOG_DEBUG("tcp start listen, ip=%s, port=%u",
              addr.getIPStr().c_str(), addr.getPort());
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {

    }

    struct sockaddr sock_addr = addr.transformToSocketAddr();
    int ret = bind(fd, &sock_addr, sizeof(sock_addr));
    if (ret < 0)
    {

    }

    ret = listen(fd, 10);
    if (ret < 0)
    {

    }
    return LUNA_RUNTIME_OK;
}

}

