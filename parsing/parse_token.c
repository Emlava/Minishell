/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 10:08:00 by hudescam          #+#    #+#             */
/*   Updated: 2026/02/28 02:28:17 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_builtin	get_builtin_type(char *cmd)
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

t_cmd	*cmd_new(void)
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

void	add_arg(t_cmd *cmd, char *value)
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

void	add_redir(t_cmd *cmd, t_token *token)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return ;
	redir->type = get_redir_type(token->type);
	redir->target = token->next->value;
	redir->quoted = token->next->quoted;
	redir->next = NULL;
	redir_add_back(&cmd->redirs, redir);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current;

	head = cmd_new();
	current = head;
	while (tokens)
	{
		handle_token(&current, &tokens);
		tokens = tokens->next;
	}
	return (head);
}
