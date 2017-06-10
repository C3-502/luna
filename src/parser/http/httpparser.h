#ifndef HTTPPARSER_H
#define HTTPPARSER_H

#include "http_parser.h"
#include <string>

namespace luna {

namespace http {

class HttpConnection;

class HttpParser
{
public:
    HttpParser() {}
    void init(HttpConnection* connection);
    int parse(const char* buf, size_t count);
    static int on_message_begin(http_parser *parser);
    static int on_url(http_parser *parser, const char * at, size_t len);
    static int on_header_field(http_parser *parser, const char * at, size_t len);
    static int on_header_value(http_parser *parser, const char * at, size_t len);
    static int on_headers_complete(http_parser *parser);
    static int on_body(http_parser *parser, const char * at, size_t len);
    static int on_message_complete(http_parser *parser);

private:
    http_parser parser;
    http_parser_settings settings;

};

}

}



#endif // HTTPPARSER_H
