
#ifndef __MY_EPOLLPOLLER_H_
#define __MY_EPOLLPOLLER_H_
#include "Noncopyable.h"
#include "TcpConnection.h"
#include <sys/epoll.h>
#include <vector>
#include <map>
#include <functional>

using std::vector;
using std::map;

#define READ 0
#define WRITE 1
namespace wd
{

class EpollPoller : Noncopyable
{
public:
	typedef std::function<void(TcpConnectionPtr)> EpollPollerCallback;
	EpollPoller(int listenfd);
	~EpollPoller();

	void loop();
	void unloop();

	void setConnectionCallback(EpollPollerCallback cb);
	void setMessageCallback(EpollPollerCallback cb);
	void setCloseCallback(EpollPollerCallback cb);
	
	void setReadMessageCallback(EpollPollerCallback cb);
	void setWriteMessageCallback(EpollPollerCallback cb);

private:
	void waitEpollfd();
	void handleConnection();
	void handleMessage(int fd,int op);

private:
	int _epollfd;
	int _listenfd;
	bool _isLooping;

	vector<struct epoll_event> _eventList;
	map<int, TcpConnectionPtr> _connMap;

	EpollPollerCallback _onConnection;
	EpollPollerCallback _onMessage;
	EpollPollerCallback _onClose;
	
	EpollPollerCallback onReadMessage;
	EpollPollerCallback onWriteMessage;
	
};

}//end of namespace wd


#endif
