//
// Created by jay on 7/21/26.
//

#include "UdpServer.hpp"

UdpServer::UdpServer() {
    if ((sockfd_ = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr_, 0, sizeof(servaddr_));
    memset(&clientaddr_, 0, sizeof(clientaddr_));

    servaddr_.sin_family = AF_INET;
    servaddr_.sin_addr.s_addr = INADDR_ANY;
    servaddr_.sin_port = htons(PORT);

    int opt = 1;
    setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(sockfd_, reinterpret_cast<const sockaddr *>(&servaddr_),
             sizeof(servaddr_)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    int flags = fcntl(sockfd_, F_GETFL, 0);
    fcntl(sockfd_, F_SETFL, flags | O_NONBLOCK);
}

void UdpServer::receive() {
    const char *hello = "Hello from server";
    socklen_t len = sizeof(clientaddr_);

    //Non-blocking, so an empty queue is the normal case and not an error
    ssize_t n = recvfrom(sockfd_, buffer_, MAXLINE - 1, 0,
                         reinterpret_cast<sockaddr *>(&clientaddr_), &len);
    if (n < 0) {
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
            perror("Recvfrom failed");
        }
        return;
    }
    buffer_[n] = '\0';

    std::cout << "Client: " << n << " " << buffer_ << std::endl;

    sendto(sockfd_, hello, strlen(hello), MSG_CONFIRM, reinterpret_cast<const sockaddr *>(&clientaddr_), len);

    std::cout << "Hello message sent" << std::endl;
}

void UdpServer::closeServer() {
    if (sockfd_ >= 0) {
        close(sockfd_);
        sockfd_ = -1;
    }
}

UdpServer::~UdpServer() {
    closeServer();
}
