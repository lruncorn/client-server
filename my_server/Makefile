PATH_SRC = .
CLIENT = client
SERVER = server

UTILS = ./utils.c
FILES_S = ./server.c
FILES_C = ./client.c

OBJ_UTILS = $(UTILS:.c=.o)
OBJ_SERVER = $(FILES_S:.c=.o)
OBJ_CLIENT = $(FILES_C:.c=.o)

CC = clang
CFLAGS = -Wall -Wextra -Werror
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
