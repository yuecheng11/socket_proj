#ifndef _MY_INETADDRESS_H_
#define _MY_INETADDRESS_H_
#include <netinet/in.h>
#include <iostream>
#include <string>


using namespace std;

class InerAddress
{
public:
	InerAddress(unsigned short port);
	InerAddress(const char* ip,unsigned short port);
	InerAddress(const struct sockaddr_in& addr);

	struct sockaddr_in* getInetAddressPtr();
	string getIp();
	unsigned short getPort();
	
	
private:
	struct sockaddr_in _addr;
};

#endif