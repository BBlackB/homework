#include "unp.h"

void my_str_echo(int sockfd)
{
	ssize_t n;
	char recvline[MAXLINE];

	while (1)
	{
		while( (n = read(sockfd, recvline, MAXLINE)) > 0)
		{
			writen(sockfd, recvline, n);		
		}
		if (n < 0 && errno == EINTR)	continue;
		else if(n < 0)	printf("my_str_echo: read error\n");
		else break;
	}
}

int main(int argc, char const *argv[])
{
	int connfd, listenfd;
	struct sockaddr_in cliaddr, servaddr;
	socklen_t len;
	pid_t childpid;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);

	bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
	listen(listenfd, LISTENQ);
	
	
	while(1){
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (SA *)&cliaddr, &len);

		if ((childpid = fork()) == 0)
		{
			close(listenfd);
			my_str_echo(connfd);
			exit(0);
		}
		close(connfd);
	}
		

	return 0;
}
