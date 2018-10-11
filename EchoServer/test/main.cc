/*
 * @File: main.cc
 * @Brief
 * 测试EchoServer
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#include "EchoServer/include/net/EchoServer.h"
#include "EchoServer/include/net/EventLoop.h"

int main()
{
    EventLoop eloop;
    EchoServer echoserv(&eloop);
    echoserv.start();
    return 0;
}