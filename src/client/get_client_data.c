#include "../../includes/client_server.h"

void get_client_data(int argc, char **argv, t_client_data *data){
    init_client_data(data);
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
        data->name_to_save_file = strdup(argv[4]);
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

void clean_client_data(t_client_data * data){
    if (data->address != NULL){
        free(data->address);
        data->address = NULL;
    }
    if (data->name_to_save_file != NULL){
        free(data->name_to_save_file);
        data->name_to_save_file = NULL;
    }
    if (data->filename_len != NULL){
        free(data->filename_len);
        data->filename_len = NULL;
    }
    if(data->file_path != NULL){
        free(data->file_path);
        data->file_path = NULL;
    }
}

void init_client_data(t_client_data *data){
    data->port = -1;
    data->address = NULL;
    data->file_path = NULL;
    data->name_to_save_file = NULL;
    data->filename_len = NULL;
}

int64_t get_filesize(int file_fd){
    struct stat _fileStatbuff;
    fstat(file_fd, &_fileStatbuff);
    // int64_t _file_size = 0;
    return(_fileStatbuff.st_size); 
}
