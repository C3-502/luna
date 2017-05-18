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

    int addEvent(EventBase* eb, EventType events);
    int modEvent(EventBase* eb, EventType events);
    int delEvent(EventBase* eb, EventType events);

    int poll(int timeout);

private:

};

}


#endif // POLLER_H
