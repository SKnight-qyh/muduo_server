cmake_minimum_required(VERSION 2.5)
project(mymuduo)


#mymuduo最终编译成so动态库，这是设置动态库的路径:根目录下的lib文件夹
set(LIBRARY_OUTPUT_DIRECTORY $(PROJECT_SOURCE_DIR)/lib)

#设置调试信息
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

#定义参与编译的源文件
aux_source_directory(. SRC_LIST)
#编译动态库
add_library(mymuduo SHEARD ${SRC_LIST})