#ifndef LUNASERVER_H
#define LUNASERVER_H
#include <string>
#include <memory>

#include "../util/const.h"
#include "../util/config.h"
#include "luna_process.h"

namespace luna
{

class LunaServer
{
public:
    LunaServer()
    {}
    ~LunaServer()
    {}

    int init(const std::string &confPath);
    int run();

private:
    int runWithDaemon();
    int initLog();
private:
    Config svrConf;
    LunaMasterProcessPtr master;
};

using LunaServer = LunaServer;
using LunaServerPtr = std::shared_ptr<LunaServer>;

}


#endif // LUNASERVER_H
