//
// Created by lxy on 2017/5/12.
//

#include <unistd.h>

#include "luna_worker.h"
#include "../util/const.h"
namespace luna
{

LunaWorkerProcess::LunaWorkerProcess(const char *name_)
    : name(name_)
{

}
int LunaWorkerProcess::startFork(const LunaWorkerProcess::WorkerFunc &workFunc)
{
    pid_t pid = fork();
    if (pid == -1)
    {

    }
    else if (pid == 0)
    {
        this->pid = pid;
        return LUNA_RUNTIME_OK;
    }
    else
    {
        workFunc();
    }
    return 0;
}

}