//
// Created by lxy on 2017/5/12.
//

#include <sys/wait.h>

#include "luna_master.h"

namespace luna
{
static void testWorker()
{

}

volatile sig_atomic_t LunaMasterProcess::sigKill = 0;

volatile sig_atomic_t LunaMasterProcess::sigTerm = 0;

volatile sig_atomic_t LunaMasterProcess::sigChild = 0;

LunaMasterProcess::LunaMasterProcess(int workerSize_, const char *name_)
    : workers(workerSize_), workerSize(workerSize_), name(name_)
{

}
int LunaMasterProcess::run()
{
    if (workerSize < 0)
    {
        return LUNA_RUNTIME_ERROR;
    }

    int ret = spawnWorkers();
    if (ret != LUNA_RUNTIME_OK)
    {

    }


    return LUNA_RUNTIME_OK;
}
int LunaMasterProcess::spawnWorkers()
{
    for (int i = 0; i < workerSize; ++i)
    {
        LunaWorkerProcessPtr worker(new LunaWorkerProcess);
        workers[i] = worker;
        worker->startFork(testWorker);
    }

    return LUNA_RUNTIME_OK;
}
void LunaMasterProcess::masterLoop()
{
    while (!sigKill && !sigTerm)
    {
        int status;
        int ret = wait(&status);
        if (ret != -1)
        {

        }
        else
        {

        }
    }
}
void LunaMasterProcess::initSignals()
{

}
}