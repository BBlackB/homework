/*
 * @File: channel.h
 * @Brief
 * 定义一个channel
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#ifndef __NET_CHANNEL_H__
#define __NET_CHANNEL_H__

#include "EchoServer/include/net/EventLoop.h"

using Handler = void (*)(TcpConnection *, int);

class Channel
{
  public:
  private:
    int sockfd_;
    EventLoop *ploop_;
    uint32_t event_;
    uint32_t revent_;
    Handler handleRead_;
    Handler handleWrite_;
    // 是否可以去掉？
    TcpConnection *ptcp_;

  private:
    void update();

  public:
    Channel(EventLoop *loop, int sockfd);
    Channel(EventLoop *loop, int sockfd, TcpConnection ptcp);
    // Channel(int sockfd);
    ~Channel();
    uint32_t getEvent();
    void setEvent(uint32_t event);
    void setRevent(uint32_t revent);
    int getSockfd();
    void enableReading();
    void enableWriting();
    void setReadHandler(Handler readHandler);
    void setWriteHandler(Handler writeHandler);
    void handleEvent();
};

Channel::Channel(EventLoop *loop, int sockfd)
    : ploop_(loop)
    , sockfd_(sockfd)
    , event_(0)
    , revent_(0)
    , handleRead_(NULL)
    , handleWrite_(NULL)
    , ptcp_(NULL)
{
}

Channel::Channel(EventLoop *loop, int sockfd, TcpConnection *ptcp)
    : ploop_(loop)
    , sockfd_(sockfd)
    , event_(0)
    , revent_(0)
    , handleRead_(NULL)
    , handleWrite_(NULL)
    , ptcp_(ptcp)
{
}

#endif // __NET_CHANNEL_H__