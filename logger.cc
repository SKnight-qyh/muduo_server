
#include <iostream>

#include "logger.h"

//获取唯一的实例对象
Logger& logger::instance()
{
    static logger logger;
    return logger;
}

//设置日志级别
void logger::setLogLevel(int level)
{
    logLevel_ = level;
}
//写日志 [级别信息] time : msg
void logger::log(std::string msg)
{
    switch (logLevel_)
    {
    case INFO:
        std::cout << "[INFO]" ;
        break;
    case ERROR:
        std::cout << "[ERROR]" ;
        break;
    case FATAL:
        std::cout << "[FATAL]";
        break;
    case DEBUG:
        std::cout << "[DEBUG]";
        break;
    default:
        break;
    }
    std::cout << "print time" << " : " << msg << std::endl;
}
