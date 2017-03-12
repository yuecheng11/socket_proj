#ifndef MY_SOCKET_H_
#define MY_SOCKET_H_
#include <Noncopy.h>

class InerAddress;

class Socket:Noncopy
{
public:
	Socket();
	Socket(int sockfd);
	void ready(InerAddress& addr);
	int accept();

	void shutdownWrite();
	static InerAddress getLocalAddr(int fd);
	static InerAddress getPeerAddr(int fd);

private:
	void setReuseAddr(bool flag);
	void setReusePort(bool flag);
	void bind(InerAddress& addr);
	void listen();
private:
	int _sockFd;
};

#endif