#include "EPollPoller.h"
#include "logger.h"

#include <sys/epoll.h>
#include <errno.h>

//表示Channel和epoll当前的状态
const int kNew = -1;    //chanel还未被添加到epoll
const int kAdded = 1;   //将chanel添加到epoll
const int kDelete = 2;

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

Timestamp EPollPoller::Poll(int timeoutMs, ChannelList* activeChannels)
{
}
    // epoll_ctl
void EPollPoller::updateChannel(Channel* channel)
{

}
    
void EPollPoller::removeChannel(Channel* channel)
{

}