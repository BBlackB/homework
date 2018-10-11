/**
 * @file Epoll.h
 * @brief
 * 封装epoll
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */
#ifndef __NET_EPOLL_H__
#define __NET_EPOLL_H__

#include <sys/epoll.h>
#include <vector>
#include "../utils/Log.h"
#include "Channel.h"

#define MAX_EVENTS 1024

class Channel;

/**
 * @brief
 * 封装epoll
 */
class Epoll
{
  private:
    int epfd_;
    bool bEt_; // 是否使用ET模式
    struct epoll_event events_[MAX_EVENTS];

  public:
    Epoll(bool bEt = true);
    ~Epoll();
    int init();                  // 初始化epfd
    void add(Channel *pChannel); // 添加事件
    void del(Channel *pChannel); // 删除事件
    void mod(Channel *pChannel); // 修改事件
    void wait(std::vector<Channel *> &channels);
};

#endif // __NET_EPOLL_H__