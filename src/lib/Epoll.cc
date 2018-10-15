/*
 * @File: Epoll.cc
 * @Brief
 * Epoll类的实现
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#include "net/Channel.h"
#include "log/Log.h"

Epoll::Epoll(bool bEt)
    : bEt_(bEt)
{}

int Epoll::init()
{
    epfd_ = epoll_create(1024);
    if (epfd_ < 0) {
        LOG(LOG_ERROR_LEVEL, "Epoll::init epoll_create\n");
        return -1;
    }
    return 0;
}

int Epoll::add(Channel *pChannel)
{
    struct epoll_event ev;
    ev.data.ptr = pChannel;
    ev.events = pChannel->getEvent();
    if (bEt_) ev.events |= EPOLLET;
    if (pChannel->getFd() < 0) return -1;
    ::epoll_ctl(epfd_, EPOLL_CTL_ADD, pChannel->getFd(), &ev);
    return 0;
}

int Epoll::del(Channel *pChannel)
{
    struct epoll_event ev;
    if (pChannel->getFd() < 0) return -1;
    ::epoll_ctl(epfd_, EPOLL_CTL_DEL, pChannel->getFd(), &ev);
    return 0;
}

int Epoll::mod(Channel *pChannel)
{
    struct epoll_event ev;
    ev.data.ptr = pChannel;
    ev.events = pChannel->getEvent();
    if (bEt_) ev.events |= EPOLLET;
    if (pChannel->getFd() < 0) return -1;
    ::epoll_ctl(epfd_, EPOLL_CTL_MOD, pChannel->getFd(), &ev);
    return 0;
}

void Epoll::wait(std::vector<Channel *> &channels)
{
    int res = ::epoll_wait(epfd_, events_, MAX_EVENTS, -1);

    LOG(LOG_DEBUG_LEVEL, "epfd = %d, res = %d\n", epfd_, res);
    if (res < 0) { LOG(LOG_ERROR_LEVEL, "Epoll::wait epoll_wait\n"); }

    for (int i = 0; i < res; ++i) {
        Channel *pchannel = static_cast<Channel *>(events_[i].data.ptr);
        pchannel->setRevent(events_[i].events);
        channels.push_back(pchannel);
    }
}
