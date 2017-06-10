#ifndef _LUNA_NET_EVENT_BASE_H_
#define _LUNA_NET_EVENT_BASE_H_

#include "../../util/common_inc.h"

namespace luna
{

enum EventItem
{
    EVENT_IN  = 1 << 0,
    EVENT_PRI = 1 << 1,
    EVENT_OUT = 1 << 2,
    EVENT_ERR = 1 << 3,
    EVENT_HUP = 1 << 4,
};

using EventType = uint32_t;

class EventBase
{
public:
    EventBase()
        : fd(-1), reg_events(0) {}
    virtual ~EventBase() {}
    virtual int handleEvent(EventType event) { return LUNA_RUNTIME_NO_IMPL; }

    void setFileDescriptor(int fd_) { fd = fd_; }
    int getFileDescriptor() const { return fd; }

    int enableRead();
    int enableWrite();
    int disableWrite();

    static uint32_t transformEpollEvent(uint32_t epollEvent);

    void close();
    void closeRead();
    void closeWrite();
protected:
    int updateEvent(EventType event);
protected:
	int fd;
    EventType reg_events;
};


}

#endif
