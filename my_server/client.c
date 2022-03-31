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

void get_client_data(int argc, char **argv, t_client_data *data){
    if (argc < 4 || argc > 5){
        fprintf(stderr, "Error: wrong argument number\nUsage: ./client [server address] [server port] \
                        [file path] [name to save file on server]\n \
                        Last argument is optional\n");
        exit(EXIT_FAILURE);
    }
    if (argc == 4){
        data->name_to_save_file = "newfile";
    }
    else
        data->name_to_save_file = strdup(argv[4]); //malloc!
        if (data->name_to_save_file == NULL){
            perror("Filename parse error");
            exit(EXIT_FAILURE);
        }
    data->address = strdup(argv[1]);
    if (data->address == NULL){
        perror("Address parse error");
        exit(EXIT_FAILURE);
    }
    data->port = strtol(argv[2], NULL, 10);
    if (data->port < 1 || data->port > 65535){
        fprintf(stderr,  "Wrong port number. Approvable diapason: 1 - 65535\n");
        exit(EXIT_FAILURE);
    }
    data->file_path = strdup(argv[3]);
    if(data->file_path == NULL){
        perror("File to send parse error");
        exit(EXIT_FAILURE);
    }
}

void clean_data(t_client_data * data){
    if (data->address != NULL){
        free(data->address);
        data->address = NULL;
    }
    if (data->name_to_save_file != NULL){
        free(data->name_to_save_file);
        data->name_to_save_file = NULL;
    }
}

int main(int argc, char **argv){
    
    t_client_data data;
    get_client_data(argc, **argv, &data);
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0}; // мемсет нормальный сделай
    adr.sin_family = AF_INET;
    adr.sin_port = htons(data.port);
    
    inet_pton_wrap(AF_INET, data.address, &adr.sin_addr);
    connect_wrap(client_fd, (struct sockaddr *)&adr, sizeof(adr));

    write(client_fd, data.name_to_save_file, strlen(data.name_to_save_file)); //if...

    int file_fd = open(data.file_path, O_RDONLY);
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
    clean_data(&data);
    return 0;
}