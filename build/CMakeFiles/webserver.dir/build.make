# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yuqiao/Desktop/d/muduo_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yuqiao/Desktop/d/muduo_server/build

# Include any dependencies generated for this target.
include CMakeFiles/webserver.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/webserver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/webserver.dir/flags.make

CMakeFiles/webserver.dir/Acceptor.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/Acceptor.o: ../Acceptor.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/webserver.dir/Acceptor.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/Acceptor.o -c /home/yuqiao/Desktop/d/muduo_server/Acceptor.cc

CMakeFiles/webserver.dir/Acceptor.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/Acceptor.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuqiao/Desktop/d/muduo_server/Acceptor.cc > CMakeFiles/webserver.dir/Acceptor.i

CMakeFiles/webserver.dir/Acceptor.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/Acceptor.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuqiao/Desktop/d/muduo_server/Acceptor.cc -o CMakeFiles/webserver.dir/Acceptor.s

CMakeFiles/webserver.dir/Buffer.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/Buffer.o: ../Buffer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/webserver.dir/Buffer.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/Buffer.o -c /home/yuqiao/Desktop/d/muduo_server/Buffer.cc

CMakeFiles/webserver.dir/Buffer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/Buffer.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuqiao/Desktop/d/muduo_server/Buffer.cc > CMakeFiles/webserver.dir/Buffer.i

CMakeFiles/webserver.dir/Buffer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/Buffer.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuqiao/Desktop/d/muduo_server/Buffer.cc -o CMakeFiles/webserver.dir/Buffer.s

CMakeFiles/webserver.dir/Channel.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/Channel.o: ../Channel.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/webserver.dir/Channel.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/Channel.o -c /home/yuqiao/Desktop/d/muduo_server/Channel.cc

CMakeFiles/webserver.dir/Channel.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/Channel.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuqiao/Desktop/d/muduo_server/Channel.cc > CMakeFiles/webserver.dir/Channel.i

CMakeFiles/webserver.dir/Channel.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/Channel.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuqiao/Desktop/d/muduo_server/Channel.cc -o CMakeFiles/webserver.dir/Channel.s

CMakeFiles/webserver.dir/CurrentThread.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/CurrentThread.o: ../CurrentThread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/webserver.dir/CurrentThread.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/CurrentThread.o -c /home/yuqiao/Desktop/d/muduo_server/CurrentThread.cc

CMakeFiles/webserver.dir/CurrentThread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/CurrentThread.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuqiao/Desktop/d/muduo_server/CurrentThread.cc > CMakeFiles/webserver.dir/CurrentThread.i

CMakeFiles/webserver.dir/CurrentThread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/CurrentThread.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuqiao/Desktop/d/muduo_server/CurrentThread.cc -o CMakeFiles/webserver.dir/CurrentThread.s

CMakeFiles/webserver.dir/DefaultPoller.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/DefaultPoller.o: ../DefaultPoller.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/webserver.dir/DefaultPoller.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/DefaultPoller.o -c /home/yuqiao/Desktop/d/muduo_server/DefaultPoller.cc

CMakeFiles/webserver.dir/DefaultPoller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/DefaultPoller.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuqiao/Desktop/d/muduo_server/DefaultPoller.cc > CMakeFiles/webserver.dir/DefaultPoller.i

CMakeFiles/webserver.dir/DefaultPoller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/DefaultPoller.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuqiao/Desktop/d/muduo_server/DefaultPoller.cc -o CMakeFiles/webserver.dir/DefaultPoller.s

CMakeFiles/webserver.dir/EPollPoller.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/EPollPoller.o: ../EPollPoller.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/webserver.dir/EPollPoller.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/EPollPoller.o -c /home/yuqiao/Desktop/d/muduo_server/EPollPoller.cc

CMakeFiles/webserver.dir/EPollPoller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/EPollPoller.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuqiao/Desktop/d/muduo_server/EPollPoller.cc > CMakeFiles/webserver.dir/EPollPoller.i

CMakeFiles/webserver.dir/EPollPoller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/EPollPoller.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuqiao/Desktop/d/muduo_server/EPollPoller.cc -o CMakeFiles/webserver.dir/EPollPoller.s

CMakeFiles/webserver.dir/EventLoop.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/EventLoop.o: ../EventLoop.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/webserver.dir/EventLoop.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/EventLoop.o -c /home/yuqiao/Desktop/d/muduo_server/EventLoop.cc

CMakeFiles/webserver.dir/EventLoop.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/EventLoop.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuqiao/Desktop/d/muduo_server/EventLoop.cc > CMakeFiles/webserver.dir/EventLoop.i

CMakeFiles/webserver.dir/EventLoop.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/EventLoop.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuqiao/Desktop/d/muduo_server/EventLoop.cc -o CMakeFiles/webserver.dir/EventLoop.s

