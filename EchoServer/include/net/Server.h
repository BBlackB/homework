/**
 * @file Server.h
 * @brief
 * 封装server
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#ifndef __NET_SERVER_H__
#define __NET_SERVER_H__

#include <sys/socket.h>
#include <fcntl.h>
#include "EchoServer/include/net/InetAddr.h"

#define LISTENQ 1024 // 设置最大监听数

/**
 * @brief
 * 封装server
 */
class Server
{
  private:
    InetAddr inetaddr_;
    int listenfd_;

  public:
    Server(unsigned int port);
    ~Server();

  private:
    void setNonblock();
};

Server::Server(unsigned int port)
    : inetaddr_(port)
{
}

Server::~Server() {}

void Server::setNonblock()
{
    int val;
    val = fcntl(listenfd_, F_GETFL);
    if (val < 0) LOG(LOG_ERROR_LEVEL, "Server::setnonblock fcntl:GET\n");

    if (fcntl(listenfd_, F_SETFL, val | O_NONBLOCK) < 0)
        LOG(LOG_ERROR_LEVEL, "Server::setnonblock fcntl:SET\n");
}

#endif // __NET_SERVER_H__