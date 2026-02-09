NAME = minishell
LIBRARY = libft/libft.a
CC = cc
FLAGS = -Wall -Wextra -Werror -fsanitize=address
LINKING_FLAGS = -lreadline
OBJECTS = main.o manage_prompt.o

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
	
# valgrind --leak-check=full --show-leak-kinds=all ./minishell
