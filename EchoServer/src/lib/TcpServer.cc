/*
 * @File: TcpServer.cc
 * @Brief
 * TcpServer类的实现
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#include "EchoServer/include/net/TcpServer.h"

TcpServer::TcpServer(EventLoop *ploop)
    : ploop_(ploop)
    , response_(onResponse)
{
    pthis_ = this;
}

TcpServer::~TcpServer()
{
    delete pAcceptor_;
    for (auto it = tcpConnections_.begin(); it != tcpConnections_.end(); ++it)
        delete *it;
}

void TcpServer::start()
{
    pAcceptor_ = new Acceptor(ploop_);
    pAcceptor_->setConnectionHandler(newConnetion);
    pAcceptor_->start();
}

void TcpServer::newConnetion(int sockfd)
{
    TcpConnection *tcp = new TcpConnection(pthis_->ploop_, sockfd);
    pthis_->tcpConnections_.push_back(tcp);
}

void TcpServer::onResponse(TcpConnection *pcap, char *message)
{
    LOG(LOG_INFO_LEVEL, "receive the message: %s\n", message);
}

void TcpServer::setResponse(Response response) { response_ = response; }
