#include "Thread.h"
#include "CurrentThread.h"

#include <semaphore.h>
std::atomic_int Thread::numCreated_(0);

Thread::Thread(ThreadFunc func, const std::string& name)
    : started_(false)
    , joined_(false)
    , tid_(0)
    , func_(std::move(func))
    , name_(name)
{
     setDefaultName();
}
Thread::~Thread()
{   // 销毁的前提是线程已经开启，并且不处于join状态
    if(started_ && !joined_)
    {
        // 将线程设置为分离状态，线程结束后会被自动回收
        thread_->detach();
    }

}
void Thread::start()    // 一个Thread对象，记录的是一个新线程的详细信息
{
    started_ = true;
    sem_t sem;
    sem_init(&sem, false, 0);

    thread_ = std::shared_ptr<std::thread>(new std::thread([&](){
        tid_ = CurrentThread::tid();
        sem_post(&sem); //信号量+1
        func_();
    }));
    // 如果线程还未被创建出来，那么就会阻塞带wait()
    // 这里必须等待获取上面新创建的线程tid，使用信号量处理
    sem_wait(&sem); //
}
void Thread::join()
{
    joined_ = true;
    thread_->join();
}

void Thread::setDefaultName()
{
    int num = ++numCreated_;
    if(name_.empty())
    {
        char buf[32];
        snprintf(buf, sizeof(buf), "Thread%d", num);
        name_ = buf;
    }

}