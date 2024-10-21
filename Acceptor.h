#pragma once

// Acceptor of incoming TCP connections, running in baseLoop_

#include "noncopyable.h"
#include "Socket.h"
#include "Channel.h"

#include <functional>

class EventLoop;
class InetAddress;
class Acceptor : noncopyable
{
public:
    using newConnectionCallback = std::function<void(int connfd, const InetAddress& peerAddr)>;
    Acceptor(EventLoop* loop, const InetAddress& listenAddr, bool reusePort);
    ~Acceptor();
    void setNewConnectionCallback(const newConnectionCallback& cb) { newConnectionCallback_ = std::move(cb); }

    void listen();

    bool listenning() const { return listenning_; }


private:
    void handleRead();

    EventLoop* loop_;
    Socket acceptSocket_;
    Channel acceptChannel_;
    newConnectionCallback newConnectionCallback_;   // TcpServer设定的用户连接成功后执行的回调函数
    bool listenning_;

};