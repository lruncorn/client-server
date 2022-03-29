#include "utils.h"
// #include <string.h> 

int main(){
    int server_fd = 0;
    // int flag = 0;
    server_fd = socket_with_error_handler(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0}; ///// memset?
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543); //какой порт слушаем
    // adr.sin_addr = тут можно прописать ip adress


    bind_with_error_handler(server_fd, (struct sockaddr*)&adr, sizeof(adr));
    listen_with_error_handler(server_fd, 5);
    socklen_t addrlen = sizeof(adr);
    int fd = Accept(server_fd, (struct sockaddr*)&adr, &addrlen);

    // ssize_t nread;
    char buf[256];
    int flag = 0;
    int nread = 0;
    int file_fd = 0;
    file_fd = open("test", O_CREAT | O_RDWR);
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


    sleep(1);
    close(fd);
    close(server_fd);
    return 0;
}