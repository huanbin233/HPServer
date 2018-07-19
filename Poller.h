/*************************************************************************
	> File Name: Poller.h
	> Author: 
	> Mail: 
	> Created Time: Thursday, July 19, 2018 AM11:28:22 CST
 ************************************************************************/

#ifndef _POLLER_H
#define _POLLER_H
#include <vector>
#include <map>
#include <poll.h>
#include "Channel.h"
#include "EventLoop.h"
#include <boost::noncopyable.hpp>
class Poller:public boost::noncopyable
{
public:
    typedef std::vector<Channel*> ChannelList;
    Poller();
    ~Poller();
    void updateChannel(Channel* channel);
    void poll(int timeout,ChannelList *activeChannels);
private:
    typedef std::vector<struct pollfd> PollFdList;
    typedef std::map<int,Channel*> ChannelMap;
    PollFdList pollfds_;
    ChannelMap channels_;
    EventLoop* loop_;
};
#endif

