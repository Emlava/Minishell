NAME = libft.a
CC = cc
FLAGS = -Wall -Wextra -Werror
OBJECTS = ft_abs.o ft_atoi.o ft_isalpha.o ft_itoa.o ft_memmove.o ft_putnbr_fd.o ft_strdup.o ft_strlcpy.o ft_strnstr.o \
	ft_tolower.o ft_bzero.o ft_isascii.o ft_memchr.o ft_memset.o ft_putstr_fd.o ft_striteri.o ft_strlen.o \
	ft_strrchr.o ft_toupper.o ft_calloc.o ft_hexatoi.o ft_isdigit.o ft_memcmp.o ft_putchar_fd.o ft_split.o ft_strjoin.o \
	ft_strmapi.o ft_strtrim.o ft_isalnum.o ft_isprint.o ft_memcpy.o ft_putendl_fd.o ft_strchr.o ft_strlcat.o \
	ft_strncmp.o ft_substr.o ft_printf/ft_csu_percent.o ft_printf/ft_di.o ft_printf/ft_p.o ft_printf/ft_xx.o \
	ft_printf/ft_printf.o ft_dprintf/ft_d_csu_percent.o ft_dprintf/ft_d_di.o ft_dprintf/ft_d_p.o ft_dprintf/ft_d_xx.o \
	ft_dprintf/ft_dprintf.o get_next_line/get_next_line.o get_next_line/get_next_line_utils.o ft_listlen.o \
	cleaning_functions/ft_free_str_arr.o

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS) 

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
