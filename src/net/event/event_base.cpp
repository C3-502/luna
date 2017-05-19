#include <sys/epoll.h>

#include "event_base.h"

namespace luna {

uint32_t EventBase::transformEpollEvent(uint32_t epollEvent)
{
    uint32_t event = 0;
    if (epollEvent & EPOLLIN)
        event |= EVENT_IN;
    else if (epollEvent & EPOLLOUT)
        event |= EVENT_OUT;
    else if (epollEvent & EPOLLPRI)
        event |= EVENT_PRI;
    else if (epollEvent & EPOLLERR)
        event |= EVENT_ERR;
    else if (epollEvent & EPOLLHUP)
        event |= EVENT_HUP;

    return event;
}

}
