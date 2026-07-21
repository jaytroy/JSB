//
// Created by jay on 7/21/26.
//

#ifndef JSB_UDPSERVER_HPP
#define JSB_UDPSERVER_HPP

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <errno.h>

#define PORT 7777
#define MAXLINE 1024

class UdpServer {
public:
    UdpServer();
    ~UdpServer();

    //Owns a file descriptor, so copying it would double-close
    UdpServer(const UdpServer &) = delete;
    UdpServer &operator=(const UdpServer &) = delete;

    void receive();
    void closeServer();

private:
    int sockfd_ = -1;
    char buffer_[MAXLINE];
    sockaddr_in servaddr_, clientaddr_;
};


#endif //JSB_UDPSERVER_HPP
