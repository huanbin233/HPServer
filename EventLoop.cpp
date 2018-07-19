#include "EventLoop.h"

EventLoop::EventLoop()
{}
EventLoop::~EventLoop()
{}

void EventLoop::loop()
{
    while(true)
    {
        activeChannels_.clear();
        poller_->poll(60,&activeChannels_);
        for(auto &it:activeChannels_)
        {
            (*it)->handleEvent();
        }
    }
}
 void EventLoop::updateChannel(Channel *channel)
 {
     poller_->updateChannel(channel);
 }