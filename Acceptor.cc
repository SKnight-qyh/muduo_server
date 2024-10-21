#include "Acceptor.h"
#include "logger.h"
#include "InetAddress.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
static int createNonblocking()
{
    int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
    if( sockfd < 0 ) 
    {
        LOG_FATAL( "%s:%s:%d socket errno: %d\n", __FILE__, __FUNCTION__, __LINE__, errno);
    }
    return sockfd;
}

Acceptor::Acceptor(EventLoop* loop, const InetAddress& listenAddr, bool reusePort)
    : loop_(loop)
    , acceptSocket_(createNonblocking())
    , listenning_(false)
    , acceptChannel_(loop, acceptSocket_.fd())
{
    acceptSocket_.setReuseAddr(true);
    acceptSocket_.setReuseAddr(reusePort);
    acceptSocket_.bindAddress(listenAddr);

    // TcpServer::start() 启动Acceptor的listen后
    // 有新用户的连接，要执行一个回调
    // 回调的作用就是将fd打包成一个Channel，==》唤醒一个subloop，由subloop监听客户端的读写事件

    // 绑定回调
    acceptChannel_.setReadCallback(std::bind(&Acceptor::handleRead, this));


}
Acceptor::~Acceptor()
{
    // 删除channel 并删除在Poller中注册的事件
    acceptChannel_.disableAll();
    acceptChannel_.remove();
    

}
void Acceptor::listen()
{
    listenning_ = true;
    acceptSocket_.listen();
    acceptChannel_.enableReading(); // 将channel注册到Poller中

}


// listenfd有事件发生了，就是有新用户连接了
void Acceptor::handleRead()
{
    InetAddress peerAddr;
    int connfd = acceptSocket_.accept(&peerAddr);
    if(connfd > 0)
    {
        if(newConnectionCallback_)
        {
            // 轮询找到subloop，唤醒并分发当前的新客户端的channel
            newConnectionCallback_(connfd, peerAddr);
        }
        else
        {
            ::close(connfd);
        }
    }
    else
    {
        LOG_ERROR("%s:%s:%d accept errno: %d\n", __FILE__, __FUNCTION__, __LINE__, errno);
        if(errno == EMFILE)
        {
        LOG_ERROR("%s:%s:%d sockfd reach limit \n", __FILE__, __FUNCTION__, __LINE__);

        }
    }

}