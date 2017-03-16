 ///
 /// @file    TcpServer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-24 10:28:34
 ///
 
#include "TcpServer.h"

namespace wd
{

TcpServer::TcpServer(unsigned short port)
: _sock()
, _epoll(_sock.fd())
{
	InetAddress addr(port);
	_sock.ready(addr);
}

TcpServer::TcpServer(const char * ip, unsigned short port)
: _sock()
, _epoll(_sock.fd())
{
	InetAddress addr(ip, port);
	_sock.ready(addr);
}

void TcpServer::start()
{
	_epoll.loop();
}

void TcpServer::stop()
{
	_epoll.unloop();
}

void TcpServer::setConnectionCallback(TcpServerCallback cb)
{
	_onConnection = cb;
}

void TcpServer::setMessageCallback(TcpServerCallback cb)
{
	_onMessage = cb;
}

void TcpServer::setCloseCallback(TcpServerCallback cb)
{
	_onClose = cb;
}

}// end of namespace wd
