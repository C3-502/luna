
#include "config.h"
#include "const.h"

namespace luna
{

int Config::init(const std::string &path)
{
    this->configPath = path;
    //暂时未实现配置文件解析，并且不知要配置哪些内容，以后在做
    return LUNA_RUNTIME_OK;
}

}
