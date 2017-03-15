#include "TcpConnection.h"
#include <string.h>
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>

using namespace std;

TcpConnection::TcpConnection(int fd)
	:_sock(fd)
	,_sockIO(fd)
	,_localaddr(Socket::getLocalAddr(fd))
	,_peeraddr(Socket::getPeerAddr(fd))
	,_isShutdownWite(false)
{

}

TcpConnection::~TcpConnection()
{
	if(_isShutdownWite == false)
	{
		shutdown();
	}
}
string TcpConnection::receive()
{
	char buff[1024];
	memset(buff,0,sizeof(buff));
	_sockIO.readline(buff,sizeof(buff));
	return string(buff);
}
void TcpConnection::send(const string& msg)
{
	_sockIO.writen(msg.c_str(),msg.size());
}

void TcpConnection::shutdown()
{
	if(!_isShutdownWite)
	{
		_isShutdownWite = true;
		_sock.shutdownWrite();
	}
}

string TcpConnection::tostring() 
{
	ostringstream oss;
	oss<<"client [ "<<_localaddr.getIp()<<" : "<<_localaddr.getPort()<<"]"
		<<"---->"
		<<"server ["<<_peeraddr.getIp()<<" : "<<_peeraddr.getPort()<<"]"
		<<"has connect!";

	return oss.str();
}

