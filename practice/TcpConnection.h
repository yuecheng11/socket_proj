 ///
 /// @file    TcpConnection.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-23 11:15:40
 ///
 
#ifndef _MY_TCPCONNECTION_H_
#define _MY_TCPCONNECTION_H_

#include "Noncopyable.h"
#include "Socket.h"
#include "SocketIO.h"
#include "InetAddress.h"
#include <string>

namespace wd
{

class TcpConnection 
: Noncopyable
{
public:
	TcpConnection(int fd);
	~TcpConnection();

	std::string receive();
	void send(const std::string & msg);
	void shutdown();

	std::string toString() const;
private:
	Socket _sock;
	SocketIO _sockIO;
	const InetAddress _localAddr;
	const InetAddress _peerAddr;
	bool _isShutdownWrite;
};

}// end of namespace wd

#endif
