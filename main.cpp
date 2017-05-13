#include <iostream>

#include "log_warpper.h"

using namespace std;

int main(int argc, char *argv[])
{
    initLog("./", "open_api", LogCutByDay, LogDebug, 1);
    LOG_ERROR("%s", "this is a error message");
    return 0;
}
