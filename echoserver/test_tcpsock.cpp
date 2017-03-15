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
void AcceptConn(Socket listensock,int events,void *arg)
{
	//client addr
	struct sockaddr_in sin;
	socklen_t len = sizeof(struct sockaddr_in);
	int listenfd = listensock.getfd();
	int nclientfd,i;
	nclientfd = listensock.accept();
	if(nclientfd < 0)
	{
		cout<<"accept clint error"<<endl;
		return;
	}
	do
	{
		for(i = 0 ;i < )
	}
}

int main(int argc,char** argv)
{
	unsigned short port = 12345;
	if(argc != 2)
	{
		cout<<"param error in main"<<endl;
		exit(-1);
	}
	port = atoi(argv[1]);
	
	InerAddress addr(port);
	
	//create socket;
	Socket listensock;  
	listensock.ready(addr);

	TcpConnection conn(listensock);
	
	
	EpollPoller epoolInstance;
	epoolInstance.AddListenSock(listensock.getfd());
	

	return 0;
}
