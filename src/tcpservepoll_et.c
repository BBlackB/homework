/* TCP server, EPOLL with ET mode */
#include "myunp.h"
// #define DEBUG

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

void err_quit(const char *strerr)
{
	perror(strerr);
	exit(1);
}

void setnonblock(int sockfd)
{
	int val;
	val = fcntl(sockfd, F_GETFL);
	if (val < 0) err_quit("fcntl GET");

	if ( fcntl(sockfd, F_SETFL, val | O_NONBLOCK) < 0)
		err_quit("fcntl SET");
}

void debug_print(const char * str)
{

#ifdef DEBUG
	puts(str);
#endif

}

int main(int argc, char const *argv[])
{
	int 				epfd, sockfd, listenfd, connfd;
	int 				nready, nread, nwritten, i, flag;	//flag用于标记是否操作了缓冲区，以便设置EPOLLIN/EPOLLOUT
	struct epoll_event 	events[MAX_EVENTS], ev;
	struct user 		users[MAX_EVENTS];
	struct sockaddr_in 	servaddr, cliaddr;
	socklen_t clilen;

	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
		err_quit("socket");
	
	setnonblock(listenfd);		// 将listenfd设置为非阻塞

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family	 		= 	AF_INET;
	servaddr.sin_port 			= 	htons(SERV_PORT);
	servaddr.sin_addr.s_addr 	= 	htonl(INADDR_ANY);

	if ( bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		err_quit("bind");

	if ( listen(listenfd, LISTENQ) < 0)
		err_quit("listen");

	clilen = sizeof(cliaddr);

	epfd = epoll_create(1024);
	ev.data.fd = listenfd;
	ev.events = EPOLLIN | EPOLLET;
	epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);

	flag = 0;		

	while (1){
		debug_print("epoll_wait called\n");
		nready = epoll_wait(epfd, events, MAX_EVENTS, -1);

		for (i = 0; i < nready; i++){
			if (events[i].data.fd == listenfd){
				debug_print("listenfd triggered!\n");
				while (1){
					debug_print("accpet called\n");
					connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
					if (connfd < 0){
						if (errno == EWOULDBLOCK || errno == EINTR) break;
						if (errno == ECONNABORTED || errno == EPROTO) continue;
						err_quit("accpet");
					}
					setnonblock(connfd);
					inituser(users, connfd);

					ev.data.fd = connfd;
					ev.events = EPOLLIN | EPOLLET;
					epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
				}
			}
			else if (events[i].events & EPOLLIN){
				debug_print("sockfd EPOLLIN triggered\n");
				sockfd = events[i].data.fd;
				flag = 0;				//还未操作缓冲区
				while (1){
					debug_print("read called\n");
					//read 是从套接字读到buf中
					nread = read(sockfd, users[sockfd].iptr, &users[sockfd].buf[MAXLINE] - users[sockfd].iptr);
					if (nread == -1){
						debug_print("nread == -1\n");
						if (errno == EWOULDBLOCK) break;
						err_quit("read sockfd");
					}
					else if (nread == 0){
						debug_print("nread == 0\n");
						close(sockfd);
						ev = events[i];
						epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, &ev);
						flag = 0;		//疑问：是否会先置flag为1，然后关闭套接字？
						break;
					}
					else{
						// printf("read %d bytes\n\n", nread);
						users[sockfd].iptr += nread;						
						flag = 1;
					}
				}

				if (flag){
					ev.data.fd = sockfd;
					ev.events = EPOLLOUT | EPOLLET;
					epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
				}				
			}
			else if (events[i].events & EPOLLOUT)
			{
				debug_print("sockfd EPOLLOUT triggered\n");
				sockfd = events[i].data.fd;
				flag = 0;
				
				while(1){
					debug_print("write called\n");
					// 从 buf write 到套接字中，所以地址从optr开始
					nwritten = write(sockfd, users[sockfd].optr, users[sockfd].iptr - users[sockfd].optr);
					// printf("write %d bytes to sockfd\n\n", nwritten);
					if (nwritten == -1){
						if (errno == EWOULDBLOCK)	break;
						err_quit("write scokfd");
					}
					else if (nwritten == 0){
						break;
					}
					else{
						users[sockfd].optr += nwritten;
						flag = 1;
						if (users[sockfd].optr == users[sockfd].iptr){
							users[sockfd].optr = users[sockfd].buf;
							users[sockfd].iptr = users[sockfd].buf;
						}
					}
				}

				if (flag){
					ev.data.fd = sockfd;
					ev.events = EPOLLIN | EPOLLET;
					epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
				}				
			}
			else
			{
				err_quit("unkonwn error");
			}

		}	// i == nready
	}

	return 0;
}
