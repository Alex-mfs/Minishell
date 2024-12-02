CC = cc

CFLAGS = -Wall -Werror -Wextra

AR = ar -rc

RM = rm -rf

# TEXT COLOR
GREEN = \033[92m
RESET = \033[0m

NAME = libft.a

# FOLDER PRINTF
FOLDER1 = FT_PRINTF

# FOLDER GET_NEXT_LINE
FOLDER2 = GET_NEXT_LINE

# SOURCE FOLDER
SRCFOLDER = src

# OBJS FOLDER
OBJFOLDER = obj

SRC = $(wildcard $(SRCFOLDER)/*.c)

OBJS = $(patsubst $(SRCFOLDER)/%.c, $(OBJFOLDER)/%.o, $(SRC))
OBJS2 = $(wildcard $(FOLDER1)/$(OBJFOLDER)/*.o)
OBJS3 = $(wildcard $(FOLDER2)/$(OBJFOLDER)/*.o)

TRIGGER_HEADERS = $(SRCFOLDER)/libft.h

all: $(NAME)

$(NAME): $(TRIGGER_HEADERS) $(OBJS) other_objs
	$(AR) $(NAME) $(OBJS) $(OBJS2) $(OBJS3)
	ranlib $(NAME)
	@echo "[$(GREEN)SUCCESS$(RESET)] LIBFT - $(NAME) CREATED."
	
$(OBJFOLDER)/%.o: $(SRCFOLDER)/%.c $(TRIGGER_HEADERS)
	@mkdir -p $(OBJFOLDER)
	$(CC) $(CFLAGS) -c $< -o $@ -pg

other_objs:
	make -C $(FOLDER1)
	make -C $(FOLDER2)

clean:
	make clean -C $(FOLDER1)
	make clean -C $(FOLDER2)
	$(RM) $(OBJFOLDER)
	@echo "[$(GREEN)SUCCESS$(RESET)] LIBFT - ALL OBJS DELETED."
	
fclean: clean
	make fclean -C $(FOLDER1)
	make fclean -C $(FOLDER2)
	$(RM) $(NAME)
	@echo "[$(GREEN)SUCCESS$(RESET)] LIBFT - LIBRARY DELETED."

re: fclean all

.SILENT:

.PHONY: all clean fclean re other_objs
