# Rewrite Muduo Library

```mermaid
sequenceDiagram
	title Reactor Model
    participant Event
    participant Reactor
    participant Demultiplex
    participant EventHandler
    Event ->> Reactor: 注册 Event && Handler
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

## EventLoop

***one loop per thread, one EventLoop includes a Poller and a ChannelList***

wakeupFd_：通过系统调用 eventfd() 实现，当 mainLoop 获取一个新用户的 channel，通过轮询算法选择一个 subLoop，通过该成员唤醒 subLoop

每一个 subReactor 监听一个 wakeupChannel，mainReactor 通过向 wakeChannel 写消息，某一个 subReactor 就会被唤醒，就会得到新用户连接的 Channel，

### Channel

### Poller

抽象类，不能实例化，不能拷贝构造

#### 为什么要单独建立DefaultPoller.cc来专门实现Poller类的Poller方法

EventLoop 可以通过 Poller() 获取默认的IO复用的具体实现：poll 还是 epoll, 如果在Poller.cc中实现，需要引用 Poller 的派生类PollPoller 和 EpollPoler ，显然不合适的
