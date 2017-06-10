#include "tcp_listener.h"
#include "tcp_connection.h"
#include "../tcp_manager.h"
#include "../socket.h"

#include <string.h>

namespace luna {

TcpListener::TcpListener(const IPv4Addr &addr_,
                         uint32_t backlog_,
                         uint32_t maxAccpet_,
                         TcpManagerPtr tcpManager_)
    : addr(addr_), backlog(backlog_), maxAccpet(maxAccpet_), tcpManager(tcpManager_)
{

}

int TcpListener::startListen()
{
    fd = socket::tcp_socket();
    if (fd < 0)
    {
        LOG_ERROR("socket create error");
        return LUNA_RUNTIME_ERROR;
    }

    int ret;
    ret = socket::set_nonblock(fd);
    if (ret < 0)
    {
        return LUNA_RUNTIME_ERROR;
    }

    ret = socket::bind(fd, addr);
    if (ret < 0)
    {
        LOG_ERROR("socket bind error");
        return LUNA_RUNTIME_ERROR;
    }

    ret = socket::set_reuse_addr(fd);
    if (ret < 0)
    {
        LOG_ERROR("socket set_reuse_addr failed");
        return LUNA_RUNTIME_ERROR;
    }

    ret = socket::listen(fd, 10);
    if (ret < 0)
    {
        LOG_ERROR("socket listen error");
        return LUNA_RUNTIME_ERROR;
    }
    LOG_DEBUG("tcp start listen, ip=%s, port=%u",
              addr.getIPStr().c_str(), addr.getPort());
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
                LOG_ERROR("accept socket get error: %d, %s", err, strerror(err));
                break;
            }
        }
        else
        {
            IPv4Addr addr(sock_addr);

            LOG_INFO("connection established, ip=%s, port=%d, fd=%d",
                     addr.getIPStr().c_str(), addr.getPort(), ret);
            ++count;
            int fd = ret;
            TcpConnectionPtr connection = new TcpConnection(this);
            connection->setFileDescriptor(fd);
            connection->enableRead();
            addConnection(connection);
        }

    }
}

void TcpListener::addConnection(TcpConnectionPtr connection)
{
    connectionList.push_back(connection);
}

void TcpListener::delConnection(TcpConnectionPtr connection)
{
    connectionList.remove(connection);
    tcpManager->addDieConnection(connection);
}

}

