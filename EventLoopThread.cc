#include "EventLoopThread.h"

EventLoopThread::EventLoopThread(const ThreadInitCallBack& cb, 
                                 const std::string& name)
    : loop_(nullptr)
    , exiting_(false)
    , thread_(std::bind(&EventLoopThread::threadFunc, this), name)
    , mutex_()
    , cond_()
    , callback_(cb)
{
}

EventLoopThread::~EventLoopThread()
{
    exiting_ = true;
    if(!loop_)
    {
        loop_->quit();
        thread_.join();
    }


    
}

EventLoop* EventLoopThread::startLoop()
{
    thread_.start(); //启动底层的新线程，并在新线程中运行threadFunc()函数

    EventLoop *loop = nullptr;
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while(!loop_)
        {
            // 在等待期间互斥锁被自动释放，从而允许其他线程在等待期间安全地访问共享资源
            cond_.wait(lock);
        }
        loop = loop_;
    }
    return loop;

}

// threadFunc()函数在单独的新线程中运行
void EventLoopThread::threadFunc()
{
    // 创建一个新的EventLoop,与上面新创建的thread相对应
    // one loop per thread
    EventLoop loop;
    if(callback_)
    {
        callback_(&loop);
    }
    // 多个线程对loop_的访问是互斥的，所以需要加锁+条件变量
    {
        std::unique_lock<std::mutex> lock(mutex_);
        loop_ = &loop;
        cond_.notify_one();
    }

    loop.loop(); //进入EventLoop的事件循环
    std::unique_lock<std::mutex> lock(mutex_);
    loop_ = nullptr;
}