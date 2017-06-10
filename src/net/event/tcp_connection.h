#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include "event_base.h"
#include "../../util/buffer.h"

namespace luna {

class TcpConnection : public EventBase
{
public:
    TcpConnection(TcpListenerPtr listener_);
    int handleEvent(EventType event);

    void send(const char* msg, uint32_t count);
    void send(const std::string& msg);
    int recv();

    Buffer* get_input_buffer() { return &inputBuffer; }

private:
    int handleRead();
    int handleWrite();

private:

private:
    TcpListenerPtr listener;
    Buffer inputBuffer;
    Buffer outputBuffer;
    bool readClosed;
};

}

#endif // TCPCONNECTION_H
