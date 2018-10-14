/*
 * @File: channel.h
 * @Brief
 * 定义一个channel
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#ifndef __NET_CHANNEL_H__
#define __NET_CHANNEL_H__

#include "EventLoop.h"
#include "TcpConnection.h"
#include "Callback.h"

// using Handler = void (*)(TcpConnection *, int);

class Channel
{
  public:
  private:
    EventLoop *ploop_;
    int fd_;
    uint32_t event_;
    uint32_t revent_;
    Handler handleRead_;
    Handler handleWrite_;
    // 是否可以去掉？
    TcpConnection *ptcp_;

  private:
    void update();
    void delEvent();

  public:
    Channel(EventLoop *loop, int fd);
    Channel(EventLoop *loop, int fd, TcpConnection *ptcp);
    ~Channel();

    uint32_t getEvent();
    void setEvent(uint32_t event);
    void setRevent(uint32_t revent);
    int getFd();

    void enableReading();
    void enableWriting();
    bool isWriting();

    void setReadHandler(Handler readHandler);
    void setWriteHandler(Handler writeHandler);

    void addReading();
    void handleEvent();
};

#endif // __NET_CHANNEL_H__