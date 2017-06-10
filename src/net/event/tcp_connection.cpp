#include "tcp_connection.h"
#include "tcp_listener.h"
#include "../socket.h"

#include "../../parser/http/httphandler.h"

namespace luna {

TcpConnection::TcpConnection(TcpListenerPtr listener_)
    : listener(listener_), readClosed(false)
{

}

int TcpConnection::handleEvent(EventType event)
{
    LOG_DEBUG("tcp connection handle event begin");
    if (event & EVENT_IN)
    {
        handleRead();
    }
    else if (event & EVENT_OUT)
    {
        handleWrite();
    }
    else
    {

    }
    return LUNA_RUNTIME_OK;
}

void TcpConnection::send(const char *msg, uint32_t count)
{
    int nwrite = 0;
    if (outputBuffer.size() == 0)
    {
        nwrite = socket::send(fd, msg, count);
        if (nwrite < 0)
        {
            nwrite = 0;
            ERROR_LOG("socket::send");
        }
    }

    if (nwrite < count)
    {
        outputBuffer.append(msg+nwrite, count-nwrite);
        this->enableWrite();
    }
}

void TcpConnection::send(const std::string &msg)
{
    send(msg.c_str(), msg.size());
}

int TcpConnection::recv()
{
    Buffer* buf = &inputBuffer;
    uint32_t readSize = 0;
    int err;
    while (true)
    {
        char* mem = buf->writeableMemory();
        uint32_t bufSize = buf->backSize();

        if (bufSize == 0)
        {
            buf->resize();
            continue;
        }

        int curReadSize = socket::recv(fd, mem, bufSize);
        if (curReadSize < 0)
        {
            err = errno;
            if (err == EINTR)
                continue;
            if (err == EAGAIN || err == EWOULDBLOCK)
            {
                return LUNA_IO_COMPLETE;
            }
            else
            {
                LOG_ERROR("socket read error, errno=%d, errstr=%s", err, strerror(err));
                return LUNA_IO_ERROR;
            }
        }
        else if (curReadSize == 0)
        {
            LOG_ERROR("connection may be closed by client");
            return LUNA_IO_CLOSE;
        }
        else
        {
            readSize = curReadSize;
            buf->addReadAreaLength(readSize);
        }

        if (readSize == bufSize)
        {
            buf->moveForward();
        }
    }
}

int TcpConnection::handleRead()
{
    int ret = recv();
    if (ret == LUNA_IO_COMPLETE)
    {
        LOG_DEBUG("input buffer data:\n%s", inputBuffer.data());
        int ret = http::handle_message(this);
        if (ret == LUNA_CON_CLOSE)
        {
            LOG_DEBUG("handle message error, close connection");
        }
    }
    else if (ret == LUNA_IO_CLOSE)
    {
        if (outputBuffer.size() == 0)
        {
            close();
            listener->delConnection(this);
        }
        else
        {
            LOG_DEBUG("out buffer not empty, close read first");
            closeRead();
            readClosed = true;
        }
    }
    else
    {

    }

}

int TcpConnection::handleWrite()
{
    const char* msg = outputBuffer.data();
    uint32_t count = outputBuffer.size();
    int nwrite = socket::send(fd, msg, count);
    if (nwrite < 0)
    {
        nwrite = 0;
        ERROR_LOG("socket::send");
    }

    outputBuffer.retrieve(nwrite);
    if (outputBuffer.size() == 0)
    {
        disableWrite();
        if (readClosed)
        {
            LOG_DEBUG("read closed and out buffer is empty, close write");
            closeWrite();
            listener->delConnection(this);
        }
    }

}

}


