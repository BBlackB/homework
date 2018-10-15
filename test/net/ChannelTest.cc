/*
 * @File: ChannelTest.cc
 * @Brief
 * Channel的单元测试
 *
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */
#include "catch2/catch.hpp"
#include "net/Channel.h"
#include "net/EventLoop.h"

TEST_CASE("net/Channel")
{
    EventLoop eloop;
    Channel channel(&eloop, 10);

    SECTION("Fd")
    {
        int fd = channel.getFd();
        REQUIRE(fd == 10);
    }

    SECTION("Event")
    {
        channel.setEvent(EPOLLIN);
        REQUIRE(channel.getEvent() == EPOLLIN);
    }

    SECTION("Reading/Writing")
    {
        channel.enableReading(true);
        REQUIRE(channel.isWriting() == true);
    }
}