#include "Socket.h"
Socket::Socket()
{
    sockfd_ = ::socket(PF_INET,SOCK_STREAM,0);
    assert(sockfd_ != -1);
}
Socket::~Socket()
{
    ::close(sockfd_);
}
void Socket::bindAddress(const string &ip,int port)
{
    struct sockaddr_in adr;
    bzero(&adr,sizeof(adr));   
    adr.sin_family = AF_INET;
    adr.sin_port = htons(port);
    inet_pton(AF_INET,ip.c_str(),&adr.sin_addr);

    assert(::bind(sockfd_,(struct sockaddr*)&localAddress,sizeof(localAddress)) != -1);
}
void Socket::listen()
{
    assert(::listen(sockfd_,SOMAXCONN) != -1);
}
Socket Socket::accept()
{
    int connfd = accpet(sockfd_,nullptr,nullptr);
    assert(connfd != -1);
    return Socket(connfd);
}
void Socket::shutdownWrite()
{
    ::shutdown(sockfd_,SHUT_WR);
}
void Socket::setReuseAddr(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR,
               &optval, static_cast<socklen_t>(sizeof optval));
}
void Socket::setReusePort(bool on)
{
    int optval = on ? 1 : 0;
    int ret = ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT,
                &optval, static_cast<socklen_t>(sizeof optval));
    if(on)
    {
        assert(ret != -1);
    }
}
void Socket::setTcpNoDelay(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY,
               &optval, static_cast<socklen_t>(sizeof optval));
}
void Socket::setKeepAlive(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE,
               &optval, static_cast<socklen_t>(sizeof optval));
}