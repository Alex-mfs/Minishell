NAME = minishell
#BONUS_NAME = minishell_bonus
CC = cc
FLAGS = -Wall -Wextra -Werror
LFT_FLAGS = -lft
RM = rm -fr
MAIN = minishell.c
#BONUS = minishell_bonus.c
SRC = Utils/*.c Parse/*.c Execution/*.c Commands/*.c
SRC_LFT = libft
OBJ = obj/*.o
#BONUS_SRC = libft/*.c Bonus/*.c
#BONUS_OBJ = obj_bonus/*.o

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -L $(SRC_LFT) $(LFT_FLAGS) -lreadline -o $(NAME)

#$(BONUS_NAME): $(BONUS_OBJ)
#	@$(CC) $(FLAGS) $(BONUS_OBJ) -L $(SRC_LFT) $(LFT_FLAGS) -o $(BONUS_NAME)

$(OBJ): $(MAIN) $(SRC)
#	@git clone git@github.com:joao-rib/JP_libft.git libft
	@make -C $(SRC_LFT) -s
	@mkdir -p obj
	@$(CC) $(FLAGS) -c $(SRC) $(MAIN)
	@mv *.o obj/

#$(BONUS_OBJ): $(BONUS) $(BONUS_SRC)
#	@git clone git@github.com:joao-rib/JP_libft.git libft
#	@make -C $(SRC_LFT) -s
#	@mkdir -p obj_bonus
#	@$(CC) $(FLAGS) -c $(BONUS_SRC) $(BONUS)
#	@mv *.o obj_bonus/

clean:
	@$(RM) $(OBJ) $(BONUS_OBJ) obj obj_bonus
	@make clean -C $(SRC_LFT) -s

fclean:
	@$(RM) $(OBJ) $(BONUS_OBJ) $(NAME) $(BONUS_NAME) obj obj_bonus
	@make fclean -C $(SRC_LFT) -s
#	@$(RM) libft

re: fclean all

bonus_re: fclean bonus
