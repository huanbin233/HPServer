/*************************************************************************
	> File Name: test1.cpp
	> Author: 
	> Mail: 
	> Created Time: Thursday, July 19, 2018 PM11:32:39 CST
 ************************************************************************/

#include<iostream>
#include <sys/timerfd.h>
#include "EventLoop.h"
#include "Channel.h"
#include "Poller.h"
using namespace std;

EventLoop *g_loop;
void timeout()
{
    printf("Timeout\n");
    g_loop->quit();
}
int main()
{
    EventLoop loop;
    g_loop = &loop;

    int timerfd = ::timerfd_create(CLOCK_MONOTONIC,TFD_NONBLOCK|TFD_CLOEXEC);
    Channel channel(&loop,timerfd);
    channel.setReadCallback(timeout);
    channel.enableReading();

    struct itimerspec howlong;
    bzero(&howlong,sizeof(howlong));
    howlong.it_value.tv_sec = 5;
    ::timerfd_settime(timerfd,0,&howlong,NULL);

    loop.loop();
    ::close(timerfd);
}
