#pragma once

#include <unistd.h>
#include <sys/syscall.h>


namespace CurrentThread
{
    // 虽然是全局变量，加了 __thread 后，会在每一个线程中存储一份拷贝

    extern __thread int t_cachedTid;

    void cacheTid();

    //内联只在当前文件中生效，不会影响到其他文件
    //在头文件中实现
    inline int tid()
    {
        //如果没获取tid
        if(__builtin_expect(t_cachedTid == 0, 0))
        {
            cacheTid();
        }
        return t_cachedTid;
    }
}
