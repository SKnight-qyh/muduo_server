/*muduo库主要的两个类：
    TcpServer
    TcpClient
    能把网络I/O的代码和业务代码区分开
        把 用户的连接和断开 和 用户的可读写事件 暴露出来

*/
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>

using namespace std;

//基于muduo网络库开发服务器程序
class ChatServer
{
public:
private:
};
