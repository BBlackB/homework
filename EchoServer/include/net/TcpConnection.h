/*
 * @File: TcpConnection.h
 * @Brief
 * 建立TCP连接
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#ifndef __NET_TCPCONNECTION_H__
#define __NET_TCPCONNECTION_H__

#include <iostream>
#include <unistd.h>
#include <string>
#include <string.h>
#include "Channel.h"

#define MAX_LINE 1024

using Response = void (*)(TcpConnection *ptcp, char *message);
/**
 * @brief
 * 建立TCP连接的类
 */
class TcpConnection
{
  private:
    int sockfd_;
    Channel *pchannel_;
    EventLoop *ploop_;

  public:
    Response pResponse_;

  public:
    TcpConnection(EventLoop *ploop, int sockfd);
    ~TcpConnection();
    void start();
    void send(const std::string message);
    friend void handleRead(int);
    friend void handleWrite(int);

  private:
    void setResponse(Response pResponse);
};

#endif // __NET_TCPCONNECTION_H__