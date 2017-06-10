#include "buffer.h"
#include <string.h>
using namespace luna;

Buffer::Buffer(uint32_t size)
{
    start_ = new char[size+1];
    read_ = write_ = start_;
    end_ = start_ + size;
    *write_ = 0;
}

void Buffer::append(const char *msg, size_t len)
{
    uint32_t back = backSize();
    uint32_t remain = remainSize();
    if (len <= back)
    {

    }
    else if (len <= remain)
    {
        moveForward();
    }
    else
    {
        resize();
    }
    memcpy(write_, msg, len);
    write_ += len;
    *write_ = 0;
}

void Buffer::append(const std::string &msg)
{
    append(msg.c_str(), msg.size());
}

void Buffer::retrieve(uint32_t count)
{
    if (read_ + count < write_)
        read_ += count;
    else
        read_ = write_;
}

void Buffer::addReadAreaLength(uint32_t count)
{
    if (backSize() <= count)
        write_ = end_;
    else
        write_ += count;

    *write_ = 0;
}

void Buffer::resize()
{
    uint32_t size = capacity();
    char* oldSt = start_;
    start_ = new char[size * 2];
    end_ = start_ + size * 2;
    moveForward();
    delete[] oldSt;
}

void Buffer::release()
{
    if (start_ != nullptr)
    {
        delete[] start_;
    }
    start_ = end_ = read_ = write_ = nullptr;
}

void Buffer::moveForward()
{
    uint32_t used = size();
    memcpy(start_, read_, used);
    read_ = start_;
    write_ = read_ + used;
    *write_ = 0;
}
