#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"
#include "TcpConnection.h"
#include "EpollPoller.h"
#include <iostream>
#include <string.h>
#include <string>
#include <signal.h>


using namespace std;

int main()
{
	signal(SIGPIPE,SIG_IGN);
	Socket sock;
	//string str;
	char buf[1024];
	InerAddress addr(5666);
	sock.ready(addr);

	EpollPoller epoller(sock.getfd());
	epoller.loop();



	return 0;
}
