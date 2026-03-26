/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:40:35 by hudescam          #+#    #+#             */
/*   Updated: 2026/03/20 18:02:12 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_if_needed(char *line, t_exec_resources *res, int quoted)
{
	t_token	*tokens;
	t_cmd	*cmd;
	char	*result;

	if (quoted)
		return (line);
	tokens = lexer(line, res->local_envp, res->new_exports,
			res->curr_exit_status);
	if (!tokens)
		return (line);
	cmd = parse_tokens(tokens);
	if (!cmd || !cmd->argv)
	{
		free_tokens(tokens);
		if (cmd)
			free_cmds(cmd);
		return (line);
	}
	result = join_args(cmd->argv);
	free_tokens(tokens);
	free_cmds(cmd);
	free(line);
	return (result);
}

static int	handle_null_line(int fd[2])
{
	if (g_signal == 130)
	{
		close(fd[0]);
		close(fd[1]);
		init_signals();
		g_signal = 0;
		return (130);
	}
	return (0);
}

int	process_heredoc_helper(t_redir *redir, int fd[2], t_exec_resources *res)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (handle_null_line(fd) == 130)
				return (130);
			break ;
		}
		if (!ft_strcmp(line, redir->target))
		{
			free(line);
			break ;
		}
		line = expand_if_needed(line, res, redir->quoted);
		write_line(fd[1], line);
		free(line);
	}
	return (0);
}

int	process_all_heredocs_helper(t_redir *r, t_exec_resources *res)
{
	int	status;

	while (r)
	{
		if (r->type == HEREDOC)
		{
			status = process_heredoc(r, res);
			if (status == 130)
			{
				res->curr_exit_status = 130;
				close(0);
				open("/dev/tty", O_RDONLY);
				return (1);
			}
		}
		r = r->next;
	}
	return (0);
}
