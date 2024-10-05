
#include "InetAddress.h"

#include <strings.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
Inetaddress::Inetaddress(uint16_t port, std::string ip)
{
    bzero(&addr_, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    //将小端字节转换为大端字节
    addr_.sin_addr.s_addr = inet_addr(ip.c_str());

}

std::string Inetaddress::toIp() const
{

    char buf[64] = {0};
    inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof buf);
    return buf;

}
std::string Inetaddress::toIpPort() const
{
    // ip:port
    char buf[64] = {0};
    inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof buf);
    size_t end = strlen(buf);
    uint16_t port = ntohs(addr_.sin_port);
    sprintf(buf + end, ":%u", port);
    return buf;
}
uint16_t Inetaddress::toPort() const
{

    return ntohs(addr_.sin_port);
}

int main(){
    Inetaddress addr(8080);
    std::cout << addr.toIp() << std::endl;
    std::cout << addr.toIpPort() << std::endl;
    std::cout << addr.toPort() << std::endl;
    return 0;
}
