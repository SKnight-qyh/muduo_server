#include "CurrentThread.h"



namespace CurrentThread 
{
    __thread int t_cachedTid = 0;
    void cacheTid()
    {
        if(t_cachedTid == 0)
        {
            //通过linux系统调用获取当前线程id
            return static_cast<pit_t>(::syscall(SYS_gettid));
        }
        
    }
}