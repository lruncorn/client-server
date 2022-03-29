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
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0}; // мемсет нормальный сделай
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543);
    inet_pton_wrap(AF_INET, "127.0.0.1", &adr.sin_addr);
    connect_erh(client_fd, (struct sockaddr *)&adr, sizeof(adr));
    // connect_erh(client_fd, (struct sockaddr *)NULL, 0);

    write(client_fd, "Hello\n", 6); //if...

    int file_fd = open(argv[1], O_RDONLY);
    if (file_fd == -1){
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    struct stat _fileStatbuff;
    fstat(file_fd, &_fileStatbuff);
    int64_t _file_size = 0;
    _file_size = _fileStatbuff.st_size;
    
    
    

    // if (sendfile(client_fd, file_fd, 0, &_file_size, (struct sf_hdtr *)NULL, 0) == -1){
    //     perror("sendfile error");
    //     exit(EXIT_FAILURE);
    // };
char buf[256];
ssize_t nread = 0;
// while (1)
// {
//     nread = read(client_fd, buf, 256);
    
//     if (nread == -1){
//         perror("read failed");
//         exit(EXIT_FAILURE);
//     }
//     if (nread == 0){
//         printf("EOF occured\n");
//         break;
//     }
//     write(STDOUT_FILENO, buf, nread);
// }

    char buf[256];
    // ssize_t nread = read(client_fd, buf, 256);
    // if (nread == -1){
    //     perror("read failed");
    //     exit(EXIT_FAILURE);
    // }
    // if (nread == 0){
    //     printf("EOF occured\n");
    // }
    // write(STDOUT_FILENO, buf, nread);

    // int send_bytes = 0;
    // int offset = 0;
    // int remain_data = _file_size;

    // while(((send_bytes = sendfile(client_fd, file_fd,(off_t *) &offset, 256)) > 0) && (remain_data > 0)){
    //     printf("enviados: %*ld bytes\toffset: %*ld\tbytes restantes: %ld\r",sizeof(send_bytes), send_bytes, sizeof(offset), offset, remain_data);
    //     sizeof(stdout);
    //     remain_data -= send_bytes;
    // }
    char Buff[256];
    int tmp = 0;
    int k = 0;
     int file = fopen( argv[1], "r" );
            for(k = 0; (tmp = getc(file)) != EOF; k++ )
            {
                Buff[k] = (char)tmp;
                if(k == 256-2)
                {
                    Buff[k+1] = '\0';
                    send(client_fd, &Buff, 256, 0);
                    k = 0;
                }       
            }
            Buff[k] = '\0';
            send(client_fd, &Buff, 256, 0);
 
            snprintf(Buff, 256, "END");
            send(client_fd, &Buff, 256, 0); 
            fclose(file);


close(file_fd);
    close(client_fd);
    
    return 0;
}