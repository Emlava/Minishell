/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:38:36 by hudescam          #+#    #+#             */
/*   Updated: 2026/02/20 18:22:20 by elara-va         ###   ########.fr       */
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
	int				is_builtin;
	struct s_cmd	*next;
}	t_cmd;

extern int	g_exit_status;

char	*read_word(char *line, int *i, int *quoted);
t_token	*token_new(t_token_type type, char *value);
void	token_add_back(t_token **lst, t_token *new);
t_token	*lexer(char *line);

int		is_operator(char c);
void	handle_operator(char *line, int *i, t_token **tokens);
void	handle_input_redir(char *line, int *i, t_token **tokens);
void	handle_output_redir(char *line, int *i, t_token **tokens);
int		handle_word(char *line, int *i, t_token **tokens);

int		ft_isspace(int c);
char	*ft_strjoin_free(char *s1, char *s2);
void	free_tokens(t_token *tokens);
void	free_redirs(t_redir *redir);
void	free_cmds(t_cmd *cmd);

t_cmd	*parse_tokens(t_token *tokens);

int		check_syntax(t_token *tokens);

void	sigint_handler(int sig);
void	init_signals(void);

t_cmd	*start_parsing(char *line);

#endif