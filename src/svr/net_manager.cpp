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
    tcpManager.enableListener();

    while (true)
    {
        netPoller.poll(10);
    }
}

}
