#ifndef CONST_H
#define CONST_H

#define LUNA_RUNTIME_OK             0
#define LUNA_RUNTIME_ERROR          -200 //common error
#define LUNA_RUNTIME_WARN           -201 // warn not error, no need to terminate.
#define LUNA_RUNTIME_NO_IMPL        -202

#define LUNA_RUNTIME_NO_CONF_PATH   -201
#define LUNA_RUNTIME_CONF_INIT_ERROR -202

#define LUNA_RUNTIME_LOG_ERROR -300
#define LUNA_RUNTIME_LOG_NO_DIR -301
#define LUNA_RUNTIME_LOG_NOT_DIR -302

#define LUNA_IO_ERROR -400
#define LUNA_IO_CLOSE -401
#define LUNA_IO_COMPLETE -402

#define LUNA_CON_ERROR -500
#define LUNA_CON_CONTINUE -501
#define LUNA_CON_NEXT -502
#define LUNA_CON_CLOSE -503


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
