#include "httpconnection.h"
#include "httprequest.h"
#include "httpresponse.h"
#include "httpparser.h"

#include "../../net/event/tcp_connection.h"

#include <cstdio>

using namespace luna::http;

static std::string test = "<!DOCTYPE><html><body><h1>it works!</h1></body></html>";
static void test_func(HttpRequest* request, HttpResponse* response)
{
    auto len = test.size();
    char buf[16] = { 0 };
    std::snprintf(buf, sizeof(buf), "%d", len);
    response.set_code(HttpCode::NotFound);
    response.set_version(HttpVersion::Http1_1);
    response.set_body(test);
    response.add_header("Server", "luna");
    response.add_header("Content-Length", buf);
    response.add_header("Content-Type", "text/html; charset=utf-8");
}

HttpConnection::HttpConnection(TcpConnectionPtr tcp_connection_)
    : tcp_connection(tcp_connection_)
{
    http_parser.init(this);
    request.reset();
    response.reset();
}

int HttpConnection::handle_message()
{
    Buffer* buffer = tcp_connection->get_input_buffer();
    const char* msg = buffer->data();
    uint32_t len = buffer->size();
    int nparsed = http_parser.parse(msg, len);
    if (nparsed == -1)
    {
        return LUNA_CON_CLOSE;
    }

    buffer->retrieve(nparsed);
    if (status == HttpParseComplete)
    {
        test_func(&request, &response);
        std::string response_str = response.to_string();
        LOG_DEBUG("http response:\n %s", response_str.c_str());
        tcp_connection->send(response_str);
        return LUNA_CON_NEXT;
    }
    return LUNA_CON_CONTINUE;
}
