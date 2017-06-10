#include "httphandler.h"
#include "httpconnection.h"

#include <map>

namespace luna {

namespace http {


class HttpHandler
{
public:
    HttpConnection* get_http_connection(TcpConnectionPtr tcp_connection)
    {
        HttpConnection* http_connection = nullptr;
        auto it = connection_map.find(tcp_connection);
        if (it == connection_map.end())
        {
            http_connection = new HttpConnection(tcp_connection);
            connection_map.insert(std::make_pair(tcp_connection, http_connection));
        }
        else
        {
            http_connection = it->second;
        }
        return http_connection;
    }

private:
    std::map<TcpConnectionPtr, HttpConnection*> connection_map;
};

static HttpHandler http_handler;

int handle_message(TcpConnectionPtr connection)
{
    LOG_DEBUG("handle http begin");
    HttpConnection* http_connection = http_handler.get_http_connection(connection);
    return http_connection->handle_message();
}

}

}
