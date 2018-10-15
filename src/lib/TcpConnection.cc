/*
 * @File: TcpConnection.cc
 * @Brief
 * TcpConnection类的实现
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <string>
#include <errno.h>
#include "net/TcpConnection.h"
#include "net/Channel.h"
#include "log/Log.h"

void handleRead(TcpConnection *ptcp, int sockfd);
void handleWrite(TcpConnection *ptcp, int sockfd);

TcpConnection::TcpConnection(EventLoop *ploop, int sockfd)
    : sockfd_(sockfd)
    , ploop_(ploop)
{}

TcpConnection::~TcpConnection() { delete pchannel_; }

void TcpConnection::init()
{
    pchannel_ = new Channel(ploop_, sockfd_, this);
    pchannel_->setReadHandler(handleRead);
    pchannel_->setWriteHandler(handleWrite);
    pchannel_->addReading();
}

void TcpConnection::setResponse(Response pResponse) { pResponse_ = pResponse; }

int TcpConnection::send(const std::string message)
{
    int nwritten = 0;
    if (obuf_.empty()) {
        nwritten = ::write(sockfd_, message.c_str(), message.size());
        if (nwritten < 0) {
            LOG(LOG_ERROR_LEVEL, "TcpConnection::send write\n");
            return errno;
        }
    }

    if (nwritten < static_cast<int>(message.size())) {
        obuf_ += message.substr(nwritten, message.size());
        if (!pchannel_->isWriting()) pchannel_->enableWriting(true);
    }
    return 0;
}

// @bug:没有断开连接操作
void handleRead(TcpConnection *ptcp, int sockfd)
{
    int nread;
    std::string ibuf;
    char buf[MAX_LINE];

    printf("TcpConnection handleRead called!\n");

    while (1) {
        nread = ::read(sockfd, buf, MAX_LINE);
        if (nread == -1) {
            if (errno == EWOULDBLOCK) {
                printf("errno == EWOULDBLOCK, break\n");
                break;
            }
        } else if (nread == 0) {
            // 关闭连接
            ::close(sockfd);
            break;
        } else {
            ibuf.append(buf, nread);
        }
    }

    if (ibuf.size()) {
        ptcp->pResponse_(ptcp, ibuf.c_str());
        ptcp->setInputBuffer(ibuf);
        LOG(LOG_INFO_LEVEL, "Read message: %s\n", ibuf.c_str());
    }
}

void handleWrite(TcpConnection *ptcp, int sockfd)
{
    int nwritten;
    std::string obuf;
    printf("TcpConnection handleWrite called\n");
    obuf = ptcp->getOutputBuffer();
    while (1) {
        nwritten = ::write(sockfd, obuf.c_str(), obuf.size());
        if (nwritten == -1) {
            if (errno == EWOULDBLOCK) break;
            LOG(LOG_ERROR_LEVEL, "TcpConnection handleWrite nwritten==-1\n");
        } else if (nwritten == 0) {
            break;
        } else {
            obuf = obuf.substr(nwritten, obuf.size());
        }
    }
}
