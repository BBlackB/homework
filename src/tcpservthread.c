#include "unp.h"
#include <pthread.h>

void str_echo_(int sockfd)
{
    char buf[MAXLINE];
    int nread;

again:
    while ( (nread = read(sockfd, buf, MAXLINE)) > 0)
    {
        write(sockfd, buf, nread);
    }

    if (nread <0 && errno == EINTR) goto again;
    printf("str_echo_: read error!\n");
}

void *doit(void *arg)
{
    int connfd = (int)arg;
    
    pthread_detach(pthread_self()); //主线程不必等待子线程的返回（不必调用pthread_join）

    str_echo_(connfd);
    close(connfd);
    return NULL;
}

int main(int argc, char const *argv[])
{
    int listenfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clilen;
    pthread_t tid;

    listenfd = socket(AF_INET, SOCK_STREAM,0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

    listen(listenfd, LISTENQ);

    while (1)
    {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (SA *) &cliaddr, &clilen);
        pthread_create(&tid, NULL, doit, (void *)connfd);   //safe or not?
    }
    return 0;
}
