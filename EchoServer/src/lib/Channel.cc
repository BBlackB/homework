/*
 * @File: Channel.cc
 * @Brief
 * Channel类的实现
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#include "EchoServer/include/net/Channel.h"

u_int32_t Channel::getEvent() { return event_; }

void Channel::setEvent(uint32_t event) { event_ = event; }

void Channel::setRevent(uint32_t revent) { revent_ = revent; }

int Channel::getSockfd() { return sockfd_; }

void Channel::enableReading()
{
    revent_ = EPOLLIN;
    update();
}

void Channel::enableWriting()
{
    revent_ = EPOLLOUT;
    update();
}

void Channel::update() { ploop_->mod(this); }

// 设置read回调函数
void Channel::setReadHandler(Handler readHandler) { handleRead_ = readHandler; }

// 设置write回调函数
void Channel::setWriteHandler(Handler writeHandler)
{
    handleWrite_ = writeHandler;
}

// 使用回调函数
void Channel::handleEvent()
{
    if (revent_ & EPOLLIN)
        handleRead_(ptcp_, sockfd_);
    else if (revent_ & EPOLLOUT)
        handleWrite_(ptcp_, sockfd_);
}
