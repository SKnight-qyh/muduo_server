#pragma once

#include <netinet/in.h>
#include <string>
//封装socket地址类型
class InetAddress
{
public:
    //参数的默认值不管是声明还是定义只能出现一次
    explicit InetAddress(uint16_t port = 0, std::string ip = "127.0.0.1");
    explicit InetAddress(const sockaddr_in &addr)
        : addr_(addr)
    { }
    std::string toIp() const;
    std::string toIpPort() const;
    uint16_t toPort() const;
    void setSockAddr(const sockaddr_in& addr) { addr_ = addr; }
    const sockaddr_in* getSockAddr() const { return &addr_; }
private:
    sockaddr_in addr_;

};