# FLAGS
MAKEFLAGS += -s

CC = cc

CFLAGS = -Wall -Werror -Wextra

AR = ar -rc

RM = rm -rf

SUPR_FILE = valgrind_supression

# TEXT COLOR
GREEN = \033[92m
RESET = \033[0m

NAME = minishell

# LIBRARIES
LIBFOLDER = LIBFT
LIBNAME = $(LIBFOLDER)/libft.a

# SOURCE FOLDERS
SRCFOLDER_PARSER = source/parser
SRCFOLDER_EXECUT = source/execution
SRCFOLDER_INITCL = source/init_close
SRCFOLDER_ERRORH = source/error_handling
SRCFOLDER_BUILTIN = source/built_in
SRCFOLDER_ENVIRONMENT = source/environment
SRCFOLDER_SIGNALS = source/signals

# OBJS FOLDERS
OBJFOLDER_PARSER = source/obj_parser
OBJFOLDER_EXECUT = source/obj_execution
OBJFOLDER_INITCL = source/obj_init_close
OBJFOLDER_ERRORH = source/obj_error_handling
OBJFOLDER_BUILTIN = source/obj_built_in
OBJFOLDER_ENVIRONMENT = source/obj_environment
OBJFOLDER_SIGNALS = source/obj_signals

# HEADERS FOLDER
HEADFOLDER = includes

SRC_PARSER = $(wildcard $(SRCFOLDER_PARSER)/*.c)
SRC_EXECUT = $(wildcard $(SRCFOLDER_EXECUT)/*.c)
SRC_INITCL = $(wildcard $(SRCFOLDER_INITCL)/*.c)
SRC_ERRORH = $(wildcard $(SRCFOLDER_ERRORH)/*.c)
SRC_BUILTIN = $(wildcard $(SRCFOLDER_BUILTIN)/*.c)
SRC_ENVIRONMENT = $(wildcard $(SRCFOLDER_ENVIRONMENT)/*.c)
SRC_SIGNALS = $(wildcard $(SRCFOLDER_SIGNALS)/*.c)

OBJS_PARSER = $(patsubst $(SRCFOLDER_PARSER)/%.c, $(OBJFOLDER_PARSER)/%.o, $(SRC_PARSER))
OBJS_EXECUT = $(patsubst $(SRCFOLDER_EXECUT)/%.c, $(OBJFOLDER_EXECUT)/%.o, $(SRC_EXECUT))
OBJS_INITCL = $(patsubst $(SRCFOLDER_INITCL)/%.c, $(OBJFOLDER_INITCL)/%.o, $(SRC_INITCL))
OBJS_ERRORH = $(patsubst $(SRCFOLDER_ERRORH)/%.c, $(OBJFOLDER_ERRORH)/%.o, $(SRC_ERRORH))
OBJS_BUILTIN = $(patsubst $(SRCFOLDER_BUILTIN)/%.c, $(OBJFOLDER_BUILTIN)/%.o, $(SRC_BUILTIN))
OBJS_ENVIRONMENT = $(patsubst $(SRCFOLDER_ENVIRONMENT)/%.c, $(OBJFOLDER_ENVIRONMENT)/%.o, $(SRC_ENVIRONMENT))
OBJS_SIGNALS = $(patsubst $(SRCFOLDER_SIGNALS)/%.c, $(OBJFOLDER_SIGNALS)/%.o, $(SRC_SIGNALS))

OBJS = $(OBJS_PARSER) $(OBJS_EXECUT) $(OBJS_INITCL) $(OBJS_ERRORH) $(OBJS_BUILTIN) $(OBJS_ENVIRONMENT) $(OBJS_SIGNALS)

HEADER = $(HEADFOLDER)/minishell.h

all: $(NAME)

$(NAME): $(OBJS) $(HEADER) $(LIBNAME)
	$(CC) $(CFLAGS) $(OBJS) $(LIBNAME) -o $(NAME) -lreadline -g
	@echo "[$(GREEN)SUCCESS$(RESET)] MINISHELL - $(NAME) CREATED."
	
$(OBJFOLDER_PARSER)/%.o: $(SRCFOLDER_PARSER)/%.c $(HEADER)
	@mkdir -p $(OBJFOLDER_PARSER)
	$(CC) $(CFLAGS) -c $< -o $@ -g

$(OBJFOLDER_EXECUT)/%.o: $(SRCFOLDER_EXECUT)/%.c $(HEADER)
	@mkdir -p $(OBJFOLDER_EXECUT)
	$(CC) $(CFLAGS) -c $< -o $@ -g

$(OBJFOLDER_BUILTIN)/%.o: $(SRCFOLDER_BUILTIN)/%.c $(HEADER)
	@mkdir -p $(OBJFOLDER_BUILTIN)
	$(CC) $(CFLAGS) -c $< -o $@ -g

$(OBJFOLDER_INITCL)/%.o: $(SRCFOLDER_INITCL)/%.c $(HEADER)
	@mkdir -p $(OBJFOLDER_INITCL)
	$(CC) $(CFLAGS) -c $< -o $@ -g

$(OBJFOLDER_ERRORH)/%.o: $(SRCFOLDER_ERRORH)/%.c $(HEADER)
	@mkdir -p $(OBJFOLDER_ERRORH)
	$(CC) $(CFLAGS) -c $< -o $@ -g

$(OBJFOLDER_ENVIRONMENT)/%.o: $(SRCFOLDER_ENVIRONMENT)/%.c $(HEADER)
	@mkdir -p $(OBJFOLDER_ENVIRONMENT)
	$(CC) $(CFLAGS) -c $< -o $@ -g

$(OBJFOLDER_SIGNALS)/%.o: $(SRCFOLDER_SIGNALS)/%.c $(HEADER)
	@mkdir -p $(OBJFOLDER_SIGNALS)
	$(CC) $(CFLAGS) -c $< -o $@ -g

$(LIBNAME):
	make -C $(LIBFOLDER)

valgrind: 
	$(file > $(SUPR_FILE),$(SUPRESSION_FILE_BODY))
	@valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=$(SUPR_FILE) --tool=memcheck ./$(NAME)
	$(RM) $(SUPR_FILE)

define SUPRESSION_FILE_BODY
{
   name
   Memcheck:Leak
   fun:*alloc
   ...
   obj:*/libreadline.so.*
   ...
}
{
    leak readline
    Memcheck:Leak
    ...
    fun:readline
}
{
    leak add_history
    Memcheck:Leak
    ...
    fun:add_history
}
endef

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJFOLDER_PARSER) $(OBJFOLDER_EXECUT) $(OBJFOLDER_INITCL) $(OBJFOLDER_ERRORH) \
	$(OBJFOLDER_BUILTIN) $(OBJFOLDER_ENVIRONMENT) $(OBJFOLDER_SIGNALS)
	make clean -C $(LIBFOLDER)
	@echo "[$(GREEN)SUCCESS$(RESET)] MINISHELL - ALL OBJS DELETED."

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFOLDER)
	@echo "[$(GREEN)SUCCESS$(RESET)] MINISHELL - PROGRAM DELETED."

re: fclean all

.PHONY: all clean fclean re
