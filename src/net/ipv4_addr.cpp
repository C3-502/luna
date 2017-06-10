#include <arpa/inet.h>

#include "ipv4_addr.h"


namespace luna {

IPv4Addr::IPv4Addr(const sockaddr_in &sock_addr)
    : ip(ntohl(sock_addr.sin_addr.s_addr)),
      port(ntohs(sock_addr.sin_port))
{
    transformIPv4BinaryToStr(sock_addr.sin_addr.s_addr);
}

IPv4Addr::IPv4Addr(uint32_t ip_, uint16_t port_)
    : ip(ip_), port(port_)
{
    transformIPv4BinaryToStr(htonl(ip_));
}

IPv4Addr::IPv4Addr(const char *ip, uint16_t port)
    : ip_str(ip)
{
    in_addr buf;
    int ret =  inet_pton(ipv4_domin, ip, &buf);
    if (ret < 0)
    {

    }
    this->ip = ntohl(buf.s_addr);
    this->port = port;
}

sockaddr_in IPv4Addr::transformToSocketAddr()
{
    sockaddr_in sock_addr;
    sock_addr.sin_family = ipv4_domin;
    sock_addr.sin_addr.s_addr = htonl(this->ip);
    sock_addr.sin_port = htons(this->port);
    return sock_addr;
}

void IPv4Addr::transformIPv4BinaryToStr(uint32_t ip_)
{
    in_addr temp;
    temp.s_addr = ip_;
    char buf[INET_ADDRSTRLEN] = { 0 };
    inet_ntop(ipv4_domin, &temp, buf, sizeof(buf));
    ip_str = buf;
}

}


