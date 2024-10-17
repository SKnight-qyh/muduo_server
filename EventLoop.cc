#include "EventLoop.h"
#include "logger.h"
#include "CurrentThread.h"
#include "Poller.h"
#include "EPollPoller.h"
#include "Channel.h"

#include <sys/eventfd.h>
#include <errno.h>
#include <unistd.h>
#include <memory>

//防止一个线程创建多个EventLoop
__thread EventLoop* t_loopInThisThread = nullptr;

const int kPollTimeMs = 10000;//默认Poller超时时间10ms
// 创建wakeupFd_,用来通知唤醒subReactor处理新来的channel
int creatEventfd()
{
    int evtfd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if(evtfd < 0)
    {
        LOG_FATAL("eventfd error:%d\n", errno);
    }
}
EventLoop::EventLoop()
    : looping_(false)
    , quit_(false)
    , callingPendingFunctors_(false)
    , threadId_(CurrentThread::tid())
    , poller_(Poller::newDefaultPoller(this))
    , wakeupFd_(creatEventfd())
    , wakeChannel_(new Channel(this, wakeupFd_))    //只是注册，并未设置感兴趣的事件
{
    LOG_DEBUG("EventLoop created %p in thread %d\n", this, threadId_);
    if(t_loopInThisThread)
    {
        LOG_FATAL("Another EventLoop %p exists in this thread %d\n", t_loopInThisThread, threadId_);    
    }
    else
    {
        t_loopInThisThread = this;
    }
    //设置wakeupFd 的事件类型以及发生事件后的回调
    wakeChannel_->setReadCallback(std::bind(&EventLoop::handleRead, this));
    // 每一个EventLoop都将监听wakeChannel_ 的EPOLLIN事件
    wakeChannel_->enableReading();
}

EventLoop::~EventLoop()
{
    wakeChannel_->disableAll();
    wakeChannel_->remove(); //从Poller中移除
    ::close(wakeupFd_);
    t_loopInThisThread  = nullptr;
}

void EventLoop::handleRead()
{
    uint64_t one = 1;
    ssize_t n = read(wakeupFd_, &one, sizeof one);
    if(n != sizeof one)
    {
        LOG_ERROR("EventLoop::handleRead() reads  %d bytes instead of 8\n", n);
    }
}
void EventLoop::loop()
{
    looping_ = true;
    quit_ = false;
    LOG_INFO("EventLoop %p starts loop\n", this);
    // 监听两种fd，client的fd和wakeupfd_
    while(!quit_)
    {
        activeChannels_.clear();
        pollReturnTime_ = poller_->poll(kPollTimeMs, &activeChannels_);
        for(auto channel : activeChannels_)
        {
            channel->handleEvent(pollReturnTime_);
        }
        // 执行当前EventLoop中需要处理的回调函数
        /* 
         * mainLoop 事先注册一个或者多个回调cb（需要subLoop执行），
         * 当wakeup subLoop后，执行mainLoop注册的cb操作
         */
        doPendingFunctors();
    
    }
    LOG_INFO("EventLoop %p stops loop\n", this);

    looping_ = false;
}
void EventLoop::quit()
{
    quit_ = true;
    // 情况1：非looping的线程中调用了quit，则需要唤醒loop
    // 情况2：正在looping的线程中调用了quit
    if(!isInLoopThread())
    {
        wakeup();
    }
}

void EventLoop::runInLoop(Functor cb)
{
    if(isInLoopThread())
    {
        cb();
    }
    else//在非当前loop线程中调用，就需要唤醒loop线程，执行cb
    {
        queueInLoop(cb);
    }
}

void EventLoop::queueInLoop(Functor cb)
{
    // 多个loop 调用runInLoop，涉及并发访问，需要引用锁
    {
    std::unique_lock<std::mutex> lock(mutex_);
    pendihgFunctors_.emplace_back(cb);
    }
    // 在非当前loop线程中调用，就需要唤醒loop线程，执行cb
    // 或者当前loop正在执行回调，当loop又有了新的回调，执行完回调后，会被阻塞在poll，需要被重新唤醒
    if(!isInLoopThread() || callingPendingFunctors_)
    {
        wakeup();
    }
}

void EventLoop::wakeup()
{
    uint64_t one = 1;
    ssize_t n = write(wakeupFd_, &one, sizeof one);
    if(n != sizeof one)
    {
        LOG_ERROR("EventLoop::wakeup() writes %d bytes instead of 8\n", n); 

    }
}

void EventLoop::updateChannel(Channel* channel)
{
    poller_->updateChannel(channel);
}


void EventLoop::removeChannel(Channel* channel)
{
    poller_->removeChannel(channel);
}

void EventLoop::hasChannel(channel)
{
    poller_->hasChannel(channel);
}

void EventLoop::doPendingFunctors()
{
    // cb在不断的emplace_back,由于加锁
    // 如果一个一个的取cb， 开销非常大
    // 所以定义vector，一次性取出所有cb，然后执行
    std::vector<Functor> functors;
    callingPendingFunctors_ = true;
    {
        std::unique_lock<std::mutex> lock(mutex_);
        functors.swap(pendingFunctors_);

    }
    for(const auto& functor : functors)
    {
        functor();
    }
    callingPendingFunctors_ = false;
}