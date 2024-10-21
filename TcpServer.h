#pragma once

#include "noncopyable.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include "EventLoopThreadPool.h"

#include <functional>
#include <string>
#include <memory>

//对外的服务器编程使用的类
class TcpServer : noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;

    TcpServer();
    ~TcpServer();



private:
    EventLoop* loop_; // 用户定义的loop
    const std::string ipPort_;
    const std::string name_;
    std::unique_ptr<Acceptor> acceptor_;
    // 需要将threadPool_ 共享给多个线程，所以用shared_ptr
    std::shared_ptr<EventLoopThreadPool> threadPool_;
    ThreadInitCallback threadInitCallback_; // 线程初始化回调函数

};
