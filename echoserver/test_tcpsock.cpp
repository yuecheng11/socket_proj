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
	Socket sock;  
	sock.ready(addr);

	
	EpollPoller epoolInstance;


	return 0;
}
