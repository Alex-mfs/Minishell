NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -fr
SRC = flood_fill.c \
ft_atoi.c \
ft_atol.c \
ft_bzero.c \
ft_calloc.c \
ft_error_exit.c \
ft_error_msg.c \
ft_free_intmatrix.c \
ft_free_matrix.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdelim.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_lstadd_back.c \
ft_lstadd_front.c \
ft_lstclear.c \
ft_lstdelone.c \
ft_lstiter.c \
ft_lstlast.c \
ft_lstmap.c \
ft_lstnew.c \
ft_lstsize.c \
ft_mat_add_safe_line.c \
ft_matrix_add_line.c \
ft_matrix_dup.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_printf.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putnbr_lbase_fd.c \
ft_putnbr_ubase_fd.c \
ft_putstr_fd.c \
ft_rptcheck_str.c \
ft_smaller_int.c \
ft_split.c \
ft_str_cmp.c \
ft_str_repl_chr.c \
ft_str_repl_seg.c \
ft_strbuild.c \
ft_strchr.c \
ft_strchr_pos.c \
ft_strdup.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strmapi.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strnstr_pos.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
get_next_line.c \
ft_matrix_del_line_top.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean re
