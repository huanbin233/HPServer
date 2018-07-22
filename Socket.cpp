#include "Socket.h"
#include "InetAddress.h"
Socket::Socket()
:sockfd_(::socket(PF_INET,SOCK_STREAM,0))
{
    assert(sockfd_ != -1);
    fcntl(sockfd_,F_SETFL,O_NONBLOCK);
}
Socket::~Socket()
{
    ::close(sockfd_);
}
void Socket::bindAddress(const InetAddress &localAddress)
{
    assert(::bind(sockfd_,localAddress.getSockAddr(),localAddress.getSockAddrLength()) != -1);
}
void Socket::listen()
{
    assert(::listen(sockfd_,SOMAXCONN) != -1);
}
Socket Socket::accept(InetAddress *peerAddress)
{
    struct sockaddr_in adr;
    socklen_t len;
    const int connfd = ::accept4(sockfd_,(struct sockaddr*)&adr,&len,SOCK_NONBLOCK|SOCK_CLOEXEC);
    assert(connfd != -1);
    if(peerAddress!=nullptr)
        peerAddress = new InetAddress(adr);
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
