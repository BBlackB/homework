#
# @File: CMakeLists.txt
# @Brief 
# test下的CMakeLists.txt
# @Author Liu GuangRui
# @Email 675040625@qq.com
#

include_directories(${CMAKE_SOURCE_DIR}/include())

add_executable(EchoServer main.cc)
target_link_libraries(EchoServer LIB_ECHOSERVER)
