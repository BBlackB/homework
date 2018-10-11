##
# @File: CMakeLists.txt
# @Brief 
# src/lib目录的CMakeLists.txt
# @Author Liu GuangRui
# @Email 675040625@qq.com
#

include_directories(${CMAKE_SOURCE_DIR}/include)

set(LIB_ECHOSERVER_SRC Channel.cc EchoServer.cc Epoll.cc EventLoop.cc Log.cc TcpConnection.cc TcpServer.cc)
add_library(LIB_ECHOSERVER ${LIB_ECHOSERVER_SRC})
