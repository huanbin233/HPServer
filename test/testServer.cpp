#include "Socket.h"
#include "InetAddress.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
int main(int argc, char **argv)
{
    Socket listenfd;
    InetAddress adr(argv[1],atoi(argv[2]));
    listenfd.bindAddress(adr);
    listenfd.listen();

    char buf[1024];
    Socket connfd = listenfd.accept(nullptr);
    while(1)
    {
        int ret = recv(connfd.fd(),buf,sizeof(buf)-1,0);
        if(ret <= 0)
        {
            break;
        }
        buf[ret] = '\0';
        send(connfd.fd(),buf,strlen(buf),0);
    }
    return 0 ;

}
