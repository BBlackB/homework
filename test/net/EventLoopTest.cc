/*
 * @File: EpollTest.cc
 * @Brief
 * Epoll的单元测试
 *
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */
#include "catch2/catch.hpp"
#include "net/EventLoop.h"

TEST_CASE("net/EventLoop")
{
    EventLoop eloop;

    SECTION("init")
    {
        int ret = eloop.init();
        REQUIRE(ret == 0);
    }

    SECTION("Event")
    {
        Channel *pchannel = new Channel(&eloop, 10);

        pchannel->setEvent(EPOLLIN);
        int ret = eloop.add(pchannel);
        REQUIRE(ret == 0);

        Channel *pchan = new Channel(&eloop, 12);
        pchan->setEvent(EPOLLOUT);
        ret = eloop.mod(pchan);

        REQUIRE(ret == 0);
    }
}