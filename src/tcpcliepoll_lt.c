
/* TCP client, EPOLL with LT mode */
#include	"myunp.h"
//#define DEBUG

int main(int argc, char const *argv[])
{
	int 				sockfd, epfd, nready, nread_send, nread_recv, nwritten, i;
	struct sockaddr_in 	servaddr;
	char 				sendline[MAXLINE], recvline[MAXLINE];
	struct epoll_event 	events[MAX_EVENTS], add_event, del_event;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);

	if (argc < 2)
	{
		printf("usage: tcpcliepoll <IPaddress> \n");
		exit(0);
	}
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr.s_addr);

	connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

	epfd = epoll_create(1024);

	add_event.data.fd = sockfd;
	add_event.events = EPOLLIN;
	epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &add_event);

	add_event.data.fd = fileno(stdin);
	add_event.events = EPOLLIN;
	epoll_ctl(epfd, EPOLL_CTL_ADD, fileno(stdin), &add_event);

	while (1)
	{
		nready = epoll_wait(epfd, events, MAX_EVENTS, -1);
		if (nready <= 0)
		{
			printf("epoll_wait error: nready <= 0\n");
			exit(0);
		}

		for (i = 0; i < nready; i++)
		{
			if (events[i].data.fd == fileno(stdin))			// stdin 
			{
#ifdef DEBUG
				printf("stdin EPOLLIN triggered!\n");
#endif
				if ( (nread_send = read(fileno(stdin), sendline, MAXLINE)) < 0)
				{
					printf("read error: read from stdin to sockfd, nread < 0\n");
					exit(0);
				}
				else if (nread_send == 0)
				{
					shutdown(sockfd, SHUT_WR);
					// close(sockfd);
					epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, &del_event);
#ifdef DEBUG
					printf("sockfd closed!\n");
#endif 
					exit(0);		//continue;程序不会结束，会阻塞在epoll中
				}
				else
				{
					add_event.data.fd = sockfd;
					add_event.events = EPOLLOUT;
					epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &add_event);
				}
					
			}
			else if (events[i].data.fd == fileno(stdout))		//stdout
			{
#ifdef DEBUG
				printf("stdout EPOLLOUT triggered!\n");
#endif
				nwritten = write(fileno(stdout), recvline, nread_recv);
#ifdef DEBUG
				printf("write %d bytes to stdout!\n", nwritten);
#endif
				epoll_ctl(epfd, EPOLL_CTL_DEL, fileno(stdout), &del_event);
			}
			else	//sockfd
			{
				if (events[i].events & EPOLLIN)
				{
#ifdef DEBUG
					printf("sockfd EPOLLIN triggered!\n");
#endif
					if ( (nread_recv = read(events[i].data.fd, recvline, MAXLINE)) < 0)
					{
						printf("read error: read from sockfd to stdout, nread < 0\n");
						exit(0);
					}
					else if (nread_recv == 0)
					{
						printf("exit from sockfd!\n");
						exit(0);
					}
					else
					{
						add_event.data.fd = fileno(stdout);
						add_event.events = EPOLLOUT;
						epoll_ctl(epfd, EPOLL_CTL_ADD, fileno(stdout), &add_event);
					}
				}
				else if ( events[i].events & EPOLLOUT)
				{
#ifdef DEBUG					
					printf("sockfd EPOLLOUT triggered!\n");
#endif				
					nwritten = write(sockfd, sendline, nread_send);
#ifdef DEBUG
					printf("write %d bytes to sockfd!\n", nwritten);
#endif					
					add_event = events[i];
					add_event.events = EPOLLIN;
					epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &add_event);
				}
			}
			
		}
	}
	
	return 0;
}
