/*
 * @File: Acceptor.h
 * @Brief
 * 接受连接
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */
#ifndef __NET_ACCEPTOR_H__
#define __NET_ACCEPTOR_H__

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include "../utils/Log.h"
#include "Channel.h"
#include "EventLoop.h"
#include "TcpConnection.h"

using ConnHandler = void (*)(int);

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
    void start();
    void setConnectionHandler(ConnHandler connectionHandler);
    static void handleEvent(TcpConnection *pcap, int socket);

  private:
    int createAndListen();
};

Acceptor::Acceptor(EventLoop *ploop)
    : ploop_(ploop)
    , listenfd_(-1)
    , pacceptorchannel_(NULL)
{
    pthis_ = this;
}

int Acceptor::createAndListen()
{
    struct sockaddr_in servaddr;

    listenfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd_ < 0)
        LOG(LOG_ERROR_LEVEL, "Acceptor::createAndListen socket\n");

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9877); // 监听端口默认9877
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    fcntl(listenfd_, F_SETFL, O_NONBLOCK); // 设置非阻塞

    if (-1 == bind(listenfd_, (struct sockaddr *) &servaddr, sizeof(servaddr)))
        LOG(LOG_ERROR_LEVEL, "Acceptor::createAndListen bind\n");

    if (-1 == listen(listenfd_, 1024)) // 最大监听数默认1024
        LOG(LOG_ERROR_LEVEL, "Acceptor::createAndListen listen\n");

    return listenfd_;
}

void Acceptor::start()
{
    listenfd_ = createAndListen();
    pacceptorchannel_ = new Channel(ploop_, listenfd_);
    pacceptorchannel_->setReadHandler(handleEvent);
}

// 设置connection回调函数
void Acceptor::setConnectionHandler(ConnHandler connectionHandler)
{
    handleConnection_ = connectionHandler;
}

void Acceptor::handleEvent(TcpConnection *pcap, int sockfd)
{
    int connfd;
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(struct sockaddr_in);

    while (1) {
        connfd = accept(sockfd, (sockaddr *) &cliaddr, &clilen);
        if (connfd < 0) {
            if (errno = EWOULDBLOCK || errno == EINTR) break;
            if (errno == ECONNABORTED || errno == EPROTO) continue;
            LOG(LOG_ERROR_LEVEL, "Acceptor::handleEvent accept\n");
        }
        LOG(LOG_INFO_LEVEL,
            "new connection from [%s:%d] new socket fd: %d\n",
            inet_ntoa(cliaddr.sin_addr),
            ntohs(cliaddr.sin_port),
            connfd);
        fcntl(connfd, F_SETFL, O_NONBLOCK); // 设置非阻塞
        // TODO: newConnection
        pthis_->handleConnection_(connfd);
    }
}

#endif //__NET_ACCEPTOR_H__