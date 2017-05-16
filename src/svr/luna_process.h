#ifndef LUNA_PROCESS_H
#define LUNA_PROCESS_H

#include <signal.h>

#include <vector>
#include <string>
#include <memory>
#include <functional>

#include "../util/const.h"


namespace luna
{
class LunaMasterProcess;
class LunaWorkerProcess;
using LunaMasterProcess = LunaMasterProcess;
using LunaMasterProcessPtr = std::shared_ptr<LunaMasterProcess>;
using LunaWorkerProcess = LunaWorkerProcess;
using LunaWorkerProcessPtr = std::shared_ptr<LunaWorkerProcess>;

class LunaMasterProcess
{
public:
    LunaMasterProcess(int workerSize_, const char *name_ = "luna_master");
    ~LunaMasterProcess() {}

    int run();
private:
    int spawnWorkers();
    int restartWorkers();
    void masterLoop();
    void initSignals();
    int sendSignalToWorkers(int sig);
private:
    ProcessType type;
    std::vector<LunaWorkerProcessPtr> workers;
    std::string name;
    int workerSize;

};

class LunaWorkerProcess
{
public:
    LunaWorkerProcess(const char *name_ = "luna_worker");
    ~LunaWorkerProcess() {}
    typedef std::function<void()> WorkerFunc;
    int startFork(const WorkerFunc& workFunc);
    int handleMasterSignal(int sig);

    void setStatus(ProcessStatus status) { this->status = status; }
    ProcessStatus getStatus() const { return status; }
    const pid_t getPid() const { return pid; }

private:
    ProcessType type;
    ProcessStatus status;
    std::string name;
    pid_t pid;
};

}






#endif // LUNA_PROCESS_H
