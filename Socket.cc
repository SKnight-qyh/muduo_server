#include "Socket.h"
#include "logger.h"
#include "InetAddress.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <errno.h>
#include <strings.h>

Socket::~Socket()
{
    ::close(sockfd_);
}

void Socket::bindAddress(const InetAddress& addr)
{
    if(0 != ::bind(sockfd_, (sockaddr*)addr.getSockAddr(), sizeof(sockaddr_in)));
    {
        LOG_FATAL("bind sockfd errno:%d\n", errno);
    }
}
void Socket::listen()
{
    if(0 != ::listen(sockfd_, 1024))
    {
        LOG_FATAL("listen sockfd errno:%d\n", errno);
    }
}
int Socket::accept(InetAddress* peeraddr)
{
    sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    socklen_t addrlen = sizeof(addr);
    int connfd = ::accept(sockfd_, (sockaddr*)&addr, &addrlen);
    if(connfd >= 0)
    {
        peeraddr->setSockAddr(addr);
    }
    return connfd;
}
void Socket::shutdownWrite()
{
    if(0 != ::shutdown(sockfd_, SHUT_WR))
    {
        LOG_ERROR("shutdownWrite sockfd errno:%d\n", errno);
    }
}

void Socket::setTcpNoDelay(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval));

}

void Socket::setReuseAddr(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

}

void Socket::setReusePort(bool on)
{
    int optval  = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
}

void Socket::setKeepAlive(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval));
}

sockaddr_in Socket::getLocalAddr(int sockfd)
{
    sockaddr_in local;
    bzero(&local, sizeof local);
    socklen_t addrlen = sizeof local;
    if(::getsockname(sockfd, (sockaddr*)&local, &addrlen) < 0)
    {
        LOG_ERROR("socket::getLocalAddr\n");
    }
    return local;
}