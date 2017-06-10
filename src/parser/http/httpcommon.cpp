#include "httpcommon.h"

namespace luna {

namespace http {

static const char* http_method[] = {
    "delete", "get", "head", "post", "put", "not_support"
};

static const char* http_version[] = {
  "HTTP/1.0", "HTTP/1.1", "HTTP/2.0", "not_support"
};

struct HttpCodeMap
{
    HttpCode code;
    std::string code_str;
};

static HttpCodeMap http_code[] = {
    { HttpCode::OK, "OK" },
    { HttpCode::NotFound, "Not Found" },
    { HttpCode::NotSupport, ""}
};

std::string get_http_method_str(HttpMethod method)
{
    int index = static_cast<int>(method);
    return http_method[index];
}

std::string get_http_version_str(HttpVersion version)
{
    int index = static_cast<int>(version);
    return http_version[index];
}

std::string get_http_code_str(HttpCode code)
{
    for (int i = 0; http_code[i].code != HttpCode::NotSupport; ++i)
    {
        if (code == http_code[i].code)
            return http_code[i].code_str;
    }
    return "";
}

}

}



