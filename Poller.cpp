/*************************************************************************
	> File Name: Poller.cpp
	> Author: 
	> Mail: 
	> Created Time: Thursday, July 19, 2018 PM12:08:18 CST
 ************************************************************************/

#include "Poller.h"

Poller::Poller()
{

}
Poller::~Poller()
{

}
void Poller::poll( int timeout, ChannelList *activeChannels )
{
    int numEvent = poll( pollfds_.data(), pollfds_.size(), timeout );
    if( numEvent > 0 )
    {
        for( auto &pfd : pollfds )
        {
            if(numEvent <= 0) break;
            numEvent --;
            Channel *channel = channels_[pfd->fd];
            channel->set_revents(pfd->revents);
            activeChannels.push_back(channel);
        }
    }
}

void Poller::updateChannel(Channel* channel)
{
    // new one
    if(channel->index() < 0)
    {
        struct pollfd pfd;
        pfd.fd = channel->fd;
        pfd.events = channle->events;
        pfd.revents = 0;

        channels_[pfd.fd] = channel;
        pollfds_.push_back(pfd);
    }
    else
    {
        //modtify
        pollfds_[channel->index()].fd = channel.fd;
        pollfds_[channel->index()].events = channel.events;
        pollfds_[channel->index()].revents = 0;
        
    }
}
