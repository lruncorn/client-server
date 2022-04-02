#include "../../includes/client_server.h"

void clean_args(t_args *args){
    if(args->directory != NULL){
        free(args->directory);
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