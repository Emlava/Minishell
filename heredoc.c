/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 13:57:03 by hudescam          #+#    #+#             */
/*   Updated: 2026/03/20 14:03:47 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	close(0);
}

static void	write_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static char	*join_args(char **argv)
{
	char	*res;
	char	*tmp;
	int		i;

	if (!argv || !argv[0])
		return (ft_strdup(""));
	res = ft_strdup(argv[0]);
	i = 1;
	while (argv[i])
	{
		tmp = ft_strjoin(res, " ");
		free(res);
		res = ft_strjoin(tmp, argv[i]);
		free(tmp);
		i++;
	}
	return (res);
}

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

int	process_heredoc(t_redir *redir, t_exec_resources *res)
{
	int		fd[2];
	char	*line;

	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	if (pipe(fd) == -1)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd[0]);
			close(fd[1]);
			init_signals();
			return (130);
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
	close(fd[1]);
	redir->fd = fd[0];
	init_signals();
	return (0);
}

int	process_all_heredocs(t_cmd *cmds, t_exec_resources *res)
{
	t_cmd	*cmd;
	t_redir	*r;
	int		status;

	cmd = cmds;
	while (cmd)
	{
		r = cmd->redirs;
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
		cmd = cmd->next;
	}
	return (0);
}