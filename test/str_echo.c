#include "unp.h"
#include "sum.h"

void str_echo(int sockfd)
{
    ssize_t n;
    struct args args;
    struct result result;
    while (1)
    {
        if ((n=Readn(sockfd, &args, sizeof(args))) == 0)
            return;
        result.sum = args.arg1 + args.arg2;
       // printf("%ld + %ld = %ld\n", args.arg1, args.arg2, result.sum);
        Writen(sockfd, &result, sizeof(result));
    }
}

void str_echo123(int sockfd)
{
    long arg1, arg2;
    ssize_t n;
    char line[MAXLINE];
    while (1)
    {
        if ((n = Readline(sockfd, line, MAXLINE)) == 0)
            return;
        if (sscanf(line, "%ld%ld", &arg1, &arg2) == 2)
            snprintf(line, sizeof(line), "%ld\n", arg1 + arg2);
        else
            snprintf(line, sizeof(line), "input error!\n");
        n = strlen(line);
        Writen(sockfd, line, n);
    }
}