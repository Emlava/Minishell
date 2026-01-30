NAME = minishell
LIBRARY = libft/libft.a
CC = cc
FLAGS = -Wall -Wextra -Werror
LINKING_FLAGS = -lreadline
OBJECTS = main.o

.PHONY: all clean fclean re

all: $(NAME)

$(LIBRARY):
	$(MAKE) -C ./libft

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(LIBRARY) $(OBJECTS)
	   $(CC) $(FLAGS) $(OBJECTS) $(LIBRARY) $(LINKING_FLAGS) -o $(NAME)

clean:
	$(MAKE) -C ./libft clean
	rm -f $(OBJECTS)

fclean:
	$(MAKE) -C ./libft fclean
	rm -f $(OBJECTS) $(NAME)

re: fclean all
	
