NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -g -MMD
LFT_FLAGS = -lft
#READLINE_INC = -I/opt/homebrew/opt/readline/include
#READLINE_LIB = -L/opt/homebrew/opt/readline/lib -lreadline
RM = rm -fr
MAIN = minishell.c
SRC = Utils/initialising.c Utils/reading.c Utils/sanitizing.c Utils/sanitizing_aux.c Utils/signaling.c Utils/handling.c \
      Parse/tokenizing.c Parse/tk_checks.c Parse/tk_listing.c Parse/expanding.c Parse/parsing.c Parse/parsing_aux.c Parse/cmd_listing.c \
      Execution/executing.c Execution/executing_aux.c Execution/executing_aux2.c Execution/executing_aux3.c Execution/path.c Execution/pipeline.c Execution/redirection.c Execution/redirection_aux.c Execution/redirection_aux2.c Execution/redirection_aux3.c \
      Commands/com_cd.c Commands/com_echo.c Commands/com_env.c Commands/com_exit.c Commands/com_unset.c Commands/com_export.c Commands/com_export_aux_1.c Commands/com_export_aux_2.c
SRC = Utils/initialising.c Utils/reading.c Utils/validating.c Utils/sanitizing.c Utils/sanitizing_aux.c Utils/signaling.c Utils/handling.c \
      Parse/tokenizing.c Parse/tk_checks.c Parse/tk_listing.c Parse/expanding.c Parse/parsing.c Parse/parsing_aux.c Parse/cmd_listing.c \
      Execution/executing.c Execution/executing_aux.c Execution/executing_aux2.c Execution/executing_aux3.c Execution/path.c Execution/pipeline.c Execution/redirection.c Execution/redirection_aux.c Execution/redirection_aux2.c Execution/redirection_aux3.c \
      Commands/com_cd.c Commands/com_echo.c Commands/com_env.c Commands/com_exit.c Commands/com_unset.c Commands/com_export.c Commands/com_export_aux_1.c Commands/com_export_aux_2.c
OBJ = obj/initialising.o obj/reading.o obj/validating.o obj/sanitizing.o obj/sanitizing_aux.o obj/signaling.o obj/handling.o \
      obj/tokenizing.o obj/tk_checks.o obj/tk_listing.o obj/expanding.o obj/parsing.o obj/parsing_aux.o obj/cmd_listing.o \
      obj/executing.o obj/executing_aux.o obj/executing_aux2.o obj/executing_aux3.o obj/path.o obj/pipeline.o obj/redirection.o obj/redirection_aux.o obj/redirection_aux2.o obj/redirection_aux3.o \
      obj/com_cd.o obj/com_echo.o obj/com_env.o obj/com_exit.o obj/com_unset.o obj/com_export.o obj/com_export_aux_1.o obj/com_export_aux_2.o \
      obj/minishell.o
DEPS = dep/initialising.o dep/reading.o dep/validating.d dep/sanitizing.o dep/sanitizing_aux.o dep/signaling.o dep/handling.o \
       dep/tokenizing.o dep/tk_checks.o dep/tk_listing.o dep/expanding.o dep/parsing.o dep/parsing_aux.o dep/cmd_listing.o \
       dep/executing.o dep/executing_aux.o dep/executing_aux2.o dep/executing_aux3.o dep/path.o dep/pipeline.o dep/redirection.o dep/redirection_aux.o dep/redirection_aux2.o dep/redirection_aux3.o \
       dep/com_cd.o dep/com_echo.o dep/com_env.o dep/com_exit.o dep/com_unset.o dep/com_export.o dep/com_export_aux_1.o dep/com_export_aux_2.o \
       dep/minishell.o
OBJ_ROOT = initialising.o reading.o validating.o sanitizing.o sanitizing_aux.o signaling.o handling.o \
           tokenizing.o tk_checks.o tk_listing.o expanding.o parsing.o parsing_aux.o cmd_listing.o \
           executing.o executing_aux.o executing_aux2.o executing_aux3.o path.o pipeline.o redirection.o redirection_aux.o redirection_aux2.o redirection_aux3.o \
           com_cd.o com_echo.o com_env.o com_exit.o com_unset.o com_export.o com_export_aux_1.o com_export_aux_2.o \
           minishell.o
DEPS_ROOT = initialising.d reading.d validating.d sanitizing.d sanitizing_aux.d signaling.d handling.d \
            tokenizing.d tk_checks.d tk_listing.d expanding.d parsing.d parsing_aux.d cmd_listing.d \
            executing.d executing_aux.d executing_aux2.d executing_aux3.d path.d pipeline.d redirection.d redirection_aux.d redirection_aux2.d redirection_aux3.d \
            com_cd.d com_echo.d com_env.d com_exit.d com_unset.d com_export.d com_export_aux_1.d com_export_aux_2.d \
            minishell.d
OBJ_ROOT = 
SRC_LFT = libft

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
	@mv $(OBJ_ROOT) obj/
	@mv $(DEPS_ROOT) dep/

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
