#include <string>
#include <memory>

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

    std::shared_ptr<luna::LunaServer> server(new luna::LunaServer);

    return LUNA_RUNTIME_OK;
}
