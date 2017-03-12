#ifndef _MY_SOCKETIO_H_
#define _MY_SOCKETIO_H_
#include "Noncopy.h"
#include <unistd.h>

class SocketIO:Noncopy
{
public:
	SocketIO(int fd);
	ssize_t readn(char* buff,size_t count);
	ssize_t writen(const char* buff,size_t count);
	ssize_t readline(char* buff,size_t max);
private:
	ssize_t readPeek(char* buff,size_t count);
private:
	int _fd;
};

#endif