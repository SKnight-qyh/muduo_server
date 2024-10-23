#include "TcpServer.h"
#include "logger.h"

EventLoop* checkLoopNotNull(EventLoop* loop)
{
    if(!loop)
    {
        LOG_FATAL
    }
}


TcpServer::TcpServer(EventLoop* loop
                   , const InetAddress& listenAddr
                   , Option option)
    : 
