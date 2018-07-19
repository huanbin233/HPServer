/*************************************************************************
	> File Name: Channel.h
	> Author: huanbin
	> Mail: huanbin233@163.com
	> Created Time: Thursday, July 19, 2018 AM11:04:41 CST
 ************************************************************************/

#ifndef _CHANNEL_H
#define _CHANNEL_H
#include "EventLoop.h"
#include <boost/function.hpp>
#include <boost::noncopyable.hpp>
class Channel:public boost::noncopyable
{
    typedef boost::functional<void()> EventCallback;
public:
    Channel(EventLoop *loop, int fd);
    ~Channel();
    void handleEvent();
    
    void setReadCallback(const EventCallback &cb){readCallback_ = cb;}
    void setWriteCallback(const EventCallback &cb){writeCallback_ = cb;}
    void setErrorCallback(const EventCallback &cb){errorCallback_ = cb;}
    
    void set_index(int index){index_ = index;}
    void set_events(short events){events_ = events;}
    void set_revents(short revents){revents_ = revents;}

    void int fd(){return fd;}
    void short events(){return events_;}
    
    void enableReading(){events_ |= ReadEvent;}
    //
private:
    void update();
private:
    
    static const int NoneEvent = 0;
    static const int ReadEvent = POLLIN|POLLPRI ;
    static const int WriteEvent = POLLOUT;

    EventLoop *loop;
    int fd_;
    short events_;
    short revents_;
    int index_;

    EventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;
};
#endif
