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
#include <sys/sendfile.h>
#include <stdint.h> 
#include <inttypes.h>
#include <sys/uio.h>
#include <string.h>
#include <dirent.h>

typedef struct s_client_data{
    int port;
    char *address;
    char *file_path;
    char *name_to_save_file;
    char *filename_len;
}              t_client_data;



typedef struct s_args{
    int port;
    char* directory;
}               t_args;

int socket_wrap(int domain, int type, int protocol);

void bind_wrap(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int accept_wrap(int sockfd, struct sockaddr *adr, socklen_t *addrlen);

void listen_wrap(int sockfd, int backlog);

char	*strjoin(char const *s1, char const *s2);

char	*itoa(int n);

void get_client_data(int argc, char **argv, t_client_data *data);

void clean_client_data(t_client_data * data);

void connect_wrap(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

void inet_pton_wrap(int af, const char *src, void *dst);

int open_wrap(char *name);

void sendfile_wrap(int client_fd, int file_fd);

void send_filename(int client_fd, t_client_data *data);

void init_client_data(t_client_data *data);

int64_t get_filesize(int file_fd);

void get_args(int argc, char **argv, t_args *args);

char	*strnew(size_t len);

void clean_args(t_args *args);