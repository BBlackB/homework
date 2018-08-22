#include "unp.h"


void str_cli_select(FILE *fp, int sockfd)
{
    int maxfdp1, n;
    char recvline[MAXLINE], sendline[MAXLINE];
    fd_set rset;
    int stdineof = 0;

    // char tmp1[] = "this is send to stdin\n";
    // char tmp2[] = "this is send to stdout\n";

    FD_ZERO(&rset);

    // write(fileno(stdin), tmp1, strlen(tmp1));
    // write(fileno(stdout), tmp2, strlen(tmp2));

    // printf("fileno(fp) = %d\n", fileno(fp));
    // printf("sockfd = %d\n", sockfd);
    while(1)
    {
        if (stdineof == 0)
            FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        select(maxfdp1, &rset, NULL, NULL, NULL);

        //printf("stdineof = %d\n", stdineof);

        if (FD_ISSET(fileno(fp), &rset))
        {
           // printf("**************fp rset*************\n");
            if ( (n = read(fileno(fp), sendline, MAXLINE)) == 0)
            {
                stdineof = 1;
                shutdown(sockfd, SHUT_WR);
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            else if(n < 0)
                printf("have a error\n");
            writen(sockfd, sendline, n);
        }

        if (FD_ISSET(sockfd, &rset))
        {
            //printf("**************sockfd rset*************\n");
            if ( (n = read(sockfd, recvline, MAXLINE)) == 0)
            {
                if ( stdineof == 1) return;
                else
                {
                    printf("str_cli_select:read error\n");
                    exit(0);
                }
            }
            //printf("In sockfd: n = %d\n", n);
            writen(fileno(stdout), recvline, n);
        }
    }
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

    connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

    str_cli_select(stdin, sockfd);
    
    return 0;
}
