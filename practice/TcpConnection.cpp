 ///
 /// @file    TcpConnection.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-23 11:20:09
 ///
 
#include "TcpConnection.h"
#include <string.h>
#include <iostream>
#include <sstream>



namespace wd
{

TcpConnection::TcpConnection(int fd)
: _sock(fd)
, _sockIO(fd)
, _localAddr(Socket::getLocalAddr(fd))
, _peerAddr(Socket::getPeerAddr(fd))
, _isShutdownWrite(false)
{
}


TcpConnection::~TcpConnection()
{
	if(!_isShutdownWrite)
	{
		shutdown();
	}
}

std::string TcpConnection::receive()
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	_sockIO.readline(buff, 1024);
	return std::string(buff);
}

void TcpConnection::send(const std::string & msg)
{
	_sockIO.writen(msg.c_str(), msg.size());
}

void TcpConnection::shutdown()
{
	if(!_isShutdownWrite) { _isShutdownWrite = true;
		_sock.shutdownWrite();
	}
}

std::string TcpConnection::toString() const
{
	std::ostringstream oss;
	oss << _localAddr.ip() << ":" << _localAddr.port()
			  << "--->"
			  << _peerAddr.ip() <<  ":" << _peerAddr.port()
			  << " has connected!";
	return oss.str();
}


}// end of namespace wd