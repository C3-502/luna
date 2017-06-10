#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include "httpcommon.h"

#include <string>

namespace luna {

namespace http {

class HttpRequest
{
public:
    HttpRequest();

    void reset() { headers.clear(); }

    HttpMethod get_method() const { return method; }
    void set_method(HttpMethod method_) { method = method_; }
    const std::string & get_path() const { return path; }
    void set_path(const std::string path_) { path = path_; }
    HttpVersion get_version() const { return version; }
    void set_version(HttpVersion version_) { version = version_; }
    const HttpHeaderValue& get_header_value(const HttpHeaderKey& key)
    {
        return headers.at(key);
    }

    void add_header(const HttpHeaderKey& key, const HttpHeaderValue& value)
    {
        headers[key] = value;
    }

    void set_key_buf(const HttpHeaderKey& key) { key_buf = key; }
    const HttpHeaderKey& get_key_buf() { return key_buf; }
private:
    HttpMethod method;
    std::string path;
    HttpVersion version;
    HttpHeader headers;

private:
    HttpHeaderKey key_buf;
};

}

}

#endif // HTTPREQUEST_H
