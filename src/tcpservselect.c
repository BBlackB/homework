#include "unp.h"



int main(int argc, char const *argv[])
{
    int                 listenfd, connfd, sockfd;
    struct sockaddr_in  servaddr,cliaddr;
    socklen_t           clilen;
    fd_set              rset, allset;
    int                 i, maxfd, maxi, nready;
    ssize_t             n;
    char                buf[MAXLINE];
    int                 client[FD_SETSIZE];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family         = AF_INET;
    servaddr.sin_port           = htons(SERV_PORT);
    servaddr.sin_addr.s_addr    = htonl(INADDR_ANY);
    
    bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

    listen(listenfd, LISTENQ);

    maxfd = listenfd;
    maxi = -1;
    
    for(i = 0; i < FD_SETSIZE; i++) client[i] = -1;
    
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    while(1)
    {
        rset = allset; 
        nready = select(maxfd+1, &rset, NULL, NULL, NULL);


        if (nready <= 0)
        {
            printf("select error: nready <= 0\n");
            printf("maxfd = %d, maxi = %d, nready = %d\n", maxfd, maxi, nready);    
            exit(0);
        } 

        if (FD_ISSET(listenfd, &rset))
        {
            clilen = sizeof(cliaddr);
            connfd = accept(listenfd, (SA *)&cliaddr, &clilen);

            for (i = 0; i < FD_SETSIZE; i++)
                if (client[i] < 0) break;
            
            if (i == FD_SETSIZE)
            {
                printf("FD_SETSIZE error: too much client!\n");
                exit(0);
            }

            client[i] = connfd;
            if (connfd > maxfd) maxfd = connfd;
            if (i > maxi) maxi = i;

            FD_SET(connfd, &allset);


            if (--nready <= 0)
            {
                continue;
            } 
        }
        
        for (i = 0; i <= maxi; i++)
        {
            if (client[i] < 0) continue;
            sockfd = client[i];
            if (FD_ISSET(sockfd, &rset))
            {
                if ( (n = read(sockfd, buf, MAXLINE)) == 0)
                {
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                    close(sockfd);
                }
                else
                    writen(sockfd, buf, n);
             
               if (--nready <=0 )break;

            }
        }

        while(client[maxi] == -1) maxi--;
    }

    return 0;
}
