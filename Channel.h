/*************************************************************************
	> File Name: Channel.h
	> Author: huanbin
	> Mail: huanbin233@163.com
	> Created Time: Thursday, July 19, 2018 AM11:04:41 CST
 ************************************************************************/

#ifndef _CHANNEL_H
#define _CHANNEL_H
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <poll.h>

class EventLoop;
class Channel:public boost::noncopyable
{
    typedef boost::function<void()> EventCallback;
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

    int fd(){return fd_;}
    short events(){return events_;}
    int index(){return index_;}

    void enableReading(){events_ |= ReadEvent;update();}
    void enableWriting(){events_ |= WritEvent;update(); }

    void disableReading(){events_ &= ~ReadEvent;update();}
    void disableWriting(){events_ &= ~WriteEvent;update();}
    void disableAll(){events_ = NoneEvent;update();}

    bool isWriting() const {return events_ & WriteEvent;}
    bool isReading() const {return events_ & ReadEvent;}

    //
private:
    void update();
private:
    
    static const int NoneEvent = 0;
    static const int ReadEvent = POLLIN|POLLPRI ;
    static const int WriteEvent = POLLOUT;

    EventLoop *loop_;
    int fd_;
    short events_;
    short revents_;
    int index_;

    EventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;
    EventCallback closeCallback_;
};
#endif
