#include "utils.h"

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

void send_filename(int client_fd, t_client_data *data){
    data->filename_len = itoa(strlen(data->name_to_save_file));
    write(client_fd, data->filename_len, strlen(data->filename_len));
    write(client_fd, " ", 1);
    write(client_fd, data->name_to_save_file, strlen(data->name_to_save_file));
}

void sendfile_wrap(int client_fd, int file_fd){
    int64_t file_size = get_filesize(file_fd);
    if (sendfile(client_fd, file_fd, (off_t *)0, file_size) == -1){
        perror("sendfile error");
        exit(EXIT_FAILURE);
    };
}