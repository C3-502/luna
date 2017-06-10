#ifndef HTTPCOMMON_H
#define HTTPCOMMON_H

#include <string>
#include <map>

namespace luna {

namespace http {

enum class HttpMethod
{
    Delete,
    Get,
    Head,
    Post,
    Put,
    NotSupport
};

enum class HttpVersion
{
    Http1_0, Http1_1, Http2_0, NotSupport
};

enum class HttpCode
{
    OK = 200,
    NotFound = 404,
    NotSupport = 600
};

using HttpHeaderKey = std::string;
using HttpHeaderValue = std::string;
using HttpHeader = std::map<HttpHeaderKey, HttpHeaderValue>;
using HttpBody = std::string;

std::string get_http_method_str(HttpMethod method);
std::string get_http_version_str(HttpVersion version);
std::string get_http_code_str(HttpCode code);

}

}

#endif // HTTPCOMMON_H
