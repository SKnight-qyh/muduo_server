#include "Channel.h"
#include "EventLoop.h"
#include "logger.h"

#include <sys/epoll.h>

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = EPOLLIN & EPOLLPRI;
const int Channel::kWriteEvent = EPOLLOUT;

Channel::Channel(EventLoop *loop, int fd)
    : loop_(loop)
    , fd_(fd)
    , events_(0)
    , revents_(0)
    , index_(-1)
    , tied_(false)
{
}

Channel::~Channel()
{
}

void Channel::tie(const std::shared_ptr<void> &obj)
{
    //std::weak_ptr<void> tie_;
    tie_ = obj;
    tied_ = true;

}

// 当改变channel所表示fd的events事件后，update负责改变fd相应的事件 epoll_ctl
// EventLoop => channelList Poller
void Channel::update()
{
    // 通过Channel所属的EventLoop，调用Poller相应的方法，注册fd的events事件
    loop_->updateChannel(this);
}

// 在Channel所属的EventLoop中，把当前的Channel删除
void Channel::remove()
{
    loop_->removeChannel(this);
}

void Channel::handleEvent(Timestamp receiveTime)
{
    std::shared_ptr<void> guard;
    if(tied_)
    {
        guard = tie_.lock();
        if(guard)
        {
            handleEventWirthGuard(receiveTime);
        }
    }
    else
    {
        handleEventWirthGuard(receiveTime);
    }
}
// 根据Poller通知Channel具体发生的事件，由Channel负责回调工作；
void Channel::handleEventWirthGuard(Timestamp receiveTime)
{
    LOG_INFO("channel handleEvent revent%d", revents_);
    if((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
    {
        if(closeCallback_)
            closeCallback_();

    }
    if(revents_ & EPOLLERR)
        errorCallback_();
    if(revents_ & (EPOLLIN | EPOLLPRI))
    {
        if(readCallback_)
            readCallback_(receiveTime);
    }
    if(revents_ & EPOLLOUT)
        writeCallback_();

}
