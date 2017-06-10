#ifndef TCPMANAGER_H
#define TCPMANAGER_H

#include <vector>

#include "../util/common_inc.h"
#include "../util/config.h"

namespace luna {

class TcpManager
{
public:
    TcpManager(NetManagerPtr netManager_);
    int init(const Config& config);
    int start();
    int enableListener();

    void addDieConnection(TcpConnectionPtr connection);
    void clearDieConnections();

    uint32_t activeConNumber() const;
    uint32_t dieConNumber() const { return dieConnections.size(); }
private:

private:
    std::vector<TcpListenerPtr> listenList;
    std::vector<TcpConnectionPtr> dieConnections;
private:
    NetManagerPtr netManager;
};


}



#endif // TCPMANAGER_H
