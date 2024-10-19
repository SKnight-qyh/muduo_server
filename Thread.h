#pragma once

#include "noncopyable.h"

#include <functional>
#include <thread>
#include <memory>
#include <atomic>
#include <string>

class Thread : noncopyable 
{
public:
    using ThreadFunc = std::function<void()>;
    //  name 线程名，默认为空
    explicit Thread(ThreadFunc func, const std::string& name = std::string());
    ~Thread();
    void start();
    void join(); // 
private:
    void setDefaultName();
    bool started_;
    bool joined_; // 当前线程等待其他线程运行完了，当前线程继续运行
    // 直接 std::thread thread_; 会直接创建一个线程，并运行，需要智能指针封装
    std::shared_ptr<std::thread> thread_;
    pid_t tid_;
    ThreadFunc func_;
    std::string name_;
    // 对所有线程数量进行计数，所以是静态的
    static std::atomic_int numCreated_;
};