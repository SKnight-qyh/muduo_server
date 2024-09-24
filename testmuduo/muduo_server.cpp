/*muduo库主要的两个类：
    TcpServer
    TcpClient
    能把网络I/O的代码和业务代码区分开
        把 用户的连接和断开 和 用户的可读写事件 暴露出来

*/
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <functional>
#include <iostream>
using namespace std;
using namespace placeholders;
using namespace nuduo::net::TcpServer;
using namespace nuduo::net;

//基于muduo网络库开发服务器程序
//1. 组合TcpServer对象
//2. 创建EventLoop事件循环对象的指针
//3. 明确TcpServer构造函数需要什么参数，输出ChatServer构造函数
//4. 在当前服务器类的构造函数当中，注册处理连接的回调函数和处理读写事件的回调函数
//5. 设置合适的服务端线程数量，muduo库会自适应的分配I/O线程和工作线程
class ChatServer
{
public:
    ChatServer(EventLoop* loop, //时间循环
            const InetAddress& listenAddr,  //IP + port
            const string& nameArg)      //服务器名称
            : _server(_loop, listenAddr, nameArg)
            , _loop(loop)
            {
                //给服务器注册用户连接的创建和断开回调
                _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

                //给服务器注册用户读写事件回调
                _server.setMessageCallback(std::bind(ChatServer::onMessage, this, _1, _2, _3));

                //设置线程数量
                _server.setThreadNum(3);    //muduo库会自适应，将有1个IO线程，2个工作线程
            }
    //开启事件循环
    void start(){
        _server.start();
    }
private:
    //专门处理用户的连接创建和断开 epoll lintenfd accept
    void onConnection(const TcpConnectionPtr &conn) {
        
        
    }

    //专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr &conn,    //连接
                            Buffer *buf,    //缓冲区
                            Timestamp time) //接收到数据的时间信息
                            {

                            }
    muduo::net::TcpServer _server;  //#1
    muduo::net::EventLoop *_loop;   //#2 epoll
};