CMakeFiles/webserver.dir/EventLoopThread.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/EventLoopThread.o: ../EventLoopThread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/webserver.dir/EventLoopThread.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/EventLoopThread.o -c /home/yuqiao/Desktop/d/muduo_server/EventLoopThread.cc

CMakeFiles/webserver.dir/EventLoopThread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/EventLoopThread.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuqiao/Desktop/d/muduo_server/EventLoopThread.cc > CMakeFiles/webserver.dir/EventLoopThread.i

CMakeFiles/webserver.dir/EventLoopThread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/EventLoopThread.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuqiao/Desktop/d/muduo_server/EventLoopThread.cc -o CMakeFiles/webserver.dir/EventLoopThread.s

CMakeFiles/webserver.dir/EventLoopThreadPool.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/EventLoopThreadPool.o: ../EventLoopThreadPool.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/webserver.dir/EventLoopThreadPool.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/EventLoopThreadPool.o -c /home/yuqiao/Desktop/d/muduo_server/EventLoopThreadPool.cc

CMakeFiles/webserver.dir/EventLoopThreadPool.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/EventLoopThreadPool.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuqiao/Desktop/d/muduo_server/EventLoopThreadPool.cc > CMakeFiles/webserver.dir/EventLoopThreadPool.i

CMakeFiles/webserver.dir/EventLoopThreadPool.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/EventLoopThreadPool.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuqiao/Desktop/d/muduo_server/EventLoopThreadPool.cc -o CMakeFiles/webserver.dir/EventLoopThreadPool.s

CMakeFiles/webserver.dir/InetAddress.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/InetAddress.o: ../InetAddress.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/webserver.dir/InetAddress.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/InetAddress.o -c /home/yuqiao/Desktop/d/muduo_server/InetAddress.cc

CMakeFiles/webserver.dir/InetAddress.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/InetAddress.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuqiao/Desktop/d/muduo_server/InetAddress.cc > CMakeFiles/webserver.dir/InetAddress.i

CMakeFiles/webserver.dir/InetAddress.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/InetAddress.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuqiao/Desktop/d/muduo_server/InetAddress.cc -o CMakeFiles/webserver.dir/InetAddress.s

CMakeFiles/webserver.dir/Poller.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/Poller.o: ../Poller.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/webserver.dir/Poller.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/Poller.o -c /home/yuqiao/Desktop/d/muduo_server/Poller.cc

CMakeFiles/webserver.dir/Poller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/Poller.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuqiao/Desktop/d/muduo_server/Poller.cc > CMakeFiles/webserver.dir/Poller.i

CMakeFiles/webserver.dir/Poller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/Poller.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuqiao/Desktop/d/muduo_server/Poller.cc -o CMakeFiles/webserver.dir/Poller.s

CMakeFiles/webserver.dir/Socket.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/Socket.o: ../Socket.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/webserver.dir/Socket.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/Socket.o -c /home/yuqiao/Desktop/d/muduo_server/Socket.cc

CMakeFiles/webserver.dir/Socket.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/Socket.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuqiao/Desktop/d/muduo_server/Socket.cc > CMakeFiles/webserver.dir/Socket.i

CMakeFiles/webserver.dir/Socket.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/Socket.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuqiao/Desktop/d/muduo_server/Socket.cc -o CMakeFiles/webserver.dir/Socket.s

CMakeFiles/webserver.dir/TcpConnection.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/TcpConnection.o: ../TcpConnection.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/webserver.dir/TcpConnection.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/TcpConnection.o -c /home/yuqiao/Desktop/d/muduo_server/TcpConnection.cc

CMakeFiles/webserver.dir/TcpConnection.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/TcpConnection.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuqiao/Desktop/d/muduo_server/TcpConnection.cc > CMakeFiles/webserver.dir/TcpConnection.i

CMakeFiles/webserver.dir/TcpConnection.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/TcpConnection.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuqiao/Desktop/d/muduo_server/TcpConnection.cc -o CMakeFiles/webserver.dir/TcpConnection.s

CMakeFiles/webserver.dir/TcpServer.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/TcpServer.o: ../TcpServer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/webserver.dir/TcpServer.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/TcpServer.o -c /home/yuqiao/Desktop/d/muduo_server/TcpServer.cc

CMakeFiles/webserver.dir/TcpServer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/TcpServer.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuqiao/Desktop/d/muduo_server/TcpServer.cc > CMakeFiles/webserver.dir/TcpServer.i

CMakeFiles/webserver.dir/TcpServer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/TcpServer.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuqiao/Desktop/d/muduo_server/TcpServer.cc -o CMakeFiles/webserver.dir/TcpServer.s

CMakeFiles/webserver.dir/Thread.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/Thread.o: ../Thread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/webserver.dir/Thread.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/Thread.o -c /home/yuqiao/Desktop/d/muduo_server/Thread.cc

CMakeFiles/webserver.dir/Thread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/Thread.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuqiao/Desktop/d/muduo_server/Thread.cc > CMakeFiles/webserver.dir/Thread.i

