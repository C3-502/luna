#include "tcp_manager.h"
#include "ipv4_addr.h"

namespace luna {

TcpManager::TcpManager()
{

}

int TcpManager::init(const Config &config)
{
    auto tcpListenerConfigs = config.getTcpListenerConfigs();
    size_t len = tcpListenerConfigs.size();
    listenList.resize(len);
    for (int i = 0; i < size; ++i)
    {
        const TcpListenerConfig& tcpListenerConfig = tcpListenerConfigs[i];
        IPv4Addr addr(tcpListenerConfig.ip.c_str(), tcpListenerConfig.port);
        TcpListener tcpListener(addr, tcpListenerConfig.backlog,
                                tcpListenerConfig.maxAccept);
        listenList.push_back(tcpListener);
    }
    return LUNA_RUNTIME_OK;
}

int TcpManager::start()
{
    int ret = LUNA_RUNTIME_OK;
    int len = listenList.size();
    for (int i = 0; i < len; ++i)
    {
        ret = listenList[i].startListen();
        if (ret != LUNA_RUNTIME_OK)
        {
            return ret;
        }
    }
    return ret;
}

}
