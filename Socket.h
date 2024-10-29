#pragma once

#include "noncopyable.h"
#include <netinet/in.h>

class InetAddress;


class Socket : noncopyable
{
public:
    Socket(int sockfd) 
        : sockfd_(sockfd) 
    {
    }
    ~Socket();
    int fd() const { return sockfd_; }
    void bindAddress(const InetAddress& addr);
    void listen();
    int accept(InetAddress* peeraddr);
    void shutdownWrite();

    void setTcpNoDelay(bool on);

    void setReuseAddr(bool on);

    void setReusePort(bool on);

    void setKeepAlive(bool on);
    static sockaddr_in getLocalAddr(int sockfd);
private:
    const int sockfd_;
};