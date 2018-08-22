#include "unp.h"
#include <pthread.h>


struct copyto_t
{
    int fd;
    FILE *fp;
};

void *_copyto(void *arg)
{
    char recvline[MAXLINE];
    struct copyto_t *carg;
    carg = (struct copyto_t *)arg;
    int nread;

    while ( (nread = read(fileno(carg->fp), recvline, MAXLINE)) > 0)
    {
        write(carg->fd, recvline, nread);
    }
    shutdown(carg->fd, SHUT_WR);

    return NULL;
}


void str_cli_thread(FILE* fp_arg, int sockfd)
{
    struct copyto_t arg;
    arg.fd = sockfd;
    arg.fp = fp_arg;
    pthread_t tid;
    char sendline[MAXLINE];
    int nread;

    pthread_create(&tid, NULL, _copyto, &arg);

    while((nread = read(sockfd, sendline, MAXLINE)))
    {        
        write(fileno(stdout), sendline, nread);
    }

    return ;
}

int main(int argc, char const *argv[])
{
    struct sockaddr_in servaddr;
    int sockfd;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    if ( connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
    {
        printf("connect error!\n");
        exit(0);
    }

    str_cli_thread(stdin, sockfd);

    return 0;
}
