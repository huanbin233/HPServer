#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
class TcpConnection:public boost::noncopyalbe
{
public:
private:
    enum StateE{kConnecting,kConnected,};
    void setState(State s){state_=s;}
    void handleRead();

    EventLoop *loop;
    std::string name_;
    StateE state_;
    boost::scoped_ptr<Socket> socket_;
    boost::scoped_ptr<Channel> channel_;

    InetAddress loaclAddr_;
    InetAddress peerAddr_;

    ConnectionCallback connectionCallback_;
    MessageCallback messageCallback_;
};  