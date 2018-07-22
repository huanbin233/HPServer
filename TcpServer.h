#ifndef _TCPSERVER_H_
#define _TCPSERVER_H_

#include <map>
#include <boost/scoped_ptr.hpp>
class EventLoop;
class InetAddress;

class TcpServer
{
public:
    TcpServer(EventLoop*loop,const InetAddress& listenAddr);
    ~TcpServer();
    void start();
    void setConnectionCallback(const ConnectionCallback &cb)
    {connectionCallback_ = cb;}
    void setMessageCallback(const MessageCallback &cb)
    {MessageCallback_ = cb;}
private:
    void newConnection(int sockfd,const InetAddress& peer);
    typedef std::map<std::string,TcpConnectionPtr> ConnectionMap;
    EventLoop* loop_;
    const std::string name_;
    boost::scoped_ptr<Acceptor> acceptor_;
    ConnectionCallback connectionCallback_;
    MessageCallback messageCallback_;
    bool started_;
    int nextConnId_;
    ConnectionMap connections_;
};

#endif