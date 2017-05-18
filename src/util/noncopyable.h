#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

#define NONCOPYABLE(cls) \
    cls(const cls&) = delete; \
    const cls&  operator=(const cls&) = delete

#endif // NONCOPYABLE_H
