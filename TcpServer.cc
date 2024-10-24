#include "TcpServer.h"
#include "logger.h"
#include "InetAddress.h"

#include <functional>

EventLoop* checkLoopNotNull(EventLoop* loop)
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
{

    acceptor_->setNewConnectionCallback(std::bind(&TcpServer::newConnection, this, std::placeholders::_1, std::placeholders::_2));
}

TcpServer::~TcpServer()
{

}

// 根据轮询算法选中一个subLoop， 将当前connfd封装成channel，分发给subloop
void TcpServer::newConnection(int connfd, const InetAddress& peerAddr)
{
    EventLoop* ioLoop = threadPool_->getNextLoop();

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

}
void TcpServer::removeConnectionInLoop(const TcpConnectionPtr& conn)
{

}