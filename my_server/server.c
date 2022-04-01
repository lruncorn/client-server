#include "utils.h"
#include <string.h>

void clean_args(t_args *args){
    if(args->directory != NULL){
        // free(args->directory);
        args->directory = NULL;
    }
}

void init_args(char **argv, t_args *args){
    args->port = strtol(argv[1], NULL, 10);
    if (args->port < 1 || args->port > 65535){
        fprintf(stderr,  "Wrong port number. Approvable diapason: 1 - 65535\n");
        exit(EXIT_FAILURE);
    }
    args->directory = strdup(argv[2]);
    if (args->directory == NULL){
        perror("Parse directory failure");
        exit(EXIT_FAILURE);
    }
}

void get_args(int argc, char **argv, t_args *args){
    if (argc != 3){
        fprintf(stderr,  "Wrong number of arguments!\nUsage: ./server [port] [directory to save file]\n");
        exit(EXIT_FAILURE);
    }
    init_args(argv, args);
    printf("%d\n%s\n", args->port, args->directory);
}

int main(int argc, char** argv){
    t_args args;
    
    get_args(argc, argv, &args);
    int server_fd = 0;
    server_fd = socket_with_error_handler(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0}; ///// memset?
    adr.sin_family = AF_INET;
    adr.sin_port = htons(args.port); 

    bind_with_error_handler(server_fd, (struct sockaddr*)&adr, sizeof(adr));
    listen_with_error_handler(server_fd, 5);
    socklen_t addrlen = sizeof(adr);
    int fd = Accept(server_fd, (struct sockaddr*)&adr, &addrlen);

    // ssize_t nread;
    char buf[256];
    int flag = 0;
    int nread = 0;
    int file_fd = 0;
    char minibuf[2];
    bzero(minibuf, 2);
    char *name_to_save = "";
    char *len_of_name = "";

    char *tmp = NULL;
    while (minibuf[0] != ' ')
    {
        nread = read(fd, minibuf, 1);
        minibuf[1]='\0';
        // tmp = len_of_name;
        len_of_name = strjoin(tmp, minibuf);
        // if (tmp != NULL)
            // free(tmp);
    }

    tmp = NULL;
    bzero(minibuf, 2);
    nread = read(fd, buf, atoi(len_of_name));
    char *filename = strdup(buf); //malloc
    printf("%s\n", len_of_name);// убери принтф
    printf("%s\n", buf); // убери принтф
    bzero(buf, 256);
    
    printf("%d\n", 111);
    
    DIR *d;
    d = opendir(args.directory);
    if (d == NULL){
        perror("directory error");
        exit(EXIT_FAILURE);
    }

    printf("%d\n", 222);

    // char *filename = "test"; //replace it
    tmp = strjoin(args.directory, "/"); //malloc
    char *path = strjoin(tmp, filename); //malloc
    free(tmp);


    file_fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    // write(file_fd, "hello\n", 6);

    
    
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
    close(file_fd);
    
    closedir(d);
    // free(path);
    sleep(1);
    close(fd);
    close(server_fd);
    return 0;
}