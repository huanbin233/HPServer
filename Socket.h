#include <boost/noncopyable.hpp>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
//class InetAddress;
//struct tcp_info;
class Socket:public boost::noncopyable
{
public:
    explicit Socket(int sockfd):sockfd_(sockfd){};
    ~Socket();
    int fd() const {return sockfd_;}
    int accept(struct sockaddr_in *peerAddr);
    void listen();
    void shutdownWrite();
    void bindAddress(const struct sockaddr_in &localAddress);

    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void setTcpNoDelay(bool on);
    void setKeepAlive(bool on);
private:
    const int sockfd_;
};