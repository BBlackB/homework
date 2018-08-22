#include "unp.h"

void str_cli_select(FILE *fp, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];
    int maxfdp1;
    fd_set rset;

    FD_ZERO(&rset);
    while(1)
    {
        FD_SET(sockfd, &rset);
        FD_SET(fileno(fp), &rset);
        maxfdp1 = max(sockfd, fileno(fp)) + 1;
        select(maxfdp1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(fileno(fp), &rset))
        {
            if ( fgets(sendline, MAXLINE, fp) == NULL)
            {
                return; 
            }
            writen(sockfd, sendline, strlen(sendline));
        }
        
        if (FD_ISSET(sockfd, &rset))
        {
            if ( readline(sockfd, recvline, MAXLINE) == 0)
            {
                printf("str_cli_select: read error\n");
                exit(0);
            }
            //writen(fileno(stdout), recvline, strlen(recvline));
            fputs(recvline, stdout);
        }
    }
}

int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

    str_cli_select(stdin,sockfd);

    return 0;
}
