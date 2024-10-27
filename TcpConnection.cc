#include "TcpConnection.h"
#include "logger.h"
#include "Socket.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include "Channel.h"
#include "Callbacks.h"

#include <functional>
#include <string>
#include <errno.h>
#include <sys/types.h>          
#include <sys/socket.h>
static EventLoop* checkLoopNotNull(EventLoop* loop)
{
    if(!loop)
    {
        LOG_FATAL("%s:%s:%d TcpConnection loop is null\n", __FILE__, __FUNCTION__, __LINE__);
    }
    return loop;
}


TcpConnection::TcpConnection(EventLoop* loop
                           , const std::string& nameArg
                           , int connfd
                           , const InetAddress& localAddr
                           , const InetAddress& peerAddr)
    : loop_(checkLoopNotNull(loop))
    , name_(nameArg)
    , state_(kConnecting)
    , reading_(true)
    , socket_(new Socket(connfd))
    , channel_(new Channel(loop, connfd))
    , localAddr_(localAddr)
    , peerAddr_(peerAddr)
    , highWaterMark_(64*1024*1024) // 64MB

{
    channel_->setReadCallback(std::bind(&TcpConnection::handleRead, this, std::placeholders::_1));
    channel_->setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
    channel_->setCloseCallback(std::bind(&TcpConnection::handleClose, this));
    channel_->setErrorCallback(std::bind(&TcpConnection::handleError, this));

    LOG_INFO("TcpConnection::ctor[%s] at %p fd=%d \n", name_.c_str(), this, connfd);
    socket_->setKeepAlive(true);
}

TcpConnection::~TcpConnection()
{
    LOG_INFO("TcpConnection::dtor[%s] at %p fd=%d state=%d\n", name_.c_str(), this, channel_->fd(), (int)(state_));

}

void TcpConnection::handleRead(Timestamp receiveTime)
{
    int savedErrno = 0;
    ssize_t n = inputBuffer_.readFd(channel_->fd(), &savedErrno);
    if (n > 0)
    {
        // 已建立连接的客户，有可读事件发生了，调用用户传入的回调操作onMessage
        messageCallback_(shared_from_this(), &inputBuffer_, receiveTime);
    }
    else if (n == 0)    //客户端断开
    {
        handleClose();
    }
    else
    {
        errno = savedErrno;
        LOG_ERROR("TcpConnection::handleRead\n");
        handleError();
    }

}
void TcpConnection::handleWrite()
{
    if (channel_->isWriting())
    {   int savedErrno = 0;
        ssize_t n = outputBuffer_.writeFd(channel_->fd(), &savedErrno);
        if (n > 0)
        {
            outputBuffer_.retrieve(n);
            if (outputBuffer_.readableBytes() == 0)
            {
                channel_->disableWriting();
                if(writeCompleteCallback_)
                {
                   loop_->queueInLoop(std::bind(writeCompleteCallback_, shared_from_this())); 
                }
                if(state_ == kDisconnecting)
                {
                    shutdownInLoop();
                }

            }
        }
        else
        {
            LOG_ERROR("TcpConnection::handleWrite\n");
        }

    }
    else
    {
        LOG_ERROR("Connection fd =%d, is down, no more writing\n", channel_->fd());
    }
}
void TcpConnection::handleClose()
{
    LOG_INFO("fd = %d, state = %d\n", channel_->fd(), (int)state_);
    setState(kDisconnected);
    channel_->disableAll();
    
    TcpConnectionPtr connPtr(shared_from_this());
    // 这个回调负责连接的建立，连接的断开都会执行
    connectionCallback_(connPtr);
    closeCallback_(connPtr);


}
void TcpConnection::handleError()
{
    int optval;
    socklen_t optlen = sizeof optval;
    int err = 0;
    if(::getsockopt(channel_->fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0)
    {
        err = errno;
    }
    else
    {
        err = optval;
    }
    LOG_ERROR("TcpConnection::handleError name:%s - SO_ERROR:%d\n", name_.c_str(), err);

}
void TcpConnection::send(const std::string& buf)
{
    if(state_ == kConnected)
    {
        if(loop_->isInLoopThread())
        {
            sendInLoop(buf.c_str(), buf.size());
        }
        else
        {
            loop_->runInLoop(std::bind(&TcpConnection::sendInLoop, this, buf.c_str(), buf.size()));

        }

    }
}


// 发送数据 应用写的快，内核发的慢， 需要把待发送数据写入缓冲区，而且设置了水位回调
void TcpConnection::sendInLoop(const void* message, size_t len)
{
    ssize_t nwrote = 0;
    size_t remaining = len; // 没发送完的数据
    bool faultError = false;
    // 之前调用过该connection的shutdown()
    if (state_ == kDisconnected)
    {
        LOG_ERROR("disconnected, give up writing\n");
        return ;
    }
    // channel在初始化时，默认对读事件感兴趣
    // 表示channel第一次开始写事件，并且缓冲区没有待发送事件

    if(!channel_->isWriting() && outputBuffer_.readableBytes() == 0)
    {
        // 直接向fd发，不经过buffer
        nwrote = ::write(channel_->fd(), &message, len);
        if (nwrote >= 0)
        {
            remaining = len - nwrote;
            // 既然在这里数据Q全部发送完，就不用再给channel注册epollout事件了
            if (remaining == 0 && writeCompleteCallback_)
            {
                loop_->queueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
            }
        }
        else // nwrote < 0
        {
            nwrote = 0;
            if (errno != EWOULDBLOCK)
            {
                LOG_ERROR("TcpConnection::sendInLoop\n");
            }
            if (errno == EPIPE || errno == ECONNRESET)
            {
                faultError = true;
            }
        }
    }

    // 并没有把数据一次性的发送出去，剩余的数据保存在buffer中，
    // 然后注册epollout事件，LT， Poller发现tcp的发送缓冲区有空间，会通知对应的channel， 调用TcpConnection::handleWrite()回调
    if(!faultError && remaining > 0)
    {
        // oldLen 表示buffer中剩余的待发送数据
        size_t oldLen = outputBuffer_.readableBytes();
        if (oldLen + remaining >= highWaterMark_
            &&  oldLen < highWaterMark_
            &&  highWaterMarkCallback_)
        {
            loop_->queueInLoop(std::bind(highWaterMarkCallback_, shared_from_this(), oldLen + remaining));

        }
        outputBuffer_.append((char*)message + nwrote, remaining);
        // 注册EPOLLOUT
        if (!channel_->isWriting())
        {
            channel_->enableWriting();
        }
    }
}
void TcpConnection::shutdown()
{
    if (state_ == kConnected)
    {
        setState(kDisconnecting);
        loop_->runInLoop(std::bind(&TcpConnection::shutdownInLoop, this));
    }
}
void TcpConnection::shutdownInLoop()
{
    
    if(channel_->isWriting()) // 说明outputBuffer的数据全部发送完成
    {
        socket_->shutdownWrite();
    }

}
// 建立连接
void TcpConnection::connectEstablished()
{
    setState(kConnected);
    channel_->tie(shared_from_this());  // 保证TcpConnection和Channel的生命周期一致
    channel_->enableReading();
    connectionCallback_(shared_from_this());
}
// 关闭连接
void TcpConnection::connectDestroyed()
{
    if (state_ == kConnected)
    {
        setState(kDisconnected);
        channel_->disableAll();
        connectionCallback_(shared_from_this());

    }
    channel_->remove();
    

}
