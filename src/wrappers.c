#include "../includes/client_server.h"

void connect_wrap(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
    int res = connect(sockfd, addr, addrlen);
    if(res == -1){
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
}

void inet_pton_wrap(int af, const char *src, void *dst){
    int res = inet_pton(af, src, dst);
    if (res == 0){
        printf("inet_pton failed\n");
        exit(EXIT_FAILURE);
    }
    if (res == -1){
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }
}

int open_wrap(char *name){
    int file_fd = open(name, O_RDONLY);
    if (file_fd == -1){
        perror("open failed");
        exit(EXIT_FAILURE);
    }
    return(file_fd);
}

void sendfile_wrap(int client_fd, int file_fd){
    int64_t file_size = get_filesize(file_fd);
    if (sendfile(client_fd, file_fd, (off_t *)0, file_size) == -1){
        perror("sendfile error");
        exit(EXIT_FAILURE);
    };
}

int socket_wrap(int domain, int type, int protocol){
    int res = 0;
    res = socket(domain, type, protocol);
    if (res == -1){
        perror("Error: ");
        exit(EXIT_FAILURE);
    }
    return res;
}

void bind_wrap(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
    int res = 0;
    res = bind(sockfd, addr, addrlen);
    if (res == -1){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

int accept_wrap(int sockfd, struct sockaddr *adr, socklen_t *addrlen){
    int res = accept(sockfd, adr, addrlen);
    if(res == -1){
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void listen_wrap(int sockfd, int backlog){
    int res = listen(sockfd, backlog);
    if (res == -1){
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}