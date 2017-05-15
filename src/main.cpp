#include <string>

#include "util/const.h"
#include "svr/luna_server.h"

static const std::string configPath = "../config/config.json";

bool getOptions(int argc, char *argv[])
{
    return true;
}

int main(int argc, char *argv[])
{
    if (!getOptions(argc, argv))
    {
        return LUNA_RUNTIME_ERROR;
    }

    if (configPath.empty())
    {
        return LUNA_RUNTIME_NO_CONF_PATH;
    }
    luna::LunaServerPtr server(new luna::LunaServer);
    int ret = server->init(configPath);
    if (ret != LUNA_RUNTIME_OK)
    {
        return ret;
    }
    return server->run();
}
