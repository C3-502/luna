#ifndef CONST_H
#define CONST_H

#define LUNA_RUNTIME_OK             0
#define LUNA_RUNTIME_ERROR          -200 //common error

#define LUNA_RUNTIME_NO_CONF_PATH   -201
#define LUNA_RUNTIME_CONF_INIT_ERROR -202

#define LUNA_RUNTIME_LOG_ERROR -300
#define LUNA_RUNTIME_LOG_NO_DIR -301
#define LUNA_RUNTIME_LOG_NOT_DIR -302

typedef enum ProcessType
{
    ProcessMaster,
    ProcessWorker,
} ProcessType;

typedef enum ProcessStatus
{
    ProcessNew,
    ProcessRunning,
    ProcessExited
} ProcessStatus;

#endif // CONST_H
