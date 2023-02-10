//
// Created by james on 2023/2/3.
//

#ifndef CPLUS_DEMO_TCPSERVER_H
#define CPLUS_DEMO_TCPSERVER_H

#include <sys/epoll.h>

#define MAGIC_NUM 0xAABB

class TcpServer {
public:
    TcpServer(int listenPort);

    void  start();

    ~TcpServer(){

    }

    const static int maxEpollEvent = 1024;


private:
    int port;
    int epollFd;

    int listen_sock;

    int createSock() const;

    void epollInit(int listen_sock);

    void setNoBlock(int listen_sock) const;

    void sendResponse(int fd,  char *response) const;
};



#endif //CPLUS_DEMO_TCPSERVER_H
