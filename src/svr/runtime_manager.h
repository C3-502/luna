#ifndef RUNTIMEMANAGER_H
#define RUNTIMEMANAGER_H

#include "../util/noncopyable.h"
#include "../util/config.h"
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
    int init(const Config& config);
    NetManager* getNetManager() { return &net; }
private:
    RuntimeManager();
private:
    NetManager net;
};

}

#endif // RUNTIMEMANAGER_H
