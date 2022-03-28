#include "utils.h"

int socket_with_error_handler(int domain, int type, int protocol){
    int res = 0;
    res = socket(domain, type, protocol);
    if (res == -1){
        perror("Error: ");
        exit(EXIT_FAILURE);
    }
    return res;
}

void bind_with_error_handler(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
    int res = 0;
    res = bind(sockfd, addr, addrlen);
    if (res == -1){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

int Accept(int sockfd, struct sockaddr *adr, socklen_t *addrlen){
    int res = accept(sockfd, adr, addrlen);
    if(res == -1){
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void listen_with_error_handler(int sockfd, int backlog){
    int res = listen(sockfd, backlog);
    if (res == -1){
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}