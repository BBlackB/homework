/*
 * @File: AcceptorTest.cc
 * @Brief
 * Acceptor单元测试
 *
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#include "catch2/catch.hpp"
#include "net/Acceptor.h"
#include "net/EventLoop.h"

void func(int sockfd) {}

TEST_CASE("net/Acceptor")
{
    EventLoop eloop;
    Acceptor acceptor(&eloop);
    SECTION("init")
    {
        int ret = acceptor.init();
        REQUIRE(ret == 0);
    }

    SECTION("setConnectionHandler")
    {
        int ret = acceptor.setConnectionHandler(NULL);
        REQUIRE(ret == -1);

        ret = acceptor.setConnectionHandler(func);
        REQUIRE(ret == 0);
    }
}