##
# @File: CMakeLists.txt
# @Brief 
# src/lib目录的CMakeLists.txt
# @Author Liu GuangRui
# @Email 675040625@qq.com
#

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR})

set(LIB_ECHOSERVER_SRC Acceptor.cc Channel.cc EchoServer.cc Epoll.cc EventLoop.cc Log.cc TcpConnection.cc TcpServer.cc)
add_library(LIB_ECHOSERVER ${LIB_ECHOSERVER_SRC})
