/*
 * @File: EventLoop.cc
 * @Brief
 * EventLoop类的实现
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#include <vector>
#include "net/EventLoop.h"
#include "log/Log.h"

int EventLoop::init() { return pEpoll_.init(); }

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

int EventLoop::add(Channel *pchannel) { return pEpoll_.add(pchannel); }

int EventLoop::mod(Channel *pchannel) { return pEpoll_.mod(pchannel); }

int EventLoop::del(Channel *pchannel) { return pEpoll_.del(pchannel); }
