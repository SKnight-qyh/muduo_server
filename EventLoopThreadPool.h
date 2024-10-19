#pragma once

#include "noncopyable.h"
#include "EventLoopThread.h"

#include <functional>
#include <string>
#include <vector>
#include <memory>

class EventLoop;
class EventLoopThreadPool : noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>; 
    EventLoopThreadPool(EventLoop* baseLoop, const std::string& name);
    ~EventLoopThreadPool();
    void setThreadNum(int numThreads) { numThreads_ = numThreads; }
    // 开启整个事件循环
    void start(const ThreadInitCallback& cb = ThreadInitCallback());

    // 如果是工作在多线程中，baseLoop_ 默认以轮询的方式分配channel给subLOOP
    EventLoop* getNextLoop();

    std::vector<EventLoop*> getAllLoops();

    bool started() const { return started_; }
    const std::string& name() const { return name_; }

private:
    EventLoop* baseLoop_;   // 用户创建的Loop，最开始的Loop
    std::string name_;
    bool started_;
    int numThreads_;
    int next_;  // 轮询的下标

    std::vector<std::unique_ptr<EventLoopThread>> threads_;
    std::vector<EventLoop*> loops_;
};