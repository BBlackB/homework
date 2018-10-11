/*
 * @File: EchoServer.cc
 * @Brief
 * EchoServer类的实现
 * @Author Liu GuangRui
 * @Email 675040625@qq.com
 */
#include <iostream>
#include "EchoServer/include/net/EchoServer.h"

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

void EchoServer::onResponse(TcpConnection *ptcp, char *message)
{
    std::string str;
    ptcp->send(std::string(message));
}