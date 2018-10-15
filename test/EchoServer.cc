/*
 * @File: EchoServer.cc
 * @Brief
 * 测试EchoServer
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#include "net/EchoServer.h"
#include "net/EventLoop.h"
#include "log/Log.h"

int main()
{
    EventLoop eloop;
    eloop.init();
    EchoServer echoserv(&eloop);
    echoserv.start();
    LOG(LOG_DEBUG_LEVEL, "Begin to loop\n");
    eloop.loop();
    return 0;
}