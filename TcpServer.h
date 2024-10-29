#pragma once

#include "noncopyable.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include "EventLoopThreadPool.h"
#include "Callbacks.h"

#include <functional>
#include <string>
#include <memory>
#include <atomic>
#include <unordered_map>

//对外的服务器编程使用的类
class TcpServer : noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;
    // key = connName, vale = TcpConnectionPtr
    using ConnectionMap = std::unordered_map<std::string, TcpConnectionPtr>;
    enum Option
    {
        kNoReusePort,
        kReusePort,
    };
    
    
    TcpServer(EventLoop* EventLoop
            , const InetAddress& listenAddr
            , const std::string& nameArg
            , Option option = kNoReusePort);
    ~TcpServer();
    void setThreadInitCallback(const ThreadInitCallback& cb)
        { threadInitCallback_  = std::move(cb); }  
    
    // 设置subloop的个数
    void setThreadNum(int numThreads);

    // 开启服务器监听, 之后就是loop.loop()开启事件循环
    void start();

    void setConnectionCallback(const ConnectionCallback& cb)
    { connectionCallback_ = std::move(cb); }

    void setMessageCallback(const MessageCallback& cb)
    { messageCallback_ = std::move(cb); }

    void setWriteCompleteCallback(const WriteCompleteCallback& cb)
    { writeCompleteCallback_ = std::move(cb); }


private:
    // not thread safe, but in loop
    void newConnection(int connfd, const InetAddress& peerAddr);
    // thread safe
    void removeConnection(const TcpConnectionPtr& conn);
    // not thread safe, but in loop
    void removeConnectionInLoop(const TcpConnectionPtr& conn);
    
    EventLoop* loop_; // 用户定义的loop
    const std::string ipPort_;
    const std::string name_;
    std::unique_ptr<Acceptor> acceptor_;
    // 需要将threadPool_ 共享给多个线程，所以用shared_ptr
    std::shared_ptr<EventLoopThreadPool> threadPool_;
    ThreadInitCallback threadInitCallback_; // 线程初始化回调函数
    ConnectionCallback connectionCallback_; //有新连接时的回调
    MessageCallback messageCallback_;   // 有读写消息时的回调
    WriteCompleteCallback writeCompleteCallback_; // 消息写完后的回调
    std::atomic_int started_;
    int nextConnId_;
    ConnectionMap connectionMap_; // 保存所有的连接
};
