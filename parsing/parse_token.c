/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 10:08:00 by hudescam          #+#    #+#             */
/*   Updated: 2026/02/21 11:44:18 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_builtin	get_builtin_type(char *cmd)
{
	if (!cmd)
		return (BUILTIN_NONE);
	if (!ft_strcmp(cmd, "echo"))
		return (BUILTIN_ECHO);
	if (!ft_strcmp(cmd, "cd"))
		return (BUILTIN_CD);
	if (!ft_strcmp(cmd, "pwd"))
		return (BUILTIN_PWD);
	if (!ft_strcmp(cmd, "export"))
		return (BUILTIN_EXPORT);
	if (!ft_strcmp(cmd, "unset"))
		return (BUILTIN_UNSET);
	if (!ft_strcmp(cmd, "env"))
		return (BUILTIN_ENV);
	if (!ft_strcmp(cmd, "exit"))
		return (BUILTIN_EXIT);
	return (BUILTIN_NONE);
}

static t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->builtin = BUILTIN_NONE;
	cmd->next = NULL;
	return (cmd);
}

static void	add_arg(t_cmd *cmd, char *value)
{
	int		i;
	char	**new_argv;

	i = 0;
	while (cmd->argv && cmd->argv[i])
		i++;
	new_argv = malloc(sizeof(char *) * (i + 2));
	if (!new_argv)
		return ;
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[i++] = ft_strdup(value);
	new_argv[i] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

static void	add_redir(t_cmd *cmd, t_token *token)
{
	t_redir	*redir;
	t_redir	*tmp;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return ;
	if (token->type == TOKEN_REDIR_IN)
		redir->type = REDIR_IN;
	else if (token->type == TOKEN_REDIR_OUT)
		redir->type = REDIR_OUT;
	else if (token->type == TOKEN_REDIR_APPEND)
		redir->type = REDIR_APPEND;
	else if (token->type == TOKEN_HEREDOC)
		redir->type = HEREDOC;
	redir->target = token->next->value;
	redir->quoted = token->next->quoted;
	redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		tmp = cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current;

	head = cmd_new();
	current = head;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
		{
			add_arg(current, tokens->value);
			if (!current->argv[1])
				current->builtin = get_builtin_type(current->argv[0]);
		}
		else if (tokens->type == TOKEN_PIPE)
		{
			current->next = cmd_new();
			current = current->next;
		}
		else if (tokens->type == TOKEN_REDIR_IN
			|| tokens->type == TOKEN_REDIR_OUT
			|| tokens->type == TOKEN_REDIR_APPEND
			|| tokens->type == TOKEN_HEREDOC)
		{
			add_redir(current, tokens);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (head);
}
