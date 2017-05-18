#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <memory>

#include "../util/noncopyable.h"

namespace luna {

class NetManager
{
public:
    NetManager();
};

using NetManager = NetManager;
using NetManagerPtr = std::shared_ptr<NetManager>;
}


#endif // NETMANAGER_H
