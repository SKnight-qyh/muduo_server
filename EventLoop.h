#pragma once 

#include "noncopyable.h"
#include "Timestamp.h"
#include "CurrentThread.h"

#include <mutex>
#include <vector>
#include <memory>
#include <atomic>

class Channel;
class Poller;

//事件循环类
//主要包含两个大模块 Channel Poller (epoll的抽象)
class EventLoop : noncopyable
{
public:
    using Functor = std::function<void()>;
    EventLoop();
    ~EventLoop();
    void loop();    //开启事件循环
    void quit();    //退出事件循环
    Timestamp pollReturnTime() const { return pollReturnTime_; } 
   
    void runInLoop(Functor cb); //在当前loop中执行回调操作
    void queueInLoop(Functor cb);//把cb放在队列中,唤醒loop所在线程，并执行
    void wakeup();
    //调用Poller的方法
    void updateChannel(Channel* channel); //更新channel的状态
    void removeChannel(Channel* channel); //从activeChannels_中移除channel
    void hasChannel(Channel* channel);
   
   
    bool isInLoopThread() const { return threadID_ == CurrentThread::tid(); }

    // static EventLoop* getEventLoopOgCurrentThread();

private:
    void handleRead();//唤醒 wakup()
    void doPendingFunctors();   //执行pendingFunctors中的回调操作

    using ChannelList = std::vector<Channel*>; 
    ChannelList activeChannels_;
    std::unique_ptr<Poller> poller_;
    
    std::atomic_bool looping_;//原子操作，通过CAS来实现
    std::atomic_bool quit; //标识退出loop循环
    const pid_t threadID_; //当前loop所在的线程ID
    Timestamp pollReturnTime_;// 记录Poller返回activeChannels的时间

    int wakeupFd_;  //调用eventfd()函数
    std::unique_ptr<Channel> wakeChannel_; // 封装wakeupFd_
    Channel* currentActiveChannel_; // 主要是为了断言
    std::atomic_bool callingPendingFunctors; //标识当前loop是否正在调用回调操作
    std::vector<Functor> pendingFunctors; //存储loop需要执行的所有Loop操作

    std::mutex mutex_;  // 互斥锁用来保护上面vector容器的线程安全操作
    
}; 
