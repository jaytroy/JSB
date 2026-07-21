//
// Created by jay on 7/21/26.
//

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "UdpClient.hpp"

#include <fcntl.h>

UdpClient::UdpClient() {
    sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd_ < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr_, 0, sizeof(servaddr_));

    servaddr_.sin_family = AF_INET;
    servaddr_.sin_port = htons(PORT);
    servaddr_.sin_addr.s_addr = inet_addr("127.0.0.1"); //loopback

    len_ = sizeof(servaddr_);

    int flags = fcntl(sockfd_, F_GETFL, 0);
    fcntl(sockfd_, F_SETFL, flags | O_NONBLOCK);
}

void UdpClient::send() {
    const char *hello = "Hello from client";
    sendto(sockfd_, hello, strlen(hello), MSG_CONFIRM,
           reinterpret_cast<const sockaddr *>(&servaddr_), sizeof(servaddr_));
    std::cout << "Hello message sent" << std::endl;
}

void UdpClient::closeSocket() {
    if (sockfd_ >= 0) {
        close(sockfd_);
        sockfd_ = -1;
    }
}

UdpClient::~UdpClient() {
    closeSocket();
}
