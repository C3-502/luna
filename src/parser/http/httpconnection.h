#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include "../../util/common_inc.h"
#include "httpresponse.h"
#include "httpparser.h"
#include "httprequest.h"

namespace luna {

namespace http {

class HttpRequest;
class HttpResponse;
class HttpParser;

class HttpConnection
{
public:
    HttpConnection(TcpConnectionPtr tcp_connection_);

    enum Status
    {
        HttpParseBegin, HttpParsing, HttpParseComplete
    };

    int handle_message();
    void set_status(Status status_) { status = status_; }
    HttpRequest* get_http_request() { return &request; }
    HttpResponse* get_http_response() { return &response; }
private:
    TcpConnectionPtr tcp_connection;
    HttpParser http_parser;
    HttpRequest request;
    HttpResponse response;
    Status status;
};

}

}

#endif // HTTPCONNECTION_H
