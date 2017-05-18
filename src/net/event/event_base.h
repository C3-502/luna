#ifndef _LUNA_NET_EVENT_BASE_H_
#define _LUNA_NET_EVENT_BASE_H_

#include "../../util/common_inc.h"

namespace luna
{

enum class EventType
{
    EVENT_IN  = 1 << 0,
    EVENT_PRT = 1 << 1,
    EVENT_OUT = 1 << 2,
    EVENT_ERR = 1 << 3,
    EVENT_HUP = 1 << 4,
};

class EventBase
{
public:
    EventBase(int fd_ = -1)
        : fd(fd_) {}
    virtual ~EventBase() {}
    virtual int handleEvent(EventType event) { return LUNA_RUNTIME_NO_IMPL; }

    void setFileDescriptor(int fd_) { fd = fd_; }
    int getFileDescriptor() const { return fd; }
private:
	int fd;
};


}

#endif
