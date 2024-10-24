#pragma once

// 网络库底层的缓冲区定义

/// @code
/// +-------------------+------------------+------------------+
/// | prependable bytes |  readable bytes  |  writable bytes  |
/// |                   |     (CONTENT)    |                  |
/// +-------------------+------------------+------------------+
/// |                   |                  |                  |
/// 0      <=      readerIndex   <=   writerIndex    <=     size
/// @endcode



#include <vector>
#include <string>
#include <algorithm>

class Buffer
{
public:
    static const size_t kCheapPrepend = 8;
    static const size_t kInitialSize = 1024;

    explicit Buffer(size_t initialSize = kInitialSize)
        : buffer_(kCheapPrepend + initialSize)
        , readerIndex_(kCheapPrepend)
        , writerIndex_(kCheapPrepend)
    {   
    }
    ~Buffer();

    size_t readableBytes() const { return writerIndex_ - readerIndex_; }
    size_t writableBytes() const { return buffer_.size() - writerIndex_; }
    size_t prependableBytes() const { return readerIndex_; }
    
    const char* peek() const // 返回buffer中可读部分的起始地址
    { return begin() + readerIndex_; }

    // Buffer -> string
    void retrieve(size_t len)
    {
        if(len < readableBytes())
        {
            readerIndex_ += len;
        }
        else
        {
            retrieveAll();
        }

    }

    void retrieveAll()
    {
        readerIndex_ = kCheapPrepend;
        writerIndex_ = kCheapPrepend;
    }

    //  将onMessage上报的Buffer数据转换为string类型
    std::string retrieveALlAsString()
    {
        return retrieveAsString(readableBytes());
    }

    std::string retrieveAsString(size_t len)
    {
        std::string result(peek(), len);
        retrieve(len);  // 更新readerIndex_和writerIndex_
        return result;
    }

    void ensureWritableBytes(size_t len)
    {
        if(writableBytes() < len) // 需要对buffer进行扩容
        {
            makeSpace(len);
        }
    }
    // 扩容函数
    void makeSpace(size_t len)
    {
        if(writableBytes() + prependableBytes() < len + kCheapPrepend)
        {
            buffer_.resize(writerIndex_ + len);
        }
        else    // make space inside the buffer
        {
            // move readable data to the front 
            size_t readable = readableBytes();
            std::copy(begin() + readerIndex_
                    , begin() + writerIndex_
                    , begin() + kCheapPrepend);
            readerIndex_ = kCheapPrepend;
            writerIndex_ = readerIndex_ + readable;

        }

    }

    // 将数据添加到buffer中
    void append(const char* /*restrict*/ data, size_t len)
    {
        ensureWritableBytes(len);
        std::copy(data, data + len, beginWrite());
        hasWritten(len);

    }

    void hasWritten(size_t len)
    {
        writerIndex_ += len;
    }
    // read data directly into buffer
    ssize_t readFd(int fd, int* savefEeeno);


private:

    char* beginWrite()
    { return begin() + writerIndex_; }

    const char* beginWrite() const
    { return begin() + writerIndex_; }

    char* begin()
    {
        // 先是调用了迭代器的*重载函数，再&取地址
        return &*buffer_.begin();
    }
    // 常量方法，不能通过指针修改数据
    const char* begin() const 
    {
        // 先是调用了迭代器的*重载函数，再&取地址
        return &*buffer_.begin();
    }
    std::vector<char> buffer_;
    size_t readerIndex_;
    size_t writerIndex_;


};