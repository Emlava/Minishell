/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_management_helper.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:15:46 by hudescam          #+#    #+#             */
/*   Updated: 2026/03/20 19:20:50 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	output_redirection_append(t_redir *redirection_info)
{
	int		target_fd;
	char	*err_str;

	target_fd = open(redirection_info->target,
			O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (target_fd == -1)
	{
		err_str = ft_strjoin("minishell: ", redirection_info->target);
		if (!err_str)
			return (ft_dprintf(2, "minishell: malloc() failure in "
					"output_redirection_append()\n"), 1);
		perror(err_str);
		free(err_str);
		return (2);
	}
	if (dup2(target_fd, STDOUT_FILENO) == -1)
	{
		ft_dprintf(2, "minishell: dup2() failure in "
			"output_redirection_append()\n");
		close(target_fd);
		return (3);
	}
	close(target_fd);
	return (0);
}

int	heredoc_redirection(t_redir *redirection_info)
{
	int		heredoc_fd;

	heredoc_fd = -1;
	while (redirection_info)
	{
		if (redirection_info->type == HEREDOC)
			heredoc_fd = redirection_info->fd;
		redirection_info = redirection_info->next;
	}
	if (heredoc_fd != -1)
	{
		if (dup2(heredoc_fd, STDIN_FILENO) == -1)
		{
			ft_dprintf(2, "minishell: dup2() failure in "
				"output_redirection_append()\n");
			close(heredoc_fd);
			return (1);
		}
		close(heredoc_fd);
	}
	return (0);
}
