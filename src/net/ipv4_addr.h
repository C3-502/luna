#ifndef IPV4ADDR_H
#define IPV4ADDR_H

#include <netinet/in.h>
#include <string>

namespace luna {

class IPv4Addr
{
public:
    IPv4Addr(const sockaddr_in& sock_addr);
    IPv4Addr(uint32_t ip_, uint16_t port_);
    IPv4Addr(const char* ip, uint16_t port);

    const std::string& getIPStr() const { return ip_str; }
    uint16_t getPort() { return port; }

    sockaddr_in transformToSocketAddr();
private:
    void transformIPv4BinaryToStr(uint32_t ip_);
private:
    in_addr_t ip;
    in_port_t port;
    std::string ip_str;
    const static int ipv4_domin = AF_INET;
};

}

#endif // IPV4ADDR_H
