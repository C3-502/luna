#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <memory>

#include "../util/noncopyable.h"
#include "../util/config.h"
#include "../net/tcp_manager.h"
#include "../net/poller.h"

namespace luna {

class NetManager
{
    NONCOPYABLE(NetManager);
public:
    NetManager();
    int init(const Config& config);
    int initPoll(int eventSize);
    int addEvent(EventBase* eb, uint32_t event);
    int modEvent(EventBase* eb, uint32_t event);
    int delEvent(EventBase* eb, uint32_t event);

    int run();
private:
    TcpManager tcpManager;
    Poller netPoller;
};

using NetManager = NetManager;
}


#endif // NETMANAGER_H
