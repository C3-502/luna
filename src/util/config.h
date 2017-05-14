#ifndef _LUNA_UTIL_CONFIG_H_
#define _LUNA_UTIL_CONFIG_H_

#include <string>

#include "../module/mylog/log_warpper.h"

namespace luna
{

struct SystemConfig
{
    int maxWorker;
    bool daemon;
    SystemConfig()
    {
        maxWorker = 2;
        daemon = true;
    }
};

struct LogConfig
{
    unsigned maxSize;
    LogCutType cutType;
    LogLevel level;
    std::string logDir;
    std::string logName;

    LogConfig()
    {
        maxSize = 512;
        cutType = LogCutType::LogCutByDay;
        level = LogLevel::LogDebug;
        logDir = "../config/";
        logName = "luna";
    }
};

class Config
{
public:
    Config()
    {}
    ~Config()
    {}
    int init(const std::string &path);
    bool isRunWithDaemon() const
    {
        return systemConfig.daemon;
    }
    int getMaxWorker()
    {
        return systemConfig.maxWorker;
    }

    const LogConfig &getLogConfig()
    {
        return logConfig;
    }

private:
    std::string configPath;
    SystemConfig systemConfig;
    LogConfig logConfig;
};

}

#endif
