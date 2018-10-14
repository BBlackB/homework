/*
 * @File: TcpServer.cc
 * @Brief
 * TcpServer类的实现
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#include "net/TcpServer.h"
#include "log/Log.h"

TcpServer *TcpServer::pthis_ = NULL;

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
    // 建立acceptor
    pAcceptor_ = new Acceptor(ploop_);
    pAcceptor_->setConnectionHandler(newConnetion);
    pAcceptor_->init();
}

void TcpServer::newConnetion(int sockfd)
{
    TcpConnection *ptcp = new TcpConnection(pthis_->ploop_, sockfd);
    ptcp->init(); // 初始化连接
    ptcp->pResponse_ = pthis_->getResponse();
    pthis_->tcpConnections_.push_back(ptcp); // 记录连接用于回收
}

void TcpServer::closeConnection(int sockfd)
{
    // TODO:
}

void TcpServer::onResponse(TcpConnection *pcap, const char *message)
{
    LOG(LOG_INFO_LEVEL, "receive the message: %s\n", message);
}
