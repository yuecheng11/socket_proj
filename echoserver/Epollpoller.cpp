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
