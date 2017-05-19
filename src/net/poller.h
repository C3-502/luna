/*
based on epoll(linux kernal > 2.6)
*/
#ifndef _LUNA_NET_POLLER_H_
#define _LUNA_NET_POLLER_H_

#include <sys/epoll.h>

#include "event/event_base.h"

namespace luna {

class Poller
{
public:
    Poller();
    ~Poller() { release(); }

    int init(int eventSize);

    int addEvent(EventBase* eb, EventType events);
    int modEvent(EventBase* eb, EventType events);
    int delEvent(EventBase* eb, EventType events);

    int poll(int timeout);

private:
    void release();
    void getValidEpollEvent(EventBase* eb, EventType events, epoll_event* ev);
private:
    int epfd;
    int eventSize;
    epoll_event* eventList;
};

}


#endif // POLLER_H
