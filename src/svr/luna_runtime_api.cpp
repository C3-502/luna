#include "luna_runtime_api.h"
#include "runtime_manager.h"
#include "../util/common_inc.h"

using namespace luna;

int lunaWorkBefore(const Config &config)
{
    RuntimeManagerPtr runtimeManager = RuntimeManager::getInstance();
    int ret = runtimeManager->init(config);
    if (ret != LUNA_RUNTIME_OK)
    {
        LOG_ERROR("runtime init failed");
        return ret;
    }
    return LUNA_RUNTIME_OK;
}

int lunaWorkFunc()
{
    RuntimeManagerPtr runtimeManager = RuntimeManager::getInstance();
    NetManagerPtr net = runtimeManager->getNetManager();
    int ret = net->initPoll(1024);
    if (ret != LUNA_RUNTIME_OK)
    {

    }
    net->run();
}
