#ifndef RUNTIMEMANAGER_H
#define RUNTIMEMANAGER_H

#include "../util/noncopyable.h"
#include "net_manager.h"

namespace luna {

class RuntimeManager;
using RuntimeManager = RuntimeManager;
using RuntimeManagerPtr = std::shared_ptr<RuntimeManager>;

class RuntimeManager
{
    NONCOPYABLE(RuntimeManager);
public:
    static RuntimeManagerPtr getInstance();
    int init();
private:
    RuntimeManager();
private:
    NetManagerPtr net;
};

}

#endif // RUNTIMEMANAGER_H
