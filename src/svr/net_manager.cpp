#include "net_manager.h"

namespace luna {

NetManager::NetManager()
    : tcpManager(this)
{

}

int NetManager::init(const Config &config)
{
    int ret = tcpManager.init(config);
    if (ret != LUNA_RUNTIME_OK)
    {
        return ret;
    }
    return LUNA_RUNTIME_OK;
}

int NetManager::initPoll(int eventSize)
{
    int ret = netPoller.init(eventSize);
    if (ret != LUNA_RUNTIME_OK)
    {
        return LUNA_RUNTIME_ERROR;
    }
    return LUNA_RUNTIME_OK;
}

int NetManager::addEvent(EventBase *eb, uint32_t event)
{
    return netPoller.addEvent(eb, event);
}

int NetManager::modEvent(EventBase *eb, uint32_t event)
{
    return netPoller.modEvent(eb, event);
}

int NetManager::delEvent(EventBase *eb, uint32_t event)
{
    return netPoller.delEvent(eb, event);
}

int NetManager::run()
{
    // worker main loop
    int ret = tcpManager.enableListener();
    if (ret != LUNA_RUNTIME_OK)
    {

    }

    while (true)
    {
        LOG_DEBUG("active connection number: %d, die connection number: %d",
                  tcpManager.activeConNumber(), tcpManager.dieConNumber());
        tcpManager.clearDieConnections();
        netPoller.poll(-1);
    }
}

}
