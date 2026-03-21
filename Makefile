NAME = minishell
LIBRARY = libft/libft.a
CC = cc
FLAGS = -Wall -Wextra -Werror
LINKING_FLAGS = -lreadline -lncurses
PARSING_OBJECTS = parsing/lexer_helper.o parsing/lexer.o parsing/start_parsing.o parsing/parse_token.o parsing/read_word.o \
parsing/signals.o parsing/syntax.o parsing/utils.o parsing/parse_token_helper.o parsing/read_word_helper.o
EXEC_OBJECTS = execution/prompt_management/manage_prompt.o execution/env_management/env_utils.o execution/builtins_management/manage_builtin.o \
execution/builtins_management/ft_echo.o execution/builtins_management/ft_cd.o execution/builtins_management/ft_pwd.o \
execution/builtins_management/ft_export_utils.o execution/builtins_management/ft_export.o execution/builtins_management/ft_unset.o \
execution/builtins_management/ft_env.o execution/builtins_management/ft_exit.o execution/define_non_reiterative_path/define_non_reiterative_path.o \
execution/executables_management/manage_executables.o execution/redirection_management/redirection_management.o \
execution/command_execution/run_simple_command.o execution/command_execution/create_pipe_and_pib_lists.o \
execution/command_execution/run_compound_command_utils.o execution/command_execution/run_compound_command.o execution/cleaning/cleaning_functions.o \
heredoc.o heredoc_helper.o execution/env_management/env_utils_helper.o execution/redirection_management/redirection_management_helper.o \
execution/prompt_management/manage_prompt_helper.o
ALL_OBJECTS = main.o $(PARSING_OBJECTS) $(EXEC_OBJECTS)

.PHONY: all clean fclean re leak_check

all: $(NAME)

$(LIBRARY):
	$(MAKE) -C libft

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(LIBRARY) $(ALL_OBJECTS)
	   $(CC) $(FLAGS) $(ALL_OBJECTS) $(LIBRARY) $(LINKING_FLAGS) -o $(NAME)

clean:
	$(MAKE) -C libft clean
	rm -f $(ALL_OBJECTS)

fclean:
	$(MAKE) -C libft fclean
	rm -f $(ALL_OBJECTS) $(NAME)

re: fclean all

leak_check:
	$(MAKE)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=valgrind.supp -s ./minishell
