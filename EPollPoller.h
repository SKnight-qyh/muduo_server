#pragma once

#include "Poller.h"
#include "Timestamp.h"

#include <vector>
#include <sys/epoll.h>

class Channel;

/* epoll工作流程
 * epoll_create
 * epoll_ctl add/mod/del
 * epoll_wait
 * 
 */
class EPollPoller : Poller
{
public:
    // epoll_create with epollfd_
    EPollPoller(EventLoop* loop);

    ~EPollPoller() override;    //用编译器检查基类中是否有对应的虚函数
    // epoll_wait
    Timestamp Poll(int timeoutMs, ChannelList* activeChannels) override;
    // epoll_ctl
    void updateChannel(Channel* channel) override;  
    void removeChannel(Channel* channel) override;

private:

    static const int kInitEventListSize = 16;
    using EventList = std::vector<epoll_event>;
    int epollfd_;
    EventList events_;
    //填写活跃的连接
    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;
    //更新Channel通道 通过epoll_ctl方式
    void update(int operation, Channel* channel);

};
