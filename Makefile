NAME = minishell
LIBRARY = libft/libft.a
CC = cc
FLAGS = -Wall -Wextra -Werror #-fsanitize=address#,undefined -g -O0
LINKING_FLAGS = -lreadline
OBJECTS = main.o execution/prompt_management/manage_prompt.o execution/prompt_management/manage_prompt_utils.o \


.PHONY: all clean fclean re leak_check

all: $(NAME)

$(LIBRARY):
	$(MAKE) -C libft

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(LIBRARY) $(OBJECTS)
	   $(CC) $(FLAGS) $(OBJECTS) $(LIBRARY) $(LINKING_FLAGS) -o $(NAME)

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJECTS)

fclean:
	$(MAKE) -C libft fclean
	rm -f $(OBJECTS) $(NAME)

re: fclean all

leak_check:
	$(MAKE)
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=valgrind.supp ./minishell
