##
# @File: CMakeLists.txt
# @Brief 
# test下的目录文件
# 
# @Author Liu GuangRui
# @Email 675040625@qq.com
#

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR})

# catch要求打开异常
string(REGEX REPLACE "-fno-exceptions" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

set(TEST  testMain.cc net/AcceptorTest.cc net/ChannelTest.cc net/EventLoopTest.cc)

add_executable(test ${TEST})

add_executable(EchoServer EchoServer.cc)

target_link_libraries(EchoServer LIB_ECHOSERVER)
target_link_libraries(test LIB_ECHOSERVER)