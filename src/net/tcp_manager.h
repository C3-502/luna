#ifndef TCPMANAGER_H
#define TCPMANAGER_H

#include <vector>

#include "../svr/net_manager.h"
#include "./event/tcp_listener.h"
#include "../util/common_inc.h"
#include "../util/config.h"

namespace luna {

class TcpManager
{
public:
    TcpManager(NetManager* netManager_);
    int init(const Config& config);
    int start();
    int enableListener();
private:

private:
    std::vector<TcpListener> listenList;

private:
    NetManager* netManager;
};


}



#endif // TCPMANAGER_H
