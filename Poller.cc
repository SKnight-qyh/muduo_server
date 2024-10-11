#include "Poller.h"
#include "Channel.h"

Poller::Poller(EventLoop* loop)
    : ownerLoop_(loop)
{
}
Poller::~Poller() = default;

//判断Channel是否在当前loop中
bool Poller::hasChannel(Channel* channel) const
{
    //ChannelMap::const_iterator
    auto it = Channels_.find(channel->fd());
    return it != Channels_.end() && it->second == channel;
}
//EventLoop可以通过该接口获取默认的IO复用的具体实现：poll还是epoll
//static Poller* newDefaultPoller(EventLoop* loop);
//并没有实现