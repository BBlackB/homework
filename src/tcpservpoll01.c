#include "unp.h"
#define OPEN_MAX 1024

int main(int argc, char const *argv[])
{
    int                 i, maxi, listenfd, connfd, n, nready;
    socklen_t           clilen;
    struct sockaddr_in  servaddr, cliaddr;
    struct pollfd       client[OPEN_MAX];
    char                buf[MAXLINE];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family         = AF_INET;
    servaddr.sin_port           = htons(SERV_PORT);
    servaddr.sin_addr.s_addr    = htonl(INADDR_ANY);

    bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    listen(listenfd, LISTENQ);

    maxi = 0;
    client[0].fd     = listenfd;
    client[0].events = POLLIN;
    for (i = 1; i < OPEN_MAX; i++) client[i].fd = -1;

    while(1)
    {
        nready = poll(client, maxi+1, INFTIM);

        if (client[0].revents & POLLIN)
        {
            clilen = sizeof(cliaddr);
            connfd = accept(listenfd, (SA *) &cliaddr, &clilen);

            for (i = 0; i < OPEN_MAX; i++)  if (client[i].fd < 0) break;

            if (i == OPEN_MAX)
            {
                printf("client error: too much clients!\n");
                exit(0);
            }

            if (i > maxi) maxi = i;

            client[i].fd = connfd;
            client[i].events = POLLIN;

            if (--nready <= 0) continue;

        }

        for (i = 1; i <= maxi; i++)
        {
            if (client[i].fd < 0)continue;
            if ( client[i].revents & POLLIN)
            {
                if ( (n = read(client[i].fd, buf, MAXLINE)) < 0)
                {
                    printf("read error!\n");
                    exit(0);
                }
                else if (n == 0)
                {
                    close(client[i].fd);
                    client[i].fd = -1;
                }
                else
                    write(client[i].fd, buf, n);

                if (--nready <= 0) break;
            }
        }
    }

    return 0;
}
