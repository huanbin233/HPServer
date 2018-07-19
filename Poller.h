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
#include <sys/poll.h>
#include "Channel.h"
#include "EventLoop.h"
class Poller
{
public:
    typedef std::vector<Channel*> ChannelList;
    Poller(EventLoop *loop);
    ~Poller();
    void updateChannel(Channel* channel);
    void poll(int timeout,ChannelList *activeChannels);
private:
    void fillActiveChannel( int numEvent, ChannelList *activeChannels ) const;
private:
    typedef std::vector<struct pollfd> PollFdList;
    typedef std::map<int,Channel*> ChannelMap;
    PollFdList pollfds_;
    ChannelMap channels_;
    EventLoop* loop_;
};
#endif

