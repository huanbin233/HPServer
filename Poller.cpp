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
        for( auto &channel : pollfds )
    }
}
