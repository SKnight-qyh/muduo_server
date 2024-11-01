#include <remuduo/TcpServer.h>
#include <remuduo/TcpConnection.h>
#include <remuduo/logger.h>


using namespace std::placeholders;
class EchoServer
{
public:
    EchoServer(EventLoop *loop
             , const InetAddress& listenAddr
             , const std::string& name = "EchoServer")
        : _loop(loop)
        , _server(loop, listenAddr, name)
    {
        // 注册回调
        _server.setConnectionCallback(
            std::bind(&EchoServer::onConnection, this, _1)
        );

        _server.setMessageCallback(
            std::bind(&EchoServer::onMessage, this, _1, _2, _3)
        );

        // 设置合适的线程数量
        _server.setThreadNum(3);
    }
    void start()
    {
        _server.start();
    }

    private: 
    void onConnection(const TcpConnectionPtr& conn)
    {
        if(conn->connected())
        {
            LOG_INFO("connection UP : %s -> %s\n"
                    , conn->peerAddress().toIpPort().c_str()
                    , conn->localAddress().toIpPort().c_str());
        }
        else
        {
            LOG_INFO("connection DOWN : %s -> %s\n"
                    , conn->peerAddress().toIpPort().c_str()
                    , conn->localAddress().toIpPort().c_str());
        }    
    }
    void onMessage(const TcpConnectionPtr& conn
                 , Buffer* buf
                 , Timestamp time)
    {
        std::string msg = buf->retrieveALlAsString();
        conn->send(msg);
        printf("%s\n", msg.c_str());
        // conn->shutdown(); // 关闭写端 =》 EPOLLHUP => closeCallback_;

    }
    EventLoop *_loop; 
    TcpServer _server;
};
int main()
{
    EventLoop loop;
    InetAddress listenAddr(8000);
    EchoServer server(&loop, listenAddr);   // Acceptor create non-blocking listenfd and bind
    server.start(); // start listening linstenfd
    loop.loop();    // start loop;
    return 0;
}