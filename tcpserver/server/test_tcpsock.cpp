#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"
#include "TcpConnection.h"
#include <iostream>
#include <string.h>
#include <string>

using namespace std;

int main()
{
	Socket sock;
	string str;
	char buf[1024];
	InerAddress addr(5666);
	sock.ready(addr);

	int peerfd = sock.accept();
	
	cout<<"client connect succed"<<endl;

	TcpConnection conn(peerfd);
	cout<<conn.tostring()<<endl;
	conn.send("welcome server\n");
	while(1)
	{
		str.clear();
		str = conn.receive();
		cout<<str<<endl;
		if(str.compare("byebye") == 0)
		{
			break;
		}
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),stdin);
		str.clear();
		str = buf;
		conn.send(str);
	}

	return 0;
}
