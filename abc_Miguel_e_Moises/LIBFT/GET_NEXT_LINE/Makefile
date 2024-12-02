CC = cc

CFLAGS = -Wall -Werror -Wextra

AR = ar -rc

RM = rm -rf

# TEXT COLOR
GREEN = \033[92m
RESET = \033[0m

# SOURCE FOLDER
SRCFOLDER = src

# OBJS FOLDER
OBJFOLDER = obj

SRC = $(wildcard $(SRCFOLDER)/*.c)

OBJS = $(patsubst $(SRCFOLDER)/%.c, $(OBJFOLDER)/%.o, $(SRC))

TRIGGER_HEADERS = $(SRCFOLDER)/get_next_line_bonus.h

all: $(TRIGGER_HEADERS) $(OBJS)
	@echo "[$(GREEN)SUCCESS$(RESET)] GET NEXT LINE - OBJS CREATED"

$(OBJFOLDER)/%.o: $(SRCFOLDER)/%.c $(TRIGGER_HEADERS)
	@mkdir -p $(OBJFOLDER)
	$(CC) $(CFLAGS) -c $< -o $@ -pg

clean:
	$(RM) $(OBJFOLDER)
	@echo "[$(GREEN)SUCCESS$(RESET)] GET NEXT LINE - ALL OBJS DELETED."

fclean: clean

re: fclean all

.SILENT:

.PHONY: all clean fclean re
