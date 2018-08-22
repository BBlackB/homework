// #include "unp.h"

// int main(int argc, char const *argv[])
// {
//     union{
//         short s;
//         char c[sizeof(short)];
//     }un;
//     un.s = 0x0102;
//     printf("%s: ",CPU_VENDOR_OS);
//     if (sizeof(short) == 2)
//     {
//         if (un.c[0] == 1 && un.c[1] == 2)
//             printf("big-endian\n");
//         else if (un.c[0] == 2 && un.c[1] == 1)
//             printf("little-endian\n");
//         else
//             printf("unkown\n");
//     }
//     else
//     {
//         printf("sizeof(short) = %d\n", sizeof(short));
//     }
//     getchar();
//     return 0;
// }

// #include <stdio.h>

// int main(int argc, char const *argv[])
// {
//     int arg1, arg2;
//     char str[1024];
//     while (1)
//     {
//         printf("input string: ");
//         gets(str);
//         puts(str);
//         //scanf("%s", str);
//         sscanf(str, "%ld%ld", &arg1, &arg2);
//         printf("arg1=%ld, arg2=%ld\n", arg1, arg2);
//         //getchar();
//     }
    
//     return 0;
// }

// #include "unp.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <errno.h>
// #include <errno.h>

// void sig_chld(int signo)
// {
//     pid_t pid;
//     int stat;
//     pid = wait(&stat);
//     printf("child process %d terminated.\n",pid);
// }


// int main(int argc, char const *argv[])
// {
//     pid_t pid;
//     pid = fork();
//     if (pid < 0)
//     {
//         printf("fork error:");
//         exit(1);
//     }

//    // signal(SIGCHLD, SIG_IGN);
//     if (pid == 0)
//     {
//         printf("I am the child process:\n");
//         // printf("pid:%d\tppid:%d\n",getpid(), getppid());
//         // printf("I will sleep five seconds.\n");
//         // sleep(5);
//         // printf("pid:%d\tppid:%d\n",getpid(),getppid());
//         // printf("child process is exited.\n");
//         exit(0);
//     }
//     else
//     {
//         printf("I am father process.\n");
//         sleep(2);
//         system("ps -o pid,ppid,state,tty,command");
//         printf("father process is exited.\n");
//     }
//     return 0;
// }


// #include "unp.h"
// #include "udp_server2.h"
// #include <time.h>

// int main(int argc, char const *argv[])
// {
//     int sockfd;
//     ssize_t n;
//     time_t ticks;
//     char buff[MAXLINE];
//     socklen_t len;
//     struct sockaddr_storage cliaddr;

//     if(argc == 2)
//         sockfd = udp_server2(NULL, argv[1], NULL);
//     else if (argc == 3)
//         sockfd = udp_server2(argv[1], argv[2], NULL);
//     else
//         err_quit("usage: test [ <host> ] <services or port>");

//     while(1)
//     {
//         len = sizeof(cliaddr);
//         n = Recvfrom(sockfd, buff, MAXLINE, 0, (SA *)&cliaddr, &len);
//         printf("dategram from %s\n", Sock_ntop((SA *)&cliaddr, len));

//         ticks = time(NULL);
//         snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
//         Sendto(sockfd, buff, sizeof(buff), 0, (SA *)&cliaddr, len);
//     }

//     return 0;
// }

// #include	"unp.h"
// #include <netinet/tcp.h>

// int
// main(int argc, char **argv)
// {
// 	int					sockfd, n;
// 	char				recvline[MAXLINE + 1];
// 	struct sockaddr_in	servaddr;
//     int val_buf, val_seg;
//     socklen_t len;


// 	if (argc != 2)
// 		err_quit("usage: a.out <IPaddress>");

// 	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
// 		err_sys("socket error");

// 	bzero(&servaddr, sizeof(servaddr));
// 	servaddr.sin_family = AF_INET;
// 	servaddr.sin_port   = htons(13);	/* daytime server */
// 	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
// 		err_quit("inet_pton error for %s", argv[1]);

//     len = sizeof(val_buf);
//     getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &val_buf, &len);
//     printf("Before connect, RCVBUF=%d\n", val_buf);
//     getsockopt(sockfd, IPPROTO_TCP, TCP_MAXSEG, &val_seg, &len);
//     printf("Before connect, MAXSEG=%d\n", val_seg);

// 	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
// 		err_sys("connect error");

//     getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &val_buf, &len);
//     printf("After connect, RCVBUF=%d\n", val_buf);
//     getsockopt(sockfd, IPPROTO_TCP, TCP_MAXSEG, &val_seg, &len);
//     printf("After connect, MAXSEG=%d\n", val_seg);

// 	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
// 		recvline[n] = 0;	/* null terminate */
// 		if (fputs(recvline, stdout) == EOF)
// 			err_sys("fputs error");
// 	}
// 	if (n < 0)
// 		err_sys("read error");

// 	exit(0);
// }

//tcp client
// #include "unp.h"

