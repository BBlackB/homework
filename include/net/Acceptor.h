/*
 * @File: Acceptor.h
 * @Brief
 * 接受连接
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */
#ifndef __NET_ACCEPTOR_H__
#define __NET_ACCEPTOR_H__

#include "Channel.h"
#include "EventLoop.h"
#include "TcpConnection.h"
#include "Callback.h"

// using ConnHandler = void (*)(int);

/**
 * @brief
 * 用于接受连接
 */
class Acceptor
{
  private:
    int listenfd_;              // 保存监听套接字
    Channel *pacceptorchannel_; // acceptor的channel
    EventLoop *ploop_;
    ConnHandler handleConnection_; // 处理连接的函数指针
    // 危险！！！ 只能被实例化一次
    static Acceptor *pthis_; // 静态指针指向自己，实现对非静态变量的访问。

  public:
    Acceptor(EventLoop *ploop);
    void init();
    void setConnectionHandler(ConnHandler connectionHandler);
    static void handleEvent(TcpConnection *pcap, int socket);

  private:
    int createAndListen();
};

#endif //__NET_ACCEPTOR_H__