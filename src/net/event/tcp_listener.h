#ifndef TCPLISTENER_H
#define TCPLISTENER_H

#include <vector>

#include <sys/socket.h>

#include "../ipv4_addr.h"
#include "../../util/common_inc.h"
#include "tcp_connection.h"
#include "event_base.h"


namespace luna {

class TcpListener : public EventBase
{
public:
    TcpListener(const IPv4Addr& addr_, uint32_t backlog_, uint32_t maxAccpet_);
    int startListen();
private:
    IPv4Addr addr;
    uint32_t backlog;
    uint32_t maxAccpet;

    std::vector<TcpConnection> connectionList;
};

}

#endif // TCPLISTENER_H
