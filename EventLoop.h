#ifndef _EVENTLOOP_H
#define _EVENTLOOP_H

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <vector>
#include "Channel.h"
#include "Poller.h"

class Poller;
class Channel;
class EventLoop:public boost::noncopyable
{
public:
    EventLoop();
    ~EventLoop();
    void loop();
    void quit();
    void updateChannel(Channel *channel);
private:
    typedef std::vector<Channel*> ChannelList;
    ChannelList activeChannels_;
    boost::scoped_ptr<Poller> poller_;
    bool quit_;
};
#endif
