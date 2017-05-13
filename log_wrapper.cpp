#include <memory>
#include <stdio.h>
#include <stdarg.h>

#include "log_warpper.h"
#include "log.h"

static std::shared_ptr<Log> log;

int initLog(const std::string& logDir, const std::string& logPrefix, LogCutType type, LogLevel minLevel, unsigned size)
{
    if (!log)
    {
        log = std::shared_ptr<Log>(new Log);
        int ret = log->init(logDir, logPrefix, type, size, minLevel);
        return ret;
    }
    return LOG_INIT_DUP;
}

int debug(const char* fmt, ...)
{
    char buf[1024] = { 0 };
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    return log->logMsg(buf, LogLevel::LogDebug);
}

int info(const char* fmt, ...)
{
    char buf[1024] = { 0 };
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    return log->logMsg(buf, LogLevel::LogInfo);
}

int warn(const char* fmt, ...)
{
    char buf[1024] = { 0 };
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    return log->logMsg(buf, LogLevel::LogWarn);
}

int error(const char* fmt, ...)
{
    char buf[1024] = { 0 };
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    return log->logMsg(buf, LogLevel::LogError);
}

int fatal(const char* fmt, ...)
{
    char buf[1024] = { 0 };
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    return log->logMsg(buf, LogLevel::LogFatal);
}
