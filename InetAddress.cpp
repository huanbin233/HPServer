/*************************************************************************
	> File Name: InetAddress.cpp
	> Author: 
	> Mail: 
	> Created Time: Sunday, July 22, 2018 PM02:38:07 CST
 ************************************************************************/

#include <iostream>
#include "InetAddress.h"
#include <string.h>

InetAddress::InetAddress(uint16_t port)
{
    bzero(&addr_,sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = htonl(INADDR_ANY);
}
InetAddress::InetAddress( std::string ip, uint16_t port )
{
    bzero(&addr_,sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    inet_pton(AF_INET,ip.c_str(),&addr_.sin_addr);
}
