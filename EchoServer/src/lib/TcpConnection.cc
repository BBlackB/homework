/*
 * @File: TcpConnection.cc
 * @Brief
 * TcpConnection类的实现
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#include "EchoServer/include/net/TcpConnection.h"

std::string *ibuf; // 输入缓冲区
std::string *obuf; // 输出缓冲区

TcpConnection::TcpConnection(EventLoop *ploop, int sockfd)
    : ploop_(ploop)
    , sockfd_(sockfd)
{
}

TcpConnection::~TcpConnection() { delete pchannel_; }

void TcpConnection::start()
{
    pchannel_ = new Channel(ploop_, sockfd_);
    pchannel_->setReadHandler(handleRead);
    pchannel_->setWriteHandler(handleWrite);
}

void TcpConnection::setResponse(Response pResponse) { pResponse_ = pResponse; }

void TcpConnection::send(const std::string message)
{
    int nwritten = 0;
    if (obuf->empty()) {
        nwritten = ::write(sockfd_, message.c_str(), message.size());
        if (nwritten < 0) {
            LOG(LOG_ERROR_LEVEL, "TcpConnection::send write\n");
        }
    }

    if (nwritten < message.size()) {
        *obuf += message.substr(nwritten, message.size());
    }
}

void handleRead(TcpConnection *pcap, int sockfd)
{
    int nread;
    char buf[MAX_LINE];
    while (1) {
        nread = ::read(sockfd, buf, MAX_LINE);
        if (nread == -1) {
            if (errno == EWOULDBLOCK) break;
            LOG(LOG_ERROR_LEVEL, "TcpConnection handleRead nread==-1\n");
        } else if (nread == 0) {
            ::close(sockfd);
        } else {
            ibuf->append(buf, strlen(buf));
        }
    }
    pcap->pResponse_(pcap, ibuf.c_str());
}

void handleWrite(TcpConnection *pcap, int sockfd)
{
    int nwritten;
    while (1) {
        nwritten = ::write(sockfd, obuf->c_str(), obuf->size());
        if (nwritten == -1) {
            if (errno == EWOULDBLOCK) break;
            LOG(LOG_ERROR_LEVEL, "TcpConnection handleWrite nwritten==-1\n");
        } else if (nwritten == 0) {
            break;
        } else {
            *obuf = obuf->substr(nwritten, obuf->size());
        }
    }
}
