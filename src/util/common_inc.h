#ifndef COMMON_INC_H
#define COMMON_INC_H

#include <stdint.h>
#include <string.h>

#include "../module/log/include/log_warpper.h"
#include "const.h"
#include "common_def.h"

#define ERROR_LOG(str) \
    int err = errno; \
    LOG_ERROR(str " failed, errno=%d, errstr=%s", err, strerror(err))

#endif // COMMON_INC_H
