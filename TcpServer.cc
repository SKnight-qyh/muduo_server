#include "TcpServer.h"
#include "logger.h"
#include "InetAddress.h"
#include "TcpConnection.h"
#include "Socket.h"

#include <functional>
#include <netinet/in.h>

static EventLoop* checkLoopNotNull(EventLoop* loop)
{
    if(!loop)
    {
        LOG_FATAL("%s:%s:%d mainoop is null\n", __FILE__, __FUNCTION__, __LINE__);
    }
    return loop;
}


TcpServer::TcpServer(EventLoop* loop
                   , const InetAddress& listenAddr
                   , const std::string& nameArg
                   , Option option)
    : loop_(checkLoopNotNull(loop))
    , name_(nameArg)
    , ipPort_(listenAddr.toIpPort())
    , acceptor_(new Acceptor(loop, listenAddr, option == kReusePort))
    , threadPool_(new EventLoopThreadPool(loop, name_))
    , connectionCallback_()
    , messageCallback_()
    , nextConnId_(1)
    , started_(0)
{

    acceptor_->setNewConnectionCallback(std::bind(&TcpServer::newConnection, this, std::placeholders::_1, std::placeholders::_2));
}

TcpServer::~TcpServer()
{
    for (auto& item : connectionMap_)
    {
        
        // 局部的强智能指针对象经过reset，出右括号后会自动释放new出来的TcpConnection对象资源
        // 细节在于reset后，item.second已经变成空悬指针，不能再用
        TcpConnectionPtr conn(item.second);
        item.second.reset();
        conn->getLoop()->queueInLoop(std::bind(&TcpConnection::connectDestroyed, conn));
    }

}

// 有一个新用户连接，acceptor会执行这个回调
// 根据轮询算法选中一个subLoop， 将当前connfd封装成channel，分发给subloop
void TcpServer::newConnection(int connfd, const InetAddress& peerAddr)
{
    EventLoop* ioLoop = threadPool_->getNextLoop();
    char buf[64];
    snprintf(buf, sizeof buf, "-%s#%d", ipPort_.c_str(), nextConnId_);
    ++nextConnId_;
    std::string connName = name_ + buf;

    LOG_INFO("TcpServer::newConnection [%s] - new connection[%s] from %s\n"
    , name_.c_str(), connName.c_str(), peerAddr.toIpPort().c_str());
    
    InetAddress localAddr(Socket::getLocalAddr(connfd));
    
    // 根据连接成功的connfd，创建TcpConnection
    TcpConnectionPtr conn(new TcpConnection(loop_
                                          , connName
                                          , connfd
                                          , localAddr
                                          , peerAddr));
    connectionMap_[connName] = conn;
    // 下面的回调由用户设置给TcpSerVer=>TcpConnection=>channel=>Poller=>notify channel调用回调
    conn->setConnectionCallback(connectionCallback_);
    conn->setMessageCallback(messageCallback_);
    conn->setWriteCompleteCallback(writeCompleteCallback_);
    conn->setCloseCallback(std::bind(&TcpServer::removeConnection, this, std::placeholders::_1));
    ioLoop->runInLoop(std::bind(&TcpConnection::connectEstablished, conn));

}


void TcpServer::start()
{
    if(started_++ == 0) // 保证start只被调用一次，防止start多次
    {
        threadPool_->start(threadInitCallback_);
        loop_->runInLoop(std::bind(&Acceptor::listen, acceptor_.get()));
    }
}

void TcpServer::setThreadNum(int numThreads)
{
    threadPool_->setThreadNum(numThreads);
}

void TcpServer::removeConnection(const TcpConnectionPtr& conn)
{
    loop_->runInLoop(std::bind(&TcpServer::removeConnectionInLoop, this, conn));
}
void TcpServer::removeConnectionInLoop(const TcpConnectionPtr& conn)
{
    LOG_INFO("TcpServer::removeConnection [%s] - connection[%s] is closed\n"
    , name_.c_str(), conn->name().c_str());

    connectionMap_.erase(conn->name());
    EventLoop* ioLoop = conn->getLoop();    // 切换到connection所在的subLoop
    ioLoop->queueInLoop(std::bind(&TcpConnection::connectDestroyed, conn));

}