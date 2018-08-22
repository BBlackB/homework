//tcp client
#include "unp.h"

void my_str_cli(FILE *fp, int sockfd)
{
	char sendline[MAXLINE], recvline[MAXLINE];

	
	while((fgets(sendline, MAXLINE, fp) != NULL)){
		writen(sockfd, sendline, strlen(sendline));

		
		if (readline(sockfd, recvline, MAXLINE) == 0) {
			printf("my_str_cli: server terminated prematurely\n");
			exit(0);
		}
		
		fputs(recvline, stdout);
	}
	
}

int main(int argc, char const *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr;

	if (argc != 2)
		printf("usage: tcpcli <IP address>");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

	my_str_cli(stdin, sockfd);

	exit(0);
}