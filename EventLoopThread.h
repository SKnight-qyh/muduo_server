#pragma once

#include "Thread.h"
#include "noncopyable.h"
#include "EventLoop.h"

#include <functional>
#include <string>
#include <memory>
#include <condition_variable>

class EventLoopThread : noncopyable
{
public:
    using ThreadInitCallBack = std::function<void(EventLoop*)>;
    EventLoopThread(const ThreadInitCallBack& cb = ThreadInitCallBack(), 
                    const std::string& name = std::string());
    ~EventLoopThread();
    EventLoop* startLoop();

private:
    void threadFunc();
    EventLoop* loop_;
    bool exiting_;  
    Thread thread_;
    std::mutex mutex_;
    std::condition_variable cond_;
    ThreadInitCallBack callback_;




};