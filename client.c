#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <errno.h>
# define MAXLINE  4096
void str_cli(FILE *fp,int sockfd){
	char sendline[MAXLINE],recvline[MAXLINE];
	while(fgets(sendline,MAXLINE,fp) != NULL){
		write(sockfd,sendline,strlen(sendline));
		if(read(sockfd,recvline,MAXLINE) == 0){
			printf("str_cli:server terminated prematurely");
			exit(0);
		}
		fputs(recvline,stdout);
	}
}
int main(int argc,char **argv){
	int sockfd,sockfd1,sockfd2,sockfd3,sockfd4,sockfd5;
	struct sockaddr_in servaddr;
	if(argc!=3)
		printf("usage:tcpcli<IPaddress> <Port>");
	sockfd1 = socket(AF_INET,SOCK_STREAM,0);
	sockfd2 = socket(AF_INET,SOCK_STREAM,0);
	sockfd3 = socket(AF_INET,SOCK_STREAM,0);
	sockfd4 = socket(AF_INET,SOCK_STREAM,0);
	sockfd5 = socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
	connect(sockfd1,(struct sockaddr*)&servaddr,sizeof(servaddr));
	connect(sockfd2,(struct sockaddr*)&servaddr,sizeof(servaddr));
	connect(sockfd3,(struct sockaddr*)&servaddr,sizeof(servaddr));
	connect(sockfd4,(struct sockaddr*)&servaddr,sizeof(servaddr));
	connect(sockfd5,(struct sockaddr*)&servaddr,sizeof(servaddr));
	str_cli(stdin,sockfd);
	exit(0);
}


