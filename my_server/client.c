#include "utils.h"

void connect_erh(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
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

int main(int argc, char **argv){
    (void) argc;
    
    void get_args(int argc, char **argv);
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0}; // мемсет нормальный сделай
    adr.sin_family = AF_INET;
    // adr.sin_port = htons(34543);
    inet_pton_wrap(AF_INET, "127.0.0.1", &adr.sin_addr);
    connect_erh(client_fd, (struct sockaddr *)&adr, sizeof(adr));

    // write(client_fd, "Hello\n", 6); //if...

    int file_fd = open(argv[1], O_RDONLY);
    if (file_fd == -1){
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    struct stat _fileStatbuff;
    fstat(file_fd, &_fileStatbuff);
    int64_t _file_size = 0;
    _file_size = _fileStatbuff.st_size;
    

   if (sendfile(client_fd, file_fd, (off_t *)0, _file_size) == -1){
        perror("sendfile error");
        exit(EXIT_FAILURE);
    };

close(file_fd);
    close(client_fd);
    
    return 0;
}