// void my_str_cli(FILE *fp, int sockfd)
// {
// 	char sendline[MAXLINE], recvline[MAXLINE];

	
// 	while((fgets(sendline, MAXLINE, fp) != NULL)){
// 		writen(sockfd, sendline, strlen(sendline));

		
// 		if (readline(sockfd, recvline, MAXLINE) == 0) {
// 			printf("my_str_cli: server terminated prematurely\n");
// 			exit(0);
// 		}
		
// 		fputs(recvline, stdout);
// 	}
	
// }

// int main(int argc, char const *argv[])
// {
// 	int sockfd;
// 	struct sockaddr_in servaddr;

// 	if (argc != 2)
// 		printf("usage: tcpcli <IP address>");

// 	bzero(&servaddr, sizeof(servaddr));
// 	servaddr.sin_family = AF_INET;
// 	servaddr.sin_port = htons(SERV_PORT);
// 	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

// 	sockfd = socket(AF_INET, SOCK_STREAM, 0);

// 	connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

// 	my_str_cli(stdin, sockfd);

// 	exit(0);
// }

// #include "unp.h"

// void my_str_echo(int sockfd)
// {
// 	ssize_t n;
// 	char recvline[MAXLINE];

// 	while (1)
// 	{
// 		while( (n = read(sockfd, recvline, MAXLINE)) > 0)
// 		{
// 			writen(sockfd, recvline, n);		
// 		}
// 		if (n < 0 && errno == EINTR)	continue;
// 		else if(n < 0)	printf("my_str_echo: read error\n");
// 		else break;
// 	}
// }

// int main(int argc, char const *argv[])
// {
// 	int connfd, listenfd;
// 	struct sockaddr_in cliaddr, servaddr;
// 	socklen_t len;
// 	pid_t childpid;

// 	listenfd = socket(AF_INET, SOCK_STREAM, 0);

// 	bzero(&servaddr, sizeof(servaddr));
// 	servaddr.sin_family = AF_INET;
// 	servaddr.sin_port = htons(SERV_PORT);
// 	servaddr.sin_addr.s_addr = htons(INADDR_ANY);

// 	bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
// 	listen(listenfd, LISTENQ);
	
	
// 	while(1){
// 		len = sizeof(cliaddr);
// 		connfd = accept(listenfd, (SA *)&cliaddr, &len);

// 		if ((childpid = fork()) == 0)
// 		{
// 			close(listenfd);
// 			my_str_echo(connfd);
// 			exit(0);
// 		}
// 		close(connfd);
// 	}
		

// 	return 0;
// }

// #include "unp.h"
// #include <stdio.h>
// #include <pthread.h>
// #include <sys/epoll.h>

// void *doit(void *arg)
// {
// 	int counter = 0;
// 	while(1)
// 	{
// 		printf("counter = %d\n", counter++);
// 		sleep(1);
// 	}
// 	return NULL;
// }


// int main(int argc, char const *argv[])
// {
// 	pthread_t tid;
// 	int res;
	
// 	res = pthread_create(&tid, NULL, doit, NULL);

// 	printf("In main: pthread_create return  = %d\n", res);
	
// 	sleep(10);

// 	return 0;
// }

// #include <sys/epoll.h>
// #include "myunp.h"
// #define MAX_EVENTS 1024


// int main(int argc, char const *argv[])
// {
// 	int 				listenfd, connfd, epfd, nready, i, nread, sockfd;
// 	socklen_t 			clilen;
// 	char 				buf[MAXLINE];
// 	struct sockaddr_in 	servaddr, cliaddr;
// 	struct epoll_event 	events[MAX_EVENTS], add_event;


// 	listenfd = socket(AF_INET, SOCK_STREAM, 0);

// 	bzero(&servaddr, sizeof(servaddr));
// 	servaddr.sin_family 		= AF_INET;
// 	servaddr.sin_port 			= htons(SERV_PORT);
// 	servaddr.sin_addr.s_addr 	= htonl(INADDR_ANY);

// 	bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
// 	listen(listenfd, LISTENQ);

// 	clilen = sizeof(cliaddr);

// 	//创建epoll实例
// 	epfd = epoll_create(1024);

// 	add_event.events = 	EPOLLIN;
// 	add_event.data.fd = listenfd;
// 	epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &add_event);

// 	while (1)
// 	{
// 		nready = epoll_wait(epfd, events, MAX_EVENTS, -1);

// 		if (nready < 0)
// 		{
// 			printf("nready < 0\n");
// 			break;
// 		}

// 		for (i = 0; i < nready; i++)
// 		{
// 			if (events[i].data.fd == listenfd)
// 			{
// 				connfd = accept(listenfd, (SA *) &cliaddr, &clilen);
// 				if (connfd < 0)
// 				{
// 					printf("connect error!\n");
// 					exit(0);
// 				}

