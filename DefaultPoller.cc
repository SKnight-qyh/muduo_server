#include "Poller.h"

#include <stdlib.h>

Poller* Poller::newDefaultPoller(EventLoop* loop)
{
    if(::getenv()"MUDUO_USE_POLL")
    {
        return nullptr; //生成PollPoller的实例
    }
    else
    {
        return new EpollPoller(loop);
    }
}