#ifndef _LUNA_UTIL_CONFIG_H_
#define _LUNA_UTIL_CONFIG_H_

#include <string>
#include <vector>
#include "common_inc.h"

namespace luna
{

struct TcpListenerConfig
{
    std::string ip;
    uint16_t port;
    uint32_t backlog;
    uint32_t maxAccept;
    TcpListenerConfig()
    {
        ip = "127.0.0.1";
        port = 8080;
        backlog = 10;
        maxAccept = 10;
    }
};

struct SystemConfig
{
    int maxWorker;
    bool daemon;
    SystemConfig()
    {
        maxWorker = 1;
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
        logDir = "../log/";
        logName = "luna";
    }
};

class Config
{
public:
    Config()
    {
        tcpListenerConfigs.push_back(TcpListenerConfig());
    }
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

    const std::vector<TcpListenerConfig>& getTcpListenerConfigs() const
    {
        return tcpListenerConfigs;
    }

private:
    std::string configPath;
    SystemConfig systemConfig;
    LogConfig logConfig;
    std::vector<TcpListenerConfig> tcpListenerConfigs;
};

}

#endif
