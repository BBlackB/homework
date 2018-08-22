#include "unp.h"

void sig_chld(int signo)
{
    pid_t pid;
    int stat;

    while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
        printf("child %d terminated\n", pid);
    }

    return;
}

void str_echo(int sockfd)
{
    char buf[MAXLINE];
    int n;
    
    while(1){
        while( (n = read(sockfd, buf, MAXLINE)) > 0){
                write(sockfd, buf, n);
        }
        if (n < 0 && errno == EINTR)
            continue;
        else if (n < 0)
        {
            printf("read error\n");
            exit(0);
        }
        else break;
    }
}

int main(int argc, char const *argv[])
{
    int listenfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    pid_t pid;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    listen(listenfd, LISTENQ);

    signal(SIGCHLD, sig_chld);

    while (1)
    {
        len = sizeof(cliaddr);
        if ( (connfd = accept(listenfd, (SA *)&cliaddr, &len)) < 0)
        {
            if (errno == EINTR)
                continue;
            else
            {
                printf("accept error\n");
                exit(0);
            }
        }

        if ( (pid = fork()) == 0)
        {
            close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        close(connfd);
    }

    return 0;
}
