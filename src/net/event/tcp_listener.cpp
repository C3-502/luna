#include "tcp_listener.h"
#include <string.h>
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

int TcpListener::handleEvent(EventType event)
{
    int count = 0;
    struct sockaddr_in sock_addr;
    memset(&sock_addr, 0, sizeof(sock_addr));
    socklen_t len = 0;
    while (true)
    {
        int ret = accept4(fd, (sockaddr*)(&sock_addr), &len,
                          SOCK_NONBLOCK | SOCK_CLOEXEC);
        if (ret < 0)
        {
            int err = errno;
            if (err == EAGAIN || err == EWOULDBLOCK)
            {
                LOG_DEBUG("accept socket eagin");
                break;
            }
            else if (err == EINTR)
            {
                continue;
            }
            else
            {
                LOG_ERR("accept socket get error: %d, %s", err, strerror(err));
                break;
            }
        }
        else
        {
            ++count;
        }

    }
}

}

