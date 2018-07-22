#ifndef _ACCEPTOR_H_
#define _ACCEPTOR_H_

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include "Channel.h"
#include "Socket.h"

class EventLoop;

class Acceptor:public boost::noncopyable
{
public:
    typedef boost::function<void(int,const InetAddress &)> NewConnectionCallback;
    Acceptor(EventLoop* loop,const InetAddress &listenAddr);
    void setNewConnectionCallback(const NewConnectionCallback& cb);
    {newConnectionCallback_ = cb;}
    bool listenning() const{return listenning_;}
    void listen();
private:
    void handleRead();
    EventLoop *loop_;
    Socket acceptSocket_;
    Channel acceptChannel_;
    NewConnectionCallback newConnectionCallback_;
    bool listennig_;
};
#endif
