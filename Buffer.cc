#include "Buffer.h"

#include <errno.h>
#include <sys/uio.h>
#include <unistd.h>

// read data from fd, Poller works in LT mode
// buffer大小有限，但是从fd上读数据的时候，却不知道tcp数据最终的大小
// extrabuf 栈上分配，自动释放，效率很高
ssize_t Buffer::readFd(int fd, int* savedErrno)
{
    char extrabuf[65536] = {0}; // 栈上内存 64k
    struct iovec vec[2];
    const size_t writeable = writableBytes();
    vec[0].iov_base = begin() + writerIndex_;
    vec[0].iov_len = writeable;
    vec[1].iov_base = extrabuf;
    vec[1].iov_len = sizeof extrabuf;
    // 如果writeable >= 64k，则只定义一块内存空间
    // 说明一次最多读取64k数据
    const int iovcnt = (writeable < sizeof extrabuf)? 2 : 1;
    const ssize_t n = ::readv(fd, vec, iovcnt);
    if( n < 0)
    {
        *savedErrno = errno;
    }
    else if (n <= writeable)
    {
        writerIndex_ += n;
    }
    else
    {
        writerIndex_ = buffer_.size();
        append(extrabuf, n - writeable);
    }
    return n;
}
ssize_t Buffer::writeFd(int fd, int* savedErrno)
{
    const size_t readable = readableBytes();
    const ssize_t n = ::write(fd, peek(), readable);
    if( n < 0)
    {
        *savedErrno = errno;
    }
    return n;
}