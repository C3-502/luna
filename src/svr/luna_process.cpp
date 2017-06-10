
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>

#include "luna_process.h"
#include "../util/common_inc.h"
#include "luna_runtime_api.h"
namespace luna
{

volatile static sig_atomic_t lunaQuit = 0;
volatile static sig_atomic_t lunaWorkerQuit = 0;
static int gProcessType = 0;

static void testWorker()
{
    sigset_t empty;
    sigemptyset(&empty);
    sigprocmask(SIG_SETMASK, &empty, NULL);
    lunaWorkFunc();
}

static void signalHandler(int sig)
{
    switch (gProcessType) {
    case ProcessMaster:
        switch (sig)
        {
        case SIGINT:
        case SIGTERM:
        case SIGQUIT:
            lunaQuit = 1;
            break;

        case SIGCHLD:
            lunaWorkerQuit = 1;
            break;
        default:
            break;
        }
        break;
    case ProcessWorker:
        LOG_DEBUG("worker recv signal %d", sig);
        exit(0);
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

    // block some signals temporarily
    sigset_t sigset, oldset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGTERM);
    sigaddset(&sigset, SIGQUIT);
    sigaddset(&sigset, SIGCHLD);
    sigprocmask(SIG_BLOCK, &sigset, &oldset);

    initSignals();

    int ret = spawnWorkers();
    if (ret != LUNA_RUNTIME_OK)
        return ret;

    masterLoop();

    sigprocmask(SIG_BLOCK, &oldset, NULL);
    return LUNA_RUNTIME_OK;
}
int LunaMasterProcess::spawnWorkers()
{
    for (int i = 0; i < workerSize; ++i)
    {
        LunaWorkerProcessPtr worker(new LunaWorkerProcess);
        workers[i] = worker;
        int ret = worker->startFork(testWorker);
        if (ret != LUNA_RUNTIME_OK)
        {
            return ret;
        }
    }

    return LUNA_RUNTIME_OK;
}

int LunaMasterProcess::restartWorkers()
{
    // 1.wait worker to exit
    auto len = workers.size();

    while (true)
    {
        int status;
        pid_t pid = waitpid(-1, &status, WNOHANG);
        if (pid < 0)
        {
            int err = errno;
            LOG_DEBUG("waitpid failed, errno %d, errstr %s", err, strerror(err));
            if (err == ECHILD)
            {
                break;
            }
        }
        else if (pid == 0)
        {
            break;
        }
        else
        {
            LOG_DEBUG("a worker exit, pid=%d", (int) pid);

            for (int i = 0; i < len; ++i)
            {
                LunaWorkerProcessPtr worker = workers[i];
                if (worker->getPid() == pid)
                    worker->setStatus(ProcessExited);
            }
        }
    }

    // 2.restart if lunaQuit is not set

    int liveWorkers = 0;

    for (int i = 0; i < len; ++i)
    {
        if (workers[i]->getStatus() == ProcessExited)
        {
            if (lunaQuit)
            {
                continue;
            }
            workers[i]->startFork(testWorker);
        }
        ++liveWorkers;
    }
    return liveWorkers;
}

void LunaMasterProcess::masterLoop()
{
    //use sigterm first, if no effect, use sigkill.
    int lunaQuitCount = 0;
    int liveWorkers = workers.size();
    sigset_t empty;
    sigemptyset(&empty);

    struct itimerval itv;

    itv.it_interval.tv_sec = 10;
    itv.it_interval.tv_usec = 0;

    itv.it_value.tv_sec = 10;
    itv.it_value.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &itv, NULL) < 0)
    {
        LOG_ERROR("set timer failed");
        return;
    }

    while (true)
    {
        sigsuspend(&empty);

        if (lunaWorkerQuit)
        {
            lunaWorkerQuit = 0;
            liveWorkers = restartWorkers();
        }
        LOG_DEBUG("%d worker live", liveWorkers);

        if (liveWorkers == 0 && lunaQuit)
        {
            LOG_INFO("master is going to exit");
            break;
        }

        if (lunaQuit)
        {
            ++lunaQuitCount;
            if  (lunaQuitCount == 1) // first signal recv
            {
                LOG_INFO("%s", "master will send sigterm to woker");
                sendSignalToWorkers(SIGTERM);
            }
            else if (lunaQuitCount == 2)
            {
                LOG_INFO("%s", "master will send sigkill to woker");
                sendSignalToWorkers(SIGKILL);
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
            SIGALRM, "SIGALRM", signalHandler
        },

        {
            SIGCHLD, "SIGCHLD", signalHandler
        },

        {
            0, "", nullptr
        }
    };

    for (int i=0; ; ++i)
    {
        if (sigHandlerArr[i].sig == 0)
            break;
        struct sigaction act;
        act.sa_handler = sigHandlerArr[i].handler;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        if (sigaction(sigHandlerArr[i].sig, &act, NULL) < 0)
        {
            LOG_WARN("sigaction failed, sig=%s", sigHandlerArr[i].name);
        }
    }
}

int LunaMasterProcess::sendSignalToWorkers(int sig)
{
    for (int i=0; i < workers.size(); ++i)
    {
        workers[i]->handleMasterSignal(sig);
    }
    return LUNA_RUNTIME_OK;
}


LunaWorkerProcess::LunaWorkerProcess(const char *name_)
    : name(name_), type(ProcessWorker), status(ProcessNew)
{

}
int LunaWorkerProcess::startFork(const LunaWorkerProcess::WorkerFunc &workFunc)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        LOG_ERROR("fork failed");
        return LUNA_RUNTIME_ERROR;
    }
    else if (pid == 0)
    {
        gProcessType = ProcessWorker;
        status = ProcessRunning;
        workFunc();
        exit(LUNA_RUNTIME_OK);
    }
    else
    {
        gProcessType = ProcessMaster;
        this->pid = pid;
        return LUNA_RUNTIME_OK;
    }
}

int LunaWorkerProcess::handleMasterSignal(int sig)
{
    if (status != ProcessExited)
    {
        int ret = kill(pid, sig);
        if (ret < 0)
        {
            LOG_ERROR("send signal %d to worker %d failed", sig, pid);
            return LUNA_RUNTIME_ERROR;
        }
        LOG_DEBUG("send signal %d to worker %d success", sig, pid);
    }
    return LUNA_RUNTIME_OK;
}

}
