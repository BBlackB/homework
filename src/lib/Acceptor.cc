/*
 * @File: Acceptor.cc
 * @Brief
 * Acceptor类的实现
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include "log/Log.h"
#include "net/Acceptor.h"

Acceptor *Acceptor::pthis_ = NULL;

Acceptor::Acceptor(EventLoop *ploop)
    : listenfd_(-1)
    , pacceptorchannel_(NULL)
    , ploop_(ploop)
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

void Acceptor::init()
{
    listenfd_ = createAndListen();
    pacceptorchannel_ = new Channel(ploop_, listenfd_);
    pacceptorchannel_->setReadHandler(handleEvent);
    pacceptorchannel_->addReading();
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

    LOG(LOG_DEBUG_LEVEL, "Acceptor::handleEvent called!\n");

    while (1) {
        connfd = accept(sockfd, (sockaddr *) &cliaddr, &clilen);
        if (connfd < 0) {
            if ((errno = EWOULDBLOCK) || (errno == EINTR)) break;
            if ((errno == ECONNABORTED) || (errno == EPROTO)) continue;
            LOG(LOG_ERROR_LEVEL, "Acceptor::handleEvent accept\n");
        }
        LOG(LOG_INFO_LEVEL,
            "new connection from [%s:%d] new socket fd: %d\n",
            inet_ntoa(cliaddr.sin_addr),
            ntohs(cliaddr.sin_port),
            connfd);

        fcntl(connfd, F_SETFL, O_NONBLOCK); // 设置非阻塞
        // 创建一个新的连接
        pthis_->handleConnection_(connfd);
    }
}