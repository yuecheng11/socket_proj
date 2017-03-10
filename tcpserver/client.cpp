#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <iostream>
#include <arpa/inet.h>


int main(int argc,char* argv[])
{
	int sockfd;
	int buflen = -1;
	char buf[1024],recvbuf[1024];
	
	if(argc != 3)
	{
		printf("param error");
		exit(0);
	}	
	//client start creat sockfd
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		printf("client create socket error: %s(error : %d)!!!\n",strerror(errno),errno);
		exit(0);
	}
	
	//set ip and  port...of servers'
	struct sockaddr_in srvaddr;
	bzero(&srvaddr,sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(atoi(argv[2]));
	srvaddr.sin_addr.s_addr = inet_addr(argv[1]);
	//srvaddr.sin_addr.s_addr = INADDR_ANY;
	/*
	if(inet_pton(AF_INET,argv[1],&srvaddr.sin_addr) <= 0)
	{
		printf("client set server ip error : %s(error: %d)\n",strerror(errno),errno);
		exit(0);
	}
	*/
	//client start connet server
	if(connect(sockfd,(struct sockaddr*)&srvaddr,sizeof(srvaddr)) == -1)
	{
		printf("client connect server error : %s(error : %d)\n",strerror(errno),errno);
		exit(0);
	}	
	
	printf("\nconnect success\n\nsend message to server\n");
	while(1)
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),stdin);
		if(send(sockfd,buf,strlen(buf),0) == -1)
		{
			printf("send message error: %s(error: %d)\n",strerror(errno),errno);
			exit(0);
		}

		printf("write buf: %s\n",buf);
		if(0 == strncmp(buf,"byebye",6))
		{
			printf("disconnect server\n");
			break;
		}

		memset(recvbuf,0,sizeof(recvbuf));
		if((buflen = recv(sockfd,recvbuf,sizeof(recvbuf),0)) == -1)
		{
		    printf("read client error: %s\n",strerror(errno));
		    exit(0);
		}
		recvbuf[buflen] = '\0';	
		printf("recv from server: %s\n",recvbuf);
	
	}
	close(sockfd);
	printf("comunication with server over\n");
	return 0;


}
