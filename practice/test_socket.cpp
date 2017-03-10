 ///
 /// @file    test_socket.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-22 14:54:59
 ///
 
#include "Socket.h"
#include "InetAddress.h"
#include "TcpConnection.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>


int main(void)
{
	wd::Socket sock;
	wd::InetAddress addr(8888);
	sock.ready(addr);

	int peerfd = sock.accept();
	wd::TcpConnection conn(peerfd);
	std::cout << conn.toString() << std::endl;
	conn.send("welcome to server");
	while(true)
	{
		std::string s1 = conn.receive();
		conn.send(s1);
	}
	return 0;
}
