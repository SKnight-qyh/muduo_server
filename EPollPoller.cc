#include "EPollPoller.h"
#include "logger.h"
#include "Channel.h"


#include <sys/epoll.h>
#include <errno.h>
#include <strings.h>
#include <unistd.h>
//表示Channel和epoll当前的状态
const int kNew = -1;    // channel还未被添加到epoll
const int kAdded = 1;   // channel已经添加到epoll
const int kDelete = 2;  // channel从Poller中删除

EPollPoller::EPollPoller(EventLoop* loop)
    : Poller(loop)
    , epollfd_(::epoll_create1(EPOLL_CLOEXEC))
    , events_(kInitEventListSize)
{
    if(epollfd_ < 0)
    {
        LOG_FATAL("epoll_create error : %d \n", errno);
    }
}

EPollPoller::~EPollPoller()
{
    ::close(epollfd_);
}
Timestamp EPollPoller::poll(int timeoutMs, ChannelList* activeChannels)
{
    //用DEBUG 来打印日志更合理，因为会频繁调用，LOG_INFO会打印很多，影响性能
    LOG_DEBUG("func=%s => total count=%d\n", __FUNCTION__, channels_.size());
    int numEvents = ::epoll_wait(epollfd_, 
                                 &*events_.begin(),
                                 static_cast<int>(events_.size()),
                                 timeoutMs);
    int savedErrno = errno; 
    Timestamp now(Timestamp::now());    

    if(numEvents > 0)
    {
        LOG_INFO("%d events happened\n", numEvents);
        fillActiveChannels(numEvents, activeChannels);
        //如果监听的事件都发生了，那么就需要扩容events_数组
        if(events_.size() == numEvents) 
        {
            events_.resize(events_.size() * 2);
        }
    } 
    else if(numEvents == 0) 
    {
        LOG_DEBUG("nithing hanppened\n");
    }  
    else
    {
        if(savedErrno != EINTR)
        {
            errno = savedErrno;
            LOG_ERROR("EPollPoller::Poll() error:%d \n", errno);
        }
    }
    return now;//返回具体Poll的时间点                    
}
    // epoll_ctl
void EPollPoller::updateChannel(Channel* channel)
{
    // index 初始化为-1，对应的就是kNew 未添加到epoll
    // 还要添加到channelmap中
    const int index = channel->index();
    LOG_INFO("func=%s => fd=%d, events=%d, index=%d\n", __FUNCTION__, channel->fd(), channel->events(), index);

    if(index == kNew || index == kDelete)
    {
        int fd = channel->fd();
        if(index == kNew)
        {
            Channels_[fd] = channel;
        }
        channel->set_index(kAdded);
        update(EPOLL_CTL_ADD, channel);
    }
    else  // index == kAdded
    {
        // update existing one with EPOLL_CTL_MOD/DEL
        int fd = channel->fd();
        (void)fd;//强制转换，说明变量fd在后续代码中未被使用
        if(channel->isNoneEvent())  //该channel对任何事件都不感兴趣，则删除该channel
        {
            update(EPOLL_CTL_DEL, channel);
        }
        else
        {
            update(EPOLL_CTL_MOD, channel);
        }
    }

}
    
void EPollPoller::removeChannel(Channel* channel)
{
    //不仅需要在channelmap中删除，还需要再epoll中删除
    int fd = channel->fd();
    int index = channel->index();
    LOG_INFO("func=%s => fd=%d\n", __FUNCTION__, channel->fd());

    Channels_.erase(fd);
    //在epoll中删除
    if(index == kAdded)
    {
        update(EPOLL_CTL_DEL, channel);
    }
    channel->set_index(kNew);

}

void EPollPoller::fillActiveChannels(int numEvents, 
                                     ChannelList* activeChannels) const
{
    for(int i = 0; i < numEvents; ++i)
    {
        Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
        channel->set_revents(events_[i].events);
        activeChannels->push_back(channel);
    }
}
//更新Channel通道 通过epoll_ctl方式
void EPollPoller::update(int operation, Channel* channel)
{
    epoll_event event;
    bzero(&event, sizeof event);
    event.events = channel->events();
    event.data.ptr = channel;
    int fd = channel->fd();
    if(::epoll_ctl(epollfd_, operation,fd, &event) < 0)
    {
        if(operation == EPOLL_CTL_DEL)
        {
            LOG_ERROR("epoll_ctl del error:%d \n", errno);
        }
        else
        {
            LOG_FATAL("epoll_ctl add/mod error:%d \n", errno);
        }
    }

}
