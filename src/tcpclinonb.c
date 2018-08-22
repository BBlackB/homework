#include "unp.h"

void str_cli_nonblock(int sockfd)
{
    char    to[MAXLINE], fr[MAXLINE];
    char    *toiptr, *tooptr, *friptr, *froptr;
    fd_set  rset, wset;
    int     val, maxfdp1, stdeof, n, nwritten;

    stdeof = 0;

    val = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, val | O_NONBLOCK);
    val = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, val | O_NONBLOCK);
    val = fcntl(STDOUT_FILENO, F_GETFL, 0);
    fcntl(STDOUT_FILENO, F_SETFL, val | O_NONBLOCK);

    toiptr = tooptr = to;
    friptr = froptr = fr;

    maxfdp1 = max(max(STDIN_FILENO, STDOUT_FILENO), sockfd);

    while(1)
    {
        FD_ZERO(&rset);
        FD_ZERO(&wset);
        
        if (stdeof == 0 && toiptr < &to[MAXLINE])
            FD_SET(STDIN_FILENO, &rset);
        if (tooptr < toiptr)
            FD_SET(sockfd, &wset);
        if (friptr < &fr[MAXLINE])
            FD_SET(sockfd, &rset);
        if (froptr < friptr)
            FD_SET(STDOUT_FILENO, &wset);

        select(maxfdp1+1, &rset, &wset, NULL, NULL);

        if (FD_ISSET(STDIN_FILENO, &rset) && toiptr < &to[MAXLINE])
        {
            if ( (n = read(STDIN_FILENO, toiptr, &to[MAXLINE] - toiptr)) < 0)
            {
                if (errno != EWOULDBLOCK)
                {
                    printf("read STDIN error!\n");
                    exit(0);
                }
            }
            else if (n == 0)
            {
                stdeof = 1;
                if (toiptr == tooptr)
                    shutdown(sockfd, SHUT_WR);    
            }
            else
            {
                toiptr += n;
                FD_SET(sockfd, &wset);
            }
        }

        if (FD_ISSET(sockfd, &wset) && toiptr > tooptr)
        {
            nwritten = write(sockfd, tooptr, toiptr-tooptr);
            if (nwritten < 0)
            {
                if (errno != EWOULDBLOCK)
                {
                    printf("write sockfd error!\n");
                    exit(0);
                }
            }
            else
            {
                tooptr += nwritten;
                if (tooptr == toiptr)
                {
                    tooptr = toiptr = to;
                    if (stdeof)
                        shutdown(sockfd, SHUT_WR);
                }
            }
        }

        if (FD_ISSET(sockfd, &rset) && friptr < &fr[MAXLINE])
        {
            if ( (n = read(sockfd, friptr, &fr[MAXLINE] - friptr)) < 0)
            {
                if (errno != EWOULDBLOCK)
                {
                    printf("read sockfd error!\n");
                    exit(0);
                }
            }
            else if (n == 0)
            {
                //I don't kown what happened???
                if (stdeof)
                    return;
                else
                    printf("str_cli: server terminated prematurely!\n");
                    exit(0);
            }
            else
            {
                friptr += n;
                FD_SET(STDOUT_FILENO, &wset);
            }
        }

        if (FD_ISSET(STDOUT_FILENO, &wset) && friptr > froptr)
        {
            nwritten = write(STDOUT_FILENO, froptr, friptr-froptr);
            if (nwritten < 0)  //how about nwritten == 0??
            {
                if (errno != EWOULDBLOCK)
                {
                    printf("write STDOUT error!\n");
                    exit(0);
                }
            }
            else
            {
                froptr += nwritten;
                if (froptr == friptr)
                {
                    friptr = froptr = fr;
                }
            }
            
        }
    }// end of while
    
}


int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    if ( connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
    {
        printf("Connect error!\n");
        exit(0);
    }

    str_cli_nonblock(sockfd);

    return 0;
}
