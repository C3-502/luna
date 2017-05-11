#ifndef LUNASERVER_H
#define LUNASERVER_H
#include <string>

#include "util/const.h"
#include "util/config.h"

namespace luna {

class LunaServer
{
public:
    LunaServer();
    ~LunaServer();

    int init(const std::string& confPath);
    int run();
private:
    Config svrConf;
};

}



#endif // LUNASERVER_H
