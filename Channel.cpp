/*************************************************************************
	> File Name: Channel.cpp
	> Author: 
	> Mail: 
	> Created Time: Thursday, July 19, 2018 AM11:20:19 CST
 ************************************************************************/

#include "Channel.h"
#include "EventLoop.h"
Channel::Channel( EventLoop *loop, int fd )
:loop_(loop),
 fd_(fd),
 events_(0),
 revents_(0),
 index_(-1)
 {}

 Channel::~Channel()
 {}

 void Channel::handleEvent()
 {
    if(revents_ & (POLLERR|POLLNVAL))
    {
        if(errorCallback_) errorCallback_();
    }
    if(revents_ & (POLLIN | POLLPRI | POLLRDHUP))
    {
        if(readCallback_) readCallback_();
    }
    if(revents_ & POLLOUT)
    {
        if(writeCallback_) writeCallback_();
    }
 }

 void Channel::update()
 {
    loop_->updateChannel(this);
 }