// 				add_event.data.fd = connfd;
// 				add_event.events = EPOLLIN;
// 				epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &add_event);
// 			}
// 			else if (events[i].events & EPOLLIN)
// 			{
// 				sockfd = events[i].data.fd;
// 				if ( (nread = read(sockfd, buf, MAXLINE)) < 0)
// 				{
// 					printf("nread < 0\n");
// 					exit(0);
// 				}
// 				else if (nread == 0)
// 					close(sockfd);
// 				else
// 					write(sockfd, buf, nread);
// 			}
// 		}
// 	}

// 	close(listenfd);
	
// 	return 0;
// }

// /* TCP client, EPOLL with LT mode */
// #include	"myunp.h"
// #define DEBUG

// // TCP client of epoll
// int main(int argc, char const *argv[])
// {
// 	int 				sockfd, epfd, nready, nread_send, nread_recv, nwritten, i;
// 	struct sockaddr_in 	servaddr;
// 	char 				sendline[MAXLINE], recvline[MAXLINE];
// 	struct epoll_event 	events[MAX_EVENTS], add_event, del_event;

// 	sockfd = socket(AF_INET, SOCK_STREAM, 0);
// 	bzero(&servaddr, sizeof(servaddr));
// 	servaddr.sin_family = AF_INET;
// 	servaddr.sin_port = htons(SERV_PORT);

// 	if (argc < 2)
// 	{
// 		printf("usage: tcpcliepoll <IPaddress> \n");
// 		exit(0);
// 	}
// 	inet_pton(AF_INET, argv[1], &servaddr.sin_addr.s_addr);

// 	connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

// 	epfd = epoll_create(1024);

// 	add_event.data.fd = sockfd;
// 	add_event.events = EPOLLIN;
// 	epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &add_event);

// 	add_event.data.fd = fileno(stdin);
// 	add_event.events = EPOLLIN;
// 	epoll_ctl(epfd, EPOLL_CTL_ADD, fileno(stdin), &add_event);

// 	while (1)
// 	{
// 		nready = epoll_wait(epfd, events, MAX_EVENTS, -1);
// 		if (nready <= 0)
// 		{
// 			printf("epoll_wait error: nready <= 0\n");
// 			exit(0);
// 		}

// 		for (i = 0; i < nready; i++)
// 		{
// 			if (events[i].data.fd == fileno(stdin))			// stdin 
// 			{
// #ifdef DEBUG
// 				printf("stdin EPOLLIN triggered!\n");
// #endif
// 				if ( (nread_send = read(fileno(stdin), sendline, MAXLINE)) < 0)
// 				{
// 					printf("read error: read from stdin to sockfd, nread < 0\n");
// 					exit(0);
// 				}
// 				else if (nread_send == 0)
// 				{
// 					shutdown(sockfd, SHUT_WR);
// 					// close(sockfd);
// 					epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, &del_event);
// #ifdef DEBUG
// 					printf("sockfd closed!\n");
// #endif 
// 					exit(0);		//continue;程序不会结束，会阻塞在epoll中
// 				}
// 				else
// 				{
// 					add_event.data.fd = sockfd;
// 					add_event.events = EPOLLOUT;
// 					epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &add_event);
// 					continue;
// 				}
					
// 			}
// 			else if (events[i].data.fd == fileno(stdout))		//stdout
// 			{
// #ifdef DEBUG
// 				printf("stdout EPOLLOUT triggered!\n");
// #endif
// 				nwritten = write(fileno(stdout), recvline, nread_recv);
// #ifdef DEBUG
// 				printf("write %d bytes to stdout!\n", nwritten);
// #endif
// 				epoll_ctl(epfd, EPOLL_CTL_DEL, fileno(stdout), &del_event);
// 				continue;
// 			}
// 			else	//sockfd
// 			{
// 				if (events[i].events & EPOLLIN)
// 				{
// #ifdef DEBUG
// 					printf("sockfd EPOLLIN triggered!\n");
// #endif
// 					if ( (nread_recv = read(events[i].data.fd, recvline, MAXLINE)) < 0)
// 					{
// 						printf("read error: read from sockfd to stdout, nread < 0\n");
// 						exit(0);
// 					}
// 					else if (nread_recv == 0)
// 					{
// 						printf("exit from sockfd!\n");
// 						exit(0);
// 					}
// 					else
// 					{
// 						add_event.data.fd = fileno(stdout);
// 						add_event.events = EPOLLOUT;
// 						epoll_ctl(epfd, EPOLL_CTL_ADD, fileno(stdout), &add_event);
// 						continue;
// 					}
// 				}
// 				else if ( events[i].events & EPOLLOUT)
// 				{
// #ifdef DEBUG					
// 					printf("sockfd EPOLLOUT triggered!\n");
// #endif				
// 					nwritten = write(sockfd, sendline, nread_send);
// #ifdef DEBUG
// 					printf("write %d bytes to sockfd!\n", nwritten);
// #endif					
// 					add_event = events[i];
// 					add_event.events = EPOLLIN;
// 					epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &add_event);
// 					continue;
// 				}
// 			}
			
// 		}
// 	}
	
// 	return 0;
// }


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
