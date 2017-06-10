#ifndef RUNTIMEMANAGER_H
#define RUNTIMEMANAGER_H

#include "../util/noncopyable.h"
#include "../util/config.h"
#include "net_manager.h"
#include "../util/common_inc.h"

namespace luna {

class RuntimeManager
{
    NONCOPYABLE(RuntimeManager);
public:
    static RuntimeManagerPtr getInstance();
    int init(const Config& config);
    NetManagerPtr getNetManager() { return &net; }
private:
    RuntimeManager();
private:
    NetManager net;
};

}

#endif // RUNTIMEMANAGER_H
