#include <sys/epoll.h>
#include <sys/socket.h>

#include "event_base.h"
#include "../../svr/runtime_manager.h"

namespace luna {

int EventBase::enableRead()
{
    uint32_t readEvent = EVENT_IN | EVENT_PRI;
    return updateEvent(readEvent);
}

int EventBase::enableWrite()
{
    EventType writeEvent = EVENT_OUT;
    return updateEvent(writeEvent);
}

int EventBase::disableWrite()
{
    if (reg_events & EVENT_OUT)
    {
        uint32_t event = reg_events & (~EVENT_OUT);
        return updateEvent(event);
    }
    return LUNA_RUNTIME_OK;
}

int EventBase::updateEvent(EventType event)
{
    if (fd == -1)
    {
        LOG_ERROR("event_base fd is -1");
        return LUNA_RUNTIME_ERROR;
    }

    NetManagerPtr net = RuntimeManager::getInstance()->getNetManager();
    if (reg_events == 0)
    {
        net->addEvent(this, event);
        reg_events = event;
    }
    else
    {
        EventType tmp_event = reg_events | event;
        if (tmp_event != reg_events)
        {
            net->modEvent(this, tmp_event);
        }
        reg_events = tmp_event;
    }
    return LUNA_RUNTIME_OK;
}

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

void EventBase::close()
{
    if (fd != -1)
    {
        ::close(fd);
        fd = -1;
    }
}

void EventBase::closeRead()
{
    if (fd != -1)
    {
        ::shutdown(fd, SHUT_RD);
    }
}

void EventBase::closeWrite()
{
    if (fd != -1)
    {
        ::shutdown(fd, SHUT_WR);
    }
}

}
