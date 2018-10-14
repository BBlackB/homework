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
    void init();
    void loop();
    void mod(Channel *pchannel);
    void add(Channel *pchannel);
    void del(Channel *pchannel);
};

#endif // __NET_EVENT_LOOP_H__