#!/bin/bash

set -e

if [ ! -d `pwd`/build ]; then
    mkdir `pwd`/build
fi

rm -rf `pwd`/build/*

cd `pwd`/build &&
    cmake .. &&
    make
cd ..

# 把.h拷贝到系统目录 /usr/include/remuduo
# 将so库拷贝到系统目录 /usr/lib
if [ ! -d /usr/include/remuduo ]; then
    mkdir /usr/include/remuduo
fi

for header in `ls *.h`
do
    cp $header /usr/include/remuduo
done

cp `pwd`/lib/libremuduo.so /usr/lib

# 刷新系统缓存, 使得添加路径生效
ldconfig 

# chmod +x autobuild.sh 添加执行权限