#ifndef _MY_EPOLLPOLLER_H_
#define _MY_EPOLLPOLLER_H_
#include "Noncopy.h"
#include "TcpConnection.h"
#include <vector>
#include <map>
#include <sys/epoll.h>
#include <iostream>

using namespace std;
#define MAX_EVENTS 500

struct myevent_s
{
	int fd;
	void (*call_back)(int fd, int events,void *arg);
	int events;
	void* arg;
	int status;  //1: in epoll wait list,0:not in
	char buff[1024]; //recv data buffer
	int len,s_offset;
	long last_actives; //last active time
	
};

class EpollPoller:Noncopy
{
public:
	EpollPoller();
	void loop();
	void unloop();

	void InitListenSock(int g_epollfd,unsigned short port);
	void wait_epoll();
private:
	int _epollfd;
	struct myevent_s _myevent;
	struct epoll_event _epollEvents[MAX_EVENTS];
	//TcpConnection _conn;
};

#endif
