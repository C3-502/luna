#ifndef TCPMANAGER_H
#define TCPMANAGER_H

#include <vector>

#include "./event/tcp_listener.h"
#include "../util/common_inc.h"
#include "../util/config.h"

namespace luna {

class TcpManager
{
public:
    TcpManager();
    int init(const Config& config);
    int start();
private:

private:
    std::vector<TcpListener> listenList;
};


}



#endif // TCPMANAGER_H
