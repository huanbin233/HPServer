#ifndef _EVENTLOOP_H
#define _EVENTLOOP_H

#include <boost/noncopyable.hpp>
class Channel;
class Poller;

class EventLoop:public boost::noncopyable
{
public:
    EventLoop();
    ~EventLoop();
    void loop();
    void updateChannel(Channel *channel);
private:
    ChannelList activeChannels_;
    boost::scope_ptr<Poller> poller_;
};
#endif