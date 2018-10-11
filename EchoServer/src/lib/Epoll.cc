/*
 * @File: Epoll.cc
 * @Brief
 * Epoll类的实现
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#include "EchoServer/include/net/Channel.h"

Epoll::Epoll(bool bEt = true)
    : bEt_(bEt)
{
}

int Epoll::init()
{
    epfd_ = epoll_create(1024);
    if (epfd_ < 0) LOG(LOG_ERROR_LEVEL, "Epoll::init epoll_create\n");
}

void Epoll::add(Channel *pChannel)
{
    struct epoll_event ev;
    ev.data.ptr = pChannel;
    ev.events = pChannel->getEvent;
    if (bEt_) ev.events |= EPOLLET;
    ::epoll_ctl(epfd_, EPOLL_CTL_ADD, pChannel->getSockfd(), &ev);
}

void Epoll::del(Channel *pChannel)
{
    struct epoll_event ev;
    ::epoll_ctl(epfd_, EPOLL_CTL_DEL, pChannel->getSockfd(), &ev);
}

void Epoll::mod(Channel *pChannel)
{
    struct epoll_event ev;
    ev.data.ptr = pChannel;
    ev.events = pChannel->getEvent;
    if (bEt_) ev.events |= EPOLLET;
    ::epoll_ctl(epfd_, EPOLL_CTL_MOD, pChannel->getSockfd(), &ev);
}

void Epoll::wait(std::vector<Channel *> &channels)
{
    int res = ::epoll_wait(epfd_, events_, MAX_EVENTS, -1);

    if (res < 0) LOG(LOG_ERROR_LEVEL, "Epoll::wait epoll_wait\n");

    for (int i = 0; i < res; ++i) {
        Channel *pchannel = static_cast<Channel *>(events_[i].data.ptr);
        pchannel->setRevent(events_[i].events);
        channels.push_back(pchannel);
    }
}