CMakeFiles/webserver.dir/Thread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/Thread.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuqiao/Desktop/d/muduo_server/Thread.cc -o CMakeFiles/webserver.dir/Thread.s

CMakeFiles/webserver.dir/Timestamp.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/Timestamp.o: ../Timestamp.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/webserver.dir/Timestamp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/Timestamp.o -c /home/yuqiao/Desktop/d/muduo_server/Timestamp.cc

CMakeFiles/webserver.dir/Timestamp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/Timestamp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuqiao/Desktop/d/muduo_server/Timestamp.cc > CMakeFiles/webserver.dir/Timestamp.i

CMakeFiles/webserver.dir/Timestamp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/Timestamp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuqiao/Desktop/d/muduo_server/Timestamp.cc -o CMakeFiles/webserver.dir/Timestamp.s

CMakeFiles/webserver.dir/logger.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/logger.o: ../logger.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/webserver.dir/logger.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/logger.o -c /home/yuqiao/Desktop/d/muduo_server/logger.cc

CMakeFiles/webserver.dir/logger.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/logger.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuqiao/Desktop/d/muduo_server/logger.cc > CMakeFiles/webserver.dir/logger.i

CMakeFiles/webserver.dir/logger.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/logger.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuqiao/Desktop/d/muduo_server/logger.cc -o CMakeFiles/webserver.dir/logger.s

# Object files for target webserver
webserver_OBJECTS = \
"CMakeFiles/webserver.dir/Acceptor.o" \
"CMakeFiles/webserver.dir/Buffer.o" \
"CMakeFiles/webserver.dir/Channel.o" \
"CMakeFiles/webserver.dir/CurrentThread.o" \
"CMakeFiles/webserver.dir/DefaultPoller.o" \
"CMakeFiles/webserver.dir/EPollPoller.o" \
"CMakeFiles/webserver.dir/EventLoop.o" \
"CMakeFiles/webserver.dir/EventLoopThread.o" \
"CMakeFiles/webserver.dir/EventLoopThreadPool.o" \
"CMakeFiles/webserver.dir/InetAddress.o" \
"CMakeFiles/webserver.dir/Poller.o" \
"CMakeFiles/webserver.dir/Socket.o" \
"CMakeFiles/webserver.dir/TcpConnection.o" \
"CMakeFiles/webserver.dir/TcpServer.o" \
"CMakeFiles/webserver.dir/Thread.o" \
"CMakeFiles/webserver.dir/Timestamp.o" \
"CMakeFiles/webserver.dir/logger.o"

# External object files for target webserver
webserver_EXTERNAL_OBJECTS =

../lib/libwebserver.so: CMakeFiles/webserver.dir/Acceptor.o
../lib/libwebserver.so: CMakeFiles/webserver.dir/Buffer.o
../lib/libwebserver.so: CMakeFiles/webserver.dir/Channel.o
../lib/libwebserver.so: CMakeFiles/webserver.dir/CurrentThread.o
../lib/libwebserver.so: CMakeFiles/webserver.dir/DefaultPoller.o
../lib/libwebserver.so: CMakeFiles/webserver.dir/EPollPoller.o
../lib/libwebserver.so: CMakeFiles/webserver.dir/EventLoop.o
../lib/libwebserver.so: CMakeFiles/webserver.dir/EventLoopThread.o
../lib/libwebserver.so: CMakeFiles/webserver.dir/EventLoopThreadPool.o
../lib/libwebserver.so: CMakeFiles/webserver.dir/InetAddress.o
../lib/libwebserver.so: CMakeFiles/webserver.dir/Poller.o
../lib/libwebserver.so: CMakeFiles/webserver.dir/Socket.o
../lib/libwebserver.so: CMakeFiles/webserver.dir/TcpConnection.o
../lib/libwebserver.so: CMakeFiles/webserver.dir/TcpServer.o
../lib/libwebserver.so: CMakeFiles/webserver.dir/Thread.o
../lib/libwebserver.so: CMakeFiles/webserver.dir/Timestamp.o
../lib/libwebserver.so: CMakeFiles/webserver.dir/logger.o
../lib/libwebserver.so: CMakeFiles/webserver.dir/build.make
../lib/libwebserver.so: CMakeFiles/webserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Linking CXX shared library ../lib/libwebserver.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/webserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/webserver.dir/build: ../lib/libwebserver.so

.PHONY : CMakeFiles/webserver.dir/build

CMakeFiles/webserver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/webserver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/webserver.dir/clean

CMakeFiles/webserver.dir/depend:
	cd /home/yuqiao/Desktop/d/muduo_server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yuqiao/Desktop/d/muduo_server /home/yuqiao/Desktop/d/muduo_server /home/yuqiao/Desktop/d/muduo_server/build /home/yuqiao/Desktop/d/muduo_server/build /home/yuqiao/Desktop/d/muduo_server/build/CMakeFiles/webserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/webserver.dir/depend

