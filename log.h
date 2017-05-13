#ifndef LOG_H
#define LOG_H

#include <string>

#define MB (1024 * 1024)

#include "log_common_def.h"

struct LogFileInfo
{
    int fd;
    unsigned int seq;
    std::string datetimeStr;
    std::string fileName;
    LogFileInfo()
        :fd(-1), seq(0)
    {}
};

class Log
{
public:
    Log() {}
    ~Log() {}

    int init(const std::string path, const std::string &prefix, LogCutType type = LogCutType::LogCutByDay,
             unsigned size = 512, LogLevel minLevel=LogLevel::LogDebug);

    int logMsg(const char* msg, LogLevel level);

private:
    int getFileHandle();
    std::string getDatetimeStr();
    std::string getNewFileName();
    std::string getLevelName(LogLevel level);
private:
    std::string filePath;
    std::string filePrefix;
    LogCutType cutType;
    unsigned int maxSize;
    LogLevel minLevel;
    LogFileInfo logInfo;
};

#endif // LOG_H
