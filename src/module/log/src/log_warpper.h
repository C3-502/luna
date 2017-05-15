#ifndef LOG_WARPPER_H
#define LOG_WARPPER_H
#include <unistd.h>
#include <string>

#include "log_common_def.h"

#define LOG_DEBUG(format, ...) \
    debug(GREEN"%d %s:%d:%s " format COLOR_END, getpid(), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

#define LOG_INFO(format, ...) \
    info(YELLOW"%d %s:%d:%s " format COLOR_END, getpid(), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

#define LOG_WARN(format, ...) \
    warn(LIGHT_RED"%d %s:%d:%s " format COLOR_END, getpid(), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

#define LOG_ERROR(format, ...) \
    error(RED"%d %s:%d:%s " format COLOR_END, getpid(), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

#define LOG_FATAL(format, ...) \
    fatal(PURPLE"%d %s:%d:%s " format COLOR_END, getpid(), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)


int initLog(const std::string &logDir, const std::string &logPrefix,
            LogCutType type = LogCutByDay, LogLevel minLevel = LogDebug, unsigned size = 512);
int debug(const char* fmt, ...);
int info(const char* fmt, ...);
int warn(const char* fmt, ...);
int error(const char* fmt, ...);
int fatal(const char* fmt, ...);


#endif // LOG_WARPPER_H
