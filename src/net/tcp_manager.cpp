#include "tcp_manager.h"
#include "ipv4_addr.h"
#include "../svr/net_manager.h"
#include "./event/tcp_listener.h"
namespace luna {

TcpManager::TcpManager(NetManagerPtr netManager_)
    : netManager(netManager_)
{

}

int TcpManager::init(const Config &config)
{
    auto tcpListenerConfigs = config.getTcpListenerConfigs();
    size_t len = tcpListenerConfigs.size();
    listenList.resize(len);
    for (size_t i = 0; i < len; ++i)
    {
        const TcpListenerConfig& tcpListenerConfig = tcpListenerConfigs[i];
        IPv4Addr addr(tcpListenerConfig.ip.c_str(), tcpListenerConfig.port);
        TcpListenerPtr tcpListener = new TcpListener(addr, tcpListenerConfig.backlog,
                                tcpListenerConfig.maxAccept, this);
        LOG_DEBUG("init tcp listener, ip=%s, port=%d",
                  addr.getIPStr().c_str(), addr.getPort());
        listenList[i] = tcpListener;
    }

    int ret = start();
    if (ret != LUNA_RUNTIME_OK)
    {
        return ret;
    }
    return LUNA_RUNTIME_OK;
}

int TcpManager::start()
{
    int ret = LUNA_RUNTIME_OK;
    int len = listenList.size();
    for (int i = 0; i < len; ++i)
    {
        ret = listenList[i]->startListen();
        if (ret != LUNA_RUNTIME_OK)
        {
            return ret;
        }
    }
    return ret;
}

int TcpManager::enableListener()
{
    size_t len = listenList.size();
    int ret = 0;
    for (size_t i = 0; i < len; ++i)
    {
        TcpListenerPtr listener = listenList[i];
        ret = listener->enableRead();
        if (ret != LUNA_RUNTIME_OK)
        {
            return ret;
        }
    }
    return LUNA_RUNTIME_OK;
}

void TcpManager::addDieConnection(TcpConnectionPtr connection)
{
    this->dieConnections.push_back(connection);
}

void TcpManager::clearDieConnections()
{
    size_t len = dieConnections.size();

    if (len == 0)
        return;

    int i = len;
    while (i > 0)
    {
        TcpConnectionPtr con = dieConnections[i-1];
        dieConnections.pop_back();
        if (con != nullptr)
            delete con;
        --i;
    }
}

uint32_t TcpManager::activeConNumber() const
{
    uint32_t count = 0;
    size_t len = listenList.size();
    for (size_t i = 0; i < len; ++i)
    {
        TcpListenerPtr listener = listenList[i];
        count += listener->activeConNumber();
    }
    return count;
}

}
