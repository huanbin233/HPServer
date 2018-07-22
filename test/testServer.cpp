#include "Socket.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
int main(int argc, char **argv)
{
    Socket listenfd;
    listenfd.bindAddress(adr);
    listenfd.listen();

    char buf[1024];
    while(1)
    {
        Socket connfd = listenfd.accept();

        int ret = recv(connfd.fd(),buf,sizeof(buf)-1,0);
        if(ret <= 0)
        {
            break;
        }
        buf[ret] = '\0';
        send(connfd.fd(),buf,sizeof(buf),0);
    }
    return ;

}