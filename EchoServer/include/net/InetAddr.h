/**
 * @file InetAddr.h
 * @brief
 * 封装IP和port信息
 * 
 * @author Liu GuangRui
 * @email 675040625@qq.com
*/
#ifndef __NET_INETADDR_H__
#define __NET_INETADDR_H__

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>

/**
 * @brief
 * 仅支持IPv4地址
*/
class InetAddr
{
  public:
    
  private:
    struct sockaddr_in serv_;
  public:
    InetAddr(unsigned port);    // for server
    InetAddr(const char *ip, unsigned int port);    // for client
    InetAddr(const std::string ip, unsigned int port);  // for client
    ~InetAddr();

    struct sockaddr_in getSockaddr();
};

InetAddr::InetAddr(unsigned port)
{
    bzero(&serv_, sizeof(serv_));
    serv_.sin_family        =   AF_INET;
    serv_.sin_port          =   htons(port);
    serv_.sin_addr.s_addr   =   htonl(INADDR_ANY);
}

InetAddr::InetAddr(const char *ip, unsigned port)
{
    bzero(&serv_, sizeof(serv_));
    serv_.sin_family        =   AF_INET;
    serv_.sin_port          =   htons(port);
    inet_pton(AF_INET, ip, &serv_.sin_addr.s_addr);
}

InetAddr::InetAddr(const std::string ip, unsigned port)
{
    bzero(&serv_, sizeof(serv_));
    serv_.sin_family        =   AF_INET;
    serv_.sin_port          =   htons(port);
    inet_pton(AF_INET, ip.c_str(), &serv_.sin_addr.s_addr);
}


InetAddr::~InetAddr()
{
}

struct sockaddr_in InetAddr::getSockaddr()
{
    return serv_;
}


#endif // __NET_INETADDR_H__