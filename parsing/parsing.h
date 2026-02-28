/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:38:36 by hudescam          #+#    #+#             */
/*   Updated: 2026/02/28 02:39:09 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include "../libft/libft.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				quoted;
	struct s_token	*next;
}	t_token;

typedef enum e_builtin
{
	BUILTIN_NONE,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT
}	t_builtin;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	int				quoted;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	t_builtin		builtin;
	struct s_cmd	*next;
}	t_cmd;

extern int	g_exit_status;

char			*read_word(char *line, int *i, int *quoted);
t_token			*token_new(t_token_type type, char *value);
void			token_add_back(t_token **lst, t_token *new);
t_token			*lexer(char *line);

int				is_operator(char c);
void			handle_operator(char *line, int *i, t_token **tokens);
void			handle_input_redir(char *line, int *i, t_token **tokens);
void			handle_output_redir(char *line, int *i, t_token **tokens);
int				handle_word(char *line, int *i, t_token **tokens);

int				ft_isspace(int c);
char			*ft_strjoin_free(char *s1, char *s2);
void			free_tokens(t_token *tokens);
void			free_redirs(t_redir *redir);
void			free_cmds(t_cmd *cmd);

t_redir_type	get_redir_type(t_token_type type);
void			redir_add_back(t_redir **lst, t_redir *new);
void			handle_token(t_cmd **current, t_token **tokens);

t_builtin		get_builtin_type(char *cmd);
t_cmd			*cmd_new(void);
void			add_arg(t_cmd *cmd, char *value);
void			add_redir(t_cmd *cmd, t_token *token);
t_cmd			*parse_tokens(t_token *tokens);

char			*process_double_content(char *word, char *tmp);
char			*handle_quote_case(char *word, char *line, int *i, int *quoted);
char			*handle_word_char(char *word, char *line, int *i);

char			*append_plain(char *word, char *line, int *i);
char			*append_variable(char *word, char *line, int *i);
char			*append_single_quoted(char *word, char *line, int *i);
char			*append_double_quoted(char *word, char *line, int *i);

int				check_syntax(t_token *tokens);

void			sigint_handler(int sig);
void			init_signals(void);

t_cmd			*start_parsing(char *line);

#endif