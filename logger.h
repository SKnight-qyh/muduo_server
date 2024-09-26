#pragma once 

#include <string>

#include "noncopyable.h"


//定义日志级别
enum logLevel
{
    INFO,
    REEOR,
    FATAL,
    DEBUG
};

//输出一个日志类
class Logger : noncopyable 
{
public:
    //获取唯一的实例对象
    static Logger& instance();

    //设置日志级别
    void setLogLevel(int level);
    //写日志
    void log(std::string msg);

private:
    int logLevel_;
    logger(){}

};