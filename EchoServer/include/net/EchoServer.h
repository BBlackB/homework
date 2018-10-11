/*
 * @File: EchoServer.h
 * @Brief
 * 回射服务器
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */
#ifndef __NET_ECHOSERVER_H__
#define __NET_ECHOSERVER_H__

#include "TcpServer.h"

class EchoServer
{
  private:
    EventLoop *ploop_;
    TcpServer pServer_;

  public:
    EchoServer(EventLoop *ploop);
    ~EchoServer();
    void start();
    static void onResponse(TcpConnection *ptcp, char *message);
};

#endif // __NET_ECHOSERVER_H__