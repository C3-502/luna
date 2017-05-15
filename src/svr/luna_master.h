//
// Created by lxy on 2017/5/12.
//

#ifndef LUNA_LUNA_MASTER_H
#define LUNA_LUNA_MASTER_H

#include <signal.h>

#include <vector>
#include <string>
#include <memory>

#include "../util/const.h"
#include "luna_worker.h"

namespace luna
{

class LunaMasterProcess
{
public:
    LunaMasterProcess(int workerSize_, const char *name_ = "luna_master");
    ~LunaMasterProcess() {}

    int run();
private:
    int spawnWorkers();
    void masterLoop();
    void initSignals();
private:
    ProcessType type;
    std::vector<LunaWorkerProcessPtr> workers;
    std::string name;
    int workerSize;

};

using LunaMasterProcess = LunaMasterProcess;
using LunaMasterProcessPtr = std::shared_ptr<LunaMasterProcess>;
}
#endif //LUNA_LUNA_MASTER_H
