/*
 * @File: EventLoop.h
 * @Brief
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#ifndef __NET_EVENT_LOOP_H__
#define __NET_EVENT_LOOP_H__

#include "Epoll_.h"

class EventLoop
{
  private:
    Epoll pEpoll_;

  public:
    // EventLoop();
    // ~EventLoop();
    int init();
    void loop();
    int mod(Channel *pchannel);
    int add(Channel *pchannel);
    int del(Channel *pchannel);
};

#endif // __NET_EVENT_LOOP_H__