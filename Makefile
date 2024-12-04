INC = include

OBJ_DIR = objects

NAME = minishell
FILES = Utils/initialising.c Utils/reading.c Utils/validating.c Utils/sanitizing.c Utils/sanitizing_aux.c Utils/signaling.c Utils/handling.c \
	Parse/tokenizing.c Parse/tk_checks.c Parse/tk_listing.c Parse/expanding.c Parse/parsing.c Parse/parsing_aux.c Parse/cmd_listing.c \
	Execution/executing.c Execution/executing_aux.c Execution/executing_aux2.c Execution/executing_aux3.c Execution/path.c Execution/pipeline.c Execution/redirection.c Execution/redirection_aux.c Execution/redirection_aux2.c Execution/redirection_aux3.c \
	Commands/com_cd.c Commands/com_echo.c Commands/com_env.c Commands/com_exit.c Commands/com_unset.c Commands/com_export.c Commands/com_export_aux_1.c Commands/com_export_aux_2.c \
	minishell.c

TARGET = $(FILES:%.c=$(OBJ_DIR)/%.o)

CC = cc
RM = rm
W = -Wall -Wextra -Werror
O = -c
I = -I $(INC)
WBLOCK = --no-print-directory

LIBFT = -L ./libft -lft
READLINE = -lreadline

#  =============== RULES =====================

all: $(NAME)

$(NAME): $(OBJ_DIR) $(TARGET)
	@make $(WBLOCK) -C ./libft all
	@$(CC) $(W) $(TARGET) $(LIBFT) $(READLINE) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(W) $(I) $(O) $< -o $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@make $(WBLOCK) clean -C ./libft
	@$(RM) -rf $(OBJ_DIR)
	@echo "$(NAME): binary files deleted"

fclean: clean
	@make $(WBLOCK) fclean -C ./libft
	@$(RM) -f $(NAME)
	@echo "$(NAME): deleted"

re: fclean all

.PHONY: all clean fclean re