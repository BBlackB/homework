include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR})

add_executable(EchoServer main.cc)

target_link_libraries(EchoServer LIB_ECHOSERVER)