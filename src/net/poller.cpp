#include <string.h>

#include "poller.h"

namespace luna {

Poller::Poller()
    : eventList(nullptr)
{

}

int Poller::init(int eventSize)
{
    int ret = epoll_create1(EPOLL_CLOEXEC);
    if (ret < 0)
    {
        int err = errno;
        LOG_ERROR("epoll_create1 failed, errno=%d, errstr=%s", err, strerror(err));
        return LUNA_RUNTIME_ERROR;
    }

    this->eventSize = eventSize;
    eventList = new epoll_event(eventSize);
    return LUNA_RUNTIME_OK;
}

int Poller::addEvent(EventBase *eb, EventType events)
{
    epoll_event ev;
    getValidEpollEvent(eb, events, &ev);
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, eb->getFileDescriptor(), &ev);
    if (ret < 0)
    {
        int err = errno;
        LOG_WARN("epoll_ctl failed, errno=%d, errstr=%s", err, strerror(err));
        return LUNA_RUNTIME_WARN;
    }
    return LUNA_RUNTIME_OK;
}

int Poller::modEvent(EventBase *eb, EventType events)
{

}

int Poller::delEvent(EventBase *eb, EventType events)
{

}

int Poller::poll(int timeout)
{
    LOG_DEBUG("epoll_wait begin, timeout=%d", timeout);
    int nevent = epoll_wait(epfd, eventList, eventSize, timeout);
    if (nevent < 0)
    {

    }
    else if (nevent == 0)
    {

    }
    else
    {
        for (int i = 0; i < nevent; ++i)
        {
            EventBase* eb = (EventBase*) eventList[i].data.ptr;
            uint32_t epollEvent = eventList[i].events;
            if ((eb != nullptr) && (eb->getFileDescriptor() != -1))
            {
                uint32_t event = EventBase::transformEpollEvent(epollEvent);
                eb->handleEvent(event);
            }
        }
    }

}

void Poller::release()
{
    if (epfd != -1)
    {
        close(epfd);
        epfd = -1;
    }
    delete[] eventList;
    eventList = nullptr;
}

void Poller::getValidEpollEvent(EventBase *eb, EventType events, epoll_event *ev)
{
    ev->data = eb;
    if (events & EventType::EVENT_IN)
        ev->events |= EPOLLIN;
    else if (events & EventType::EVENT_OUT)
        ev->events |= EPOLLOUT;
    else if (events & EventType::EVENT_PRI)
        ev->events |= EPOLLPRI;
}

}


