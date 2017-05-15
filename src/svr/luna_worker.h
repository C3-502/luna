//
// Created by lxy on 2017/5/12.
//

#ifndef LUNA_LUNA_WORKER_H
#define LUNA_LUNA_WORKER_H

#include <memory>
#include <string>
#include <functional>

#include "util/const.h"

namespace luna
{
class LunaWorkerProcess
{
public:
    LunaWorkerProcess(const char *name_ = "luna_worker");
    ~LunaWorkerProcess() {}
    typedef std::function<void()> WorkerFunc;
    int startFork(const WorkerFunc& workFunc);
private:
    ProcessType type;
    std::string name;
    pid_t pid;
};

using LunaWorkerProcessPtr = std::shared_ptr<LunaWorkerProcess>;
}

#endif //LUNA_LUNA_WORKER_H
