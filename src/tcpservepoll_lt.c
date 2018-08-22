/* TCP server, EPOLL with LT mode */

#include <sys/epoll.h>
#include "myunp.h"

struct user{
	char buf[MAXLINE];
	char *iptr;
	char *optr;
};	

void inituser(struct user *users, int sockfd)
{
	memset(users[sockfd].buf, 0, sizeof(users[sockfd].buf));
	users[sockfd].iptr = users[sockfd].buf;
	users[sockfd].optr = users[sockfd].buf;
}

int main(int argc, char const *argv[])
{
	int 				listenfd, connfd, epfd, nready, i, nread, sockfd, nwritten;
	socklen_t 			clilen;
	//char 				buf[MAXLINE];
	struct sockaddr_in 	servaddr, cliaddr;
	struct epoll_event 	events[MAX_EVENTS], add_event, del_event;	//此处add_event和del_event有点重复，可删去其一
	struct user			users[MAX_EVENTS];


	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family 		= AF_INET;
	servaddr.sin_port 			= htons(SERV_PORT);
	servaddr.sin_addr.s_addr 	= htonl(INADDR_ANY);

	bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
	listen(listenfd, LISTENQ);

	clilen = sizeof(cliaddr);

	//创建epoll实例
	epfd = epoll_create(1024);

	add_event.events = 	EPOLLIN;
	add_event.data.fd = listenfd;
	epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &add_event);

	while (1)
	{
		nready = epoll_wait(epfd, events, MAX_EVENTS, -1);

		if (nready < 0)
		{
			printf("nready < 0\n");
			break;
		}

		for (i = 0; i < nready; i++)
		{
			if (events[i].data.fd == listenfd)
			{
				connfd = accept(listenfd, (SA *) &cliaddr, &clilen);
				if (connfd < 0)
				{
					printf("connect error!\n");
					exit(0);
				}

				inituser(users, connfd);

				add_event.data.fd = connfd;
				add_event.events = EPOLLIN;
				epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &add_event);
			}
			else if (events[i].events & EPOLLIN)
			{
				sockfd = events[i].data.fd;
				// read是从套接字读到buf中
				if ( (nread = read(sockfd, users[sockfd].iptr, &users[sockfd].buf[MAX_EVENTS] - users[sockfd].iptr)) < 0)
				{
					printf("nread < 0\n");
					exit(0);
				}
				else if (nread == 0)
				{
					close(sockfd);
					del_event = events[i];
					epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, &del_event);
				}
				else
				{
					//write(sockfd, buf, nread);
					users[sockfd].iptr += nread;
					add_event.data.fd = sockfd;
					add_event.events = EPOLLOUT;
					epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &add_event);
				}
					
			}
			else if (events[i].events & EPOLLOUT)
			{
				sockfd = events[i].data.fd;
				nwritten = write(sockfd, users[sockfd].optr, users[sockfd].iptr - users[sockfd].optr);
				
				if (nwritten < 0)
				{
					perror("write");
					exit(0);
				}
				
				users[sockfd].optr += nwritten;
				
				if(users[sockfd].iptr == users[sockfd].optr){
					users[sockfd].iptr = users[sockfd].buf;
					users[sockfd].optr = users[sockfd].buf;
				}

				del_event.data.fd = sockfd;
				del_event.events = EPOLLIN;
				epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &del_event);
			}
		}
	}

	close(listenfd);
	
	return 0;
}
