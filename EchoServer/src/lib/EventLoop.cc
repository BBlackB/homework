/*
 * @File: EventLoop.cc
 * @Brief
 * EventLoop类的实现
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#include "EchoServer/include/net/EventLoop.h"

void EventLoop::loop()
{
    while (true) {
        std::vector<Channel *> channels;
        pEpoll_.wait(channels);

        std::vector<Channel *>::iterator it;
        for (it = channels.begin(); it != channels.end(); ++it) {
            (*it)->handleEvent();
        }
    }
}

void EventLoop::add(Channel *pchannel) { pEpoll_.add(pchannel); }

void EventLoop::mod(Channel *pchannel) { pEpoll_.mod(pchannel); }

void EventLoop::del(Channel *pchannel) { pEpoll_.del(pchannel); }
