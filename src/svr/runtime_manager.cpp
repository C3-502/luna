#include "runtime_manager.h"

namespace luna {

static RuntimeManagerPtr handle;

RuntimeManagerPtr RuntimeManager::getInstance()
{
    if (!handle)
    {
        handle = RuntimeManagerPtr(new RuntimeManager);
    }
    return handle;
}

RuntimeManager::RuntimeManager()
{

}

}
