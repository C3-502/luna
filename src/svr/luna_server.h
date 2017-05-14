#ifndef LUNASERVER_H
#define LUNASERVER_H
#include <string>

#include "../util/const.h"
#include "../util/config.h"
#include "luna_master.h"
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

}


#endif // LUNASERVER_H
