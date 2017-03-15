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

	void AddListenSock(int fd);
	
	void wait_epoll();
private:
	void EventSet(myevent_s* ev,int fd,void(*call_back)(int,int,void*),void* arg);
	void EventAdd(int events,myevent_s* myev);
private:
	int _epollfd;
	int _listensock;
	
	struct myevent_s _myevent[MAX_EVENTS];
	struct epoll_event _epollEvents[MAX_EVENTS];
	//TcpConnection _conn;
};

#endif
