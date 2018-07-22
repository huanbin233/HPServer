/*************************************************************************
	> File Name: InetAddress.h
	> Author: 
	> Mail: 
	> Created Time: Sunday, July 22, 2018 PM02:06:52 CST
 ************************************************************************/

#ifndef _INETADDRESS_H
#define _INETADDRESS_H
#include <arpa/inet.h>
class InetAddress
{
public:
    explicit InetAddress(uint16_t port);
    InetAddress( std::string ip,uint16_t port );
    explicit InetAddress(const struct sockaddr_in &addr):addr_(addr){};
    ~InetAddress(){};
    const struct sockaddr* getSockAddr()const {return (const struct sockaddr* )&addr_;}
    int getSockAddrLength()const {return sizeof(addr_);}
private:
    struct sockaddr_in addr_;
};

#endif
