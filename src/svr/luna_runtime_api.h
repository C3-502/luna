#ifndef LUNA_RUNTIME_API_H
#define LUNA_RUNTIME_API_H

#include "../util/config.h"

int lunaWorkBefore(const luna::Config &config);
int lunaWorkFunc();
int lunaWorkAfter();

#endif // LUNA_RUNTIME_API_H
