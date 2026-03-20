/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 13:57:03 by hudescam          #+#    #+#             */
/*   Updated: 2026/03/20 18:02:22 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	close(0);
}

void	write_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

char	*join_args(char **argv)
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

int	process_heredoc(t_redir *redir, t_exec_resources *res)
{
	int		fd[2];
	int		sigc;

	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	if (pipe(fd) == -1)
		return (1);
	sigc = process_heredoc_helper(redir, fd, res);
	if (sigc == 130)
		return (130);
	close(fd[1]);
	redir->fd = fd[0];
	init_signals();
	return (0);
}

int	process_all_heredocs(t_cmd *cmds, t_exec_resources *res)
{
	t_cmd	*cmd;
	t_redir	*r;
	int		sigc;

	cmd = cmds;
	while (cmd)
	{
		r = cmd->redirs;
		sigc = process_all_heredocs_helper(r, res);
		if (sigc == 1)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}
