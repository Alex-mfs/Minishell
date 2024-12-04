NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -g -MMD
LFT_FLAGS = -lft
#READLINE_INC = -I/opt/homebrew/opt/readline/include
#READLINE_LIB = -L/opt/homebrew/opt/readline/lib -lreadline
RM = rm -fr
MAIN = minishell.c
SRC = Utils/*.c Parse/*.c Execution/*.c Commands/*.c
SRC_LFT = libft
OBJ = obj/*.o
DEPS = dep/*.d

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -L $(SRC_LFT) $(LFT_FLAGS) -lreadline -o $(NAME)
#	@$(CC) $(FLAGS) $(OBJ) -L $(SRC_LFT) $(LFT_FLAGS) $(READLINE_LIB) -o $(NAME)

$(OBJ): $(MAIN) $(SRC)
	@make -C $(SRC_LFT) -s
	@mkdir -p obj
	@mkdir -p dep
	@$(CC) $(FLAGS) -c $(SRC) $(MAIN)
#	@$(CC) $(FLAGS) $(READLINE_INC) -c $(SRC) $(MAIN)
	@mv *.o obj/
	@mv *.d dep/

-include $(DEPS)

clean:
	@$(RM) $(OBJ) $(DEPS) obj dep
	@make clean -C $(SRC_LFT) -s

#va : re
#	valgrind -q --suppressions=./wip_suppressions --show-leak-kinds=all --track-fds=yes --leak-check=full ./$(NAME)
fclean:
	@$(RM) $(OBJ) $(DEPS) $(NAME) $(BONUS_NAME) obj dep
	@make fclean -C $(SRC_LFT) -s
#	@$(RM) libft

re: fclean all



