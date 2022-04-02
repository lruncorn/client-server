#include "../../includes/client_server.h"

int main(int argc, char **argv){
    
    t_client_data data;
    int client_fd = 0;
    int file_fd = 0;
    struct sockaddr_in adr;
    memset(&adr, 0, sizeof(adr));

    get_client_data(argc, argv, &data);

    client_fd = socket_wrap(AF_INET, SOCK_STREAM, 0);
    adr.sin_family = AF_INET;
    adr.sin_port = htons(data.port);
    inet_pton_wrap(AF_INET, data.address, &adr.sin_addr);
    connect_wrap(client_fd, (struct sockaddr *)&adr, sizeof(adr));

    send_filename(client_fd, &data);
    file_fd = open_wrap(data.file_path);
    sendfile_wrap(client_fd, file_fd);

    close(file_fd);
    close(client_fd);
    clean_client_data(&data);
    return 0;
}