/*************************************************************************
	> File Name: test01.cpp
	> Author: 
	> Mail: 
	> Created Time: Thursday, July 19, 2018 PM09:21:20 CST
 ************************************************************************/

#include<iostream>
#include "EventLoop.h"
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
using namespace std;
int listenfd;
void Callback()
{
    int connfd = accept(listenfd, 0, 0);
    printf("new connection come[%d]\n",connfd);
}
int main()
{
    EventLoop *loop = new EventLoop;
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    fcntl(listenfd,F_SETFL,O_NONBLOCK);
    Channel *channel = new Channel(loop,listenfd);

    struct sockaddr_in adr;
    bzero(&adr,sizeof(adr));
    adr.sin_family = AF_INET;
    adr.sin_port = htons(8880);
    adr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listenfd,(struct sockaddr*)&adr,sizeof(adr));
    listen(listenfd,10);
    channel->setReadCallback(Callback);
    channel->enableReading();

    loop->loop();
}
