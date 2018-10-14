/*
 * @File: Channel.cc
 * @Brief
 * Channel类的实现
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#include "net/Channel.h"
#include "log/Log.h"

Channel::Channel(EventLoop *loop, int fd)
    : ploop_(loop)
    , fd_(fd)
    , event_(0)
    , revent_(0)
    , handleRead_(NULL)
    , handleWrite_(NULL)
    , ptcp_(NULL)
{
}

Channel::Channel(EventLoop *loop, int fd, TcpConnection *ptcp)
    : ploop_(loop)
    , fd_(fd)
    , event_(0)
    , revent_(0)
    , handleRead_(NULL)
    , handleWrite_(NULL)
    , ptcp_(ptcp)
{
}

Channel::~Channel()
{
    // 若被注册过，则需要删除事件
    if (event_) { delEvent(); }
}

u_int32_t Channel::getEvent() { return event_; }

void Channel::setEvent(uint32_t event) { event_ = event; }

void Channel::setRevent(uint32_t revent) { revent_ = revent; }

int Channel::getFd() { return fd_; }

void Channel::enableReading()
{
    event_ = EPOLLIN;
    update();
}

void Channel::enableWriting()
{
    event_ = EPOLLOUT;
    update();
}

bool Channel::isWriting() { return event_ & EPOLLOUT; }

void Channel::update() { ploop_->mod(this); }

void Channel::addReading()
{
    event_ = EPOLLIN;
    ploop_->add(this);
}

void Channel::delEvent() { ploop_->del(this); }

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
    LOG(LOG_DEBUG_LEVEL, "handle evnet called,\n");
    if (revent_ & EPOLLIN)
        handleRead_(ptcp_, fd_);
    else if (revent_ & EPOLLOUT)
        handleWrite_(ptcp_, fd_);
}
