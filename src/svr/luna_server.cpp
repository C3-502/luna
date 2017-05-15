#include "luna_server.h"
#include "../module/log/include/log_warpper.h"
namespace luna
{

int LunaServer::init(const std::string &confPath)
{
    int ret;
    ret = svrConf.init(confPath);
    if (ret != LUNA_RUNTIME_OK)
    {
        return LUNA_RUNTIME_CONF_INIT_ERROR;
    }

    ret = initLog();
    return ret;
}
int LunaServer::run()
{
    int ret;
    if (svrConf.isRunWithDaemon())
    {
        ret = this->runWithDaemon();
        if (ret != LUNA_RUNTIME_OK)
        {
            return ret;
        }
    }
    int maxWorker = svrConf.getMaxWorker();
    master = LunaMasterProcessPtr(new LunaMasterProcess(maxWorker));
    master->run();
}
int LunaServer::runWithDaemon()
{
    return LUNA_RUNTIME_OK;
}
int LunaServer::initLog()
{
    const LogConfig &logConfig = svrConf.getLogConfig();
    int ret = ::initLog(logConfig.logDir, logConfig.logName, logConfig.cutType,
            logConfig.level, logConfig.maxSize);
    switch (ret)
    {
        case LOG_PATH_NOT_EXIST:
            return LUNA_RUNTIME_LOG_NO_DIR;
        case LOG_PATH_NOT_DIR:
            return LUNA_RUNTIME_LOG_NOT_DIR;
        default:
            break;
    }

    LOG_INFO("%s", "log init success");
    return LUNA_RUNTIME_OK;
}

}
