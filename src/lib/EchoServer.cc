/*
 * @File: EchoServer.cc
 * @Brief
 * EchoServer类的实现
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */

#include <iostream>
#include "net/EchoServer.h"
#include "log/Log.h"

EchoServer::EchoServer(EventLoop *ploop)
    : ploop_(ploop)
    , pServer_(ploop)
{
}

EchoServer::~EchoServer() {}

void EchoServer::start()
{
    pServer_.start();
    pServer_.setResponse(onResponse);
}

void EchoServer::onResponse(TcpConnection *ptcp, const char *message)
{
    LOG(LOG_DEBUG_LEVEL, "EchoServer::onResponse called!\n");
    std::string str;
    ptcp->send(std::string(message));
}