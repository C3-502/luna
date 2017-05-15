#include "../include/log_warpper.h"

int main()
{
	initLog("./", "test");
	LOG_DEBUG("%s", "this is a test");
	return 0;
}
