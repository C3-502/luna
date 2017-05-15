#ifndef LOG_COMMON_DEF_H
#define LOG_COMMON_DEF_H

enum LogCutType
{
    LogCutByHour,
    LogCutByDay
};

enum LogLevel
{
    LogDebug,
    LogInfo,
    LogWarn,
    LogError,
    LogFatal
};

#define LOG_INIT_DUP 1
#define LOG_OK 0
#define LOG_PATH_NOT_EXIST -1
#define LOG_PATH_NOT_DIR   -2
#define LOG_GET_HANDLE_ERROR -3
#define LOG_WRITE_ERROR -4

#define NONE "\033[m"
#define RED "\033[0;32;31m"

#define LIGHT_RED "\033[1;31m"
#define GREEN "\033[0;32;32m"
#define LIGHT_GREEN "\033[1;32m"
#define BLUE "\033[0;32;34m"
#define LIGHT_BLUE "\033[1;34m"
#define DARY_GRAY "\033[1;30m"
#define CYAN "\033[0;36m"
#define LIGHT_CYAN "\033[1;36m"
#define PURPLE "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN "\033[0;33m"
#define YELLOW "\033[1;33m"
#define LIGHT_GRAY "\033[0;37m"
#define WHITE "\033[1;37m"
#define COLOR_END "\033[0m"


#endif // LOG_COMMON_DEF_H
