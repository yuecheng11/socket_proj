#include "EpollPoller.h"
#include "TcpConnection.h"
#include <stdio.h>
#include <stdlib.g>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/epoll.h>
const int kInitNumber = 2048;
using namespace std;

int crateEpollFd()
{
	int fd = ::epoll_create1(0);
	if(fd == -1)
	{
		perror("epoll create1");
	}

	return fd;
}

void addEpollFd(int epollfd,int fd)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;

	int ret = ::epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);
	if(fd == -1)
	{
		perror("epoll epoll_ctl add");
		exit(EXIT_FAILURE);
	}

	
}

void delEpollFd(int epollfd,int fd)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;

	int ret = ::epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&ev);
	if(fd == -1)
	{
		perror("epoll epoll_ctl del");
		exit(EXIT_FAILURE);
	}

	
}

ssize_t SocketIO::recvPeek(int fd,char * buff,size_t count)
{
	ssize_t nread;
	do
	{	
		//只读取到buff中，并不移走内核缓冲区的数据
		nread = ::recv(fd,buff,count,MSG_PEEK);
	}while(nread == -1 && errno == EINTR);

	return nread;
}

bool isConectionClosed(int fd)
{
	char buf[1024];
	int nread = recvPeek(fd,buf,1024);
	if(nread == -1)
	{
		perror("recv peek");
		exit(EXT_FAILURE);
	}

	return (0 == nread);
}

EpollPoller::EpollPoller(int listenfd)
	:_epollfd(crateEpollFd())
	,_listenfd(listenfd)
	,_isLooping(false)
{
	eventList.reserve(kInitNumber);
	addEpollFd(_epollfd,_listenfd);
	
}

void EpollPoller::loop()
{
	if(!_isLooping)
	{
		_isLooping = true;
		while(_isLooping)
		{
			waitEpollfd();
		}
	}
}

void EpollPoller::unloop()
{
	if(_isLooping)
	{
		_isLooping = false;
	}
}

void EpollPoller::waitEpollfd()
{
	int nready;
	do
	{
		nready = ::epoll_wait(_epollfd,&(*eventList.begin()),
					eventList.size(),5000);
		
	}while(nready == -1 && errno == EINTR);
	
	if(nready == -1)
	{
		perror("epoll wait");
		exit(EXIT_FAILURE);
	}
	else if(nready == 0)
	{
		cout<<"epoll wait timeout"<<endl;
	}
	else
	{
		//kuo da rong liang
		if(nready == static_cast<int>(eventList.size()))
		{
			eventList.resize(nready*2);
		}

		for(int idx = 0;idx<nready;++idx)
		{
			if(eventList[idx].data.fd == _listenfd)
			{//chu li xin  lianjie
				if(eventList[idx].events & EPOLLIN)
				{
					handleConnection();
				}
			}
			else
			{
				if(eventList[idx].events & EPOLLIN)
				{
					//chu li jiu lianjie
					handleMessage(eventList[idx].data.fd);
				}
			}
		}
	}
	
}

void EpollPoller::handleConnection()
{
	int peerfd = ::accept(_listenfd,NULL,NULL);
	if(peerfd == -1)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

	//jiang xinlianjie tianjia dao epoll shilide jian ting lie biao zhong
	addEpollFd(_epollfd,peerfd);

	TcpConnection* pConn = new TcpConnection(peerfds);

	_connMap[peerfd] = pConn;

	//shou dao xin lianjie gei kehuduan fa yixie xinxi 
	pConn.send("welcome to server");
}


void EpollPoller::handleMessage(int fd)
{
	bool isClosed = isConectionClosed(fd);
	map<int,TcpConnection*>::iterator it = _connMap.find(fd);
	assert(it != _connMap.end());

	if(isClosed)
	{
		::close(fd);
		
		delEpollFd(_epollfd,fd)
		_connMap.erase(it);
	}
	else
	{
		it->second->receive();
		it->second->send("test");
	}
}