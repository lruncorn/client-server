PATH_SRC = src
CLIENT = client
SERVER = server

UTILS = ./src/utils.c ./src/wrappers.c
FILES_S = ./src/server/server.c ./src/server/get_server_data.c 
FILES_C = ./src/client/client.c ./src/client/get_client_data.c 

OBJ_UTILS = $(UTILS:.c=.o)
OBJ_SERVER = $(FILES_S:.c=.o)
OBJ_CLIENT = $(FILES_C:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra #-g -fsanitize=address
RM = rm -rf

all: $(CLIENT) $(SERVER)


$(CLIENT): $(OBJ_CLIENT) $(OBJ_UTILS)
	@$(CC) $(CFLAGS) $(OBJ_CLIENT)  $(OBJ_UTILS) -o $(CLIENT)
	@echo client done!!

$(SERVER): $(OBJ_SERVER) $(OBJ_UTILS)
	@$(CC) $(CFLAGS) $(OBJ_SERVER) $(OBJ_UTILS) -o $(SERVER)
	@echo server done!!

bonus: all

clean:
	@$(RM) $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_UTILS)
	@echo objs clean!!

fclean:	clean
	@$(RM) server client
	@echo compiled clean!!

re: fclean all
