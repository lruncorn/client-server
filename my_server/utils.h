#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>

#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
// #include <sys/sendfile.h>
#include <stdint.h> // для int64_t
#include <inttypes.h> // для правильного вывода int64_t в printf

//  #include <sys/types.h>
    //  #include <sys/socket.h>
     #include <sys/uio.h>
     #include <string.h>
     #include <dirent.h>

typedef struct s_client_data{
    int port;
    char *address;
    char *file_path;
    char *name_to_save_file;
}              t_client_data;



typedef struct s_args{
    int port;
    char* directory;
}               t_args;

int socket_with_error_handler(int domain, int type, int protocol);

void bind_with_error_handler(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Accept(int sockfd, struct sockaddr *adr, socklen_t *addrlen);

void listen_with_error_handler(int sockfd, int backlog);

char	*strjoin(char const *s1, char const *s2);