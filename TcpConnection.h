#pragma once

#include "noncopyable.h"
#include "InetAddress.h"
#include "Callbacks.h"
#include "Timestamp.h"
#include "Buffer.h"

#include <memory>
#include <string>
#include <atomic>

class EventLoop;
class Channel;
class Socket;

/**
 * TcpServer => Acceptor => 有一个新用户连接 ，通过accept() 拿到connfd
 * => TcpConnection => 设置回调 => Channel => Poller => channel的回调操作
 * 
 */


class TcpConnection : noncopyable, public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(EventLoop* loop
                 , const std::string& name
                 , int connfd
                 , const InetAddress& localAddr
                 , const InetAddress& peerAddr);
    ~TcpConnection();
    EventLoop* getLoop() const { return loop_; }
    const std::string& name() const { return name_; }
    const InetAddress& localAddress() const { return localAddr_; }
    const InetAddress& peerAddress() const { return peerAddr_; }
    bool connected() const { return state_ == kConnected; }
    bool disconnected() const { return state_ == kDisconnected; }

    // void send(const void* data, int len);
    void send(const std::string& buf);

    // 关闭连接
    void shutdown();


    void setConnectionCallback(const ConnectionCallback& cb)
  { connectionCallback_ = std::move(cb); }

    void setMessageCallback(const MessageCallback& cb)
    { messageCallback_ = std::move(cb); }

    void setWriteCompleteCallback(const WriteCompleteCallback& cb)
    { writeCompleteCallback_ = std::move(cb); }

    void setHighWaterMarkCallback(const HighWaterMarkCallback& cb, size_t highWaterMark)
    { 
      highWaterMarkCallback_ = std::move(cb); 
      highWaterMark_ = highWaterMark; 
    }
    void setCloseCallback(const CloseCallback& cb)
    { closeCallback_ = std::move(cb); }


    // 建立连接
    void connectEstablished();
    // 关闭连接
    void connectDestroyed();

   

private:
    enum State  // 连接的状态
    {
        kDisconnected,
        kConnecting,
        kConnected,
        kDisconnecting  // 断开连接中
    };

    void handleRead(Timestamp receiveTime);
    void handleWrite();
    void handleClose();
    void handleError();

    void sendInLoop(const void* message, size_t len);
    void shutdownInLoop();

    void setState(State s) { state_ = s; }

    EventLoop *loop_;   // 如果setThreadNum()后，那么肯定不是baseLoop，因为TcpConnection都是在subLoop管理的
    const std::string name_;
    std::atomic_int state_;
    bool reading_;
    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;

    const InetAddress localAddr_;
    const InetAddress peerAddr_;

    // callbacks
    ConnectionCallback connectionCallback_;
    MessageCallback messageCallback_;
    WriteCompleteCallback writeCompleteCallback_;
    CloseCallback closeCallback_;
    // 防止client 和 server 的收发速率不同，导致数据丢失
    HighWaterMarkCallback highWaterMarkCallback_;
    size_t highWaterMark_;  // 高水位标记
    // buffer
    Buffer inputBuffer_;
    Buffer outputBuffer_;

};