#ifndef _LUNA_NET_POLLER_H_
#define _LUNA_NET_POLLER_H_

#include "event_base.h"

namespace luna {

class Poller
{
public:
    Poller() {}
    ~Poller() {}

    int init();

    enum class EventType
    {
        EVENT_IN  = 1 << 0,
        EVENT_PRT = 1 << 1,
        EVENT_OUT = 1 << 2,
        EVENT_ERR = 1 << 3,
        EVENT_HUP = 1 << 4,
    };

    int addEvent(EventBase* eb, EventType events);
    int modEvent(EventBase* eb, EventType events);
    int delEvent(EventBase* eb, EventType events);

    int poll(int timeout);

private:

};

}


#endif // POLLER_H
