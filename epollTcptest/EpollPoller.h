#ifndef _MY_EPOLLPOLLER_H_
#define _MY_EPOLLPOLLER_H_
#include "Noncopy.h"
#include "TcpConnection.h"
#include <vector>
#include <map>
#include <sys/epoll.h>
#include <iostream>

#define MAXNUM 100
using namespace std;

class EpollPoller:Noncopy
{
public:
	EpollPoller(int listenfd);

	void loop();
	void unloop();

private:
	void waitEpollfd();
	void handleConnection();
	void handleMessage(int fd);
private:
	int _epollfd;
	int _listenfd;
	bool _isLooping;

	//vector<struct epoll_event> eventList;
	struct epoll_event eventList[MAXNUM];
	map<int,TcpConnection*> _connMap;
};

#endif
