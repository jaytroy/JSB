//
// Created by jay on 7/21/26.
//

#ifndef JSB_UDPCLIENT_HPP
#define JSB_UDPCLIENT_HPP

#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 7777
#define MAXLINE 1024

class UdpClient {
public:
    UdpClient();
    ~UdpClient();

    //Owns a file descriptor, so copying it would double-close
    UdpClient(const UdpClient &) = delete;
    UdpClient &operator=(const UdpClient &) = delete;

    void send();
    void closeSocket();

private:
    int sockfd_ = -1;
    sockaddr_in servaddr_;
    char buffer_[MAXLINE];
    socklen_t len_;
};


#endif //JSB_UDPCLIENT_HPP
