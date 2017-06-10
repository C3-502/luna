#include "runtime_manager.h"

namespace luna {

static RuntimeManagerPtr handle;

RuntimeManagerPtr RuntimeManager::getInstance()
{
    if (!handle)
    {
        handle = new RuntimeManager;
    }
    return handle;
}

int RuntimeManager::init(const Config &config)
{
    int ret = net.init(config);
    if (ret != LUNA_RUNTIME_OK)
    {
        return LUNA_RUNTIME_ERROR;
    }
    return LUNA_RUNTIME_OK;
}

RuntimeManager::RuntimeManager()
{

}

}
