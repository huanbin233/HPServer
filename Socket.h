#include <boost/noncopyable.hpp>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <netinet/in.h>
#include <netinet/tcp.h>

class InetAddress;
//class InetAddress;
//struct tcp_info;
class Socket
{
public:
    explicit Socket(int sockfd):sockfd_(sockfd){};
    Socket();
    ~Socket();
    int fd() const {return sockfd_;}
    Socket accept(InetAddress * peerAddress);
    void listen();
    void shutdownWrite();
    void bindAddress(const InetAddress& localAddress);

    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void setTcpNoDelay(bool on);
    void setKeepAlive(bool on);
private:
    const int sockfd_;
};
