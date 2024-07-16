NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = src/main.c src/commands.c src/builtins.c src/utils.c
OBJ = $(SRC:.c=.o)
INCLUDE = -Iinclude

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.silent: Joao was here
