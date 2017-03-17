
 
#include "Socket.h"
#include "InetAddress.h"
#include "TcpConnection.h"
#include "EpollPoller.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>
#include <string>
#include <stdlib.h>



using std::cout;
using std::endl;

void onConnection(wd::TcpConnectionPtr conn)
{
	cout << conn->toString() << "has connected!" << endl;
	//conn->send("welcome to server.");
}

void onMessage(wd::TcpConnectionPtr conn)
{
	std::string msg = conn->receive();
	cout << msg << endl;
	conn->send(msg);
}

void onReadMessage(wd::TcpConnectionPtr conn)
{
	std::string msg = conn->receive();
	cout << msg << endl;
	//conn->send(msg);
}

void onWriteMessage(wd::TcpConnectionPtr conn)
{
	char buf[1024] = {0};
	memset(buf,0,sizeof(buf));
	cout<<"please send : ";
	fgets(buf,sizeof(buf),stdin);
	std::string str(buf);
	conn->send(str);
}


void onClose(wd::TcpConnectionPtr conn)
{
	cout << conn->toString() << " hase close." << endl;
}

int main()
{
	wd::Socket sock;
	wd::InetAddress addr(8888);
	sock.ready(addr);

	wd::EpollPoller epollPoller(sock.fd());
	epollPoller.setConnectionCallback(onConnection);
	//epollPoller.setMessageCallback(onMessage);
	epollPoller.setReadMessageCallback(onReadMessage);
	epollPoller.setWriteMessageCallback(onWriteMessage);
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
