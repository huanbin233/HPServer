#include "EventLoop.h"
#include "Channel.h"
#include "Poller.h"
EventLoop::EventLoop()
:poller_(new Poller),quit_(false)
{}
EventLoop::~EventLoop()
{}

void EventLoop::loop()
{
    while(!quit_)
    {
        activeChannels_.clear();
        poller_->poll(60,&activeChannels_);
        for( auto it = activeChannels_.begin();it!=activeChannels_.end();it++ )
        {
            (*it)->handleEvent();
        }
    }
}
void EventLoop::updateChannel(Channel *channel)
{
   poller_->updateChannel(channel);
}
void EventLoop::quit()
{
    quit_ = true;
}
