#include "Acceptor.h"

Accpetor::Acceptor(EventLoop *loop,const InetAddress &listenAddr)
:loop_(loop),
 acceptSocket_(sockets::createNonBlockingOrDie()),
 acceptChannel_(loop,accpetSocket_.fd()),
 listenning(false) 
{
    acceptSocket_.setReuseAddr(true);
    acceptSocket_.bindAddress(listenAddr);
    acceptChannel_.setReadCallback(boost::bind(&Acceptor::handleRead,this));
}

void Acceptor::listen()
{
    listenning_ = true;
    accpetSocket_.listen();
    acceptChannel_.enableReading();
}

void Accpetor::handleRead()
{
    //loop_->assertInLoopThread()
    InetAddress peerAddr(0);
    int connfd = accpetSocket_.accpet(&peerAddr);
    if(connfd >= 0)
    {
        if(newConnectionCallback_)
        {
            newConnectionCallback_(connfd,peerAddr);
        }
        else
        {
            sockets::close(connfd);
        }
    }
}