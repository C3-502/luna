#ifndef TCPLISTENER_H
#define TCPLISTENER_H

#include <list>

#include <sys/socket.h>

#include "../ipv4_addr.h"
#include "../../util/common_inc.h"
#include "event_base.h"


namespace luna {

class TcpListener : public EventBase
{
public:
    TcpListener(const IPv4Addr& addr_, uint32_t backlog_,
                uint32_t maxAccpet_, TcpManagerPtr tcpManager_);
    int startListen();
    int handleEvent(EventType event);

    void addConnection(TcpConnectionPtr connection);
    void delConnection(TcpConnectionPtr connection);

    uint32_t activeConNumber() const { return connectionList.size(); }
private:
    IPv4Addr addr;
    uint32_t backlog;
    uint32_t maxAccpet;
    std::list<TcpConnectionPtr> connectionList;
private:
    TcpManagerPtr tcpManager;
};

}

#endif // TCPLISTENER_H
