#ifndef _MY_EPOLLPOLLER_H_
#define _MY_EPOLLPOLLER_H_
#include "Noncopy.h"
#include <vector>
#include <map>

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

	vector<struct epoll_event> eventList;
	map<int,TcpConnection*> _connMap;
};

#endif