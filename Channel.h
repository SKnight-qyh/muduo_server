#pragma once

#include "noncopyable.h"
#include "Timestamp.h"

#include <memory>
#include <functional>
//前置声明
class EventLoop;



/** 
 * Channel 理解为通道，封装了socket和其感兴趣的event，如EPOLLIN、EPOLLOUT事件
 * 还绑定了poller返回的具体事件
 */
class Channel : noncopyable
{
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(Timestamp)>;

    Channel(EventLoop *loop, int fd);
    ~Channel();
    //使用指针，大小是4个字节，直接前置声明就行
    //Timestamp需要计算整个大小，需要包含头文件
    // fd得到Poller通知后来处理事件
    void handleEvent(Timestamp receiveTime);

    //设置回调函数对象
    void setReadCallback(ReadEventCallback cb) { readCallback_ = std::move(cb); }
    void setWriteCallback(EventCallback cb) { writeCallback_ = std::move(cb); }
    void setCloseCallback(EventCallback cb) { closeCallback_ = std::move(cb); }
    void setErrorCallback(EventCallback cb) { errorCallback_ = std::move(cb); }

    // 防止channel被手动remove掉，channel还在执行回调操作
    void tie(const std::shared_ptr<void>&);
    
    int fd() const { return fd_; }
    int events() const { return events_; }
    void set_revents(int revt)   { revents_ = revt; }
   
    
    //设置fd相应的事件状态
    void enableReading() { events_ |= kReadEvent; update(); }
    void disableReading() { events_ &= ~kReadEvent; update(); }
    void enableWriting() { events_ |= kWriteEvent; update(); }
    void disableWriting() { events_ &= ~kWriteEvent; update(); } 
    void disableAll() { events_ = kNoneEvent; update();}

    //返回fd当前的事件状态
    bool isReading() const { return events_ & kReadEvent; }
    bool isWriting() const { return events_ & kWriteEvent; }
    bool isNoneEvent() const { return events_ == kNoneEvent; }
    
    //for Poller
    int index() const { return index_; }
    void set_index(int idx) {index_ = idx; }

    // one loop per thread
    EventLoop* ownerLoop() { return loop_; }
    void remove();

private:

    void update();
    void handleEventWirthGuard(Timestamp receiveTime);

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_;   //事件循环
    int fd_;    // Poller监听的对象
    int events_;    //注册fd感兴趣的事件
    int revents_;   // Poller返回的具体发生的事件
    int index_;

    std::weak_ptr<void> tie_;
    bool tied_; //绑定

    //因为Channel通道里能获得fd最终发生的具体事件revents，所以它负责具体事件的回调操作
    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;

};