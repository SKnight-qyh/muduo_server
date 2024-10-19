#include "EventLoopThreadPool.h"
#include "EventLoopThread.h"

#include <memory>

EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop, const std::string& name)
    : baseLoop_(baseLoop)   // 用户传递的baseLoop
    , name_(name)
    , started_(false)
    , numThreads_(0)
    , next_(0) 
{
}

EventLoopThreadPool::~EventLoopThreadPool()
{
    // 线程中绑定的loop，是在线程栈上创建的对象 ，不需要手动delete
}

void EventLoopThreadPool::start(const ThreadInitCallback& cb)
{
    started_ = true;
    for(int i = 0; i  < numThreads_; ++i)
    {
        char buf[name_.size() + 32];
        snprintf(buf, sizeof buf, "%s%d", name_.c_str(), i);
        EventLoopThread* t = new EventLoopThread(cb, buf) ;
        threads_.emplace_back(std::unique_ptr<EventLoopThread>(t)); // 智能指针自动释放资源
        loops_.emplace_back(t->startLoop());    //底层创建线程，绑定一个新的eventLoop
    }
    // 整个服务端只有一个线程，运行baseLoop， 
    if(numThreads_ == 0 && cb)
    {
        cb(baseLoop_);
    }
}

   
EventLoop* EventLoopThreadPool::getNextLoop()
{
    EventLoop* loop = baseLoop_;
    if(!loops_.empty())
    {
        loop = loops_[next_++];
        if(static_cast<size_t>(next_) >= loops_.size())
        {
            next_ = 0;
        }
    }
    
    return loop;
}

std::vector<EventLoop*> EventLoopThreadPool::getAllLoops()
{
    if(loops_.empty())
    {
        return std::vector<EventLoop*>(1, baseLoop_);
    }
    else
    {
        return loops_;
    }
}