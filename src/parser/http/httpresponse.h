#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include "httpcommon.h"

namespace luna {

namespace http {

class HttpResponse
{
public:
    HttpResponse();
    void reset() { headers.clear(); }

    void set_version(HttpVersion version_) { version = version_; }
    void set_code(HttpCode code_) { code = code_; }
    void add_header(const HttpHeaderKey& key, const HttpHeaderValue& value)
    { headers[key] = value; }
    void set_body(const HttpBody& body_) { body = body_; }

    std::string to_string();
private:
    HttpVersion version;
    HttpCode code;
    HttpHeader headers;
    HttpBody body;
};

}

}

#endif // HTTPRESPONSE_H
