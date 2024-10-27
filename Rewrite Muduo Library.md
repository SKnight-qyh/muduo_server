# Rewrite Muduo Library

### TARGET OF REWRITE :

- 完全依赖C++11标准库，舍弃对boost库的依赖，可移植性更强

  ![1729694778272](images/RewriteMuduoLibrary/1729694778272.png)![1729949961596](images/RewriteMuduoLibrary/1729949961596.png)

```mermaid
sequenceDiagram
title Reactor Model
participant Event
participant Reactor
participant Demultiplex
participant EventHandler
Event ->> Reactor: 注册 Event & Handler
loop 事件集合
Reactor ->> Reactor: Event 集合
end
Reactor ->> Demultiplex: Epoll add/mod/del Event
Reactor ->> Demultiplex: 启动反应堆
loop 事件分发器
Demultiplex ->> Demultiplex: 开启事件循环 Epoll_wait
end
Demultiplex ->> Reactor: 返回发生的revent
Reactor ->> EventHandler: 调用 Event 对应的事件处理器 EventHandler
```

sequenceDiagram
title Reactor Model
participant Event
participant Reactor
participant Demultiplex
participant EventHandler
Event ->> Reactor: 注册 Event & Handler
loop 事件集合
Reactor ->> Reactor: Event 集合
end
Reactor ->> Demultiplex: Epoll add/mod/del Event
Reactor ->> Demultiplex: 启动反应堆
loop 事件分发器
Demultiplex ->> Demultiplex: 开启事件循环 Epoll_wait
end
Demultiplex ->> Reactor: 返回发生的revent
Reactor ->> EventHandler: 调用 Event 对应的事件处理器 EventHandler

## EventLoop

***one loop per thread, one EventLoop includes a Poller and a ChannelList***

- 如何唤醒subLoop？

TcpServer::newConnection() 根据轮询算法选择一个subLoop，ioLoop = Thread::getNextLoop, 如果ioLoop正式当前loop，则runInLoop，否则就queueInLoop向wakeupfd发送8字节的数据，此时各个subloop正在睡眠，也就是阻塞于epoll_wait()，监听到wakeupfd发生事件，就会执行相应的回调操作，这种做法没有加同步队列，也就是mainLoop封装channel放在队列中，供subloop使用，muduo的做法拥有更高的效率，不需要频繁的切换锁

如何解决“粘包”问题

通过Buffer

### Channel

channel update/remove ==> EventLoop updateChannel/removeChannel ==> Poller updateChannel/removeChannel

Channel 的tie方法的作用
channel 的回调都是绑定的是TcpConnection的成员方法，如果TcpConnection被remove掉，channel将会执行回调的结果显然是未知的，一个TCPConnection绑定一个channel，在一个新连接创建的时候调用tie方法，使得channel有一个weak_ptr指向对应的TcpConnection，防止TCPCOnnection被自动释放资源 

### Poller

抽象类，不能实例化，不能拷贝构造

ChannelMap <fd, channel*>

#### 为什么要单独建立DefaultPoller.cc来专门实现Poller类的Poller方法

EventLoop 可以通过 Poller() 获取默认的IO复用的具体实现：poll 还是 epoll, 如果在Poller.cc中实现，需要引用 Poller 的派生类PollPoller 和 EpollPoler ，显然不合适的

### Buffer

### Acceptor => mainLoop

### TcpConnnection => subLoop

已经建立连接的客户端与服务器的通信链路

在sendInLoop()中如果没有把数据一次性的发送出去，那么剩余的数据保存在buffer中，然后注册epollout事件， Poller发现tcp的发送缓冲区有空间，会通知对应的channel， 调用TcpConnection::handleWrite()回调， 工作在LT模式，多次调用回调指导将发送缓冲区的的数据发送完毕