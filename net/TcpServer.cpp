//
// Created by james on 2023/2/3.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "TcpServer.h"

#include <unistd.h>
#include <iostream>

using namespace std;

TcpServer::TcpServer(int listenPort) {
    this->port = listenPort;
    this->listen_sock = createSock();
    epollInit(this->listen_sock);
}

void TcpServer::epollInit(int listen_sock) {
    setNoBlock(listen_sock);
    this->epollFd = epoll_create(maxEpollEvent);
    if (this->epollFd < 0) {
        exit(-1);
    }

    struct epoll_event ep_event;
    ep_event.events = EPOLLIN;
    ep_event.data.fd = listen_sock;

    if (epoll_ctl(this->epollFd, EPOLL_CTL_ADD, listen_sock, &ep_event) < 0) {
        throw "fail to set epoll ctl on sock:" + listen_sock;
    }
}

void TcpServer::setNoBlock(int listen_sock) const {
    fcntl(listen_sock, F_SETFL, fcntl(listen_sock, F_GETFL) | O_NONBLOCK);
}

int TcpServer::createSock() const {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        throw "create socket error.";
    }

    int opt = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        throw "set opt SO_REUSEADDR error. ";
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    int ret = bind(sock, (struct sockaddr *) &addr, sizeof(addr));
    if (ret < 0) {
        throw "bind on port error:" + port;
    }

    if (listen(sock, 5) < 0) {
        throw "listen socket fail." + this->port;
    }
    return sock;
}

void TcpServer::start() {
    const int maxNum = 512;
    struct epoll_event ready_ev[maxNum];
    int timeout = 1000;

    while (true) {
        int ret = epoll_wait(this->epollFd, ready_ev, maxNum, timeout);
        switch (ret) {
            case -1:
            case 0:
                break;
            default:
                for (int i = 0; i < ret; i++) {
                    int fd = ready_ev[i].data.fd;
                    //handle connect events
                    if (fd == this->listen_sock && (ready_ev[i].events && EPOLLIN)) {
                        struct sockaddr_in client;
                        socklen_t len = sizeof(client);
                        int client_sock = accept(this->listen_sock, (struct sockaddr *) &client, &len);
                        if (client_sock < 0) {
                            std::cerr << "fail to create client sock." << std::endl;
                        }
                        setNoBlock(client_sock);

                        struct epoll_event ev;
                        ev.events = EPOLLIN | EPOLLOUT;
                        ev.data.fd = client_sock;

                        epoll_ctl(this->epollFd, EPOLL_CTL_ADD, client_sock, &ev);

                    } else {
                        //handle socket read and write events.
                        if (ready_ev[i].events && EPOLLIN) {
                            char header[4];
                            memset(header, '\0', sizeof(header));
                            int readBytes = read(fd, header, sizeof(header));
                            if (readBytes < 4) {
                                continue;
                            }

                            int magic = ((header[0] & 0xFF) << 8) | (header[1] & 0xFF);
                            if (magic != MAGIC_NUM) {
                                std::cout << "wrong magic num:" + magic << endl;
                                close(listen_sock);
                            }

                            int len = ((header[2] & 0xFF) << 8) | (header[3] & 0xFF);

                            char data[len];
                            read(fd, data, len);
                            printf("the result is :%s\n", data);

                            char *response = "resonse!!!";
                            //send response...
                            sendResponse(fd, response);

//                            close(listen_sock);
                        } else if (ready_ev[i].events && EPOLLOUT) {
                            std::cout << "receive  write events." << endl;
                        }
                    }
                }
        }
    }


}

void TcpServer::sendResponse(int fd, char *response) const {
    char sendHeader[4];
    size_t dataLen = strlen(response);
    sendHeader[0] = 0xAA;
    sendHeader[1] = 0xBB;
    sendHeader[2] = ((dataLen << 16) >> 24) & 0xFF;
    sendHeader[3] = ((dataLen << 24) >> 24) & 0xFF;;

    write(fd, sendHeader, 4);
    write(fd, response, dataLen);
}
