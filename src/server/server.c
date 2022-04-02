#include "../../includes/client_server.h"

void check_directory(t_args *args){
    DIR *d;
    d = opendir(args->directory);
    if (d == NULL){
        perror("directory error");
        exit(EXIT_FAILURE);
    }
    closedir(d);
}

char *get_filename(int fd, t_args *args){
    char minibuf[2];
    char buf[256] = {0};
    bzero(minibuf, 2);
    char *len_of_name = strnew(0);
    char *tmp = NULL;
    while (minibuf[0] != ' ')
    {
        read(fd, minibuf, 1);
        minibuf[1]='\0';
        tmp = len_of_name;
        len_of_name = strjoin(len_of_name, minibuf);
        if (tmp != NULL)
            free(tmp);
    }
    tmp = NULL;
    bzero(minibuf, 2);
    read(fd, buf, atoi(len_of_name));
    char *filename = strdup(buf);
    bzero(buf, 256);
    tmp = strjoin(args->directory, "/");
    char *path = strjoin(tmp, filename);
    free(len_of_name);
    free(tmp);
    free(filename);
    return path;
}

void copy_file(int fd, int file_fd){
    int flag = 0;
    char buf[256];
    ssize_t nread = 0;

    while(flag == 0){
    nread = read(fd, buf, 256);
    if (nread  == -1){
        perror("read failure");
        exit(EXIT_FAILURE);
    }
    if (nread == 0){
        printf("End of file occured\n");
        flag = 1;
        break;
    }
    write(file_fd, buf, nread);
    }
}

int main(int argc, char** argv){
    t_args args;
    get_args(argc, argv, &args);
    check_directory(&args);
    int fd = 0;
    int file_fd = 0;
    int server_fd = 0;

    server_fd = socket_wrap(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0}; ///// memset?
    adr.sin_family = AF_INET;
    adr.sin_port = htons(args.port); 
    
    bind_wrap(server_fd, (struct sockaddr*)&adr, sizeof(adr));
    listen_wrap(server_fd, 5);
    socklen_t addrlen = sizeof(adr);
    fd = accept_wrap(server_fd, (struct sockaddr*)&adr, &addrlen);

    char *path = get_filename(fd, &args);
    
    file_fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    copy_file(fd, file_fd);
    close(file_fd);
    sleep(1);
    close(fd);
    close(server_fd);
    clean_args(&args);
    free(path);
    return 0;
}