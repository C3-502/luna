//
// Created by lxy on 2017/5/12.
//

#include <sys/wait.h>
#include <unistd.h>

#include "luna_master.h"
#include "../module/log/include/log_warpper.h"

namespace luna
{

volatile static sig_atomic_t lunaQuit = 0;

static void testWorker()
{
    while (true) {
        LOG_DEBUG("%s", "worker run");
        sleep(1);
    }
}

static void signalHandler(int sig)
{
    switch (sig)
    {
    case SIGINT:
    case SIGTERM:
    case SIGQUIT:
        lunaQuit = 1;
        break;

    case SIGCHLD:
        break;
    default:
        break;
    }
}

struct SignalHandler
{
    int sig;
    const char* name;
    void (*handler)(int);
};

LunaMasterProcess::LunaMasterProcess(int workerSize_, const char *name_)
    : type(ProcessMaster), workers(workerSize_), workerSize(workerSize_), name(name_)
{

}
int LunaMasterProcess::run()
{
    if (workerSize < 0)
    {
        return LUNA_RUNTIME_ERROR;
    }

    spawnWorkers();
    masterLoop();
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
    //use sigterm first, if no effect, use sigkill.
    int lunaQuitCount = 0;
    while (true)
    {
        if (lunaQuit)
        {
            ++lunaQuitCount;
            if  (lunaQuitCount == 1) // first signal recv
            {
                LOG_INFO("%s", "master will send sigterm to woker");
            }
            else if (lunaQuitCount == 2)
            {
                LOG_INFO("%s", "master will send sigkill to woker");
            }
            else
            {
                LOG_INFO("%s", "master has sent signal to worker");
            }

        }
    }
}
void LunaMasterProcess::initSignals()
{
    SignalHandler sigHandlerArr[] =
    {
        {
            SIGPIPE, "SIGPIPE", SIG_IGN
        },

        {
            SIGINT, "SIGINT", signalHandler
        },

        {
            SIGTERM, "SIGTERM", signalHandler
        },

        {
            SIGQUIT, "SIGQUIT", signalHandler
        },

        {
            SIGHUP, "SIGHUP", signalHandler
        },

        {
            SIGCHLD, "SIGCHLD", signalHandler
        },
    };
}

}
