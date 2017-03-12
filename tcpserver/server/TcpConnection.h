#ifndef _MY_TCPCONNECTION_H_
#define _MY_TCPCONNECTION_H_
#include "Noncopy.h"
#include "Socket.h"
#include "SocketIO.h"
#include "InetAddress.h"
#include <string>

class TcpConnection:Noncopy
{
public:
	TcpConnection(int fd);
	~TcpConnection();

	string	receive();
	void send(const string& msg);
	void shutdown();

	string tostring();
private:
	Socket _sock;
	SocketIO _sockIO;
	InerAddress _localaddr;
	InerAddress _peeraddr;
	bool _isShutdownWite;
};
#endif