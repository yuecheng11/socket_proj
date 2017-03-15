#include "EpollPoller.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <string>
#include <sys/epoll.h>

using namespace std;

int creatEpollFd()
{
	int fd = ::epoll_create1(0);
	if(fd == -1)
	{
		perror("epoll create1");
	}

	return fd;
}

EpollPoller::EpollPoller()
	:_epollfd(creatEpollFd())
{
	memset(_myevent,0,sizeof(struct myevent_s));
	_epollEvents[MAX_EVENTS] = {0,{0}};
}
void EpollPoller::AddListenSock(int listenfd)
{
	_listensock = listenfd;
	EventSet(&_myevent[MAX_EVENTS],_listensock,AcceptConn,&_epollEvents[MAX_EVENTS]);
	EventAdd(EPOLLIN,&_myevent[MAX_EVENTS]);
}
void EpollPoller::EventSet(myevent_s * ev,int fd,void(* call_back)(int,int,void *),void * arg)
{
	ev->fd = fd;
	ev->call_back = call_back;
	ev->events = 0;
	ev->arg = arg;
	ev->status = 0;
	memset(ev->buff,0,sizeof(ev->buff));
	ev->s_offset = 0;
	ev->len = 0;
	ev->last_actives = time(NULL);
	
}
void EpollPoller::EventAdd(int events,myevent_s* myev)
{
	struct epoll_event ep = {0,{0}};
	int op;
	ep.data.ptr = myev;
	ep.events = myev->events = events;
	ep.data.fd = myev->fd;
	if(myev->status)
	{
		op = EPOLL_CTL_MOD;
	}
	else
	{
		op = EPOLL_CTL_ADD;
		myev->status = 1;
	}
	int ret = ::epoll_ctl(_epollfd,op,myev->fd,&ep);
	if(ret < 0)
	{
		cout<<"Event Add failed fd = "<<myev->fd<<"event: "<<events<<endl;
	}
	else
	{
		cout<<"Event Add succed fd = "<<myev->fd<<"op = "<<op<<"event: "<<events<<endl;
	}
	
}