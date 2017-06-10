#include "httpparser.h"
#include "httprequest.h"
#include "httpcommon.h"
#include "httpconnection.h"

using namespace luna::http;

#define GET_CON_AND_REQUEST \
    HttpConnection* con = (HttpConnection*)(parser->data); \
    HttpRequest* request = con->get_http_request()

static HttpMethod get_http_method(http_method method)
{
    if (method > 4)
        return HttpMethod::NotSupport;
    return static_cast<HttpMethod>(method);
}

void HttpParser::init(HttpConnection *connection)
{
    http_parser_init(&parser, HTTP_REQUEST);
    parser.data = connection;

    settings.on_message_begin = HttpParser::on_message_begin;
    settings.on_url = HttpParser::on_url;
    settings.on_header_field = HttpParser::on_header_field;
    settings.on_header_value = HttpParser::on_header_value;
    settings.on_headers_complete = HttpParser::on_headers_complete;
    settings.on_body = HttpParser::on_body;
    settings.on_message_complete = HttpParser::on_message_complete;
}

int HttpParser::parse(const char *buf, size_t count)
{
    int nparsed = http_parser_execute(&parser, &settings, buf, count);
    if (parser.http_errno != HPE_OK)
    {
        return -1;
    }
    return nparsed;
}

int HttpParser::on_message_begin(http_parser *parser)
{
    LOG_DEBUG("");
    GET_CON_AND_REQUEST;
    con->set_status(HttpConnection::HttpParsing);
    return 0;
}

int HttpParser::on_url(http_parser *parser, const char *at, size_t len)
{
    LOG_DEBUG("");
    GET_CON_AND_REQUEST;
    request->set_path(std::string(at, len));
    return 0;
}

int HttpParser::on_header_field(http_parser *parser, const char *at, size_t len)
{
    LOG_DEBUG("");
    GET_CON_AND_REQUEST;
    request->set_key_buf(std::string(at, len));
    return 0;
}

int HttpParser::on_header_value(http_parser *parser, const char *at, size_t len)
{
    LOG_DEBUG("");
    GET_CON_AND_REQUEST;
    std::string key_buf = request->get_key_buf();
    request->add_header(key_buf, std::string(at, len));
    return 0;
}

int HttpParser::on_headers_complete(http_parser *parser)
{
    LOG_DEBUG("");
    GET_CON_AND_REQUEST;
    http_method method = (http_method)(parser->method);
    request->set_method(get_http_method(method));
    HttpVersion version;
    switch (parser->http_major)
    {
    case 1:
        switch (parser->http_minor) {
        case 0:
            version = HttpVersion::Http1_0;
            break;
        case 1:
            version = HttpVersion::Http1_1;
            break;
        default:
            version = HttpVersion::NotSupport;
            break;
        }
    case 2:
        version = HttpVersion::Http2_0;
        break;
    default:
        version = HttpVersion::NotSupport;
    }
    request->set_version(version);

    return 0;
}

int HttpParser::on_body(http_parser *parser, const char *at, size_t len)
{
    LOG_DEBUG("");
    return 0;
}

int HttpParser::on_message_complete(http_parser *parser)
{
    LOG_DEBUG("");
    GET_CON_AND_REQUEST;
    con->set_status(HttpConnection::HttpParseComplete);
    return 0;
}
