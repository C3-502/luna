#include "httpresponse.h"

#include "../../util/common_inc.h"

#include <cstdio>

using namespace luna::http;

static const char* clrf = "\r\n";

HttpResponse::HttpResponse()
{

}

// TODO
std::string HttpResponse::to_string()
{
    std::string buf;
    std::string http_version_str = get_http_version_str(version);
    int http_code = static_cast<int>(code);
    std::string http_code_str = get_http_code_str(code);

    char tmp[32] = { 0 };
    std::snprintf(tmp, sizeof(tmp), "%s %d %s\r\n",
                  http_version_str.c_str(),
                  http_code, http_code_str.c_str());
    buf += tmp;
    auto it = headers.begin();
    auto end = headers.end();
    while (it != end)
    {
        char tmp[128] = { 0 };
        std::snprintf(tmp, sizeof(tmp), "%s: %s\r\n",
                      it->first.c_str(), it->second.c_str());
        buf += tmp;
        ++it;
    }
    buf += clrf;
    if (!body.empty())
        buf += body;
    return buf;
}
