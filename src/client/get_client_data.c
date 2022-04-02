#include "../../includes/client_server.h"

int is_valid(char *str){
    int i = 0;
    if(strlen(str) == 0)
        return -1;
    while(str[i] != '\0'){
        if (str[i] == 46 || str[i]== 45 || (str[i] > 64 && str[i] < 91)\
             || (str[i] > 96 && str[i] < 122) || str[i] == 95)
            i++;
        else
            return (-1);
    }
    return 1;
}

void get_client_data(int argc, char **argv, t_client_data *data){
    init_client_data(data);
    if (argc < 4 || argc > 5){
        fprintf(stderr, "Error: wrong argument number\nUsage: ./client [server address] [server port] \
                        [file path] [name to save file on server]\n \
                        Last argument is optional\n");
        exit(EXIT_FAILURE);
    }
    if (argc == 5){
        if (is_valid(argv[4]) == -1){
            fprintf(stderr, "Error: not valid name to save file\n");
            exit(EXIT_FAILURE);
        }
        data->name_to_save_file = strdup(argv[4]);
    }
    else
        data->name_to_save_file = strdup("newfile");
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
    if (access(argv[3], 0) == -1){
        fprintf(stderr,  "File to send doesn't exist\n");
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
