/*
 * @File: TcpConnection.h
 * @Brief
 * 建立TCP连接
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#ifndef __NET_TCPCONNECTION_H__
#define __NET_TCPCONNECTION_H__

#include "Channel.h"
#include "Callback.h"
#include <iostream>
#include <string>

#define MAX_LINE 1024

// using Response = void (*)(TcpConnection *ptcp, char *message);

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
    std::string ibuf_; // 输入缓冲区
    std::string obuf_; // 输出缓冲区

  public:
    Response pResponse_;

  public:
    TcpConnection(EventLoop *ploop, int sockfd);
    ~TcpConnection();

    void init();
    void send(const std::string message);

    void setInputBuffer(std::string buf) { ibuf_ = buf; }
    void setOutputBuffer(std::string buf) { obuf_ = buf; }
    std::string getOutputBuffer() { return obuf_; }

    friend void handleRead(int);
    friend void handleWrite(int);

    void setResponse(Response pResponse);
};

#endif // __NET_TCPCONNECTION_H__