#ifndef __MYUNP_H__
#define __MYUNP_H__

#include    <stdio.h>
#include    <stdlib.h>
#include    <unistd.h>
#include    <string.h>
#include    <dirent.h>
#include    <fcntl.h>
#include    <errno.h>
#include    <arpa/inet.h>
#include    <sys/socket.h>
#include	<netinet/in.h>
#include    <sys/epoll.h>

#define SA struct sockaddr 
#define MAXLINE 4096
#define LISTENQ 1024
#define SERV_PORT 9877
#define MAX_EVENTS 1024

#endif // __MYUNP_H__
