/*
 * @File: TcpServer.h
 * @Brief
 * 封装TcpServer类
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */
#ifndef __NET_TCPSERVER_H__
#define __NET_TCPSERVER_H__

#include <vector>
#include "Acceptor.h"
#include "TcpConnection.h"

/**
 * @brief
 * 封装TcpServer
 */
class TcpServer
{
  private:
    EventLoop *ploop_;
    Acceptor *pAcceptor_;
    std::vector<TcpConnection *> tcpConnections_;
    // 危险！！！只能被实例化一次
    static TcpServer *pthis_; // 静态指针指向自己，实现访问非静态变量。
    Response response_;

  public:
    TcpServer(EventLoop *ploop);
    ~TcpServer();

    void start();

    void setResponse(Response response) { response_ = response; }
    Response getResponse() { return response_; }

    static void newConnetion(int sockfd);
    void closeConnection(int sockfd);
    static void onResponse(TcpConnection *pcap, const char *massage);
};

#endif // __NET_TCPSERVER_H__