#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "log.h"

int Log::init(const std::string path, const std::string &prefix,
              LogCutType type, unsigned size, LogLevel minLevel)
{
    if (size < 0 || size > 1024)
    {
        size = 512;
    }

    struct stat buf;
    if (stat(path.c_str(), &buf) < 0)
    {
        return -1;
    }
    else
    {
        if (!S_ISDIR(buf.st_mode))
        {
            return -2;
        }
    }

    this->filePath = path;
    this->filePrefix = prefix;
    this->cutType = type;
    this->maxSize = size;
    this->minLevel = minLevel;
    return 0;
}

int Log::logMsg(const char *msg, LogLevel level)
{
    if (level < minLevel)
    {
        return 0;
    }

    int fd = getFileHandle();
    if (fd < 0)
    {
        return -3;
    }
    std::string levelName = getLevelName(level);
    time_t now = time(NULL);
    tm tmp;
    char buf[64] = { 0 };
    localtime_r(&now, &tmp);
    snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d %s ", tmp.tm_year+1990,
             tmp.tm_mon+1, tmp.tm_mday, tmp.tm_hour, tmp.tm_min, tmp.tm_sec, levelName.c_str());
    std::string msgBuf(buf);
    msgBuf.append(msg);
    msgBuf.append("\n");

    if (write(fd, msgBuf.c_str(), msgBuf.size()) < 0)
    {
        return -4;
    }

    return 0;
}

int Log::getFileHandle()
{
    auto datetime = getDatetimeStr();
    if (datetime == logInfo.datetimeStr)
    {
        struct stat buf;
        if (fstat(logInfo.fd, &buf) < 0)
        {
            logInfo.fd = -1;
        }
        else
        {
            if (buf.st_size / MB > this->maxSize)
            {
                close(logInfo.fd);
                logInfo.fd = -1;
                ++logInfo.seq;
            }
        }
    }
    else
    {
        logInfo.datetimeStr = datetime;
        if (logInfo.fd != -1)
            close(logInfo.fd);
        logInfo.fd = -1;
        logInfo.seq = 0;
    }

    if (logInfo.fd == -1)
    {
        std::string newName = getNewFileName();
        logInfo.fileName = newName;
        std::string newFilePath = filePath + newName;
        logInfo.fd = open(newFilePath.c_str(), O_WRONLY|O_APPEND|O_CREAT|O_LARGEFILE, 0666);
    }

    if (logInfo.fd < 0)
        return -1;
    return logInfo.fd;
}

std::string Log::getDatetimeStr()
{
    char buf[32] = { 0 };
    tm lwt;
    time_t now = time(NULL);
    switch (cutType)
    {
    case LogCutType::LogCutByDay:
        strftime(buf, sizeof(buf), "%Y-%m-%d", localtime_r(&now, &lwt));
        break;
    case LogCutType::LogCutByHour:
        strftime(buf, sizeof(buf), "%Y-%m-%d-%H", localtime_r(&now, &lwt));
        break;
    }
    return std::string(buf);
}

std::string Log::getNewFileName()
{
    char buf[128] = { 0 };
    snprintf(buf, sizeof(buf), "%s.%s.%d", filePrefix.c_str(),
             logInfo.datetimeStr.c_str(), logInfo.seq);
    return std::string(buf);
}

std::string Log::getLevelName(LogLevel level)
{
    static const char* levelNames[] = {
        "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
    };

    return std::string(levelNames[level]);
}

