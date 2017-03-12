#include "InetAddress.h"
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

InerAddress::InerAddress(unsigned short port)
{
	memset(&_addr,0,sizeof(struct sockaddr_in));

	_addr.sin_family = AF_INET;
	_addr.sin_port=htons(port); 
	//srvaddr.sin_addr.s_addr = inet_addr("0.0.0.0");
	_addr.sin_addr.s_addr = INADDR_ANY;
	//srvaddr.sin_addr.s_addr = inet_addr("10.2.68.120");
}
InerAddress::InerAddress(const char* ip,unsigned short port)
{
	memset(&_addr,0,sizeof(struct sockaddr_in));

	_addr.sin_family = AF_INET;
	_addr.sin_port=htons(port); 
	//srvaddr.sin_addr.s_addr = inet_addr("0.0.0.0");
	//_addr.sin_addr.s_addr = INADDR_ANY;
	_addr.sin_addr.s_addr = inet_addr(ip);
}

InerAddress::InerAddress(const struct sockaddr_in& addr)
	:_addr(addr)
{

}

struct sockaddr_in* InerAddress::getInetAddressPtr()
{
	return &_addr;
}
string InerAddress::getIp()
{
	return string(inet_ntoa(_addr.sin_addr));
}
unsigned short InerAddress::getPort()
{
	return ntohs(_addr.sin_port);
}

