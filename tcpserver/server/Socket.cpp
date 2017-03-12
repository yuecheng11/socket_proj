#include "Socket.h"
#include "InetAddress.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>


using namespace std;
int createSocketFd()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		printf("socket error: %s\n",strerror(errno));
		exit(0);
	}
	return sockfd;
}

Socket::Socket()
:_sockFd(createSocketFd())
{

}

Socket::Socket(int sockfd)
	:_sockFd(sockfd)
{
}

void Socket::ready(InerAddress& addr)
{
	setReuseAddr(true);
	setReusePort(true);
	bind(addr);
	listen();
}

int Socket::accept()
{
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(struct sockaddr_in);
	int peerFd = ::accept(_sockFd,(struct sockaddr*)(&cliaddr),&len);
	if(peerFd < 0)
	{
		printf("accept error: %s\n",strerror(errno));
        exit(0);
	}

	return peerFd;
}
void Socket::bind(InerAddress& addr)
{
	
	int ret = ::bind(_sockFd,
		(struct sockaddr*)(addr.getInetAddressPtr()),
		sizeof(struct sockaddr));
	if(ret < 0)
	{
		printf("bind error: %s\n",strerror(errno));
		close(_sockFd);
		exit(0);
	}
}

void Socket::listen()
{
	int ret = ::listen(_sockFd,5);
	if(ret == -1)
	{
		printf("listen error: %s\n",strerror(errno));
        exit(0);
	}
}
void Socket::setReuseAddr(bool flag)
{
	int on = flag ? 1 : 0;
	int ret = ::setsockopt(_sockFd,
						SOL_SOCKET,
						SO_REUSEADDR,
						&on,
						static_cast<socklen_t>(sizeof(on)));
	if(-1 == ret)
	{
		perror("setsockopt error");
		close(_sockFd);
		exit(0);
	}
}
void Socket::setReusePort(bool flag)
{
#ifdef SO_REUSEPORT

	int on = flag ? 1 : 0;
	int ret = ::setsockopt(_sockFd,
						SOL_SOCKET,
						SO_REUSEPORT,
						&on,
						static_cast<socklen_t>(sizeof(on)));
	if(-1 == ret)
	{
		perror("setsockopt reuseport");
		close(_sockFd);
		exit(0);
	}
#else
	if(flag)
	{
		cout<<"SO_REUSEPORT us not support"<<endl;
	}
#endif
}


void Socket::shutdownWrite()
{
	int ret = ::shutdown(_sockFd,SHUT_WR);
	if(ret == -1)
	{
	    perror("shutdown error!");
		exit(EXIT_FAILURE);
	}
}

InerAddress Socket::getLocalAddr(int fd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(struct sockaddr_in);

	int ret = ::getsockname(fd,(struct sockaddr*)&addr,&len);
	if(-1 == ret)
	{
		perror("getsockname error");
	}
	return InerAddress(addr);
}

InerAddress Socket::getPeerAddr(int fd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(struct sockaddr_in);

	int ret = ::getpeername(fd,(struct sockaddr*)&addr,&len);
	if(-1 == ret)
	{
		perror("getsockname error");
	}
	return InerAddress(addr);
}
