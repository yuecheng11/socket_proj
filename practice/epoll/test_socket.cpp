 ///
 /// @file    test_socket.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-22 14:54:59
 ///
 
#include "Socket.h"
#include "InetAddress.h"
#include "TcpConnection.h"
#include "EpollPoller.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>

using std::cout;
using std::endl;

void onConnection(wd::TcpConnectionPtr conn)
{
	cout << conn->toString() << "has connected!" << endl;
	conn->send("welcome to server.");
}

void onMessage(wd::TcpConnectionPtr conn)
{
	std::string msg = conn->receive();
	conn->send(msg);
}

void onClose(wd::TcpConnectionPtr conn)
{
	cout << conn->toString() << " hase close." << endl;
}

int main(void)
{
	wd::Socket sock;
	wd::InetAddress addr(8888);
	sock.ready(addr);

	wd::EpollPoller epollPoller(sock.fd());
	epollPoller.setConnectionCallback(onConnection);
	epollPoller.setMessageCallback(onMessage);
	epollPoller.setCloseCallback(onClose);

	epollPoller.loop();

#if 0
	int peerfd = sock.accept();
	wd::TcpConnection conn(peerfd);
	std::cout << conn.toString() << std::endl;
	conn.send("welcome to server");
	while(true)
	{
		std::string s1 = conn.receive();
		conn.send(s1);
	}
#endif
	return 0;
}
