#pragma once

#include <vector>
#include <unordered_map>

#include "noncopyable.h"
#include "Timestamp.h"

class Channel;
class EventLoop;

// moduo库中 Demultiplex  的核心I/O复用模块
class Poller : noncopyable
{
public:
    //指针变量，不用前置声明class EventLoop
    using ChannelList = std::vector<Channel*>;
    Poller(EventLoop* loop);
    virtual ~Poller() = 0;

    virtual Timestamp poll(int timeoutMs, ChannelList* activeChannels) = 0;

    virtual void updateChannel(Channel* channel) = 0;

    virtual void removeChannel(Channel* channel) = 0;
    //判断Channel是否在当前loop中
    virtual bool hasChannel(Channel* channel) const ;
    //EventLoop可以通过该接口获取默认的IO复用的具体实现：poll还是epoll
    static Poller* newDefaultPoller(EventLoop* loop);


protected:
    // key 是 sockfd， channel 是指sockfd所处的channel
    using ChannelMap = std::unordered_map<int, Channel*>;
    ChannelMap Channels_;
private:
    EventLoop *ownerLoop_;  //定义事件所属的事件循环

};