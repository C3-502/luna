#ifndef _LUNA_UTIL_CONFIG_H_
#define _LUNA_UTIL_CONFIG_H_

#include <string>

namespace luna
{

struct SystemConfig
{
	int maxWorker;
};

class Config
{
public:
	config();
	~config();
	int init(const std::string& path);

private:
	std::string configPath;
	SystemConfig systemConfig;
};

}

#endif
