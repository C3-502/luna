#ifndef BUFFER_H
#define BUFFER_H

#include <string>

#include "common_inc.h"

namespace luna {

class Buffer
{
public:
    Buffer(uint32_t size = 1024);
    ~Buffer() { release(); }

    uint32_t capacity() const { return end_ - start_; }
    uint32_t size() const { return write_ - read_; }

    void append(const char* msg, size_t len);
    void append(const std::string& msg);
    const char* data() { return read_; }
    char* writeableMemory() { return write_; }
    void retrieve(uint32_t count);

    uint32_t remainSize() const { return end_ - write_ + read_ - start_; }
    uint32_t frontSize() const { return read_ - start_; }
    uint32_t backSize() const { return end_ - write_; }

    void addReadAreaLength(uint32_t count);

    void resize();
    void release();
    void moveForward();
private:
    char* start_;
    char* read_;
    char* write_;
    char* end_;
};

}
#endif // BUFFER_H
